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
GjN1_GjN1_1000 = plotterInput(lineColor_=kRed+0,histoTag_="GjN1_GjN1_1000",legLabel_="#tilde{g}(j#tilde{#chi}^{0}),#tilde{g}(j#tilde{#chi}^{0})",stack_=False)
GjN1_GjjN1_1000 = plotterInput(lineColor_=kRed+0,histoTag_="GjN1_GjjN1_1000",legLabel_="#tilde{g}(j#tilde{#chi}^{0}),#tilde{g}(jj#tilde{#chi}^{0})",stack_=False)
GjjN1_GjjN1_1000 = plotterInput(lineColor_=kRed+2,histoTag_="GjjN1_GjjN1_1000",legLabel_="#tilde{g}(jj#tilde{#chi}^{0}),#tilde{g}(jj#tilde{#chi}^{0})",stack_=False)
GjjN1_GjjjN1_1000 = plotterInput(lineColor_=kRed+1,histoTag_="GjjN1_GjjjN1_1000",legLabel_="#tilde{g}(jj#tilde{#chi}^{0}),#tilde{g}(jjj#tilde{#chi}^{0})",stack_=False)
GjjN1_GjjjN1_1000.lineStyle=2
GjjjN1_GjjjN1_1000 = plotterInput(lineColor_=kRed+0,histoTag_="GjjjN1_GjjjN1_1000",legLabel_="#tilde{g}(jjj#tilde{#chi}^{0}),#tilde{g}(jjj#tilde{#chi}^{0})",stack_=False)
GjjjN1_GjjjN1_1000.lineStyle=2
GjjjN1_GjjjjN1_1000 = plotterInput(lineColor_=kOrange+1,histoTag_="GjjjN1_GjjjjN1_1000",legLabel_="#tilde{g}(jjj#tilde{#chi}^{0}),#tilde{g}(jjjj#tilde{#chi}^{0})",stack_=False)
GjjjjN1_GjjjjN1_1000 = plotterInput(lineColor_=kRed+2,histoTag_="GjjjjN1_GjjjjN1_1000",legLabel_="#tilde{g}(jjjj#tilde{#chi}^{0}),#tilde{g}(jjjj#tilde{#chi}^{0})",stack_=False)
GjjjjN1_GjjjjN1_1000.lineStyle=2

allSig = [GjN1_GjN1_1000,GjN1_GjjN1_1000,GjjN1_GjjN1_1000,GjjN1_GjjjN1_1000,
         GjjjN1_GjjjN1_1000,GjjjN1_GjjjjN1_1000,GjjjjN1_GjjjjN1_1000]

for s in allSig : 
    s.lineWidth=3

evenSig = [GjN1_GjN1_1000,GjjN1_GjjN1_1000,
          GjjjN1_GjjjN1_1000,GjjjjN1_GjjjjN1_1000]

oddSig = [GjN1_GjjN1_1000,GjjN1_GjjjN1_1000,GjjjN1_GjjjjN1_1000]

allsamples = allBkg+evenSig

