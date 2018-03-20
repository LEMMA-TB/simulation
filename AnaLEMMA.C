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

void AnaLEMMA::Loop()
{
	//
	//
	//
	//
	//
	//
	//
	//
	

	if (fChain == 0) return;
	int ii=0, jj=0;
	
	int ParticlesId[NPART]={
		-11,
		11,
		22,
		-13,
		13
		
	};
	
	TString ParticlesName[NPART]={
		"Pos",
		"Ele",
		"Phot",
		"MuP",
		"MuM"
	};
	
	TH1F* EneBeam=new TH1F("EneBeam","Energy of primary beam particles; E [GeV]", (ENEMAX-ENEMIN)/ENEBW, ENEMIN, ENEMAX);


	TH1F* CosZBeam=new TH1F("CosZBeam","CosZ of primary beam particles; CosZ", 100, 1, -1);
	TH2F* XYBeam=new TH2F("XYBeam","X-Y position of primary particles; X [cm]; Y [cm]", 100, -20, 20, 100, -20, 20);
	
	TH1F* EneMuP=new TH1F("EneMuP","Mu + Energy", (ENEMAX-ENEMIN)/ENEBW, ENEMIN, ENEMAX);
	TH1F* EneMuM=new TH1F("EneMuM","Mu - Energy", (ENEMAX-ENEMIN)/ENEBW, ENEMIN, ENEMAX);
	
	TH1F* Zeta[5];
	TH2F* ZetaX[5];
	TH1F* Subdet[5];
	
	for (ii=0; ii<NPART; ii++) {
		Zeta[ii]=new TH1F(Form("Z%s",ParticlesName[ii].Data()),Form("Z position of interactions for %s; Z [cm]", ParticlesName[ii].Data()), (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
		ZetaX[ii]=new TH2F(Form("ZX%s",ParticlesName[ii].Data()),Form("Z-X position of interactions for %s; Z [cm]; X [cm]", ParticlesName[ii].Data()), (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX, 300, 0, -100);
		Subdet[ii]=new TH1F(Form("Det%s",ParticlesName[ii].Data()),Form("Subdetector of interactions of for %s", ParticlesName[ii].Data()), 100, 0.5, 100.5);
	}
	/*
	Zeta[0]=new TH1F("ZPos","Z position of interactions of positrons; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	Zeta[1]=new TH1F("ZEle","Z position of interactions of electrons; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	Zeta[2]=new TH1F("ZPhot","Z position of interactions of photons; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	Zeta[3]=new TH1F("ZMuP","Z position of interactions of mu+; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	Zeta[4]=new TH1F("ZMuM","Z position of interactions of mu-; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);

	
	TH2F* ZetaX[5];
	
	ZetaX[0]=new TH2F("ZXPos","Z position of interactions of positrons; Z [cm]; X [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX, 300, 0, -100);
	ZetaX[1]=new TH2F("ZXEle","Z position of interactions of electrons; Z [cm]; X [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX, 300, 0, -100);
	ZetaX[2]=new TH2F("ZXPhot","Z position of interactions of photons; Z [cm]; X [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX, 300, 0, -100);
	ZetaX[3]=new TH2F("ZXMuP","Z position of interactions of mu+; Z [cm]; X [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX, 300, 0, -100);
	ZetaX[4]=new TH2F("ZXMuM","Z position of interactions of mu-; Z [cm]; X [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX, 300, 0, -100);
	 
	 TH1F* Subdet[5];
	 
	 Subdet[0]=new TH1F("DetPos","Subdetector of interactions of positrons", 100, 0.5, 100.5);
	 Subdet[1]=new TH1F("DetEle","Subdetector of interactions of electrons", 100, 0.5, 100.5);
	 Subdet[2]=new TH1F("DetPhot","Subdetector of interactions of photons", 100, 0.5, 100.5);
	 Subdet[3]=new TH1F("DetMuP","Subdetector of interactions of mu+", 100, 0.5, 100.5);
	 Subdet[4]=new TH1F("DetMuM","Subdetector of interactions of mu-", 100, 0.5, 100.5);
	 
	 
		*/
//	TH2F* XHDet[10][5];
	
//	for (ii=0; ii<10; ii++)
	
	TH2F* XHDet40[5];
	
	XHDet40[0]=new TH2F("XHDet40Pos", "X-H coordinates on det 40 for positrons", 100, -6, 6, 100, -5, 5);
	XHDet40[1]=new TH2F("XHDet40Ele", "X-H coordinates on det 40 for electrons", 100, -6, 6, 100, -5, 5);
	XHDet40[2]=new TH2F("XHDet40Phot", "X-H coordinates on det 40 for photons", 100, -6, 6, 100, -5, 5);
	XHDet40[3]=new TH2F("XHDet40MuP", "X-H coordinates on det 40 for mu +", 100, -6, 6, 100, -5, 5);
	XHDet40[4]=new TH2F("XHDet40MuM", "X-H coordinates on det 40 for mu -", 100, -6, 6, 100, -5, 5);
	XHDet40[0]->SetMarkerColor(kRed);
	XHDet40[1]->SetMarkerColor(kBlue);
	XHDet40[2]->SetMarkerColor(kOrange);
	XHDet40[3]->SetMarkerColor(kGreen+1);
	XHDet40[4]->SetMarkerColor(kAzure);

	/*
	 TH1F* ZPos=new TH1F("ZPos","Z position of interactions of positrons; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	 TH1F* ZEle=new TH1F("ZEle","Z position of interactions of electrons; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	 TH1F* ZPhot=new TH1F("ZPhot","Z position of interactions of photons; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	 TH1F* ZMuP=new TH1F("ZMuP","Z position of interactions of mu+; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	 TH1F* ZMuM=new TH1F("ZMuM","Z position of interactions of mu-; Z [cm]", (ZMAX-ZMIN)/ZBW, ZMIN, ZMAX);
	 
	 */
	
	
	
	
	Long64_t nentries = fChain->GetEntriesFast();
	cout<<nentries<<endl;
	nentries=1e4;
	

	Long64_t nbytes = 0, nb = 0;
//	nentries/=10;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		if (jentry==0) cout<<"##### ANALYSIS OF MC SIMULATION\n PRIMARY PARTICLE GENERATED (11=e-, -11=e+, 13=mu-, -13=m+): "<< BeamPart->at(0)<<" of Energy= "<<(int)(BeamEne->at(0)+0.5) <<" GeV"<<endl;
		
		for (ii=0; ii<BeamEne->size(); ii++) { //ciclo sul vettore "Beam"
			EneBeam->Fill(BeamEne->at(ii));
			CosZBeam->Fill(BeamCZ->at(ii));
			XYBeam->Fill(BeamX->at(ii),BeamY->at(ii));
		}
		
		for (jj=0; jj<subdet->size(); jj++) { //ciclo sul vettore "Interactions"
			if(Idp->at(jj)==11) {
				Zeta[0]->Fill(zh->at(jj));
				ZetaX[0]->Fill(zh->at(jj),xh->at(jj));
				Subdet[0]->Fill(subdet->at(jj));
				if (subdet->at(jj)==40) XHDet40[0]->Fill(xh->at(jj), yh->at(jj));
			}
			if(Idp->at(jj)==-11) {
				Zeta[1]->Fill(zh->at(jj));
				ZetaX[1]->Fill(zh->at(jj),xh->at(jj));
				Subdet[1]->Fill(subdet->at(jj));
				if (subdet->at(jj)==40) XHDet40[1]->Fill(xh->at(jj), yh->at(jj));
			}
			if(Idp->at(jj)==22) {
				Zeta[2]->Fill(zh->at(jj));
				ZetaX[2]->Fill(zh->at(jj),xh->at(jj));
				Subdet[2]->Fill(subdet->at(jj));
				if (subdet->at(jj)==40) XHDet40[2]->Fill(xh->at(jj), yh->at(jj));
			}
			if(Idp->at(jj)==13){
				Zeta[3]->Fill(zh->at(jj));
				ZetaX[3]->Fill(zh->at(jj),xh->at(jj));
				Subdet[3]->Fill(subdet->at(jj));
				if (subdet->at(jj)==40) XHDet40[3]->Fill(xh->at(jj), yh->at(jj));
			}
			if(Idp->at(jj)==-13) {
				Zeta[4]->Fill(zh->at(jj));
				ZetaX[4]->Fill(zh->at(jj),xh->at(jj));
				Subdet[4]->Fill(subdet->at(jj));
				if (subdet->at(jj)==40) XHDet40[4]->Fill(xh->at(jj), yh->at(jj));
			}
		}
		
		
		// if (Cut(ientry) < 0) continue;
	}
	/*
	EneBeam->Draw();
	CosZBeam->Draw();
	XYBeam->Draw();
	*/
	DirHistoBeam->cd();
	EneBeam->Write();
	CosZBeam->Write();
	XYBeam->Write();
	outputfile->cd();
	
	for (ii=0; ii<5; ii++) {
		DirHistoZ->cd();
		Zeta[ii]->Write();
		DirHistoZX->cd();
		ZetaX[ii]->Write();
		DirHistoDet->cd();
		Subdet[ii]->Write();
		outputfile->cd();
		XHDet40[ii]->Write();
	}
	/*
	ZEle->Write();
	ZPos->Write();
	ZPhot->Write();
	ZMuM->Write();
	ZMuP->Write();
	*/
}
