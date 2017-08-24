#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithADouble;


class PhysicsListMessenger: public G4UImessenger
{
public:  
  PhysicsListMessenger(PhysicsList*);
  ~PhysicsListMessenger();
  
  virtual void SetNewValue(G4UIcommand*, G4String);
  
private:  
  PhysicsList*        fPhysList;    
  G4UIdirectory*      fPhysDir;    
  G4UIcmdWithADouble* fGammaToMuPairFacCmd;
  G4UIcmdWithADouble* fAnnihiToMuPairFacCmd;
  G4UIcmdWithADouble* fAnnihiToHadronFacCmd;    
};

#endif
