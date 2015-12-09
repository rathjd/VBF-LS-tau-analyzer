import ROOT
import sys
from DataFormats.FWLite import Events, Handle
from math import *

import ROOT,sys,os
ROOT.gROOT.SetBatch()

#ROOT Hinstograms and Output file

fin = ROOT.TFile(sys.argv[1])

outfile = sys.argv[2]

fout = ROOT.TFile( outfile, "recreate")

fin.cd()

h_tauDecayModeFinding_eff_vs_pt_num = fin.Get("h_tauDecayModeFinding_eff_vs_pt_num")
h_tauDecayModeFinding_eff_vs_pt_den = fin.Get("h_tauDecayModeFinding_eff_vs_pt_den")

h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num = fin.Get("h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num")
h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den = fin.Get("h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den")

h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num = fin.Get("h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num")
h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den = fin.Get("h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den")

h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num = fin.Get("h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num")
h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den = fin.Get("h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den")

h_tauid_eff_looseiso_vs_pt_num = fin.Get("h_tauid_eff_looseiso_vs_pt_num")
h_tauid_eff_looseiso_vs_pt_den = fin.Get("h_tauid_eff_looseiso_vs_pt_den")

h_tauid_eff_mediumiso_vs_pt_num = fin.Get("h_tauid_eff_mediumiso_vs_pt_num")
h_tauid_eff_mediumiso_vs_pt_den = fin.Get("h_tauid_eff_mediumiso_vs_pt_den")

h_tauid_eff_tightiso_vs_pt_num = fin.Get("h_tauid_eff_tightiso_vs_pt_num")
h_tauid_eff_tightiso_vs_pt_den = fin.Get("h_tauid_eff_tightiso_vs_pt_den")

fout.cd()

h_tauDecayModeFinding_eff_vs_pt = ROOT.TGraphAsymmErrors(h_tauDecayModeFinding_eff_vs_pt_num, h_tauDecayModeFinding_eff_vs_pt_den)
h_tauDecayModeFinding_eff_vs_pt.GetXaxis().SetTitle("visible gen #tau pt [GeV]")
h_tauDecayModeFinding_eff_vs_pt.GetYaxis().SetTitle("#epsilon tauDecayModeFinding")
h_tauDecayModeFinding_eff_vs_pt.Write()

h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt = ROOT.TGraphAsymmErrors(h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num, h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den)
h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.GetXaxis().SetTitle("visible gen #tau pt [GeV]")
h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.GetYaxis().SetTitle("#epsilon tauByLooseCombinedIsolationDeltaBetaCorr3Hits")
h_tauByLooseCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.Write()

h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt = ROOT.TGraphAsymmErrors(h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num, h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den)
h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.GetXaxis().SetTitle("visible gen #tau pt [GeV]")
h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.GetYaxis().SetTitle("#epsilon tauByMediumCombinedIsolationDeltaBetaCorr3Hits")
h_tauByMediumCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.Write()

h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt = ROOT.TGraphAsymmErrors(h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_num, h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt_den)
h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.GetXaxis().SetTitle("visible gen #tau pt [GeV]")
h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.GetYaxis().SetTitle("#epsilon tauByTightCombinedIsolationDeltaBetaCorr3Hits")
h_tauByTightCombinedIsolationDeltaBetaCorr3Hits_eff_vs_pt.Write()

h_tauid_eff_looseiso_vs_pt = ROOT.TGraphAsymmErrors(h_tauid_eff_looseiso_vs_pt_num, h_tauid_eff_looseiso_vs_pt_den)
h_tauid_eff_looseiso_vs_pt.GetXaxis().SetTitle("visible gen #tau pt [GeV]")
h_tauid_eff_looseiso_vs_pt.GetYaxis().SetTitle("#epsilon tauid with loose iso")
h_tauid_eff_looseiso_vs_pt.Write()

h_tauid_eff_mediumiso_vs_pt = ROOT.TGraphAsymmErrors(h_tauid_eff_mediumiso_vs_pt_num, h_tauid_eff_mediumiso_vs_pt_den)
h_tauid_eff_mediumiso_vs_pt.GetXaxis().SetTitle("visible gen #tau pt [GeV]")
h_tauid_eff_mediumiso_vs_pt.GetYaxis().SetTitle("#epsilon tauid with medium iso")
h_tauid_eff_mediumiso_vs_pt.Write()

h_tauid_eff_tightiso_vs_pt = ROOT.TGraphAsymmErrors(h_tauid_eff_tightiso_vs_pt_num, h_tauid_eff_tightiso_vs_pt_den)
h_tauid_eff_tightiso_vs_pt.GetXaxis().SetTitle("visible gen #tau pt [GeV]")
h_tauid_eff_tightiso_vs_pt.GetYaxis().SetTitle("#epsilon tauid with tight iso")
h_tauid_eff_tightiso_vs_pt.Write()

