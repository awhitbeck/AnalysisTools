#!/bin/sh

source /cvmfs/cms.cern.ch/cmsset_default.sh

hadd -f HTvalidation.root `xrdfsls -u /store/user/awhitbe1/DissectingJetsPlusMET/analysis/ | grep outFile | grep \.root`
python stackPlots.py -s QCD -f HTvalidation.root
python stackPlots.py -s Wjets -f HTvalidation.root
python stackPlots.py -s znunu -f HTvalidation.root
python stackPlots.py -s ttbar -f HTvalidation.root

scp *Stack.png whitbeck@lxplus.cern.ch:www/.