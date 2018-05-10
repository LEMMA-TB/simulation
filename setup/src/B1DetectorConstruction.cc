#include "B1DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4PVReplica.hh"
#include <G4UIcommand.hh>
#include <G4String.hh>
#include "G4CrystalExtension.hh"
#include "G4ExtendedMaterial.hh"
#include "G4LogicalCrystalVolume.hh"
#include "G4ChannelingMaterialData.hh"
#include "G4ChannelingOptrMultiParticleChangeCrossSection.hh"
#include "PurgMagTabulatedField3D.hh"
#include "G4LogicalVolumeStore.hh"
//------------------------------
//#include "G4PhysicalVolumeStore.hh"
#include "G4RegionStore.hh"
#include <G4Region.hh>
#include "G4ProductionCuts.hh"
//------------------------------
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Transform3D.hh"
#include <G4ChordFinder.hh>
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SubtractionSolid.hh"



B1DetectorConstruction::B1DetectorConstruction(G4bool MuonBeamFlag, G4bool ElectronBeamFlag, G4bool TargetFlag, G4bool FlipFieldFlag, G4bool MagMapFlag)
: G4VUserDetectorConstruction(),
fScoringVolume_Trk1(0),
fScoringVolume_Trk2(0),
fScoringVolume_T1(0),
fScoringVolume_Trk3(0),
fScoringVolume_Trk4(0),
fScoringVolume_Trk5a(0),
fScoringVolume_Trk5b(0),
fScoringVolume_Trk6a(0),
fScoringVolume_Trk6b(0),
fScoringVolume_Chamber(0),
fScoringVolume_ScintA(0),
fScoringVolume_ScintB(0),
fScoringVolume_Ecal(0),
fScoringVolume_Gcal(0),
fScoringVolume_Cerenkov(0),
fScoringVolume_PbGlass(0),
//fMuonBeamFlag(MuonBeamFlag),
//fElectronBeamFlag(ElectronBeamFlag),
fTargetFlag(TargetFlag),
fFlipFieldFlag(FlipFieldFlag),
fMagMapFlag(MagMapFlag)
{ }


B1DetectorConstruction::~B1DetectorConstruction()
{}


G4VPhysicalVolume* B1DetectorConstruction::Construct(){
	
	// =============================
	// Detector parameters and size
	// =============================
	
	G4bool Si30Shift=false; //toggle shift of Si30 wrt beam center
	
	//--> WORLD:
	G4double world_sizeX = 4*m;
	G4double world_sizeY = 3*m;
	G4double world_sizeZ = 80*m;
	
	//--> trackers (TrkX): Si-trackers
	G4double trk_sizeXa = 2*cm; 
	G4double trk_sizeYa = 2*cm;
	G4double trk_sizeXb = 10*cm;
	G4double trk_sizeYb = 10*cm;
	G4double trk_sizeZ1 = 0.2*mm;
	G4double trk_sizeZ2 = 0.2*mm;
	G4double trk_sizeZ3 = 0.4*mm;
	G4double trk_sizeZ4 = 0.8*mm;
	G4double trk_sizeZ5 = 0.8*mm;
	G4double trk_sizeZ6 = 0.8*mm;
	
	G4double Si30Box_sizeX=125*mm;
	G4double Si30Box_sizeY=125*mm;
	G4double Si30Box_sizeZ=45*mm; //was 40...
	G4double Si30Box_AluThicknessX=10*mm;
	G4double Si30Box_AluThicknessY=10*mm;
	G4double Si30Box_AluThicknessZ=3.3*mm;
	G4double Si30AluBar_sizeX=100*mm;
	G4double Si30AluBar_sizeY=13*mm;
	G4double Si30AluBar_sizeZ=13*mm;
	G4double DistXSi30Bar=0;
	G4double DistYSi30Bar=-Si30Box_sizeY/2.+Si30Box_AluThicknessY+Si30AluBar_sizeY/2.;
	G4double DistZSi30Bar=-Si30Box_sizeZ/2.+Si30Box_AluThicknessZ+Si30AluBar_sizeZ/2.;
	G4double Si30Vetronite_sizeX=100*mm;
	G4double Si30Vetronite_sizeY=100*mm;
	G4double Si30Vetronite_sizeZ=11*mm;

	//--> Be amorphous crystal target:
	//	G4double cry_sizeX = 5.*cm;
	//	G4double cry_sizeY = 5.*cm;
	//	G4double cry_sizeZ = 60.*mm;
	G4double target_R = 2.5*cm;
	G4double target_Z = 60*mm; //was "30" till 2017.12.29
	
	//--> dipole magnet
	G4double innerRadius = 0.*cm;
	G4double outerRadius = 100.*cm;
	G4double hBdipole = 20.*cm; // half-height
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;
	
	//--> Beam Pipe
	G4double PipeinnerRadius = 0*cm;
	G4double PipeouterRadius = 10.*cm;
	G4double PipeH12 = 474.8*cm;
	G4double PipeH34 = 492.3*cm;
	
	// G-cal:
	G4double Gcal_sizeX = 13.5*cm;
	G4double Gcal_sizeY = 13.5*cm;
	G4double Gcal_sizeZ = 230.*mm; // ~25Xo
	
	// Iron blocks:
	G4double Iblock_sizeX = 20*cm;
	G4double Iblock_sizeY = 20*cm;
	G4double Iblock_sizeZ = 400*mm;
	
	// Iron column:
	G4double Icol_sizeX = 30*cm;
	G4double Icol_sizeY = 100*cm;
	G4double Icol_sizeZ = 30*cm;
	
	// E-cal: "DEVA" - this is the alluminum container
	G4double DEVAenv_sizeX = 22*cm;
	G4double DEVAenv_sizeY = 30*cm;
	G4double DEVAenv_sizeZ = 400.*mm; // ~23Xo
	
	// DEVA Active element - this is the active element
	G4double DEVAact_sizeX = 15.*cm;
	G4double DEVAact_sizeY = 15.*cm;
	G4double DEVAact_sizeZ = 2.*cm;
	
	// DEVA Active element - this is the active element
	G4double DEVAabs_sizeX = 12.*cm;
	G4double DEVAabs_sizeY = 12.*cm;
	G4double DEVAabs_sizeZ = .5*cm;
	G4double DEVAabs_sizeZbis = 1.*cm;
	
	// shield wall:
	G4double shield_sizeX = 1.62*m;
	G4double shield_sizeY = 2.6*m;
	G4double shield_sizeZ = 0.4*m;
	
	//--> detectors (D-ghost): // ghost-detectors
	G4double Chamber_sizeX = 2.55*m;
	G4double Chamber_sizeY = 2.55*m;
	G4double Chamber_sizeZTot = 29*cm; //entire chamber
	G4double Chamber_sizeZ = 0.1*cm; //chamber layer is 1.2, but use smaller value since we just use z position
	
	// Scintillator A behind T6a:
	G4double ScintA_sizeX = 10*cm;
	G4double ScintA_sizeY = 4*cm;
	G4double ScintA_sizeZ = 2*cm;
	
	// Scintillator B behind T6b:
	G4double ScintB_sizeX = 10*cm;
	G4double ScintB_sizeY = 10*cm;
	G4double ScintB_sizeZ = 2*cm;
	
	// Lead Glass :
	G4double LeadGlass_sizeX = 40*cm;
	G4double LeadGlass_sizeY = 11.5*cm;
	G4double LeadGlass_sizeZ = 11.5*cm;
	
	// Cerenkov counter and various elements:
	G4double Cerenkov_sizeX = 30*cm;
	G4double Cerenkov_sizeY = 30*cm;
	G4double Cerenkov_sizeZ = 868.6*mm;
	G4double Cerenkov_AluZ = 4*mm;
	G4double Cerenkov_SiOX = 29.5*cm;
	G4double Cerenkov_SiOZ = 25.4*mm;
	G4double Cerenkov_SiOY = Cerenkov_SiOZ;
	G4double Cerenkov_AirZ = 209.4*mm;
	G4double Cerenkov_Air2Z = 100*mm;
	G4double Cerenkov_FeX = Cerenkov_SiOX;
	G4double Cerenkov_FeY = 3*Cerenkov_SiOY;
	G4double Cerenkov_FeZ = 500*mm;
	
	
	/*
	 
	 |— 4mm —|——— 25,6 mm ———|———— 309,4 aria + 500mm acciaio —————|——— 25,6 mm ———|— 4mm —|
	 Al			SiO2						Fe						SiO2		  Al
	 
	 */
	
	// ============
	//   positions
	// ============
	G4double xTrk5a=3.9*cm+trk_sizeXb/2.; //Det 51
	G4double xTrk5b=-5*cm-trk_sizeXb/2.; //Det 50
	G4double zTrk5=1563*cm;
	G4double zBendMagn=zTrk5-260*cm;  //1563-260=1303
	
	//	G4double xTrk6=14.85*cm+trk_sizeXb/2.; //before 2017-11-28
	//	G4double zTrk6=2137.4*cm;   //before 2017-11-28
//	G4double xTrk6=10.5*cm+2.6*cm+trk_sizeXb/2.; //before 3.3.18
	G4double xTrk6a=11.3*cm+trk_sizeXb/2.; //Det 56
	G4double xTrk6b=-12.5*cm-trk_sizeXb/2.; //Det 55
	//	G4double zTrk6=1852*cm; //correcting for 280cm pre T1 offset
	G4double zTrk6=1776*cm; //believing my measured distance from last geom measurement: 2137.4-280=1852 is measured by geom, but then was moved by Mario and Fabio to match the beam. At the end I add 213cm fro T5 -> 1776cm
	
	//	G4double xScintA=5.1*cm+ScintA_sizeX/2.;
	//	G4double zCalo=2941*cm; //before 2017-11-28
	G4double zCalo=zTrk6+804*cm; //=2580 using measured distance from T5
	
	//	G4double zChamber=3132.4*cm;//before 2017-11-28
	G4double zChamber=zTrk6+995*cm;//=2771 using measured distance from T5
	
	//	G4double zShield=3082.4*cm;//before 2017-11-28
	G4double zShield=zChamber-70*cm; //=2701 using measured distance from chamber
	
	
	//	G4double zLeadGlass=3132.4*cm+29*cm+10*cm;//before 2017-11-28
	G4double zLeadGlass=zChamber+29*cm+10*cm; //= 2810 using measured distance from chamber
	
	//	G4double zCerenkov=3132.4*cm+29*cm+10*cm + 10*cm + LeadGlass_sizeZ/2. + Cerenkov_sizeZ/2.;//before 2017-11-28
	G4double zCerenkov=zChamber+29*cm+10*cm + LeadGlass_sizeZ; //= BOH using measured distance from chamber
	// ############################################
	// ##########################
	G4double CaloOffset=-.0*cm; //post 2017-11-29: 0 cm becca bene, 5 cm spizza, 10 quasi tutto fuori (OLD 5cm iniziale - 15cm per iniziare a beccarlo al bordo sotto - 20cm sembra ben centrato) per 22GeV
	// ##########################
	// ############################################
	G4double DistXGcalIron=5*cm;
	G4double DistXIronEcal=4*cm; //was 2, but 4 fits better photos
	G4double DistXEcalColumn=10*cm;
	G4double DistZGcalIron=5*cm;
	G4double DistLeadCerenkov=10*cm;
	G4double ChamberOffsetX=3*cm;
	G4double X3Corr=-1.052*cm; //was 1.cm according to exp data, changed to 0 on 2018-01-31 by collamaf after discussion with Bertolin - changed to -1.052cm on 3-3-18 according to M Rotondo
	G4double Y3Corr=-.885*cm; //was -.5cm according to exp data, changed to 0 on 2018-01-31 by collamaf after discussion with Bertolin - changed to -0.885cm on 3-3-18 according to M Rotondo
	if (!Si30Shift) {
		X3Corr=0;
		Y3Corr=0;
	}
	G4double ChamberLayerZ[12]={-10.75*cm, -9.45*cm, -8.15*cm, -6.85*cm,  7.45*cm, 8.75*cm, 10.05*cm,11.35*cm, 12.85*cm, 14.15*cm, 15.45*cm, 16.75*cm}; //meas. from Bertolin
	//	G4double ChamberLayerZ[12]={0*cm, 1.5*cm, 3*cm, 4.5*cm, 6*cm, 7.5*cm, 9*cm, 10.5*cm, 12*cm, 13.5*cm, 15*cm, 16.5*cm};
	
	
	G4ThreeVector posTrk1  = G4ThreeVector(0.,0.,0*mm); // Si-Trk1  Subdet 10
	G4ThreeVector posPipe12  = G4ThreeVector(0.,0.,277.4*cm); // Pipe between T1 and T2
	G4ThreeVector posTrk2  = G4ThreeVector(0.,0.,516.8*cm); // Si-Trk2  Subdet 20
	G4ThreeVector posTarg1 = G4ThreeVector(0.,0.,545.8*cm); // TARGET
	G4ThreeVector posTrk3  = G4ThreeVector(X3Corr,Y3Corr,577.8*cm); // Si-Trk3  Subdet 30
	G4ThreeVector Hole30Shift= G4ThreeVector(2.35*cm,2.65*cm,0); //calculated to have the active area @e.6cm from bottom and 2.9 cm from right edges
	G4ThreeVector posBox30  = posTrk3+Hole30Shift; // Si-Trk3  Subdet 30
	G4ThreeVector posVetronite30  = posTrk3+Hole30Shift; // Si-Trk3  Subdet 30
//	G4ThreeVector posAlu30Bar  = G4ThreeVector(DistXSi30Bar,DistYSi30Bar,DistZSi30Bar); // added on 2018.03.28
//	G4ThreeVector posAlu30Bar  = G4ThreeVector(posTrk3.x()+DistXSi30Bar,posTrk3.y()+DistYSi30Bar,posTrk3.z()+DistZSi30Bar); // added on 2018.03.28
	G4ThreeVector posAlu30Bar  = posBox30+G4ThreeVector(DistXSi30Bar, DistYSi30Bar, DistZSi30Bar); // added on 2018.03.28
	G4ThreeVector posTrk3HoleF  = G4ThreeVector(0,0,-Si30Box_sizeZ/2.+Si30Box_AluThicknessZ/2.)-Hole30Shift; // added on 2018.03.28
	G4ThreeVector posTrk3HoleB  = G4ThreeVector(0,0,Si30Box_sizeZ/2.-Si30Box_AluThicknessZ/2.)-Hole30Shift; // added on 2018.03.28
	G4ThreeVector posPipe34  = G4ThreeVector(0.,0.,903.95*cm); // Pipe between T3 and T4
	G4ThreeVector posTrk4  = G4ThreeVector(0.,0.,1152.1*cm); // Si-Trk4  Subdet 40
	G4ThreeVector posBend  = G4ThreeVector(0.,0.,zBendMagn); // Dipole magnet center era 1203
	G4ThreeVector posTrk5a  = G4ThreeVector(xTrk5a,0.,zTrk5); // Si-Trk5a
	G4ThreeVector posTrk5b  = G4ThreeVector(xTrk5b,0.,zTrk5); // Si-Trk5b
	G4ThreeVector posTrk6a  = G4ThreeVector(xTrk6a,0.,zTrk6); // Si-Trk6a
	G4ThreeVector posTrk6b  = G4ThreeVector(xTrk6b,0.,zTrk6); // Si-Trk6b
	G4ThreeVector posScintA  = G4ThreeVector(xTrk6a,0.,zTrk6+ScintA_sizeZ/2.+1*cm); // ScintA behind T6a
	G4ThreeVector posScintB  = G4ThreeVector(xTrk6b,0.,zTrk6+ScintB_sizeZ/2.+1*cm); // ScintB behind T6b
	G4ThreeVector posGcal  = G4ThreeVector(CaloOffset,0.,zCalo+Gcal_sizeZ/2.); // GCAL center
	G4ThreeVector posIblock  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX/2.+DistXGcalIron,0.,zCalo+Iblock_sizeZ/2.+DistZGcalIron); // Iron Block center
	G4ThreeVector posEcal  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX+DistXIronEcal+DistXGcalIron+DEVAenv_sizeX/2.,0.,zCalo+DEVAenv_sizeZ/2.); // ECAL center
	//	G4ThreeVector posEcalDummy  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX+DistXIronEcal+DistXGcalIron+DEVAenv_sizeX/2.,0.,zCalo-1*cm/2); // ECALDummy center
	G4ThreeVector posEcalDummy  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX+DistXIronEcal+DistXGcalIron+DEVAenv_sizeX/2.,0.,zCalo+DEVAenv_sizeZ/2.); // ECALDummy center
	G4ThreeVector posDevaAct=G4ThreeVector(0, 0, 0);
	G4ThreeVector posDevaAbs=G4ThreeVector(0, 0, 0);
	
	G4ThreeVector posIcol  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX+DistXIronEcal+DistXGcalIron+DEVAenv_sizeX+Icol_sizeX/2.+DistXEcalColumn,0.,zCalo+Icol_sizeZ/2.); // ECAL center
	
	
	//	 G4Transform3D transform1 = G4Transform3D(rotEcal,posEcal);
	G4ThreeVector posShield= G4ThreeVector(92.7/2.*cm,0.*cm,zShield+shield_sizeZ/2.); // Shield center
	G4ThreeVector posChamber  = G4ThreeVector(ChamberOffsetX,0.,zChamber); // D-ghost Subdet 70
	G4ThreeVector posLeadGlass  = G4ThreeVector(-40*cm-LeadGlass_sizeX/2.,0.,zLeadGlass+LeadGlass_sizeZ/2.);
	
	
	// ################################
	// CERENKOV DETECTOR ELEMENTS
	G4ThreeVector posCerenkov  = G4ThreeVector(-40*cm-LeadGlass_sizeX/2.,0.,zCerenkov+ Cerenkov_sizeZ/2.+DistLeadCerenkov);  //centered behing LeadGlass
	
	G4ThreeVector posCerenkovAlu1  = G4ThreeVector(0, 0,-Cerenkov_sizeZ/2.+Cerenkov_AluZ/2.); //in Cerenkov mother volume
	
	G4ThreeVector posCerenkovSiO1A  = G4ThreeVector(0, -Cerenkov_SiOY,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ/2); //in Cerenkov mother volume
	G4ThreeVector posCerenkovSiO1B  = G4ThreeVector(0, 0,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ/2); //in Cerenkov mother volume
	G4ThreeVector posCerenkovSiO1C  = G4ThreeVector(0, +Cerenkov_SiOY,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ/2); //in Cerenkov mother volume
	
	G4ThreeVector posCerenkovFe  = G4ThreeVector(0, 0,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ+Cerenkov_AirZ+Cerenkov_FeZ/2.); //in Cerenkov mother volume
	
	G4ThreeVector posCerenkovSiO2A  = G4ThreeVector(0, -Cerenkov_SiOY,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ+Cerenkov_AirZ+Cerenkov_FeZ +Cerenkov_Air2Z +Cerenkov_SiOZ/2.); //in Cerenkov mother volume
	G4ThreeVector posCerenkovSiO2B  = G4ThreeVector(0, 0,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ+Cerenkov_AirZ+Cerenkov_FeZ +Cerenkov_Air2Z +Cerenkov_SiOZ/2.); //in Cerenkov mother volume
	G4ThreeVector posCerenkovSiO2C  = G4ThreeVector(0, +Cerenkov_SiOY,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ+Cerenkov_AirZ+Cerenkov_FeZ +Cerenkov_Air2Z +Cerenkov_SiOZ/2.); //in Cerenkov mother volume
	
	G4ThreeVector posCerenkovAlu2  = G4ThreeVector(0, 0,-Cerenkov_sizeZ/2.+Cerenkov_AluZ+Cerenkov_SiOZ+Cerenkov_AirZ+Cerenkov_FeZ +Cerenkov_Air2Z +Cerenkov_SiOZ+Cerenkov_AluZ/2.); //in Cerenkov mother volume
	//##################################
	
	
	G4double EcalAngle=1*7.94*CLHEP::deg;
	//G4RotationMatrix* rotEcal = new G4RotationMatrix;
	G4RotationMatrix rotEcal;
	rotEcal.rotateY(EcalAngle); // add rotation angle of the crystal here
	//	G4Transform3D translateEcal = HepGeom::Translate3D(7*cm*sin(EcalAngle), 7*cm*cos(EcalAngle), 0);
	G4Transform3D translateEcal = HepGeom::Translate3D(7*cm*sin(EcalAngle), 0, -7*cm*cos(EcalAngle));
	//	G4Transform3D translateEcalDummy = HepGeom::Translate3D((7.5*cm+1*DEVAenv_sizeZ/2.)*sin(EcalAngle), 0, -(7.5*cm+1*DEVAenv_sizeZ/2.)*cos(EcalAngle));
	G4Transform3D translateEcalDummy = HepGeom::Translate3D(0,0,-(7.69*cm+1*DEVAenv_sizeZ/2.)*cos(EcalAngle));
	//	G4Transform3D translateEcalDummy = HepGeom::Translate3D((7*cm)*sin(EcalAngle), 0, -(7*cm)*cos(EcalAngle));
	G4cout<<"DEBUG "<<(7*cm+DEVAenv_sizeZ/2.)*sin(EcalAngle)/cm<<G4endl;
	G4cout<<"DEBUG "<<-(7*cm+DEVAenv_sizeZ/2.)*cos(EcalAngle)/cm<<G4endl;
	G4Transform3D rotateEcal(rotEcal,posEcal);
	G4Transform3D rotateEcalDummy(rotEcal,posEcalDummy);
	
	// ================
	// define materials
	// ================
	
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* vuoto = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* aria = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* berillio = nist->FindOrBuildMaterial("G4_Be");
	G4Material* silicio = nist->FindOrBuildMaterial("G4_Si");
	G4Material* ferro = nist->FindOrBuildMaterial("G4_Fe");
	G4Material* plastica = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	G4Material* alluminium = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
	G4Material* piombo = nist->FindOrBuildMaterial("G4_Pb");

	// ================
	// Optical parameters for Cerenkov detectors
	// ================
	
	//Cerenkov counter
	const G4int nCerPointsCer = 7;
	G4double photonEnergyCer[nCerPointsCer] = {6.2*eV, 3.1*eV, 1.55*eV, 1*eV, .775*eV, .517*eV, .387*eV};
	G4double refractiveIndex_silica[nCerPointsCer] = {1.5, 1.48, 1.457, 1.446, 1.44, 1.43, 1.411 };
	G4MaterialPropertiesTable* silicaOP = new G4MaterialPropertiesTable();
	silicaOP->AddProperty("RINDEX", photonEnergyCer, refractiveIndex_silica, nCerPointsCer);

	//Lead Glass counter
	const G4int nCerPointsPb = 1;
//	G4double photonEnergyPb[nCerPointsPb] = {6.2*eV, 2.85*eV, 2.55*eV, 2.27*eV, 2.10*eV, 1.88*eV, .387*eV};
//	G4double refractiveIndex_Pb[nCerPointsPb] = {1.674, 1.674, 1.661, 1.652, 1.648, 1.642, 1.642};
	G4double photonEnergyPb[nCerPointsPb]={2.11577*eV}; //586nm
	G4double refractiveIndex_Pb[nCerPointsPb]={1.8467};
	//as referenced in:
	/*
	 SF57 lead glass, from Schott Glaswerke, Hattenbergstrasse 10, D-6500 Mainz 1, Germany. This glass has the following properties: 75% by weight PbO, density 5.54 g cm−3, X0 = 1.50 cm, and refractive index 1.8467 at λ = 586 nm.
	 https://www.sciencedirect.com/science/article/pii/0168900291905474
	 */
	G4MaterialPropertiesTable* PBOP = new G4MaterialPropertiesTable();
	PBOP->AddProperty("RINDEX", photonEnergyPb, refractiveIndex_Pb, nCerPointsPb);
//	PBOP->AddProperty("RINDEX", photonEnergyCer, refractiveIndex_silica, nCerPointsCer);

	//	if (fMuonBeamFlag || fElectronBeamFlag) berillio=nist->FindOrBuildMaterial("G4_Galactic");;  //if MuonBeam case I want no target
	if (!fTargetFlag) berillio=nist->FindOrBuildMaterial("G4_Galactic");;  //if I do not want the target
	//--PbWO4 G-CAL crystal (CMS)
	G4double A,Z,d;
	d=8.28*g/cm3;
	A=16.00*g/mole; Z=8; G4Element* elO = new G4Element("Oxygen","O2",Z,A);
	A=183.84*g/mole; Z=74; G4Element* elW = new G4Element("Tungsten","W",Z,A);
	A=207.20*g/mole; Z=82; G4Element* elPb = new G4Element("Lead","Pb",Z,A);
	G4Material* PbWO4= new G4Material("PbWO4",d,3);
	G4int natoms;
	PbWO4->AddElement(elO,natoms=4);
	PbWO4->AddElement(elW,natoms=1);
	PbWO4->AddElement(elPb,natoms=1);
	
	G4Element* elSi = new G4Element("Silicon" ,"Si" , 14., 28.09*g/mole);
	

	
	
	G4Material* SiO2 =
	new G4Material("quartz",d= 2.200*g/cm3, natoms=2);
	SiO2->AddElement(elSi, natoms=1);
	SiO2->AddElement(elO , natoms=2);
//	SiO2->SetMaterialPropertiesTable(silicaOP);  //toggle cerenkov in SiO2
	
	A=1.008*g/mole; Z=1; G4Element* elH = new G4Element("Hydrogen","H",Z,A);
	A=12.011*g/mole; Z=6; G4Element* elC = new G4Element("Carbon","C",Z,A);
	//Epoxy (for FR4 )
	d = 1.2*g/cm3;
	G4Material* Epoxy = new G4Material("Epoxy" , d, 2);
	Epoxy->AddElement(elH, natoms=2);
	Epoxy->AddElement(elC, natoms=2);
	
	
	//FR4 (Glass + Epoxy)
	d = 1.86*g/cm3;
	G4Material* FR4 = new G4Material("FR4"  , d, 2);
	FR4->AddMaterial(SiO2, 0.528);
	FR4->AddMaterial(Epoxy, 0.472);

	// lead glass
	G4Material* PbGl = new G4Material("Lead Glass", d= 3.85*g/cm3,
									  natoms=2);
	PbGl->AddElement(elPb, 0.5316);
	PbGl->AddMaterial(SiO2, 0.4684);
//	PbGl->SetMaterialPropertiesTable(silicaOP);  //toggle cerenkov in PbGlass - CHECK I leave silicaOP because real PbGlass parameter seem not to work
	
	G4bool checkOverlaps = true;
	
	// ================
	// build detector
	// ================
	
	//-- WORLD
	G4Box* solidWorld = new G4Box("World",world_sizeX/2,world_sizeY/2,world_sizeZ/2);
	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, aria, "World");
	G4VPhysicalVolume* physWorld = new G4PVPlacement
	(0,                    // no rotation
	 G4ThreeVector(),       // centre position
	 logicWorld,            // its logical volume
	 "World",               // its name
	 0,                     // its mother volume
	 false,                 // no boolean operation
	 0,                     // copy number
	 checkOverlaps);        // overlaps checking
	G4LogicalVolume* logicTarg;
	G4LogicalCrystalVolume* crystalLogic;
	
	//-- TARGET
	if ( channeling==true ){
		//-- Crystal TARGET
		G4double crystalSizeXY = 50. * CLHEP::millimeter;
		G4double crystalSizeZ = 1. * CLHEP::millimeter; // modify crystal size along beam
		G4Box* crystalSolid = new G4Box("crystal.solid",crystalSizeXY/2.,crystalSizeXY/2.,crystalSizeZ/2.);
		//   G4Material* silicon = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
		G4ExtendedMaterial* Crystal = new G4ExtendedMaterial("crystal.material",silicio);
		Crystal->RegisterExtension(std::unique_ptr<G4CrystalExtension>(new G4CrystalExtension(Crystal)));
		G4CrystalExtension* crystalExtension = (G4CrystalExtension*)Crystal->RetrieveExtension("crystal");
		crystalExtension->SetUnitCell(new G4CrystalUnitCell(5.43 * CLHEP::angstrom,
															5.43 * CLHEP::angstrom,
															5.43 * CLHEP::angstrom,
															CLHEP::halfpi,
															CLHEP::halfpi,
															CLHEP::halfpi,
															227));
		Crystal->RegisterExtension(std::unique_ptr<G4ChannelingMaterialData>(new G4ChannelingMaterialData("channeling")));
		G4ChannelingMaterialData* crystalChannelingData = (G4ChannelingMaterialData*)Crystal->RetrieveExtension("channeling");
		crystalChannelingData->SetFilename("data/Si220pl");
		crystalChannelingData->SetBR(G4ThreeVector(0.,0.,0.)); // add bending radius here
		crystalLogic = new G4LogicalCrystalVolume(crystalSolid,Crystal,"crystal.logic");
		G4RotationMatrix* rot = new G4RotationMatrix;
		rot->rotateX(0.E-6 * CLHEP::rad); // add rotation angle of the crystal here
		new G4PVPlacement(rot,posTarg1,crystalLogic,"crystal.physic",logicWorld,false,0);
	}
	else{
		//-- amorphous Be TARGET
		/*
		 G4Box* targ = new G4Box("Target",cry_sizeX/2,cry_sizeY/2,cry_sizeZ/2);
		 logicTarg = new G4LogicalVolume(targ, berillio, "Target");
		 new G4PVPlacement(0,posTarg1,logicTarg,"Target",logicWorld,false,0,checkOverlaps);
		 */
		
		G4Tubs* targ = new G4Tubs("Target",0,target_R,target_Z/2.,startAngle,spanningAngle);
		logicTarg = new G4LogicalVolume(targ, berillio, "Target");
		new G4PVPlacement(0,posTarg1,logicTarg,"Target",logicWorld,false,0,checkOverlaps);
	}
	
	//-- Trk1-Si (subdet=10)
	G4Box* trk1 = new G4Box("Trk1", trk_sizeXa/2, trk_sizeYa/2, 0.3*trk_sizeZ1/2);
	G4LogicalVolume* logicTrk1 = new G4LogicalVolume(trk1, silicio, "Trk1");
	new G4PVPlacement(0,posTrk1,logicTrk1,"Trk1",logicWorld,false,0,checkOverlaps);
	
	//-- Beam Pipe between T1 and T2
	G4Tubs* pipe12 = new G4Tubs("Pipe12",PipeinnerRadius,PipeouterRadius,PipeH12/2.,startAngle,spanningAngle);
	G4LogicalVolume* logicPipe12 = new G4LogicalVolume(pipe12,vuoto,"Pipe12");
	new G4PVPlacement(0,posPipe12,logicPipe12,"Pipe12",logicWorld,false,0,checkOverlaps);
	
	//-- Trk2-Si (20)
	G4Box* trk2 = new G4Box("Trk2", trk_sizeXa/2, trk_sizeYa/2, 0.3*trk_sizeZ2/2);
	G4LogicalVolume* logicTrk2 = new G4LogicalVolume(trk2, silicio, "Trk2");
	new G4PVPlacement(0,posTrk2,logicTrk2,"Trk2",logicWorld,false,0,checkOverlaps);
	
//	Si30Box_sizeX DistZSi30Bar posTrk3HoleF Si30Vetronite_sizeX
	//-- Trk3-Si (30)
	//I build the Alu Box by subtracting several pieces from a whole box
	G4Box* Box30out = new G4Box("Box30out", Si30Box_sizeX/2, Si30Box_sizeY/2, Si30Box_sizeZ/2);
	G4Box* Box30in = new G4Box("Box30in", Si30Box_sizeX/2-Si30Box_AluThicknessX, Si30Box_sizeY/2-Si30Box_AluThicknessY, Si30Box_sizeZ/2-Si30Box_AluThicknessZ);
	G4VSolid* Box30a= new G4SubtractionSolid("Box30a", Box30out, Box30in);
	G4Box* Box30HoleF = new G4Box("Box30HoleF", trk_sizeXa/2, trk_sizeYa/2, Si30Box_AluThicknessZ);
	G4VSolid* Box30b= new G4SubtractionSolid("Box30b", Box30a, Box30HoleF, 0, posTrk3HoleF);
	G4Box* Box30HoleB = new G4Box("Box30HoleB", trk_sizeXa/2, trk_sizeYa/2, Si30Box_AluThicknessZ);
	G4VSolid* Box30= new G4SubtractionSolid("Box30", Box30b, Box30HoleB, 0, posTrk3HoleB);
	
	G4LogicalVolume* logicBox30 = new G4LogicalVolume(Box30, ferro, "Box30");
	new G4PVPlacement(0,posBox30,logicBox30,"Box30",logicWorld,false,0,checkOverlaps);

	G4Box* AluBar30 = new G4Box("AluBar30", Si30AluBar_sizeX/2, Si30AluBar_sizeY/2, Si30AluBar_sizeZ/2);
	G4LogicalVolume* logicAluBar30 = new G4LogicalVolume(AluBar30, ferro, "AluBar30");
	new G4PVPlacement(0,posAlu30Bar,logicAluBar30,"AluBar30",logicWorld,false,0,checkOverlaps);
	
		//I build the Vetroniet holder by subtracting several pieces from a whole box
	G4Box* Vetronite30ext = new G4Box("Vetronite30ext", Si30Vetronite_sizeX/2, Si30Vetronite_sizeY/2, Si30Vetronite_sizeZ/2);
	G4Box* Vetronite30Hole = new G4Box("Vetronite30Hole", trk_sizeXa/2, trk_sizeYa/2, Si30Vetronite_sizeZ/2+0.1);
	//subtracting the hole with a shift: Hole30Shift
	G4VSolid* Vetronite30= new G4SubtractionSolid("Vetronite30", Vetronite30ext, Vetronite30Hole, 0, -Hole30Shift);
	G4LogicalVolume* logicVetronite30 = new G4LogicalVolume(Vetronite30, FR4, "Vetronite30");
	new G4PVPlacement(0,posVetronite30,logicVetronite30,"Vetronite30",logicWorld,false,0,checkOverlaps);
	
	G4Box* trk3 = new G4Box("Trk3", trk_sizeXa/2, trk_sizeYa/2, 0.8*trk_sizeZ3/2);
	G4LogicalVolume* logicTrk3 = new G4LogicalVolume(trk3, silicio, "Trk3");
	new G4PVPlacement(0,posTrk3,logicTrk3,"Trk3",logicWorld,false,0,checkOverlaps);
	
	//-- Beam Pipe between T3 and T4
	G4Tubs* pipe34 = new G4Tubs("Pipe34",PipeinnerRadius,PipeouterRadius,PipeH34/2.,startAngle,spanningAngle);
	G4LogicalVolume* logicPipe34 = new G4LogicalVolume(pipe34,vuoto,"Pipe34");
	new G4PVPlacement(0,posPipe34,logicPipe34,"Pipe34",logicWorld,false,0,checkOverlaps);
	
	//-- Trk4-Si (40)
	G4Box* trk4 = new G4Box("Trk4", trk_sizeXb/2, trk_sizeYb/2, 0.8*trk_sizeZ4/2);
	G4LogicalVolume* logicTrk4 = new G4LogicalVolume(trk4, silicio, "Trk4");
	new G4PVPlacement(0,posTrk4,logicTrk4,"Trk4",logicWorld,false,0,checkOverlaps);
	
	//-- BENDING MAGNET (a cylinder)
	G4Tubs* bend = new G4Tubs("Bend",innerRadius,outerRadius,hBdipole,startAngle,spanningAngle);
	G4RotationMatrix *xRot = new G4RotationMatrix;
	xRot->rotateX(90.*deg);
	G4LogicalVolume* logicBend = new G4LogicalVolume(bend,aria,"Bend");
	new G4PVPlacement(xRot,posBend,logicBend,"Bend",logicWorld,false,0,checkOverlaps);
	
	//-- Trk5a-Si (51)
	G4Box* trk5a = new G4Box("Trk5a", trk_sizeXb/2, trk_sizeYb/2, trk_sizeZ5/2);
	G4LogicalVolume* logicTrk5a = new G4LogicalVolume(trk5a, vuoto, "Trk5a");
	new G4PVPlacement(0,posTrk5a,logicTrk5a,"Trk5a",logicWorld,false,0,checkOverlaps);
	
	//-- Trk5b-Si (50)
	G4Box* trk5b = new G4Box("Trk5b", trk_sizeXb/2, trk_sizeYb/2, trk_sizeZ5/2);
	G4LogicalVolume* logicTrk5b = new G4LogicalVolume(trk5b, vuoto, "Trk5b");
	new G4PVPlacement(0,posTrk5b,logicTrk5b,"Trk5b",logicWorld,false,0,checkOverlaps);
	
	//-- Trk6a-Si (56)
	G4Box* trk6a = new G4Box("Trk6a", trk_sizeXb/2, trk_sizeYb/2, trk_sizeZ6/2);
	G4LogicalVolume* logicTrk6a = new G4LogicalVolume(trk6a, vuoto, "Trk6a");
	new G4PVPlacement(0,posTrk6a,logicTrk6a,"Trk6a",logicWorld,false,0,checkOverlaps);
	
	//-- Trk6b-Si (55)
	G4Box* trk6b = new G4Box("Trk6b", trk_sizeXb/2, trk_sizeYb/2, trk_sizeZ6/2);
	G4LogicalVolume* logicTrk6b = new G4LogicalVolume(trk6b, vuoto, "Trk6b");
	new G4PVPlacement(0,posTrk6b,logicTrk6b,"Trk6b",logicWorld,false,0,checkOverlaps);
	
	//-- Scint A
	G4Box* scintA = new G4Box("ScintA", ScintA_sizeX/2, ScintA_sizeY/2, ScintA_sizeZ/2);
	G4LogicalVolume* logicScintA = new G4LogicalVolume(scintA, plastica, "ScintA");
	new G4PVPlacement(0,posScintA,logicScintA,"ScintA",logicWorld,false,0,checkOverlaps);
	
	//-- Scint B
	G4Box* scintB = new G4Box("ScintB", ScintB_sizeX/2, ScintB_sizeY/2, ScintB_sizeZ/2);
	G4LogicalVolume* logicScintB = new G4LogicalVolume(scintB, plastica, "ScintB");
	new G4PVPlacement(0,posScintB,logicScintB,"ScintB",logicWorld,false,0,checkOverlaps);
	
	//-- GCAL (PbW04)
	G4Box* gcal = new G4Box("Gcal",Gcal_sizeX/2, Gcal_sizeY/2, Gcal_sizeZ/2);
	G4LogicalVolume* logicGcal = new G4LogicalVolume(gcal, PbWO4, "Gcal");
	new G4PVPlacement(0,posGcal,logicGcal,"Gcal",logicWorld,false,0,checkOverlaps);
	
	//-- Iron Blocks between calorimeters
	G4Box* iblock = new G4Box("IronBlock",Iblock_sizeX/2, Iblock_sizeY/2, Iblock_sizeZ/2);
	G4LogicalVolume* logicIblock = new G4LogicalVolume(iblock, ferro, "IronBlock");
	new G4PVPlacement(0,posIblock,logicIblock,"IronBlock",logicWorld,false,0,checkOverlaps);
	
	//-- ECAL (Fe) - DEVA Dummy for scoring what enters from front
	G4Box* ecalDummy = new G4Box("EcalDummy",DEVAenv_sizeX/2, DEVAenv_sizeY/2, 1*cm/2.);
	G4LogicalVolume* logicEcalDummy = new G4LogicalVolume(ecalDummy, aria, "EcalDummy");
	//	new G4PVPlacement(G4Transform3D(*rotEcal,posEcal),logicEcal,"Ecal",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(rotateEcalDummy*translateEcalDummy,logicEcalDummy,"EcalDummy",logicWorld,false,0,checkOverlaps);
	
	//-- ECAL (Fe) - DEVA
	G4Box* ecal = new G4Box("Ecal",DEVAenv_sizeX/2, DEVAenv_sizeY/2, DEVAenv_sizeZ/2);
	G4LogicalVolume* logicEcal = new G4LogicalVolume(ecal, aria, "Ecal");
	//	new G4PVPlacement(G4Transform3D(*rotEcal,posEcal),logicEcal,"Ecal",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(rotateEcal*translateEcal,logicEcal,"Ecal",logicWorld,false,0,checkOverlaps);
	
	//############# DEVA COMPONENTS
	//DEVA active components
	G4Box* devaAct = new G4Box("DEVAact",DEVAact_sizeX/2, DEVAact_sizeY/2, DEVAact_sizeZ/2);
	G4LogicalVolume* logicDevaAct = new G4LogicalVolume(devaAct, plastica, "DEVAact");
	
	for (int ii=0; ii<12; ii++) {
		if (ii<9) posDevaAct.setZ(-(DEVAenv_sizeZ/2-DEVAact_sizeZ/2-DEVAact_sizeZ*ii-DEVAabs_sizeZ*ii));
		else posDevaAct.setZ(-(DEVAenv_sizeZ/2-DEVAact_sizeZ/2-DEVAact_sizeZ*ii-DEVAabs_sizeZ*8-DEVAabs_sizeZbis*(ii-8)));
		new G4PVPlacement(0,posDevaAct, logicDevaAct,"DEVAact",logicEcal,false,ii,checkOverlaps);
		//		new G4PVPlacement(0,posDevaAct, logicDevaAct,"DEVAact",logicEcal,false,0,checkOverlaps);
		
	}
	
	//DEVA absorber components
	
	for (int ii=0; ii<11; ii++) {
		
		if (ii<8) 	{
			posDevaAbs.setZ(-(DEVAenv_sizeZ/2-DEVAact_sizeZ-DEVAabs_sizeZ/2.-DEVAact_sizeZ*ii-DEVAabs_sizeZ*ii));
			G4Box* devaAbs = new G4Box("DEVAabs",DEVAabs_sizeX/2, DEVAabs_sizeY/2, DEVAabs_sizeZ/2);
			G4LogicalVolume* logicDevaAbs = new G4LogicalVolume(devaAbs, piombo, "DEVAabs");
			new G4PVPlacement(0,posDevaAbs, logicDevaAbs,"DEVAabs",logicEcal,false,ii,checkOverlaps);
			
		}
		else {
			posDevaAbs.setZ(-(DEVAenv_sizeZ/2-DEVAact_sizeZ-DEVAact_sizeZ*ii-DEVAabs_sizeZ*7-DEVAabs_sizeZbis*(ii-7)));
			G4Box* devaAbs = new G4Box("DEVAabs",DEVAabs_sizeX/2, DEVAabs_sizeY/2, DEVAabs_sizeZbis/2);
			G4LogicalVolume* logicDevaAbs = new G4LogicalVolume(devaAbs, piombo, "DEVAabs");
			new G4PVPlacement(0,posDevaAbs, logicDevaAbs,"DEVAabs",logicEcal,false,ii,checkOverlaps);
			
		}
		
	}
	
	//	new G4PVPlacement(G4Transform3D(*rotEcal,posEcal),logicEcal,"Ecal",logicWorld,false,0,checkOverlaps);
	//#############################
	
	//-- Iron Column
	G4Box* icol = new G4Box("IronColumn",Icol_sizeX/2, Icol_sizeY/2, Icol_sizeZ/2);
	G4LogicalVolume* logicIcol = new G4LogicalVolume(icol, ferro, "IronColumn");
	new G4PVPlacement(0,posIcol,logicIcol,"IronColumn",logicWorld,false,0,checkOverlaps);
	
	//-- Shield Wall (Fe)
	G4Box* shield = new G4Box("Shield",shield_sizeX/2, shield_sizeY/2, shield_sizeZ/2);
	G4LogicalVolume* logicShield = new G4LogicalVolume(shield, ferro, "Shield");
	new G4PVPlacement(0,posShield,logicShield,"Shield",logicWorld,false,0,checkOverlaps);
	
	//-- Muon Chamber - FULL
	/*
	 G4Box* solidChamber = new G4Box("Chamber",Chamber_sizeX/2,Chamber_sizeY/2,Chamber_sizeZ/2);
	 G4LogicalVolume* logicChamber = new G4LogicalVolume(solidChamber, alluminium,"Chamber");
	 new G4PVPlacement(0,posChamber,logicChamber,"Chamber",logicWorld,false,0,checkOverlaps);
	 */
	
	//-- Muon Chamber Layer
	G4Box* solidChamber = new G4Box("Chamber",Chamber_sizeX/2,Chamber_sizeY/2,Chamber_sizeZ/2);
	G4LogicalVolume* logicChamber = new G4LogicalVolume(solidChamber, vuoto /*alluminium*/,"Chamber");
	double ztemp=posChamber.z();
	
	for (int ii=0; ii<12; ii++) {
		posChamber.setZ(ztemp+ChamberLayerZ[ii]+10.75*cm+Chamber_sizeZ/2.);
		new G4PVPlacement(0,posChamber,logicChamber,"Chamber",logicWorld,false,0,checkOverlaps);
	}
	
	//-- LeadGlass
	G4Box* solidLeadGlass = new G4Box("LeadGlass",LeadGlass_sizeX/2,LeadGlass_sizeY/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicLeadGlass = new G4LogicalVolume(solidLeadGlass, PbGl,"LeadGlass");
	new G4PVPlacement(0,posLeadGlass,logicLeadGlass,"LeadGlass",logicWorld,false,0,checkOverlaps);
	
	//-- Cerenkov counter
	G4Box* solidCerenkov = new G4Box("Cerenkov",Cerenkov_sizeX/2,Cerenkov_sizeY/2,Cerenkov_sizeZ/2);
	G4LogicalVolume* logicCerenkov = new G4LogicalVolume(solidCerenkov,  aria,"Cerenkov");
	new G4PVPlacement(0,posCerenkov,logicCerenkov,"Cerenkov",logicWorld,false,0,checkOverlaps);
	
	//-- Cerenkov counter elements
	G4Box* solidCerenkovAlu = new G4Box("CerenkovAlu",Cerenkov_sizeX/2,Cerenkov_sizeY/2,Cerenkov_AluZ/2);
	G4LogicalVolume* logicCerenkovAlu = new G4LogicalVolume(solidCerenkovAlu,  alluminium,"CerenkovAlu");
	new G4PVPlacement(0,posCerenkovAlu1,logicCerenkovAlu,"CerenkovAlu1",logicCerenkov,false,1,checkOverlaps);
	new G4PVPlacement(0,posCerenkovAlu2,logicCerenkovAlu,"CerenkovAlu2",logicCerenkov,false,2,checkOverlaps);
	
	G4Box* solidCerenkovSiO = new G4Box("CerenkovSiO",Cerenkov_SiOX/2,Cerenkov_SiOY/2,Cerenkov_SiOZ/2);
	G4LogicalVolume* logicCerenkovSiO = new G4LogicalVolume(solidCerenkovSiO,  SiO2,"CerenkovSiO");
	new G4PVPlacement(0,posCerenkovSiO1A,logicCerenkovSiO,"CerenkovSiO1A",logicCerenkov,false,0,checkOverlaps);
	new G4PVPlacement(0,posCerenkovSiO1B,logicCerenkovSiO,"CerenkovSiO1B",logicCerenkov,false,1,checkOverlaps);
	new G4PVPlacement(0,posCerenkovSiO1C,logicCerenkovSiO,"CerenkovSiO1C",logicCerenkov,false,2,checkOverlaps);
	
	new G4PVPlacement(0,posCerenkovSiO2A,logicCerenkovSiO,"CerenkovSiO2A",logicCerenkov,false,3,checkOverlaps);
	new G4PVPlacement(0,posCerenkovSiO2B,logicCerenkovSiO,"CerenkovSiO2B",logicCerenkov,false,4,checkOverlaps);
	new G4PVPlacement(0,posCerenkovSiO2C,logicCerenkovSiO,"CerenkovSiO2C",logicCerenkov,false,5,checkOverlaps);
	

	
	G4Box* solidCerenkovFe = new G4Box("CerenkovFe",Cerenkov_FeX/2,Cerenkov_FeY/2,Cerenkov_FeZ/2);
	G4LogicalVolume* logicCerenkovFe = new G4LogicalVolume(solidCerenkovFe,  ferro,"CerenkovFe");
	new G4PVPlacement(0,posCerenkovFe,logicCerenkovFe,"CerenkovFe",logicCerenkov,false,0,checkOverlaps);
	
	fScoringVolume_Trk1  = logicTrk1;
	fScoringVolume_Trk2  = logicTrk2;
	if( channeling==true ){
		fScoringVolume_T1 = crystalLogic;
	}else{
		fScoringVolume_T1 = logicTarg;
	}
	fScoringVolume_Trk3  = logicTrk3;
	fScoringVolume_Trk4  = logicTrk4;
	fScoringVolume_Trk5a  = logicTrk5a;
	fScoringVolume_Trk5b  = logicTrk5b;
	fScoringVolume_Trk6a  = logicTrk6a;
	fScoringVolume_Trk6b  = logicTrk6b;
	fScoringVolume_Chamber  = logicChamber;
	fScoringVolume_ScintA  = logicScintA;
	fScoringVolume_ScintB = logicScintB;
	fScoringVolume_Ecal= logicEcal;
	fScoringVolume_DEVA= logicDevaAct;
	fScoringVolume_Gcal=logicGcal;
	fScoringVolume_Cerenkov=logicCerenkovSiO;
	fScoringVolume_PbGlass=logicLeadGlass;

	G4cout<<" ... Detector construction DONE !"<<G4endl;
	return physWorld;
}


void B1DetectorConstruction::ConstructSDandField(){
	if( channeling==true ){
		G4LogicalVolume* crystalLogic = G4LogicalVolumeStore::GetInstance()->GetVolume("crystal.logic");
		G4ChannelingOptrMultiParticleChangeCrossSection* testMany = new G4ChannelingOptrMultiParticleChangeCrossSection();
		testMany->AttachTo(crystalLogic);
		G4cout << " Attaching biasing operator " << testMany->GetName()
		<< " to logical volume " << crystalLogic->GetName()
		<< G4endl;
	}
	
	
	// =============================
	//       MAGNETIC FIELD
	// =============================
	// Conventional sign: non-flipped field sends positrons towards the "clean channel" (just chamber, no calos, "down" direction)
	
	//	G4double zOffset=posBend.z();
	G4VPhysicalVolume* physicalBend = G4PhysicalVolumeStore::GetInstance()->GetVolume("Bend");
	G4double zOffset=physicalBend->GetTranslation().z();
#if 1
	//	/*
	if(fMagMapFlag) {
		G4cout<<"lemmaDEBUG zoffset= "<<zOffset<<G4endl;
		//		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE",  -zOffset+100*cm);
		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE",  zOffset+00*cm, fFlipFieldFlag);
		fField.Put(PurgMagField);
		
		///*
		G4FieldManager* pFieldMgr =
		G4TransportationManager::GetTransportationManager()->GetFieldManager();
		
		pFieldMgr->SetDetectorField(fField.Get());
		pFieldMgr->CreateChordFinder(fField.Get());
		//*/
	} else {
		G4double fieldValue;
		if (fFlipFieldFlag) fieldValue= -0.7*1.8*tesla;  //=-1,26
		else fieldValue=0.7*1.8*tesla;
		
		//		G4double fieldValue = -1.1557*tesla; //calculated rescaling the map for the current bias
		G4UniformMagField* myField = new G4UniformMagField(G4ThreeVector(0., fieldValue, 0.));
		G4LogicalVolume* logicBend = G4LogicalVolumeStore::GetInstance()->GetVolume("Bend");
		G4FieldManager* localfieldMgr = new G4FieldManager(myField);
		logicBend->SetFieldManager(localfieldMgr,true);
		localfieldMgr->CreateChordFinder(myField);
	}
	//	*/
#endif
	
	/*
	 //G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("PurgMag3D.TABLE", zOffset);
	 G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE", zOffset);
	 
	 fField.Put(PurgMagField);
	 
	 //This is thread-local
	 G4FieldManager* pFieldMgr =
	 G4TransportationManager::GetTransportationManager()->GetFieldManager();
	 
	 G4cout<< "DeltaStep "<<pFieldMgr->GetDeltaOneStep()/mm <<"mm" <<endl;
	 //G4ChordFinder *pChordFinder = new G4ChordFinder(PurgMagField);
	 
	 pFieldMgr->SetDetectorField(fField.Get());
	 pFieldMgr->CreateChordFinder(fField.Get());
	 
	 */
}
