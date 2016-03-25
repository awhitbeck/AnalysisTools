#!/bin/python

from ROOT import *
gROOT.SetBatch(True)
import os
from stackPlots import *
from samples import *

#os.system("source /cvmfs/cms.cern.ch/cmsset_default.sh")
#os.system("hadd -f genericPlotter.root `xrdfsls -u /store/user/awhitbe1/DissectingJetsPlusMET/analysis/ | grep genericPlotter | grep \.root`")

gROOT.ProcessLine(".L ~/tdrstyle.C")
gROOT.ProcessLine("setTDRStyle()")

samples = [ "znunu" , "ttbar" , "Wjets" , "QCD" ]
vars = [ "HT" , "MHT" , "MET" , "mT2" , "mT2_zeroMass" , 
         "alphaT" , "alphaT_dHThemi" , "mRazor" , "dRazor" , 
         "mEff" , "NJets" , "NLeptons" , "dPhi" , 
         "dEta" , "sumJetMass" , "leadJetPt", "baselineYields"
         ]

can = TCanvas("can","can",500,500)
for var in vars : 
    stackPlots(sampleChoices=allsamples , inputFile="genericPlotter.root" , x=var )

    can.SaveAs("{0}_allStack.png".format(var))
    can.SetLogy()
    can.SaveAs("{0}_allStackLogY.png".format(var))

#for sample in samples :
#    stackPlots( sample , "dPhiTests.root" , "baselineYields" )

os.system("scp *Stack*.png whitbeck@lxplus.cern.ch:www/DissectingJetsMET/1DplotsNormalized/RA2bBaseline/.")

