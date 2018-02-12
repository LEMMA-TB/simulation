#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class PhysicsListMessenger;
class G4GammaConversionToMuons;
class G4AnnihiToMuPair;
class G4eeToHadrons; 

class PhysicsList: public G4VUserPhysicsList
{
public:
  PhysicsList();
  ~PhysicsList();
  
  // Construct particles
  virtual void ConstructParticle();
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructHadrons();
  void SetCuts();
  
  // Construct processes and register them
  virtual void ConstructProcess();
  void ConstructGeneral();
  void ConstructEM();
  void ConstructPhotonuclear();
  void SetGammaToMuPairFac(G4double);
  void SetAnnihiToMuPairFac(G4double);
  void SetAnnihiToHadronFac(G4double);
	void ConstructOp();
  //PhysicsListMessenger*  fMes;
private:
   PhysicsListMessenger*  fMes;
};

#endif
