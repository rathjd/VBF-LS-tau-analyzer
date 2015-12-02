import ROOT
import sys
from DataFormats.FWLite import Events, Handle
from math import *

import ROOT,sys,os
ROOT.gROOT.SetBatch()

#ROOT Hinstograms and Output file

f = ROOT.TFile("miniaodreader_genparticles_histograms.root", "recreate")
#h1 = ROOT.TH1F("hgaus","histo from a gaussian",100,-3,3)
#h1.FillRandom("gaus",10000)
#h1.Write()

event_index = 0
nMatches = 0
nFails = 0
nHadronic = 0
nGenTaus = 0

h_counters =  ROOT.TH1F("h_counters", "", 1,0,1)
h_counters.SetBit(ROOT.TH1.kCanRebin)
h_counters.SetStats(0);
h_counters.Fill("Events",0.)
h_counters.Fill("GenTaus",0.)
h_counters.Fill("HadronicGenTaus",0.)
h_counters.Fill("RecoGenTaus matches",0.)
h_counters.Fill("RecoGenTaus fail matches",0.)

h2_genTaueta_vs_genTaupt = ROOT.TH2F("h2_genTaueta_vs_genTaupt","h2_genTaueta_vs_genTaupt", 50, 0., 500., 30, -3., 3.)
h2_genTaueta_vs_genTaupt.SetStats(0)
h2_genTaueta_vs_genTaupt.GetXaxis().SetTitle("gen #tau pt [GeV]")
h2_genTaueta_vs_genTaupt.GetYaxis().SetTitle("gen #tau #eta")

h_genTanMatching_eff_vs_pt_num =  ROOT.TH1F("h_genTanMatching_eff_vs_pt_num", "h_genTanMatching_eff_vs_pt_num", 50, 0., 500.)
h_genTanMatching_eff_vs_pt_den = ROOT.TH1F("h_genTanMatching_eff_vs_pt_den", "h_genTanMatching_eff_vs_pt_den", 50, 0., 500.)


filelist = open(sys.argv[1],'r')
lines = filelist.read().splitlines()
	
#Handles
gen_handle  = Handle ("std::vector<reco::GenParticle>")
gen_label = "prunedGenParticles"

tau_handle = Handle("vector<pat::Tau>")
tau_label = "slimmedTaus"

# loop over events
for line in lines:
	ifile = ROOT.TFile(line);
	events = Events(ifile);

	print "Opening file: {}".format(line)

	for event in events:

		h_counters.Fill("Events",1.)
    		event.getByLabel (gen_label, gen_handle)
    		event.getByLabel (tau_label, tau_handle)
    		
		# get the product
    		genparticles = gen_handle.product()
    		taus = tau_handle.product()
    
    		visibleGenTau4Vs = []
    		#for gen in genparticles :
    		for gen_index in range(len(genparticles)) :
        		gen = genparticles[gen_index]
			if not abs(gen.pdgId()) == 15: continue
			isFinalTau = True
		        isHadronic = True
			for daughter_index in range(0,gen.numberOfDaughters()):
            			daughter = gen.daughter(daughter_index)
            			if abs(daughter.pdgId()) == 15: isFinalTau = False
            			if abs(daughter.pdgId()) == 11: isHadronic = False
            			if abs(daughter.pdgId()) == 13: isHadronic = False
        		if not isFinalTau:
            			continue
			nGenTaus += 1
			h_counters.Fill("GenTaus",1.)
        		if not isHadronic:
				#print "Not Hadronic"
            			continue

        		visibleGenTau4V = ROOT.TLorentzVector();
        		for daughter_index in range(0,gen.numberOfDaughters()):
            			daughter = gen.daughter(daughter_index)
				#print daughter.pdgId()
            			if abs(daughter.pdgId()) == 12: continue
            			if abs(daughter.pdgId()) == 14: continue
            			if abs(daughter.pdgId()) == 16: continue
            			daughter4V = ROOT.TLorentzVector(daughter.px(),daughter.py(),daughter.pz(),daughter.energy())
				#print daughter.px(), daughter.py(), daughter.pz(), daughter.energy()
            			visibleGenTau4V += daughter4V
        		if  visibleGenTau4V.Pt() < 20:
            			continue;
			h_counters.Fill("HadronicGenTaus",1.)
			nHadronic += 1
			
			visibleGenTau4Vs.append(visibleGenTau4V)

    		recoTau4Vs = []
    		for tau_index in range(len(taus)):
        		tau = taus[tau_index]
		  	#if not ( tau.tauID("againstElectronVLooseMVA5") > 0.5 ) : continue
		  	#if not ( tau.tauID("againstMuonLoose3") > 0.5 ) : continue
		  	if not ( tau.tauID("decayModeFindingNewDMs") > 0.5 ) : continue
		  	if not ( tau.tauID("byLooseCombinedIsolationDeltaBetaCorr3Hits") > 0.5 ) : continue
		  	#if not ( tau.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") > 0.5 ) : continue
		  	#if not ( tau.tauID("byTightCombinedIsolationDeltaBetaCorr3Hits") > 0.5 ) : continue
		  	#if not ( tau.eta() <= 2.1 ) : continue
		  	#if not ( tau.pt() >= 20. ) : continue
            		tau4V = ROOT.TLorentzVector(tau.px(),tau.py(),tau.pz(),tau.energy())
            		recoTau4Vs.append(tau4V)

        		
			#if tau.tauID("decayModeFindingNewDMs") > 0.5:
            			#print tau.pt(),tau.eta(),tau.phi()
            			#tau4V = ROOT.TLorentzVector(tau.px(),tau.py(),tau.pz(),tau.energy())
            			#recoTau4Vs.append(tau4V)
				#print "appended"

    		#print "matching"
    		for genTau in visibleGenTau4Vs:
        		h_genTanMatching_eff_vs_pt_den.Fill(visibleGenTau4V.Pt())
			h2_genTaueta_vs_genTaupt.Fill(visibleGenTau4V.Pt(),visibleGenTau4V.Eta())
        		isMatched = False
        		for recoTau in recoTau4Vs:
				#print "deltaR: {}".format(genTau.DeltaR(recoTau))
            			if genTau.DeltaR(recoTau) < 0.5:
                			isMatched = True
                			break
        		if isMatched:
				h_genTanMatching_eff_vs_pt_num.Fill(visibleGenTau4V.Pt())
            			nMatches += 1
				h_counters.Fill("RecoGenTaus matches",1.)
        		else:
				h_counters.Fill("RecoGenTaus fail matches",1.)
            			nFails += 1
        #print genTau.Pt(),genTau.Eta(),genTau.Phi(),isMatched

    		event_index += 1

print "# of Total events: {}".format(event_index)
print "# of Gen Taus: {}".format(nGenTaus)
print "-----------------------------"
print "# of Hadronic Taus: {}".format(nHadronic)
print "# of Matches: {}".format(nMatches)
print "# of Failed Matches: {}".format(nFails)
print "-----------------------------"
f.cd()

#writing and saving plots
print "Printing and saving plots"
h_genTanMatching_eff_vs_pt = ROOT.TGraphAsymmErrors(h_genTanMatching_eff_vs_pt_num, h_genTanMatching_eff_vs_pt_den)
h_genTanMatching_eff_vs_pt.GetXaxis().SetTitle("gen #tau pt [GeV]")
h_genTanMatching_eff_vs_pt.GetYaxis().SetTitle("#epsilon")

h_genTanMatching_eff_vs_pt.Write()
h2_genTaueta_vs_genTaupt.Write()
h_genTanMatching_eff_vs_pt_num.Write()
h_genTanMatching_eff_vs_pt_den.Write()
h_counters.Write()
