# simulation
Geant4 simulation of LEMMA test beam, done @CERN on ~August 2017.

### HOW TO RUN
- You have to have Geant4 up and running
- type:
cd build
cmake -DGeant4_DIR=$G4INSTALL ../setup/
make
./mainMCMC
./mainMCMC ../setup/run1.mac

Please note that if any changes are done to ../setup/*.mac you need to cmake -XXX again
### GEOMETRY
The geometry is the one of the final configuration

### PRIMARY PARTICLE
The simulation is set to simulate primary positrons starting at the origin (0,0,0). It is possible to simulate a realistic beam (energy, angular and position spread), but there is a flag (SimpleFlag) in B1PrimaryGeneratorAction.cc to select the simple case of ideal beam.
There are flags in the mainMCMC.cc to generate other particles (electrons, muons) and other energies.

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

Please note that due to Geant4 issues regarding multi core root output, multi thread is currently disabled (can be enabled in mainMCMC.cc, but creates N-root files named LemmaMC_t?.root)

### TO MERGE MULTIPLE ROOT OUTPUT FILES:
TChain * chain = new TChain("LEMMA")
chain->Add("LemmaMC_t*.root")
TFile *file = TFile::Open("LemmaMC_Pos22_NoT_Ff.root","RECREATE");
chain->CloneTree(-1,"fast");
file->Write();

### FILE NAMES FOR OUTPUT
TFile *file = TFile::Open("LemmaMC_Tot45PosT_bias.root","RECREATE");
TFile *file = TFile::Open("LemmaMC_Tot22PosNoT_simple.root","RECREATE");

TFile *file = TFile::Open("LemmaMC_Pos22s_NoT_Ff_calo.root","RECREATE");  //Fixed field  flipped
TFile *file = TFile::Open("LemmaMC_Pos22_NoT_M_calo.root","RECREATE");    //Map field not flipped



### OR TO READ TOGETHER WITHOUT MERGING

TChain * chain = new TChain("LEMMA")
chain->Add("LemmaMC_t*.root")
LEMMA->Draw("DEVAEneTot")

### COMANDI VARI
LEMMA->Draw("DEVAEneTot")
LEMMA->Draw("Kinev:CopyNb","subdet==77&&Idp==-11","lego")


#############################
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
- moved all flags to mainMCMC.cc

2017.10.27 by collamaf
- added exact structure of DEVA calorimeter (12 plastic scintillator tiles and 11 lead absorbers)
- first approach to scoring of deposited energy into DEVA. For now simply saving total energy deposited in each of 12 layers using 12 (+1 total) entries in the root file

2017.10.28 by collamaf
- expanded scoring of energy depositon into DEVA, dividing for Total, Photons, Electrons and Positrons contribution. However, probably this division does not have much sense in MC.. have to think about it
- reduced number of reading channel in DEVA from 12 (as layers) to 6 (as in experiment)
- added a flag to the main to decide if to score calorimeter info

2017.10.30 by collamaf
- added scoring of CopyNb to know in which layer of DEVA the interaction happens
- corrected DEVA container material (was full of iron!)

2017.11.28 by collamaf
- new system of naming for total .root file (not the one(s) produced by Geant, but the ones done with root)

2017.11.29 by collamaf
- fixed a lot of X and Z positions, due to found error in Z placing of T6 (was moved towards target ~1m, and thus also the chamber position was wrong)

2017.12.15 by collamaf (@Padova)
- added additional scoring of XYZ of particles entering DEVA to compare with data analysis

2017.12.29 by collamaf
- added possibility to use external generator for primary events: there are now 2 new flags in mainMCMC.cc (ExtSourceFlagBha and ExtSourceFlagMu): if true default settings for source are overrided
- moved from PrimaryAction to StackingAction the lines to save on the root file info on primary particles, in order to be able to do so also for externally generated particels
- changed structure in the root outpit file to house more than 1 primary per event: now BeamX etc are vectors
- at the current stage the origin of primary external particles is decided with the generator (e.g. they are all generated at the center of the target), but we will work on it




