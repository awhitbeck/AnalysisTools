//#ifndef DISSECTINGJETMET
//#define DISSECTINGJETMET
//#include "dissectingJetsMET.cc"
//#endif

#ifndef SELECTBASELINE
#define SELECTBASELINE

#include "processor.h"
#include <iostream>

using namespace std;

template <class TreeType> class selectBaseline : public processor<TreeType> {

public : 

  TH1F* histo;
  TreeType* ntuple;
  int cutMask;

  selectBaseline(){ ntuple = 0; };
  selectBaseline( TreeType *ntuple_ , int cutMask_ = 0 ){
    ntuple = ntuple_;
    histo = new TH1F("selectBaselineYields","selectBaselineYields",5,0.5,5.5);
    cutMask = cutMask_;
  };
  
  bool process( ) override {
    
    /*
    cout << "HT: " << ntuple->HT << " mask: " << static_cast<bool>(cutMask&1) << endl;
    cout << "MHT: " << ntuple->MHT << " mask: " << static_cast<bool>(cutMask&2) << endl;
    cout << "NJets: " << ntuple->NJets << " mask: " << static_cast<bool>(cutMask&4) << endl;
    cout << "NLeptons: " << ntuple->NLeptons << " mask: " << static_cast<bool>(cutMask&8) << endl;
    cout << "dPhi: " << ntuple->dPhi << " mask: " << static_cast<bool>(cutMask&16) << endl;
    */

    histo->Fill(0);
    if( ntuple->NJets>=4 || static_cast<bool>(cutMask&1) ) histo->Fill(1);
    else return false;
    if( ntuple->HT>500. || static_cast<bool>(cutMask&2) ) histo->Fill(2);
    else return false;
    if( ntuple->MHT>200. || static_cast<bool>(cutMask&4) ) histo->Fill(3); 
    else return false;
    if( ntuple->NLeptons <= 0 || static_cast<bool>(cutMask&8) ) histo->Fill(4);
    else return false;
    if( ntuple->dPhi>0.5 || static_cast<bool>(cutMask&16) ) histo->Fill(5);
    else return false;

    return true;

  };

};

#endif
