#ifndef ANALYZER_H
#define ANALYZER_H
//-----------------------------------------------------------------------------
// File:        analyzer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Wed Dec 18 18:04:53 2013 by mkanalyzer.py
// Author:      Daniele Marconi
//-----------------------------------------------------------------------------
// -- System

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cmath>

#include "analyzerutil.h"
#include "treestream.h"
#include "pdg.h"

// -- Root

#include "TROOT.h"
#include "TApplication.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TKey.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"

namespace evt {
//-----------------------------------------------------------------------------
// --- Declare variables
//-----------------------------------------------------------------------------
double	GenRunInfoProduct_crossSection;
double	GenRunInfoProduct_filterEfficiency;
double	GenRunInfoProduct_internalXSec_value;
std::vector<int>	PileupSummaryInfo_getBunchCrossing(10,0);
std::vector<int>	PileupSummaryInfo_getPU_NumInteractions(10,0);
std::vector<int>	ak5GenJets_charge(100,0);
std::vector<double>	ak5GenJets_eta(100,0);
std::vector<double>	ak5GenJets_mass(100,0);
std::vector<double>	ak5GenJets_phi(100,0);
std::vector<double>	ak5GenJets_pt(100,0);
int	eventhelper_bunchCrossing;
int	eventhelper_event;
int	eventhelper_isRealData;
int	eventhelper_luminosityBlock;
int	eventhelper_orbitNumber;
int	eventhelper_run;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v1;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v10;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v11;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v12;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v13;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v14;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v15;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v16;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v17;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v18;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v19;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v2;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v20;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v3;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v4;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v5;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v6;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v7;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v8;
int	triggerresultshelper_prescale_HLT_DiPFJetAve140_v9;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v1;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v10;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v11;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v12;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v13;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v14;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v15;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v16;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v17;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v18;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v19;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v2;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v20;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v3;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v4;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v5;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v6;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v7;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v8;
int	triggerresultshelper_prescale_HLT_DiPFJetAve200_v9;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v1;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v10;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v11;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v12;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v13;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v14;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v15;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v16;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v17;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v18;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v19;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v2;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v20;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v3;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v4;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v5;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v6;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v7;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v8;
int	triggerresultshelper_prescale_HLT_DiPFJetAve260_v9;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v1;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v10;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v11;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v12;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v13;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v14;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v15;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v16;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v17;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v18;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v19;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v2;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v20;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v3;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v4;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v5;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v6;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v7;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v8;
int	triggerresultshelper_prescale_HLT_DiPFJetAve320_v9;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v1;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v10;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v11;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v12;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v13;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v14;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v15;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v16;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v17;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v18;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v19;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v2;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v20;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v3;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v4;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v5;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v6;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v7;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v8;
int	triggerresultshelper_prescale_HLT_DiPFJetAve400_v9;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v1;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v10;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v11;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v12;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v13;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v14;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v15;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v16;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v17;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v18;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v19;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v2;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v20;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v3;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v4;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v5;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v6;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v7;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v8;
int	triggerresultshelper_prescale_HLT_DiPFJetAve40_v9;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v1;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v10;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v11;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v12;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v13;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v14;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v15;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v16;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v17;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v18;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v19;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v2;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v20;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v3;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v4;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v5;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v6;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v7;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v8;
int	triggerresultshelper_prescale_HLT_DiPFJetAve80_v9;
int	triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3;
int	triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4;
int	triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2;
int	triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3;
int	triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4;
int	triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v1;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v10;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v11;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v12;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v13;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v14;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v15;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v16;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v17;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v18;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v19;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v2;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v20;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v3;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v4;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v5;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v7;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v8;
int	triggerresultshelper_value_HLT_DiPFJetAve140_v9;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v1;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v10;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v11;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v12;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v13;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v14;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v15;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v16;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v17;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v18;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v19;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v2;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v20;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v3;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v4;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v5;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v7;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v8;
int	triggerresultshelper_value_HLT_DiPFJetAve200_v9;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v1;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v10;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v11;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v12;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v13;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v14;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v15;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v16;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v17;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v18;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v19;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v2;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v20;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v3;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v4;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v5;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v7;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v8;
int	triggerresultshelper_value_HLT_DiPFJetAve260_v9;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v1;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v10;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v11;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v12;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v13;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v14;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v15;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v16;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v17;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v18;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v19;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v2;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v20;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v3;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v4;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v5;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v7;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v8;
int	triggerresultshelper_value_HLT_DiPFJetAve320_v9;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v1;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v10;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v11;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v12;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v13;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v14;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v15;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v16;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v17;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v18;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v19;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v2;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v20;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v3;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v4;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v5;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v7;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v8;
int	triggerresultshelper_value_HLT_DiPFJetAve400_v9;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v1;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v10;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v11;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v12;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v13;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v14;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v15;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v16;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v17;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v18;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v19;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v2;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v20;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v3;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v4;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v5;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v7;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v8;
int	triggerresultshelper_value_HLT_DiPFJetAve40_v9;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v1;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v10;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v11;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v12;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v13;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v14;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v15;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v16;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v17;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v18;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v19;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v2;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v20;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v3;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v4;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v5;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v6;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v7;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v8;
int	triggerresultshelper_value_HLT_DiPFJetAve80_v9;
int	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3;
int	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4;
int	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2;
int	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3;
int	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4;
int	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6;
int	nPileupSummaryInfo;
int	nak5GenJets;
int	npatElectron;
int	npatJet;
int	npatMET;
int	npatMuon;
int	npatTau;
std::vector<size_t>	patTau_signalPFChargedHadrCands_size(200,0);
int	nrecoGenParticleHelper;
int	nrecoGenParticleHelperPlus;
int	nrecoGsfElectron;
int	nrecoPFMET;
int	nrecoPFMET1;
int	nrecoVertex;
std::vector<float>	patElectron_deltaEtaSuperClusterTrackAtVtx(200,0);
std::vector<float>	patElectron_deltaPhiSuperClusterTrackAtVtx(200,0);
std::vector<float>	patElectron_dr04EcalRecHitSumEt(200,0);
std::vector<float>	patElectron_dr04TkSumPt(200,0);
std::vector<float>	patElectron_eSuperClusterOverP(200,0);
std::vector<double>	patElectron_energy(200,0);
std::vector<double>	patElectron_et(200,0);
std::vector<double>	patElectron_eta(200,0);
std::vector<double>	patElectron_gsfTrack_d0(200,0);
std::vector<double>	patElectron_gsfTrack_dxy(200,0);
std::vector<double>	patElectron_gsfTrack_dz(200,0);
std::vector<float>	patElectron_hadronicOverEm(200,0);
std::vector<double>	patElectron_p(200,0);
std::vector<double>	patElectron_phi(200,0);
std::vector<double>	patElectron_pt(200,0);
std::vector<double>	patElectron_px(200,0);
std::vector<double>	patElectron_py(200,0);
std::vector<double>	patElectron_pz(200,0);
std::vector<float>	patElectron_scE1x5(200,0);
std::vector<float>	patElectron_scE2x5Max(200,0);
std::vector<float>	patElectron_scE5x5(200,0);
std::vector<float>	patElectron_sigmaIetaIeta(200,0);
std::vector<float>	patJet_HFEMEnergy(200,0);
std::vector<float>	patJet_HFEMEnergyFraction(200,0);
std::vector<int>	patJet_HFEMMultiplicity(200,0);
std::vector<float>	patJet_HFHadronEnergy(200,0);
std::vector<float>	patJet_HFHadronEnergyFraction(200,0);
std::vector<int>	patJet_HFHadronMultiplicity(200,0);
std::vector<float>	patJet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_combinedMVABJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_combinedSecondaryVertexBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_combinedSecondaryVertexMVABJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_impactParameterTagInfos(200,0);
std::vector<float>	patJet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos(200,0);
std::vector<float>	patJet_bDiscriminator_jetBProbabilityBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_jetProbabilityBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_negativeTrackCountingHighEffJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_negativeTrackCountingHighPurJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_secondaryVertexNegativeTagInfos(200,0);
std::vector<float>	patJet_bDiscriminator_secondaryVertexTagInfos(200,0);
std::vector<float>	patJet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_softElectronTagInfos(200,0);
std::vector<float>	patJet_bDiscriminator_softMuonBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_softMuonByIP3dBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_softMuonByPtBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_softMuonTagInfos(200,0);
std::vector<float>	patJet_bDiscriminator_trackCountingHighEffBJetTags(200,0);
std::vector<float>	patJet_bDiscriminator_trackCountingHighPurBJetTags(200,0);
std::vector<int>	patJet_charge(200,0);
std::vector<float>	patJet_chargedEmEnergyFraction(200,0);
std::vector<float>	patJet_chargedHadronEnergyFraction(200,0);
std::vector<int>	patJet_chargedHadronMultiplicity(200,0);
std::vector<float>	patJet_electronEnergy(200,0);
std::vector<float>	patJet_electronEnergyFraction(200,0);
std::vector<int>	patJet_electronMultiplicity(200,0);
std::vector<double>	patJet_energy(200,0);
std::vector<double>	patJet_et(200,0);
std::vector<double>	patJet_eta(200,0);
std::vector<float>	patJet_muonEnergy(200,0);
std::vector<float>	patJet_muonEnergyFraction(200,0);
std::vector<float>	patJet_neutralEmEnergyFraction(200,0);
std::vector<float>	patJet_neutralHadronEnergy(200,0);
std::vector<float>	patJet_neutralHadronEnergyFraction(200,0);
std::vector<int>	patJet_neutralHadronMultiplicity(200,0);
std::vector<size_t>	patJet_numberOfDaughters(200,0);
std::vector<double>	patJet_p(200,0);
std::vector<double>	patJet_phi(200,0);
std::vector<float>	patJet_photonEnergy(200,0);
std::vector<float>	patJet_photonEnergyFraction(200,0);
std::vector<int>	patJet_photonMultiplicity(200,0);
std::vector<double>	patJet_pt(200,0);
std::vector<double>	patJet_px(200,0);
std::vector<double>	patJet_py(200,0);
std::vector<double>	patJet_pz(200,0);
std::vector<double>	patMET_energy(200,0);
std::vector<double>	patMET_et(200,0);
std::vector<double>	patMET_eta(200,0);
std::vector<double>	patMET_p(200,0);
std::vector<double>	patMET_phi(200,0);
std::vector<double>	patMET_pt(200,0);
std::vector<double>	patMET_px(200,0);
std::vector<double>	patMET_py(200,0);
std::vector<double>	patMET_pz(200,0);
std::vector<double>	patMuon_energy(200,0);
std::vector<double>	patMuon_et(200,0);
std::vector<double>	patMuon_eta(200,0);
std::vector<int>	patMuon_globalTrack_hitPattern_numberOfValidMuonHits(200,0);
std::vector<double>	patMuon_globalTrack_normalizedChi2(200,0);
std::vector<double>	patMuon_innerTrack_dxy(200,0);
std::vector<double>	patMuon_innerTrack_dz(200,0);
std::vector<int>	patMuon_innerTrack_hitPattern_numberOfValidPixelHits(200,0);
std::vector<int>	patMuon_innerTrack_hitPattern_pixelLayersWithMeasurement(200,0);
std::vector<double>	patMuon_innerTrack_normalizedChi2(200,0);
std::vector<int>	patMuon_isGlobalMuon(200,0);
std::vector<int>	patMuon_isPFMuon(200,0);
std::vector<int>	patMuon_isTrackerMuon(200,0);
std::vector<double>	patMuon_muonBestTrack_dxy(200,0);
std::vector<double>	patMuon_muonBestTrack_dz(200,0);
std::vector<int>	patMuon_numberOfMatchedStations(200,0);
std::vector<double>	patMuon_p(200,0);
std::vector<float>	patMuon_pfIsolationR03_sumChargedHadronPt(200,0);
std::vector<float>	patMuon_pfIsolationR03_sumChargedParticlePt(200,0);
std::vector<float>	patMuon_pfIsolationR03_sumNeutralHadronEt(200,0);
std::vector<float>	patMuon_pfIsolationR03_sumNeutralHadronEtHighThreshold(200,0);
std::vector<float>	patMuon_pfIsolationR03_sumPUPt(200,0);
std::vector<float>	patMuon_pfIsolationR03_sumPhotonEt(200,0);
std::vector<float>	patMuon_pfIsolationR03_sumPhotonEtHighThreshold(200,0);
std::vector<float>	patMuon_pfIsolationR04_sumChargedHadronPt(200,0);
std::vector<float>	patMuon_pfIsolationR04_sumChargedParticlePt(200,0);
std::vector<float>	patMuon_pfIsolationR04_sumNeutralHadronEt(200,0);
std::vector<float>	patMuon_pfIsolationR04_sumNeutralHadronEtHighThreshold(200,0);
std::vector<float>	patMuon_pfIsolationR04_sumPUPt(200,0);
std::vector<float>	patMuon_pfIsolationR04_sumPhotonEt(200,0);
std::vector<float>	patMuon_pfIsolationR04_sumPhotonEtHighThreshold(200,0);
std::vector<double>	patMuon_phi(200,0);
std::vector<double>	patMuon_pt(200,0);
std::vector<double>	patMuon_px(200,0);
std::vector<double>	patMuon_py(200,0);
std::vector<double>	patMuon_pz(200,0);
std::vector<int>	patTau_charge(200,0);
std::vector<double>	patTau_energy(200,0);
std::vector<double>	patTau_et(200,0);
std::vector<double>	patTau_eta(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_energy(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_et(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_eta(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_mass(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_massSqr(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_mt(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_mtSqr(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_p(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_phi(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_pt(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_px(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_py(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_pz(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_rapidity(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_theta(200,0);
std::vector<double>	patTau_leadPFChargedHadrCand_y(200,0);
std::vector<double>	patTau_p(200,0);
std::vector<double>	patTau_phi(200,0);
std::vector<double>	patTau_pt(200,0);
std::vector<double>	patTau_px(200,0);
std::vector<double>	patTau_py(200,0);
std::vector<double>	patTau_pz(200,0);
std::vector<float>	patTau_tauID_againstElectronDeadECAL(200,0);
std::vector<float>	patTau_tauID_againstElectronLoose(200,0);
std::vector<float>	patTau_tauID_againstElectronLooseMVA5(200,0);
std::vector<float>	patTau_tauID_againstElectronMVA5category(200,0);
std::vector<float>	patTau_tauID_againstElectronMVA5raw(200,0);
std::vector<float>	patTau_tauID_againstElectronMedium(200,0);
std::vector<float>	patTau_tauID_againstElectronMediumMVA5(200,0);
std::vector<float>	patTau_tauID_againstElectronTight(200,0);
std::vector<float>	patTau_tauID_againstElectronTightMVA5(200,0);
std::vector<float>	patTau_tauID_againstElectronVLooseMVA5(200,0);
std::vector<float>	patTau_tauID_againstElectronVTightMVA5(200,0);
std::vector<float>	patTau_tauID_againstMuonLoose(200,0);
std::vector<float>	patTau_tauID_againstMuonLoose2(200,0);
std::vector<float>	patTau_tauID_againstMuonLoose3(200,0);
std::vector<float>	patTau_tauID_againstMuonLooseMVA(200,0);
std::vector<float>	patTau_tauID_againstMuonMVAraw(200,0);
std::vector<float>	patTau_tauID_againstMuonMedium(200,0);
std::vector<float>	patTau_tauID_againstMuonMedium2(200,0);
std::vector<float>	patTau_tauID_againstMuonMediumMVA(200,0);
std::vector<float>	patTau_tauID_againstMuonTight(200,0);
std::vector<float>	patTau_tauID_againstMuonTight2(200,0);
std::vector<float>	patTau_tauID_againstMuonTight3(200,0);
std::vector<float>	patTau_tauID_againstMuonTightMVA(200,0);
std::vector<float>	patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw(200,0);
std::vector<float>	patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits(200,0);
std::vector<float>	patTau_tauID_byIsolationMVA3newDMwLTraw(200,0);
std::vector<float>	patTau_tauID_byIsolationMVA3newDMwoLTraw(200,0);
std::vector<float>	patTau_tauID_byIsolationMVA3oldDMwLTraw(200,0);
std::vector<float>	patTau_tauID_byIsolationMVA3oldDMwoLTraw(200,0);
std::vector<float>	patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	patTau_tauID_byLooseIsolation(200,0);
std::vector<float>	patTau_tauID_byLooseIsolationMVA3newDMwLT(200,0);
std::vector<float>	patTau_tauID_byLooseIsolationMVA3newDMwoLT(200,0);
std::vector<float>	patTau_tauID_byLooseIsolationMVA3oldDMwLT(200,0);
std::vector<float>	patTau_tauID_byLooseIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	patTau_tauID_byMediumIsolationMVA3newDMwLT(200,0);
std::vector<float>	patTau_tauID_byMediumIsolationMVA3newDMwoLT(200,0);
std::vector<float>	patTau_tauID_byMediumIsolationMVA3oldDMwLT(200,0);
std::vector<float>	patTau_tauID_byMediumIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	patTau_tauID_byTightCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	patTau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	patTau_tauID_byTightIsolationMVA3newDMwLT(200,0);
std::vector<float>	patTau_tauID_byTightIsolationMVA3newDMwoLT(200,0);
std::vector<float>	patTau_tauID_byTightIsolationMVA3oldDMwLT(200,0);
std::vector<float>	patTau_tauID_byTightIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	patTau_tauID_byVLooseCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	patTau_tauID_byVLooseIsolationMVA3newDMwLT(200,0);
std::vector<float>	patTau_tauID_byVLooseIsolationMVA3newDMwoLT(200,0);
std::vector<float>	patTau_tauID_byVLooseIsolationMVA3oldDMwLT(200,0);
std::vector<float>	patTau_tauID_byVLooseIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	patTau_tauID_byVTightIsolationMVA3newDMwLT(200,0);
std::vector<float>	patTau_tauID_byVTightIsolationMVA3newDMwoLT(200,0);
std::vector<float>	patTau_tauID_byVTightIsolationMVA3oldDMwLT(200,0);
std::vector<float>	patTau_tauID_byVTightIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	patTau_tauID_byVVTightIsolationMVA3newDMwLT(200,0);
std::vector<float>	patTau_tauID_byVVTightIsolationMVA3newDMwoLT(200,0);
std::vector<float>	patTau_tauID_byVVTightIsolationMVA3oldDMwLT(200,0);
std::vector<float>	patTau_tauID_byVVTightIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	patTau_tauID_chargedIsoPtSum(200,0);
std::vector<float>	patTau_tauID_decayModeFinding(200,0);
std::vector<float>	patTau_tauID_decayModeFindingNewDMs(200,0);
std::vector<float>	patTau_tauID_decayModeFindingOldDMs(200,0);
std::vector<float>	patTau_tauID_neutralIsoPtSum(200,0);
std::vector<float>	patTau_tauID_puCorrPtSum(200,0);
std::vector<double>	patTau_vx(200,0);
std::vector<double>	patTau_vy(200,0);
std::vector<double>	patTau_vz(200,0);
double	recoBeamSpot_x0;
double	recoBeamSpot_y0;
double	recoBeamSpot_z0;
std::vector<int>	recoGenParticleHelperPlus_charge(100,0);
std::vector<double>	recoGenParticleHelperPlus_eta(100,0);
std::vector<int>	recoGenParticleHelperPlus_firstDaughter(100,0);
std::vector<int>	recoGenParticleHelperPlus_firstMother(100,0);
std::vector<int>	recoGenParticleHelperPlus_lastDaughter(100,0);
std::vector<int>	recoGenParticleHelperPlus_lastMother(100,0);
std::vector<double>	recoGenParticleHelperPlus_mass(100,0);
std::vector<int>	recoGenParticleHelperPlus_pdgId(100,0);
std::vector<double>	recoGenParticleHelperPlus_phi(100,0);
std::vector<double>	recoGenParticleHelperPlus_pt(100,0);
std::vector<int>	recoGenParticleHelperPlus_status(100,0);
std::vector<int>	recoGenParticleHelper_charge(100,0);
std::vector<double>	recoGenParticleHelper_eta(100,0);
std::vector<int>	recoGenParticleHelper_firstDaughter(100,0);
std::vector<int>	recoGenParticleHelper_firstMother(100,0);
std::vector<int>	recoGenParticleHelper_lastDaughter(100,0);
std::vector<int>	recoGenParticleHelper_lastMother(100,0);
std::vector<double>	recoGenParticleHelper_mass(100,0);
std::vector<int>	recoGenParticleHelper_pdgId(100,0);
std::vector<double>	recoGenParticleHelper_phi(100,0);
std::vector<double>	recoGenParticleHelper_pt(100,0);
std::vector<int>	recoGenParticleHelper_status(100,0);
std::vector<float>	recoGsfElectron_deltaEtaSuperClusterTrackAtVtx(200,0);
std::vector<float>	recoGsfElectron_deltaPhiSuperClusterTrackAtVtx(200,0);
std::vector<float>	recoGsfElectron_dr04EcalRecHitSumEt(200,0);
std::vector<float>	recoGsfElectron_dr04TkSumPt(200,0);
std::vector<float>	recoGsfElectron_eSuperClusterOverP(200,0);
std::vector<double>	recoGsfElectron_energy(200,0);
std::vector<double>	recoGsfElectron_et(200,0);
std::vector<double>	recoGsfElectron_eta(200,0);
std::vector<double>	recoGsfElectron_gsfTrack_d0(200,0);
std::vector<double>	recoGsfElectron_gsfTrack_dxy(200,0);
std::vector<double>	recoGsfElectron_gsfTrack_dz(200,0);
std::vector<float>	recoGsfElectron_hadronicOverEm(200,0);
std::vector<double>	recoGsfElectron_p(200,0);
std::vector<double>	recoGsfElectron_phi(200,0);
std::vector<double>	recoGsfElectron_pt(200,0);
std::vector<double>	recoGsfElectron_px(200,0);
std::vector<double>	recoGsfElectron_py(200,0);
std::vector<double>	recoGsfElectron_pz(200,0);
std::vector<float>	recoGsfElectron_scE1x5(200,0);
std::vector<float>	recoGsfElectron_scE2x5Max(200,0);
std::vector<float>	recoGsfElectron_scE5x5(200,0);
std::vector<float>	recoGsfElectron_sigmaIetaIeta(200,0);
std::vector<double>	recoPFMET1_energy(200,0);
std::vector<double>	recoPFMET1_et(200,0);
std::vector<double>	recoPFMET1_eta(200,0);
std::vector<double>	recoPFMET1_p(200,0);
std::vector<double>	recoPFMET1_phi(200,0);
std::vector<double>	recoPFMET1_pt(200,0);
std::vector<double>	recoPFMET1_px(200,0);
std::vector<double>	recoPFMET1_py(200,0);
std::vector<double>	recoPFMET1_pz(200,0);
std::vector<double>	recoPFMET_energy(200,0);
std::vector<double>	recoPFMET_et(200,0);
std::vector<double>	recoPFMET_eta(200,0);
std::vector<double>	recoPFMET_p(200,0);
std::vector<double>	recoPFMET_phi(200,0);
std::vector<double>	recoPFMET_pt(200,0);
std::vector<double>	recoPFMET_px(200,0);
std::vector<double>	recoPFMET_py(200,0);
std::vector<double>	recoPFMET_pz(200,0);
std::vector<int>	recoVertex_isFake(200,0);
std::vector<double>	recoVertex_ndof(200,0);
std::vector<double>	recoVertex_x(200,0);
std::vector<double>	recoVertex_y(200,0);
std::vector<double>	recoVertex_z(200,0);

//-----------------------------------------------------------------------------
// --- indexmap keeps track of which objects have been flagged for selection
// --- IMPORTANT: initialize must be called every event to clear selection
std::map<std::string, std::vector<int> > indexmap;
void initialize()
{
  for(std::map<std::string, std::vector<int> >::iterator
    item=indexmap.begin(); 
    item != indexmap.end();
	++item)
	item->second.clear();
}

void select(std::string objname)
{
  indexmap[objname] = std::vector<int>();
}

void select(std::string objname, int index)
{
  try
    {
      indexmap[objname].push_back(index);
    }
  catch (...)
    {
      std::cout << "*** perhaps you failed to call select for " 
                << objname << std::endl;
      assert(0);
    }
}

//-----------------------------------------------------------------------------
// --- Structs can be filled by calling fillObjects()
// --- after the call to stream.read(...)
//-----------------------------------------------------------------------------
struct PileupSummaryInfo_s
{
  int	getBunchCrossing;
  int	getPU_NumInteractions;
};
std::vector<PileupSummaryInfo_s> PileupSummaryInfo(10);

std::ostream& operator<<(std::ostream& os, const PileupSummaryInfo_s& o)
{
  char r[1024];
  os << "PileupSummaryInfo" << std::endl;
  sprintf(r, "  %-32s: %f\n", "getBunchCrossing", (double)o.getBunchCrossing); os << r;
  sprintf(r, "  %-32s: %f\n", "getPU_NumInteractions", (double)o.getPU_NumInteractions); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct ak5GenJets_s
{
  int	charge;
  double	pt;
  double	eta;
  double	phi;
  double	mass;
};
std::vector<ak5GenJets_s> ak5GenJets(100);

std::ostream& operator<<(std::ostream& os, const ak5GenJets_s& o)
{
  char r[1024];
  os << "ak5GenJets" << std::endl;
  sprintf(r, "  %-32s: %f\n", "charge", (double)o.charge); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct electron_s
{
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
  float	eSuperClusterOverP;
  float	deltaEtaSuperClusterTrackAtVtx;
  float	deltaPhiSuperClusterTrackAtVtx;
  float	sigmaIetaIeta;
  float	scE1x5;
  float	scE2x5Max;
  float	scE5x5;
  float	hadronicOverEm;
  float	dr04TkSumPt;
  float	dr04EcalRecHitSumEt;
  double	gsfTrack_dxy;
  double	gsfTrack_d0;
  double	gsfTrack_dz;
};
std::vector<electron_s> electron(200);

std::ostream& operator<<(std::ostream& os, const electron_s& o)
{
  char r[1024];
  os << "electron" << std::endl;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "eSuperClusterOverP", (double)o.eSuperClusterOverP); os << r;
  sprintf(r, "  %-32s: %f\n", "deltaEtaSuperClusterTrackAtVtx", (double)o.deltaEtaSuperClusterTrackAtVtx); os << r;
  sprintf(r, "  %-32s: %f\n", "deltaPhiSuperClusterTrackAtVtx", (double)o.deltaPhiSuperClusterTrackAtVtx); os << r;
  sprintf(r, "  %-32s: %f\n", "sigmaIetaIeta", (double)o.sigmaIetaIeta); os << r;
  sprintf(r, "  %-32s: %f\n", "scE1x5", (double)o.scE1x5); os << r;
  sprintf(r, "  %-32s: %f\n", "scE2x5Max", (double)o.scE2x5Max); os << r;
  sprintf(r, "  %-32s: %f\n", "scE5x5", (double)o.scE5x5); os << r;
  sprintf(r, "  %-32s: %f\n", "hadronicOverEm", (double)o.hadronicOverEm); os << r;
  sprintf(r, "  %-32s: %f\n", "dr04TkSumPt", (double)o.dr04TkSumPt); os << r;
  sprintf(r, "  %-32s: %f\n", "dr04EcalRecHitSumEt", (double)o.dr04EcalRecHitSumEt); os << r;
  sprintf(r, "  %-32s: %f\n", "gsfTrack_dxy", (double)o.gsfTrack_dxy); os << r;
  sprintf(r, "  %-32s: %f\n", "gsfTrack_d0", (double)o.gsfTrack_d0); os << r;
  sprintf(r, "  %-32s: %f\n", "gsfTrack_dz", (double)o.gsfTrack_dz); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct jet_s
{
  int	charge;
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
  float	neutralHadronEnergy;
  float	chargedHadronEnergyFraction;
  float	neutralHadronEnergyFraction;
  float	chargedEmEnergyFraction;
  float	neutralEmEnergyFraction;
  float	photonEnergy;
  float	photonEnergyFraction;
  float	electronEnergy;
  float	electronEnergyFraction;
  float	muonEnergy;
  float	muonEnergyFraction;
  float	HFHadronEnergy;
  float	HFHadronEnergyFraction;
  float	HFEMEnergy;
  float	HFEMEnergyFraction;
  int	chargedHadronMultiplicity;
  int	neutralHadronMultiplicity;
  int	photonMultiplicity;
  int	electronMultiplicity;
  int	HFHadronMultiplicity;
  int	HFEMMultiplicity;
  size_t	numberOfDaughters;
  float	bDiscriminator_impactParameterTagInfos;
  float	bDiscriminator_secondaryVertexTagInfos;
  float	bDiscriminator_softMuonTagInfos;
  float	bDiscriminator_secondaryVertexNegativeTagInfos;
  float	bDiscriminator_inclusiveSecondaryVertexFinderTagInfos;
  float	bDiscriminator_softElectronTagInfos;
  float	bDiscriminator_jetBProbabilityBJetTags;
  float	bDiscriminator_jetProbabilityBJetTags;
  float	bDiscriminator_trackCountingHighPurBJetTags;
  float	bDiscriminator_trackCountingHighEffBJetTags;
  float	bDiscriminator_simpleSecondaryVertexHighEffBJetTags;
  float	bDiscriminator_simpleSecondaryVertexHighPurBJetTags;
  float	bDiscriminator_combinedSecondaryVertexBJetTags;
  float	bDiscriminator_combinedSecondaryVertexMVABJetTags;
  float	bDiscriminator_softMuonBJetTags;
  float	bDiscriminator_softMuonByPtBJetTags;
  float	bDiscriminator_softMuonByIP3dBJetTags;
  float	bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags;
  float	bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags;
  float	bDiscriminator_negativeTrackCountingHighEffJetTags;
  float	bDiscriminator_negativeTrackCountingHighPurJetTags;
  float	bDiscriminator_combinedInclusiveSecondaryVertexBJetTags;
  float	bDiscriminator_combinedMVABJetTags;
};
std::vector<jet_s> jet(200);

std::ostream& operator<<(std::ostream& os, const jet_s& o)
{
  char r[1024];
  os << "jet" << std::endl;
  sprintf(r, "  %-32s: %f\n", "charge", (double)o.charge); os << r;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "neutralHadronEnergy", (double)o.neutralHadronEnergy); os << r;
  sprintf(r, "  %-32s: %f\n", "chargedHadronEnergyFraction", (double)o.chargedHadronEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "neutralHadronEnergyFraction", (double)o.neutralHadronEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "chargedEmEnergyFraction", (double)o.chargedEmEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "neutralEmEnergyFraction", (double)o.neutralEmEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "photonEnergy", (double)o.photonEnergy); os << r;
  sprintf(r, "  %-32s: %f\n", "photonEnergyFraction", (double)o.photonEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "electronEnergy", (double)o.electronEnergy); os << r;
  sprintf(r, "  %-32s: %f\n", "electronEnergyFraction", (double)o.electronEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "muonEnergy", (double)o.muonEnergy); os << r;
  sprintf(r, "  %-32s: %f\n", "muonEnergyFraction", (double)o.muonEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "HFHadronEnergy", (double)o.HFHadronEnergy); os << r;
  sprintf(r, "  %-32s: %f\n", "HFHadronEnergyFraction", (double)o.HFHadronEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "HFEMEnergy", (double)o.HFEMEnergy); os << r;
  sprintf(r, "  %-32s: %f\n", "HFEMEnergyFraction", (double)o.HFEMEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "chargedHadronMultiplicity", (double)o.chargedHadronMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "neutralHadronMultiplicity", (double)o.neutralHadronMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "photonMultiplicity", (double)o.photonMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "electronMultiplicity", (double)o.electronMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "HFHadronMultiplicity", (double)o.HFHadronMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "HFEMMultiplicity", (double)o.HFEMMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "numberOfDaughters", (double)o.numberOfDaughters); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_impactParameterTagInfos", (double)o.bDiscriminator_impactParameterTagInfos); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_secondaryVertexTagInfos", (double)o.bDiscriminator_secondaryVertexTagInfos); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_softMuonTagInfos", (double)o.bDiscriminator_softMuonTagInfos); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_secondaryVertexNegativeTagInfos", (double)o.bDiscriminator_secondaryVertexNegativeTagInfos); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_inclusiveSecondaryVertexFinderTagInfos", (double)o.bDiscriminator_inclusiveSecondaryVertexFinderTagInfos); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_softElectronTagInfos", (double)o.bDiscriminator_softElectronTagInfos); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_jetBProbabilityBJetTags", (double)o.bDiscriminator_jetBProbabilityBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_jetProbabilityBJetTags", (double)o.bDiscriminator_jetProbabilityBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_trackCountingHighPurBJetTags", (double)o.bDiscriminator_trackCountingHighPurBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_trackCountingHighEffBJetTags", (double)o.bDiscriminator_trackCountingHighEffBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_simpleSecondaryVertexHighEffBJetTags", (double)o.bDiscriminator_simpleSecondaryVertexHighEffBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_simpleSecondaryVertexHighPurBJetTags", (double)o.bDiscriminator_simpleSecondaryVertexHighPurBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_combinedSecondaryVertexBJetTags", (double)o.bDiscriminator_combinedSecondaryVertexBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_combinedSecondaryVertexMVABJetTags", (double)o.bDiscriminator_combinedSecondaryVertexMVABJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_softMuonBJetTags", (double)o.bDiscriminator_softMuonBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_softMuonByPtBJetTags", (double)o.bDiscriminator_softMuonByPtBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_softMuonByIP3dBJetTags", (double)o.bDiscriminator_softMuonByIP3dBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags", (double)o.bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags", (double)o.bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_negativeTrackCountingHighEffJetTags", (double)o.bDiscriminator_negativeTrackCountingHighEffJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_negativeTrackCountingHighPurJetTags", (double)o.bDiscriminator_negativeTrackCountingHighPurJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_combinedInclusiveSecondaryVertexBJetTags", (double)o.bDiscriminator_combinedInclusiveSecondaryVertexBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "bDiscriminator_combinedMVABJetTags", (double)o.bDiscriminator_combinedMVABJetTags); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct met_s
{
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
};
std::vector<met_s> met(200);

std::ostream& operator<<(std::ostream& os, const met_s& o)
{
  char r[1024];
  os << "met" << std::endl;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct muon_s
{
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
  int	isGlobalMuon;
  int	isTrackerMuon;
  int	isPFMuon;
  float	pfIsolationR03_sumChargedHadronPt;
  float	pfIsolationR03_sumChargedParticlePt;
  float	pfIsolationR03_sumNeutralHadronEt;
  float	pfIsolationR03_sumNeutralHadronEtHighThreshold;
  float	pfIsolationR03_sumPhotonEt;
  float	pfIsolationR03_sumPhotonEtHighThreshold;
  float	pfIsolationR03_sumPUPt;
  float	pfIsolationR04_sumChargedHadronPt;
  float	pfIsolationR04_sumChargedParticlePt;
  float	pfIsolationR04_sumNeutralHadronEt;
  float	pfIsolationR04_sumNeutralHadronEtHighThreshold;
  float	pfIsolationR04_sumPhotonEt;
  float	pfIsolationR04_sumPhotonEtHighThreshold;
  float	pfIsolationR04_sumPUPt;
  int	numberOfMatchedStations;
  double	innerTrack_normalizedChi2;
  double	innerTrack_dxy;
  double	innerTrack_dz;
  int	innerTrack_hitPattern_numberOfValidPixelHits;
  int	innerTrack_hitPattern_pixelLayersWithMeasurement;
  double	globalTrack_normalizedChi2;
  int	globalTrack_hitPattern_numberOfValidMuonHits;
  double	muonBestTrack_dxy;
  double	muonBestTrack_dz;
};
std::vector<muon_s> muon(200);

std::ostream& operator<<(std::ostream& os, const muon_s& o)
{
  char r[1024];
  os << "muon" << std::endl;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "isGlobalMuon", (double)o.isGlobalMuon); os << r;
  sprintf(r, "  %-32s: %f\n", "isTrackerMuon", (double)o.isTrackerMuon); os << r;
  sprintf(r, "  %-32s: %f\n", "isPFMuon", (double)o.isPFMuon); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR03_sumChargedHadronPt", (double)o.pfIsolationR03_sumChargedHadronPt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR03_sumChargedParticlePt", (double)o.pfIsolationR03_sumChargedParticlePt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR03_sumNeutralHadronEt", (double)o.pfIsolationR03_sumNeutralHadronEt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR03_sumNeutralHadronEtHighThreshold", (double)o.pfIsolationR03_sumNeutralHadronEtHighThreshold); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR03_sumPhotonEt", (double)o.pfIsolationR03_sumPhotonEt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR03_sumPhotonEtHighThreshold", (double)o.pfIsolationR03_sumPhotonEtHighThreshold); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR03_sumPUPt", (double)o.pfIsolationR03_sumPUPt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR04_sumChargedHadronPt", (double)o.pfIsolationR04_sumChargedHadronPt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR04_sumChargedParticlePt", (double)o.pfIsolationR04_sumChargedParticlePt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR04_sumNeutralHadronEt", (double)o.pfIsolationR04_sumNeutralHadronEt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR04_sumNeutralHadronEtHighThreshold", (double)o.pfIsolationR04_sumNeutralHadronEtHighThreshold); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR04_sumPhotonEt", (double)o.pfIsolationR04_sumPhotonEt); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR04_sumPhotonEtHighThreshold", (double)o.pfIsolationR04_sumPhotonEtHighThreshold); os << r;
  sprintf(r, "  %-32s: %f\n", "pfIsolationR04_sumPUPt", (double)o.pfIsolationR04_sumPUPt); os << r;
  sprintf(r, "  %-32s: %f\n", "numberOfMatchedStations", (double)o.numberOfMatchedStations); os << r;
  sprintf(r, "  %-32s: %f\n", "innerTrack_normalizedChi2", (double)o.innerTrack_normalizedChi2); os << r;
  sprintf(r, "  %-32s: %f\n", "innerTrack_dxy", (double)o.innerTrack_dxy); os << r;
  sprintf(r, "  %-32s: %f\n", "innerTrack_dz", (double)o.innerTrack_dz); os << r;
  sprintf(r, "  %-32s: %f\n", "innerTrack_hitPattern_numberOfValidPixelHits", (double)o.innerTrack_hitPattern_numberOfValidPixelHits); os << r;
  sprintf(r, "  %-32s: %f\n", "innerTrack_hitPattern_pixelLayersWithMeasurement", (double)o.innerTrack_hitPattern_pixelLayersWithMeasurement); os << r;
  sprintf(r, "  %-32s: %f\n", "globalTrack_normalizedChi2", (double)o.globalTrack_normalizedChi2); os << r;
  sprintf(r, "  %-32s: %f\n", "globalTrack_hitPattern_numberOfValidMuonHits", (double)o.globalTrack_hitPattern_numberOfValidMuonHits); os << r;
  sprintf(r, "  %-32s: %f\n", "muonBestTrack_dxy", (double)o.muonBestTrack_dxy); os << r;
  sprintf(r, "  %-32s: %f\n", "muonBestTrack_dz", (double)o.muonBestTrack_dz); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct tau_s
{
  int	charge;
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
  double	vx;
  double	vy;
  double	vz;
  float	tauID_againstElectronDeadECAL;
  float	tauID_againstElectronLoose;
  float	tauID_againstElectronLooseMVA5;
  float	tauID_againstElectronMVA5category;
  float	tauID_againstElectronMVA5raw;
  float	tauID_againstElectronMedium;
  float	tauID_againstElectronMediumMVA5;
  float	tauID_againstElectronTight;
  float	tauID_againstElectronTightMVA5;
  float	tauID_againstElectronVLooseMVA5;
  float	tauID_againstElectronVTightMVA5;
  float	tauID_againstMuonLoose;
  float	tauID_againstMuonLoose2;
  float	tauID_againstMuonLoose3;
  float	tauID_againstMuonLooseMVA;
  float	tauID_againstMuonMVAraw;
  float	tauID_againstMuonMedium;
  float	tauID_againstMuonMedium2;
  float	tauID_againstMuonMediumMVA;
  float	tauID_againstMuonTight;
  float	tauID_againstMuonTight2;
  float	tauID_againstMuonTight3;
  float	tauID_againstMuonTightMVA;
  float	tauID_byCombinedIsolationDeltaBetaCorrRaw;
  float	tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits;
  float	tauID_byIsolationMVA3newDMwLTraw;
  float	tauID_byIsolationMVA3newDMwoLTraw;
  float	tauID_byIsolationMVA3oldDMwLTraw;
  float	tauID_byIsolationMVA3oldDMwoLTraw;
  float	tauID_byLooseCombinedIsolationDeltaBetaCorr;
  float	tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byLooseIsolation;
  float	tauID_byLooseIsolationMVA3newDMwLT;
  float	tauID_byLooseIsolationMVA3newDMwoLT;
  float	tauID_byLooseIsolationMVA3oldDMwLT;
  float	tauID_byLooseIsolationMVA3oldDMwoLT;
  float	tauID_byMediumCombinedIsolationDeltaBetaCorr;
  float	tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byMediumIsolationMVA3newDMwLT;
  float	tauID_byMediumIsolationMVA3newDMwoLT;
  float	tauID_byMediumIsolationMVA3oldDMwLT;
  float	tauID_byMediumIsolationMVA3oldDMwoLT;
  float	tauID_byTightCombinedIsolationDeltaBetaCorr;
  float	tauID_byTightCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byTightIsolationMVA3newDMwLT;
  float	tauID_byTightIsolationMVA3newDMwoLT;
  float	tauID_byTightIsolationMVA3oldDMwLT;
  float	tauID_byTightIsolationMVA3oldDMwoLT;
  float	tauID_byVLooseCombinedIsolationDeltaBetaCorr;
  float	tauID_byVLooseIsolationMVA3newDMwLT;
  float	tauID_byVLooseIsolationMVA3newDMwoLT;
  float	tauID_byVLooseIsolationMVA3oldDMwLT;
  float	tauID_byVLooseIsolationMVA3oldDMwoLT;
  float	tauID_byVTightIsolationMVA3newDMwLT;
  float	tauID_byVTightIsolationMVA3newDMwoLT;
  float	tauID_byVTightIsolationMVA3oldDMwLT;
  float	tauID_byVTightIsolationMVA3oldDMwoLT;
  float	tauID_byVVTightIsolationMVA3newDMwLT;
  float	tauID_byVVTightIsolationMVA3newDMwoLT;
  float	tauID_byVVTightIsolationMVA3oldDMwLT;
  float	tauID_byVVTightIsolationMVA3oldDMwoLT;
  float	tauID_chargedIsoPtSum;
  float	tauID_decayModeFinding;
  float	tauID_decayModeFindingNewDMs;
  float	tauID_decayModeFindingOldDMs;
  float	tauID_neutralIsoPtSum;
  float	tauID_puCorrPtSum;
  double	leadPFChargedHadrCand_p;
  double	leadPFChargedHadrCand_energy;
  double	leadPFChargedHadrCand_et;
  double	leadPFChargedHadrCand_mass;
  double	leadPFChargedHadrCand_massSqr;
  double	leadPFChargedHadrCand_mt;
  double	leadPFChargedHadrCand_mtSqr;
  double	leadPFChargedHadrCand_px;
  double	leadPFChargedHadrCand_py;
  double	leadPFChargedHadrCand_pz;
  double	leadPFChargedHadrCand_pt;
  double	leadPFChargedHadrCand_phi;
  double	leadPFChargedHadrCand_theta;
  double	leadPFChargedHadrCand_eta;
  double	leadPFChargedHadrCand_rapidity;
  double	leadPFChargedHadrCand_y;
  size_t	signalPFChargedHadrCands_size;
};
std::vector<tau_s> tau(200);

std::ostream& operator<<(std::ostream& os, const tau_s& o)
{
  char r[1024];
  os << "tau" << std::endl;
  sprintf(r, "  %-32s: %f\n", "charge", (double)o.charge); os << r;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "vx", (double)o.vx); os << r;
  sprintf(r, "  %-32s: %f\n", "vy", (double)o.vy); os << r;
  sprintf(r, "  %-32s: %f\n", "vz", (double)o.vz); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronDeadECAL", (double)o.tauID_againstElectronDeadECAL); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronLoose", (double)o.tauID_againstElectronLoose); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronLooseMVA5", (double)o.tauID_againstElectronLooseMVA5); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMVA5category", (double)o.tauID_againstElectronMVA5category); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMVA5raw", (double)o.tauID_againstElectronMVA5raw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMedium", (double)o.tauID_againstElectronMedium); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMediumMVA5", (double)o.tauID_againstElectronMediumMVA5); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronTight", (double)o.tauID_againstElectronTight); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronTightMVA5", (double)o.tauID_againstElectronTightMVA5); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronVLooseMVA5", (double)o.tauID_againstElectronVLooseMVA5); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronVTightMVA5", (double)o.tauID_againstElectronVTightMVA5); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonLoose", (double)o.tauID_againstMuonLoose); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonLoose2", (double)o.tauID_againstMuonLoose2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonLoose3", (double)o.tauID_againstMuonLoose3); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonLooseMVA", (double)o.tauID_againstMuonLooseMVA); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonMVAraw", (double)o.tauID_againstMuonMVAraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonMedium", (double)o.tauID_againstMuonMedium); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonMedium2", (double)o.tauID_againstMuonMedium2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonMediumMVA", (double)o.tauID_againstMuonMediumMVA); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonTight", (double)o.tauID_againstMuonTight); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonTight2", (double)o.tauID_againstMuonTight2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonTight3", (double)o.tauID_againstMuonTight3); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonTightMVA", (double)o.tauID_againstMuonTightMVA); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byCombinedIsolationDeltaBetaCorrRaw", (double)o.tauID_byCombinedIsolationDeltaBetaCorrRaw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits", (double)o.tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3newDMwLTraw", (double)o.tauID_byIsolationMVA3newDMwLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3newDMwoLTraw", (double)o.tauID_byIsolationMVA3newDMwoLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3oldDMwLTraw", (double)o.tauID_byIsolationMVA3oldDMwLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3oldDMwoLTraw", (double)o.tauID_byIsolationMVA3oldDMwoLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseCombinedIsolationDeltaBetaCorr", (double)o.tauID_byLooseCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolation", (double)o.tauID_byLooseIsolation); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3newDMwLT", (double)o.tauID_byLooseIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3newDMwoLT", (double)o.tauID_byLooseIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3oldDMwLT", (double)o.tauID_byLooseIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3oldDMwoLT", (double)o.tauID_byLooseIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumCombinedIsolationDeltaBetaCorr", (double)o.tauID_byMediumCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3newDMwLT", (double)o.tauID_byMediumIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3newDMwoLT", (double)o.tauID_byMediumIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3oldDMwLT", (double)o.tauID_byMediumIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3oldDMwoLT", (double)o.tauID_byMediumIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightCombinedIsolationDeltaBetaCorr", (double)o.tauID_byTightCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byTightCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3newDMwLT", (double)o.tauID_byTightIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3newDMwoLT", (double)o.tauID_byTightIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3oldDMwLT", (double)o.tauID_byTightIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3oldDMwoLT", (double)o.tauID_byTightIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseCombinedIsolationDeltaBetaCorr", (double)o.tauID_byVLooseCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseIsolationMVA3newDMwLT", (double)o.tauID_byVLooseIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseIsolationMVA3newDMwoLT", (double)o.tauID_byVLooseIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseIsolationMVA3oldDMwLT", (double)o.tauID_byVLooseIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseIsolationMVA3oldDMwoLT", (double)o.tauID_byVLooseIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVTightIsolationMVA3newDMwLT", (double)o.tauID_byVTightIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVTightIsolationMVA3newDMwoLT", (double)o.tauID_byVTightIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVTightIsolationMVA3oldDMwLT", (double)o.tauID_byVTightIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVTightIsolationMVA3oldDMwoLT", (double)o.tauID_byVTightIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVVTightIsolationMVA3newDMwLT", (double)o.tauID_byVVTightIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVVTightIsolationMVA3newDMwoLT", (double)o.tauID_byVVTightIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVVTightIsolationMVA3oldDMwLT", (double)o.tauID_byVVTightIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVVTightIsolationMVA3oldDMwoLT", (double)o.tauID_byVVTightIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_chargedIsoPtSum", (double)o.tauID_chargedIsoPtSum); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_decayModeFinding", (double)o.tauID_decayModeFinding); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_decayModeFindingNewDMs", (double)o.tauID_decayModeFindingNewDMs); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_decayModeFindingOldDMs", (double)o.tauID_decayModeFindingOldDMs); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_neutralIsoPtSum", (double)o.tauID_neutralIsoPtSum); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_puCorrPtSum", (double)o.tauID_puCorrPtSum); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_p", (double)o.leadPFChargedHadrCand_p); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_energy", (double)o.leadPFChargedHadrCand_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_et", (double)o.leadPFChargedHadrCand_et); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_mass", (double)o.leadPFChargedHadrCand_mass); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_massSqr", (double)o.leadPFChargedHadrCand_massSqr); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_mt", (double)o.leadPFChargedHadrCand_mt); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_mtSqr", (double)o.leadPFChargedHadrCand_mtSqr); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_px", (double)o.leadPFChargedHadrCand_px); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_py", (double)o.leadPFChargedHadrCand_py); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_pz", (double)o.leadPFChargedHadrCand_pz); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_pt", (double)o.leadPFChargedHadrCand_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_phi", (double)o.leadPFChargedHadrCand_phi); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_theta", (double)o.leadPFChargedHadrCand_theta); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_eta", (double)o.leadPFChargedHadrCand_eta); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_rapidity", (double)o.leadPFChargedHadrCand_rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "leadPFChargedHadrCand_y", (double)o.leadPFChargedHadrCand_y); os << r;
  sprintf(r, "  %-32s: %f\n", "signalPFChargedHadrCands_size", (double)o.signalPFChargedHadrCands_size); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct genparticlehelper_s
{
  int	firstMother;
  int	lastMother;
  int	firstDaughter;
  int	lastDaughter;
  int	charge;
  int	pdgId;
  int	status;
  double	pt;
  double	eta;
  double	phi;
  double	mass;
};
std::vector<genparticlehelper_s> genparticlehelper(100);

std::ostream& operator<<(std::ostream& os, const genparticlehelper_s& o)
{
  char r[1024];
  os << "genparticlehelper" << std::endl;
  sprintf(r, "  %-32s: %f\n", "firstMother", (double)o.firstMother); os << r;
  sprintf(r, "  %-32s: %f\n", "lastMother", (double)o.lastMother); os << r;
  sprintf(r, "  %-32s: %f\n", "firstDaughter", (double)o.firstDaughter); os << r;
  sprintf(r, "  %-32s: %f\n", "lastDaughter", (double)o.lastDaughter); os << r;
  sprintf(r, "  %-32s: %f\n", "charge", (double)o.charge); os << r;
  sprintf(r, "  %-32s: %f\n", "pdgId", (double)o.pdgId); os << r;
  sprintf(r, "  %-32s: %f\n", "status", (double)o.status); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct genparticlehelperplus_s
{
  int	firstMother;
  int	lastMother;
  int	firstDaughter;
  int	lastDaughter;
  int	charge;
  int	pdgId;
  int	status;
  double	pt;
  double	eta;
  double	phi;
  double	mass;
};
std::vector<genparticlehelperplus_s> genparticlehelperplus(100);

std::ostream& operator<<(std::ostream& os, const genparticlehelperplus_s& o)
{
  char r[1024];
  os << "genparticlehelperplus" << std::endl;
  sprintf(r, "  %-32s: %f\n", "firstMother", (double)o.firstMother); os << r;
  sprintf(r, "  %-32s: %f\n", "lastMother", (double)o.lastMother); os << r;
  sprintf(r, "  %-32s: %f\n", "firstDaughter", (double)o.firstDaughter); os << r;
  sprintf(r, "  %-32s: %f\n", "lastDaughter", (double)o.lastDaughter); os << r;
  sprintf(r, "  %-32s: %f\n", "charge", (double)o.charge); os << r;
  sprintf(r, "  %-32s: %f\n", "pdgId", (double)o.pdgId); os << r;
  sprintf(r, "  %-32s: %f\n", "status", (double)o.status); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct recoGsfElectron_s
{
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
  float	eSuperClusterOverP;
  float	deltaEtaSuperClusterTrackAtVtx;
  float	deltaPhiSuperClusterTrackAtVtx;
  float	sigmaIetaIeta;
  float	scE1x5;
  float	scE2x5Max;
  float	scE5x5;
  float	hadronicOverEm;
  float	dr04TkSumPt;
  float	dr04EcalRecHitSumEt;
  double	gsfTrack_dxy;
  double	gsfTrack_d0;
  double	gsfTrack_dz;
};
std::vector<recoGsfElectron_s> recoGsfElectron(200);

std::ostream& operator<<(std::ostream& os, const recoGsfElectron_s& o)
{
  char r[1024];
  os << "recoGsfElectron" << std::endl;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "eSuperClusterOverP", (double)o.eSuperClusterOverP); os << r;
  sprintf(r, "  %-32s: %f\n", "deltaEtaSuperClusterTrackAtVtx", (double)o.deltaEtaSuperClusterTrackAtVtx); os << r;
  sprintf(r, "  %-32s: %f\n", "deltaPhiSuperClusterTrackAtVtx", (double)o.deltaPhiSuperClusterTrackAtVtx); os << r;
  sprintf(r, "  %-32s: %f\n", "sigmaIetaIeta", (double)o.sigmaIetaIeta); os << r;
  sprintf(r, "  %-32s: %f\n", "scE1x5", (double)o.scE1x5); os << r;
  sprintf(r, "  %-32s: %f\n", "scE2x5Max", (double)o.scE2x5Max); os << r;
  sprintf(r, "  %-32s: %f\n", "scE5x5", (double)o.scE5x5); os << r;
  sprintf(r, "  %-32s: %f\n", "hadronicOverEm", (double)o.hadronicOverEm); os << r;
  sprintf(r, "  %-32s: %f\n", "dr04TkSumPt", (double)o.dr04TkSumPt); os << r;
  sprintf(r, "  %-32s: %f\n", "dr04EcalRecHitSumEt", (double)o.dr04EcalRecHitSumEt); os << r;
  sprintf(r, "  %-32s: %f\n", "gsfTrack_dxy", (double)o.gsfTrack_dxy); os << r;
  sprintf(r, "  %-32s: %f\n", "gsfTrack_d0", (double)o.gsfTrack_d0); os << r;
  sprintf(r, "  %-32s: %f\n", "gsfTrack_dz", (double)o.gsfTrack_dz); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct recoPFMET_s
{
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
};
std::vector<recoPFMET_s> recoPFMET(200);

std::ostream& operator<<(std::ostream& os, const recoPFMET_s& o)
{
  char r[1024];
  os << "recoPFMET" << std::endl;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct recoPFMET1_s
{
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  double	pt;
  double	phi;
  double	eta;
};
std::vector<recoPFMET1_s> recoPFMET1(200);

std::ostream& operator<<(std::ostream& os, const recoPFMET1_s& o)
{
  char r[1024];
  os << "recoPFMET1" << std::endl;
  sprintf(r, "  %-32s: %f\n", "p", (double)o.p); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "px", (double)o.px); os << r;
  sprintf(r, "  %-32s: %f\n", "py", (double)o.py); os << r;
  sprintf(r, "  %-32s: %f\n", "pz", (double)o.pz); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct vertex_s
{
  int	isFake;
  double	ndof;
  double	x;
  double	y;
  double	z;
};
std::vector<vertex_s> vertex(200);

std::ostream& operator<<(std::ostream& os, const vertex_s& o)
{
  char r[1024];
  os << "vertex" << std::endl;
  sprintf(r, "  %-32s: %f\n", "isFake", (double)o.isFake); os << r;
  sprintf(r, "  %-32s: %f\n", "ndof", (double)o.ndof); os << r;
  sprintf(r, "  %-32s: %f\n", "x", (double)o.x); os << r;
  sprintf(r, "  %-32s: %f\n", "y", (double)o.y); os << r;
  sprintf(r, "  %-32s: %f\n", "z", (double)o.z); os << r;
  return os;
}
//-----------------------------------------------------------------------------

inline void fillPileupSummaryInfo()
{
  PileupSummaryInfo.resize(PileupSummaryInfo_getBunchCrossing.size());
  for(unsigned int i=0; i < PileupSummaryInfo.size(); ++i)
    {
      PileupSummaryInfo[i].getBunchCrossing	= PileupSummaryInfo_getBunchCrossing[i];
      PileupSummaryInfo[i].getPU_NumInteractions	= PileupSummaryInfo_getPU_NumInteractions[i];
    }
}

inline void fillak5GenJets()
{
  ak5GenJets.resize(ak5GenJets_charge.size());
  for(unsigned int i=0; i < ak5GenJets.size(); ++i)
    {
      ak5GenJets[i].charge	= ak5GenJets_charge[i];
      ak5GenJets[i].pt	= ak5GenJets_pt[i];
      ak5GenJets[i].eta	= ak5GenJets_eta[i];
      ak5GenJets[i].phi	= ak5GenJets_phi[i];
      ak5GenJets[i].mass	= ak5GenJets_mass[i];
    }
}

inline void fillpatElectron()
{
  electron.resize(patElectron_p.size());
  for(unsigned int i=0; i < electron.size(); ++i)
    {
      electron[i].p	= patElectron_p[i];
      electron[i].energy	= patElectron_energy[i];
      electron[i].et	= patElectron_et[i];
      electron[i].px	= patElectron_px[i];
      electron[i].py	= patElectron_py[i];
      electron[i].pz	= patElectron_pz[i];
      electron[i].pt	= patElectron_pt[i];
      electron[i].phi	= patElectron_phi[i];
      electron[i].eta	= patElectron_eta[i];
      electron[i].eSuperClusterOverP	= patElectron_eSuperClusterOverP[i];
      electron[i].deltaEtaSuperClusterTrackAtVtx	= patElectron_deltaEtaSuperClusterTrackAtVtx[i];
      electron[i].deltaPhiSuperClusterTrackAtVtx	= patElectron_deltaPhiSuperClusterTrackAtVtx[i];
      electron[i].sigmaIetaIeta	= patElectron_sigmaIetaIeta[i];
      electron[i].scE1x5	= patElectron_scE1x5[i];
      electron[i].scE2x5Max	= patElectron_scE2x5Max[i];
      electron[i].scE5x5	= patElectron_scE5x5[i];
      electron[i].hadronicOverEm	= patElectron_hadronicOverEm[i];
      electron[i].dr04TkSumPt	= patElectron_dr04TkSumPt[i];
      electron[i].dr04EcalRecHitSumEt	= patElectron_dr04EcalRecHitSumEt[i];
      electron[i].gsfTrack_dxy	= patElectron_gsfTrack_dxy[i];
      electron[i].gsfTrack_d0	= patElectron_gsfTrack_d0[i];
      electron[i].gsfTrack_dz	= patElectron_gsfTrack_dz[i];
    }
}

inline void fillpatJet()
{
  jet.resize(patJet_charge.size());
  for(unsigned int i=0; i < jet.size(); ++i)
    {
      jet[i].charge	= patJet_charge[i];
      jet[i].p	= patJet_p[i];
      jet[i].energy	= patJet_energy[i];
      jet[i].et	= patJet_et[i];
      jet[i].px	= patJet_px[i];
      jet[i].py	= patJet_py[i];
      jet[i].pz	= patJet_pz[i];
      jet[i].pt	= patJet_pt[i];
      jet[i].phi	= patJet_phi[i];
      jet[i].eta	= patJet_eta[i];
      jet[i].neutralHadronEnergy	= patJet_neutralHadronEnergy[i];
      jet[i].chargedHadronEnergyFraction	= patJet_chargedHadronEnergyFraction[i];
      jet[i].neutralHadronEnergyFraction	= patJet_neutralHadronEnergyFraction[i];
      jet[i].chargedEmEnergyFraction	= patJet_chargedEmEnergyFraction[i];
      jet[i].neutralEmEnergyFraction	= patJet_neutralEmEnergyFraction[i];
      jet[i].photonEnergy	= patJet_photonEnergy[i];
      jet[i].photonEnergyFraction	= patJet_photonEnergyFraction[i];
      jet[i].electronEnergy	= patJet_electronEnergy[i];
      jet[i].electronEnergyFraction	= patJet_electronEnergyFraction[i];
      jet[i].muonEnergy	= patJet_muonEnergy[i];
      jet[i].muonEnergyFraction	= patJet_muonEnergyFraction[i];
      jet[i].HFHadronEnergy	= patJet_HFHadronEnergy[i];
      jet[i].HFHadronEnergyFraction	= patJet_HFHadronEnergyFraction[i];
      jet[i].HFEMEnergy	= patJet_HFEMEnergy[i];
      jet[i].HFEMEnergyFraction	= patJet_HFEMEnergyFraction[i];
      jet[i].chargedHadronMultiplicity	= patJet_chargedHadronMultiplicity[i];
      jet[i].neutralHadronMultiplicity	= patJet_neutralHadronMultiplicity[i];
      jet[i].photonMultiplicity	= patJet_photonMultiplicity[i];
      jet[i].electronMultiplicity	= patJet_electronMultiplicity[i];
      jet[i].HFHadronMultiplicity	= patJet_HFHadronMultiplicity[i];
      jet[i].HFEMMultiplicity	= patJet_HFEMMultiplicity[i];
      jet[i].numberOfDaughters	= patJet_numberOfDaughters[i];
      jet[i].bDiscriminator_impactParameterTagInfos	= patJet_bDiscriminator_impactParameterTagInfos[i];
      jet[i].bDiscriminator_secondaryVertexTagInfos	= patJet_bDiscriminator_secondaryVertexTagInfos[i];
      jet[i].bDiscriminator_softMuonTagInfos	= patJet_bDiscriminator_softMuonTagInfos[i];
      jet[i].bDiscriminator_secondaryVertexNegativeTagInfos	= patJet_bDiscriminator_secondaryVertexNegativeTagInfos[i];
      jet[i].bDiscriminator_inclusiveSecondaryVertexFinderTagInfos	= patJet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos[i];
      jet[i].bDiscriminator_softElectronTagInfos	= patJet_bDiscriminator_softElectronTagInfos[i];
      jet[i].bDiscriminator_jetBProbabilityBJetTags	= patJet_bDiscriminator_jetBProbabilityBJetTags[i];
      jet[i].bDiscriminator_jetProbabilityBJetTags	= patJet_bDiscriminator_jetProbabilityBJetTags[i];
      jet[i].bDiscriminator_trackCountingHighPurBJetTags	= patJet_bDiscriminator_trackCountingHighPurBJetTags[i];
      jet[i].bDiscriminator_trackCountingHighEffBJetTags	= patJet_bDiscriminator_trackCountingHighEffBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexHighEffBJetTags	= patJet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexHighPurBJetTags	= patJet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags[i];
      jet[i].bDiscriminator_combinedSecondaryVertexBJetTags	= patJet_bDiscriminator_combinedSecondaryVertexBJetTags[i];
      jet[i].bDiscriminator_combinedSecondaryVertexMVABJetTags	= patJet_bDiscriminator_combinedSecondaryVertexMVABJetTags[i];
      jet[i].bDiscriminator_softMuonBJetTags	= patJet_bDiscriminator_softMuonBJetTags[i];
      jet[i].bDiscriminator_softMuonByPtBJetTags	= patJet_bDiscriminator_softMuonByPtBJetTags[i];
      jet[i].bDiscriminator_softMuonByIP3dBJetTags	= patJet_bDiscriminator_softMuonByIP3dBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags	= patJet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags	= patJet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags[i];
      jet[i].bDiscriminator_negativeTrackCountingHighEffJetTags	= patJet_bDiscriminator_negativeTrackCountingHighEffJetTags[i];
      jet[i].bDiscriminator_negativeTrackCountingHighPurJetTags	= patJet_bDiscriminator_negativeTrackCountingHighPurJetTags[i];
      jet[i].bDiscriminator_combinedInclusiveSecondaryVertexBJetTags	= patJet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags[i];
      jet[i].bDiscriminator_combinedMVABJetTags	= patJet_bDiscriminator_combinedMVABJetTags[i];
    }
}

inline void fillpatMET()
{
  met.resize(patMET_p.size());
  for(unsigned int i=0; i < met.size(); ++i)
    {
      met[i].p	= patMET_p[i];
      met[i].energy	= patMET_energy[i];
      met[i].et	= patMET_et[i];
      met[i].px	= patMET_px[i];
      met[i].py	= patMET_py[i];
      met[i].pz	= patMET_pz[i];
      met[i].pt	= patMET_pt[i];
      met[i].phi	= patMET_phi[i];
      met[i].eta	= patMET_eta[i];
    }
}

inline void fillpatMuon()
{
  muon.resize(patMuon_p.size());
  for(unsigned int i=0; i < muon.size(); ++i)
    {
      muon[i].p	= patMuon_p[i];
      muon[i].energy	= patMuon_energy[i];
      muon[i].et	= patMuon_et[i];
      muon[i].px	= patMuon_px[i];
      muon[i].py	= patMuon_py[i];
      muon[i].pz	= patMuon_pz[i];
      muon[i].pt	= patMuon_pt[i];
      muon[i].phi	= patMuon_phi[i];
      muon[i].eta	= patMuon_eta[i];
      muon[i].isGlobalMuon	= patMuon_isGlobalMuon[i];
      muon[i].isTrackerMuon	= patMuon_isTrackerMuon[i];
      muon[i].isPFMuon	= patMuon_isPFMuon[i];
      muon[i].pfIsolationR03_sumChargedHadronPt	= patMuon_pfIsolationR03_sumChargedHadronPt[i];
      muon[i].pfIsolationR03_sumChargedParticlePt	= patMuon_pfIsolationR03_sumChargedParticlePt[i];
      muon[i].pfIsolationR03_sumNeutralHadronEt	= patMuon_pfIsolationR03_sumNeutralHadronEt[i];
      muon[i].pfIsolationR03_sumNeutralHadronEtHighThreshold	= patMuon_pfIsolationR03_sumNeutralHadronEtHighThreshold[i];
      muon[i].pfIsolationR03_sumPhotonEt	= patMuon_pfIsolationR03_sumPhotonEt[i];
      muon[i].pfIsolationR03_sumPhotonEtHighThreshold	= patMuon_pfIsolationR03_sumPhotonEtHighThreshold[i];
      muon[i].pfIsolationR03_sumPUPt	= patMuon_pfIsolationR03_sumPUPt[i];
      muon[i].pfIsolationR04_sumChargedHadronPt	= patMuon_pfIsolationR04_sumChargedHadronPt[i];
      muon[i].pfIsolationR04_sumChargedParticlePt	= patMuon_pfIsolationR04_sumChargedParticlePt[i];
      muon[i].pfIsolationR04_sumNeutralHadronEt	= patMuon_pfIsolationR04_sumNeutralHadronEt[i];
      muon[i].pfIsolationR04_sumNeutralHadronEtHighThreshold	= patMuon_pfIsolationR04_sumNeutralHadronEtHighThreshold[i];
      muon[i].pfIsolationR04_sumPhotonEt	= patMuon_pfIsolationR04_sumPhotonEt[i];
      muon[i].pfIsolationR04_sumPhotonEtHighThreshold	= patMuon_pfIsolationR04_sumPhotonEtHighThreshold[i];
      muon[i].pfIsolationR04_sumPUPt	= patMuon_pfIsolationR04_sumPUPt[i];
      muon[i].numberOfMatchedStations	= patMuon_numberOfMatchedStations[i];
      muon[i].innerTrack_normalizedChi2	= patMuon_innerTrack_normalizedChi2[i];
      muon[i].innerTrack_dxy	= patMuon_innerTrack_dxy[i];
      muon[i].innerTrack_dz	= patMuon_innerTrack_dz[i];
      muon[i].innerTrack_hitPattern_numberOfValidPixelHits	= patMuon_innerTrack_hitPattern_numberOfValidPixelHits[i];
      muon[i].innerTrack_hitPattern_pixelLayersWithMeasurement	= patMuon_innerTrack_hitPattern_pixelLayersWithMeasurement[i];
      muon[i].globalTrack_normalizedChi2	= patMuon_globalTrack_normalizedChi2[i];
      muon[i].globalTrack_hitPattern_numberOfValidMuonHits	= patMuon_globalTrack_hitPattern_numberOfValidMuonHits[i];
      muon[i].muonBestTrack_dxy	= patMuon_muonBestTrack_dxy[i];
      muon[i].muonBestTrack_dz	= patMuon_muonBestTrack_dz[i];
    }
}

inline void fillpatTau()
{
  tau.resize(patTau_charge.size());
  for(unsigned int i=0; i < tau.size(); ++i)
    {
      tau[i].charge	= patTau_charge[i];
      tau[i].p	= patTau_p[i];
      tau[i].energy	= patTau_energy[i];
      tau[i].et	= patTau_et[i];
      tau[i].px	= patTau_px[i];
      tau[i].py	= patTau_py[i];
      tau[i].pz	= patTau_pz[i];
      tau[i].pt	= patTau_pt[i];
      tau[i].phi	= patTau_phi[i];
      tau[i].eta	= patTau_eta[i];
      tau[i].vx	= patTau_vx[i];
      tau[i].vy	= patTau_vy[i];
      tau[i].vz	= patTau_vz[i];
      tau[i].tauID_againstElectronDeadECAL	= patTau_tauID_againstElectronDeadECAL[i];
      tau[i].tauID_againstElectronLoose	= patTau_tauID_againstElectronLoose[i];
      tau[i].tauID_againstElectronLooseMVA5	= patTau_tauID_againstElectronLooseMVA5[i];
      tau[i].tauID_againstElectronMVA5category	= patTau_tauID_againstElectronMVA5category[i];
      tau[i].tauID_againstElectronMVA5raw	= patTau_tauID_againstElectronMVA5raw[i];
      tau[i].tauID_againstElectronMedium	= patTau_tauID_againstElectronMedium[i];
      tau[i].tauID_againstElectronMediumMVA5	= patTau_tauID_againstElectronMediumMVA5[i];
      tau[i].tauID_againstElectronTight	= patTau_tauID_againstElectronTight[i];
      tau[i].tauID_againstElectronTightMVA5	= patTau_tauID_againstElectronTightMVA5[i];
      tau[i].tauID_againstElectronVLooseMVA5	= patTau_tauID_againstElectronVLooseMVA5[i];
      tau[i].tauID_againstElectronVTightMVA5	= patTau_tauID_againstElectronVTightMVA5[i];
      tau[i].tauID_againstMuonLoose	= patTau_tauID_againstMuonLoose[i];
      tau[i].tauID_againstMuonLoose2	= patTau_tauID_againstMuonLoose2[i];
      tau[i].tauID_againstMuonLoose3	= patTau_tauID_againstMuonLoose3[i];
      tau[i].tauID_againstMuonLooseMVA	= patTau_tauID_againstMuonLooseMVA[i];
      tau[i].tauID_againstMuonMVAraw	= patTau_tauID_againstMuonMVAraw[i];
      tau[i].tauID_againstMuonMedium	= patTau_tauID_againstMuonMedium[i];
      tau[i].tauID_againstMuonMedium2	= patTau_tauID_againstMuonMedium2[i];
      tau[i].tauID_againstMuonMediumMVA	= patTau_tauID_againstMuonMediumMVA[i];
      tau[i].tauID_againstMuonTight	= patTau_tauID_againstMuonTight[i];
      tau[i].tauID_againstMuonTight2	= patTau_tauID_againstMuonTight2[i];
      tau[i].tauID_againstMuonTight3	= patTau_tauID_againstMuonTight3[i];
      tau[i].tauID_againstMuonTightMVA	= patTau_tauID_againstMuonTightMVA[i];
      tau[i].tauID_byCombinedIsolationDeltaBetaCorrRaw	= patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw[i];
      tau[i].tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits	= patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[i];
      tau[i].tauID_byIsolationMVA3newDMwLTraw	= patTau_tauID_byIsolationMVA3newDMwLTraw[i];
      tau[i].tauID_byIsolationMVA3newDMwoLTraw	= patTau_tauID_byIsolationMVA3newDMwoLTraw[i];
      tau[i].tauID_byIsolationMVA3oldDMwLTraw	= patTau_tauID_byIsolationMVA3oldDMwLTraw[i];
      tau[i].tauID_byIsolationMVA3oldDMwoLTraw	= patTau_tauID_byIsolationMVA3oldDMwoLTraw[i];
      tau[i].tauID_byLooseCombinedIsolationDeltaBetaCorr	= patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits	= patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byLooseIsolation	= patTau_tauID_byLooseIsolation[i];
      tau[i].tauID_byLooseIsolationMVA3newDMwLT	= patTau_tauID_byLooseIsolationMVA3newDMwLT[i];
      tau[i].tauID_byLooseIsolationMVA3newDMwoLT	= patTau_tauID_byLooseIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byLooseIsolationMVA3oldDMwLT	= patTau_tauID_byLooseIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byLooseIsolationMVA3oldDMwoLT	= patTau_tauID_byLooseIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byMediumCombinedIsolationDeltaBetaCorr	= patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits	= patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byMediumIsolationMVA3newDMwLT	= patTau_tauID_byMediumIsolationMVA3newDMwLT[i];
      tau[i].tauID_byMediumIsolationMVA3newDMwoLT	= patTau_tauID_byMediumIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byMediumIsolationMVA3oldDMwLT	= patTau_tauID_byMediumIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byMediumIsolationMVA3oldDMwoLT	= patTau_tauID_byMediumIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byTightCombinedIsolationDeltaBetaCorr	= patTau_tauID_byTightCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits	= patTau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byTightIsolationMVA3newDMwLT	= patTau_tauID_byTightIsolationMVA3newDMwLT[i];
      tau[i].tauID_byTightIsolationMVA3newDMwoLT	= patTau_tauID_byTightIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byTightIsolationMVA3oldDMwLT	= patTau_tauID_byTightIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byTightIsolationMVA3oldDMwoLT	= patTau_tauID_byTightIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byVLooseCombinedIsolationDeltaBetaCorr	= patTau_tauID_byVLooseCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_byVLooseIsolationMVA3newDMwLT	= patTau_tauID_byVLooseIsolationMVA3newDMwLT[i];
      tau[i].tauID_byVLooseIsolationMVA3newDMwoLT	= patTau_tauID_byVLooseIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byVLooseIsolationMVA3oldDMwLT	= patTau_tauID_byVLooseIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byVLooseIsolationMVA3oldDMwoLT	= patTau_tauID_byVLooseIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byVTightIsolationMVA3newDMwLT	= patTau_tauID_byVTightIsolationMVA3newDMwLT[i];
      tau[i].tauID_byVTightIsolationMVA3newDMwoLT	= patTau_tauID_byVTightIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byVTightIsolationMVA3oldDMwLT	= patTau_tauID_byVTightIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byVTightIsolationMVA3oldDMwoLT	= patTau_tauID_byVTightIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byVVTightIsolationMVA3newDMwLT	= patTau_tauID_byVVTightIsolationMVA3newDMwLT[i];
      tau[i].tauID_byVVTightIsolationMVA3newDMwoLT	= patTau_tauID_byVVTightIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byVVTightIsolationMVA3oldDMwLT	= patTau_tauID_byVVTightIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byVVTightIsolationMVA3oldDMwoLT	= patTau_tauID_byVVTightIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_chargedIsoPtSum	= patTau_tauID_chargedIsoPtSum[i];
      tau[i].tauID_decayModeFinding	= patTau_tauID_decayModeFinding[i];
      tau[i].tauID_decayModeFindingNewDMs	= patTau_tauID_decayModeFindingNewDMs[i];
      tau[i].tauID_decayModeFindingOldDMs	= patTau_tauID_decayModeFindingOldDMs[i];
      tau[i].tauID_neutralIsoPtSum	= patTau_tauID_neutralIsoPtSum[i];
      tau[i].tauID_puCorrPtSum	= patTau_tauID_puCorrPtSum[i];
      tau[i].leadPFChargedHadrCand_p	= patTau_leadPFChargedHadrCand_p[i];
      tau[i].leadPFChargedHadrCand_energy	= patTau_leadPFChargedHadrCand_energy[i];
      tau[i].leadPFChargedHadrCand_et	= patTau_leadPFChargedHadrCand_et[i];
      tau[i].leadPFChargedHadrCand_mass	= patTau_leadPFChargedHadrCand_mass[i];
      tau[i].leadPFChargedHadrCand_massSqr	= patTau_leadPFChargedHadrCand_massSqr[i];
      tau[i].leadPFChargedHadrCand_mt	= patTau_leadPFChargedHadrCand_mt[i];
      tau[i].leadPFChargedHadrCand_mtSqr	= patTau_leadPFChargedHadrCand_mtSqr[i];
      tau[i].leadPFChargedHadrCand_px	= patTau_leadPFChargedHadrCand_px[i];
      tau[i].leadPFChargedHadrCand_py	= patTau_leadPFChargedHadrCand_py[i];
      tau[i].leadPFChargedHadrCand_pz	= patTau_leadPFChargedHadrCand_pz[i];
      tau[i].leadPFChargedHadrCand_pt	= patTau_leadPFChargedHadrCand_pt[i];
      tau[i].leadPFChargedHadrCand_phi	= patTau_leadPFChargedHadrCand_phi[i];
      tau[i].leadPFChargedHadrCand_theta	= patTau_leadPFChargedHadrCand_theta[i];
      tau[i].leadPFChargedHadrCand_eta	= patTau_leadPFChargedHadrCand_eta[i];
      tau[i].leadPFChargedHadrCand_rapidity	= patTau_leadPFChargedHadrCand_rapidity[i];
      tau[i].leadPFChargedHadrCand_y	= patTau_leadPFChargedHadrCand_y[i];
      tau[i].signalPFChargedHadrCands_size	= patTau_signalPFChargedHadrCands_size[i];
    }
}

inline void fillrecoGenParticleHelper()
{
  genparticlehelper.resize(recoGenParticleHelper_firstMother.size());
  for(unsigned int i=0; i < genparticlehelper.size(); ++i)
    {
      genparticlehelper[i].firstMother	= recoGenParticleHelper_firstMother[i];
      genparticlehelper[i].lastMother	= recoGenParticleHelper_lastMother[i];
      genparticlehelper[i].firstDaughter	= recoGenParticleHelper_firstDaughter[i];
      genparticlehelper[i].lastDaughter	= recoGenParticleHelper_lastDaughter[i];
      genparticlehelper[i].charge	= recoGenParticleHelper_charge[i];
      genparticlehelper[i].pdgId	= recoGenParticleHelper_pdgId[i];
      genparticlehelper[i].status	= recoGenParticleHelper_status[i];
      genparticlehelper[i].pt	= recoGenParticleHelper_pt[i];
      genparticlehelper[i].eta	= recoGenParticleHelper_eta[i];
      genparticlehelper[i].phi	= recoGenParticleHelper_phi[i];
      genparticlehelper[i].mass	= recoGenParticleHelper_mass[i];
    }
}

inline void fillrecoGenParticleHelperPlus()
{
  genparticlehelperplus.resize(recoGenParticleHelperPlus_firstMother.size());
  for(unsigned int i=0; i < genparticlehelperplus.size(); ++i)
    {
      genparticlehelperplus[i].firstMother	= recoGenParticleHelperPlus_firstMother[i];
      genparticlehelperplus[i].lastMother	= recoGenParticleHelperPlus_lastMother[i];
      genparticlehelperplus[i].firstDaughter	= recoGenParticleHelperPlus_firstDaughter[i];
      genparticlehelperplus[i].lastDaughter	= recoGenParticleHelperPlus_lastDaughter[i];
      genparticlehelperplus[i].charge	= recoGenParticleHelperPlus_charge[i];
      genparticlehelperplus[i].pdgId	= recoGenParticleHelperPlus_pdgId[i];
      genparticlehelperplus[i].status	= recoGenParticleHelperPlus_status[i];
      genparticlehelperplus[i].pt	= recoGenParticleHelperPlus_pt[i];
      genparticlehelperplus[i].eta	= recoGenParticleHelperPlus_eta[i];
      genparticlehelperplus[i].phi	= recoGenParticleHelperPlus_phi[i];
      genparticlehelperplus[i].mass	= recoGenParticleHelperPlus_mass[i];
    }
}

inline void fillrecoGsfElectron()
{
  recoGsfElectron.resize(recoGsfElectron_p.size());
  for(unsigned int i=0; i < recoGsfElectron.size(); ++i)
    {
      recoGsfElectron[i].p	= recoGsfElectron_p[i];
      recoGsfElectron[i].energy	= recoGsfElectron_energy[i];
      recoGsfElectron[i].et	= recoGsfElectron_et[i];
      recoGsfElectron[i].px	= recoGsfElectron_px[i];
      recoGsfElectron[i].py	= recoGsfElectron_py[i];
      recoGsfElectron[i].pz	= recoGsfElectron_pz[i];
      recoGsfElectron[i].pt	= recoGsfElectron_pt[i];
      recoGsfElectron[i].phi	= recoGsfElectron_phi[i];
      recoGsfElectron[i].eta	= recoGsfElectron_eta[i];
      recoGsfElectron[i].eSuperClusterOverP	= recoGsfElectron_eSuperClusterOverP[i];
      recoGsfElectron[i].deltaEtaSuperClusterTrackAtVtx	= recoGsfElectron_deltaEtaSuperClusterTrackAtVtx[i];
      recoGsfElectron[i].deltaPhiSuperClusterTrackAtVtx	= recoGsfElectron_deltaPhiSuperClusterTrackAtVtx[i];
      recoGsfElectron[i].sigmaIetaIeta	= recoGsfElectron_sigmaIetaIeta[i];
      recoGsfElectron[i].scE1x5	= recoGsfElectron_scE1x5[i];
      recoGsfElectron[i].scE2x5Max	= recoGsfElectron_scE2x5Max[i];
      recoGsfElectron[i].scE5x5	= recoGsfElectron_scE5x5[i];
      recoGsfElectron[i].hadronicOverEm	= recoGsfElectron_hadronicOverEm[i];
      recoGsfElectron[i].dr04TkSumPt	= recoGsfElectron_dr04TkSumPt[i];
      recoGsfElectron[i].dr04EcalRecHitSumEt	= recoGsfElectron_dr04EcalRecHitSumEt[i];
      recoGsfElectron[i].gsfTrack_dxy	= recoGsfElectron_gsfTrack_dxy[i];
      recoGsfElectron[i].gsfTrack_d0	= recoGsfElectron_gsfTrack_d0[i];
      recoGsfElectron[i].gsfTrack_dz	= recoGsfElectron_gsfTrack_dz[i];
    }
}

inline void fillrecoPFMET()
{
  recoPFMET.resize(recoPFMET_p.size());
  for(unsigned int i=0; i < recoPFMET.size(); ++i)
    {
      recoPFMET[i].p	= recoPFMET_p[i];
      recoPFMET[i].energy	= recoPFMET_energy[i];
      recoPFMET[i].et	= recoPFMET_et[i];
      recoPFMET[i].px	= recoPFMET_px[i];
      recoPFMET[i].py	= recoPFMET_py[i];
      recoPFMET[i].pz	= recoPFMET_pz[i];
      recoPFMET[i].pt	= recoPFMET_pt[i];
      recoPFMET[i].phi	= recoPFMET_phi[i];
      recoPFMET[i].eta	= recoPFMET_eta[i];
    }
}

inline void fillrecoPFMET1()
{
  recoPFMET1.resize(recoPFMET1_p.size());
  for(unsigned int i=0; i < recoPFMET1.size(); ++i)
    {
      recoPFMET1[i].p	= recoPFMET1_p[i];
      recoPFMET1[i].energy	= recoPFMET1_energy[i];
      recoPFMET1[i].et	= recoPFMET1_et[i];
      recoPFMET1[i].px	= recoPFMET1_px[i];
      recoPFMET1[i].py	= recoPFMET1_py[i];
      recoPFMET1[i].pz	= recoPFMET1_pz[i];
      recoPFMET1[i].pt	= recoPFMET1_pt[i];
      recoPFMET1[i].phi	= recoPFMET1_phi[i];
      recoPFMET1[i].eta	= recoPFMET1_eta[i];
    }
}

inline void fillrecoVertex()
{
  vertex.resize(recoVertex_isFake.size());
  for(unsigned int i=0; i < vertex.size(); ++i)
    {
      vertex[i].isFake	= recoVertex_isFake[i];
      vertex[i].ndof	= recoVertex_ndof[i];
      vertex[i].x	= recoVertex_x[i];
      vertex[i].y	= recoVertex_y[i];
      vertex[i].z	= recoVertex_z[i];
    }
}


void fillObjects()
{
  fillPileupSummaryInfo();
  fillak5GenJets();
  fillpatElectron();
  fillpatJet();
  fillpatMET();
  fillpatMuon();
  fillpatTau();
  fillrecoGenParticleHelper();
  fillrecoGenParticleHelperPlus();
  fillrecoGsfElectron();
  fillrecoPFMET();
  fillrecoPFMET1();
  fillrecoVertex();
}

//-----------------------------------------------------------------------------
// --- Call saveSelectedObjects() just before call to addEvent if
// --- you wish to save only the selected objects
//-----------------------------------------------------------------------------
// Select objects for which the select function was called
void saveSelectedObjects()
{
  int n = 0;

  n = 0;
  try
    {
       n = indexmap["PileupSummaryInfo"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["PileupSummaryInfo"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          PileupSummaryInfo_getBunchCrossing[i]	= PileupSummaryInfo_getBunchCrossing[j];
          PileupSummaryInfo_getPU_NumInteractions[i]	= PileupSummaryInfo_getPU_NumInteractions[j];
        }
      nPileupSummaryInfo = n;
    }

  n = 0;
  try
    {
       n = indexmap["ak5GenJets"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["ak5GenJets"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          ak5GenJets_charge[i]	= ak5GenJets_charge[j];
          ak5GenJets_pt[i]	= ak5GenJets_pt[j];
          ak5GenJets_eta[i]	= ak5GenJets_eta[j];
          ak5GenJets_phi[i]	= ak5GenJets_phi[j];
          ak5GenJets_mass[i]	= ak5GenJets_mass[j];
        }
      nak5GenJets = n;
    }

  n = 0;
  try
    {
       n = indexmap["patElectron"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patElectron"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patElectron_p[i]	= patElectron_p[j];
          patElectron_energy[i]	= patElectron_energy[j];
          patElectron_et[i]	= patElectron_et[j];
          patElectron_px[i]	= patElectron_px[j];
          patElectron_py[i]	= patElectron_py[j];
          patElectron_pz[i]	= patElectron_pz[j];
          patElectron_pt[i]	= patElectron_pt[j];
          patElectron_phi[i]	= patElectron_phi[j];
          patElectron_eta[i]	= patElectron_eta[j];
          patElectron_eSuperClusterOverP[i]	= patElectron_eSuperClusterOverP[j];
          patElectron_deltaEtaSuperClusterTrackAtVtx[i]	= patElectron_deltaEtaSuperClusterTrackAtVtx[j];
          patElectron_deltaPhiSuperClusterTrackAtVtx[i]	= patElectron_deltaPhiSuperClusterTrackAtVtx[j];
          patElectron_sigmaIetaIeta[i]	= patElectron_sigmaIetaIeta[j];
          patElectron_scE1x5[i]	= patElectron_scE1x5[j];
          patElectron_scE2x5Max[i]	= patElectron_scE2x5Max[j];
          patElectron_scE5x5[i]	= patElectron_scE5x5[j];
          patElectron_hadronicOverEm[i]	= patElectron_hadronicOverEm[j];
          patElectron_dr04TkSumPt[i]	= patElectron_dr04TkSumPt[j];
          patElectron_dr04EcalRecHitSumEt[i]	= patElectron_dr04EcalRecHitSumEt[j];
          patElectron_gsfTrack_dxy[i]	= patElectron_gsfTrack_dxy[j];
          patElectron_gsfTrack_d0[i]	= patElectron_gsfTrack_d0[j];
          patElectron_gsfTrack_dz[i]	= patElectron_gsfTrack_dz[j];
        }
      npatElectron = n;
    }

  n = 0;
  try
    {
       n = indexmap["patJet"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patJet"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patJet_charge[i]	= patJet_charge[j];
          patJet_p[i]	= patJet_p[j];
          patJet_energy[i]	= patJet_energy[j];
          patJet_et[i]	= patJet_et[j];
          patJet_px[i]	= patJet_px[j];
          patJet_py[i]	= patJet_py[j];
          patJet_pz[i]	= patJet_pz[j];
          patJet_pt[i]	= patJet_pt[j];
          patJet_phi[i]	= patJet_phi[j];
          patJet_eta[i]	= patJet_eta[j];
          patJet_neutralHadronEnergy[i]	= patJet_neutralHadronEnergy[j];
          patJet_chargedHadronEnergyFraction[i]	= patJet_chargedHadronEnergyFraction[j];
          patJet_neutralHadronEnergyFraction[i]	= patJet_neutralHadronEnergyFraction[j];
          patJet_chargedEmEnergyFraction[i]	= patJet_chargedEmEnergyFraction[j];
          patJet_neutralEmEnergyFraction[i]	= patJet_neutralEmEnergyFraction[j];
          patJet_photonEnergy[i]	= patJet_photonEnergy[j];
          patJet_photonEnergyFraction[i]	= patJet_photonEnergyFraction[j];
          patJet_electronEnergy[i]	= patJet_electronEnergy[j];
          patJet_electronEnergyFraction[i]	= patJet_electronEnergyFraction[j];
          patJet_muonEnergy[i]	= patJet_muonEnergy[j];
          patJet_muonEnergyFraction[i]	= patJet_muonEnergyFraction[j];
          patJet_HFHadronEnergy[i]	= patJet_HFHadronEnergy[j];
          patJet_HFHadronEnergyFraction[i]	= patJet_HFHadronEnergyFraction[j];
          patJet_HFEMEnergy[i]	= patJet_HFEMEnergy[j];
          patJet_HFEMEnergyFraction[i]	= patJet_HFEMEnergyFraction[j];
          patJet_chargedHadronMultiplicity[i]	= patJet_chargedHadronMultiplicity[j];
          patJet_neutralHadronMultiplicity[i]	= patJet_neutralHadronMultiplicity[j];
          patJet_photonMultiplicity[i]	= patJet_photonMultiplicity[j];
          patJet_electronMultiplicity[i]	= patJet_electronMultiplicity[j];
          patJet_HFHadronMultiplicity[i]	= patJet_HFHadronMultiplicity[j];
          patJet_HFEMMultiplicity[i]	= patJet_HFEMMultiplicity[j];
          patJet_numberOfDaughters[i]	= patJet_numberOfDaughters[j];
          patJet_bDiscriminator_impactParameterTagInfos[i]	= patJet_bDiscriminator_impactParameterTagInfos[j];
          patJet_bDiscriminator_secondaryVertexTagInfos[i]	= patJet_bDiscriminator_secondaryVertexTagInfos[j];
          patJet_bDiscriminator_softMuonTagInfos[i]	= patJet_bDiscriminator_softMuonTagInfos[j];
          patJet_bDiscriminator_secondaryVertexNegativeTagInfos[i]	= patJet_bDiscriminator_secondaryVertexNegativeTagInfos[j];
          patJet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos[i]	= patJet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos[j];
          patJet_bDiscriminator_softElectronTagInfos[i]	= patJet_bDiscriminator_softElectronTagInfos[j];
          patJet_bDiscriminator_jetBProbabilityBJetTags[i]	= patJet_bDiscriminator_jetBProbabilityBJetTags[j];
          patJet_bDiscriminator_jetProbabilityBJetTags[i]	= patJet_bDiscriminator_jetProbabilityBJetTags[j];
          patJet_bDiscriminator_trackCountingHighPurBJetTags[i]	= patJet_bDiscriminator_trackCountingHighPurBJetTags[j];
          patJet_bDiscriminator_trackCountingHighEffBJetTags[i]	= patJet_bDiscriminator_trackCountingHighEffBJetTags[j];
          patJet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags[i]	= patJet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags[j];
          patJet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags[i]	= patJet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags[j];
          patJet_bDiscriminator_combinedSecondaryVertexBJetTags[i]	= patJet_bDiscriminator_combinedSecondaryVertexBJetTags[j];
          patJet_bDiscriminator_combinedSecondaryVertexMVABJetTags[i]	= patJet_bDiscriminator_combinedSecondaryVertexMVABJetTags[j];
          patJet_bDiscriminator_softMuonBJetTags[i]	= patJet_bDiscriminator_softMuonBJetTags[j];
          patJet_bDiscriminator_softMuonByPtBJetTags[i]	= patJet_bDiscriminator_softMuonByPtBJetTags[j];
          patJet_bDiscriminator_softMuonByIP3dBJetTags[i]	= patJet_bDiscriminator_softMuonByIP3dBJetTags[j];
          patJet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags[i]	= patJet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags[j];
          patJet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags[i]	= patJet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags[j];
          patJet_bDiscriminator_negativeTrackCountingHighEffJetTags[i]	= patJet_bDiscriminator_negativeTrackCountingHighEffJetTags[j];
          patJet_bDiscriminator_negativeTrackCountingHighPurJetTags[i]	= patJet_bDiscriminator_negativeTrackCountingHighPurJetTags[j];
          patJet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags[i]	= patJet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags[j];
          patJet_bDiscriminator_combinedMVABJetTags[i]	= patJet_bDiscriminator_combinedMVABJetTags[j];
        }
      npatJet = n;
    }

  n = 0;
  try
    {
       n = indexmap["patMET"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patMET"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patMET_p[i]	= patMET_p[j];
          patMET_energy[i]	= patMET_energy[j];
          patMET_et[i]	= patMET_et[j];
          patMET_px[i]	= patMET_px[j];
          patMET_py[i]	= patMET_py[j];
          patMET_pz[i]	= patMET_pz[j];
          patMET_pt[i]	= patMET_pt[j];
          patMET_phi[i]	= patMET_phi[j];
          patMET_eta[i]	= patMET_eta[j];
        }
      npatMET = n;
    }

  n = 0;
  try
    {
       n = indexmap["patMuon"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patMuon"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patMuon_p[i]	= patMuon_p[j];
          patMuon_energy[i]	= patMuon_energy[j];
          patMuon_et[i]	= patMuon_et[j];
          patMuon_px[i]	= patMuon_px[j];
          patMuon_py[i]	= patMuon_py[j];
          patMuon_pz[i]	= patMuon_pz[j];
          patMuon_pt[i]	= patMuon_pt[j];
          patMuon_phi[i]	= patMuon_phi[j];
          patMuon_eta[i]	= patMuon_eta[j];
          patMuon_isGlobalMuon[i]	= patMuon_isGlobalMuon[j];
          patMuon_isTrackerMuon[i]	= patMuon_isTrackerMuon[j];
          patMuon_isPFMuon[i]	= patMuon_isPFMuon[j];
          patMuon_pfIsolationR03_sumChargedHadronPt[i]	= patMuon_pfIsolationR03_sumChargedHadronPt[j];
          patMuon_pfIsolationR03_sumChargedParticlePt[i]	= patMuon_pfIsolationR03_sumChargedParticlePt[j];
          patMuon_pfIsolationR03_sumNeutralHadronEt[i]	= patMuon_pfIsolationR03_sumNeutralHadronEt[j];
          patMuon_pfIsolationR03_sumNeutralHadronEtHighThreshold[i]	= patMuon_pfIsolationR03_sumNeutralHadronEtHighThreshold[j];
          patMuon_pfIsolationR03_sumPhotonEt[i]	= patMuon_pfIsolationR03_sumPhotonEt[j];
          patMuon_pfIsolationR03_sumPhotonEtHighThreshold[i]	= patMuon_pfIsolationR03_sumPhotonEtHighThreshold[j];
          patMuon_pfIsolationR03_sumPUPt[i]	= patMuon_pfIsolationR03_sumPUPt[j];
          patMuon_pfIsolationR04_sumChargedHadronPt[i]	= patMuon_pfIsolationR04_sumChargedHadronPt[j];
          patMuon_pfIsolationR04_sumChargedParticlePt[i]	= patMuon_pfIsolationR04_sumChargedParticlePt[j];
          patMuon_pfIsolationR04_sumNeutralHadronEt[i]	= patMuon_pfIsolationR04_sumNeutralHadronEt[j];
          patMuon_pfIsolationR04_sumNeutralHadronEtHighThreshold[i]	= patMuon_pfIsolationR04_sumNeutralHadronEtHighThreshold[j];
          patMuon_pfIsolationR04_sumPhotonEt[i]	= patMuon_pfIsolationR04_sumPhotonEt[j];
          patMuon_pfIsolationR04_sumPhotonEtHighThreshold[i]	= patMuon_pfIsolationR04_sumPhotonEtHighThreshold[j];
          patMuon_pfIsolationR04_sumPUPt[i]	= patMuon_pfIsolationR04_sumPUPt[j];
          patMuon_numberOfMatchedStations[i]	= patMuon_numberOfMatchedStations[j];
          patMuon_innerTrack_normalizedChi2[i]	= patMuon_innerTrack_normalizedChi2[j];
          patMuon_innerTrack_dxy[i]	= patMuon_innerTrack_dxy[j];
          patMuon_innerTrack_dz[i]	= patMuon_innerTrack_dz[j];
          patMuon_innerTrack_hitPattern_numberOfValidPixelHits[i]	= patMuon_innerTrack_hitPattern_numberOfValidPixelHits[j];
          patMuon_innerTrack_hitPattern_pixelLayersWithMeasurement[i]	= patMuon_innerTrack_hitPattern_pixelLayersWithMeasurement[j];
          patMuon_globalTrack_normalizedChi2[i]	= patMuon_globalTrack_normalizedChi2[j];
          patMuon_globalTrack_hitPattern_numberOfValidMuonHits[i]	= patMuon_globalTrack_hitPattern_numberOfValidMuonHits[j];
          patMuon_muonBestTrack_dxy[i]	= patMuon_muonBestTrack_dxy[j];
          patMuon_muonBestTrack_dz[i]	= patMuon_muonBestTrack_dz[j];
        }
      npatMuon = n;
    }

  n = 0;
  try
    {
       n = indexmap["patTau"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patTau"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patTau_charge[i]	= patTau_charge[j];
          patTau_p[i]	= patTau_p[j];
          patTau_energy[i]	= patTau_energy[j];
          patTau_et[i]	= patTau_et[j];
          patTau_px[i]	= patTau_px[j];
          patTau_py[i]	= patTau_py[j];
          patTau_pz[i]	= patTau_pz[j];
          patTau_pt[i]	= patTau_pt[j];
          patTau_phi[i]	= patTau_phi[j];
          patTau_eta[i]	= patTau_eta[j];
          patTau_vx[i]	= patTau_vx[j];
          patTau_vy[i]	= patTau_vy[j];
          patTau_vz[i]	= patTau_vz[j];
          patTau_tauID_againstElectronDeadECAL[i]	= patTau_tauID_againstElectronDeadECAL[j];
          patTau_tauID_againstElectronLoose[i]	= patTau_tauID_againstElectronLoose[j];
          patTau_tauID_againstElectronLooseMVA5[i]	= patTau_tauID_againstElectronLooseMVA5[j];
          patTau_tauID_againstElectronMVA5category[i]	= patTau_tauID_againstElectronMVA5category[j];
          patTau_tauID_againstElectronMVA5raw[i]	= patTau_tauID_againstElectronMVA5raw[j];
          patTau_tauID_againstElectronMedium[i]	= patTau_tauID_againstElectronMedium[j];
          patTau_tauID_againstElectronMediumMVA5[i]	= patTau_tauID_againstElectronMediumMVA5[j];
          patTau_tauID_againstElectronTight[i]	= patTau_tauID_againstElectronTight[j];
          patTau_tauID_againstElectronTightMVA5[i]	= patTau_tauID_againstElectronTightMVA5[j];
          patTau_tauID_againstElectronVLooseMVA5[i]	= patTau_tauID_againstElectronVLooseMVA5[j];
          patTau_tauID_againstElectronVTightMVA5[i]	= patTau_tauID_againstElectronVTightMVA5[j];
          patTau_tauID_againstMuonLoose[i]	= patTau_tauID_againstMuonLoose[j];
          patTau_tauID_againstMuonLoose2[i]	= patTau_tauID_againstMuonLoose2[j];
          patTau_tauID_againstMuonLoose3[i]	= patTau_tauID_againstMuonLoose3[j];
          patTau_tauID_againstMuonLooseMVA[i]	= patTau_tauID_againstMuonLooseMVA[j];
          patTau_tauID_againstMuonMVAraw[i]	= patTau_tauID_againstMuonMVAraw[j];
          patTau_tauID_againstMuonMedium[i]	= patTau_tauID_againstMuonMedium[j];
          patTau_tauID_againstMuonMedium2[i]	= patTau_tauID_againstMuonMedium2[j];
          patTau_tauID_againstMuonMediumMVA[i]	= patTau_tauID_againstMuonMediumMVA[j];
          patTau_tauID_againstMuonTight[i]	= patTau_tauID_againstMuonTight[j];
          patTau_tauID_againstMuonTight2[i]	= patTau_tauID_againstMuonTight2[j];
          patTau_tauID_againstMuonTight3[i]	= patTau_tauID_againstMuonTight3[j];
          patTau_tauID_againstMuonTightMVA[i]	= patTau_tauID_againstMuonTightMVA[j];
          patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw[i]	= patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw[j];
          patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[i]	= patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[j];
          patTau_tauID_byIsolationMVA3newDMwLTraw[i]	= patTau_tauID_byIsolationMVA3newDMwLTraw[j];
          patTau_tauID_byIsolationMVA3newDMwoLTraw[i]	= patTau_tauID_byIsolationMVA3newDMwoLTraw[j];
          patTau_tauID_byIsolationMVA3oldDMwLTraw[i]	= patTau_tauID_byIsolationMVA3oldDMwLTraw[j];
          patTau_tauID_byIsolationMVA3oldDMwoLTraw[i]	= patTau_tauID_byIsolationMVA3oldDMwoLTraw[j];
          patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr[i]	= patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr[j];
          patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[i]	= patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[j];
          patTau_tauID_byLooseIsolation[i]	= patTau_tauID_byLooseIsolation[j];
          patTau_tauID_byLooseIsolationMVA3newDMwLT[i]	= patTau_tauID_byLooseIsolationMVA3newDMwLT[j];
          patTau_tauID_byLooseIsolationMVA3newDMwoLT[i]	= patTau_tauID_byLooseIsolationMVA3newDMwoLT[j];
          patTau_tauID_byLooseIsolationMVA3oldDMwLT[i]	= patTau_tauID_byLooseIsolationMVA3oldDMwLT[j];
          patTau_tauID_byLooseIsolationMVA3oldDMwoLT[i]	= patTau_tauID_byLooseIsolationMVA3oldDMwoLT[j];
          patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr[i]	= patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr[j];
          patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[i]	= patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[j];
          patTau_tauID_byMediumIsolationMVA3newDMwLT[i]	= patTau_tauID_byMediumIsolationMVA3newDMwLT[j];
          patTau_tauID_byMediumIsolationMVA3newDMwoLT[i]	= patTau_tauID_byMediumIsolationMVA3newDMwoLT[j];
          patTau_tauID_byMediumIsolationMVA3oldDMwLT[i]	= patTau_tauID_byMediumIsolationMVA3oldDMwLT[j];
          patTau_tauID_byMediumIsolationMVA3oldDMwoLT[i]	= patTau_tauID_byMediumIsolationMVA3oldDMwoLT[j];
          patTau_tauID_byTightCombinedIsolationDeltaBetaCorr[i]	= patTau_tauID_byTightCombinedIsolationDeltaBetaCorr[j];
          patTau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[i]	= patTau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[j];
          patTau_tauID_byTightIsolationMVA3newDMwLT[i]	= patTau_tauID_byTightIsolationMVA3newDMwLT[j];
          patTau_tauID_byTightIsolationMVA3newDMwoLT[i]	= patTau_tauID_byTightIsolationMVA3newDMwoLT[j];
          patTau_tauID_byTightIsolationMVA3oldDMwLT[i]	= patTau_tauID_byTightIsolationMVA3oldDMwLT[j];
          patTau_tauID_byTightIsolationMVA3oldDMwoLT[i]	= patTau_tauID_byTightIsolationMVA3oldDMwoLT[j];
          patTau_tauID_byVLooseCombinedIsolationDeltaBetaCorr[i]	= patTau_tauID_byVLooseCombinedIsolationDeltaBetaCorr[j];
          patTau_tauID_byVLooseIsolationMVA3newDMwLT[i]	= patTau_tauID_byVLooseIsolationMVA3newDMwLT[j];
          patTau_tauID_byVLooseIsolationMVA3newDMwoLT[i]	= patTau_tauID_byVLooseIsolationMVA3newDMwoLT[j];
          patTau_tauID_byVLooseIsolationMVA3oldDMwLT[i]	= patTau_tauID_byVLooseIsolationMVA3oldDMwLT[j];
          patTau_tauID_byVLooseIsolationMVA3oldDMwoLT[i]	= patTau_tauID_byVLooseIsolationMVA3oldDMwoLT[j];
          patTau_tauID_byVTightIsolationMVA3newDMwLT[i]	= patTau_tauID_byVTightIsolationMVA3newDMwLT[j];
          patTau_tauID_byVTightIsolationMVA3newDMwoLT[i]	= patTau_tauID_byVTightIsolationMVA3newDMwoLT[j];
          patTau_tauID_byVTightIsolationMVA3oldDMwLT[i]	= patTau_tauID_byVTightIsolationMVA3oldDMwLT[j];
          patTau_tauID_byVTightIsolationMVA3oldDMwoLT[i]	= patTau_tauID_byVTightIsolationMVA3oldDMwoLT[j];
          patTau_tauID_byVVTightIsolationMVA3newDMwLT[i]	= patTau_tauID_byVVTightIsolationMVA3newDMwLT[j];
          patTau_tauID_byVVTightIsolationMVA3newDMwoLT[i]	= patTau_tauID_byVVTightIsolationMVA3newDMwoLT[j];
          patTau_tauID_byVVTightIsolationMVA3oldDMwLT[i]	= patTau_tauID_byVVTightIsolationMVA3oldDMwLT[j];
          patTau_tauID_byVVTightIsolationMVA3oldDMwoLT[i]	= patTau_tauID_byVVTightIsolationMVA3oldDMwoLT[j];
          patTau_tauID_chargedIsoPtSum[i]	= patTau_tauID_chargedIsoPtSum[j];
          patTau_tauID_decayModeFinding[i]	= patTau_tauID_decayModeFinding[j];
          patTau_tauID_decayModeFindingNewDMs[i]	= patTau_tauID_decayModeFindingNewDMs[j];
          patTau_tauID_decayModeFindingOldDMs[i]	= patTau_tauID_decayModeFindingOldDMs[j];
          patTau_tauID_neutralIsoPtSum[i]	= patTau_tauID_neutralIsoPtSum[j];
          patTau_tauID_puCorrPtSum[i]	= patTau_tauID_puCorrPtSum[j];
          patTau_leadPFChargedHadrCand_p[i]	= patTau_leadPFChargedHadrCand_p[j];
          patTau_leadPFChargedHadrCand_energy[i]	= patTau_leadPFChargedHadrCand_energy[j];
          patTau_leadPFChargedHadrCand_et[i]	= patTau_leadPFChargedHadrCand_et[j];
          patTau_leadPFChargedHadrCand_mass[i]	= patTau_leadPFChargedHadrCand_mass[j];
          patTau_leadPFChargedHadrCand_massSqr[i]	= patTau_leadPFChargedHadrCand_massSqr[j];
          patTau_leadPFChargedHadrCand_mt[i]	= patTau_leadPFChargedHadrCand_mt[j];
          patTau_leadPFChargedHadrCand_mtSqr[i]	= patTau_leadPFChargedHadrCand_mtSqr[j];
          patTau_leadPFChargedHadrCand_px[i]	= patTau_leadPFChargedHadrCand_px[j];
          patTau_leadPFChargedHadrCand_py[i]	= patTau_leadPFChargedHadrCand_py[j];
          patTau_leadPFChargedHadrCand_pz[i]	= patTau_leadPFChargedHadrCand_pz[j];
          patTau_leadPFChargedHadrCand_pt[i]	= patTau_leadPFChargedHadrCand_pt[j];
          patTau_leadPFChargedHadrCand_phi[i]	= patTau_leadPFChargedHadrCand_phi[j];
          patTau_leadPFChargedHadrCand_theta[i]	= patTau_leadPFChargedHadrCand_theta[j];
          patTau_leadPFChargedHadrCand_eta[i]	= patTau_leadPFChargedHadrCand_eta[j];
          patTau_leadPFChargedHadrCand_rapidity[i]	= patTau_leadPFChargedHadrCand_rapidity[j];
          patTau_leadPFChargedHadrCand_y[i]	= patTau_leadPFChargedHadrCand_y[j];
	  patTau_signalPFChargedHadrCands_size[i]	= patTau_signalPFChargedHadrCands_size[j];
        }
      npatTau = n;
    }

  n = 0;
  try
    {
       n = indexmap["recoGenParticleHelper"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["recoGenParticleHelper"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          recoGenParticleHelper_firstMother[i]	= recoGenParticleHelper_firstMother[j];
          recoGenParticleHelper_lastMother[i]	= recoGenParticleHelper_lastMother[j];
          recoGenParticleHelper_firstDaughter[i]	= recoGenParticleHelper_firstDaughter[j];
          recoGenParticleHelper_lastDaughter[i]	= recoGenParticleHelper_lastDaughter[j];
          recoGenParticleHelper_charge[i]	= recoGenParticleHelper_charge[j];
          recoGenParticleHelper_pdgId[i]	= recoGenParticleHelper_pdgId[j];
          recoGenParticleHelper_status[i]	= recoGenParticleHelper_status[j];
          recoGenParticleHelper_pt[i]	= recoGenParticleHelper_pt[j];
          recoGenParticleHelper_eta[i]	= recoGenParticleHelper_eta[j];
          recoGenParticleHelper_phi[i]	= recoGenParticleHelper_phi[j];
          recoGenParticleHelper_mass[i]	= recoGenParticleHelper_mass[j];
        }
      nrecoGenParticleHelper = n;
    }

  n = 0;
  try
    {
       n = indexmap["recoGenParticleHelperPlus"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["recoGenParticleHelperPlus"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          recoGenParticleHelperPlus_firstMother[i]	= recoGenParticleHelperPlus_firstMother[j];
          recoGenParticleHelperPlus_lastMother[i]	= recoGenParticleHelperPlus_lastMother[j];
          recoGenParticleHelperPlus_firstDaughter[i]	= recoGenParticleHelperPlus_firstDaughter[j];
          recoGenParticleHelperPlus_lastDaughter[i]	= recoGenParticleHelperPlus_lastDaughter[j];
          recoGenParticleHelperPlus_charge[i]	= recoGenParticleHelperPlus_charge[j];
          recoGenParticleHelperPlus_pdgId[i]	= recoGenParticleHelperPlus_pdgId[j];
          recoGenParticleHelperPlus_status[i]	= recoGenParticleHelperPlus_status[j];
          recoGenParticleHelperPlus_pt[i]	= recoGenParticleHelperPlus_pt[j];
          recoGenParticleHelperPlus_eta[i]	= recoGenParticleHelperPlus_eta[j];
          recoGenParticleHelperPlus_phi[i]	= recoGenParticleHelperPlus_phi[j];
          recoGenParticleHelperPlus_mass[i]	= recoGenParticleHelperPlus_mass[j];
        }
      nrecoGenParticleHelperPlus = n;
    }

  n = 0;
  try
    {
       n = indexmap["recoGsfElectron"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["recoGsfElectron"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          recoGsfElectron_p[i]	= recoGsfElectron_p[j];
          recoGsfElectron_energy[i]	= recoGsfElectron_energy[j];
          recoGsfElectron_et[i]	= recoGsfElectron_et[j];
          recoGsfElectron_px[i]	= recoGsfElectron_px[j];
          recoGsfElectron_py[i]	= recoGsfElectron_py[j];
          recoGsfElectron_pz[i]	= recoGsfElectron_pz[j];
          recoGsfElectron_pt[i]	= recoGsfElectron_pt[j];
          recoGsfElectron_phi[i]	= recoGsfElectron_phi[j];
          recoGsfElectron_eta[i]	= recoGsfElectron_eta[j];
          recoGsfElectron_eSuperClusterOverP[i]	= recoGsfElectron_eSuperClusterOverP[j];
          recoGsfElectron_deltaEtaSuperClusterTrackAtVtx[i]	= recoGsfElectron_deltaEtaSuperClusterTrackAtVtx[j];
          recoGsfElectron_deltaPhiSuperClusterTrackAtVtx[i]	= recoGsfElectron_deltaPhiSuperClusterTrackAtVtx[j];
          recoGsfElectron_sigmaIetaIeta[i]	= recoGsfElectron_sigmaIetaIeta[j];
          recoGsfElectron_scE1x5[i]	= recoGsfElectron_scE1x5[j];
          recoGsfElectron_scE2x5Max[i]	= recoGsfElectron_scE2x5Max[j];
          recoGsfElectron_scE5x5[i]	= recoGsfElectron_scE5x5[j];
          recoGsfElectron_hadronicOverEm[i]	= recoGsfElectron_hadronicOverEm[j];
          recoGsfElectron_dr04TkSumPt[i]	= recoGsfElectron_dr04TkSumPt[j];
          recoGsfElectron_dr04EcalRecHitSumEt[i]	= recoGsfElectron_dr04EcalRecHitSumEt[j];
          recoGsfElectron_gsfTrack_dxy[i]	= recoGsfElectron_gsfTrack_dxy[j];
          recoGsfElectron_gsfTrack_d0[i]	= recoGsfElectron_gsfTrack_d0[j];
          recoGsfElectron_gsfTrack_dz[i]	= recoGsfElectron_gsfTrack_dz[j];
        }
      nrecoGsfElectron = n;
    }

  n = 0;
  try
    {
       n = indexmap["recoPFMET"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["recoPFMET"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          recoPFMET_p[i]	= recoPFMET_p[j];
          recoPFMET_energy[i]	= recoPFMET_energy[j];
          recoPFMET_et[i]	= recoPFMET_et[j];
          recoPFMET_px[i]	= recoPFMET_px[j];
          recoPFMET_py[i]	= recoPFMET_py[j];
          recoPFMET_pz[i]	= recoPFMET_pz[j];
          recoPFMET_pt[i]	= recoPFMET_pt[j];
          recoPFMET_phi[i]	= recoPFMET_phi[j];
          recoPFMET_eta[i]	= recoPFMET_eta[j];
        }
      nrecoPFMET = n;
    }

  n = 0;
  try
    {
       n = indexmap["recoPFMET1"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["recoPFMET1"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          recoPFMET1_p[i]	= recoPFMET1_p[j];
          recoPFMET1_energy[i]	= recoPFMET1_energy[j];
          recoPFMET1_et[i]	= recoPFMET1_et[j];
          recoPFMET1_px[i]	= recoPFMET1_px[j];
          recoPFMET1_py[i]	= recoPFMET1_py[j];
          recoPFMET1_pz[i]	= recoPFMET1_pz[j];
          recoPFMET1_pt[i]	= recoPFMET1_pt[j];
          recoPFMET1_phi[i]	= recoPFMET1_phi[j];
          recoPFMET1_eta[i]	= recoPFMET1_eta[j];
        }
      nrecoPFMET1 = n;
    }

  n = 0;
  try
    {
       n = indexmap["recoVertex"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["recoVertex"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          recoVertex_isFake[i]	= recoVertex_isFake[j];
          recoVertex_ndof[i]	= recoVertex_ndof[j];
          recoVertex_x[i]	= recoVertex_x[j];
          recoVertex_y[i]	= recoVertex_y[j];
          recoVertex_z[i]	= recoVertex_z[j];
        }
      nrecoVertex = n;
    }
}

//-----------------------------------------------------------------------------
// --- Select variables to be read
//-----------------------------------------------------------------------------
void selectVariables(itreestream& stream)
{
  stream.select("GenRunInfoProduct_generator.crossSection", GenRunInfoProduct_crossSection);
  stream.select("GenRunInfoProduct_generator.filterEfficiency", GenRunInfoProduct_filterEfficiency);
  stream.select("GenRunInfoProduct_generator.internalXSec_value", GenRunInfoProduct_internalXSec_value);
  stream.select("PileupSummaryInfo_addPileupInfo.getBunchCrossing", PileupSummaryInfo_getBunchCrossing);
  stream.select("PileupSummaryInfo_addPileupInfo.getPU_NumInteractions", PileupSummaryInfo_getPU_NumInteractions);
  stream.select("recoGenJet_ak5GenJets.charge", ak5GenJets_charge);
  stream.select("recoGenJet_ak5GenJets.eta", ak5GenJets_eta);
  stream.select("recoGenJet_ak5GenJets.mass", ak5GenJets_mass);
  stream.select("recoGenJet_ak5GenJets.phi", ak5GenJets_phi);
  stream.select("recoGenJet_ak5GenJets.pt", ak5GenJets_pt);
  stream.select("edmEventHelper_info.bunchCrossing", eventhelper_bunchCrossing);
  stream.select("edmEventHelper_info.event", eventhelper_event);
  stream.select("edmEventHelper_info.isRealData", eventhelper_isRealData);
  stream.select("edmEventHelper_info.luminosityBlock", eventhelper_luminosityBlock);
  stream.select("edmEventHelper_info.orbitNumber", eventhelper_orbitNumber);
  stream.select("edmEventHelper_info.run", eventhelper_run);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v1", triggerresultshelper_prescale_HLT_DiPFJetAve140_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v10", triggerresultshelper_prescale_HLT_DiPFJetAve140_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v11", triggerresultshelper_prescale_HLT_DiPFJetAve140_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v12", triggerresultshelper_prescale_HLT_DiPFJetAve140_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v13", triggerresultshelper_prescale_HLT_DiPFJetAve140_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v14", triggerresultshelper_prescale_HLT_DiPFJetAve140_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v15", triggerresultshelper_prescale_HLT_DiPFJetAve140_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v16", triggerresultshelper_prescale_HLT_DiPFJetAve140_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v17", triggerresultshelper_prescale_HLT_DiPFJetAve140_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v18", triggerresultshelper_prescale_HLT_DiPFJetAve140_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v19", triggerresultshelper_prescale_HLT_DiPFJetAve140_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v2", triggerresultshelper_prescale_HLT_DiPFJetAve140_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v20", triggerresultshelper_prescale_HLT_DiPFJetAve140_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v3", triggerresultshelper_prescale_HLT_DiPFJetAve140_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v4", triggerresultshelper_prescale_HLT_DiPFJetAve140_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v5", triggerresultshelper_prescale_HLT_DiPFJetAve140_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v6", triggerresultshelper_prescale_HLT_DiPFJetAve140_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v7", triggerresultshelper_prescale_HLT_DiPFJetAve140_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v8", triggerresultshelper_prescale_HLT_DiPFJetAve140_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve140_v9", triggerresultshelper_prescale_HLT_DiPFJetAve140_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v1", triggerresultshelper_prescale_HLT_DiPFJetAve200_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v10", triggerresultshelper_prescale_HLT_DiPFJetAve200_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v11", triggerresultshelper_prescale_HLT_DiPFJetAve200_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v12", triggerresultshelper_prescale_HLT_DiPFJetAve200_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v13", triggerresultshelper_prescale_HLT_DiPFJetAve200_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v14", triggerresultshelper_prescale_HLT_DiPFJetAve200_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v15", triggerresultshelper_prescale_HLT_DiPFJetAve200_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v16", triggerresultshelper_prescale_HLT_DiPFJetAve200_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v17", triggerresultshelper_prescale_HLT_DiPFJetAve200_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v18", triggerresultshelper_prescale_HLT_DiPFJetAve200_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v19", triggerresultshelper_prescale_HLT_DiPFJetAve200_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v2", triggerresultshelper_prescale_HLT_DiPFJetAve200_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v20", triggerresultshelper_prescale_HLT_DiPFJetAve200_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v3", triggerresultshelper_prescale_HLT_DiPFJetAve200_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v4", triggerresultshelper_prescale_HLT_DiPFJetAve200_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v5", triggerresultshelper_prescale_HLT_DiPFJetAve200_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v6", triggerresultshelper_prescale_HLT_DiPFJetAve200_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v7", triggerresultshelper_prescale_HLT_DiPFJetAve200_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v8", triggerresultshelper_prescale_HLT_DiPFJetAve200_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve200_v9", triggerresultshelper_prescale_HLT_DiPFJetAve200_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v1", triggerresultshelper_prescale_HLT_DiPFJetAve260_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v10", triggerresultshelper_prescale_HLT_DiPFJetAve260_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v11", triggerresultshelper_prescale_HLT_DiPFJetAve260_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v12", triggerresultshelper_prescale_HLT_DiPFJetAve260_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v13", triggerresultshelper_prescale_HLT_DiPFJetAve260_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v14", triggerresultshelper_prescale_HLT_DiPFJetAve260_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v15", triggerresultshelper_prescale_HLT_DiPFJetAve260_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v16", triggerresultshelper_prescale_HLT_DiPFJetAve260_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v17", triggerresultshelper_prescale_HLT_DiPFJetAve260_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v18", triggerresultshelper_prescale_HLT_DiPFJetAve260_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v19", triggerresultshelper_prescale_HLT_DiPFJetAve260_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v2", triggerresultshelper_prescale_HLT_DiPFJetAve260_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v20", triggerresultshelper_prescale_HLT_DiPFJetAve260_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v3", triggerresultshelper_prescale_HLT_DiPFJetAve260_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v4", triggerresultshelper_prescale_HLT_DiPFJetAve260_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v5", triggerresultshelper_prescale_HLT_DiPFJetAve260_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v6", triggerresultshelper_prescale_HLT_DiPFJetAve260_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v7", triggerresultshelper_prescale_HLT_DiPFJetAve260_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v8", triggerresultshelper_prescale_HLT_DiPFJetAve260_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve260_v9", triggerresultshelper_prescale_HLT_DiPFJetAve260_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v1", triggerresultshelper_prescale_HLT_DiPFJetAve320_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v10", triggerresultshelper_prescale_HLT_DiPFJetAve320_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v11", triggerresultshelper_prescale_HLT_DiPFJetAve320_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v12", triggerresultshelper_prescale_HLT_DiPFJetAve320_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v13", triggerresultshelper_prescale_HLT_DiPFJetAve320_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v14", triggerresultshelper_prescale_HLT_DiPFJetAve320_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v15", triggerresultshelper_prescale_HLT_DiPFJetAve320_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v16", triggerresultshelper_prescale_HLT_DiPFJetAve320_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v17", triggerresultshelper_prescale_HLT_DiPFJetAve320_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v18", triggerresultshelper_prescale_HLT_DiPFJetAve320_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v19", triggerresultshelper_prescale_HLT_DiPFJetAve320_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v2", triggerresultshelper_prescale_HLT_DiPFJetAve320_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v20", triggerresultshelper_prescale_HLT_DiPFJetAve320_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v3", triggerresultshelper_prescale_HLT_DiPFJetAve320_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v4", triggerresultshelper_prescale_HLT_DiPFJetAve320_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v5", triggerresultshelper_prescale_HLT_DiPFJetAve320_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v6", triggerresultshelper_prescale_HLT_DiPFJetAve320_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v7", triggerresultshelper_prescale_HLT_DiPFJetAve320_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v8", triggerresultshelper_prescale_HLT_DiPFJetAve320_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve320_v9", triggerresultshelper_prescale_HLT_DiPFJetAve320_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v1", triggerresultshelper_prescale_HLT_DiPFJetAve400_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v10", triggerresultshelper_prescale_HLT_DiPFJetAve400_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v11", triggerresultshelper_prescale_HLT_DiPFJetAve400_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v12", triggerresultshelper_prescale_HLT_DiPFJetAve400_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v13", triggerresultshelper_prescale_HLT_DiPFJetAve400_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v14", triggerresultshelper_prescale_HLT_DiPFJetAve400_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v15", triggerresultshelper_prescale_HLT_DiPFJetAve400_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v16", triggerresultshelper_prescale_HLT_DiPFJetAve400_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v17", triggerresultshelper_prescale_HLT_DiPFJetAve400_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v18", triggerresultshelper_prescale_HLT_DiPFJetAve400_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v19", triggerresultshelper_prescale_HLT_DiPFJetAve400_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v2", triggerresultshelper_prescale_HLT_DiPFJetAve400_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v20", triggerresultshelper_prescale_HLT_DiPFJetAve400_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v3", triggerresultshelper_prescale_HLT_DiPFJetAve400_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v4", triggerresultshelper_prescale_HLT_DiPFJetAve400_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v5", triggerresultshelper_prescale_HLT_DiPFJetAve400_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v6", triggerresultshelper_prescale_HLT_DiPFJetAve400_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v7", triggerresultshelper_prescale_HLT_DiPFJetAve400_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v8", triggerresultshelper_prescale_HLT_DiPFJetAve400_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve400_v9", triggerresultshelper_prescale_HLT_DiPFJetAve400_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v1", triggerresultshelper_prescale_HLT_DiPFJetAve40_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v10", triggerresultshelper_prescale_HLT_DiPFJetAve40_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v11", triggerresultshelper_prescale_HLT_DiPFJetAve40_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v12", triggerresultshelper_prescale_HLT_DiPFJetAve40_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v13", triggerresultshelper_prescale_HLT_DiPFJetAve40_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v14", triggerresultshelper_prescale_HLT_DiPFJetAve40_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v15", triggerresultshelper_prescale_HLT_DiPFJetAve40_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v16", triggerresultshelper_prescale_HLT_DiPFJetAve40_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v17", triggerresultshelper_prescale_HLT_DiPFJetAve40_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v18", triggerresultshelper_prescale_HLT_DiPFJetAve40_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v19", triggerresultshelper_prescale_HLT_DiPFJetAve40_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v2", triggerresultshelper_prescale_HLT_DiPFJetAve40_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v20", triggerresultshelper_prescale_HLT_DiPFJetAve40_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v3", triggerresultshelper_prescale_HLT_DiPFJetAve40_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v4", triggerresultshelper_prescale_HLT_DiPFJetAve40_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v5", triggerresultshelper_prescale_HLT_DiPFJetAve40_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v6", triggerresultshelper_prescale_HLT_DiPFJetAve40_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v7", triggerresultshelper_prescale_HLT_DiPFJetAve40_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v8", triggerresultshelper_prescale_HLT_DiPFJetAve40_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve40_v9", triggerresultshelper_prescale_HLT_DiPFJetAve40_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v1", triggerresultshelper_prescale_HLT_DiPFJetAve80_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v10", triggerresultshelper_prescale_HLT_DiPFJetAve80_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v11", triggerresultshelper_prescale_HLT_DiPFJetAve80_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v12", triggerresultshelper_prescale_HLT_DiPFJetAve80_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v13", triggerresultshelper_prescale_HLT_DiPFJetAve80_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v14", triggerresultshelper_prescale_HLT_DiPFJetAve80_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v15", triggerresultshelper_prescale_HLT_DiPFJetAve80_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v16", triggerresultshelper_prescale_HLT_DiPFJetAve80_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v17", triggerresultshelper_prescale_HLT_DiPFJetAve80_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v18", triggerresultshelper_prescale_HLT_DiPFJetAve80_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v19", triggerresultshelper_prescale_HLT_DiPFJetAve80_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v2", triggerresultshelper_prescale_HLT_DiPFJetAve80_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v20", triggerresultshelper_prescale_HLT_DiPFJetAve80_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v3", triggerresultshelper_prescale_HLT_DiPFJetAve80_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v4", triggerresultshelper_prescale_HLT_DiPFJetAve80_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v5", triggerresultshelper_prescale_HLT_DiPFJetAve80_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v6", triggerresultshelper_prescale_HLT_DiPFJetAve80_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v7", triggerresultshelper_prescale_HLT_DiPFJetAve80_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v8", triggerresultshelper_prescale_HLT_DiPFJetAve80_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DiPFJetAve80_v9", triggerresultshelper_prescale_HLT_DiPFJetAve80_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3", triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4", triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2", triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3", triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4", triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6", triggerresultshelper_prescale_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v1", triggerresultshelper_value_HLT_DiPFJetAve140_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v10", triggerresultshelper_value_HLT_DiPFJetAve140_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v11", triggerresultshelper_value_HLT_DiPFJetAve140_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v12", triggerresultshelper_value_HLT_DiPFJetAve140_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v13", triggerresultshelper_value_HLT_DiPFJetAve140_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v14", triggerresultshelper_value_HLT_DiPFJetAve140_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v15", triggerresultshelper_value_HLT_DiPFJetAve140_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v16", triggerresultshelper_value_HLT_DiPFJetAve140_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v17", triggerresultshelper_value_HLT_DiPFJetAve140_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v18", triggerresultshelper_value_HLT_DiPFJetAve140_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v19", triggerresultshelper_value_HLT_DiPFJetAve140_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v2", triggerresultshelper_value_HLT_DiPFJetAve140_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v20", triggerresultshelper_value_HLT_DiPFJetAve140_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v3", triggerresultshelper_value_HLT_DiPFJetAve140_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v4", triggerresultshelper_value_HLT_DiPFJetAve140_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v5", triggerresultshelper_value_HLT_DiPFJetAve140_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v6", triggerresultshelper_value_HLT_DiPFJetAve140_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v7", triggerresultshelper_value_HLT_DiPFJetAve140_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v8", triggerresultshelper_value_HLT_DiPFJetAve140_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve140_v9", triggerresultshelper_value_HLT_DiPFJetAve140_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v1", triggerresultshelper_value_HLT_DiPFJetAve200_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v10", triggerresultshelper_value_HLT_DiPFJetAve200_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v11", triggerresultshelper_value_HLT_DiPFJetAve200_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v12", triggerresultshelper_value_HLT_DiPFJetAve200_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v13", triggerresultshelper_value_HLT_DiPFJetAve200_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v14", triggerresultshelper_value_HLT_DiPFJetAve200_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v15", triggerresultshelper_value_HLT_DiPFJetAve200_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v16", triggerresultshelper_value_HLT_DiPFJetAve200_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v17", triggerresultshelper_value_HLT_DiPFJetAve200_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v18", triggerresultshelper_value_HLT_DiPFJetAve200_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v19", triggerresultshelper_value_HLT_DiPFJetAve200_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v2", triggerresultshelper_value_HLT_DiPFJetAve200_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v20", triggerresultshelper_value_HLT_DiPFJetAve200_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v3", triggerresultshelper_value_HLT_DiPFJetAve200_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v4", triggerresultshelper_value_HLT_DiPFJetAve200_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v5", triggerresultshelper_value_HLT_DiPFJetAve200_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v6", triggerresultshelper_value_HLT_DiPFJetAve200_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v7", triggerresultshelper_value_HLT_DiPFJetAve200_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v8", triggerresultshelper_value_HLT_DiPFJetAve200_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve200_v9", triggerresultshelper_value_HLT_DiPFJetAve200_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v1", triggerresultshelper_value_HLT_DiPFJetAve260_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v10", triggerresultshelper_value_HLT_DiPFJetAve260_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v11", triggerresultshelper_value_HLT_DiPFJetAve260_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v12", triggerresultshelper_value_HLT_DiPFJetAve260_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v13", triggerresultshelper_value_HLT_DiPFJetAve260_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v14", triggerresultshelper_value_HLT_DiPFJetAve260_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v15", triggerresultshelper_value_HLT_DiPFJetAve260_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v16", triggerresultshelper_value_HLT_DiPFJetAve260_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v17", triggerresultshelper_value_HLT_DiPFJetAve260_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v18", triggerresultshelper_value_HLT_DiPFJetAve260_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v19", triggerresultshelper_value_HLT_DiPFJetAve260_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v2", triggerresultshelper_value_HLT_DiPFJetAve260_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v20", triggerresultshelper_value_HLT_DiPFJetAve260_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v3", triggerresultshelper_value_HLT_DiPFJetAve260_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v4", triggerresultshelper_value_HLT_DiPFJetAve260_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v5", triggerresultshelper_value_HLT_DiPFJetAve260_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v6", triggerresultshelper_value_HLT_DiPFJetAve260_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v7", triggerresultshelper_value_HLT_DiPFJetAve260_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v8", triggerresultshelper_value_HLT_DiPFJetAve260_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve260_v9", triggerresultshelper_value_HLT_DiPFJetAve260_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v1", triggerresultshelper_value_HLT_DiPFJetAve320_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v10", triggerresultshelper_value_HLT_DiPFJetAve320_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v11", triggerresultshelper_value_HLT_DiPFJetAve320_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v12", triggerresultshelper_value_HLT_DiPFJetAve320_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v13", triggerresultshelper_value_HLT_DiPFJetAve320_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v14", triggerresultshelper_value_HLT_DiPFJetAve320_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v15", triggerresultshelper_value_HLT_DiPFJetAve320_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v16", triggerresultshelper_value_HLT_DiPFJetAve320_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v17", triggerresultshelper_value_HLT_DiPFJetAve320_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v18", triggerresultshelper_value_HLT_DiPFJetAve320_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v19", triggerresultshelper_value_HLT_DiPFJetAve320_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v2", triggerresultshelper_value_HLT_DiPFJetAve320_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v20", triggerresultshelper_value_HLT_DiPFJetAve320_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v3", triggerresultshelper_value_HLT_DiPFJetAve320_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v4", triggerresultshelper_value_HLT_DiPFJetAve320_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v5", triggerresultshelper_value_HLT_DiPFJetAve320_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v6", triggerresultshelper_value_HLT_DiPFJetAve320_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v7", triggerresultshelper_value_HLT_DiPFJetAve320_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v8", triggerresultshelper_value_HLT_DiPFJetAve320_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve320_v9", triggerresultshelper_value_HLT_DiPFJetAve320_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v1", triggerresultshelper_value_HLT_DiPFJetAve400_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v10", triggerresultshelper_value_HLT_DiPFJetAve400_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v11", triggerresultshelper_value_HLT_DiPFJetAve400_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v12", triggerresultshelper_value_HLT_DiPFJetAve400_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v13", triggerresultshelper_value_HLT_DiPFJetAve400_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v14", triggerresultshelper_value_HLT_DiPFJetAve400_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v15", triggerresultshelper_value_HLT_DiPFJetAve400_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v16", triggerresultshelper_value_HLT_DiPFJetAve400_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v17", triggerresultshelper_value_HLT_DiPFJetAve400_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v18", triggerresultshelper_value_HLT_DiPFJetAve400_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v19", triggerresultshelper_value_HLT_DiPFJetAve400_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v2", triggerresultshelper_value_HLT_DiPFJetAve400_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v20", triggerresultshelper_value_HLT_DiPFJetAve400_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v3", triggerresultshelper_value_HLT_DiPFJetAve400_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v4", triggerresultshelper_value_HLT_DiPFJetAve400_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v5", triggerresultshelper_value_HLT_DiPFJetAve400_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v6", triggerresultshelper_value_HLT_DiPFJetAve400_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v7", triggerresultshelper_value_HLT_DiPFJetAve400_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v8", triggerresultshelper_value_HLT_DiPFJetAve400_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve400_v9", triggerresultshelper_value_HLT_DiPFJetAve400_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v1", triggerresultshelper_value_HLT_DiPFJetAve40_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v10", triggerresultshelper_value_HLT_DiPFJetAve40_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v11", triggerresultshelper_value_HLT_DiPFJetAve40_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v12", triggerresultshelper_value_HLT_DiPFJetAve40_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v13", triggerresultshelper_value_HLT_DiPFJetAve40_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v14", triggerresultshelper_value_HLT_DiPFJetAve40_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v15", triggerresultshelper_value_HLT_DiPFJetAve40_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v16", triggerresultshelper_value_HLT_DiPFJetAve40_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v17", triggerresultshelper_value_HLT_DiPFJetAve40_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v18", triggerresultshelper_value_HLT_DiPFJetAve40_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v19", triggerresultshelper_value_HLT_DiPFJetAve40_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v2", triggerresultshelper_value_HLT_DiPFJetAve40_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v20", triggerresultshelper_value_HLT_DiPFJetAve40_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v3", triggerresultshelper_value_HLT_DiPFJetAve40_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v4", triggerresultshelper_value_HLT_DiPFJetAve40_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v5", triggerresultshelper_value_HLT_DiPFJetAve40_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v6", triggerresultshelper_value_HLT_DiPFJetAve40_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v7", triggerresultshelper_value_HLT_DiPFJetAve40_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v8", triggerresultshelper_value_HLT_DiPFJetAve40_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve40_v9", triggerresultshelper_value_HLT_DiPFJetAve40_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v1", triggerresultshelper_value_HLT_DiPFJetAve80_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v10", triggerresultshelper_value_HLT_DiPFJetAve80_v10);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v11", triggerresultshelper_value_HLT_DiPFJetAve80_v11);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v12", triggerresultshelper_value_HLT_DiPFJetAve80_v12);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v13", triggerresultshelper_value_HLT_DiPFJetAve80_v13);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v14", triggerresultshelper_value_HLT_DiPFJetAve80_v14);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v15", triggerresultshelper_value_HLT_DiPFJetAve80_v15);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v16", triggerresultshelper_value_HLT_DiPFJetAve80_v16);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v17", triggerresultshelper_value_HLT_DiPFJetAve80_v17);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v18", triggerresultshelper_value_HLT_DiPFJetAve80_v18);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v19", triggerresultshelper_value_HLT_DiPFJetAve80_v19);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v2", triggerresultshelper_value_HLT_DiPFJetAve80_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v20", triggerresultshelper_value_HLT_DiPFJetAve80_v20);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v3", triggerresultshelper_value_HLT_DiPFJetAve80_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v4", triggerresultshelper_value_HLT_DiPFJetAve80_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v5", triggerresultshelper_value_HLT_DiPFJetAve80_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v6", triggerresultshelper_value_HLT_DiPFJetAve80_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v7", triggerresultshelper_value_HLT_DiPFJetAve80_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v8", triggerresultshelper_value_HLT_DiPFJetAve80_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DiPFJetAve80_v9", triggerresultshelper_value_HLT_DiPFJetAve80_v9);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3", triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4", triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2", triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3", triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4", triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6", triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6);
  stream.select("nPileupSummaryInfo_addPileupInfo", nPileupSummaryInfo);
  stream.select("nrecoGenJet_ak5GenJets", nak5GenJets);
  stream.select("npatElectron_patElectrons", npatElectron);
  stream.select("npatJet_selectedPatJets", npatJet);
  stream.select("npatMET_patMETs", npatMET);
  stream.select("npatMuon_patMuons", npatMuon);
  stream.select("npatTauHelper_patTaus", npatTau);
  stream.select("patTauHelper_patTaus.signalPFChargedHadrCands_size", patTau_signalPFChargedHadrCands_size);
  stream.select("nrecoGenParticleHelper_genParticles", nrecoGenParticleHelper);
  stream.select("nrecoGenParticleHelperPlus_genParticles", nrecoGenParticleHelperPlus);
  stream.select("nrecoGsfElectron_gsfElectrons", nrecoGsfElectron);
  stream.select("nrecoPFMET_pfType1CorrectedMet", nrecoPFMET);
  stream.select("nrecoPFMET_pfType1p2CorrectedMet", nrecoPFMET1);
  stream.select("nrecoVertex_offlinePrimaryVertices", nrecoVertex);
  stream.select("patElectron_patElectrons.deltaEtaSuperClusterTrackAtVtx", patElectron_deltaEtaSuperClusterTrackAtVtx);
  stream.select("patElectron_patElectrons.deltaPhiSuperClusterTrackAtVtx", patElectron_deltaPhiSuperClusterTrackAtVtx);
  stream.select("patElectron_patElectrons.dr04EcalRecHitSumEt", patElectron_dr04EcalRecHitSumEt);
  stream.select("patElectron_patElectrons.dr04TkSumPt", patElectron_dr04TkSumPt);
  stream.select("patElectron_patElectrons.eSuperClusterOverP", patElectron_eSuperClusterOverP);
  stream.select("patElectron_patElectrons.energy", patElectron_energy);
  stream.select("patElectron_patElectrons.et", patElectron_et);
  stream.select("patElectron_patElectrons.eta", patElectron_eta);
  stream.select("patElectron_patElectrons.gsfTrack_d0", patElectron_gsfTrack_d0);
  stream.select("patElectron_patElectrons.gsfTrack_dxy", patElectron_gsfTrack_dxy);
  stream.select("patElectron_patElectrons.gsfTrack_dz", patElectron_gsfTrack_dz);
  stream.select("patElectron_patElectrons.hadronicOverEm", patElectron_hadronicOverEm);
  stream.select("patElectron_patElectrons.p", patElectron_p);
  stream.select("patElectron_patElectrons.phi", patElectron_phi);
  stream.select("patElectron_patElectrons.pt", patElectron_pt);
  stream.select("patElectron_patElectrons.px", patElectron_px);
  stream.select("patElectron_patElectrons.py", patElectron_py);
  stream.select("patElectron_patElectrons.pz", patElectron_pz);
  stream.select("patElectron_patElectrons.scE1x5", patElectron_scE1x5);
  stream.select("patElectron_patElectrons.scE2x5Max", patElectron_scE2x5Max);
  stream.select("patElectron_patElectrons.scE5x5", patElectron_scE5x5);
  stream.select("patElectron_patElectrons.sigmaIetaIeta", patElectron_sigmaIetaIeta);
  stream.select("patJet_selectedPatJets.HFEMEnergy", patJet_HFEMEnergy);
  stream.select("patJet_selectedPatJets.HFEMEnergyFraction", patJet_HFEMEnergyFraction);
  stream.select("patJet_selectedPatJets.HFEMMultiplicity", patJet_HFEMMultiplicity);
  stream.select("patJet_selectedPatJets.HFHadronEnergy", patJet_HFHadronEnergy);
  stream.select("patJet_selectedPatJets.HFHadronEnergyFraction", patJet_HFHadronEnergyFraction);
  stream.select("patJet_selectedPatJets.HFHadronMultiplicity", patJet_HFHadronMultiplicity);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedInclusiveSecondaryVertexBJetTags", patJet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedMVABJetTags", patJet_bDiscriminator_combinedMVABJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedSecondaryVertexBJetTags", patJet_bDiscriminator_combinedSecondaryVertexBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedSecondaryVertexMVABJetTags", patJet_bDiscriminator_combinedSecondaryVertexMVABJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_impactParameterTagInfos", patJet_bDiscriminator_impactParameterTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_inclusiveSecondaryVertexFinderTagInfos", patJet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_jetBProbabilityBJetTags", patJet_bDiscriminator_jetBProbabilityBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_jetProbabilityBJetTags", patJet_bDiscriminator_jetProbabilityBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_negativeTrackCountingHighEffJetTags", patJet_bDiscriminator_negativeTrackCountingHighEffJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_negativeTrackCountingHighPurJetTags", patJet_bDiscriminator_negativeTrackCountingHighPurJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_secondaryVertexNegativeTagInfos", patJet_bDiscriminator_secondaryVertexNegativeTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_secondaryVertexTagInfos", patJet_bDiscriminator_secondaryVertexTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexHighEffBJetTags", patJet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexHighPurBJetTags", patJet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags", patJet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags", patJet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softElectronTagInfos", patJet_bDiscriminator_softElectronTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonBJetTags", patJet_bDiscriminator_softMuonBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonByIP3dBJetTags", patJet_bDiscriminator_softMuonByIP3dBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonByPtBJetTags", patJet_bDiscriminator_softMuonByPtBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonTagInfos", patJet_bDiscriminator_softMuonTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_trackCountingHighEffBJetTags", patJet_bDiscriminator_trackCountingHighEffBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_trackCountingHighPurBJetTags", patJet_bDiscriminator_trackCountingHighPurBJetTags);
  stream.select("patJet_selectedPatJets.charge", patJet_charge);
  stream.select("patJet_selectedPatJets.chargedEmEnergyFraction", patJet_chargedEmEnergyFraction);
  stream.select("patJet_selectedPatJets.chargedHadronEnergyFraction", patJet_chargedHadronEnergyFraction);
  stream.select("patJet_selectedPatJets.chargedHadronMultiplicity", patJet_chargedHadronMultiplicity);
  stream.select("patJet_selectedPatJets.electronEnergy", patJet_electronEnergy);
  stream.select("patJet_selectedPatJets.electronEnergyFraction", patJet_electronEnergyFraction);
  stream.select("patJet_selectedPatJets.electronMultiplicity", patJet_electronMultiplicity);
  stream.select("patJet_selectedPatJets.energy", patJet_energy);
  stream.select("patJet_selectedPatJets.et", patJet_et);
  stream.select("patJet_selectedPatJets.eta", patJet_eta);
  stream.select("patJet_selectedPatJets.muonEnergy", patJet_muonEnergy);
  stream.select("patJet_selectedPatJets.muonEnergyFraction", patJet_muonEnergyFraction);
  stream.select("patJet_selectedPatJets.neutralEmEnergyFraction", patJet_neutralEmEnergyFraction);
  stream.select("patJet_selectedPatJets.neutralHadronEnergy", patJet_neutralHadronEnergy);
  stream.select("patJet_selectedPatJets.neutralHadronEnergyFraction", patJet_neutralHadronEnergyFraction);
  stream.select("patJet_selectedPatJets.neutralHadronMultiplicity", patJet_neutralHadronMultiplicity);
  stream.select("patJet_selectedPatJets.numberOfDaughters", patJet_numberOfDaughters);
  stream.select("patJet_selectedPatJets.p", patJet_p);
  stream.select("patJet_selectedPatJets.phi", patJet_phi);
  stream.select("patJet_selectedPatJets.photonEnergy", patJet_photonEnergy);
  stream.select("patJet_selectedPatJets.photonEnergyFraction", patJet_photonEnergyFraction);
  stream.select("patJet_selectedPatJets.photonMultiplicity", patJet_photonMultiplicity);
  stream.select("patJet_selectedPatJets.pt", patJet_pt);
  stream.select("patJet_selectedPatJets.px", patJet_px);
  stream.select("patJet_selectedPatJets.py", patJet_py);
  stream.select("patJet_selectedPatJets.pz", patJet_pz);
  stream.select("patMET_patMETs.energy", patMET_energy);
  stream.select("patMET_patMETs.et", patMET_et);
  stream.select("patMET_patMETs.eta", patMET_eta);
  stream.select("patMET_patMETs.p", patMET_p);
  stream.select("patMET_patMETs.phi", patMET_phi);
  stream.select("patMET_patMETs.pt", patMET_pt);
  stream.select("patMET_patMETs.px", patMET_px);
  stream.select("patMET_patMETs.py", patMET_py);
  stream.select("patMET_patMETs.pz", patMET_pz);
  stream.select("patMuon_patMuons.energy", patMuon_energy);
  stream.select("patMuon_patMuons.et", patMuon_et);
  stream.select("patMuon_patMuons.eta", patMuon_eta);
  stream.select("patMuon_patMuons.globalTrack_hitPattern_numberOfValidMuonHits", patMuon_globalTrack_hitPattern_numberOfValidMuonHits);
  stream.select("patMuon_patMuons.globalTrack_normalizedChi2", patMuon_globalTrack_normalizedChi2);
  stream.select("patMuon_patMuons.innerTrack_dxy", patMuon_innerTrack_dxy);
  stream.select("patMuon_patMuons.innerTrack_dz", patMuon_innerTrack_dz);
  stream.select("patMuon_patMuons.innerTrack_hitPattern_numberOfValidPixelHits", patMuon_innerTrack_hitPattern_numberOfValidPixelHits);
  stream.select("patMuon_patMuons.innerTrack_hitPattern_pixelLayersWithMeasurement", patMuon_innerTrack_hitPattern_pixelLayersWithMeasurement);
  stream.select("patMuon_patMuons.innerTrack_normalizedChi2", patMuon_innerTrack_normalizedChi2);
  stream.select("patMuon_patMuons.isGlobalMuon", patMuon_isGlobalMuon);
  stream.select("patMuon_patMuons.isPFMuon", patMuon_isPFMuon);
  stream.select("patMuon_patMuons.isTrackerMuon", patMuon_isTrackerMuon);
  stream.select("patMuon_patMuons.muonBestTrack_dxy", patMuon_muonBestTrack_dxy);
  stream.select("patMuon_patMuons.muonBestTrack_dz", patMuon_muonBestTrack_dz);
  stream.select("patMuon_patMuons.numberOfMatchedStations", patMuon_numberOfMatchedStations);
  stream.select("patMuon_patMuons.p", patMuon_p);
  stream.select("patMuon_patMuons.pfIsolationR03_sumChargedHadronPt", patMuon_pfIsolationR03_sumChargedHadronPt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumChargedParticlePt", patMuon_pfIsolationR03_sumChargedParticlePt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumNeutralHadronEt", patMuon_pfIsolationR03_sumNeutralHadronEt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumNeutralHadronEtHighThreshold", patMuon_pfIsolationR03_sumNeutralHadronEtHighThreshold);
  stream.select("patMuon_patMuons.pfIsolationR03_sumPUPt", patMuon_pfIsolationR03_sumPUPt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumPhotonEt", patMuon_pfIsolationR03_sumPhotonEt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumPhotonEtHighThreshold", patMuon_pfIsolationR03_sumPhotonEtHighThreshold);
  stream.select("patMuon_patMuons.pfIsolationR04_sumChargedHadronPt", patMuon_pfIsolationR04_sumChargedHadronPt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumChargedParticlePt", patMuon_pfIsolationR04_sumChargedParticlePt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumNeutralHadronEt", patMuon_pfIsolationR04_sumNeutralHadronEt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumNeutralHadronEtHighThreshold", patMuon_pfIsolationR04_sumNeutralHadronEtHighThreshold);
  stream.select("patMuon_patMuons.pfIsolationR04_sumPUPt", patMuon_pfIsolationR04_sumPUPt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumPhotonEt", patMuon_pfIsolationR04_sumPhotonEt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumPhotonEtHighThreshold", patMuon_pfIsolationR04_sumPhotonEtHighThreshold);
  stream.select("patMuon_patMuons.phi", patMuon_phi);
  stream.select("patMuon_patMuons.pt", patMuon_pt);
  stream.select("patMuon_patMuons.px", patMuon_px);
  stream.select("patMuon_patMuons.py", patMuon_py);
  stream.select("patMuon_patMuons.pz", patMuon_pz);
  stream.select("patTauHelper_patTaus.charge", patTau_charge);
  stream.select("patTauHelper_patTaus.energy", patTau_energy);
  stream.select("patTauHelper_patTaus.et", patTau_et);
  stream.select("patTauHelper_patTaus.eta", patTau_eta);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_energy", patTau_leadPFChargedHadrCand_energy);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_et", patTau_leadPFChargedHadrCand_et);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_eta", patTau_leadPFChargedHadrCand_eta);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_mass", patTau_leadPFChargedHadrCand_mass);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_massSqr", patTau_leadPFChargedHadrCand_massSqr);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_mt", patTau_leadPFChargedHadrCand_mt);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_mtSqr", patTau_leadPFChargedHadrCand_mtSqr);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_p", patTau_leadPFChargedHadrCand_p);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_phi", patTau_leadPFChargedHadrCand_phi);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_pt", patTau_leadPFChargedHadrCand_pt);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_px", patTau_leadPFChargedHadrCand_px);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_py", patTau_leadPFChargedHadrCand_py);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_pz", patTau_leadPFChargedHadrCand_pz);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_rapidity", patTau_leadPFChargedHadrCand_rapidity);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_theta", patTau_leadPFChargedHadrCand_theta);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_y", patTau_leadPFChargedHadrCand_y);
  stream.select("patTauHelper_patTaus.p", patTau_p);
  stream.select("patTauHelper_patTaus.phi", patTau_phi);
  stream.select("patTauHelper_patTaus.pt", patTau_pt);
  stream.select("patTauHelper_patTaus.px", patTau_px);
  stream.select("patTauHelper_patTaus.py", patTau_py);
  stream.select("patTauHelper_patTaus.pz", patTau_pz);
  stream.select("patTauHelper_patTaus.tauID_againstElectronDeadECAL", patTau_tauID_againstElectronDeadECAL);
  stream.select("patTauHelper_patTaus.tauID_againstElectronLoose", patTau_tauID_againstElectronLoose);
  stream.select("patTauHelper_patTaus.tauID_againstElectronLooseMVA5", patTau_tauID_againstElectronLooseMVA5);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMVA5category", patTau_tauID_againstElectronMVA5category);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMVA5raw", patTau_tauID_againstElectronMVA5raw);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMedium", patTau_tauID_againstElectronMedium);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMediumMVA5", patTau_tauID_againstElectronMediumMVA5);
  stream.select("patTauHelper_patTaus.tauID_againstElectronTight", patTau_tauID_againstElectronTight);
  stream.select("patTauHelper_patTaus.tauID_againstElectronTightMVA5", patTau_tauID_againstElectronTightMVA5);
  stream.select("patTauHelper_patTaus.tauID_againstElectronVLooseMVA5", patTau_tauID_againstElectronVLooseMVA5);
  stream.select("patTauHelper_patTaus.tauID_againstElectronVTightMVA5", patTau_tauID_againstElectronVTightMVA5);
  stream.select("patTauHelper_patTaus.tauID_againstMuonLoose", patTau_tauID_againstMuonLoose);
  stream.select("patTauHelper_patTaus.tauID_againstMuonLoose2", patTau_tauID_againstMuonLoose2);
  stream.select("patTauHelper_patTaus.tauID_againstMuonLoose3", patTau_tauID_againstMuonLoose3);
  stream.select("patTauHelper_patTaus.tauID_againstMuonLooseMVA", patTau_tauID_againstMuonLooseMVA);
  stream.select("patTauHelper_patTaus.tauID_againstMuonMVAraw", patTau_tauID_againstMuonMVAraw);
  stream.select("patTauHelper_patTaus.tauID_againstMuonMedium", patTau_tauID_againstMuonMedium);
  stream.select("patTauHelper_patTaus.tauID_againstMuonMedium2", patTau_tauID_againstMuonMedium2);
  stream.select("patTauHelper_patTaus.tauID_againstMuonMediumMVA", patTau_tauID_againstMuonMediumMVA);
  stream.select("patTauHelper_patTaus.tauID_againstMuonTight", patTau_tauID_againstMuonTight);
  stream.select("patTauHelper_patTaus.tauID_againstMuonTight2", patTau_tauID_againstMuonTight2);
  stream.select("patTauHelper_patTaus.tauID_againstMuonTight3", patTau_tauID_againstMuonTight3);
  stream.select("patTauHelper_patTaus.tauID_againstMuonTightMVA", patTau_tauID_againstMuonTightMVA);
  stream.select("patTauHelper_patTaus.tauID_byCombinedIsolationDeltaBetaCorrRaw", patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw);
  stream.select("patTauHelper_patTaus.tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits", patTau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits);
  stream.select("patTauHelper_patTaus.tauID_byIsolationMVA3newDMwLTraw", patTau_tauID_byIsolationMVA3newDMwLTraw);
  stream.select("patTauHelper_patTaus.tauID_byIsolationMVA3newDMwoLTraw", patTau_tauID_byIsolationMVA3newDMwoLTraw);
  stream.select("patTauHelper_patTaus.tauID_byIsolationMVA3oldDMwLTraw", patTau_tauID_byIsolationMVA3oldDMwLTraw);
  stream.select("patTauHelper_patTaus.tauID_byIsolationMVA3oldDMwoLTraw", patTau_tauID_byIsolationMVA3oldDMwoLTraw);
  stream.select("patTauHelper_patTaus.tauID_byLooseCombinedIsolationDeltaBetaCorr", patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits", patTau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolation", patTau_tauID_byLooseIsolation);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolationMVA3newDMwLT", patTau_tauID_byLooseIsolationMVA3newDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolationMVA3newDMwoLT", patTau_tauID_byLooseIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolationMVA3oldDMwLT", patTau_tauID_byLooseIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolationMVA3oldDMwoLT", patTau_tauID_byLooseIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byMediumCombinedIsolationDeltaBetaCorr", patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits", patTau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolationMVA3newDMwLT", patTau_tauID_byMediumIsolationMVA3newDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolationMVA3newDMwoLT", patTau_tauID_byMediumIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolationMVA3oldDMwLT", patTau_tauID_byMediumIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolationMVA3oldDMwoLT", patTau_tauID_byMediumIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byTightCombinedIsolationDeltaBetaCorr", patTau_tauID_byTightCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byTightCombinedIsolationDeltaBetaCorr3Hits", patTau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolationMVA3newDMwLT", patTau_tauID_byTightIsolationMVA3newDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolationMVA3newDMwoLT", patTau_tauID_byTightIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolationMVA3oldDMwLT", patTau_tauID_byTightIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolationMVA3oldDMwoLT", patTau_tauID_byTightIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byVLooseCombinedIsolationDeltaBetaCorr", patTau_tauID_byVLooseCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byVLooseIsolationMVA3newDMwLT", patTau_tauID_byVLooseIsolationMVA3newDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byVLooseIsolationMVA3newDMwoLT", patTau_tauID_byVLooseIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byVLooseIsolationMVA3oldDMwLT", patTau_tauID_byVLooseIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byVLooseIsolationMVA3oldDMwoLT", patTau_tauID_byVLooseIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byVTightIsolationMVA3newDMwLT", patTau_tauID_byVTightIsolationMVA3newDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byVTightIsolationMVA3newDMwoLT", patTau_tauID_byVTightIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byVTightIsolationMVA3oldDMwLT", patTau_tauID_byVTightIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byVTightIsolationMVA3oldDMwoLT", patTau_tauID_byVTightIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byVVTightIsolationMVA3newDMwLT", patTau_tauID_byVVTightIsolationMVA3newDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byVVTightIsolationMVA3newDMwoLT", patTau_tauID_byVVTightIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_byVVTightIsolationMVA3oldDMwLT", patTau_tauID_byVVTightIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_patTaus.tauID_byVVTightIsolationMVA3oldDMwoLT", patTau_tauID_byVVTightIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_patTaus.tauID_chargedIsoPtSum", patTau_tauID_chargedIsoPtSum);
  stream.select("patTauHelper_patTaus.tauID_decayModeFinding", patTau_tauID_decayModeFinding);
  stream.select("patTauHelper_patTaus.tauID_decayModeFindingNewDMs", patTau_tauID_decayModeFindingNewDMs);
  stream.select("patTauHelper_patTaus.tauID_decayModeFindingOldDMs", patTau_tauID_decayModeFindingOldDMs);
  stream.select("patTauHelper_patTaus.tauID_neutralIsoPtSum", patTau_tauID_neutralIsoPtSum);
  stream.select("patTauHelper_patTaus.tauID_puCorrPtSum", patTau_tauID_puCorrPtSum);
  stream.select("patTauHelper_patTaus.vx", patTau_vx);
  stream.select("patTauHelper_patTaus.vy", patTau_vy);
  stream.select("patTauHelper_patTaus.vz", patTau_vz);
  stream.select("recoBeamSpot_offlineBeamSpot.x0", recoBeamSpot_x0);
  stream.select("recoBeamSpot_offlineBeamSpot.y0", recoBeamSpot_y0);
  stream.select("recoBeamSpot_offlineBeamSpot.z0", recoBeamSpot_z0);
  stream.select("recoGenParticleHelperPlus_genParticles.charge", recoGenParticleHelperPlus_charge);
  stream.select("recoGenParticleHelperPlus_genParticles.eta", recoGenParticleHelperPlus_eta);
  stream.select("recoGenParticleHelperPlus_genParticles.firstDaughter", recoGenParticleHelperPlus_firstDaughter);
  stream.select("recoGenParticleHelperPlus_genParticles.firstMother", recoGenParticleHelperPlus_firstMother);
  stream.select("recoGenParticleHelperPlus_genParticles.lastDaughter", recoGenParticleHelperPlus_lastDaughter);
  stream.select("recoGenParticleHelperPlus_genParticles.lastMother", recoGenParticleHelperPlus_lastMother);
  stream.select("recoGenParticleHelperPlus_genParticles.mass", recoGenParticleHelperPlus_mass);
  stream.select("recoGenParticleHelperPlus_genParticles.pdgId", recoGenParticleHelperPlus_pdgId);
  stream.select("recoGenParticleHelperPlus_genParticles.phi", recoGenParticleHelperPlus_phi);
  stream.select("recoGenParticleHelperPlus_genParticles.pt", recoGenParticleHelperPlus_pt);
  stream.select("recoGenParticleHelperPlus_genParticles.status", recoGenParticleHelperPlus_status);
  stream.select("recoGenParticleHelper_genParticles.charge", recoGenParticleHelper_charge);
  stream.select("recoGenParticleHelper_genParticles.eta", recoGenParticleHelper_eta);
  stream.select("recoGenParticleHelper_genParticles.firstDaughter", recoGenParticleHelper_firstDaughter);
  stream.select("recoGenParticleHelper_genParticles.firstMother", recoGenParticleHelper_firstMother);
  stream.select("recoGenParticleHelper_genParticles.lastDaughter", recoGenParticleHelper_lastDaughter);
  stream.select("recoGenParticleHelper_genParticles.lastMother", recoGenParticleHelper_lastMother);
  stream.select("recoGenParticleHelper_genParticles.mass", recoGenParticleHelper_mass);
  stream.select("recoGenParticleHelper_genParticles.pdgId", recoGenParticleHelper_pdgId);
  stream.select("recoGenParticleHelper_genParticles.phi", recoGenParticleHelper_phi);
  stream.select("recoGenParticleHelper_genParticles.pt", recoGenParticleHelper_pt);
  stream.select("recoGenParticleHelper_genParticles.status", recoGenParticleHelper_status);
  stream.select("recoGsfElectron_gsfElectrons.deltaEtaSuperClusterTrackAtVtx", recoGsfElectron_deltaEtaSuperClusterTrackAtVtx);
  stream.select("recoGsfElectron_gsfElectrons.deltaPhiSuperClusterTrackAtVtx", recoGsfElectron_deltaPhiSuperClusterTrackAtVtx);
  stream.select("recoGsfElectron_gsfElectrons.dr04EcalRecHitSumEt", recoGsfElectron_dr04EcalRecHitSumEt);
  stream.select("recoGsfElectron_gsfElectrons.dr04TkSumPt", recoGsfElectron_dr04TkSumPt);
  stream.select("recoGsfElectron_gsfElectrons.eSuperClusterOverP", recoGsfElectron_eSuperClusterOverP);
  stream.select("recoGsfElectron_gsfElectrons.energy", recoGsfElectron_energy);
  stream.select("recoGsfElectron_gsfElectrons.et", recoGsfElectron_et);
  stream.select("recoGsfElectron_gsfElectrons.eta", recoGsfElectron_eta);
  stream.select("recoGsfElectron_gsfElectrons.gsfTrack_d0", recoGsfElectron_gsfTrack_d0);
  stream.select("recoGsfElectron_gsfElectrons.gsfTrack_dxy", recoGsfElectron_gsfTrack_dxy);
  stream.select("recoGsfElectron_gsfElectrons.gsfTrack_dz", recoGsfElectron_gsfTrack_dz);
  stream.select("recoGsfElectron_gsfElectrons.hadronicOverEm", recoGsfElectron_hadronicOverEm);
  stream.select("recoGsfElectron_gsfElectrons.p", recoGsfElectron_p);
  stream.select("recoGsfElectron_gsfElectrons.phi", recoGsfElectron_phi);
  stream.select("recoGsfElectron_gsfElectrons.pt", recoGsfElectron_pt);
  stream.select("recoGsfElectron_gsfElectrons.px", recoGsfElectron_px);
  stream.select("recoGsfElectron_gsfElectrons.py", recoGsfElectron_py);
  stream.select("recoGsfElectron_gsfElectrons.pz", recoGsfElectron_pz);
  stream.select("recoGsfElectron_gsfElectrons.scE1x5", recoGsfElectron_scE1x5);
  stream.select("recoGsfElectron_gsfElectrons.scE2x5Max", recoGsfElectron_scE2x5Max);
  stream.select("recoGsfElectron_gsfElectrons.scE5x5", recoGsfElectron_scE5x5);
  stream.select("recoGsfElectron_gsfElectrons.sigmaIetaIeta", recoGsfElectron_sigmaIetaIeta);
  stream.select("recoPFMET_pfType1p2CorrectedMet.energy", recoPFMET1_energy);
  stream.select("recoPFMET_pfType1p2CorrectedMet.et", recoPFMET1_et);
  stream.select("recoPFMET_pfType1p2CorrectedMet.eta", recoPFMET1_eta);
  stream.select("recoPFMET_pfType1p2CorrectedMet.p", recoPFMET1_p);
  stream.select("recoPFMET_pfType1p2CorrectedMet.phi", recoPFMET1_phi);
  stream.select("recoPFMET_pfType1p2CorrectedMet.pt", recoPFMET1_pt);
  stream.select("recoPFMET_pfType1p2CorrectedMet.px", recoPFMET1_px);
  stream.select("recoPFMET_pfType1p2CorrectedMet.py", recoPFMET1_py);
  stream.select("recoPFMET_pfType1p2CorrectedMet.pz", recoPFMET1_pz);
  stream.select("recoPFMET_pfType1CorrectedMet.energy", recoPFMET_energy);
  stream.select("recoPFMET_pfType1CorrectedMet.et", recoPFMET_et);
  stream.select("recoPFMET_pfType1CorrectedMet.eta", recoPFMET_eta);
  stream.select("recoPFMET_pfType1CorrectedMet.p", recoPFMET_p);
  stream.select("recoPFMET_pfType1CorrectedMet.phi", recoPFMET_phi);
  stream.select("recoPFMET_pfType1CorrectedMet.pt", recoPFMET_pt);
  stream.select("recoPFMET_pfType1CorrectedMet.px", recoPFMET_px);
  stream.select("recoPFMET_pfType1CorrectedMet.py", recoPFMET_py);
  stream.select("recoPFMET_pfType1CorrectedMet.pz", recoPFMET_pz);
  stream.select("recoVertex_offlinePrimaryVertices.isFake", recoVertex_isFake);
  stream.select("recoVertex_offlinePrimaryVertices.ndof", recoVertex_ndof);
  stream.select("recoVertex_offlinePrimaryVertices.x", recoVertex_x);
  stream.select("recoVertex_offlinePrimaryVertices.y", recoVertex_y);
  stream.select("recoVertex_offlinePrimaryVertices.z", recoVertex_z);

}
}; // end namespace evt
#endif
