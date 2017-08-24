#include "B1Run.hh"

B1Run::B1Run()
: G4Run()
{} 

B1Run::~B1Run(){} 
 
void B1Run::Merge(const G4Run* run){
  G4Run::Merge(run); 
} 

