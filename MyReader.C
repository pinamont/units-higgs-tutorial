R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"

void MyReader(const char *fileName){
  
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(fileName);
  
  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  // TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  // TClonesArray *branchJet = treeReader->UseBranch("Jet");
  // ...

  // Book histograms
  TH1F *histElectronPT = new TH1F("electron pt", "electron P_{T}", 50, 0.0, 100.0);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // print event number in the file
    if(entry%100==0) cout << "Reading Event " << entry << endl;
    
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
  
    // If event contains at least 1 electron
    if(branchElectron->GetEntries() > 0)
    {
      // Take first electron
      Electron *electron = (Electron*) branchElectron->At(0);
      
      // Plot electron transverse momentum
      // histElectronPT->Fill(electron->PT);
      
      // Print electron transverse momentum
      // cout << electron->PT << endl;
    }

  }

  // Show resulting histograms
  // TCanvas *c = new TCanvas("c","c");
  // histElectronPT->Draw();

  // Save the result as image
  // c->SaveAs("ElectronPT.png");

  // Save the histogram in a ROOT file
  // TFile *f = new TFile("ElectronPT.root","RECREATE");
  // histElectronPT->Write("",TObject::kOverwrite);
}
 
