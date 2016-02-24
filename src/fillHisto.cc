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

template <class TreeType> class fillHisto : public filler<TreeType> {

public : 

  TString branchname;
  weightProducer<TreeType>* weightProd;
  //processor<TreeType>* weightProd;
  TH1F* histo;
  TreeType* ntuple;
  TString weightBranch;
  double lumi;

  fillHisto(){
    ntuple = 0;
    histo = new TH1F("test","test",20,500.,1500.);
  };
  
  fillHisto( TreeType* ntuple_ , 
	     int nBins = 20 , 
	     float lowEdge = 500. , float highEdge = 1500. , 
	     TString histoname = "default" ,
	     TString branchname_= "HT" ,
	     weightProducer<TreeType>* wp = NULL ){

    ntuple = ntuple_;
    branchname = branchname_;
    weightProd = wp;
    weightBranch="";
    lumi = 0.;
    histo = new TH1F(branchname+"_"+histoname,branchname+"_"+histoname,nBins,lowEdge,highEdge);
    if( weightProd != NULL )
      histo->Sumw2();
    
  };

  fillHisto( TreeType* ntuple_ , 
	     int nBins = 20 , 
	     float lowEdge = 500. , float highEdge = 1500. , 
	     TString histoname = "default" ,
	     TString branchname_= "HT" ,
	     TString weightBranch_ = "lheWeight" ,
	     double lumi_ = 10000. ){

    ntuple = ntuple_;
    branchname = branchname_;
    weightBranch = weightBranch_;
    lumi = lumi_;
    weightProd = NULL;
    histo = new TH1F(branchname+"_"+histoname,branchname+"_"+histoname,nBins,lowEdge,highEdge);
    if( weightProd != NULL || weightBranch != "" )
      histo->Sumw2();
    try{
      if( ntuple->fChain->GetLeaf(weightBranch)==NULL ) throw weightBranch;
    }catch( TString wb ){
      std::cout << "Exception caught in fillHisto::fillHisto()" << std::endl;
      std::cout << "no branch, " << wb << " was found in tree." << std::endl;
      assert(0);
    }
  };

  fillHisto( TreeType* ntuple_ , 
	     std::vector<string> args ,
	     weightProducer<TreeType>* weightProd = NULL ){

    ntuple = ntuple_;
    
    if( args.size() == 5 ){
      fillHisto( ntuple_ , stoi( args[0] ) , stof( args[1] ) , stof( args[2] ) , args[3] , args[4] , weightProd );
    }else{
      assert(0);
    }
    
  };

  bool process( ) override {
    
    if( weightProd == NULL && weightBranch == "" )
      histo->Fill( ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() );
    else if( weightBranch != "" && weightProd == NULL )
      histo->Fill( ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() , ntuple->fChain->GetLeaf( weightBranch.Data() )->GetValue()*lumi );
    else
      histo->Fill( ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() , weightProd->weight );

    return true;
  };

};

#endif
