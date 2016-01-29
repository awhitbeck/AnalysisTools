#ifndef DISSECTINGJETMET
#define DISSECTINGJETMET
#include "dissectingJetsMET.cc"
#endif

#ifndef FILLHISTO
#define FILLHISTO

#include "filler.h"
#include "weightProducer.cc"
#include <iostream>
#include <string>
#include <cassert>

#include "TLeaf.h"
#include "TString.h"

using namespace std;

class fillHisto : public filler {

public : 

  TString branchname;
  weightProducer* weightProd;

  fillHisto():filler(0){
    histo = new TH1F("test","test",20,500.,1500.);
  };
  
  fillHisto( dissectingJetsMET* ntuple_ , 
	     int nBins = 20 , 
	     float lowEdge = 500. , float highEdge = 1500. , 
	     TString histoname = "default" ,
	     TString branchname_= "HT" ,
	     weightProducer* wp = NULL ) : filler(ntuple_)
  {
    
    branchname = branchname_;
    weightProd = wp;
    histo = new TH1F(branchname+"_"+histoname,branchname+"_"+histoname,nBins,lowEdge,highEdge);
    if( weightProd != NULL )
      histo->Sumw2();

  };

  fillHisto( dissectingJetsMET* ntuple_ , 
	     std::vector<string> args ,
	     weightProducer* weightProd = NULL ) : filler(ntuple_)
  {
    
    if( args.size() == 5 ){
      fillHisto( ntuple_ , stoi( args[0] ) , stof( args[1] ) , stof( args[2] ) , args[3] , args[4] , weightProd );
    }else{
      assert(0);
    }
    
  };

  bool process( ) override ;

};

bool fillHisto::process( ){
  
  //cout << "filling HT histo with " << ntuple->HT << endl;

  if( weightProd == NULL )
    histo->Fill( ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() );
  else
    histo->Fill( ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() , weightProd->weight );
		  
  return true;
  
};

#endif
