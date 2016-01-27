#ifndef DISSECTINGJETMET
#define DISSECTINGJETMET
#include "dissectingJetsMET.cc"
#endif

#ifndef FILLHISTO
#define FILLHISTO

#include "filler.h"
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

#include "TString.h"

using namespace std;

class fillhisto : public filler {

public : 

  TString branchname;

  fillhisto():filler(0){
    histo = new TH1F("test","test",20,500.,1500.);
  };
  
  fillhisto( dissectingJetsMET* ntuple_ , 
	  int nBins = 20 , 
	  float lowEdge = 500. , float highEdge = 1500. , 
	     TString histoname = "default" ,
	     TString branchname_= "HT" ) : filler(ntuple_)
  {
    
    branchname = branchname_;
    histo = new TH1F(branchname+"_"+histoname,branchname+"_"+histoname,nBins,lowEdge,highEdge);
    
  };

  fillhisto( dissectingJetsMET* ntuple_ , 
	  std::vector<string> args ) : filler(ntuple_)
  {
    
    if( args.size() == 4 ){
      fillhisto( ntuple_ , stoi( args[0] ) , stof( args[1] ) , stof( args[2] ) , args[3] );
    }else{
      histo = new TH1F("HT_default","HT_default",20,500.,1500.);
    }
    
  };

  bool process( ) override ;

};

bool fillhisto::process( ){
  
  //cout << "filling HT histo with " << ntuple->HT << endl;
  
  histo->Fill(ntuple->fChain->GetLeaf(branchname.Data()->GetValue());
  
  return true;
  
};

#endif
