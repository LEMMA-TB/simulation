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
//	std::remove_const<atrack>::type  ;
	
#if 0
//Try to kill muons born outside the target, useful in case of high bias of cross section. Works, but reamains to be understood the impact on physics...
	if (fabs(atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding())==13
		&& fabs(atrack->GetPosition().z()-545.8*cm)>=3*cm
		) {
		G4cout <<"Uccido Muone nato fuori dal bersaglio  "<<fabs((atrack->GetPosition().z()-545.8*cm))/cm<<G4endl;
		return fKill;
	}
#endif
	

	
	// atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()
	if (atrack->GetParentID() == 0 && atrack->GetCurrentStepNumber()==0) { //modified by collamaf on 2017.12.29 - If is a new Primary particle - used to save info on primaries even if red by external file!
		// on 2018.02.12 added StepNumberCheck to avoid counting here also new particles created thereafter (eg optical photons)
		
//		G4cout<<"DEBUG!!! Track id= "<<atrack->GetTrackID()<<", Creator Process= "<<atrack->GetCreatorProcess()<<", StepNumber= "<<atrack->GetCurrentStepNumber()<<", PDG code= "<<atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()<<G4endl;
		/*
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"DEBUG STACKING ACTION"<<G4endl;
//		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"Particella= "<<atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"Posizione X era= "<<atrack->GetPosition().x()/mm;
		//step->GetTrack()->GetVertexPosition()
//		atrack->GetPosition().setX(13/mm);
//		atrack->SetPosition(0,0,13*mm);
//		atrack->SetVertexPosition(G4ThreeVector(0,0,0));
		G4cout<<", la imposto a 13 = "<<atrack->GetPosition().x()/mm
		<<G4endl;
		*/
		
		frunAction->GetBeamX().push_back(atrack->GetPosition().x()/mm);
		frunAction->GetBeamY().push_back(atrack->GetPosition().y()/mm);
		frunAction->GetBeamZ().push_back(atrack->GetPosition().z()/mm);
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
#if 0
	G4String process = atrack->GetCreatorProcess()->GetProcessName();
  G4int Idp = atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
  //  G4double charge = atrack->GetDefinition()->GetPDGCharge();
  //  G4cout<<process<<", Energy = "<<energy<<G4endl;

	
	if (process=="annihil" && Idp==22) {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4double energy = atrack->GetKineticEnergy();
//    analysisManager->FillH1(0,energy);
  }
#endif
  return fUrgent;
}

