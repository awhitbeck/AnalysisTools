#ifndef DISSECTINGJETMET
#define DISSECTINGJETMET
#include "dissectingJetsMET.cc"
#endif

#ifndef SELECTBASELINETEMPLATE
#define SELECTBASELINETEMPLATE

#include "processor.h"
#include <iostream>

using namespace std;

class selectBaseline : public processor {

public : 

  selectBaseline():processor(0){};
  selectBaseline( dissectingJetsMET *ntuple_ ) : processor(ntuple_){};
  
  bool process( ) override {

    //cout << "HT: " << ntuple->HT << endl;

    if(ntuple->HT<500. || 
       ntuple->MHT<200. || 
       ntuple->NJets<4 || 
       ntuple->NLeptons > 0 ||
       ntuple->dPhi<0.3){

      return false;

    }else{ 

      return true;

    }

  };

};

#endif
