//#ifndef DISSECTINGJETMET
//#define DISSECTINGJETMET
//#include "dissectingJetsMET.cc"
//#endif

#ifndef PROCESSOR
#define PROCESSOR

template <class TreeType> class processor {

public : 

  TreeType *ntuple ; 

  processor(){ ntuple=0; };
  processor( TreeType* ntuple_ ){
    ntuple = ntuple_ ;
  };

  // purely virtual method to be implement by children
  virtual bool process( ) = 0 ;

};

#endif
