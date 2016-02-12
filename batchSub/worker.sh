#!/bin/sh

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_7_4_2
cd CMSSW_7_4_2/src

eval `scramv1 runtime -sh`

pwd

git clone https://github.com/awhitbeck/AnalysisTools.git
outputDir=$(git rev-parse origin/master)

cd AnalysisTools
g++ `root-config --cflags --glibs` -I./src/ -I./test/ test/genericPlotter4Jets.cc -o test/genericPlotter4Jets.exe
ls
echo "RUNNING ANALYSIS"
./test/genericPlotter4Jets.exe $1
ls
echo "COPYING OUTPUT"
#eosls /store/user/awhitbe1/GMSBstudies/skims/
xrdcp genericPlotter4Jets_${1}.root root://cmseos.fnal.gov//store/user/awhitbe1/DissectingJetsPlusMET/analysis/genericPlotter4Jets_${1}.root
