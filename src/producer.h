#ifndef PRODUCER
#define PRODUCER

#include "processor.h"
#include "TTree.h"

template <class TreeType> class producer : public processor<TreeType> {

 public : 
  
  TreeType *ntuple ; 
  TTree* newTree ;

  producer(){
    ntuple = 0;
  };
  producer( TreeType* ntuple_ ){
    ntuple = ntuple_;
  };

  virtual void postProcess() = 0 ;
 
};

#endif
