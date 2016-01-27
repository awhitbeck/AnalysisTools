#ifndef DISSECTINGJETMET
#define DISSECTINGJETMET
#include "dissectingJetsMET.cc"
#endif

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


class analyzer{
  
public : 
  
  // ntuple class
  dissectingJetsMET* ntuple;

  // maintain a list of processes that should be 
  // run on each event:
  //     note, processor is a purely virtual class, 
  //     so it must be used as a pointer
  vector<processor*> processorList;

  analyzer( dissectingJetsMET* ntuple_ ){
    ntuple = ntuple_ ;
  };

  ~analyzer(){};

  // push processor into list
  void addProcessor( processor* p ){
    processorList.push_back( p ) ;
  };

  // see implementation for notes
  void looper();
  // see implementation for notes
  //void runConfig( string inputConfigName );


};

// function for looping over events in ntuple
// each process is called once.  If any of them 
// return false, the next event is processed. 
void analyzer::looper(){

  int numEvents = ntuple->fChain->GetEntries();

  for( int iEvt = 0 ; iEvt < numEvents ; iEvt++ ){

    ntuple->fChain->GetEntry(iEvt);

    if( iEvt % 1000000 == 0 ) cout << "Event " << iEvt << "/" << numEvents << endl;
 
    // loop over all processors
    for( auto &processor : processorList ){
      if( ! processor->process() ){
	//cout << "false" << endl;
	break;
      }
    }// end loop over processors

  }

}

  /*

void analyzer::runConfig( project p , string inputConfigName ){

  string line;
  ifstream inputConfig(inputConfigName);

  vector< vector< string > > configMatrix;
  if( inputConfig.is_open() ){

    while( getline( inputConfig , line ) ){

      vector< string > configLineTokens = split( line , '|' );
      
      for( auto &i : configLineTokens )
	cout << i << " " ;

      cout << endl;

      if( configLineTokens.size() == 0 ) continue;				  
      
      processor* processorTemp = p.getProcessor( configLineTokens[0] ) 
      if( processorTemp == NULL )
	assert( 0 ) ;
      else
	processorTemp
	

    }// end loop over lines

  }// end if file is_open()

}
  */

#endif
