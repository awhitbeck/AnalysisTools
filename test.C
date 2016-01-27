#include "selectBaseline.cc"
#include "fillHT.cc"
#include "analyzer.cc"

#include "TString.h"
#include "TChain.h"

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

TChain* buildChain(TString inputFileList, TString treeName){

  string line;
  ifstream inputFile(inputFileList);

  TChain* t = new TChain(treeName);

  char temp[200];

  if( inputFile.is_open() ){

    while( getline( inputFile , line ) ){

      sprintf( temp , "root://cmsxrootd.fnal.gov//%s", line.c_str() );
      t->Add( temp );

    }// end while loop over lines in file

  }// end is_open() if statement

  return t ;

}

void test( TString fileName ){

  cout << "Compiling local classes..." << endl;
  gROOT->ProcessLine(".L selectBaseline.cc+");
  gROOT->ProcessLine(".L fillHT.cc+");
  gROOT->ProcessLine(".L analyzer.cc+");

  TChain* t = buildChain(fileName,"analysisTree");
  
  dissectingJetsMET *ntuple = new dissectingJetsMET(t);

  fillHT *fill = new fillHT(ntuple);
  selectBaseline *select = new selectBaseline(ntuple);

  //p.runConfig("config.txt");

  analyzer a(ntuple);
  a.addProcessor( select );
  a.addProcessor( fill );

  a.looper();

  fill->histo->Draw();
  
}  
