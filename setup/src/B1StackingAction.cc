#include "B1StackingAction.hh"
#include "HistoManager.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "G4SystemOfUnits.hh"

B1StackingAction::B1StackingAction(B1EventAction* eventAction, B1RunAction * runAction)
:G4UserStackingAction(),
feventAction(eventAction),
frunAction(runAction)
{ }

B1StackingAction::~B1StackingAction()
{ }

G4ClassificationOfNewTrack B1StackingAction::ClassifyNewTrack(const G4Track* atrack)
{  
	if (atrack->GetParentID() == 0) { //modified by collamaf on 2017.12.29 - If is a new Primary particle - used to save info on primaries even if red by external file!
		
		/*
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"DEBUG STACKING ACTION"<<G4endl;
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"Particella= "<<atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()
		<<", ene= "<<atrack->GetKineticEnergy()/GeV
		<<G4endl;
		*/
		
//		(frunAction->GetBeamX()).push_back(subdet);
		frunAction->GetBeamX().push_back(atrack->GetPosition().x());
		frunAction->GetBeamY().push_back(atrack->GetPosition().y());
		frunAction->GetBeamZ().push_back(atrack->GetPosition().z());
		frunAction->GetBeamCX().push_back(atrack->GetMomentumDirection().x());
		frunAction->GetBeamCY().push_back(atrack->GetMomentumDirection().y());
		frunAction->GetBeamCZ().push_back(atrack->GetMomentumDirection().z());
		frunAction->GetBeamEne().push_back(atrack->GetKineticEnergy()/GeV);
		frunAction->GetBeamPart().push_back(atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
		/*
		feventAction->SetBeamX(atrack->GetPosition().x());
		feventAction->SetBeamY(atrack->GetPosition().y());
		feventAction->SetBeamZ(atrack->GetPosition().z());
		feventAction->SetBeamCX(atrack->GetMomentumDirection().x());
		feventAction->SetBeamCY(atrack->GetMomentumDirection().y());
		feventAction->SetBeamCZ(atrack->GetMomentumDirection().z());
		feventAction->SetBeamEne(atrack->GetKineticEnergy()/GeV);
		feventAction->SetBeamPart(atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
		*/
	return fUrgent;
	}
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

