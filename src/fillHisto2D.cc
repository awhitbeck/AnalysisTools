#ifndef FILLHISTO2D
#define FILLHISTO2D

#include "filler.h"
#include "RA2bUtils/src/weightProducer.cc"
#include <iostream>
#include <string>
#include <cassert>

#include "TLeaf.h"
#include "TString.h"

using namespace std;

template <class TreeType> class fillHisto2D : public filler<TreeType> {

public : 

  TString branchnameX;
  TString branchnameY;
  weightProducer<TreeType>* weightProd;
  //processor<TreeType>* weightProd;
  TH2F* histo;
  TreeType* ntuple;
  TString weightBranch;
  double lumi;

  fillHisto2D()
    : filler<TreeType>("fillHisto2D"){
    ntuple = 0;
    histo = new TH2F("test","test",20,500.,1500.,20,500.,1500.);
  };
  
  fillHisto2D( TreeType* ntuple_ , 
	     TString branchnameX_= "HT" ,
	     int nBinsX = 20 , 
	     float lowEdgeX = 500. , float highEdgeX = 1500. , 
	     TString branchnameY_= "MHT" ,
	     int nBinsY = 20 , 
	     float lowEdgeY = 200. , float highEdgeY = 800. , 
	     TString histoname = "default" ,
	     weightProducer<TreeType>* wp = NULL )
    : filler<TreeType>("fillHisto2D_"+histoname){

    ntuple = ntuple_;
    branchnameX = branchnameX_;
    branchnameY = branchnameY_;
    weightProd = wp;
    weightBranch="";
    lumi = 0.;
    histo = new TH2F(branchnameX+"_"+branchnameY+"_"+histoname,branchnameX+"_"+branchnameY+"_"+histoname,nBinsX,lowEdgeX,highEdgeX,nBinsY,lowEdgeY,highEdgeY);
    if( weightProd != NULL )
      histo->Sumw2();
    
    ntuple->fChain->SetBranchStatus(branchnameX.Data(),1);
    ntuple->fChain->SetBranchStatus(branchnameY.Data(),1);
    if( ntuple->fChain->GetLeaf( branchnameX.Data() ) == NULL 
	|| ntuple->fChain->GetLeaf( branchnameX.Data() ) == NULL ) 
      assert(0);
    
  };

  fillHisto2D( TreeType* ntuple_ , 
	     TString branchnameX_= "HT" ,
	     int nBinsX = 20 , 
	     float lowEdgeX = 500. , float highEdgeX = 1500. , 
	     TString branchnameY_= "MHT" ,
	     int nBinsY = 20 , 
	     float lowEdgeY = 200. , float highEdgeY = 800. , 
	     TString histoname = "default" ,
	     TString weightBranch_ = "lheWeight" ,
	     double lumi_ = 10000. ){

    ntuple = ntuple_;
    branchnameX = branchnameX_;
    branchnameY = branchnameY_;
    weightBranch = weightBranch_;
    lumi = lumi_;
    weightProd = NULL;
    histo = new TH2F(branchnameX+"_"+branchnameY+"_"+histoname,branchnameX+"_"+branchnameY+"_"+histoname,nBinsX,lowEdgeX,highEdgeX,nBinsY,lowEdgeY,highEdgeY);
    if( weightProd != NULL || weightBranch != "" )
      histo->Sumw2();
    try{
      if( ntuple->fChain->GetLeaf(weightBranch)==NULL ) throw weightBranch;
    }catch( TString wb ){
      std::cout << "Exception caught in fillHisto2D::fillHisto2D()" << std::endl;
      std::cout << "no branch, " << wb << " was found in tree." << std::endl;
      assert(0);
    }
  };
  
  fillHisto2D( const fillHisto2D& rhs , TString histoName = "default" ){

    branchnameX = rhs.branchnameX;
    branchnameY = rhs.branchnameY;
    weightProd = rhs.weightProd;
    histo = new TH2F(*rhs.histo);
    histo->SetNameTitle(histoName,histoName);
    ntuple = rhs.ntuple;
    weightBranch = rhs.weightBranch;
    lumi = rhs.lumi;

  }

  bool process( ) override {
    
    if( weightProd == NULL && weightBranch == "" ){
      //cout << branchname.Data() << " " << ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() << endl;
      histo->Fill( ntuple->fChain->GetLeaf( branchnameX.Data() )->GetValue() , 
		   ntuple->fChain->GetLeaf( branchnameY.Data() )->GetValue() );
    }else if( weightBranch != "" && weightProd == NULL ){
      //cout << branchname.Data() << " " << ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() << " weight: " << ntuple->fChain->GetLeaf( weightBranch.Data() )->GetValue()*lumi << endl;
      histo->Fill( ntuple->fChain->GetLeaf( branchnameX.Data() )->GetValue() , 
		   ntuple->fChain->GetLeaf( branchnameY.Data() )->GetValue() , 
		   ntuple->fChain->GetLeaf( weightBranch.Data() )->GetValue()*lumi );
    }else{
      //cout << branchname.Data() << " " << ntuple->fChain->GetLeaf( branchname.Data() )->GetValue() << " weight: " << weightProd->weight << endl;
      histo->Fill( ntuple->fChain->GetLeaf( branchnameX.Data() )->GetValue() , 
		   ntuple->fChain->GetLeaf( branchnameY.Data() )->GetValue() , 
		   weightProd->weight );
    }

    return true;

  };

  /*
  void postProcess( ) override {
    histo->Write();
  };
  */

};

#endif
