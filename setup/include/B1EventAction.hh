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
	void AddDEVAEneTot(G4double ene) {fDEVAEneTot+=ene;}

	void AddDEVAEneFot1(G4double ene) {fDEVAEneFot1+=ene;}
	void AddDEVAEneFot2(G4double ene) {fDEVAEneFot2+=ene;}
	void AddDEVAEneFot3(G4double ene) {fDEVAEneFot3+=ene;}
	void AddDEVAEneFot4(G4double ene) {fDEVAEneFot4+=ene;}
	void AddDEVAEneFot5(G4double ene) {fDEVAEneFot5+=ene;}
	void AddDEVAEneFot6(G4double ene) {fDEVAEneFot6+=ene;}
	void AddDEVAEneFot(G4double ene) {fDEVAEneFot+=ene;}
	
	void AddDEVAEnePos1(G4double ene) {fDEVAEnePos1+=ene;}
	void AddDEVAEnePos2(G4double ene) {fDEVAEnePos2+=ene;}
	void AddDEVAEnePos3(G4double ene) {fDEVAEnePos3+=ene;}
	void AddDEVAEnePos4(G4double ene) {fDEVAEnePos4+=ene;}
	void AddDEVAEnePos5(G4double ene) {fDEVAEnePos5+=ene;}
	void AddDEVAEnePos6(G4double ene) {fDEVAEnePos6+=ene;}
	void AddDEVAEnePos(G4double ene) {fDEVAEnePos+=ene;}
	
	void AddDEVAEneEle1(G4double ene) {fDEVAEneEle1+=ene;}
	void AddDEVAEneEle2(G4double ene) {fDEVAEneEle2+=ene;}
	void AddDEVAEneEle3(G4double ene) {fDEVAEneEle3+=ene;}
	void AddDEVAEneEle4(G4double ene) {fDEVAEneEle4+=ene;}
	void AddDEVAEneEle5(G4double ene) {fDEVAEneEle5+=ene;}
	void AddDEVAEneEle6(G4double ene) {fDEVAEneEle6+=ene;}
	void AddDEVAEneEle(G4double ene) {fDEVAEneEle+=ene;}

	void AddPbGlassEne(G4double ene) {fPbGlass_DepEne+=ene;}
	void AddPbGlassCere(G4int nfot) {fPbGlass_PulseHeight+=nfot;}

	void AddCerenkovEneTot(G4double ene) {fCerenkovEneTot+=ene;}
//	void AddCerenkovNFot(G4double nfot) {fNCerenkov+=ene;}

	
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
	G4double fDEVAEneTot;

	G4double fDEVAEneFot1;
	G4double fDEVAEneFot2;
	G4double fDEVAEneFot3;
	G4double fDEVAEneFot4;
	G4double fDEVAEneFot5;
	G4double fDEVAEneFot6;
	G4double fDEVAEneFot;
	
	G4double fDEVAEnePos1;
	G4double fDEVAEnePos2;
	G4double fDEVAEnePos3;
	G4double fDEVAEnePos4;
	G4double fDEVAEnePos5;
	G4double fDEVAEnePos6;
	G4double fDEVAEnePos;
	
	G4double fDEVAEneEle1;
	G4double fDEVAEneEle2;
	G4double fDEVAEneEle3;
	G4double fDEVAEneEle4;
	G4double fDEVAEneEle5;
	G4double fDEVAEneEle6;
	G4double fDEVAEneEle;
	
	G4int fPbGlass_PulseHeight;
	G4double fPbGlass_DepEne;

	G4double fCerenkovEneTot;
	
	G4int fNCerenkov;
	G4int fNCerenkovPbGlass;

};


#endif

    
