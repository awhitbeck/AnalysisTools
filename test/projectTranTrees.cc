#include "tranTree.cc"
#include "selectBaseline.cc"
#include "filterHighWeights.cc"
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

typedef fillHisto<tranTree> hFiller;

int main(int argc, char** argv){

  TString sample = argv[1];
  TChain* t = new TChain("otree");
  t->Add("/uscmst1b_scratch/lpc1/3DayLifetime/ntran/SUSY/samples_looseSel/ProcJPM_"+sample+"-test.root");

  tranTree *ntuple = new tranTree(t);

  selectBaseline<tranTree> *select = new selectBaseline<tranTree>(ntuple);
  filterHighWeights<tranTree> *weightFilter = new filterHighWeights<tranTree>(ntuple);
  
  analyzer<tranTree> a(ntuple);
  a.setReportEvery(2000000);
  a.addProcessor( weightFilter );
  a.addProcessor( select );

  hFiller *fillHT = new hFiller(ntuple,200,500,2500,sample,"HT","lheWeight",10000.);   a.addProcessor( fillHT );
  hFiller *fillMHT = new hFiller(ntuple,200,200,1000,sample,"MHT","lheWeight",10000.); a.addProcessor( fillMHT );
  hFiller *fillMET = new hFiller(ntuple,200,200,1000,sample,"MET","lheWeight",10000.); a.addProcessor( fillMET );
  hFiller *fillmT2 = new hFiller(ntuple,200,200,2500,sample,"mT2","lheWeight",10000.); a.addProcessor( fillmT2 );
  hFiller *fillalphaT = new hFiller(ntuple,200,0,2,sample,"alphaT","lheWeight",10000.); a.addProcessor( fillalphaT );
  hFiller *fillmRazor = new hFiller(ntuple,200,200,4000,sample,"mRazor","lheWeight",10000.); a.addProcessor( fillmRazor );
  hFiller *filldRazor = new hFiller(ntuple,200,0,1,sample,"dRazor","lheWeight",10000.); a.addProcessor( filldRazor );
  hFiller *fillmEff = new hFiller(ntuple,200,400,4000,sample,"mEff","lheWeight",10000.); a.addProcessor( fillmEff );
  hFiller *fillNJets = new hFiller(ntuple,11,-0.5,10.5,sample,"NJets","lheWeight",10000.); a.addProcessor( fillNJets );
  hFiller *fillNLeptons = new hFiller(ntuple,4,-0.5,3.5,sample,"NLeptons","lheWeight",10000.); a.addProcessor( fillNLeptons );
  hFiller *filldPhi = new hFiller(ntuple,20,0.,3.1415,sample,"dPhi","lheWeight",10000.); a.addProcessor( filldPhi );
  hFiller *filldEta = new hFiller(ntuple,20,0.,5.,sample,"dEta","lheWeight",10000.); a.addProcessor( filldEta );
  hFiller *fillsumJetMass = new hFiller(ntuple,200,100.,1000.,sample,"sumJetMass","lheWeight",10000.); a.addProcessor( fillsumJetMass );
  hFiller *fillleadJetPt = new hFiller(ntuple,200,30,500,sample,"leadJetPt","lheWeight",10000.); a.addProcessor( fillleadJetPt );

  a.looper();

  TFile* outFile = new TFile("genericPlotter_"+sample+".root","UPDATE");
  /*
  for( unsigned int iProc = 0 ; iProc < a.processorList.size() ; iProc++ ){
    if( filler<tranTree>* myFiller = dynamic_cast<filler<tranTree>* >( a.processorList[iProc] ) ){
      myFiller->histo->Write();
    }
  }
  */

  fillHT->histo->Write();
  fillMHT->histo->Write();
  fillMET->histo->Write();
  fillmT2->histo->Write();
  fillalphaT->histo->Write();
  fillmRazor->histo->Write();
  filldRazor->histo->Write();
  fillmEff->histo->Write();
  fillNJets->histo->Write();
  fillNLeptons->histo->Write();
  filldPhi->histo->Write();
  filldEta->histo->Write();
  fillsumJetMass->histo->Write();
  fillleadJetPt->histo->Write();

  select->histo->Write("baselineYields_"+sample);
  outFile->Close();

}  

