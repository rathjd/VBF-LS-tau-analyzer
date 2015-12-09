#!/bin/sh

source /afs/desy.de/user/d/dmarconi/VBF-LS-tau/setenv.sh

python /nfs/dust/cms/user/dmarconi/workdir/VBFsignalSamples_Madgraph/CMSSW_7_4_14/src/miniAODanalyzer/miniaodreader_genparticles.py $1 $2
