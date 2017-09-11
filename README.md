# simulation
Geant4 simulation of LEMMA test beam, done @CERN on ~August 2017.

### GEOMETRY
The geometry is the one of the final configuration

### PRIMARY PARTICLE
The simulation is set to simulate primary positrons starting at the origin (0,0,0). It is possible to simulate a realistic beam (energy, angular and position spread), but there is a flag (SimpleFlag) in B1PrimaryGeneratorAction.cc to select the simple case of ideal beam.

### OUTPUT
The simulation creates a LemmaMC.root file, in which on an event (i.e. a primary particle) by event basis it is stored:
BEAM vector (one entry per primary particle):
- BeamX: X coordinate of primary particle [mm];
- BeamY: Y coordinate of primary particle [mm];
- BeamZ: Z coordinate of primary particle [mm];
- BeamCX: X directive cosine of primary particle;
- BeamCY: Y directive cosine  of primary particle;
- BeamCZ: Z directive cosine  of primary particle;
- BeamEne: kinetic energy of the beam [GeV];
INTERACTIONS vector (one entry per interaction happening at the border between two different regions, to spare CPU time and disk space):
- Subdet: number of subdetector in which the interactio happened
- Idp: PDG code of particle interacting (11=e-, -11=e+, 22=gamma...);
- Ipar: parent ID of the track (0 is primary...);
- Itrack: track ID of the track;
- Time: time age of the track [ns];
- X: X coordinate of the interaction [cm];
- Y: Y coordinate of the interaction [cm];
- Z: Z coordinate of the interaction [cm];
- P: momentum of the particle [GeV];
- PX: X component of momentum of the particle [GeV];
- PY: Y component of momentum of the particle [GeV];
- PZ: Z component of momentum of the particle [GeV];
- VertexX: X component of interaction vertex vector [cm];
- VertexY: Y component of interaction vertex vector [cm];
- VertexZ: Z component of interaction vertex vector [cm];
- kinev: vertex kinetic energy [GeV];
- PXvdir: X component of momentum of interaction vertex vector [normalised to P];
- PYvdir: Y component of momentum of interaction vertex vector [normalised to P];
- PZvdir: Z component of momentum of interaction vertex vector [normalised to P];
- Iev: event id (in this way we also store the number of entries to the INTERACTIONS vector for each event);
- Step: number of current step;
- InextStep: is 1 if there will be another step, 0 if the particle is going to die


### CHANGE-LOG
2017.09.11 Modified by collamaf
- 
