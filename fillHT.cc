#ifndef DISSECTINGJETMET
#define DISSECTINGJETMET
#include "dissectingJetsMET.cc"
#endif

#ifndef FILLHT
#define FILLHT

#include "filler.h"
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

#include "TString.h"

using namespace std;

class fillHT : public filler {

public : 

  fillHT():filler(0){
    histo = new TH1F("test","test",20,500.,1500.);
  };
  
  fillHT( dissectingJetsMET* ntuple_ , 
	  int nBins = 20 , 
	  float lowEdge = 500. , float highEdge = 1500. , 
	  TString name = "default" ) : filler(ntuple_)
  {
    
    histo = new TH1F("HT_"+name,"HT_"+name,nBins,lowEdge,highEdge);
    
  };

  fillHT( dissectingJetsMET* ntuple_ , 
	  std::vector<string> args ) : filler(ntuple_)
  {
    
    if( args.size() == 4 ){
      fillHT( ntuple_ , stoi( args[0] ) , stof( args[1] ) , stof( args[2] ) , args[3] );
    }else{
      histo = new TH1F("HT_default","HT_default",20,500.,1500.);
    }
    
  };

  bool process( ) override ;

};

bool fillHT::process( ){
  
  //cout << "filling HT histo with " << ntuple->HT << endl;
  
  histo->Fill(ntuple->HT);
  
  return true;
  
};

#endif
