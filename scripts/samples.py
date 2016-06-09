#!/bin/python
from ROOT import *
from stackPlots import *

## - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
## Background samples and their drawing conventions
## - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
QCD = plotterInput(fillColor_=kGreen+1,histoTag_="QCD",legLabel_="QCD",stack_=True)
znunu = plotterInput(fillColor_=kBlue+1,histoTag_="znunu",legLabel_="Z(#nu#nu)",stack_=True)
Wjets = plotterInput(fillColor_=kCyan+1,histoTag_="Wjets",legLabel_="W(l#nu)",stack_=True)
ttbar = plotterInput(fillColor_=kMagenta+1,histoTag_="ttbar",legLabel_="t#bar{t}",stack_=True)

allBkg = [QCD,znunu,Wjets,ttbar]

## - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
## Signal samples and their drawing conventions
## - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
GjN1_GjN1_1000 = plotterInput(lineColor_=kRed+0,histoTag_="GjN1_GjN1_1000",legLabel_="2 partons",stack_=False)
GjN1_GjjN1_1000 = plotterInput(lineColor_=kRed+0,histoTag_="GjN1_GjjN1_1000",legLabel_="3 partons",stack_=False)
GjjN1_GjjN1_1000 = plotterInput(lineColor_=kRed+2,histoTag_="GjjN1_GjjN1_1000",legLabel_="4 partons",stack_=False)
GjjN1_GjjjN1_1000 = plotterInput(lineColor_=kRed+1,histoTag_="GjjN1_GjjjN1_1000",legLabel_="5 partons",stack_=False)
GjjN1_GjjjN1_1000.lineStyle=2
GjjjN1_GjjjN1_1000 = plotterInput(lineColor_=kRed+0,histoTag_="GjjjN1_GjjjN1_1000",legLabel_="6 partons",stack_=False)
GjjjN1_GjjjN1_1000.lineStyle=2
GjjjN1_GjjjjN1_1000 = plotterInput(lineColor_=kOrange+1,histoTag_="GjjjN1_GjjjjN1_1000",legLabel_="7 partons",stack_=False)
GjjjjN1_GjjjjN1_1000 = plotterInput(lineColor_=kRed+2,histoTag_="GjjjjN1_GjjjjN1_1000",legLabel_="8 partons",stack_=False)
GjjjjN1_GjjjjN1_1000.lineStyle=1

GjN1_GjN1_1000_compressed = plotterInput(lineColor_=kRed+0,lineStyle_=2,histoTag_="GjN1_GjN1_1000_compressed",legLabel_="2 partons, comp.",stack_=False)
GjjjjN1_GjjjjN1_1000_compressed = plotterInput(lineColor_=kRed+2,lineStyle_=2,histoTag_="GjjjjN1_GjjjjN1_1000_compressed",legLabel_="8 partons, comp.",stack_=False)

allSig = [GjN1_GjN1_1000,GjN1_GjjN1_1000,GjjN1_GjjN1_1000,GjjN1_GjjjN1_1000,
         GjjjN1_GjjjN1_1000,GjjjN1_GjjjjN1_1000,GjjjjN1_GjjjjN1_1000]

for s in allSig : 
    s.lineWidth=3

compuncompSig = [GjN1_GjN1_1000,
                 GjjjjN1_GjjjjN1_1000,
                 GjN1_GjN1_1000_compressed,
                 GjjjjN1_GjjjjN1_1000_compressed]

evenSig = [GjN1_GjN1_1000,GjjN1_GjjN1_1000,
          GjjjN1_GjjjN1_1000,GjjjjN1_GjjjjN1_1000]

oddSig = [GjN1_GjjN1_1000,GjjN1_GjjjN1_1000,GjjjN1_GjjjjN1_1000]

allsamples = allBkg+evenSig

