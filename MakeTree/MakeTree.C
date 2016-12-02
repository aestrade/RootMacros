#include <TFile.h>
#include <TTree.h>

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

void MakeTree(string inName="test.txt", string outName="test.root", int Nlines=0, int Nlocations=1){

  //input text file with data to store in TTree
  ifstream inFile;
  inFile.open(inName.data(), ios::in);

  //output file to save TTree
  TFile * outFile;
  outFile = new TFile(outName.data(), "RECREATE");


  double x[2];
  double y[2];

  int n;
  double my_x, my_y;

  string comment;

  //TTree object that provides data storage structure
  // see online documentation of Root TTree class
  TTree * tree;

  tree = new TTree("data","data");
  //this is the syntax to add Branches that contain arrays: see Root documentation
  tree->Branch("x",x,"x[2]/D");
  tree->Branch("y",y,"y[2]/D");
  //and this for single variables
  tree->Branch("n",&n,"n/I");

  for(int i=0; i<3; i++){
    getline(inFile,comment);
    cout << "read: ' " << comment << " ' " << endl;
  }

  cout << "\n Now reading " << Nlines << " data entries..." << endl;


  for(int i=0; i< Nlines ; i++){
    inFile >> n;

    if(inFile.eof()){

      cout << " WARNING: reached end of file before reading all lines (n= " << n << endl;
    }

    for(int j=0; j< Nlocations; j++){
      inFile >> my_x >> my_y;
      x[j]= my_x;
      y[j]= my_y;
    }

    tree->Fill();

  }

  cout << "Finished reading input file at line " << n << endl;


  tree->Write();

  outFile->Close();



}
