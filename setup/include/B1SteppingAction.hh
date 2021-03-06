#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <vector>
#include "G4SystemOfUnits.hh"

class B1EventAction;
class B1RunAction;
class G4LogicalVolume;

/// Stepping action class

class B1SteppingAction : public G4UserSteppingAction
{
public:
	B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4double EThr=-1*GeV);
	virtual ~B1SteppingAction();
	// method from the base class
	virtual void UserSteppingAction(const G4Step*);
	
private:
	B1EventAction* fEventAction;
	B1RunAction* runStepAction;

	G4LogicalVolume* fScoringVolume_Trk1;
	G4LogicalVolume* fScoringVolume_Trk2;
	G4LogicalVolume* fScoringVolume_T1;
	G4LogicalVolume* fScoringVolume_Trk3;
	G4LogicalVolume* fScoringVolume_Trk4;
	G4LogicalVolume* fScoringVolume_Trk5a;
	G4LogicalVolume* fScoringVolume_Trk5b;
	G4LogicalVolume* fScoringVolume_Trk6a;
	G4LogicalVolume* fScoringVolume_Trk6b;
	G4LogicalVolume* fScoringVolume_Chamber;
	G4LogicalVolume* fScoringVolume_ScintA;
	G4LogicalVolume* fScoringVolume_ScintB;
	G4LogicalVolume* fScoringVolume_Ecal;
	G4LogicalVolume* fScoringVolume_DEVA;
	G4LogicalVolume* fScoringVolume_Gcal;
	G4LogicalVolume* fScoringVolume_PbGlass;
	G4LogicalVolume* fScoringVolume_Cerenkov;

	G4bool fStoreCaloEnDepFlag;
	
	
	G4double fEThr;
	G4bool fCutFlag=false;

	
};

#endif
