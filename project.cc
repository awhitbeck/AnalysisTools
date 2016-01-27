#ifndef PROJECT
#define PROJECT

#include <map>
#include "TString.h"

#include "processor.h"
#include "fillHT.cc"
#include "selectBaseline.cc"
#include "dissectingJetsMET.cc"

using namespace std;

template<typename T> processor* createInstance(){ return new T; };

class project {

public : 

  // this is some serious voodoo!!
  map<TString,processor*(*)()> processorRegistry;

  project();
  ~project(){};

  void registerProcessor( TString name , processor* p );
  bool checkProcessorRegistry( TString name );
  
};
 
project::project(){
   
  // initialize registry
  processorRegistry["fillHT"] = &createInstance<fillHT>;
  processorRegistry["selectBaseline"] = &createInstance<selectBaseline>;

};

bool project::checkProcessorRegistry( TString name ){

  for( auto &p : processorRegistry ){

    if( p.first == name )
      return true;

  }

  cout << "Couldn't find processor in list of registered processors.  Check project or configuration." << endl;
  return false;

}

#endif
