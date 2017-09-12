#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "HistoManager.hh"
#include "B1RunAction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
//---------------------------
#include "G4ProcessType.hh"

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction)
: G4UserSteppingAction(),
fEventAction(eventAction),
runStepAction(runAction),
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
fScoringVolume_Gcal(0)
{}

B1SteppingAction::~B1SteppingAction()
{}

void B1SteppingAction::UserSteppingAction(const G4Step* step){
	const B1DetectorConstruction* detectorConstruction = static_cast<const B1DetectorConstruction*>
	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	if (!fScoringVolume_Trk1) {fScoringVolume_Trk1 = detectorConstruction->GetScoringVolume_Trk1();}
	if (!fScoringVolume_Trk2) {fScoringVolume_Trk2 = detectorConstruction->GetScoringVolume_Trk2();}
	if (!fScoringVolume_T1)   {fScoringVolume_T1   = detectorConstruction->GetScoringVolume_T1();}
	if (!fScoringVolume_Trk3) {fScoringVolume_Trk3 = detectorConstruction->GetScoringVolume_Trk3();}
	if (!fScoringVolume_Trk4) {fScoringVolume_Trk4 = detectorConstruction->GetScoringVolume_Trk4();}
	if (!fScoringVolume_Trk5a) {fScoringVolume_Trk5a = detectorConstruction->GetScoringVolume_Trk5a();}
	if (!fScoringVolume_Trk5b) {fScoringVolume_Trk5b = detectorConstruction->GetScoringVolume_Trk5b();}
	if (!fScoringVolume_Trk6a) {fScoringVolume_Trk6a = detectorConstruction->GetScoringVolume_Trk6a();}
	if (!fScoringVolume_Trk6b) {fScoringVolume_Trk6b = detectorConstruction->GetScoringVolume_Trk6b();}
	if (!fScoringVolume_Chamber)   {fScoringVolume_Chamber   = detectorConstruction->GetScoringVolume_Chamber();}
	if (!fScoringVolume_ScintA)   {fScoringVolume_ScintA   = detectorConstruction->GetScoringVolume_ScintA();}
	if (!fScoringVolume_ScintB)   {fScoringVolume_ScintB   = detectorConstruction->GetScoringVolume_ScintB();}
	if (!fScoringVolume_Ecal)   {fScoringVolume_Ecal   = detectorConstruction->GetScoringVolume_Ecal();}
	if (!fScoringVolume_Gcal)   {fScoringVolume_Gcal   = detectorConstruction->GetScoringVolume_Gcal();}
	//	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	
	
	//=========================================================
	//	if (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary){
	// particle enters a new subdet
	//--------------------------------------------------------
	G4LogicalVolume* volume =
	step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	G4bool SHOW = false;
	G4bool dofill = false;
	G4int subdet;
	if      (volume==fScoringVolume_Trk1) {subdet=10; dofill=true;}  // Trk1
	else if (volume==fScoringVolume_Trk2) {subdet=20; dofill=true;}  // Trk2
	else if (volume==fScoringVolume_T1)   {subdet=25; dofill=true;}  // T1 target
	else if (volume==fScoringVolume_Trk3) {subdet=30; dofill=true;}  // Trk3
	else if (volume==fScoringVolume_Trk4) {subdet=40; dofill=true;}  // Trk4
	else if (volume==fScoringVolume_Trk5a) {subdet=51; dofill=true;}  // Trk5a
	else if (volume==fScoringVolume_Trk5b) {subdet=50; dofill=true;}  // Trk5b
	else if (volume==fScoringVolume_Trk6a) {subdet=56; dofill=true;}  // Trk6a
	else if (volume==fScoringVolume_Trk6b) {subdet=55; dofill=true;}  // Trk6b
	else if (volume==fScoringVolume_Chamber)   {subdet=70; dofill=true;}  // chamber
	else if (volume==fScoringVolume_ScintA)   {subdet=72; dofill=true;}  // scintA
	else if (volume==fScoringVolume_ScintB)   {subdet=74; dofill=true;}  // scintB
	else if (volume==fScoringVolume_Ecal)   {subdet=76; dofill=true;}  // Ecal
	else if (volume==fScoringVolume_Gcal)   {subdet=78; dofill=true;}  // Gcal
	
	//-- store info
	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary) || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary))) {
	
		G4int iev = -999;
		const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
		if (evt) iev = evt->GetEventID();
		G4int Idp = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
		G4int Ipar = step->GetTrack()->GetParentID();
		G4int Itrack = step->GetTrack()->GetTrackID();
		G4int Istep = step->GetTrack()->GetCurrentStepNumber();
		G4ThreeVector xsubdet = step->GetPreStepPoint()->GetPosition();
		G4double time = step->GetTrack()->GetGlobalTime()/ns;
		G4ThreeVector xvertex(0.,0.,0.);
		G4ThreeVector pvertexdir(0.,0.,0.);
		G4double kinev=0.;
		G4String process;
		G4int pro=0;
//		G4int HitsCounter=0;
		fEventAction->AddNHits(1);
		
		G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();
		G4double pmod = momentum.mag();
		G4int Inextstep=1;
		if (step->GetTrack()->GetTrackStatus()!=fAlive) Inextstep=0;
		
		
		pvertexdir = step->GetTrack()->GetVertexMomentumDirection();
		kinev = step->GetTrack()->GetVertexKineticEnergy();
		
		//process = step->GetTrack()->GetCreatorProcess()->GetProcessName();
		pro = step->GetTrack()->GetCreatorProcess()->GetProcessSubType();
		
//		process = step->GetTrack()->GetCreatorProcess()->GetProcessName();
		// G4cout<<process<<", "<<pro<<G4endl;
		
		
		//			if (Itrack!=1) { // different from gun particle
		xvertex = step->GetTrack()->GetVertexPosition();
		
		//NEW SCORING
	
		(runStepAction->GetSubdet()).push_back(subdet);
		(runStepAction->GetIdp()).push_back(Idp);
		(runStepAction->GetIpar()).push_back(Ipar);
		(runStepAction->GetItrack()).push_back(Itrack);
		(runStepAction->GetTime()).push_back(time);
		(runStepAction->GetVectorX()).push_back(xsubdet.x()/cm);
		(runStepAction->GetVectorY()).push_back(xsubdet.y()/cm);
		(runStepAction->GetVectorZ()).push_back(xsubdet.z()/cm);
		(runStepAction->GetVectorP()).push_back(momentum.mag()/GeV);
		(runStepAction->GetVectorPX()).push_back(momentum.x()/GeV);
		(runStepAction->GetVectorPY()).push_back(momentum.y()/GeV);
		(runStepAction->GetVectorPZ()).push_back(momentum.z()/GeV);
		(runStepAction->GetVertexX()).push_back(xvertex.x()/cm);
		(runStepAction->GetVertexY()).push_back(xvertex.y()/cm);
		(runStepAction->GetVertexZ()).push_back(xvertex.z()/cm);
		(runStepAction->GetKinev()).push_back(kinev/GeV);
		(runStepAction->GetVectorPXvdir()).push_back(pvertexdir.x()/GeV);
		(runStepAction->GetVectorPYvdir()).push_back(pvertexdir.y()/GeV);
		(runStepAction->GetVectorPZvdir()).push_back(pvertexdir.z()/GeV);
		(runStepAction->GetProcess()).push_back(1);
		(runStepAction->GetIev()).push_back(iev);
		(runStepAction->GetStep()).push_back(Istep);
		(runStepAction->GetInextStep()).push_back(Inextstep);
//		(runStepAction->GetNHits()).push_back(Inextstep);
//		(runStepAction->GetItrack()).push_back(-999);
		



		if (SHOW) G4cout<<
			"  Evt="<<iev<<
			", IDtrack="<<Itrack<<
			", Idp="<<Idp<<
			", Ipar="<<Ipar<<
			", p="<<pmod<<
			", z="<<xsubdet[2]<<
			", subdet="<<subdet<<
			", vertex="<<xvertex[2]<<
			", process="<<process<<
			G4endl;
		 		/**/
	} //if(dofill)
	
	//	} // if(preStep)
	
}
