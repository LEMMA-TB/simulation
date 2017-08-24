#include "PhysicsListMessenger.hh"
#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"

PhysicsListMessenger::PhysicsListMessenger(PhysicsList* physL)
:G4UImessenger(),fPhysList(physL),
 fPhysDir(0),    
 fGammaToMuPairFacCmd(0),
 fAnnihiToMuPairFacCmd(0),
 fAnnihiToHadronFacCmd(0)
{
  fPhysDir = new G4UIdirectory("/testem/phys/");
  fPhysDir->SetGuidance("physics list commands");

  fGammaToMuPairFacCmd = new G4UIcmdWithADouble("/testem/phys/SetGammaToMuPairFac",this);
  fGammaToMuPairFacCmd->SetGuidance("Set factor to artificially increase the GammaToMuPair cross section");
  fGammaToMuPairFacCmd->SetParameterName("GammaToMuPairFac",false);
  fGammaToMuPairFacCmd->SetRange("GammaToMuPairFac>0.0");
  fGammaToMuPairFacCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fAnnihiToMuPairFacCmd = new G4UIcmdWithADouble("/testem/phys/SetAnnihiToMuPairFac",this);
  fAnnihiToMuPairFacCmd->SetGuidance("Set factor to artificially increase the AnnihiToMuPair cross section");
  fAnnihiToMuPairFacCmd->SetParameterName("AnnihiToMuPairFac",false);
  fAnnihiToMuPairFacCmd->SetRange("AnnihiToMuPairFac>0.0");
  fAnnihiToMuPairFacCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fAnnihiToHadronFacCmd = new G4UIcmdWithADouble("/testem/phys/SetAnnihiToHadronFac",this);
  fAnnihiToHadronFacCmd->SetGuidance("Set factor to artificially increase the AnnihiToHadrons cross section");
  fAnnihiToHadronFacCmd->SetParameterName("AnnihiToHadFac",false);
  fAnnihiToHadronFacCmd->SetRange("AnnihiToHadFac>0.0");
  fAnnihiToHadronFacCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
}


PhysicsListMessenger::~PhysicsListMessenger()
{
  delete fGammaToMuPairFacCmd;
  delete fAnnihiToMuPairFacCmd;
  delete fAnnihiToHadronFacCmd;  
  delete fPhysDir;  
}

void PhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if(command == fGammaToMuPairFacCmd)
    { fPhysList->SetGammaToMuPairFac(
		   fGammaToMuPairFacCmd->GetNewDoubleValue(newValue));}   
  
  if( command == fAnnihiToMuPairFacCmd)
   { fPhysList->SetAnnihiToMuPairFac(
                   fAnnihiToMuPairFacCmd->GetNewDoubleValue(newValue));}
                          
  if( command == fAnnihiToHadronFacCmd)
   { fPhysList->SetAnnihiToHadronFac(
		   fAnnihiToHadronFacCmd->GetNewDoubleValue(newValue));}
}

