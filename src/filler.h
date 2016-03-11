//#ifndef DISSECTINGJETMET
//#define DISSECTINGJETMET
//#include "dissectingJetsMET.cc"
//#endif

#ifndef FILLER
#define FILLER

#include "processor.h"
#include "TH1F.h"
#include "TFile.h"
#include "TString.h"

template <class TreeType> class filler : public processor<TreeType> {

 public : 
  
  TH1F* histo;
  TreeType *ntuple ; 

 filler()
   : processor<TreeType>("filler"){};
 filler(TString moduleName_)
   : processor<TreeType>(moduleName_){
    ntuple = 0;
  };
 filler(TString moduleName_ , TreeType* ntuple_ )
   : processor<TreeType>(moduleName_){
    ntuple = ntuple_;
  };
  
 // purely virtual method to be implement by children
 //virtual bool process( ) = 0 ;
  
 //void parseArguments( std::vector<string> );
  
 // not yet implemented
 void saveHisto( TFile* outputFile ){};
  
};

#endif
