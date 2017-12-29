#ifndef B1StackingAction_h
#define B1StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"
#include "B1EventAction.hh"
#include "B1RunAction.hh"



class B1StackingAction : public G4UserStackingAction
{
  public:
  B1StackingAction(B1EventAction*, B1RunAction *);
  ~B1StackingAction();
     
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);

	B1EventAction* feventAction;
	B1RunAction* frunAction;

	
};

#endif
