#define AnaLEMMA_cxx
#include "AnaLEMMA.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#define ENEMIN 0
#define ENEMAX 50
#define ENEBW 0.1

#define ZMIN 0
#define ZMAX 3000
#define ZBW 10

#define NPART 5
#define NDET 17

void AnaLEMMA::Loop()
{
	// Root Macro to analyze MC simulation of LEMMA TestBeam
	// It reads both single .root file or multiple .root files in chain
	// (for now filenames are hardcoded in .h)
	// It generates several histos for Beam properties
	// interactions of different particles in different detectors
	//
	//
	//
	
	
	if (fChain == 0) return;
	int ii=0, jj=0;
	
	//	int ParticlesId[NPART]={
	std::vector<double>ParticlesId={
		-11, //e+
		11, //e-
		22, //gamma
		-13, //mu+
		13 //mu-
	};
	
	TString ParticlesName[NPART]={
		"Pos",
		"Ele",
		"Phot",
		"MuP",
		"MuM"
	};
	
	std::vector<int>DetectorId={
		//		int DetectorId[NDET]={
		10,
		20,
		25,
		30,
		40,
		50,
		51,
		55,
		56,
		70,
		72,
		74,
		76,
		77,
		78,
		79,
		80
	};
	
	std::vector<double>DetectorCenterX={
		0,
		0,
		0,
		0,
		0,
		-10.1,
		10.1,
		-18.1,
		18.1,
		0,
		18.1,
		-18.1,
		46, //DEVA TBC
		46,
		0,
		-60,
		-60
	};
	
	std::vector<double>DetectorSizeXY={ //cm
		2,
		2,
		2,
		2,
		10,
		10,
		10,
		10,
		10,
		255,
		10,
		10,
		30, //DEVA TBC
		40,
		13,
		40,
		30
	};
	
	double XYBinW=0.05; //cm
	
	
	int DetectorPosition;
	int ParticlePosition;
	
	
	//	cout<<"pos= "<<pos<<endl;
	TDirectory* DirHistoSingleDet[NDET];
	
	TH1F* EneBeam=new TH1F("EneBeam","Energy of primary beam particles; E [GeV]", (ENEMAX-ENEMIN)/ENEBW, ENEMIN, ENEMAX);
	TH1F* PartBeam=new TH1F("PartBeam","ParticleID of primary beam particles; E [GeV]", 100, -50.5, 49.5);

	
	TH1F* CosZBeam=new TH1F("CosZBeam","CosZ of primary beam particles; CosZ", 100, 1, -1);
	TH2F* XYBeam=new TH2F("XYBeam","X-Y position of primary particles; X [cm]; Y [cm]", 100, -20, 20, 100, -20, 20);
	
	TH1F* EneMuP=new TH1F("EneMuP","Mu + Energy", (ENEMAX-ENEMIN)/ENEBW, ENEMIN, ENEMAX);
	TH1F* EneMuM=new TH1F("EneMuM","Mu - Energy", (ENEMAX-ENEMIN)/ENEBW, ENEMIN, ENEMAX);
	
	TH1F* Zeta[NPART];
	TH2F* ZetaX[NPART];
	TH1F* Subdet[NPART];
	
	TH2F* XYDet[NDET][NPART];
	
	for (ii=0; ii<NPART; ii++) {
		Zeta[ii]=new TH1F(Form("Z%s",ParticlesName[ii].Data()),Form("Z position of interactions for %s; Z [cm]", ParticlesName[ii].Data()), (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
		ZetaX[ii]=new TH2F(Form("ZX%s",ParticlesName[ii].Data()),Form("Z-X position of interactions for %s; Z [cm]; X [cm]", ParticlesName[ii].Data()), (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX, 300, 0, -100);
		Subdet[ii]=new TH1F(Form("Det%s",ParticlesName[ii].Data()),Form("Subdetector of interactions of for %s", ParticlesName[ii].Data()), 100, 0.5, 100.5);
		
		for (jj=0; jj<NDET; jj++) {
			if (ii==0)			DirHistoSingleDet[jj]=outputfile->mkdir(Form("HistoSingleDet%d",DetectorId[jj]));
			XYDet[jj][ii]=new TH2F(Form("XYDet%d%s", DetectorId[jj],ParticlesName[ii].Data()), Form("X-Y coordinates on det %d for %s", DetectorId[jj],ParticlesName[ii].Data()),
														 DetectorSizeXY[jj]/XYBinW, DetectorCenterX[jj]-DetectorSizeXY[jj]/2., DetectorCenterX[jj]+DetectorSizeXY[jj]/2., DetectorSizeXY[jj]/XYBinW, -DetectorSizeXY[jj]/2.,DetectorSizeXY[jj]/2.);
			XYDet[jj][ii]->SetMarkerColor(ii+1);
			
			if (ii==0) cout<<"jj= "<<jj<<" NBIN= "<<DetectorSizeXY[jj]/XYBinW<<" Xmin="<<DetectorCenterX[jj]-DetectorSizeXY[jj]/2.<<" Xmax="<<DetectorCenterX[jj]+DetectorSizeXY[jj]/2. <<endl;
		}
		
	}
	
	
//	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nentries = fChain->GetEntries();
	cout<<"Numero Entries totali: "<<nentries<<endl;
//	nentries=1e4; //quick run for checks
	
	Long64_t nbytes = 0, nb = 0;
	nentries/=10;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	
	
		
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
			if (jentry==0) cout<<"##### ANALYSIS OF MC SIMULATION\n PRIMARY PARTICLE GENERATED (11=e-, -11=e+, 13=mu-, -13=m+): "<< BeamPart->at(0)<<" of Energy= "<<(int)(BeamEne->at(0)+0.5) <<" GeV"<<endl;
	
		if (jentry%(nentries/100)==0) cout<<"I am analyzing entry: "<<jentry<<" of "<<nentries<<" - "<< (int)(((double)jentry)/nentries*100 )<<" %"<<endl;


		for (ii=0; ii<BeamEne->size(); ii++) { //ciclo sul vettore "Beam"
			EneBeam->Fill(BeamEne->at(ii));
			CosZBeam->Fill(BeamCZ->at(ii));
			XYBeam->Fill(BeamX->at(ii),BeamY->at(ii));
			PartBeam->Fill(BeamPart->at(ii));
		}
		for (jj=0; jj<subdet->size(); jj++) { //ciclo sul vettore "Interactions"
			
			
			// trovo le posizioni nei rispettivi vettori della particella e del subdet in esame
			ParticlePosition= std::find(ParticlesId.begin(), ParticlesId.end(), Idp->at(jj)) - ParticlesId.begin();
			if (ParticlePosition<5) { //Exclude particles I am not interested in
				DetectorPosition	= std::find(DetectorId.begin(), DetectorId.end(), subdet->at(jj)) - DetectorId.begin();
				
//				cout<<"jj= "<<jj<<" Particella = "<<Idp->at(jj)<<" PosPart="<<ParticlePosition<<" Subdet ="<<subdet->at(jj)<<" PosSubDet="<<DetectorPosition <<endl;
				
				Zeta[ParticlePosition]->Fill(zh->at(jj));
				ZetaX[ParticlePosition]->Fill(zh->at(jj),xh->at(jj));
				Subdet[ParticlePosition]->Fill(subdet->at(jj));
				XYDet[DetectorPosition][ParticlePosition]->Fill(xh->at(jj), yh->at(jj));
			}
		}
		
		
		// if (Cut(ientry) < 0) continue;
	}
	
	DirHistoBeam->cd();
	EneBeam->Write();
	CosZBeam->Write();
	XYBeam->Write();
	PartBeam->Write();
	outputfile->cd();
	
	for (ii=0; ii<NPART; ii++) {
		DirHistoZ->cd();
		Zeta[ii]->Write();
		DirHistoZX->cd();
		ZetaX[ii]->Write();
		DirHistoDet->cd();
		Subdet[ii]->Write();
		for (jj=0; jj<NDET; jj++) {
			DirHistoSingleDet[jj]->cd();
			XYDet[jj][ii]->Write();
		}
		outputfile->cd();
	}
	
}
