#!/bin/python

import os
from stackPlots import *

#os.system("source /cvmfs/cms.cern.ch/cmsset_default.sh")
#os.system("hadd -f genericPlotter.root `xrdfsls -u /store/user/awhitbe1/DissectingJetsPlusMET/analysis/ | grep genericPlotter | grep \.root`")

samples = [ "znunu" , 
            "ttbar" , 
            "Wjets" , 
            "QCD" ]
vars = [ "HT" , 
         "MHT" , 
         "MET" , 
         "mT2" , 
         "alphaT" , 
         "mRazor" , 
         "dRazor" , 
         "mEff" , 
         "NJets" , 
         "NLeptons" , 
         "dPhi" , 
         #"dPhi1" , 
         #"dPhi2" , 
         #"dPhi3" , 
         #"dPhi4" , 
         "dEta" , 
         "sumJetMass" , 
         "leadJetPt",
         "baseline4JetYields"
         ]

for var in vars : 
    stackPlots(sampleChoice="QCD" , inputFile="genericPlotter4Jets_nodPhi.root" , x=var )

#for sample in samples :
#    for var in vars :
#        stackPlots( sample , "dPhiTests.root" , var )

os.system("scp *Stack*.png whitbeck@lxplus.cern.ch:www/.")
