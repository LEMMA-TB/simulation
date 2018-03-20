//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 19 21:59:46 2018 by ROOT version 6.11/02
// from TTree LEMMA/LemmaMCNtuple
// found on file: LemmaMC_Pos45_T_Ff_RealMu.root
//////////////////////////////////////////////////////////

#ifndef AnaLEMMA_h
#define AnaLEMMA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class AnaLEMMA {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<double>  *BeamX;
   vector<double>  *BeamY;
   vector<double>  *BeamZ;
   vector<double>  *BeamCX;
   vector<double>  *BeamCY;
   vector<double>  *BeamCZ;
   vector<double>  *BeamEne;
   vector<double>  *BeamPart;
   Double_t        nhits;
   vector<double>  *subdet;
   vector<double>  *Idp;
   vector<double>  *Ipar;
   vector<double>  *itrack;
   vector<double>  *Time;
   vector<double>  *xh;
   vector<double>  *yh;
   vector<double>  *zh;
   vector<double>  *P;
   vector<double>  *PX;
   vector<double>  *PY;
   vector<double>  *PZ;
   vector<double>  *VertexX;
   vector<double>  *VertexY;
   vector<double>  *VertexZ;
   vector<double>  *Kinev;
   vector<double>  *PXvdir;
   vector<double>  *PYvdir;
   vector<double>  *PZvdir;
   vector<double>  *Iev;
   vector<double>  *Step;
   vector<double>  *InextStep;
   vector<double>  *CopyNb;
   Double_t        DEVAEneTot;
   vector<double>  *Deva_PulseHeight;
   Double_t        Cerenkov_DepEneTot;
   vector<int>     *Cerenkov_PulseHeight;
   vector<double>  *Cerenkov_DepEne;
   Int_t           PbGlass_PulseHeight;
   Double_t        PbGlass_DepEne;
   vector<double>  *DEVAInX;
   vector<double>  *DEVAInY;
   vector<double>  *DEVAInZ;

   // List of branches
   TBranch        *b_BeamX;   //!
   TBranch        *b_BeamY;   //!
   TBranch        *b_BeamZ;   //!
   TBranch        *b_BeamCX;   //!
   TBranch        *b_BeamCY;   //!
   TBranch        *b_BeamCZ;   //!
   TBranch        *b_BeamEne;   //!
   TBranch        *b_BeamPart;   //!
   TBranch        *b_nhits;   //!
   TBranch        *b_subdet;   //!
   TBranch        *b_Idp;   //!
   TBranch        *b_Ipar;   //!
   TBranch        *b_itrack;   //!
   TBranch        *b_Time;   //!
   TBranch        *b_xh;   //!
   TBranch        *b_yh;   //!
   TBranch        *b_zh;   //!
   TBranch        *b_P;   //!
   TBranch        *b_PX;   //!
   TBranch        *b_PY;   //!
   TBranch        *b_PZ;   //!
   TBranch        *b_VertexX;   //!
   TBranch        *b_VertexY;   //!
   TBranch        *b_VertexZ;   //!
   TBranch        *b_Kinev;   //!
   TBranch        *b_PXvdir;   //!
   TBranch        *b_PYvdir;   //!
   TBranch        *b_PZvdir;   //!
   TBranch        *b_Iev;   //!
   TBranch        *b_Step;   //!
   TBranch        *b_InextStep;   //!
   TBranch        *b_CopyNb;   //!
   TBranch        *b_DEVAEneTot;   //!
   TBranch        *b_Deva_PulseHeight;   //!
   TBranch        *b_Cerenkov_DepEneTot;   //!
   TBranch        *b_Cerenkov_PulseHeight;   //!
   TBranch        *b_Cerenkov_DepEne;   //!
   TBranch        *b_PbGlass_PulseHeight;   //!
   TBranch        *b_PbGlass_DepEne;   //!
   TBranch        *b_DEVAInX;   //!
   TBranch        *b_DEVAInY;   //!
   TBranch        *b_DEVAInZ;   //!

   AnaLEMMA(TTree *tree=0);
   virtual ~AnaLEMMA();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
	TFile* outputfile;
	TDirectory* DirHistoZ;
	TDirectory* DirHistoZX;
	TDirectory* DirHistoDet;
	TDirectory* DirHistoBeam;
};

#endif

#ifdef AnaLEMMA_cxx
AnaLEMMA::AnaLEMMA(TTree *tree) : fChain(0)
{
	// if parameter tree is not specified (or zero), connect the file
	// used to generate this class and read the Tree.
	if (tree == 0) {
		
#ifdef SINGLE_TREE
		// The following code should be used if you want this class to access
		// a single tree instead of a chain
		TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
		if (!f || !f->IsOpen()) {
			f = new TFile("Memory Directory");
		}
		f->GetObject("LEMMA",tree);
		
#else // SINGLE_TREE
		
		// The following code should be used if you want this class to access a chain
		// of trees.
		TChain * chain = new TChain("LEMMA","");
		
		chain->Add("LemmaMC_Pos45_T_Ff_RealMu.root/LEMMA");
		tree = chain;
#endif // SINGLE_TREE
		
		outputfile=new TFile(Form("%s_out.root", "LEMMA"), "RECREATE");
		DirHistoBeam=outputfile->mkdir("HistoBeam");
		DirHistoZ = outputfile->mkdir("HistoZ");
		DirHistoZX = outputfile->mkdir("HistoZX");
		DirHistoDet=outputfile->mkdir("HistoSubdet");

	}
	Init(tree);
}





AnaLEMMA::~AnaLEMMA()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnaLEMMA::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnaLEMMA::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnaLEMMA::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   BeamX = 0;
   BeamY = 0;
   BeamZ = 0;
   BeamCX = 0;
   BeamCY = 0;
   BeamCZ = 0;
   BeamEne = 0;
   BeamPart = 0;
   subdet = 0;
   Idp = 0;
   Ipar = 0;
   itrack = 0;
   Time = 0;
   xh = 0;
   yh = 0;
   zh = 0;
   P = 0;
   PX = 0;
   PY = 0;
   PZ = 0;
   VertexX = 0;
   VertexY = 0;
   VertexZ = 0;
   Kinev = 0;
   PXvdir = 0;
   PYvdir = 0;
   PZvdir = 0;
   Iev = 0;
   Step = 0;
   InextStep = 0;
   CopyNb = 0;
   Deva_PulseHeight = 0;
   Cerenkov_PulseHeight = 0;
   Cerenkov_DepEne = 0;
   DEVAInX = 0;
   DEVAInY = 0;
   DEVAInZ = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("BeamX", &BeamX, &b_BeamX);
   fChain->SetBranchAddress("BeamY", &BeamY, &b_BeamY);
   fChain->SetBranchAddress("BeamZ", &BeamZ, &b_BeamZ);
   fChain->SetBranchAddress("BeamCX", &BeamCX, &b_BeamCX);
   fChain->SetBranchAddress("BeamCY", &BeamCY, &b_BeamCY);
   fChain->SetBranchAddress("BeamCZ", &BeamCZ, &b_BeamCZ);
   fChain->SetBranchAddress("BeamEne", &BeamEne, &b_BeamEne);
   fChain->SetBranchAddress("BeamPart", &BeamPart, &b_BeamPart);
   fChain->SetBranchAddress("nhits", &nhits, &b_nhits);
   fChain->SetBranchAddress("subdet", &subdet, &b_subdet);
   fChain->SetBranchAddress("Idp", &Idp, &b_Idp);
   fChain->SetBranchAddress("Ipar", &Ipar, &b_Ipar);
   fChain->SetBranchAddress("itrack", &itrack, &b_itrack);
   fChain->SetBranchAddress("Time", &Time, &b_Time);
   fChain->SetBranchAddress("xh", &xh, &b_xh);
   fChain->SetBranchAddress("yh", &yh, &b_yh);
   fChain->SetBranchAddress("zh", &zh, &b_zh);
   fChain->SetBranchAddress("P", &P, &b_P);
   fChain->SetBranchAddress("PX", &PX, &b_PX);
   fChain->SetBranchAddress("PY", &PY, &b_PY);
   fChain->SetBranchAddress("PZ", &PZ, &b_PZ);
   fChain->SetBranchAddress("VertexX", &VertexX, &b_VertexX);
   fChain->SetBranchAddress("VertexY", &VertexY, &b_VertexY);
   fChain->SetBranchAddress("VertexZ", &VertexZ, &b_VertexZ);
   fChain->SetBranchAddress("Kinev", &Kinev, &b_Kinev);
   fChain->SetBranchAddress("PXvdir", &PXvdir, &b_PXvdir);
   fChain->SetBranchAddress("PYvdir", &PYvdir, &b_PYvdir);
   fChain->SetBranchAddress("PZvdir", &PZvdir, &b_PZvdir);
   fChain->SetBranchAddress("Iev", &Iev, &b_Iev);
   fChain->SetBranchAddress("Step", &Step, &b_Step);
   fChain->SetBranchAddress("InextStep", &InextStep, &b_InextStep);
   fChain->SetBranchAddress("CopyNb", &CopyNb, &b_CopyNb);
   fChain->SetBranchAddress("DEVAEneTot", &DEVAEneTot, &b_DEVAEneTot);
   fChain->SetBranchAddress("Deva_PulseHeight", &Deva_PulseHeight, &b_Deva_PulseHeight);
   fChain->SetBranchAddress("Cerenkov_DepEneTot", &Cerenkov_DepEneTot, &b_Cerenkov_DepEneTot);
   fChain->SetBranchAddress("Cerenkov_PulseHeight", &Cerenkov_PulseHeight, &b_Cerenkov_PulseHeight);
   fChain->SetBranchAddress("Cerenkov_DepEne", &Cerenkov_DepEne, &b_Cerenkov_DepEne);
   fChain->SetBranchAddress("PbGlass_PulseHeight", &PbGlass_PulseHeight, &b_PbGlass_PulseHeight);
   fChain->SetBranchAddress("PbGlass_DepEne", &PbGlass_DepEne, &b_PbGlass_DepEne);
   fChain->SetBranchAddress("DEVAInX", &DEVAInX, &b_DEVAInX);
   fChain->SetBranchAddress("DEVAInY", &DEVAInY, &b_DEVAInY);
   fChain->SetBranchAddress("DEVAInZ", &DEVAInZ, &b_DEVAInZ);
   Notify();
}

Bool_t AnaLEMMA::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnaLEMMA::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnaLEMMA::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AnaLEMMA_cxx
