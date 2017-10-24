#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Cache.hh"
#include "G4MagneticField.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class PurgMagTabulatedField3D;

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	B1DetectorConstruction(G4bool MuonBeamFlag,G4bool ElectronBeamFlag, G4bool TargetFlag, G4bool FlipFieldFlag, G4bool MagMapFlag);
	virtual ~B1DetectorConstruction();
	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();
	
	G4LogicalVolume* GetScoringVolume_Trk1() const { return fScoringVolume_Trk1; }
	G4LogicalVolume* GetScoringVolume_Trk2() const { return fScoringVolume_Trk2; }
	G4LogicalVolume* GetScoringVolume_T1()   const { return fScoringVolume_T1; }
	G4LogicalVolume* GetScoringVolume_Trk3() const { return fScoringVolume_Trk3; }
	G4LogicalVolume* GetScoringVolume_Trk4() const { return fScoringVolume_Trk4; }
	G4LogicalVolume* GetScoringVolume_Trk5a() const { return fScoringVolume_Trk5a; }
	G4LogicalVolume* GetScoringVolume_Trk5b() const { return fScoringVolume_Trk5b; }
	G4LogicalVolume* GetScoringVolume_Trk6a() const { return fScoringVolume_Trk6a; }
	G4LogicalVolume* GetScoringVolume_Trk6b() const { return fScoringVolume_Trk6b; }
	G4LogicalVolume* GetScoringVolume_Chamber()   const { return fScoringVolume_Chamber; }
	G4LogicalVolume* GetScoringVolume_ScintA()   const { return fScoringVolume_ScintA; }
	G4LogicalVolume* GetScoringVolume_ScintB()   const { return fScoringVolume_ScintB; }
	G4LogicalVolume* GetScoringVolume_Ecal()   const { return fScoringVolume_Ecal; }
	G4LogicalVolume* GetScoringVolume_Gcal()   const { return fScoringVolume_Gcal; }
	
protected:
	G4LogicalVolume*  fScoringVolume_Trk1;
	G4LogicalVolume*  fScoringVolume_Trk2;
	G4LogicalVolume*  fScoringVolume_T1;
	G4LogicalVolume*  fScoringVolume_Trk3;
	G4LogicalVolume*  fScoringVolume_Trk4;
	G4LogicalVolume*  fScoringVolume_Trk5a;
	G4LogicalVolume*  fScoringVolume_Trk5b;
	G4LogicalVolume*  fScoringVolume_Trk6a;
	G4LogicalVolume*  fScoringVolume_Trk6b;
	G4LogicalVolume*  fScoringVolume_Chamber;
	G4LogicalVolume*  fScoringVolume_ScintA;
	G4LogicalVolume*  fScoringVolume_ScintB;
	G4LogicalVolume*  fScoringVolume_Ecal;
	G4LogicalVolume*  fScoringVolume_Gcal;
private:
	G4bool channeling;
	G4String ctype;
	G4bool fMuonBeamFlag;
	G4bool fElectronBeamFlag;
	G4bool fTargetFlag;
	G4bool fFlipFieldFlag;
	G4bool fMagMapFlag;

public:
	void SetChanneling(bool aBool, G4String aString) {
		channeling=aBool;
		ctype=aString;};
	G4bool GetChanneling() {return channeling;};
	G4Cache<G4MagneticField*> fField;  //pointer to the thread-local fields
	
};

#endif
