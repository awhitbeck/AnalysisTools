#!/bin/sh

source /cvmfs/cms.cern.ch/cmsset_default.sh

hadd -f genericPlotter.root `xrdfsls -u /store/user/awhitbe1/DissectingJetsPlusMET/analysis/ | grep genericPlotter | grep \.root`
python stackPlots.py -s QCD -f genericPlotter.root
python stackPlots.py -s Wjets -f genericPlotter.root
python stackPlots.py -s znunu -f genericPlotter.root
python stackPlots.py -s ttbar -f genericPlotter.root

scp *Stack.png whitbeck@lxplus.cern.ch:www/.