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
  int reportEvery;
  int verbosity;

  // maintain a list of processes that should be 
  // run on each event:
  //     note, processor is a purely virtual class, 
  //     so it must be used as a pointer
  vector<processor<TreeType>* >* processorList;

  analyzer( TreeType* ntuple_ , int numProcessors = 0){
    ntuple = ntuple_ ;
    verbosity=0;
    processorList = new vector<processor<TreeType>* >(numProcessors,NULL);
  };

  ~analyzer(){};

  // push processor into list
  void addProcessor( processor<TreeType>* p ){
    //cout << "analyzer::addProcessor - processor: " << p << endl;
    //cout << "module name: " << p->moduleName << endl;

    unsigned int ithProcessor = 0 ;
    while( processorList->at(ithProcessor) != NULL && ithProcessor<processorList->size() ){
      ithProcessor++;
    }
    if( ithProcessor >= processorList->size() ){
      processorList->push_back( p ) ;
    }else{
      processorList->at(ithProcessor) = p;
    }

  };

  void setReportEvery(int re){ reportEvery = re ; };

  // function for looping over events in ntuple
  // each process is called once.  If any of them 
  // return false, the next event is processed. 
  void looper(int maxEvents=-1){
    int numEvents = ntuple->fChain->GetEntries();
    for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){
      if( maxEvents != -1 && iEvt > maxEvents ) break;
      ntuple->fChain->GetEntry(iEvt);
      if( iEvt % reportEvery == 0 ) cout << "Event " << iEvt << "/" << numEvents << endl;
      
      // loop over all processors
      for( unsigned int i = 0 ; i < processorList->size() ; i++ ){
	if( verbosity > 5 ) cout << "module: " << processorList->at(i)->moduleName << endl;
	if( ! processorList->at(i)->process() ){
          if( verbosity > 0 ) cout << processorList->at(i)->moduleName << ": false" << endl;  
          break;
        }        
      }
      
    }// end loop over events
  };

  //void runConfig( string inputConfigName );


};

#endif
