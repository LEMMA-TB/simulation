#ifndef B1Run_h
#define B1Run_h 1

#include "G4Run.hh"
#include "globals.hh"

class G4Event;
class B1Run : public G4Run
{
  public:
    B1Run();
    virtual ~B1Run();
    // method from the base class
    virtual void Merge(const G4Run*);
};

#endif

