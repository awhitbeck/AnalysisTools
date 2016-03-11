#!/bin/python

from ROOT import *
gROOT.SetBatch(True)
import os
from stackPlots import *
from samples import *

gROOT.ProcessLine(".L ~/tdrstyle.C")
gROOT.ProcessLine("setTDRStyle()")

samples = [ "znunu" , "ttbar" , "Wjets" , "QCD" ]
vars = [ "HT" , "MHT" , "MET" , "mT2" , "mT2_zeroMass" , 
         "alphaT" , "alphaT_dHThemi" , "mRazor" , "dRazor" , 
         "mEff" , "NJets" , "NLeptons" , "dPhi" , 
         "dEta" , "sumJetMass" , "leadJetPt", "baselineYields"
         ]

for s in allSig : 
    s.norm=True
    s.stack=False

for s in allBkg:
    s.norm=True
    s.stack=False
    s.lineColor=s.fillColor
    s.fillColor=0


can = TCanvas("can","can",500,500)
for var in vars : 
    
    #stackPlots(sampleChoices=allsamples , inputFile="genericPlotter.root" , x=var)
    f = TFile("genericPlotter.root")
    leg = TLegend(0.6,0.6,0.9,0.9)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)

    first = True
    max=0
    for s in allsamples : 
        s.histo = f.Get(var+"_"+s.histoTag)
        if s.histo == None : continue
        s.histo.Scale(1./s.histo.Integral())
        if s.histo.GetMaximum() > max : 
            max = s.histo.GetMaximum()
        s.setStyle()
        if first : 
            s.histo.Draw("HIST")
            first=False
        else : 
            s.histo.Draw("HIST,SAME")
        leg.AddEntry(s.histo,s.legLabel,"f")
        
    allsamples[0].histo.SetMaximum(max*1.5)

    leg.Draw()
    can.SaveAs("{0}_compareShapes.png".format(var))
