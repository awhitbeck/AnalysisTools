#include "selectBaseline.cc"
#include "fillHisto.cc"
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

#include "helpers.h"

using namespace std;

int main(int argc, char** argv){

  TString sample = argv[1];
  TChain* t = buildChain("slimFiles.txt",sample,"analysisTree");
  
  dissectingJetsMET *ntuple = new dissectingJetsMET(t);

  weightProducer *weightProd = new weightProducer(ntuple,sample);
  fillHisto *fill = new fillHisto(ntuple,200,400,10000,sample,"HT",weightProd);
  selectBaseline *select = new selectBaseline(ntuple);

  analyzer a(ntuple);
  a.addProcessor( select );
  a.addProcessor( fill );

  a.looper();

  fill->histo->Draw();

  TFile* outFile = new TFile("genericPlotter_"+sample+".root","UPDATE");
  fill->histo->Write();
  outFile->Close();

}  

