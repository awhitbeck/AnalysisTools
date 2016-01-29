#include "selectBaseline.cc"
#include "fillHT.cc"
#include "analyzer.cc"
#include "weightProducer.cc"

#include "TString.h"
#include "TChain.h"
#include "TFile.h"

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

TChain* buildChain(TString inputFileList, TString substr, TString treeName){

  string line;
  ifstream inputFile(inputFileList);

  TChain* t = new TChain(treeName);

  char temp[200];

  if( inputFile.is_open() ){

    while( getline( inputFile , line ) ){

      if( line.find(substr.Data()) == string::npos ) continue;

      sprintf( temp , "root://cmsxrootd.fnal.gov//%s", line.c_str() );
      t->Add( temp );

    }// end while loop over lines in file

  }// end is_open() if statement

  return t ;

}

int main(int argc, char** argv){

  TString sample = argv[1];
  TChain* t = buildChain("slimFiles.txt",sample,"analysisTree");
  
  dissectingJetsMET *ntuple = new dissectingJetsMET(t);

  weightProducer *weightProd = new weightProducer(ntuple,sample);
  fillHT *fill = new fillHT(ntuple,200,400,10000,sample,weightProd);
  selectBaseline *select = new selectBaseline(ntuple);

  analyzer a(ntuple);
  a.addProcessor( select );
  a.addProcessor( fill );

  a.looper();

  fill->histo->Draw();

  TFile* outFile = new TFile("outFile_"+sample+".root","UPDATE");
  fill->histo->Write();
  outFile->Close();

}  

