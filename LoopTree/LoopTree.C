#include <TFile.h>
#include <TTree.h>
#include <TH1I.h>
#include <TH2I.h>
#include <TCanvas.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

void LoopTree(string inName="out.root", long long Nmax= -1){

  //some histograms...
  TH2I *hXY= new TH2I("hXY","hXY1;x1 [ch];y1 [ch]",20,-2.,2.,20,-5,5);
  TH1I* hX2= new TH1I("hX2","hX2 !cut XY[1];x2 [ch]",20,-20,20);


  TFile *input_file;
  input_file = new TFile(inName.data(),"read");
  cout << "Opened file " << inName << endl;
    
  //read tree from file
  TTree *tree;
  tree= (TTree*) input_file->Get("data");
  //uncomment to see content of tree
  //tree->Print();

  //variables to load information of tree
  double X[2];
  double Y[2];
  int entry;

  tree->SetMakeClass(1);  

  tree->SetBranchAddress("x",X,0);
  tree->SetBranchStatus("x",1);
  tree->SetBranchAddress("y",Y,0);
  tree->SetBranchStatus("y",1);
  tree->SetBranchAddress("n",&entry,0);
  tree->SetBranchStatus("n",1);

  //number of data points in TTree
  long long n_entries;

  n_entries = tree->GetEntries();
  cout << "\nNumber of entries in input tree= " << n_entries << endl;

  //maybe we only want to look at the first few entries in tree (good for debugging)
  if(Nmax>0 && n_entries > Nmax) n_entries= Nmax;
  cout << "\nLooping over " << n_entries << " entries." << endl;


  for(long long i=0; i<n_entries;i++){

    tree->GetEntry(i);

    //fill some test histograms
    hXY->Fill(X[0],Y[0]);
    //applying some conditions on other variables
    if(sqrt(X[0]*X[0]+Y[0]*Y[0]) <= 1.25){
      hX2->Fill(X[1]);
    }

  }


  //Draw the histograms in a TCanvas and save it to a png file
  TCanvas *c1;
  c1= new TCanvas("c1","c1");
  c1->Divide(1,2);

  c1->cd(1); hXY->Draw("colz");

  c1->cd(2); hX2->Draw(); 
  gPad->SetLogy(1);

  c1->SaveAs("test.png");

}
