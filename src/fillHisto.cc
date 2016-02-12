#ifndef FILLHISTO
#define FILLHISTO

#include "filler.h"
//#include "weightProducer.cc"
#include <iostream>
#include <string>
#include <cassert>

#include "TLeaf.h"
#include "TString.h"

using namespace std;

template <class TreeType> class fillHisto : public filler<TreeType> {

public : 

  TString branchname;
  //weightProducer<TreeType>* weightProd;
  processor<TreeType>* weightProd;
  TH1F* histo;
  TreeType* ntuple;

  fillHisto(){
    ntuple = 0;
    histo = new TH1F("test","test",20,500.,1500.);
  };
  
  fillHisto( TreeType* ntuple_ , 
	     int nBins = 20 , 
	     float lowEdge = 500. , float highEdge = 1500. , 
	     TString histoname = "default" ,
	     TString branchname_= "HT" ,
	     processor<TreeType>* wp = NULL ){

    ntuple = ntuple_;
    branchname = branchname_;
    weightProd = wp;
    histo = new TH1F(branchname+"_"+histoname,branchname+"_"+histoname,nBins,lowEdge,highEdge);
    if( weightProd != NULL )
      histo->Sumw2();

  };

  fillHisto( TreeType* ntuple_ , 
	     std::vector<string> args ,
	     processor<TreeType>* weightProd = NULL ){

    ntuple = ntuple_;
    
    if( args.size() == 5 ){
      fillHisto( ntuple_ , stoi( args[0] ) , stof( args[1] ) , stof( args[2] ) , args[3] , args[4] , weightProd );
    }else{
      assert(0);
    }
    
  };

  bool process( ) override {
    if( weightProd == NULL )
      histo->Fill( ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() );
    else
      histo->Fill( ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() , weightProd->weight );
    return true;
  };

};

#endif
