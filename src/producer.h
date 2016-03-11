#ifndef PRODUCER
#define PRODUCER

#include "processor.h"
#include "TTree.h"

template <class TreeType> class producer : public processor<TreeType> {

 public : 
  
  TreeType *ntuple ; 
  TTree* newTree ;

  producer()
    : processor<TreeType>("producer")
    {
      ntuple = 0;
    };
  producer( TString moduleName_ )
    : processor<TreeType>(moduleName_)
    {
      ntuple = 0;
    };
  producer( TString moduleName_ , TreeType* ntuple_ )
    : processor<TreeType>(moduleName_)
    {
      ntuple = ntuple_;
    };
  
  virtual void postProcess() = 0 ;
 
};

#endif
