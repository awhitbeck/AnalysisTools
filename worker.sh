#!/bin/sh

source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_7_4_2
cd CMSSW_7_4_2/src

eval `scramv1 runtime -sh`

pwd

echo "this is a crazy fucking thing!"

git clone https://github.com/awhitbeck/AnalysisTools.git

ls 
ls AnalysisTools

cd AnalysisTools
g++ `root-config --cflags --glibs` test.C -o test.exe

./test.exe $1

xrdcp outFile_$1.root /eos/uscms/store/user/awhitbe1/outFile_$1.root