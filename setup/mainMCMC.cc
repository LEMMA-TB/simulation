#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"  
#endif
//----------------------------------
#include "G4UImanager.hh"
#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VUserPhysicsList.hh"
#include "PhysicsList.hh"
#include "B1RunAction.hh"
#include "B1StackingAction.hh"
#include "SteppingVerbose.hh"
#include "Randomize.hh"
#include "time.h"
#include "G4AnnihiToMuPair.hh"
#include "G4PhysListFactory.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4ChannelingPhysics.hh"
#include "G4GenericBiasingPhysics.hh"
#include "G4ProcessTable.hh"
#include "G4EmStandardPhysicsSS.hh"

//------------------------------
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


int main(int argc,char** argv)
{
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time(NULL);
  G4Random::setTheSeed(seed);
  
//#ifdef G4MULTITHREADED
#if 0
	G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads( G4Threading::G4GetNumberOfCores() );
#else
  G4RunManager* runManager = new G4RunManager;
#endif
	
	G4bool MuonBeamFlag=false;  //switching on this flag generates 22GeV mu- beam, and removes the target, otherwise 45GeV e+. The SimpleFlag in PrimGenAction is still considered for the beam distribution
	
	G4bool ElectronBeamFlag=false;  //switching on this flag generates 22GeV e- beam, and removes the target, otherwise 45GeV e+. The SimpleFlag in PrimGenAction is still considered for the beam distribution
	
 
// INITIALIZE

//==================================================
  G4bool FTFP = false; // standard Geant4 PhysicsList
  G4bool channeling = false;
  G4String ctype = "Si" ;  // "C" or "Si"
//==================================================
  B1DetectorConstruction* detector =new B1DetectorConstruction(MuonBeamFlag, ElectronBeamFlag);
  detector->SetChanneling(channeling,ctype);
  
  if ( FTFP ){
    G4PhysListFactory *physListFactory = new G4PhysListFactory();
    G4VModularPhysicsList* physics = 
      physListFactory->GetReferencePhysList("FTFP_BERT_EMV"); // default
    physics->SetVerboseLevel(1);
    if(channeling){
      G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics();
      physics->RegisterPhysics(new G4ChannelingPhysics());
      //physics->ReplacePhysics(new G4EmStandardPhysicsSS());
      biasingPhysics->PhysicsBiasAllCharged();
      physics->RegisterPhysics(biasingPhysics);
      //          detector->SetChanneling(true);
    }    
    runManager->SetUserInitialization(physics);
  } else { // use my own PhysicsList.cc 
    runManager->SetUserInitialization(new PhysicsList());
  }
  
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new B1ActionInitialization(MuonBeamFlag,ElectronBeamFlag));
  runManager->Initialize();  // init kernel
  
  
#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
  
  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  if (argc!=1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
    //UImanager->ApplyCommand("/control/execute init.mac"); 
  }
  else {
    // interactive mode : define UI session
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac"); 
#else
    UImanager->ApplyCommand("/control/execute init.mac"); 
#endif
    ui->SessionStart();
    delete ui;
#endif
  }
  
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;  
  return 0;
}
