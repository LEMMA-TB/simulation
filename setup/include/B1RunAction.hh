#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>


class G4Run;
class G4LogicalVolume;
class B1RunAction : public G4UserRunAction
{
  public:
    B1RunAction();
    virtual ~B1RunAction();
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
	
	std::vector<G4double>& GetBeamX() {return RunVectorBeamX; }
	std::vector<G4double>& GetBeamY() {return RunVectorBeamY; }
	std::vector<G4double>& GetBeamZ() {return RunVectorBeamZ; }
	std::vector<G4double>& GetBeamCX() {return RunVectorBeamCX; }
	std::vector<G4double>& GetBeamCY() {return RunVectorBeamCY; }
	std::vector<G4double>& GetBeamCZ() {return RunVectorBeamCZ; }
	std::vector<G4double>& GetBeamEne() {return RunVectorBeamEne; }
	std::vector<G4double>& GetBeamPart() {return RunVectorBeamPart; }

	
	
	std::vector<G4double>& GetSubdet() {return RunVectorSubdet; }
	std::vector<G4double>& GetIdp() {return RunVectorIdp; }
	std::vector<G4double>& GetIpar() {return RunVectorIpar; }
	std::vector<G4double>& GetItrack() {return RunVectorItrack; }
	std::vector<G4double>& GetTime() {return RunVectorTime; }
	std::vector<G4double>& GetVectorX() {return RunVectorX; }
	std::vector<G4double>& GetVectorY() {return RunVectorY; }
	std::vector<G4double>& GetVectorZ() {return RunVectorZ; }
	std::vector<G4double>& GetVectorP() {return RunVectorP; }
	std::vector<G4double>& GetVectorPX() {return RunVectorPX; }
	std::vector<G4double>& GetVectorPY() {return RunVectorPY; }
	std::vector<G4double>& GetVectorPZ() {return RunVectorPZ; }
	std::vector<G4double>& GetVertexX() {return RunVectorVertexX; }
	std::vector<G4double>& GetVertexY() {return RunVectorVertexY; }
	std::vector<G4double>& GetVertexZ() {return RunVectorVertexZ; }
	std::vector<G4double>& GetKinev() {return RunVectorKinev; }
	std::vector<G4double>& GetVectorPXvdir() {return RunVectorPXvdir; }
	std::vector<G4double>& GetVectorPYvdir() {return RunVectorPYvdir; }
	std::vector<G4double>& GetVectorPZvdir() {return RunVectorPZvdir; }
	std::vector<G4int>& GetProcess() {return RunVectorProcess; }
	std::vector<G4double>& GetIev() {return RunVectorIev; }
	std::vector<G4double>& GetStep() {return RunVectorStep; }
	std::vector<G4double>& GetInextStep() {return RunVectorInextStep; }
	std::vector<G4double>& GetCopyNb() {return RunVectorCopyNb; }
	
	std::vector<G4double>& GetDEVADepo() {return RunVectorDEVADepo; }
	std::vector<G4double>& GetCerenkovDepo() {return RunVectorCerenkovDepo; }
	std::vector<G4int>& GetCerenkovDepoOpt() {return RunVectorCerenkovDepoOpt; }

	std::vector<G4double>& GetDEVAInX() {return RunVectorDEVAInX; }
	std::vector<G4double>& GetDEVAInY() {return RunVectorDEVAInY; }
	std::vector<G4double>& GetDEVAInZ() {return RunVectorDEVAInZ; }
	
	std::vector<G4double>& GetScint72DepEne() {return RunVectorScint72DepEne; }
	std::vector<G4double>& GetScint74DepEne() {return RunVectorScint74DepEne; }

	std::vector<G4double>& GetVectorCross() {return RunVectorCross; }

	
//	std::vector<G4double>& GetNHits() {return RunVectorNHits; }
//	std::vector<G4double>& GetItrack() {return RunVectorItrack; }

private:
	std::vector<G4double> RunVectorBeamX;
	std::vector<G4double> RunVectorBeamY;
	std::vector<G4double> RunVectorBeamZ;
	std::vector<G4double> RunVectorBeamCX;
	std::vector<G4double> RunVectorBeamCY;
	std::vector<G4double> RunVectorBeamCZ;
	std::vector<G4double> RunVectorBeamEne;
	std::vector<G4double> RunVectorBeamPart;

	std::vector<G4double> RunVectorSubdet;
	std::vector<G4double> RunVectorIdp;
	std::vector<G4double> RunVectorIpar;
	std::vector<G4double> RunVectorItrack;
	std::vector<G4double> RunVectorTime;
	std::vector<G4double> RunVectorX;
	std::vector<G4double> RunVectorY;
	std::vector<G4double> RunVectorZ;
	std::vector<G4double> RunVectorP;
	std::vector<G4double> RunVectorPX;
	std::vector<G4double> RunVectorPY;
	std::vector<G4double> RunVectorPZ;
	std::vector<G4double> RunVectorVertexX;
	std::vector<G4double> RunVectorVertexY;
	std::vector<G4double> RunVectorVertexZ;
	std::vector<G4double> RunVectorKinev;
	std::vector<G4double> RunVectorPXvdir;
	std::vector<G4double> RunVectorPYvdir;
	std::vector<G4double> RunVectorPZvdir;
	std::vector<G4int> RunVectorProcess;
	std::vector<G4double> RunVectorIev;
	std::vector<G4double> RunVectorStep;
	std::vector<G4double> RunVectorInextStep;
	std::vector<G4double> RunVectorCopyNb;
	
	std::vector<G4double> RunVectorDEVADepo;
	std::vector<G4double> RunVectorCerenkovDepo;
	std::vector<G4int> RunVectorCerenkovDepoOpt;

	std::vector<G4double> RunVectorDEVAInX;
	std::vector<G4double> RunVectorDEVAInY;
	std::vector<G4double> RunVectorDEVAInZ;
	
	std::vector<G4double> RunVectorScint72DepEne;
	std::vector<G4double> RunVectorScint74DepEne;

	std::vector<G4double> RunVectorCross;

	
	
//	std::vector<G4double> RunVectorNHits;
//	std::vector<G4double> RunVectorItrack;

	
};


#endif

