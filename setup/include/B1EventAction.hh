#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"


class B1RunAction;


class B1EventAction : public G4UserEventAction
{
public:
  B1EventAction(B1RunAction* runAction);
  virtual ~B1EventAction();    
  virtual void BeginOfEventAction(const G4Event* evt);
  virtual void EndOfEventAction(const G4Event* evt);
  G4int evtNb;
	
	void SetBeamX(G4double bx) {fBeamX=bx;}
	void SetBeamY(G4double by) {fBeamY=by;}
	void SetBeamZ(G4double bz) {fBeamZ=bz;}
	void SetBeamCX(G4double bcx) {fBeamCX=bcx;}
	void SetBeamCY(G4double bcy) {fBeamCY=bcy;}
	void SetBeamCZ(G4double bcz) {fBeamCZ=bcz;}
	void SetBeamEne(G4double ben) {fBeamEne=ben;}
	void SetBeamPart(G4double bpart) {fBeamPart=bpart;}
	
private:
	B1RunAction* fRunAction;

	G4double fBeamX;
	G4double fBeamY;
	G4double fBeamZ;
	G4double fBeamEne;
	G4double fBeamPart;
	G4double fBeamCX;
	G4double fBeamCY;
	G4double fBeamCZ;

};


#endif

    
