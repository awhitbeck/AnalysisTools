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
  selectBaseline *select = new selectBaseline(ntuple);

  analyzer a(ntuple);
  a.addProcessor( select );

  fillHisto *fillHT = new fillHisto(ntuple,200,500,2500,sample,"HT",weightProd);   a.addProcessor( fillHT );
  fillHisto *fillMHT = new fillHisto(ntuple,200,200,1000,sample,"MHT",weightProd); a.addProcessor( fillMHT );
  fillHisto *fillMET = new fillHisto(ntuple,200,200,1000,sample,"MET",weightProd); a.addProcessor( fillMET );
  fillHisto *fillmT2 = new fillHisto(ntuple,200,200,2500,sample,"mT2",weightProd); a.addProcessor( fillmT2 );
  fillHisto *fillalphaT = new fillHisto(ntuple,200,0,2,sample,"alphaT",weightProd); a.addProcessor( fillalphaT );
  fillHisto *fillmRazor = new fillHisto(ntuple,200,200,4000,sample,"mRazor",weightProd); a.addProcessor( fillmRazor );
  fillHisto *filldRazor = new fillHisto(ntuple,200,0,1,sample,"dRazor",weightProd); a.addProcessor( filldRazor );
  fillHisto *fillmEff = new fillHisto(ntuple,200,400,4000,sample,"mEff",weightProd); a.addProcessor( fillmEff );
  fillHisto *fillNJets = new fillHisto(ntuple,11,-0.5,10.5,sample,"NJets",weightProd); a.addProcessor( fillNJets );
  fillHisto *fillNLeptons = new fillHisto(ntuple,4,-0.5,3.5,sample,"NLeptons",weightProd); a.addProcessor( fillNLeptons );
  fillHisto *filldPhi = new fillHisto(ntuple,20,0.,3.1415,sample,"dPhi",weightProd); a.addProcessor( filldPhi );
  fillHisto *filldEta = new fillHisto(ntuple,20,0.,5.,sample,"dEta",weightProd); a.addProcessor( filldEta );
  fillHisto *fillsumJetMass = new fillHisto(ntuple,200,100.,1000.,sample,"sumJetMass",weightProd); a.addProcessor( fillsumJetMass );
  fillHisto *fillleadJetPt = new fillHisto(ntuple,200,30,500,sample,"leadJetPt",weightProd); a.addProcessor( fillleadJetPt );

  a.looper();

  TFile* outFile = new TFile("genericPlotter_"+sample+".root","UPDATE");
  for( unsigned int iProc = 0 ; iProc < a.processorList.size() ; iProc++ ){
    if( filler* myFiller = dynamic_cast<filler*>( a.processorList[iProc] ) ){
      myFiller->histo->Write();
    }
  }
  outFile->Close();

}  

