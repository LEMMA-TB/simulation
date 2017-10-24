# simulation
Geant4 simulation of LEMMA test beam, done @CERN on ~August 2017.

### HOW TO RUN
- You have to have Geant4 up and running
- type:
cd build
cmake -DGeant4_DIR=$G4INSTALL ../setup/
make
./mainMCMC

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
- BeamPart: PDG code of primary particle (11=e-, -11=e+, 22=gamma, 13=mu-...);
- nhits: number of entries to the INTERACTIONS vector (see below) per event

INTERACTIONS vector (one entry per interaction happening at the border between two different regions, to spare CPU time and disk space):
- subdet: number of subdetector in which the interactio happened
- Idp: PDG code of particle interacting (11=e-, -11=e+, 22=gamma, 13=mu-...);
- ipar: parent ID of the track (0 is primary...);
- Itrack: track ID of the track;
- Time: time age of the track [ns];
- xh: X coordinate of the interaction [cm];
- yh: Y coordinate of the interaction [cm];
- zh: Z coordinate of the interaction [cm];
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
- InextStep: is 1 if there will be another step, 0 if the particle is going to die.

Please note that due to Geant4 issues regarding multi core root output, multi thread is currently disabled (can be enabled in mainMCMC.cc)

### CHANGE-LOG
2017.09.11 Modified by collamaf (francesco.collamati@roma1.infn.it)
- added Cerenkov absorber (with generic dimensions)
- created README file
- added MuonBeamFlag

2017.09.12 by collamaf
- fixed subdet table to match data
- added magnetic field scaling due to actual current

2017.10.19 by collamaf
- added global flag (ElectronBeamFlag) to generate electrons as primary particle (thus removing the target). To generate a positron beam at the current time it's enought to make false both ElectronBeamFlag and MuonBeamFlag

2017.10.23 by collamaf
- fixed the problem with the magnetic field, that was showing remarkable differences between map and fixed values. It was due to an error in the handling of the ZOffset in GetFieldValue of PurgMagTabulatedField3D.cc (now changed the sign of the offset passed to it by DetectorConstruction.c). Now very good agreement between map and fixed field!

2017.10.24 by collamaf
- added 12-leyer structure for the muon chamber









