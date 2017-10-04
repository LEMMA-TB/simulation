/************************************************************
 *                  Vector_To_Array.C                       *
 * **********************************************************
 *                                                          *
 * Macro to convert vectors in the MC simulation root file  *
 * in arrays of defined dimension.                          *
 *                                                          *
 *                         !!!!                             *
 * You can loose information if vector size is bigger than  *
 * the chosen array size.                                   *
 *                                                          *
 * **********************************************************/

void Vector_To_Array( TString file_input_name, TString file_output_name ) {
    
    gROOT->ProcessLine("#include <vector>");

    //--- open input tree
    
    TFile *file_input = new TFile( file_input_name );
    TTree *tree_input = ( TTree* )file_input->Get( "LEMMA" );
    
    Double_t BeamX;                 tree_input->SetBranchAddress( "BeamX",     &BeamX     );
    Double_t BeamY;                 tree_input->SetBranchAddress( "BeamY",     &BeamY     );
    Double_t BeamZ;                 tree_input->SetBranchAddress( "BeamZ",     &BeamZ     );
    Double_t BeamCX;                tree_input->SetBranchAddress( "BeamCX",    &BeamCX    );
    Double_t BeamCY;                tree_input->SetBranchAddress( "BeamCY",    &BeamCY    );
    Double_t BeamCZ;                tree_input->SetBranchAddress( "BeamCZ",    &BeamCZ    );
    Double_t BeamEne;               tree_input->SetBranchAddress( "BeamEne",   &BeamEne   );
    Double_t BeamPart;              tree_input->SetBranchAddress( "BeamPart",  &BeamPart  );
    Double_t nhits;                 tree_input->SetBranchAddress( "nhits",     &nhits     );
    vector<double> *subdet=0;       tree_input->SetBranchAddress( "subdet",    &subdet    );
    vector<double> *Idp=0;          tree_input->SetBranchAddress( "Idp",       &Idp       );
    vector<double> *Ipar=0;         tree_input->SetBranchAddress( "Ipar",      &Ipar      );
    vector<double> *itrack=0;       tree_input->SetBranchAddress( "itrack",    &itrack    );
    vector<double> *Time=0;         tree_input->SetBranchAddress( "Time",      &Time      );
    vector<double> *xh=0;           tree_input->SetBranchAddress( "xh",        &xh        );
    vector<double> *yh=0;           tree_input->SetBranchAddress( "yh",        &yh        );
    vector<double> *zh=0;           tree_input->SetBranchAddress( "zh",        &zh        );
    vector<double> *P=0;            tree_input->SetBranchAddress( "P",         &P         );
    vector<double> *PX=0;           tree_input->SetBranchAddress( "PX",        &PX        );
    vector<double> *PY=0;           tree_input->SetBranchAddress( "PY",        &PY        );
    vector<double> *PZ=0;           tree_input->SetBranchAddress( "PZ",        &PZ        );
    vector<double> *VertexX=0;      tree_input->SetBranchAddress( "VertexX",   &VertexX   );
    vector<double> *VertexY=0;      tree_input->SetBranchAddress( "VertexY",   &VertexY   );
    vector<double> *VertexZ=0;      tree_input->SetBranchAddress( "VertexZ",   &VertexZ   );
    vector<double> *Kinev=0;        tree_input->SetBranchAddress( "Kinev",     &Kinev     );
    vector<double> *PXvdir=0;       tree_input->SetBranchAddress( "PXvdir",    &PXvdir    );
    vector<double> *PYvdir=0;       tree_input->SetBranchAddress( "PYvdir",    &PYvdir    );
    vector<double> *PZvdir=0;       tree_input->SetBranchAddress( "PZvdir",    &PZvdir    );
    vector<double> *Iev=0;          tree_input->SetBranchAddress( "Iev",       &Iev       );
    vector<double> *Step=0;         tree_input->SetBranchAddress( "Step",      &Step      );
    vector<double> *InextStep=0;    tree_input->SetBranchAddress( "InextStep", &InextStep );
    
    //--- define output tree
    
    TFile *file_output = new TFile( file_output_name, "RECREATE" );
    TTree *tree_output = new TTree( "LEMMA", "LEMMA MC simulation" );
    
    ///////  ARRAY SIZE  ///////
    const Int_t nMaxHits = 5000;
    ////////////////////////////
    
    Double_t BeamX_new;                            tree_output->Branch( "BeamX",     &BeamX_new,    "BeamX/D"                                      );
    Double_t BeamY_new;                            tree_output->Branch( "BeamY",     &BeamY_new,    "BeamY/D"                                      );
    Double_t BeamZ_new;                            tree_output->Branch( "BeamZ",     &BeamZ_new,    "BeamZ/D"                                      );
    Double_t BeamCX_new;                           tree_output->Branch( "BeamCX",    &BeamCX_new,   "BeamCX/D"                                     );
    Double_t BeamCY_new;                           tree_output->Branch( "BeamCY",    &BeamCY_new,   "BeamCY/D"                                     );
    Double_t BeamCZ_new;                           tree_output->Branch( "BeamCZ",    &BeamCZ_new,   "BeamCZ/D"                                     );
    Double_t BeamEne_new;                          tree_output->Branch( "BeamEne",   &BeamEne_new,  "BeamEne/D"                                    );
    Double_t BeamPart_new;                         tree_output->Branch( "BeamPart",  &BeamPart_new, "BeamPart/D"                                   );
    Double_t nhits_new;                            tree_output->Branch( "nhits",     &nhits_new,    "nhits/D"                                      );
    Double_t subdet_new[nMaxHits];                 tree_output->Branch( "subdet",    subdet_new,    TString::Format( "subdet[%i]/D",    nMaxHits ) );
    Double_t Idp_new[nMaxHits];                    tree_output->Branch( "Idp",       Idp_new,       TString::Format( "Idp[%i]/D",       nMaxHits ) );
    Double_t Ipar_new[nMaxHits];                   tree_output->Branch( "Ipar",      Ipar_new,      TString::Format( "Ipar[%i]/D",      nMaxHits ) );
    Double_t itrack_new[nMaxHits];                 tree_output->Branch( "itrack",    itrack_new,    TString::Format( "itrack[%i]/D",    nMaxHits ) );
    Double_t Time_new[nMaxHits];                   tree_output->Branch( "Time",      Time_new,      TString::Format( "Time[%i]/D",      nMaxHits ) );
    Double_t xh_new[nMaxHits];                     tree_output->Branch( "xh",        xh_new,        TString::Format( "xh[%i]/D",        nMaxHits ) );
    Double_t yh_new[nMaxHits];                     tree_output->Branch( "yh",        yh_new,        TString::Format( "yh[%i]/D",        nMaxHits ) );
    Double_t zh_new[nMaxHits];                     tree_output->Branch( "zh",        zh_new,        TString::Format( "zh[%i]/D",        nMaxHits ) );
    Double_t P_new[nMaxHits];                      tree_output->Branch( "P",         P_new,         TString::Format( "P[%i]/D",         nMaxHits ) );
    Double_t PX_new[nMaxHits];                     tree_output->Branch( "PX",        PX_new,        TString::Format( "PX[%i]/D",        nMaxHits ) );
    Double_t PY_new[nMaxHits];                     tree_output->Branch( "PY",        PY_new,        TString::Format( "PY[%i]/D",        nMaxHits ) );
    Double_t PZ_new[nMaxHits];                     tree_output->Branch( "PZ",        PZ_new,        TString::Format( "PZ[%i]/D",        nMaxHits ) );
    Double_t VertexX_new[nMaxHits];                tree_output->Branch( "VertexX",   VertexX_new,   TString::Format( "VertexX[%i]/D",   nMaxHits ) );
    Double_t VertexY_new[nMaxHits];                tree_output->Branch( "VertexY",   VertexY_new,   TString::Format( "VertexY[%i]/D",   nMaxHits ) );
    Double_t VertexZ_new[nMaxHits];                tree_output->Branch( "VertexZ",   VertexZ_new,   TString::Format( "VertexZ[%i]/D",   nMaxHits ) );
    Double_t Kinev_new[nMaxHits];                  tree_output->Branch( "Kinev",     Kinev_new,     TString::Format( "Kinev[%i]/D",     nMaxHits ) );
    Double_t PXvdir_new[nMaxHits];                 tree_output->Branch( "PXvdir",    PXvdir_new,    TString::Format( "PXvdir[%i]/D",    nMaxHits ) );
    Double_t PYvdir_new[nMaxHits];                 tree_output->Branch( "PYvdir",    PYvdir_new,    TString::Format( "PYvdir[%i]/D",    nMaxHits ) );
    Double_t PZvdir_new[nMaxHits];                 tree_output->Branch( "PZvdir",    PZvdir_new,    TString::Format( "PZvdir[%i]/D",    nMaxHits ) );
    Double_t Iev_new[nMaxHits];                    tree_output->Branch( "Iev",       Iev_new,       TString::Format( "Iev[%i]/D",       nMaxHits ) );
    Double_t Step_new[nMaxHits];                   tree_output->Branch( "Step",      Step_new,      TString::Format( "Step[%i]/D",      nMaxHits ) );
    Double_t InextStep_new[nMaxHits];              tree_output->Branch( "InextStep", InextStep_new, TString::Format( "InextStep[%i]/D", nMaxHits ) );
    
    //--- loop on input tree
    
    Int_t nEntries = tree_input->GetEntries();
    
    for( Int_t iEntry=0; iEntry<nEntries; iEntry++ ) {
        
        tree_input->GetEntry( iEntry );
        
        if( iEntry%100 == 0 ) cout << "Event " << iEntry << endl; 
        
        for( Int_t i=0; i<nMaxHits; ++i ) {
            
            subdet_new[i]    = -999.;
            Idp_new[i]       = -999.;
            Ipar_new[i]      = -999.;
            itrack_new[i]    = -999.;
            Time_new[i]      = -999.;
            xh_new[i]        = -999.;
            yh_new[i]        = -999.;
            zh_new[i]        = -999.;
            P_new[i]         = -999.;
            PX_new[i]        = -999.;
            PY_new[i]        = -999.;
            PZ_new[i]        = -999.;
            VertexX_new[i]   = -999.;
            VertexY_new[i]   = -999.;
            VertexZ_new[i]   = -999.;
            Kinev_new[i]     = -999.;
            PXvdir_new[i]    = -999.;
            PYvdir_new[i]    = -999.;
            PZvdir_new[i]    = -999.;
            Iev_new[i]       = -999.;
            InextStep_new[i] = -999.;
            Step_new[i]      = -999.;
            
        }
        
        BeamX_new    = BeamX;
        BeamY_new    = BeamY;
        BeamZ_new    = BeamZ;
        BeamCX_new   = BeamCX;
        BeamCY_new   = BeamCY;
        BeamCZ_new   = BeamCZ;
        BeamEne_new  = BeamEne;
        BeamPart_new = BeamPart;
        nhits_new    = nhits;
        
        Int_t vsize = Iev->size(); // size is the same for all vectors
        
        if( vsize > nMaxHits ) cout << "ERROR, Vector size > Array size, entry " << iEntry << endl;
        
        Int_t n = TMath::Min( nMaxHits, vsize );
        
        for( Int_t i=0; i<n; ++i ) {
            
            subdet_new[i]    = subdet->at(i);
            Idp_new[i]       = Idp->at(i);
            Ipar_new[i]      = Ipar->at(i);
            itrack_new[i]    = itrack->at(i);
            Time_new[i]      = Time->at(i);
            xh_new[i]        = xh->at(i);
            yh_new[i]        = yh->at(i);
            zh_new[i]        = zh->at(i);
            P_new[i]         = P->at(i);
            PX_new[i]        = PX->at(i);
            PY_new[i]        = PY->at(i);
            PZ_new[i]        = PZ->at(i);
            VertexX_new[i]   = VertexX->at(i);
            VertexY_new[i]   = VertexY->at(i);
            VertexZ_new[i]   = VertexZ->at(i);
            Kinev_new[i]     = Kinev->at(i);
            PXvdir_new[i]    = PXvdir->at(i);
            PYvdir_new[i]    = PYvdir->at(i);
            PZvdir_new[i]    = PZvdir->at(i);
            Iev_new[i]       = Iev->at(i);
            Step_new[i]      = Step->at(i);
            InextStep_new[i] = InextStep->at(i);
            
        }
        
        tree_output->Fill();
        
    }
    
    tree_output->Write();
    
}
