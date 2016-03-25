#ifndef PROCESSOR
#define PROCESSOR

template <class TreeType> class processor {

public : 

  TreeType *ntuple ; 
  TString moduleName ;

  processor(){ moduleName = "<NONE>" ; ntuple = 0; };
  processor(TString moduleName_){ moduleName = moduleName_ ; ntuple=0; };
  processor(TString moduleName_ , TreeType* ntuple_ ){
    moduleName = moduleName_;
    ntuple = ntuple_ ;
  };

  TString getModuleName(){ return moduleName ; };

  // purely virtual methods to be implement by children
  virtual bool process( ) = 0 ;
  virtual void postProcess( ) = 0 ; 

};

#endif
