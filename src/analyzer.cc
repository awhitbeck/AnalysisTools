//#ifndef DISSECTINGJETMET
//#define DISSECTINGJETMET
//#include "dissectingJetsMET.cc"
//#endif

#ifndef ANALYZER
#define ANALYZER

#include "processor.h"
#include "TString.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


// stolen from stackoverflow thread with minor modifications:
// http://stackoverflow.com/questions/236129/split-a-string-in-c
vector<string> split(const string &s, char delim) {
  vector<string> elems;
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}


template <class TreeType> class analyzer{
  
public : 
  
  // ntuple class
  TreeType* ntuple;

  // maintain a list of processes that should be 
  // run on each event:
  //     note, processor is a purely virtual class, 
  //     so it must be used as a pointer
  vector<processor<TreeType>* > processorList;

  analyzer( TreeType* ntuple_ ){
    ntuple = ntuple_ ;
  };

  ~analyzer(){};

  // push processor into list
  void addProcessor( processor<TreeType>* p ){
    processorList.push_back( p ) ;
  };

  // function for looping over events in ntuple
  // each process is called once.  If any of them 
  // return false, the next event is processed. 
  void looper(int maxEvents=-1){
    int numEvents = ntuple->fChain->GetEntries();
    for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
      if( maxEvents != -1 && iEvt > maxEvents ) break;
      ntuple->fChain->GetEntry(iEvt);
      if( iEvt % 1000000 == 0 ) cout << "Event " << iEvt << "/" << numEvents << endl;
      
      // loop over all processors
      for( auto &ithProcessor : processorList ){
	if( ! ithProcessor->process() ){
	  //cout << "false" << endl;
	  break;
	}
      }// end loop over processors 
    }// end loop over events
  };

  //void runConfig( string inputConfigName );


};

#endif
