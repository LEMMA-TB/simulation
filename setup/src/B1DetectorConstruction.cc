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



B1DetectorConstruction::B1DetectorConstruction(G4bool MuonBeamFlag, G4bool ElectronBeamFlag)
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
fMuonBeamFlag(MuonBeamFlag),
fElectronBeamFlag(ElectronBeamFlag)
{ }


B1DetectorConstruction::~B1DetectorConstruction()
{}


G4VPhysicalVolume* B1DetectorConstruction::Construct(){
	
	// =============================
	// Detector parameters and size
	// =============================
	
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
	
	
	//--> Be amorphous crystal:
	G4double cry_sizeX = 5.*cm;
	G4double cry_sizeY = 5.*cm;
	G4double cry_sizeZ = 30.*mm;
	
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
	G4double Iblock_sizeX = 10*cm;
	G4double Iblock_sizeY = 10*cm;
	G4double Iblock_sizeZ = 400*mm;
	
	// Iron column:
	G4double Icol_sizeX = 30*cm;
	G4double Icol_sizeY = 100*cm;
	G4double Icol_sizeZ = 30*cm;
	
	// E-cal:
	G4double Ecal_sizeX = 22*cm;
	G4double Ecal_sizeY = 30*cm;
	G4double Ecal_sizeZ = 400.*mm; // ~23Xo
	
	// shield wall:
	G4double shield_sizeX = 1.62*m;
	G4double shield_sizeY = 2.6*m;
	G4double shield_sizeZ = 0.4*m;
	
	//--> detectors (D-ghost): // ghost-detectors
	G4double Chamber_sizeX = 2.55*m;
	G4double Chamber_sizeY = 2.55*m;
//	G4double Chamber_sizeZ = 29*cm; //entire chamber
	G4double Chamber_sizeZ = 1.2*cm; //chamber layer is 1.2, but use smaller value since we just use z position

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
	
	// Cerenkov counter :          // TO BE CHECKED
	G4double Cerenkov_sizeX = 20*cm;
	G4double Cerenkov_sizeY = 20*cm;
	G4double Cerenkov_sizeZ = 50*cm;
	
	// ============
	//   positions
	// ============
	G4double xTrk5=5.1*cm+trk_sizeXb/2.;
	G4double zTrk5=1563*cm;
	G4double zBendMagn=zTrk5-260*cm;  //1563-260=1303
	G4double xTrk6=14.85*cm+trk_sizeXb/2.;
	G4double zTrk6=2137.4*cm;
	//	G4double xScintA=5.1*cm+ScintA_sizeX/2.;
	G4double zCalo=2941*cm;
	G4double CaloOffset=5*cm;
	G4double DistXGcalIron=5*cm;
	G4double DistXIronEcal=2*cm;
	G4double DistXEcalColumn=10*cm;
	G4double DistZGcalIron=5*cm;
	G4double ChamberOffsetX=3*cm;
	G4double X3Corr=1*cm;
	G4double Y3Corr=-0.5*cm;
	G4double ChamberLayerZ[12]={-10.75*cm, -9.45*cm, -8.15*cm, -6.85*cm,  7.45*cm, 8.75*cm, 10.05*cm,11.35*cm, 12.85*cm, 14.15*cm, 15.45*cm, 16.75*cm}; //vero da Bertolin ma da capire il significato
//	G4double ChamberLayerZ[12]={0*cm, 1.5*cm, 3*cm, 4.5*cm, 6*cm, 7.5*cm, 9*cm, 10.5*cm, 12*cm, 13.5*cm, 15*cm, 16.5*cm};

	
	G4ThreeVector posTrk1  = G4ThreeVector(0.,0.,0*mm); // Si-Trk1  Subdet 10
	G4ThreeVector posPipe12  = G4ThreeVector(0.,0.,277.4*cm); // Pipe between T1 and T2
	G4ThreeVector posTrk2  = G4ThreeVector(0.,0.,516.8*cm); // Si-Trk2  Subdet 20
	G4ThreeVector posTarg1 = G4ThreeVector(0.,0.,545.8*cm); // TARGET
	G4ThreeVector posTrk3  = G4ThreeVector(X3Corr,Y3Corr,577.8*cm); // Si-Trk3  Subdet 30
	G4ThreeVector posPipe34  = G4ThreeVector(0.,0.,903.95*cm); // Pipe between T3 and T4
	G4ThreeVector posTrk4  = G4ThreeVector(0.,0.,1152.1*cm); // Si-Trk4  Subdet 40
	G4ThreeVector posBend  = G4ThreeVector(0.,0.,zBendMagn); // Dipole magnet center era 1203
	G4ThreeVector posTrk5a  = G4ThreeVector(xTrk5,0.,zTrk5); // Si-Trk5a
	G4ThreeVector posTrk5b  = G4ThreeVector(-xTrk5,0.,zTrk5); // Si-Trk5b
	G4ThreeVector posTrk6a  = G4ThreeVector(xTrk6,0.,zTrk6); // Si-Trk6a
	G4ThreeVector posTrk6b  = G4ThreeVector(-xTrk6,0.,zTrk6); // Si-Trk6b
	G4ThreeVector posScintA  = G4ThreeVector(xTrk6,0.,zTrk6+ScintA_sizeZ/2.+1*cm); // ScintA behind T6a
	G4ThreeVector posScintB  = G4ThreeVector(-xTrk6,0.,zTrk6+ScintB_sizeZ/2.+1*cm); // ScintB behind T6b
	G4ThreeVector posGcal  = G4ThreeVector(CaloOffset,0.,zCalo+Gcal_sizeZ/2.); // GCAL center
	G4ThreeVector posIblock  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX/2.+DistXGcalIron,0.,zCalo+Iblock_sizeZ/2.+DistZGcalIron); // GCAL center
	G4ThreeVector posEcal  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX+DistXIronEcal+DistXGcalIron+Ecal_sizeX/2.,0.,zCalo+Ecal_sizeZ/2.); // ECAL center
	G4ThreeVector posIcol  = G4ThreeVector(CaloOffset+Gcal_sizeX/2.+Iblock_sizeX+DistXIronEcal+DistXGcalIron+Ecal_sizeX+Icol_sizeX/2.+DistXEcalColumn,0.,zCalo+Icol_sizeZ/2.); // ECAL center
	
	
	//	 G4Transform3D transform1 = G4Transform3D(rotEcal,posEcal);
	G4ThreeVector posShield= G4ThreeVector(92.7/2.*cm,0.*cm,3082.4*cm); // Shield center
	G4ThreeVector posChamber  = G4ThreeVector(ChamberOffsetX,0.,3132.4*cm); // D-ghost Subdet 70
	G4ThreeVector posLeadGlass  = G4ThreeVector(-40*cm-LeadGlass_sizeX/2.,0.,3132.4*cm+29*cm+10*cm);
	G4ThreeVector posCerenkov  = G4ThreeVector(-40*cm-LeadGlass_sizeX/2.,0.,3132.4*cm+29*cm+10*cm + 10*cm + LeadGlass_sizeZ/2. + Cerenkov_sizeZ/2.);  //centered behing LeadGlass
	
	
	G4double EcalAngle=7.94*CLHEP::deg;
	//G4RotationMatrix* rotEcal = new G4RotationMatrix;
	G4RotationMatrix rotEcal;
	rotEcal.rotateY(EcalAngle); // add rotation angle of the crystal here
	//	G4Transform3D translateEcal = HepGeom::Translate3D(7*cm*sin(EcalAngle), 7*cm*cos(EcalAngle), 0);
	G4Transform3D translateEcal = HepGeom::Translate3D(7*cm*sin(EcalAngle), 0, -7*cm*cos(EcalAngle));
	G4Transform3D rotateEcal(rotEcal,posEcal);
	
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
	
	if (fMuonBeamFlag || fElectronBeamFlag) berillio=nist->FindOrBuildMaterial("G4_Galactic");;  //if MuonBeam case I want no target
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
	
	
	// lead glass
	G4Material* PbGl = new G4Material("Lead Glass", d= 3.85*g/cm3,
									  natoms=2);
	PbGl->AddElement(elPb, 0.5316);
	PbGl->AddMaterial(SiO2, 0.4684);
	
	
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
		G4Box* targ = new G4Box("Target",cry_sizeX/2,cry_sizeY/2,cry_sizeZ/2);
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
	
	//-- Trk3-Si (30)
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
	
	//-- Trk5a-Si (40)
	G4Box* trk5a = new G4Box("Trk5a", trk_sizeXb/2, trk_sizeYb/2, trk_sizeZ5/2);
	G4LogicalVolume* logicTrk5a = new G4LogicalVolume(trk5a, vuoto, "Trk5a");
	new G4PVPlacement(0,posTrk5a,logicTrk5a,"Trk5a",logicWorld,false,0,checkOverlaps);
	
	//-- Trk5b-Si (40)
	G4Box* trk5b = new G4Box("Trk5b", trk_sizeXb/2, trk_sizeYb/2, trk_sizeZ5/2);
	G4LogicalVolume* logicTrk5b = new G4LogicalVolume(trk5b, vuoto, "Trk5b");
	new G4PVPlacement(0,posTrk5b,logicTrk5b,"Trk5b",logicWorld,false,0,checkOverlaps);
	
	//-- Trk6a-Si (40)
	G4Box* trk6a = new G4Box("Trk6a", trk_sizeXb/2, trk_sizeYb/2, trk_sizeZ6/2);
	G4LogicalVolume* logicTrk6a = new G4LogicalVolume(trk6a, vuoto, "Trk6a");
	new G4PVPlacement(0,posTrk6a,logicTrk6a,"Trk6a",logicWorld,false,0,checkOverlaps);
	
	//-- Trk6b-Si (40)
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
	
	//-- ECAL (Fe)
	G4Box* ecal = new G4Box("Ecal",Ecal_sizeX/2, Ecal_sizeY/2, Ecal_sizeZ/2);
	G4LogicalVolume* logicEcal = new G4LogicalVolume(ecal, ferro, "Ecal");
	//	new G4PVPlacement(G4Transform3D(*rotEcal,posEcal),logicEcal,"Ecal",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(rotateEcal*translateEcal,logicEcal,"Ecal",logicWorld,false,0,checkOverlaps);
	
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
	G4LogicalVolume* logicChamber = new G4LogicalVolume(solidChamber, alluminium,"Chamber");
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
	G4LogicalVolume* logicCerenkov = new G4LogicalVolume(solidCerenkov, PbGl,"Cerenkov");
	new G4PVPlacement(0,posCerenkov,logicCerenkov,"Cerenkov",logicWorld,false,0,checkOverlaps);
	
	
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
	fScoringVolume_Gcal=logicGcal;
	
	
	
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
	
	//	G4double zOffset=posBend.z();
	G4VPhysicalVolume* physicalBend = G4PhysicalVolumeStore::GetInstance()->GetVolume("Bend");
	G4double zOffset=physicalBend->GetTranslation().z();
	G4bool MagMapFlag=true;
#if 1
	//	/*
	if(MagMapFlag) {
		//G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("PurgMag3D.TABLE", 0);
//		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE", 45*cm, 30*cm, -(zOffset-70*cm));
		G4cout<<"lemmaDEBUG zoffset= "<<zOffset<<G4endl;
//		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE",  -zOffset+100*cm);
		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE",  zOffset+00*cm);
	fField.Put(PurgMagField);
		
//		G4FieldManager* localfieldMgr = new G4FieldManager(PurgMagField);
	///*
		G4FieldManager* pFieldMgr =
	 G4TransportationManager::GetTransportationManager()->GetFieldManager();
		
		pFieldMgr->SetDetectorField(fField.Get());
		pFieldMgr->CreateChordFinder(fField.Get());
	//*/
		//		logicBend->SetFieldManager(localfieldMgr,true);
		
	} else {
		G4double fieldValue = -0.7*1.8*tesla;  //=-1,26
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
