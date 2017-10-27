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
	
	fDEVAEneTot1=0;
	fDEVAEneTot2=0;
	fDEVAEneTot3=0;
	fDEVAEneTot4=0;
	fDEVAEneTot5=0;
	fDEVAEneTot6=0;
	fDEVAEneTot7=0;
	fDEVAEneTot8=0;
	fDEVAEneTot9=0;
	fDEVAEneTot10=0;
	fDEVAEneTot11=0;
	fDEVAEneTot12=0;
	fDEVAEneTot=0;
	
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
	analysisManager->FillNtupleDColumn(15,fDEVAEneTot7);
	analysisManager->FillNtupleDColumn(16,fDEVAEneTot8);
	analysisManager->FillNtupleDColumn(17,fDEVAEneTot9);
	analysisManager->FillNtupleDColumn(18,fDEVAEneTot10);
	analysisManager->FillNtupleDColumn(19,fDEVAEneTot11);
	analysisManager->FillNtupleDColumn(20,fDEVAEneTot12);
	analysisManager->FillNtupleDColumn(21,fDEVAEneTot);


	
	analysisManager->AddNtupleRow();
	
	G4cout <<"\n---> End of Event:"<<G4endl;
	
}


