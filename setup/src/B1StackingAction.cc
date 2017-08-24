#include "B1StackingAction.hh"
#include "HistoManager.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"

B1StackingAction::B1StackingAction()
:G4UserStackingAction()
{ }

B1StackingAction::~B1StackingAction()
{ }

G4ClassificationOfNewTrack B1StackingAction::ClassifyNewTrack(const G4Track* atrack)
{  
  if (atrack->GetParentID() == 0) return fUrgent;
  G4String process = atrack->GetCreatorProcess()->GetProcessName();    
  G4int Idp = atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
  //  G4double charge = atrack->GetDefinition()->GetPDGCharge();
  //  G4cout<<process<<", Energy = "<<energy<<G4endl;
  if (process=="annihil" && Idp==22) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4double energy = atrack->GetKineticEnergy();
//    analysisManager->FillH1(0,energy);
  }
  return fUrgent;
}

