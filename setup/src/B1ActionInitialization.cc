#include "B1ActionInitialization.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"
#include "B1StackingAction.hh"

B1ActionInitialization::B1ActionInitialization(G4double BeamEnergy, G4bool MuonBeamFlag, G4bool ElectronBeamFlag, G4bool SimpleFlag)
: G4VUserActionInitialization(), fBeamEnergy(BeamEnergy), fMuonBeamFlag(MuonBeamFlag), fElectronBeamFlag(ElectronBeamFlag), fSimpleFlag(SimpleFlag)
{

}


B1ActionInitialization::~B1ActionInitialization()
{}


void B1ActionInitialization::BuildForMaster() const
{
	SetUserAction(new B1RunAction);
}

void B1ActionInitialization::Build() const
{
//	SetUserAction(new B1RunAction);
	B1RunAction* runAction = new B1RunAction;
	SetUserAction(runAction);
	
	B1EventAction* eventAction = new B1EventAction(runAction);
	SetUserAction(new B1PrimaryGeneratorAction(eventAction, fBeamEnergy, fMuonBeamFlag, fElectronBeamFlag, fSimpleFlag));
	SetUserAction(eventAction);
	SetUserAction(new B1SteppingAction(eventAction, runAction));
	SetUserAction(new B1StackingAction);
}

