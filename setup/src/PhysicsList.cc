// taken from: /examples/extended/electromagnetic/TestEm6/src/PhysicsList.cc
// $Id: PhysicsList.cc 73716 2013-09-09 10:07:13Z gcosmo $
//-------------------------------------------------------
#include "iostream"
#include "fstream"
#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
//------------------------------------
#include "G4Proton.hh"
#include "G4AntiProton.hh"
#include "G4Neutron.hh"
#include "G4AntiNeutron.hh"
//------------------------------------
#include "G4AnnihiToMuPair.hh"
#include "G4ComptonScattering.hh"
#include "G4eMultipleScattering.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eIonisation.hh"
#include "G4eplusAnnihilation.hh"
#include "G4eeToHadrons.hh"
#include "G4GammaConversion.hh"
#include "G4GammaConversionToMuons.hh"
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hhIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4Version.hh"
//---------------------------------
#include "G4Decay.hh"
#include "G4EmProcessOptions.hh"
//------------------------------------
#include "G4StepLimiter.hh"
#include "G4ProcessTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
: G4VUserPhysicsList(), fMes(0)
{
  defaultCutValue = 1.*km;
  fMes = new PhysicsListMessenger(this);
  SetVerboseLevel(1);
}


PhysicsList::~PhysicsList()
{
  delete fMes;
}

void PhysicsList::ConstructParticle()
{
  ConstructBosons();
  ConstructLeptons();
  ConstructHadrons();
}

void PhysicsList::ConstructBosons()
{
  // gamma
  G4Gamma::GammaDefinition();
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
}

void PhysicsList::ConstructLeptons()
{
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

void PhysicsList::ConstructHadrons()
{
  // mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
  // baryons
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
}

void PhysicsList::ConstructEM()
{
#if (G4VERSION_NUMBER >= 1030)
    G4ParticleTable::G4PTblDicIterator* theParticleIterator = G4ParticleTable::GetParticleTable()->GetIterator();
#endif
    
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    if (particleName == "gamma") {
      pmanager->AddDiscreteProcess(new G4GammaConversionToMuons); //g->mumu
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);      
      
    } else if (particleName == "e-") {
      pmanager->AddProcess(new G4eMultipleScattering,-1,1,1);
      pmanager->AddProcess(new G4eIonisation,        -1,2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,    -1,3,3);
      pmanager->AddProcess(new G4StepLimiter,       -1,-1,4);      
           
    } else if (particleName == "e+") {
      pmanager->AddProcess(new G4eMultipleScattering,-1,1,1);
      pmanager->AddProcess(new G4eIonisation,        -1,2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,    -1,3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,   0,-1,4); //gamma-gamma
      pmanager->AddDiscreteProcess(new G4AnnihiToMuPair); //ee->mumu
      pmanager->AddDiscreteProcess(new G4eeToHadrons);
      pmanager->AddDiscreteProcess(new G4StepLimiter);       

    } else if( particleName == "mu+" || particleName == "mu-" ) {
      pmanager->AddProcess(new G4MuMultipleScattering,-1,1,1);
      pmanager->AddProcess(new G4MuIonisation,        -1,2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,    -1,3,3);
      pmanager->AddProcess(new G4MuPairProduction,    -1,4,4);
      pmanager->AddProcess(new G4StepLimiter,         -1,-1,5);                
      
    } else if( particleName == "anti_proton") {
      pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);
      pmanager->AddProcess(new G4hhIonisation ,      -1,2,2);
      pmanager->AddProcess(new G4StepLimiter,        -1,-1,3);       

    } else if( particleName == "GenericIon") {
      pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);
      pmanager->AddProcess(new G4ionIonisation,      -1,2,2);
      pmanager->AddProcess(new G4StepLimiter,        -1,-1,3);       
      
    } else if( particle->GetPDGCharge() != 0.0 && !particle->IsShortLived()
            && particleName != "chargedgeantino") {
      pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);
      pmanager->AddProcess(new G4hIonisation,        -1,2,2);
      pmanager->AddProcess(new G4StepLimiter,        -1,-1,3);       
    }
  }
  
  G4EmProcessOptions opt;
  opt.SetVerbose(1);
  opt.SetMinEnergy(100*eV);       
  opt.SetMaxEnergy(1000*TeV);      
  opt.SetDEDXBinning(13*7);      
  opt.SetLambdaBinning(13*7);    
}


void PhysicsList::ConstructGeneral()
{
#if (G4VERSION_NUMBER >= 1030)
    G4ParticleTable::G4PTblDicIterator* theParticleIterator = G4ParticleTable::GetParticleTable()->GetIterator();
#endif
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while ((*theParticleIterator)()){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle) && !particle->IsShortLived())
      { pmanager ->AddProcess(theDecayProcess);
        // set ordering for PostStepDoIt and AtRestDoIt
        pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
        pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
      }
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Scale muon pair cross section 
  // Function call moved from SetCuts to ConstructGeneral
  // to allow proper funcionalities with MultiThread
//  SetAnnihiToMuPairFac(1.e3);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
}
    
 
 void PhysicsList::SetCuts()
 {
   if (verboseLevel>0){
     G4cout << "PhysicsList::SetCuts:";
     //     G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
   }  
   //  SetCutValue(defaultCutValue, "gamma");
   //  SetCutValue(defaultCutValue, "e-");
   //  SetCutValue(defaultCutValue, "e+");
   SetCutValue(1.*mm, "gamma");
   SetCutValue(1.*mm, "e-");
   SetCutValue(1.*mm, "e+");  
   //+++++++++++++++++++++++++
//   SetAnnihiToMuPairFac(1.e6);  // enhance cross section for this process
   //+++++++++++++++++++++++++    
   if (verboseLevel>0) DumpCutValuesTable();
 }


 void PhysicsList::SetAnnihiToMuPairFac(G4double fac)
 {
   G4ProcessTable* theProcessTable = G4ProcessTable::GetProcessTable();
   G4AnnihiToMuPair* annihiToMuPairProcess = (G4AnnihiToMuPair*) 
     theProcessTable->FindProcess("AnnihiToMuPair","e+");
   if(annihiToMuPairProcess){ 
     annihiToMuPairProcess->SetCrossSecFactor(fac);
     G4cout << "FAC= "<<fac<<G4endl;
   }else G4cout 
	   << "Warning. No process AnnihiToMuPair found, SetAnnihiToMuPairFac ignored"
	   << G4endl;
 }
 


 void PhysicsList::SetGammaToMuPairFac(G4double fac)
 {
   G4ProcessTable* theProcessTable = G4ProcessTable::GetProcessTable();
   G4GammaConversionToMuons* gammaToMuPairProcess = (G4GammaConversionToMuons*)
    theProcessTable->FindProcess("GammaToMuPair","gamma");
   if(gammaToMuPairProcess) gammaToMuPairProcess->SetCrossSecFactor(fac);
   else G4cout 
	  << "Warning. No process GammaToMuPair found, SetGammaToMuPairFac was ignored"
	  << G4endl;
 }
 
  
 
void PhysicsList::SetAnnihiToHadronFac(G4double fac)
 {
   G4ProcessTable* theProcessTable = G4ProcessTable::GetProcessTable();
   G4eeToHadrons* eehadProcess = (G4eeToHadrons*)
     theProcessTable->FindProcess("ee2hadr","e+");
   if(eehadProcess) eehadProcess->SetCrossSecFactor(fac);
   else G4cout
	  << "Warning. No process ee2hadr found, SetAnnihiToHadronFac was ignored"
	  << G4endl;
 }
 
 
