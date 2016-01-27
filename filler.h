#ifndef DISSECTINGJETMET
#define DISSECTINGJETMET
#include "dissectingJetsMET.cc"
#endif

#ifndef FILLER
#define FILLER

#include "processor.h"
#include "TH1F.h"
#include "TFile.h"
#include "TString.h"

class filler : public processor {

 public : 
  
  TH1F* histo;
  dissectingJetsMET *ntuple ; 
  
  filler( dissectingJetsMET* ntuple_ ) : processor(ntuple_) { 
    ntuple = ntuple_ ;
  };

  // purely virtual method to be implement by children
  //virtual bool process( ) = 0 ;
  
  //void parseArguments( std::vector<string> );
 
  // not yet implemented
  void saveHisto( TFile* outputFile ){};
 
};

#endif
