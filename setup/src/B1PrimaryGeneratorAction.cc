#include "B1PrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction(B1EventAction* eventAction)
: G4VUserPrimaryGeneratorAction(),
fParticleGun(0),
fEnvelopeBox(0),
evtPrimAction(eventAction)
{
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e+");
	fParticleGun->SetParticleDefinition(particle);
}


B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
	delete fParticleGun;
}


void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// COLLIMATOR and SHOOT
	// ====================
	
	G4double x0,y0,z0;
	//  G4double cut = 2.*mm; // collimator dimension
	G4double sizeX = 10*mm;
	G4double sizeY = 10*mm;
	//-- Gaussian shoot
	//   --------------
	//  while (1>0){ //
	//  x0 = G4RandGauss::shoot(0.,sizeX);
	//  y0 = G4RandGauss::shoot(0.,sizeY);
	//    if ( abs(x0)<cut && abs(y0)<cut ) break;
	//    }
	z0 = -1.e-5*mm;
	
	
	G4bool SimpleFlag=false;
	
	G4double p_smear;
	G4double EnergySpread;
	
	if (SimpleFlag) {
		p_smear = 0;
		EnergySpread = 0.0;
		sizeX=0;
		sizeY=0;
	} else 	{
		p_smear = 170.e-6;
		EnergySpread = 0.01;
		sizeX = 20*mm;
		sizeY = 20*mm;
		
	}
	
	//-- Uniform shoot
	//----------------

	x0 = sizeX * (G4UniformRand()-0.5);
	y0 = sizeY * (G4UniformRand()-0.5);
	
	fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0)); // GUN POSITION
	

	//-- ENERGY and ANGULAR SPREAD
	//   =========================

	G4double px_smear = G4RandGauss::shoot(0.,p_smear);
	G4double py_smear = G4RandGauss::shoot(0.,p_smear);
	//  G4double px_smear = p_smear*(G4UniformRand()-0.5);
	//  G4double py_smear = p_smear*(G4UniformRand()-0.5);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px_smear,py_smear,1-px_smear*px_smear-py_smear*py_smear));
	// DA MATTIA DIVERGENZA ~140urad
	// no energy spread
	G4double Energy0 = 45.*GeV;
//	G4double EnergySpread = 0.0; //0.01
	G4double Energy = G4RandGauss::shoot(Energy0, Energy0*EnergySpread);
	fParticleGun->SetParticleEnergy(Energy);
	
	//Save Primary Beam Info
	evtPrimAction->SetBeamX(x0);
	evtPrimAction->SetBeamY(y0);
	evtPrimAction->SetBeamZ(z0);
	evtPrimAction->SetBeamCX(px_smear);
	evtPrimAction->SetBeamCY(py_smear);
	evtPrimAction->SetBeamCZ(sqrt(1-px_smear*px_smear-py_smear*py_smear));   //corrected by collamaf
	evtPrimAction->SetBeamEne(Energy/GeV);
	
	
	/*
	 -- energy spread:
	 G4double Energy = 45*GeV;
	 G4double sigmaE = 0.01*Energy;
	 Energy = G4RandGauss::shoot(Energy,sigmaE);
	 fParticleGun->SetParticleEnergy(Energy);
  */
	fParticleGun->GeneratePrimaryVertex(anEvent);
}


