#include "B1EventAction.hh"
#include "B1Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "HistoManager.hh"
#include "B1SteppingAction.hh"
#include "B5Analysis.hh"
#include "B1RunAction.hh"

B1EventAction::B1EventAction(B1RunAction* runAction)
  : G4UserEventAction(),
fRunAction(runAction),
fNHits(0)
{} 

B1EventAction::~B1EventAction(){}


void B1EventAction::BeginOfEventAction(const G4Event* evt){    
  G4int fPrintModulo = 1;
  evtNb = evt->GetEventID();
  if (evtNb%fPrintModulo == 0) G4cout <<"\n---> Begin of Event:"<<evtNb<<G4endl; 
  // G4cout<<"\n---> Begin of Event +++++++++++++++ === >>>>  :"<<evtNb<<G4endl;
	
	//Initialize Primaries Info to 0

	
	(fRunAction->GetSubdet()).clear();
	(fRunAction->GetIdp()).clear();
	(fRunAction->GetIpar()).clear();
	(fRunAction->GetItrack()).clear();
	(fRunAction->GetTime()).clear();
	(fRunAction->GetVectorX()).clear();
	(fRunAction->GetVectorY()).clear();
	(fRunAction->GetVectorZ()).clear();
	(fRunAction->GetVectorP()).clear();
	(fRunAction->GetVectorPX()).clear();
	(fRunAction->GetVectorPY()).clear();
	(fRunAction->GetVectorPZ()).clear();
	(fRunAction->GetVertexX()).clear();
	(fRunAction->GetVertexY()).clear();
	(fRunAction->GetVertexZ()).clear();
	(fRunAction->GetKinev()).clear();
	(fRunAction->GetVectorPXvdir()).clear();
	(fRunAction->GetVectorPYvdir()).clear();
	(fRunAction->GetVectorPZvdir()).clear();
	(fRunAction->GetProcess()).clear();
	(fRunAction->GetIev()).clear();
	(fRunAction->GetStep()).clear();
	(fRunAction->GetInextStep()).clear();
	(fRunAction->GetCopyNb()).clear();
	
	
	fDEVAEneTot1=0;
	fDEVAEneTot2=0;
	fDEVAEneTot3=0;
	fDEVAEneTot4=0;
	fDEVAEneTot5=0;
	fDEVAEneTot6=0;
	fDEVAEneTot=0;
	
	fDEVAEneFot1=0;
	fDEVAEneFot2=0;
	fDEVAEneFot3=0;
	fDEVAEneFot4=0;
	fDEVAEneFot5=0;
	fDEVAEneFot6=0;
	fDEVAEneFot=0;
	
	fDEVAEnePos1=0;
	fDEVAEnePos2=0;
	fDEVAEnePos3=0;
	fDEVAEnePos4=0;
	fDEVAEnePos5=0;
	fDEVAEnePos6=0;
	fDEVAEnePos=0;
	
	fDEVAEneEle1=0;
	fDEVAEneEle2=0;
	fDEVAEneEle3=0;
	fDEVAEneEle4=0;
	fDEVAEneEle5=0;
	fDEVAEneEle6=0;
	fDEVAEneEle=0;

}

void B1EventAction::EndOfEventAction(const G4Event*){
	
	auto analysisManager = G4AnalysisManager::Instance();

	analysisManager->FillNtupleDColumn(0,fBeamX);
	analysisManager->FillNtupleDColumn(1,fBeamY);
	analysisManager->FillNtupleDColumn(2,fBeamZ);
	analysisManager->FillNtupleDColumn(3,fBeamCX);
	analysisManager->FillNtupleDColumn(4,fBeamCY);
	analysisManager->FillNtupleDColumn(5,fBeamCZ);
	analysisManager->FillNtupleDColumn(6,fBeamEne);
	analysisManager->FillNtupleDColumn(7,fBeamPart);
	analysisManager->FillNtupleDColumn(8,fNHits);
	analysisManager->FillNtupleDColumn(9,fDEVAEneTot1);
	analysisManager->FillNtupleDColumn(10,fDEVAEneTot2);
	analysisManager->FillNtupleDColumn(11,fDEVAEneTot3);
	analysisManager->FillNtupleDColumn(12,fDEVAEneTot4);
	analysisManager->FillNtupleDColumn(13,fDEVAEneTot5);
	analysisManager->FillNtupleDColumn(14,fDEVAEneTot6);
	analysisManager->FillNtupleDColumn(15,fDEVAEneTot);

//	/*
	analysisManager->FillNtupleDColumn(16,fDEVAEneFot1);
	analysisManager->FillNtupleDColumn(17,fDEVAEneFot2);
	analysisManager->FillNtupleDColumn(18,fDEVAEneFot3);
	analysisManager->FillNtupleDColumn(19,fDEVAEneFot4);
	analysisManager->FillNtupleDColumn(20,fDEVAEneFot5);
	analysisManager->FillNtupleDColumn(21,fDEVAEneFot6);
	analysisManager->FillNtupleDColumn(22,fDEVAEneFot);
	
	analysisManager->FillNtupleDColumn(23,fDEVAEnePos1);
	analysisManager->FillNtupleDColumn(24,fDEVAEnePos2);
	analysisManager->FillNtupleDColumn(25,fDEVAEnePos3);
	analysisManager->FillNtupleDColumn(26,fDEVAEnePos4);
	analysisManager->FillNtupleDColumn(27,fDEVAEnePos5);
	analysisManager->FillNtupleDColumn(28,fDEVAEnePos6);
	analysisManager->FillNtupleDColumn(29,fDEVAEnePos);
	
	analysisManager->FillNtupleDColumn(30,fDEVAEneEle1);
	analysisManager->FillNtupleDColumn(31,fDEVAEneEle2);
	analysisManager->FillNtupleDColumn(32,fDEVAEneEle3);
	analysisManager->FillNtupleDColumn(33,fDEVAEneEle4);
	analysisManager->FillNtupleDColumn(34,fDEVAEneEle5);
	analysisManager->FillNtupleDColumn(35,fDEVAEneEle6);
	analysisManager->FillNtupleDColumn(36,fDEVAEneEle);
//*/
	
	analysisManager->AddNtupleRow();
	
	G4cout <<"\n---> End of Event:"<<G4endl;
	
}


