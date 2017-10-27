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
	void AddNHits(G4int bnhits) {fNHits+=bnhits;}
	void AddDEVAEneTot1(G4double ene) {fDEVAEneTot1+=ene;}
	void AddDEVAEneTot2(G4double ene) {fDEVAEneTot2+=ene;}
	void AddDEVAEneTot3(G4double ene) {fDEVAEneTot3+=ene;}
	void AddDEVAEneTot4(G4double ene) {fDEVAEneTot4+=ene;}
	void AddDEVAEneTot5(G4double ene) {fDEVAEneTot5+=ene;}
	void AddDEVAEneTot6(G4double ene) {fDEVAEneTot6+=ene;}
	void AddDEVAEneTot7(G4double ene) {fDEVAEneTot7+=ene;}
	void AddDEVAEneTot8(G4double ene) {fDEVAEneTot8+=ene;}
	void AddDEVAEneTot9(G4double ene) {fDEVAEneTot9+=ene;}
	void AddDEVAEneTot10(G4double ene) {fDEVAEneTot10+=ene;}
	void AddDEVAEneTot11(G4double ene) {fDEVAEneTot11+=ene;}
	void AddDEVAEneTot12(G4double ene) {fDEVAEneTot12+=ene;}
	void AddDEVAEneTot(G4double ene) {fDEVAEneTot+=ene;}

	
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
	G4int fNHits;
//	G4int NHitsCounter;
	G4double fDEVAEneTot1;
	G4double fDEVAEneTot2;
	G4double fDEVAEneTot3;
	G4double fDEVAEneTot4;
	G4double fDEVAEneTot5;
	G4double fDEVAEneTot6;
	G4double fDEVAEneTot7;
	G4double fDEVAEneTot8;
	G4double fDEVAEneTot9;
	G4double fDEVAEneTot10;
	G4double fDEVAEneTot11;
	G4double fDEVAEneTot12;
	G4double fDEVAEneTot;
};


#endif

    
