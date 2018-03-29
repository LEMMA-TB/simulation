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
#include "G4OpticalPhoton.hh"

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4double EThr)
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
fScoringVolume_DEVA(0),
fScoringVolume_Gcal(0),
fStoreCaloEnDepFlag(StoreCaloEnDepFlag),
fEThr(EThr)
{}

B1SteppingAction::~B1SteppingAction()
{}

void B1SteppingAction::UserSteppingAction(const G4Step* step){
	const G4double hplanck=4.136e-15; //eV*s
	const G4double clight=3e14; //um/s
	const G4double CerFotLambdaCut=0.2; //in [um], cut due to PMT sensitivity
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
	if (!fScoringVolume_DEVA)   {fScoringVolume_DEVA   = detectorConstruction->GetScoringVolume_DEVA();}
	if (!fScoringVolume_Gcal)   {fScoringVolume_Gcal   = detectorConstruction->GetScoringVolume_Gcal();}
	if (!fScoringVolume_PbGlass)   {fScoringVolume_PbGlass   = detectorConstruction->GetScoringVolume_PbGlass();}
	if (!fScoringVolume_Cerenkov)   {fScoringVolume_Cerenkov   = detectorConstruction->GetScoringVolume_Cerenkov();}	//	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	
	G4LogicalVolume* volume =
	step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	G4VPhysicalVolume* ThisVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
	G4VPhysicalVolume* NextVol = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
	
	G4bool SHOW = false;
	G4bool dofill = false;
	G4int subdet=-10;
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
	else if (volume==fScoringVolume_Ecal)   {subdet=76; dofill=true;}  // Ecal - DEVA
	else if (volume==fScoringVolume_DEVA)   {subdet=77; dofill=true;}  // Ecal - DEVA active components
	else if (volume==fScoringVolume_Gcal)   {subdet=78; dofill=true;}  // Gcal
	else if (volume==fScoringVolume_PbGlass)   {subdet=79; dofill=true;}  // PbGlass detector
	else if (volume==fScoringVolume_Cerenkov)   {subdet=80; dofill=true;}  // Cerenkov detector

	
	//Score energy deposition into DEVA elements (if fStoreCaloEnDepFlag true in main!)
	G4int CopyNb=step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();
	G4double DepEne=step->GetTotalEnergyDeposit()/GeV;
	G4int Pid=step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
	

	if (subdet==77 && DepEne>0 && fStoreCaloEnDepFlag) { //DEVA deposited energy - avoiding saving 0ene events spares about 20% of disk space...
		fEventAction->AddDEVAEneTot(DepEne);
		if (CopyNb==0 || CopyNb==1) {
			(runStepAction->GetDEVADepo())[0]+=DepEne;
		} else if (CopyNb==2 || CopyNb==3) {
			(runStepAction->GetDEVADepo())[1]+=DepEne;
		}
		if (CopyNb==4 || CopyNb==5) {
			(runStepAction->GetDEVADepo())[2]+=DepEne;
		}
		if (CopyNb==6 || CopyNb==7) {
			(runStepAction->GetDEVADepo())[3]+=DepEne;
		}
		if (CopyNb==8 || CopyNb==9) {
			(runStepAction->GetDEVADepo())[4]+=DepEne;
		}
		if (CopyNb==10 || CopyNb==11) {
			(runStepAction->GetDEVADepo())[5]+=DepEne;
		}
	}
	
	if (subdet==79 && DepEne>0 && fStoreCaloEnDepFlag) { //PbGlass deposited energy
		fEventAction->AddPbGlassEne(DepEne);
	}
	
	if (subdet==80 && DepEne>0 && fStoreCaloEnDepFlag) { //Cerenkov deposited energy (only 4 of 6 channels were red): Channels go from 0 to 6 bottom-forward to top-backward wrt beam entering direction: Iacoangeli says 2,3,5,6 were on
		fEventAction->AddCerenkovEneTot(DepEne);
		if (CopyNb==0 ) {
			(runStepAction->GetCerenkovDepo())[1]+=DepEne;
		}
		if (CopyNb==1) {
			(runStepAction->GetCerenkovDepo())[2]+=DepEne;
		}
		if (CopyNb==3) {
			(runStepAction->GetCerenkovDepo())[4]+=DepEne;
		}
		if (CopyNb==4 ) {
			(runStepAction->GetCerenkovDepo())[5]+=DepEne;
		}
	}
	
	if (subdet==72 && DepEne>0 && fStoreCaloEnDepFlag) { //Scint72 deposited energy
		(runStepAction->GetScint72DepEne()).push_back(DepEne);
	}
	if (subdet==74 && DepEne>0 && fStoreCaloEnDepFlag) { //Scint74 deposited energy
		(runStepAction->GetScint74DepEne()).push_back(DepEne);
	}
	//added on 15.12.17 @ Padova
	if (NextVol && ThisVol->GetName()=="EcalDummy" && NextVol->GetName()=="Ecal") {
		runStepAction->GetDEVAInX().push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
		runStepAction->GetDEVAInY().push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
		runStepAction->GetDEVAInZ().push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
	}
	
	if (fEThr>0) fCutFlag=true;
	
	if (step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "Cerenkov") { //se sto facendo uno step di tipo cerenkov
		//		G4cout<<"DEBUG Cerenkov!!!"<<G4endl;
		const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
		if (secondaries->size()>0) {
			for (unsigned int i=0; i<secondaries->size(); i++) { //ciclo su tutti i secondari di questo step
				if (secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) { //se è un fotone ottico
					if (secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Cerenkov") { //se è stato creato dal processo Cerenkov
						G4double CerFotEne=secondaries->at(i)->GetKineticEnergy()/eV;
						G4double CerFotLambda=hplanck*clight/CerFotEne;

						// se sono nel detector di PbGlass
						if (subdet==79 && CerFotLambda>0) {
							(fEventAction->AddPbGlassCere(1)); //incremento di 1 il contatore di fotoni cerenkov del rispettivo
						}
						// se sono nel detector di Cerenkov
						else if (subdet==80 && CerFotLambda>CerFotLambdaCut) {
							(runStepAction->GetCerenkovDepoOpt())[CopyNb]+=1; //incremento di 1 il contatore di fotoni cerenkov del rispettivo canale
						}
//						G4cout<<"DEBUG Cerenkov!!! Energia fotone= "<<CerFotEne<<", lamda [um]= "<< CerFotLambda<<", subdet= "<<subdet<<  G4endl;
					}
				}
			}
		}
	}
	
	
	
	
	//-- store info
	//	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary)
	//				   || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<EThr) ) { //If Output Cut required do not store photons under a certain energy
	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary)
				   || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
		
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
		//			if (Itrack!=1) { // different from gun particle
		xvertex = step->GetTrack()->GetVertexPosition();
		
		if(subdet==77) (runStepAction->GetCopyNb()).push_back(CopyNb);  //I'm interested in CopyNb only for DEVA active components (subdet==77)
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
