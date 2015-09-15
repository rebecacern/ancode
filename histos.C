// rebeca@cern.ch
// Attempt to optimize the work
#include <iostream>
#include "TSystem.h"
#include <vector>
#include "TH1.h"
#include "TChain.h"
#include <string>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"
#include <cmath>
#include "variables.h"
#include "TLorentzVector.h"


void histos(int nsel = 1){

  char plotName[300];
  sprintf(plotName,"test");
  bool isBackground = true;
  bool isData = false;
		  
  if (nsel == 0)                	{sprintf(plotName,"Data");	isBackground = false;	isData = true;}
  else if (nsel == 1)   		{sprintf(plotName,"ttH125");	isBackground = false;}
  else if (nsel == 2)   		{sprintf(plotName,"ttJets");}
  else if (nsel == 3)   		{sprintf(plotName,"ttW");}
  else if (nsel == 4)   		{sprintf(plotName,"ttZ");}
  else if (nsel == 5)			{sprintf(plotName,"DY");}
				  
  char myRootFile[300];
  sprintf(myRootFile,"../minitrees/%s.root",plotName);
  cout << "[Info:] " << plotName  << endl;
 
  TChain *chain = new TChain("summaryTree"); //"summaryTree");
  chain->Add(myRootFile);
 
 // variables in the minitrees
    double mcwgt_intree = -999.;
    double wgt_intree = -999.;
    double lepton_1_pt_intree = -99.;
    double lepton_2_pt_intree = -99.;
    double lepton_1_px_intree = -99.;
    double lepton_2_px_intree = -99.;
    double lepton_1_py_intree = -99.;
    double lepton_2_py_intree = -99.;
    double lepton_1_pz_intree = -99.;
    double lepton_2_pz_intree = -99.;
    double lepton_1_e_intree = -99.;
    double lepton_2_e_intree = -99.;
    double met_pt_intree = -99.;
    double met_px_intree = -99.;
    double met_py_intree = -99.;
    double metLD_intree = 0.; //n.zeros(1,dtype=float)
    double MHT_intree = 0.; 
    double SumPt_intree = 0.;
    int n_jets_intree = -99.;
  
   
    chain->SetBranchAddress("mcwgt", &mcwgt_intree);
    chain->SetBranchAddress("wgt", &wgt_intree);
        
    chain->SetBranchAddress("lepton_1_pt", &lepton_1_pt_intree);
    chain->SetBranchAddress("lepton_2_pt", &lepton_2_pt_intree);
    chain->SetBranchAddress("lepton_1_px", &lepton_1_px_intree);
    chain->SetBranchAddress("lepton_2_px", &lepton_2_px_intree);
    chain->SetBranchAddress("lepton_1_py", &lepton_1_py_intree);
    chain->SetBranchAddress("lepton_2_py", &lepton_2_py_intree);
    chain->SetBranchAddress("lepton_1_pz", &lepton_1_pz_intree);
    chain->SetBranchAddress("lepton_2_pz", &lepton_2_pz_intree);
    chain->SetBranchAddress("lepton_1_e", &lepton_1_e_intree);
    chain->SetBranchAddress("lepton_2_e", &lepton_2_e_intree);
    chain->SetBranchAddress("met_pt", &met_pt_intree);
    chain->SetBranchAddress("met_px", &met_px_intree);
    chain->SetBranchAddress("met_py", &met_py_intree);
    chain->SetBranchAddress("metLD", &metLD_intree);
    chain->SetBranchAddress("MHT", &MHT_intree);
    chain->SetBranchAddress("n_jets", &n_jets_intree);    
     
  
  // Prepare output file
  char rootFile[300];
  sprintf(rootFile,"results/histos.root");
  TFile f_root(rootFile, "UPDATE");

  // Prepare histograms
  char title[300];
												    
  sprintf(title,"ptleptons_%s",plotName);
  TH1F* histo_ptleptons = new TH1F( title, " ", 100, 20, 200);
  histo_ptleptons->Sumw2();	
  							    
  sprintf(title,"ptleading_%s",plotName);
  TH1F* histo_ptleading = new TH1F( title, " ", 100, 20, 200);
  histo_ptleading->Sumw2();
			    
  sprintf(title,"pttrailing_%s",plotName);
  TH1F* histo_pttrailing = new TH1F( title, " ", 100, 20, 200);
  histo_pttrailing->Sumw2();
  								    
  sprintf(title,"etaleptons_%s",plotName);
  TH1F* histo_etaleptons = new TH1F( title, " ", 101, -3.4, 3.4);
  histo_etaleptons->Sumw2();
  					    
  sprintf(title,"etaleading_%s",plotName);
  TH1F* histo_etaleading = new TH1F( title, " ", 101, -3.4, 3.4);
  histo_etaleading->Sumw2();	
  				    
  sprintf(title,"etatrailing_%s",plotName);
  TH1F* histo_etatrailing = new TH1F( title, " ", 101, -3.4, 3.4);
  histo_etatrailing->Sumw2();	
  				
  
  double weight = 1;
  int nevents=chain->GetEntries();
  cout << "[Info:] " << nevents  << " total events in the tree " <<  endl;
  for (int i=0; i<nevents; ++i) {
	chain->GetEntry(i);
	histo_ptleptons->Fill(lepton_1_pt_intree, weight);
	histo_ptleptons->Fill(lepton_2_pt_intree, weight);
	histo_ptleading->Fill(lepton_1_pt_intree, weight);	
	histo_pttrailing->Fill(lepton_2_pt_intree, weight);	
	TLorentzVector lep1(lepton_1_px_intree,lepton_1_py_intree, lepton_1_pz_intree, lepton_1_e_intree);
        TLorentzVector lep2(lepton_2_px_intree,lepton_2_py_intree, lepton_2_pz_intree, lepton_2_e_intree);						           
        histo_etaleptons->Fill(lep1.Eta(), weight);
	histo_etaleptons->Fill(lep2.Eta(), weight);					           
        histo_etaleading->Fill(lep1.Eta(), weight);
	histo_etatrailing->Fill(lep2.Eta(), weight);
  }    
  
  cout << "[Info:] " << plotName << " done "  << endl;
  
  
  f_root.Write();
  f_root.Close();
 
  
}
