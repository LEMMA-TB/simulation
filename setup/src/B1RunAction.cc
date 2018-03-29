#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1Run.hh"
#include "G4AccumulableManager.hh"
#include "HistoManager.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "time.h"
#include <sstream>

B1RunAction::B1RunAction()
: G4UserRunAction()
{}

B1RunAction::~B1RunAction(){}


G4Run* B1RunAction::GenerateRun(){
	return new B1Run;
}


void B1RunAction::BeginOfRunAction(const G4Run*){
	//inform the runManager to save random number seed
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);
	
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Reset();
	
	
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	//analysisManager->OpenFile("pippone.root");
	//analysisManager->SetVerboseLevel(1);
	//analysisManager->SetFileName("mypippo");
	
	G4long number = time(NULL);
	std::ostringstream oss;
	oss << number;
	G4String filename = "LemmaMC";
//	filename += oss.str();
	filename += ".root";
	
	analysisManager->OpenFile(filename);
	analysisManager->CreateNtuple("LEMMA", "LemmaMCNtuple");
	/*
	analysisManager->CreateNtupleDColumn("BeamX");   //0
	analysisManager->CreateNtupleDColumn("BeamY");   //1
	analysisManager->CreateNtupleDColumn("BeamZ");   //2
	analysisManager->CreateNtupleDColumn("BeamCX");   //3
	analysisManager->CreateNtupleDColumn("BeamCY");   //4
	analysisManager->CreateNtupleDColumn("BeamCZ");   //5
	analysisManager->CreateNtupleDColumn("BeamEne");   //6
	analysisManager->CreateNtupleDColumn("BeamPart");   //7
*/
	analysisManager->CreateNtupleDColumn("BeamX", RunVectorBeamX);   //0
	analysisManager->CreateNtupleDColumn("BeamY", RunVectorBeamY);   //1
	analysisManager->CreateNtupleDColumn("BeamZ", RunVectorBeamZ);   //2
	analysisManager->CreateNtupleDColumn("BeamCX", RunVectorBeamCX);   //3
	analysisManager->CreateNtupleDColumn("BeamCY", RunVectorBeamCY);   //4
	analysisManager->CreateNtupleDColumn("BeamCZ", RunVectorBeamCZ);   //5
	analysisManager->CreateNtupleDColumn("BeamEne", RunVectorBeamEne);   //6
	analysisManager->CreateNtupleDColumn("BeamPart", RunVectorBeamPart);   //7
	
	analysisManager->CreateNtupleDColumn("nhits");   //8

	
	analysisManager->CreateNtupleDColumn(0,"subdet", RunVectorSubdet);
	analysisManager->CreateNtupleDColumn(0,"Idp", RunVectorIdp);
	analysisManager->CreateNtupleDColumn(0,"Ipar", RunVectorIpar);
	analysisManager->CreateNtupleDColumn(0,"itrack", RunVectorItrack);
	analysisManager->CreateNtupleDColumn(0,"Time", RunVectorTime);
	analysisManager->CreateNtupleDColumn(0,"xh", RunVectorX);
	analysisManager->CreateNtupleDColumn(0,"yh", RunVectorY);
	analysisManager->CreateNtupleDColumn(0,"zh", RunVectorZ);
	analysisManager->CreateNtupleDColumn(0,"P", RunVectorP);
	analysisManager->CreateNtupleDColumn(0,"PX", RunVectorPX);
	analysisManager->CreateNtupleDColumn(0,"PY", RunVectorPY);
	analysisManager->CreateNtupleDColumn(0,"PZ", RunVectorPZ);
	analysisManager->CreateNtupleDColumn(0,"VertexX", RunVectorVertexX);
	analysisManager->CreateNtupleDColumn(0,"VertexY", RunVectorVertexY);
	analysisManager->CreateNtupleDColumn(0,"VertexZ", RunVectorVertexZ);
	analysisManager->CreateNtupleDColumn(0,"Kinev", RunVectorKinev);
	analysisManager->CreateNtupleDColumn(0,"PXvdir", RunVectorPXvdir);
	analysisManager->CreateNtupleDColumn(0,"PYvdir", RunVectorPYvdir);
	analysisManager->CreateNtupleDColumn(0,"PZvdir", RunVectorPZvdir);
	analysisManager->CreateNtupleDColumn(0,"Iev", RunVectorIev);
	analysisManager->CreateNtupleDColumn(0,"Step", RunVectorStep);
	analysisManager->CreateNtupleDColumn(0,"InextStep", RunVectorInextStep);
	analysisManager->CreateNtupleDColumn(0,"CopyNb", RunVectorCopyNb);

	analysisManager->CreateNtupleDColumn("DEVAEneTot");   //32

	//added on 2018.02.12 by collamaf to reproduce Data calo info: one vector per detector
	analysisManager->CreateNtupleDColumn(0,"Deva_PulseHeight", RunVectorDEVADepo);
	analysisManager->CreateNtupleDColumn("Cerenkov_DepEneTot");   //34

	analysisManager->CreateNtupleIColumn(0,"Cerenkov_PulseHeight", RunVectorCerenkovDepoOpt);
	analysisManager->CreateNtupleDColumn(0,"Cerenkov_DepEne", RunVectorCerenkovDepo);
	analysisManager->CreateNtupleIColumn("PbGlass_PulseHeight");   //37
	analysisManager->CreateNtupleDColumn("PbGlass_DepEne");   //38

	
	//added on 15.12.2017 @ Padova to compare with data analysis of enetring points in DEVA
#if 1
	analysisManager->CreateNtupleDColumn(0,"DEVAInX", RunVectorDEVAInX);
	analysisManager->CreateNtupleDColumn(0,"DEVAInY", RunVectorDEVAInY);
	analysisManager->CreateNtupleDColumn(0,"DEVAInZ", RunVectorDEVAInZ);
#endif
//	analysisManager->CreateNtupleDColumn(0,"nhits", RunVectorNHits);
//	analysisManager->CreateNtupleDColumn(0,"itrack", RunVectorItrack);
	
	analysisManager->CreateNtupleDColumn(0,"Scint72DepEne", RunVectorScint72DepEne);
	analysisManager->CreateNtupleDColumn(0,"Scint74DepEne", RunVectorScint74DepEne);

	/*
  analysisManager->CreateNtupleIColumn("subdet");
  analysisManager->CreateNtupleIColumn("idp");
  analysisManager->CreateNtupleIColumn("ipar");
  analysisManager->CreateNtupleIColumn("itrack");
  analysisManager->CreateNtupleDColumn("time");
  analysisManager->CreateNtupleDColumn("xh");
  analysisManager->CreateNtupleDColumn("yh");
  analysisManager->CreateNtupleDColumn("zh");
  analysisManager->CreateNtupleDColumn("p");
  analysisManager->CreateNtupleDColumn("pxh");
  analysisManager->CreateNtupleDColumn("pyh");
  analysisManager->CreateNtupleDColumn("pzh");
  analysisManager->CreateNtupleDColumn("xv");
  analysisManager->CreateNtupleDColumn("yv");
  analysisManager->CreateNtupleDColumn("zv");
  analysisManager->CreateNtupleDColumn("kinev");
  analysisManager->CreateNtupleDColumn("pxvdir");
  analysisManager->CreateNtupleDColumn("pyvdir");
  analysisManager->CreateNtupleDColumn("pzvdir");
  analysisManager->CreateNtupleIColumn("pro");
  analysisManager->CreateNtupleIColumn("iev");
  analysisManager->CreateNtupleIColumn("istep");
  analysisManager->CreateNtupleIColumn("inextstep");
	 */
	analysisManager->FinishNtuple();
	// Creating histograms
	analysisManager->CreateH1("gamma-gamma","Energy",10,0.,45000.); // id=0 <=== !!!
}

void B1RunAction::EndOfRunAction(const G4Run* run){
	
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;
	
	//save histograms
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
	
}

