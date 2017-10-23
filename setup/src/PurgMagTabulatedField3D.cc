//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// Code developed by:
//  S.Larsson and J. Generowicz.
//
//    *************************************
//    *                                   *
//    *    PurgMagTabulatedField3D.cc     *
//    *                                   *
//    *************************************
//
// $Id: PurgMagTabulatedField3D.cc 84477 2014-10-16 08:44:04Z gcosmo $
//

#include "PurgMagTabulatedField3D.hh"
#include "G4SystemOfUnits.hh"
#include "G4AutoLock.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"

namespace{
	G4Mutex myPurgMagTabulatedField3DLock = G4MUTEX_INITIALIZER;
}

PurgMagTabulatedField3D::PurgMagTabulatedField3D(const char* filename,
												  double zOffset  )
:fZoffset(zOffset),invertX(false),invertY(false),invertZ(false)
{
 
	double lenUnit= millimeter;
	double fieldUnit= tesla;
	
	double NominalCurrent=500; //500 mA
	double ActualCurrent=437.5; //437.5 mA quella dichiarata, 476.96 per avere mappa con max 1.26T
	double ScaleFactor=ActualCurrent/NominalCurrent; //0.875 --> 1.155T
	
	//	G4LogicalVolume* logicBend = G4LogicalVolumeStore::GetInstance()->GetVolume("Bend");
	//	G4VPhysicalVolume* physicalBend = G4PhysicalVolumeStore::GetInstance()->GetVolume("Bend");
	//	zOffset=physicalBend->GetTranslation().z();
	G4cout << "\n-----------------------------------------------------------"
	<< "\n      Magnetic field"
	<< "\n-----------------------------------------------------------";
	
	G4cout << "\n ---> " "Reading the field grid from " << filename << " ... " << endl;
	
	//
	//This is a thread-local class and we have to avoid that all workers open the
	//file at the same time
	G4AutoLock lock(&myPurgMagTabulatedField3DLock);
	
	ifstream file( filename ); // Open the file for reading.
	
	if (!file.is_open())
	{
		G4ExceptionDescription ed;
		ed << "Could not open input file " << filename << G4endl;
		G4Exception("PurgMagTabulatedField3D::PurgMagTabulatedField3D",
					"pugmag001",FatalException,ed);
	}
	
	// Ignore first blank line
	char buffer[256];
	file.getline(buffer,256);
	
	// Read table dimensions
	file >> nx >> ny >> nz; // Note dodgy order
	
	G4cout << "  [ Number of values x,y,z: prima di estendere: "
	<< nx << " " << ny << " " << nz << " ] "
	<< endl;
	
	// Set up storage space for table - Crea matrice nx * ny * nz
	xField.resize( nx );
	yField.resize( nx );
	zField.resize( nx );
	int ix, iy, iz;
	for (ix=0; ix<nx; ix++) {
		xField[ix].resize(ny);
		yField[ix].resize(ny);
		zField[ix].resize(ny);
		for (iy=0; iy<ny; iy++) {
			xField[ix][iy].resize(nz);
			yField[ix][iy].resize(nz);
			zField[ix][iy].resize(nz);
		}
	}
	
	// Ignore other header information
	// The first line whose second character is '0' is considered to
	// be the last line of the header.
	do {
		file.getline(buffer,256);  //legge la linea
	} while ( buffer[1]!='0');
	
	// Read in the data
	double xval,yval,zval,bx,by,bz;
	
	//  double permeability; // Not used in this example.
	for (ix=0; ix<nx; ix++) {
		for (iy=0; iy<ny; iy++ /*&& G4cout<<"NUOVO"<<G4endl*/) {
			for (iz=0; iz<nz; iz++) {
				file >> xval >> yval >> zval >> bx >> by >> bz;  	// estrae i valori
		  if ( ix==0 && iy==0 && iz==0 ) {
			  minx = xval * lenUnit;
			  miny = yval * lenUnit;
			  minz = zval * lenUnit;
		  }
			
				
				xField[ix][iy][iz] = -1*bx *ScaleFactor * fieldUnit;
				yField[ix][iy][iz] = -1*by *ScaleFactor * fieldUnit;
				zField[ix][iy][iz] = -1*bz *ScaleFactor * fieldUnit;
			/*
				if (fabs(xField[ix][iy][iz])>BxMax) BxMax=xField[ix][iy][iz];
				if (fabs(yField[ix][iy][iz])>ByMax) ByMax=yField[ix][iy][iz];
				if (fabs(zField[ix][iy][iz])>BzMax) BzMax=zField[ix][iy][iz];
*/
				if (bx*fieldUnit>BxMax) BxMax=bx*fieldUnit;
				if (by*fieldUnit>ByMax) ByMax=by*fieldUnit;
				if (bz*fieldUnit>BzMax) BzMax=bz*fieldUnit;
				//Max Field Value: Bx= 1.8064, By= 2.41933, Bz= 0.51616
				
				//				1.3208538 is max By value in Map
				//						  	  if ( ix>=nx*0.7 && iy>=ny*0.7 && iz>=nz*0.7 ) {
//				G4cout<<"######### bx, by, bz SCALED = "<<xField[ix][iy][iz]<<" "<<yField[ix][iy][iz]/tesla<<" "<<zField[ix][iy][iz]<<G4endl;
	//			G4cout<<"# xval, yval, zval = "<<xval<<" "<<yval<<" "<<zval<<G4endl;
		//		G4cout<<"## bx, by, bz SCALED = "<<xField[ix][iy][iz]<<" "<<yField[ix][iy][iz]/tesla<<" "<<zField[ix][iy][iz]<<G4endl<<G4endl;
				if ( 0) { //magnetic field debug
					G4cout<<"### ix = "<<ix<<", iy "<<iy<<", iz "<<iz<<G4endl;
					G4cout<<"### nx0-1+ix = "<<nx0-1+ix<<", ny0-1+iy "<<ny0-1+iy<<", nz0-1+iz "<<nz0-1+iz<<G4endl;
					G4cout<<"### xval, yval, zval = "<<xval<<" "<<yval<<" "<<zval<<G4endl;
					G4cout<<"######### bx, by, bz ORIG = "<<bx<<" "<<by/tesla<<" "<<bz<<G4endl;
					G4cout<<"######### bx, by, bz SCALED = "<<xField[ix][iy][iz]<<" "<<yField[ix][iy][iz]/tesla<<" "<<zField[ix][iy][iz]<<G4endl;
				}
				
				
				
				/*
				xField[nx0-1+ix][ny0-1+iy][nz0-1+iz] = bx * fieldUnit;
		  yField[nx0-1+ix][ny0-1+iy][nz0-1+iz] = by * fieldUnit;
		  zField[nx0-1+ix][ny0-1+iy][nz0-1+iz] = bz * fieldUnit;

				
				xField[nx0-1-ix][ny0-1-iy][nz0-1-iz] = bx * fieldUnit;
		  yField[nx0-1-ix][ny0-1-iy][nz0-1-iz] = by * fieldUnit;
		  zField[nx0-1-ix][ny0-1-iy][nz0-1-iz] = bz * fieldUnit;
				 */
				
			}
		}
	}
	file.close();
	
	lock.unlock();
	
	maxx = xval * lenUnit;
	maxy = yval * lenUnit;
	maxz = zval * lenUnit;
	
	G4cout << "\n ---> ... done reading " << endl;
	
	// G4cout << " Read values of field from file " << filename << endl;
	G4cout << " ---> assumed the order:  x, y, z, Bx, By, Bz "
	<< "\n ---> Min values x,y,z: "
	<< minx/cm << " " << miny/cm << " " << minz/cm << " cm "
	<< "\n ---> Max values x,y,z: "
	<< maxx/cm << " " << maxy/cm << " " << maxz/cm << " cm "
	<< "\n ---> The field will be offset by " << zOffset/cm << " cm " << endl;
	
	// Should really check that the limits are not the wrong way around.
	if (maxx < minx) {swap(maxx,minx); invertX = true;}
	if (maxy < miny) {swap(maxy,miny); invertY = true;}
	if (maxz < minz) {swap(maxz,minz); invertZ = true;}
	G4cout << "\nAfter reordering if neccesary"
	<< "\n ---> Min values x,y,z: "
	<< minx/cm << " " << miny/cm << " " << minz/cm << " cm "
	<< " \n ---> Max values x,y,z: "
	<< maxx/cm << " " << maxy/cm << " " << maxz/cm << " cm ";
	
	dx = maxx - minx;
	dy = maxy - miny;
	dz = maxz - minz;
	G4cout << "\n ---> Dif values x,y,z (range): "
	<< dx/cm << " " << dy/cm << " " << dz/cm << " cm in z "
	<< "\n-----------------------------------------------------------" << endl;
	
	G4cout <<"Max Field Value: Bx= "<<
	BxMax/tesla<<", By= "<<
	ByMax/tesla<<", Bz= "<<
	BzMax/tesla
	<<G4endl;
	
	G4cout <<"Max Field Value After Scaling: Bx= "<<
	BxMax*ScaleFactor/tesla<<", By= "<<
	ByMax*ScaleFactor/tesla<<", Bz= "<<
	BzMax*ScaleFactor/tesla
	<<G4endl;
}

void PurgMagTabulatedField3D::GetFieldValue(const double point[4],
											double *Bfield ) const
{
	/* //ORIGINAL VERSION
	double x = point[0];
	double y = point[1];
	double z = point[2] + fZoffset;
	*/

	double x, y, z;
	if (point[0]<0) {
		x=fabs(point[0]);
//		cout <<"lemmaDEBUG invertito segno a x"<<endl;
	} else {
		x = point[0];
	}
	if (point[1]<0) {
		y=fabs(point[1]);
//		cout <<"lemmaDEBUG invertito segno a y"<<endl;
	} else {
		y = point[1];
	}
//	if (point[2]<0) {   //corrected Zoffset problem by collamaf - 23.10.2017
		z=fabs(point[2]-fZoffset);
//		cout <<"lemmaDEBUG invertito segno a z"<<endl;
//	} else {
//		z = point[2]+ fZoffset;
//	}
	
	// Check that the point is within the defined region
	if ( x>=minx && x<=maxx &&
		y>=miny && y<=maxy &&
		z>=minz && z<=maxz ) {
		
		// Position of given point within region, normalized to the range
		// [0,1]
		double xfraction = (x - minx) / dx;
		double yfraction = (y - miny) / dy;
		double zfraction = (z - minz) / dz;
		
		if (invertX) { xfraction = 1 - xfraction;}
		if (invertY) { yfraction = 1 - yfraction;}
		if (invertZ) { zfraction = 1 - zfraction;}
		
		// Need addresses of these to pass to modf below.
		// modf uses its second argument as an OUTPUT argument.
		double xdindex, ydindex, zdindex;
		
		// Position of the point within the cuboid defined by the
		// nearest surrounding tabulated points
		double xlocal = ( std::modf(xfraction*(nx-1), &xdindex));
		double ylocal = ( std::modf(yfraction*(ny-1), &ydindex));
		double zlocal = ( std::modf(zfraction*(nz-1), &zdindex));
		
		// The indices of the nearest tabulated point whose coordinates
		// are all less than those of the given point
		int xindex = static_cast<int>(xdindex);
		int yindex = static_cast<int>(ydindex);
		int zindex = static_cast<int>(zdindex);
		
#if 0
		G4cout << "Local x,y,z: " << xlocal << " " << ylocal << " " << zlocal << endl;
		G4cout << "Index x,y,z: " << xindex << " " << yindex << " " << zindex << endl;
#endif
		
#ifdef DEBUG_INTERPOLATING_FIELD
		G4cout << "Local x,y,z: " << xlocal << " " << ylocal << " " << zlocal << endl;
		G4cout << "Index x,y,z: " << xindex << " " << yindex << " " << zindex << endl;
		double valx0z0, mulx0z0, valx1z0, mulx1z0;
		double valx0z1, mulx0z1, valx1z1, mulx1z1;
		valx0z0= table[xindex  ][0][zindex];  mulx0z0=  (1-xlocal) * (1-zlocal);
		valx1z0= table[xindex+1][0][zindex];  mulx1z0=   xlocal    * (1-zlocal);
		valx0z1= table[xindex  ][0][zindex+1]; mulx0z1= (1-xlocal) * zlocal;
		valx1z1= table[xindex+1][0][zindex+1]; mulx1z1=  xlocal    * zlocal;
#endif
		
		//	  G4cout<<" lemmaDEBUG  FUNZIO"<<G4endl;
		
		// Full 3-dimensional version
		Bfield[0] =
		xField[xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
		xField[xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
		xField[xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
		xField[xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
		xField[xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
		xField[xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
		xField[xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
		xField[xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;
		Bfield[1] =
		yField[xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
		yField[xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
		yField[xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
		yField[xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
		yField[xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
		yField[xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
		yField[xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
		yField[xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;
		Bfield[2] =
		zField[xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
		zField[xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
		zField[xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
		zField[xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
		zField[xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
		zField[xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
		zField[xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
		zField[xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;
		
	} else {
		//	  G4cout<<" lemmaDEBUG NON FUNZIO"<<G4endl;
		Bfield[0] = 0.0;
		Bfield[1] = 0.0;
		Bfield[2] = 0.0;
	}
}

