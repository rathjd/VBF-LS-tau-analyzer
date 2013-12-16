#ifndef ANALYZER_H
#define ANALYZER_H
//-----------------------------------------------------------------------------
// File:        analyzer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Tue Oct 15 12:20:17 2013 by mkanalyzer.py
// Author:      Lukas Vanelderen
//-----------------------------------------------------------------------------
// -- System

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

#ifdef PROJECT_NAME
#include "PhysicsTools/TheNtupleMaker/interface/treestream.h"
#include "PhysicsTools/TheNtupleMaker/interface/pdg.h"
#else
#include "treestream.h"
#include "pdg.h"
#endif

// -- Root

#include "TROOT.h"
#include "TApplication.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TKey.h"
#include "TH1F.h"
#include "TH2F.h"
//-----------------------------------------------------------------------------
// -- Declare variables to be read
//-----------------------------------------------------------------------------
double	beamspot_x0;
double	beamspot_y0;
double	beamspot_z0;
std::vector<float>	electron_deltaEtaSuperClusterTrackAtVtx(200,0);
std::vector<float>	electron_deltaPhiSuperClusterTrackAtVtx(200,0);
std::vector<float>	electron_dr04EcalRecHitSumEt(200,0);
std::vector<float>	electron_dr04TkSumPt(200,0);
std::vector<float>	electron_eSuperClusterOverP(200,0);
std::vector<double>	electron_energy(200,0);
std::vector<double>	electron_et(200,0);
std::vector<double>	electron_eta(200,0);
std::vector<double>	electron_gsfTrack_d0(200,0);
std::vector<double>	electron_gsfTrack_dxy(200,0);
std::vector<double>	electron_gsfTrack_dz(200,0);
std::vector<float>	electron_hadronicOverEm(200,0);
std::vector<double>	electron_p(200,0);
std::vector<double>	electron_phi(200,0);
std::vector<double>	electron_pt(200,0);
std::vector<double>	electron_px(200,0);
std::vector<double>	electron_py(200,0);
std::vector<double>	electron_pz(200,0);
std::vector<float>	electron_scE1x5(200,0);
std::vector<float>	electron_scE2x5Max(200,0);
std::vector<float>	electron_scE5x5(200,0);
std::vector<float>	electron_sigmaIetaIeta(200,0);
int	eventhelper_bunchCrossing;
int	eventhelper_event;
int	eventhelper_isRealData;
int	eventhelper_luminosityBlock;
int	eventhelper_orbitNumber;
int	eventhelper_run;
std::vector<int>	genparticlehelper_charge(500,0);
std::vector<double>	genparticlehelper_eta(500,0);
std::vector<int>	genparticlehelper_firstDaughter(500,0);
std::vector<int>	genparticlehelper_firstMother(500,0);
std::vector<int>	genparticlehelper_lastDaughter(500,0);
std::vector<int>	genparticlehelper_lastMother(500,0);
std::vector<double>	genparticlehelper_mass(500,0);
std::vector<int>	genparticlehelper_pdgId(500,0);
std::vector<double>	genparticlehelper_phi(500,0);
std::vector<double>	genparticlehelper_pt(500,0);
std::vector<int>	genparticlehelper_status(500,0);
double	genruninfoproduct_crossSection;
double	genruninfoproduct_filterEfficiency;
double	genruninfoproduct_internalXSec_value;
std::vector<float>	gsfelectron_deltaEtaSuperClusterTrackAtVtx(200,0);
std::vector<float>	gsfelectron_deltaPhiSuperClusterTrackAtVtx(200,0);
std::vector<float>	gsfelectron_dr04EcalRecHitSumEt(200,0);
std::vector<float>	gsfelectron_dr04TkSumPt(200,0);
std::vector<float>	gsfelectron_eSuperClusterOverP(200,0);
std::vector<double>	gsfelectron_energy(200,0);
std::vector<double>	gsfelectron_et(200,0);
std::vector<double>	gsfelectron_eta(200,0);
std::vector<double>	gsfelectron_gsfTrack_d0(200,0);
std::vector<double>	gsfelectron_gsfTrack_dxy(200,0);
std::vector<double>	gsfelectron_gsfTrack_dz(200,0);
std::vector<float>	gsfelectron_hadronicOverEm(200,0);
std::vector<double>	gsfelectron_p(200,0);
std::vector<double>	gsfelectron_phi(200,0);
std::vector<double>	gsfelectron_pt(200,0);
std::vector<double>	gsfelectron_px(200,0);
std::vector<double>	gsfelectron_py(200,0);
std::vector<double>	gsfelectron_pz(200,0);
std::vector<float>	gsfelectron_scE1x5(200,0);
std::vector<float>	gsfelectron_scE2x5Max(200,0);
std::vector<float>	gsfelectron_scE5x5(200,0);
std::vector<float>	gsfelectron_sigmaIetaIeta(200,0);
std::vector<float>	jet_HFEMEnergy(200,0);
std::vector<float>	jet_HFEMEnergyFraction(200,0);
std::vector<int>	jet_HFEMMultiplicity(200,0);
std::vector<float>	jet_HFHadronEnergy(200,0);
std::vector<float>	jet_HFHadronEnergyFraction(200,0);
std::vector<int>	jet_HFHadronMultiplicity(200,0);
std::vector<float>	jet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_combinedMVABJetTags(200,0);
std::vector<float>	jet_bDiscriminator_combinedSecondaryVertexBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_combinedSecondaryVertexMVABJetTags(200,0);
std::vector<float>	jet_bDiscriminator_impactParameterTagInfos(200,0);
std::vector<float>	jet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos(200,0);
std::vector<float>	jet_bDiscriminator_jetBProbabilityBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_jetProbabilityBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_negativeTrackCountingHighEffJetTags(200,0);
std::vector<float>	jet_bDiscriminator_negativeTrackCountingHighPurJetTags(200,0);
std::vector<float>	jet_bDiscriminator_secondaryVertexNegativeTagInfos(200,0);
std::vector<float>	jet_bDiscriminator_secondaryVertexTagInfos(200,0);
std::vector<float>	jet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_softElectronTagInfos(200,0);
std::vector<float>	jet_bDiscriminator_softMuonBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_softMuonByIP3dBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_softMuonByPtBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_softMuonTagInfos(200,0);
std::vector<float>	jet_bDiscriminator_trackCountingHighEffBJetTags(200,0);
std::vector<float>	jet_bDiscriminator_trackCountingHighPurBJetTags(200,0);
std::vector<int>	jet_charge(200,0);
std::vector<float>	jet_chargedEmEnergyFraction(200,0);
std::vector<float>	jet_chargedHadronEnergyFraction(200,0);
std::vector<int>	jet_chargedHadronMultiplicity(200,0);
std::vector<float>	jet_electronEnergy(200,0);
std::vector<float>	jet_electronEnergyFraction(200,0);
std::vector<int>	jet_electronMultiplicity(200,0);
std::vector<double>	jet_energy(200,0);
std::vector<double>	jet_et(200,0);
std::vector<double>	jet_eta(200,0);
std::vector<float>	jet_muonEnergy(200,0);
std::vector<float>	jet_muonEnergyFraction(200,0);
std::vector<float>	jet_neutralEmEnergyFraction(200,0);
std::vector<float>	jet_neutralHadronEnergy(200,0);
std::vector<float>	jet_neutralHadronEnergyFraction(200,0);
std::vector<int>	jet_neutralHadronMultiplicity(200,0);
std::vector<size_t>	jet_numberOfDaughters(200,0);
std::vector<double>	jet_p(200,0);
std::vector<double>	jet_phi(200,0);
std::vector<float>	jet_photonEnergy(200,0);
std::vector<float>	jet_photonEnergyFraction(200,0);
std::vector<int>	jet_photonMultiplicity(200,0);
std::vector<double>	jet_pt(200,0);
std::vector<double>	jet_px(200,0);
std::vector<double>	jet_py(200,0);
std::vector<double>	jet_pz(200,0);
std::vector<double>	met_energy(200,0);
std::vector<double>	met_et(200,0);
std::vector<double>	met_eta(200,0);
std::vector<double>	met_p(200,0);
std::vector<double>	met_phi(200,0);
std::vector<double>	met_pt(200,0);
std::vector<double>	met_px(200,0);
std::vector<double>	met_py(200,0);
std::vector<double>	met_pz(200,0);
std::vector<double>	muon_energy(200,0);
std::vector<double>	muon_et(200,0);
std::vector<double>	muon_eta(200,0);
std::vector<int>	muon_globalTrack_hitPattern_numberOfValidMuonHits(200,0);
std::vector<double>	muon_globalTrack_normalizedChi2(200,0);
std::vector<double>	muon_innerTrack_dxy(200,0);
std::vector<double>	muon_innerTrack_dz(200,0);
std::vector<int>	muon_innerTrack_hitPattern_numberOfValidPixelHits(200,0);
std::vector<int>	muon_innerTrack_hitPattern_pixelLayersWithMeasurement(200,0);
std::vector<double>	muon_innerTrack_normalizedChi2(200,0);
std::vector<int>	muon_isGlobalMuon(200,0);
std::vector<int>	muon_isPFMuon(200,0);
std::vector<int>	muon_isTrackerMuon(200,0);
std::vector<double>	muon_muonBestTrack_dxy(200,0);
std::vector<double>	muon_muonBestTrack_dz(200,0);
std::vector<int>	muon_numberOfMatchedStations(200,0);
std::vector<double>	muon_p(200,0);
std::vector<float>	muon_pfIsolationR03_sumChargedHadronPt(200,0);
std::vector<float>	muon_pfIsolationR03_sumChargedParticlePt(200,0);
std::vector<float>	muon_pfIsolationR03_sumNeutralHadronEt(200,0);
std::vector<float>	muon_pfIsolationR03_sumNeutralHadronEtHighThreshold(200,0);
std::vector<float>	muon_pfIsolationR03_sumPUPt(200,0);
std::vector<float>	muon_pfIsolationR03_sumPhotonEt(200,0);
std::vector<float>	muon_pfIsolationR03_sumPhotonEtHighThreshold(200,0);
std::vector<float>	muon_pfIsolationR04_sumChargedHadronPt(200,0);
std::vector<float>	muon_pfIsolationR04_sumChargedParticlePt(200,0);
std::vector<float>	muon_pfIsolationR04_sumNeutralHadronEt(200,0);
std::vector<float>	muon_pfIsolationR04_sumNeutralHadronEtHighThreshold(200,0);
std::vector<float>	muon_pfIsolationR04_sumPUPt(200,0);
std::vector<float>	muon_pfIsolationR04_sumPhotonEt(200,0);
std::vector<float>	muon_pfIsolationR04_sumPhotonEtHighThreshold(200,0);
std::vector<double>	muon_phi(200,0);
std::vector<double>	muon_pt(200,0);
std::vector<double>	muon_px(200,0);
std::vector<double>	muon_py(200,0);
std::vector<double>	muon_pz(200,0);
int	nelectron;
int	ngenparticlehelper;
int	ngsfelectron;
int	njet;
int	nmet;
int	nmuon;
int	npfmet;
int	npfmet2;
int	npileupsummaryinfo;
int	ntau;
int	nvertex;
std::vector<double>	pfmet2_energy(200,0);
std::vector<double>	pfmet2_et(200,0);
std::vector<double>	pfmet2_eta(200,0);
std::vector<double>	pfmet2_p(200,0);
std::vector<double>	pfmet2_phi(200,0);
std::vector<double>	pfmet2_pt(200,0);
std::vector<double>	pfmet2_px(200,0);
std::vector<double>	pfmet2_py(200,0);
std::vector<double>	pfmet2_pz(200,0);
std::vector<double>	pfmet_energy(200,0);
std::vector<double>	pfmet_et(200,0);
std::vector<double>	pfmet_eta(200,0);
std::vector<double>	pfmet_p(200,0);
std::vector<double>	pfmet_phi(200,0);
std::vector<double>	pfmet_pt(200,0);
std::vector<double>	pfmet_px(200,0);
std::vector<double>	pfmet_py(200,0);
std::vector<double>	pfmet_pz(200,0);
std::vector<int>	pileupsummaryinfo_getBunchCrossing(10,0);
std::vector<int>	pileupsummaryinfo_getPU_NumInteractions(10,0);
std::vector<int>	tau_charge(200,0);
std::vector<double>	tau_energy(200,0);
std::vector<double>	tau_et(200,0);
std::vector<double>	tau_eta(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_energy(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_et(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_eta(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_mass(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_massSqr(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_mt(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_mtSqr(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_p(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_phi(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_pt(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_px(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_py(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_pz(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_rapidity(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_theta(200,0);
std::vector<double>	tau_leadPFChargedHadrCand_y(200,0);
std::vector<double>	tau_p(200,0);
std::vector<double>	tau_phi(200,0);
std::vector<double>	tau_pt(200,0);
std::vector<double>	tau_px(200,0);
std::vector<double>	tau_py(200,0);
std::vector<double>	tau_pz(200,0);
std::vector<size_t>	tau_signalPFChargedHadrCands_size(200,0);
std::vector<float>	tau_tauID_againstElectronDeadECAL(200,0);
std::vector<float>	tau_tauID_againstElectronLoose(200,0);
std::vector<float>	tau_tauID_againstElectronLooseMVA2(200,0);
std::vector<float>	tau_tauID_againstElectronLooseMVA3(200,0);
std::vector<float>	tau_tauID_againstElectronMVA(200,0);
std::vector<float>	tau_tauID_againstElectronMVA2category(200,0);
std::vector<float>	tau_tauID_againstElectronMVA2raw(200,0);
std::vector<float>	tau_tauID_againstElectronMVA3category(200,0);
std::vector<float>	tau_tauID_againstElectronMVA3raw(200,0);
std::vector<float>	tau_tauID_againstElectronMedium(200,0);
std::vector<float>	tau_tauID_againstElectronMediumMVA2(200,0);
std::vector<float>	tau_tauID_againstElectronMediumMVA3(200,0);
std::vector<float>	tau_tauID_againstElectronTight(200,0);
std::vector<float>	tau_tauID_againstElectronTightMVA2(200,0);
std::vector<float>	tau_tauID_againstElectronTightMVA3(200,0);
std::vector<float>	tau_tauID_againstElectronVLooseMVA2(200,0);
std::vector<float>	tau_tauID_againstElectronVTightMVA3(200,0);
std::vector<float>	tau_tauID_againstMuonLoose(200,0);
std::vector<float>	tau_tauID_againstMuonLoose2(200,0);
std::vector<float>	tau_tauID_againstMuonMedium(200,0);
std::vector<float>	tau_tauID_againstMuonMedium2(200,0);
std::vector<float>	tau_tauID_againstMuonTight(200,0);
std::vector<float>	tau_tauID_againstMuonTight2(200,0);
std::vector<float>	tau_tauID_byCombinedIsolationDeltaBetaCorrRaw(200,0);
std::vector<float>	tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits(200,0);
std::vector<float>	tau_tauID_byIsolationMVA2raw(200,0);
std::vector<float>	tau_tauID_byIsolationMVAraw(200,0);
std::vector<float>	tau_tauID_byLooseCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	tau_tauID_byLooseIsolation(200,0);
std::vector<float>	tau_tauID_byLooseIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_byLooseIsolationMVA(200,0);
std::vector<float>	tau_tauID_byLooseIsolationMVA2(200,0);
std::vector<float>	tau_tauID_byMediumCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	tau_tauID_byMediumIsolation(200,0);
std::vector<float>	tau_tauID_byMediumIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_byMediumIsolationMVA(200,0);
std::vector<float>	tau_tauID_byMediumIsolationMVA2(200,0);
std::vector<float>	tau_tauID_byTightCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	tau_tauID_byTightIsolation(200,0);
std::vector<float>	tau_tauID_byTightIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_byTightIsolationMVA(200,0);
std::vector<float>	tau_tauID_byTightIsolationMVA2(200,0);
std::vector<float>	tau_tauID_byVLooseCombinedIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_byVLooseIsolation(200,0);
std::vector<float>	tau_tauID_byVLooseIsolationDeltaBetaCorr(200,0);
std::vector<float>	tau_tauID_decayModeFinding(200,0);
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
std::vector<int>	vertex_isFake(200,0);
std::vector<double>	vertex_ndof(200,0);
std::vector<double>	vertex_x(200,0);
std::vector<double>	vertex_y(200,0);
std::vector<double>	vertex_z(200,0);

//-----------------------------------------------------------------------------
// --- Structs can be filled by calling fillObjects()
// --- after the call to stream.read(...)
//-----------------------------------------------------------------------------
struct electron_s
{
  bool	selected;
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
struct genparticlehelper_s
{
  bool	selected;
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
std::vector<genparticlehelper_s> genparticlehelper(500);

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
struct gsfelectron_s
{
  bool	selected;
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
std::vector<gsfelectron_s> gsfelectron(200);

std::ostream& operator<<(std::ostream& os, const gsfelectron_s& o)
{
  char r[1024];
  os << "gsfelectron" << std::endl;
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
  bool	selected;
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
  bool	selected;
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
  bool	selected;
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
struct pfmet_s
{
  bool	selected;
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
std::vector<pfmet_s> pfmet(200);

std::ostream& operator<<(std::ostream& os, const pfmet_s& o)
{
  char r[1024];
  os << "pfmet" << std::endl;
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
struct pfmet2_s
{
  bool	selected;
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
std::vector<pfmet2_s> pfmet2(200);

std::ostream& operator<<(std::ostream& os, const pfmet2_s& o)
{
  char r[1024];
  os << "pfmet2" << std::endl;
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
struct pileupsummaryinfo_s
{
  bool	selected;
  int	getBunchCrossing;
  int	getPU_NumInteractions;
};
std::vector<pileupsummaryinfo_s> pileupsummaryinfo(10);

std::ostream& operator<<(std::ostream& os, const pileupsummaryinfo_s& o)
{
  char r[1024];
  os << "pileupsummaryinfo" << std::endl;
  sprintf(r, "  %-32s: %f\n", "getBunchCrossing", (double)o.getBunchCrossing); os << r;
  sprintf(r, "  %-32s: %f\n", "getPU_NumInteractions", (double)o.getPU_NumInteractions); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct tau_s
{
  bool	selected;
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
  float	tauID_byIsolationMVAraw;
  float	tauID_byMediumCombinedIsolationDeltaBetaCorr;
  float	tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits;
  float	tauID_againstMuonMedium;
  float	tauID_againstElectronTightMVA3;
  float	tauID_againstElectronTightMVA2;
  float	tauID_byLooseIsolationMVA2;
  float	tauID_againstMuonTight;
  float	tauID_againstMuonLoose2;
  float	tauID_byTightIsolationMVA;
  float	tauID_byLooseIsolation;
  float	tauID_byLooseCombinedIsolationDeltaBetaCorr;
  float	tauID_againstElectronLooseMVA3;
  float	tauID_againstElectronLooseMVA2;
  float	tauID_againstElectronTight;
  float	tauID_byVLooseCombinedIsolationDeltaBetaCorr;
  float	tauID_againstElectronVTightMVA3;
  float	tauID_againstElectronMediumMVA3;
  float	tauID_againstElectronMediumMVA2;
  float	tauID_againstElectronMVA;
  float	tauID_againstMuonLoose;
  float	tauID_againstMuonTight2;
  float	tauID_againstElectronMedium;
  float	tauID_againstElectronVLooseMVA2;
  float	tauID_againstMuonMedium2;
  float	tauID_byMediumIsolationMVA;
  float	tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byLooseIsolationDeltaBetaCorr;
  float	tauID_byIsolationMVA2raw;
  float	tauID_byTightIsolationMVA2;
  float	tauID_againstElectronMVA2category;
  float	tauID_byTightIsolationDeltaBetaCorr;
  float	tauID_againstElectronDeadECAL;
  float	tauID_againstElectronMVA3category;
  float	tauID_byVLooseIsolationDeltaBetaCorr;
  float	tauID_againstElectronMVA2raw;
  float	tauID_byTightCombinedIsolationDeltaBetaCorr;
  float	tauID_againstElectronMVA3raw;
  float	tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byMediumIsolationMVA2;
  float	tauID_byMediumIsolationDeltaBetaCorr;
  float	tauID_againstElectronLoose;
  float	tauID_byTightIsolation;
  float	tauID_byVLooseIsolation;
  float	tauID_byLooseIsolationMVA;
  float	tauID_byCombinedIsolationDeltaBetaCorrRaw;
  float	tauID_byTightCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_decayModeFinding;
  float	tauID_byMediumIsolation;
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
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVAraw", (double)o.tauID_byIsolationMVAraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumCombinedIsolationDeltaBetaCorr", (double)o.tauID_byMediumCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits", (double)o.tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonMedium", (double)o.tauID_againstMuonMedium); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronTightMVA3", (double)o.tauID_againstElectronTightMVA3); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronTightMVA2", (double)o.tauID_againstElectronTightMVA2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA2", (double)o.tauID_byLooseIsolationMVA2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonTight", (double)o.tauID_againstMuonTight); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonLoose2", (double)o.tauID_againstMuonLoose2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA", (double)o.tauID_byTightIsolationMVA); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolation", (double)o.tauID_byLooseIsolation); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseCombinedIsolationDeltaBetaCorr", (double)o.tauID_byLooseCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronLooseMVA3", (double)o.tauID_againstElectronLooseMVA3); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronLooseMVA2", (double)o.tauID_againstElectronLooseMVA2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronTight", (double)o.tauID_againstElectronTight); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseCombinedIsolationDeltaBetaCorr", (double)o.tauID_byVLooseCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronVTightMVA3", (double)o.tauID_againstElectronVTightMVA3); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMediumMVA3", (double)o.tauID_againstElectronMediumMVA3); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMediumMVA2", (double)o.tauID_againstElectronMediumMVA2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMVA", (double)o.tauID_againstElectronMVA); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonLoose", (double)o.tauID_againstMuonLoose); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonTight2", (double)o.tauID_againstMuonTight2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMedium", (double)o.tauID_againstElectronMedium); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronVLooseMVA2", (double)o.tauID_againstElectronVLooseMVA2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstMuonMedium2", (double)o.tauID_againstMuonMedium2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA", (double)o.tauID_byMediumIsolationMVA); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationDeltaBetaCorr", (double)o.tauID_byLooseIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA2raw", (double)o.tauID_byIsolationMVA2raw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA2", (double)o.tauID_byTightIsolationMVA2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMVA2category", (double)o.tauID_againstElectronMVA2category); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationDeltaBetaCorr", (double)o.tauID_byTightIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronDeadECAL", (double)o.tauID_againstElectronDeadECAL); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMVA3category", (double)o.tauID_againstElectronMVA3category); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseIsolationDeltaBetaCorr", (double)o.tauID_byVLooseIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMVA2raw", (double)o.tauID_againstElectronMVA2raw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightCombinedIsolationDeltaBetaCorr", (double)o.tauID_byTightCombinedIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronMVA3raw", (double)o.tauID_againstElectronMVA3raw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA2", (double)o.tauID_byMediumIsolationMVA2); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationDeltaBetaCorr", (double)o.tauID_byMediumIsolationDeltaBetaCorr); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_againstElectronLoose", (double)o.tauID_againstElectronLoose); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolation", (double)o.tauID_byTightIsolation); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byVLooseIsolation", (double)o.tauID_byVLooseIsolation); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA", (double)o.tauID_byLooseIsolationMVA); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byCombinedIsolationDeltaBetaCorrRaw", (double)o.tauID_byCombinedIsolationDeltaBetaCorrRaw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byTightCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_decayModeFinding", (double)o.tauID_decayModeFinding); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolation", (double)o.tauID_byMediumIsolation); os << r;
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
struct vertex_s
{
  bool	selected;
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

static bool fillObjectsCalled = false;
void fillObjects()
{
  fillObjectsCalled = true;

  electron.resize(electron_p.size());
  for(unsigned int i=0; i < electron.size(); ++i)
    {
      electron[i].selected	= false;
      electron[i].p	= electron_p[i];
      electron[i].energy	= electron_energy[i];
      electron[i].et	= electron_et[i];
      electron[i].px	= electron_px[i];
      electron[i].py	= electron_py[i];
      electron[i].pz	= electron_pz[i];
      electron[i].pt	= electron_pt[i];
      electron[i].phi	= electron_phi[i];
      electron[i].eta	= electron_eta[i];
      electron[i].eSuperClusterOverP	= electron_eSuperClusterOverP[i];
      electron[i].deltaEtaSuperClusterTrackAtVtx	= electron_deltaEtaSuperClusterTrackAtVtx[i];
      electron[i].deltaPhiSuperClusterTrackAtVtx	= electron_deltaPhiSuperClusterTrackAtVtx[i];
      electron[i].sigmaIetaIeta	= electron_sigmaIetaIeta[i];
      electron[i].scE1x5	= electron_scE1x5[i];
      electron[i].scE2x5Max	= electron_scE2x5Max[i];
      electron[i].scE5x5	= electron_scE5x5[i];
      electron[i].hadronicOverEm	= electron_hadronicOverEm[i];
      electron[i].dr04TkSumPt	= electron_dr04TkSumPt[i];
      electron[i].dr04EcalRecHitSumEt	= electron_dr04EcalRecHitSumEt[i];
      electron[i].gsfTrack_dxy	= electron_gsfTrack_dxy[i];
      electron[i].gsfTrack_d0	= electron_gsfTrack_d0[i];
      electron[i].gsfTrack_dz	= electron_gsfTrack_dz[i];
    }

  genparticlehelper.resize(genparticlehelper_firstMother.size());
  for(unsigned int i=0; i < genparticlehelper.size(); ++i)
    {
      genparticlehelper[i].selected	= false;
      genparticlehelper[i].firstMother	= genparticlehelper_firstMother[i];
      genparticlehelper[i].lastMother	= genparticlehelper_lastMother[i];
      genparticlehelper[i].firstDaughter	= genparticlehelper_firstDaughter[i];
      genparticlehelper[i].lastDaughter	= genparticlehelper_lastDaughter[i];
      genparticlehelper[i].charge	= genparticlehelper_charge[i];
      genparticlehelper[i].pdgId	= genparticlehelper_pdgId[i];
      genparticlehelper[i].status	= genparticlehelper_status[i];
      genparticlehelper[i].pt	= genparticlehelper_pt[i];
      genparticlehelper[i].eta	= genparticlehelper_eta[i];
      genparticlehelper[i].phi	= genparticlehelper_phi[i];
      genparticlehelper[i].mass	= genparticlehelper_mass[i];
    }

  gsfelectron.resize(gsfelectron_p.size());
  for(unsigned int i=0; i < gsfelectron.size(); ++i)
    {
      gsfelectron[i].selected	= false;
      gsfelectron[i].p	= gsfelectron_p[i];
      gsfelectron[i].energy	= gsfelectron_energy[i];
      gsfelectron[i].et	= gsfelectron_et[i];
      gsfelectron[i].px	= gsfelectron_px[i];
      gsfelectron[i].py	= gsfelectron_py[i];
      gsfelectron[i].pz	= gsfelectron_pz[i];
      gsfelectron[i].pt	= gsfelectron_pt[i];
      gsfelectron[i].phi	= gsfelectron_phi[i];
      gsfelectron[i].eta	= gsfelectron_eta[i];
      gsfelectron[i].eSuperClusterOverP	= gsfelectron_eSuperClusterOverP[i];
      gsfelectron[i].deltaEtaSuperClusterTrackAtVtx	= gsfelectron_deltaEtaSuperClusterTrackAtVtx[i];
      gsfelectron[i].deltaPhiSuperClusterTrackAtVtx	= gsfelectron_deltaPhiSuperClusterTrackAtVtx[i];
      gsfelectron[i].sigmaIetaIeta	= gsfelectron_sigmaIetaIeta[i];
      gsfelectron[i].scE1x5	= gsfelectron_scE1x5[i];
      gsfelectron[i].scE2x5Max	= gsfelectron_scE2x5Max[i];
      gsfelectron[i].scE5x5	= gsfelectron_scE5x5[i];
      gsfelectron[i].hadronicOverEm	= gsfelectron_hadronicOverEm[i];
      gsfelectron[i].dr04TkSumPt	= gsfelectron_dr04TkSumPt[i];
      gsfelectron[i].dr04EcalRecHitSumEt	= gsfelectron_dr04EcalRecHitSumEt[i];
      gsfelectron[i].gsfTrack_dxy	= gsfelectron_gsfTrack_dxy[i];
      gsfelectron[i].gsfTrack_d0	= gsfelectron_gsfTrack_d0[i];
      gsfelectron[i].gsfTrack_dz	= gsfelectron_gsfTrack_dz[i];
    }

  jet.resize(jet_charge.size());
  for(unsigned int i=0; i < jet.size(); ++i)
    {
      jet[i].selected	= false;
      jet[i].charge	= jet_charge[i];
      jet[i].p	= jet_p[i];
      jet[i].energy	= jet_energy[i];
      jet[i].et	= jet_et[i];
      jet[i].px	= jet_px[i];
      jet[i].py	= jet_py[i];
      jet[i].pz	= jet_pz[i];
      jet[i].pt	= jet_pt[i];
      jet[i].phi	= jet_phi[i];
      jet[i].eta	= jet_eta[i];
      jet[i].neutralHadronEnergy	= jet_neutralHadronEnergy[i];
      jet[i].chargedHadronEnergyFraction	= jet_chargedHadronEnergyFraction[i];
      jet[i].neutralHadronEnergyFraction	= jet_neutralHadronEnergyFraction[i];
      jet[i].chargedEmEnergyFraction	= jet_chargedEmEnergyFraction[i];
      jet[i].neutralEmEnergyFraction	= jet_neutralEmEnergyFraction[i];
      jet[i].photonEnergy	= jet_photonEnergy[i];
      jet[i].photonEnergyFraction	= jet_photonEnergyFraction[i];
      jet[i].electronEnergy	= jet_electronEnergy[i];
      jet[i].electronEnergyFraction	= jet_electronEnergyFraction[i];
      jet[i].muonEnergy	= jet_muonEnergy[i];
      jet[i].muonEnergyFraction	= jet_muonEnergyFraction[i];
      jet[i].HFHadronEnergy	= jet_HFHadronEnergy[i];
      jet[i].HFHadronEnergyFraction	= jet_HFHadronEnergyFraction[i];
      jet[i].HFEMEnergy	= jet_HFEMEnergy[i];
      jet[i].HFEMEnergyFraction	= jet_HFEMEnergyFraction[i];
      jet[i].chargedHadronMultiplicity	= jet_chargedHadronMultiplicity[i];
      jet[i].neutralHadronMultiplicity	= jet_neutralHadronMultiplicity[i];
      jet[i].photonMultiplicity	= jet_photonMultiplicity[i];
      jet[i].electronMultiplicity	= jet_electronMultiplicity[i];
      jet[i].HFHadronMultiplicity	= jet_HFHadronMultiplicity[i];
      jet[i].HFEMMultiplicity	= jet_HFEMMultiplicity[i];
      jet[i].numberOfDaughters	= jet_numberOfDaughters[i];
      jet[i].bDiscriminator_impactParameterTagInfos	= jet_bDiscriminator_impactParameterTagInfos[i];
      jet[i].bDiscriminator_secondaryVertexTagInfos	= jet_bDiscriminator_secondaryVertexTagInfos[i];
      jet[i].bDiscriminator_softMuonTagInfos	= jet_bDiscriminator_softMuonTagInfos[i];
      jet[i].bDiscriminator_secondaryVertexNegativeTagInfos	= jet_bDiscriminator_secondaryVertexNegativeTagInfos[i];
      jet[i].bDiscriminator_inclusiveSecondaryVertexFinderTagInfos	= jet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos[i];
      jet[i].bDiscriminator_softElectronTagInfos	= jet_bDiscriminator_softElectronTagInfos[i];
      jet[i].bDiscriminator_jetBProbabilityBJetTags	= jet_bDiscriminator_jetBProbabilityBJetTags[i];
      jet[i].bDiscriminator_jetProbabilityBJetTags	= jet_bDiscriminator_jetProbabilityBJetTags[i];
      jet[i].bDiscriminator_trackCountingHighPurBJetTags	= jet_bDiscriminator_trackCountingHighPurBJetTags[i];
      jet[i].bDiscriminator_trackCountingHighEffBJetTags	= jet_bDiscriminator_trackCountingHighEffBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexHighEffBJetTags	= jet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexHighPurBJetTags	= jet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags[i];
      jet[i].bDiscriminator_combinedSecondaryVertexBJetTags	= jet_bDiscriminator_combinedSecondaryVertexBJetTags[i];
      jet[i].bDiscriminator_combinedSecondaryVertexMVABJetTags	= jet_bDiscriminator_combinedSecondaryVertexMVABJetTags[i];
      jet[i].bDiscriminator_softMuonBJetTags	= jet_bDiscriminator_softMuonBJetTags[i];
      jet[i].bDiscriminator_softMuonByPtBJetTags	= jet_bDiscriminator_softMuonByPtBJetTags[i];
      jet[i].bDiscriminator_softMuonByIP3dBJetTags	= jet_bDiscriminator_softMuonByIP3dBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags	= jet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags[i];
      jet[i].bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags	= jet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags[i];
      jet[i].bDiscriminator_negativeTrackCountingHighEffJetTags	= jet_bDiscriminator_negativeTrackCountingHighEffJetTags[i];
      jet[i].bDiscriminator_negativeTrackCountingHighPurJetTags	= jet_bDiscriminator_negativeTrackCountingHighPurJetTags[i];
      jet[i].bDiscriminator_combinedInclusiveSecondaryVertexBJetTags	= jet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags[i];
      jet[i].bDiscriminator_combinedMVABJetTags	= jet_bDiscriminator_combinedMVABJetTags[i];
    }

  met.resize(met_p.size());
  for(unsigned int i=0; i < met.size(); ++i)
    {
      met[i].selected	= false;
      met[i].p	= met_p[i];
      met[i].energy	= met_energy[i];
      met[i].et	= met_et[i];
      met[i].px	= met_px[i];
      met[i].py	= met_py[i];
      met[i].pz	= met_pz[i];
      met[i].pt	= met_pt[i];
      met[i].phi	= met_phi[i];
      met[i].eta	= met_eta[i];
    }

  muon.resize(muon_p.size());
  for(unsigned int i=0; i < muon.size(); ++i)
    {
      muon[i].selected	= false;
      muon[i].p	= muon_p[i];
      muon[i].energy	= muon_energy[i];
      muon[i].et	= muon_et[i];
      muon[i].px	= muon_px[i];
      muon[i].py	= muon_py[i];
      muon[i].pz	= muon_pz[i];
      muon[i].pt	= muon_pt[i];
      muon[i].phi	= muon_phi[i];
      muon[i].eta	= muon_eta[i];
      muon[i].isGlobalMuon	= muon_isGlobalMuon[i];
      muon[i].isTrackerMuon	= muon_isTrackerMuon[i];
      muon[i].isPFMuon	= muon_isPFMuon[i];
      muon[i].pfIsolationR03_sumChargedHadronPt	= muon_pfIsolationR03_sumChargedHadronPt[i];
      muon[i].pfIsolationR03_sumChargedParticlePt	= muon_pfIsolationR03_sumChargedParticlePt[i];
      muon[i].pfIsolationR03_sumNeutralHadronEt	= muon_pfIsolationR03_sumNeutralHadronEt[i];
      muon[i].pfIsolationR03_sumNeutralHadronEtHighThreshold	= muon_pfIsolationR03_sumNeutralHadronEtHighThreshold[i];
      muon[i].pfIsolationR03_sumPhotonEt	= muon_pfIsolationR03_sumPhotonEt[i];
      muon[i].pfIsolationR03_sumPhotonEtHighThreshold	= muon_pfIsolationR03_sumPhotonEtHighThreshold[i];
      muon[i].pfIsolationR03_sumPUPt	= muon_pfIsolationR03_sumPUPt[i];
      muon[i].pfIsolationR04_sumChargedHadronPt	= muon_pfIsolationR04_sumChargedHadronPt[i];
      muon[i].pfIsolationR04_sumChargedParticlePt	= muon_pfIsolationR04_sumChargedParticlePt[i];
      muon[i].pfIsolationR04_sumNeutralHadronEt	= muon_pfIsolationR04_sumNeutralHadronEt[i];
      muon[i].pfIsolationR04_sumNeutralHadronEtHighThreshold	= muon_pfIsolationR04_sumNeutralHadronEtHighThreshold[i];
      muon[i].pfIsolationR04_sumPhotonEt	= muon_pfIsolationR04_sumPhotonEt[i];
      muon[i].pfIsolationR04_sumPhotonEtHighThreshold	= muon_pfIsolationR04_sumPhotonEtHighThreshold[i];
      muon[i].pfIsolationR04_sumPUPt	= muon_pfIsolationR04_sumPUPt[i];
      muon[i].numberOfMatchedStations	= muon_numberOfMatchedStations[i];
      muon[i].innerTrack_normalizedChi2	= muon_innerTrack_normalizedChi2[i];
      muon[i].innerTrack_dxy	= muon_innerTrack_dxy[i];
      muon[i].innerTrack_dz	= muon_innerTrack_dz[i];
      muon[i].innerTrack_hitPattern_numberOfValidPixelHits	= muon_innerTrack_hitPattern_numberOfValidPixelHits[i];
      muon[i].innerTrack_hitPattern_pixelLayersWithMeasurement	= muon_innerTrack_hitPattern_pixelLayersWithMeasurement[i];
      muon[i].globalTrack_normalizedChi2	= muon_globalTrack_normalizedChi2[i];
      muon[i].globalTrack_hitPattern_numberOfValidMuonHits	= muon_globalTrack_hitPattern_numberOfValidMuonHits[i];
      muon[i].muonBestTrack_dxy	= muon_muonBestTrack_dxy[i];
      muon[i].muonBestTrack_dz	= muon_muonBestTrack_dz[i];
    }

  pfmet.resize(pfmet_p.size());
  for(unsigned int i=0; i < pfmet.size(); ++i)
    {
      pfmet[i].selected	= false;
      pfmet[i].p	= pfmet_p[i];
      pfmet[i].energy	= pfmet_energy[i];
      pfmet[i].et	= pfmet_et[i];
      pfmet[i].px	= pfmet_px[i];
      pfmet[i].py	= pfmet_py[i];
      pfmet[i].pz	= pfmet_pz[i];
      pfmet[i].pt	= pfmet_pt[i];
      pfmet[i].phi	= pfmet_phi[i];
      pfmet[i].eta	= pfmet_eta[i];
    }

  pfmet2.resize(pfmet2_p.size());
  for(unsigned int i=0; i < pfmet2.size(); ++i)
    {
      pfmet2[i].selected	= false;
      pfmet2[i].p	= pfmet2_p[i];
      pfmet2[i].energy	= pfmet2_energy[i];
      pfmet2[i].et	= pfmet2_et[i];
      pfmet2[i].px	= pfmet2_px[i];
      pfmet2[i].py	= pfmet2_py[i];
      pfmet2[i].pz	= pfmet2_pz[i];
      pfmet2[i].pt	= pfmet2_pt[i];
      pfmet2[i].phi	= pfmet2_phi[i];
      pfmet2[i].eta	= pfmet2_eta[i];
    }

  pileupsummaryinfo.resize(pileupsummaryinfo_getBunchCrossing.size());
  for(unsigned int i=0; i < pileupsummaryinfo.size(); ++i)
    {
      pileupsummaryinfo[i].selected	= false;
      pileupsummaryinfo[i].getBunchCrossing	= pileupsummaryinfo_getBunchCrossing[i];
      pileupsummaryinfo[i].getPU_NumInteractions	= pileupsummaryinfo_getPU_NumInteractions[i];
    }

  tau.resize(tau_charge.size());
  for(unsigned int i=0; i < tau.size(); ++i)
    {
      tau[i].selected	= false;
      tau[i].charge	= tau_charge[i];
      tau[i].p	= tau_p[i];
      tau[i].energy	= tau_energy[i];
      tau[i].et	= tau_et[i];
      tau[i].px	= tau_px[i];
      tau[i].py	= tau_py[i];
      tau[i].pz	= tau_pz[i];
      tau[i].pt	= tau_pt[i];
      tau[i].phi	= tau_phi[i];
      tau[i].eta	= tau_eta[i];
      tau[i].tauID_byIsolationMVAraw	= tau_tauID_byIsolationMVAraw[i];
      tau[i].tauID_byMediumCombinedIsolationDeltaBetaCorr	= tau_tauID_byMediumCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits	= tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[i];
      tau[i].tauID_againstMuonMedium	= tau_tauID_againstMuonMedium[i];
      tau[i].tauID_againstElectronTightMVA3	= tau_tauID_againstElectronTightMVA3[i];
      tau[i].tauID_againstElectronTightMVA2	= tau_tauID_againstElectronTightMVA2[i];
      tau[i].tauID_byLooseIsolationMVA2	= tau_tauID_byLooseIsolationMVA2[i];
      tau[i].tauID_againstMuonTight	= tau_tauID_againstMuonTight[i];
      tau[i].tauID_againstMuonLoose2	= tau_tauID_againstMuonLoose2[i];
      tau[i].tauID_byTightIsolationMVA	= tau_tauID_byTightIsolationMVA[i];
      tau[i].tauID_byLooseIsolation	= tau_tauID_byLooseIsolation[i];
      tau[i].tauID_byLooseCombinedIsolationDeltaBetaCorr	= tau_tauID_byLooseCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_againstElectronLooseMVA3	= tau_tauID_againstElectronLooseMVA3[i];
      tau[i].tauID_againstElectronLooseMVA2	= tau_tauID_againstElectronLooseMVA2[i];
      tau[i].tauID_againstElectronTight	= tau_tauID_againstElectronTight[i];
      tau[i].tauID_byVLooseCombinedIsolationDeltaBetaCorr	= tau_tauID_byVLooseCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_againstElectronVTightMVA3	= tau_tauID_againstElectronVTightMVA3[i];
      tau[i].tauID_againstElectronMediumMVA3	= tau_tauID_againstElectronMediumMVA3[i];
      tau[i].tauID_againstElectronMediumMVA2	= tau_tauID_againstElectronMediumMVA2[i];
      tau[i].tauID_againstElectronMVA	= tau_tauID_againstElectronMVA[i];
      tau[i].tauID_againstMuonLoose	= tau_tauID_againstMuonLoose[i];
      tau[i].tauID_againstMuonTight2	= tau_tauID_againstMuonTight2[i];
      tau[i].tauID_againstElectronMedium	= tau_tauID_againstElectronMedium[i];
      tau[i].tauID_againstElectronVLooseMVA2	= tau_tauID_againstElectronVLooseMVA2[i];
      tau[i].tauID_againstMuonMedium2	= tau_tauID_againstMuonMedium2[i];
      tau[i].tauID_byMediumIsolationMVA	= tau_tauID_byMediumIsolationMVA[i];
      tau[i].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits	= tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byLooseIsolationDeltaBetaCorr	= tau_tauID_byLooseIsolationDeltaBetaCorr[i];
      tau[i].tauID_byIsolationMVA2raw	= tau_tauID_byIsolationMVA2raw[i];
      tau[i].tauID_byTightIsolationMVA2	= tau_tauID_byTightIsolationMVA2[i];
      tau[i].tauID_againstElectronMVA2category	= tau_tauID_againstElectronMVA2category[i];
      tau[i].tauID_byTightIsolationDeltaBetaCorr	= tau_tauID_byTightIsolationDeltaBetaCorr[i];
      tau[i].tauID_againstElectronDeadECAL	= tau_tauID_againstElectronDeadECAL[i];
      tau[i].tauID_againstElectronMVA3category	= tau_tauID_againstElectronMVA3category[i];
      tau[i].tauID_byVLooseIsolationDeltaBetaCorr	= tau_tauID_byVLooseIsolationDeltaBetaCorr[i];
      tau[i].tauID_againstElectronMVA2raw	= tau_tauID_againstElectronMVA2raw[i];
      tau[i].tauID_byTightCombinedIsolationDeltaBetaCorr	= tau_tauID_byTightCombinedIsolationDeltaBetaCorr[i];
      tau[i].tauID_againstElectronMVA3raw	= tau_tauID_againstElectronMVA3raw[i];
      tau[i].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits	= tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byMediumIsolationMVA2	= tau_tauID_byMediumIsolationMVA2[i];
      tau[i].tauID_byMediumIsolationDeltaBetaCorr	= tau_tauID_byMediumIsolationDeltaBetaCorr[i];
      tau[i].tauID_againstElectronLoose	= tau_tauID_againstElectronLoose[i];
      tau[i].tauID_byTightIsolation	= tau_tauID_byTightIsolation[i];
      tau[i].tauID_byVLooseIsolation	= tau_tauID_byVLooseIsolation[i];
      tau[i].tauID_byLooseIsolationMVA	= tau_tauID_byLooseIsolationMVA[i];
      tau[i].tauID_byCombinedIsolationDeltaBetaCorrRaw	= tau_tauID_byCombinedIsolationDeltaBetaCorrRaw[i];
      tau[i].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits	= tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_decayModeFinding	= tau_tauID_decayModeFinding[i];
      tau[i].tauID_byMediumIsolation	= tau_tauID_byMediumIsolation[i];
      tau[i].leadPFChargedHadrCand_p	= tau_leadPFChargedHadrCand_p[i];
      tau[i].leadPFChargedHadrCand_energy	= tau_leadPFChargedHadrCand_energy[i];
      tau[i].leadPFChargedHadrCand_et	= tau_leadPFChargedHadrCand_et[i];
      tau[i].leadPFChargedHadrCand_mass	= tau_leadPFChargedHadrCand_mass[i];
      tau[i].leadPFChargedHadrCand_massSqr	= tau_leadPFChargedHadrCand_massSqr[i];
      tau[i].leadPFChargedHadrCand_mt	= tau_leadPFChargedHadrCand_mt[i];
      tau[i].leadPFChargedHadrCand_mtSqr	= tau_leadPFChargedHadrCand_mtSqr[i];
      tau[i].leadPFChargedHadrCand_px	= tau_leadPFChargedHadrCand_px[i];
      tau[i].leadPFChargedHadrCand_py	= tau_leadPFChargedHadrCand_py[i];
      tau[i].leadPFChargedHadrCand_pz	= tau_leadPFChargedHadrCand_pz[i];
      tau[i].leadPFChargedHadrCand_pt	= tau_leadPFChargedHadrCand_pt[i];
      tau[i].leadPFChargedHadrCand_phi	= tau_leadPFChargedHadrCand_phi[i];
      tau[i].leadPFChargedHadrCand_theta	= tau_leadPFChargedHadrCand_theta[i];
      tau[i].leadPFChargedHadrCand_eta	= tau_leadPFChargedHadrCand_eta[i];
      tau[i].leadPFChargedHadrCand_rapidity	= tau_leadPFChargedHadrCand_rapidity[i];
      tau[i].leadPFChargedHadrCand_y	= tau_leadPFChargedHadrCand_y[i];
      tau[i].signalPFChargedHadrCands_size	= tau_signalPFChargedHadrCands_size[i];
    }

  vertex.resize(vertex_isFake.size());
  for(unsigned int i=0; i < vertex.size(); ++i)
    {
      vertex[i].selected	= false;
      vertex[i].isFake	= vertex_isFake[i];
      vertex[i].ndof	= vertex_ndof[i];
      vertex[i].x	= vertex_x[i];
      vertex[i].y	= vertex_y[i];
      vertex[i].z	= vertex_z[i];
    }
}

//-----------------------------------------------------------------------------
// --- Call saveSelectedObjects() just before call to addEvent if
// --- you wish to save only the selected objects
//-----------------------------------------------------------------------------
void saveSelectedObjects()
{
  if ( ! fillObjectsCalled ) return;
  int n = 0;

  n = 0;
  for(unsigned int i=0; i < electron.size(); ++i)
    {
      if ( ! electron[i].selected ) continue;
      electron_p[n]	= electron[i].p;
      electron_energy[n]	= electron[i].energy;
      electron_et[n]	= electron[i].et;
      electron_px[n]	= electron[i].px;
      electron_py[n]	= electron[i].py;
      electron_pz[n]	= electron[i].pz;
      electron_pt[n]	= electron[i].pt;
      electron_phi[n]	= electron[i].phi;
      electron_eta[n]	= electron[i].eta;
      electron_eSuperClusterOverP[n]	= electron[i].eSuperClusterOverP;
      electron_deltaEtaSuperClusterTrackAtVtx[n]	= electron[i].deltaEtaSuperClusterTrackAtVtx;
      electron_deltaPhiSuperClusterTrackAtVtx[n]	= electron[i].deltaPhiSuperClusterTrackAtVtx;
      electron_sigmaIetaIeta[n]	= electron[i].sigmaIetaIeta;
      electron_scE1x5[n]	= electron[i].scE1x5;
      electron_scE2x5Max[n]	= electron[i].scE2x5Max;
      electron_scE5x5[n]	= electron[i].scE5x5;
      electron_hadronicOverEm[n]	= electron[i].hadronicOverEm;
      electron_dr04TkSumPt[n]	= electron[i].dr04TkSumPt;
      electron_dr04EcalRecHitSumEt[n]	= electron[i].dr04EcalRecHitSumEt;
      electron_gsfTrack_dxy[n]	= electron[i].gsfTrack_dxy;
      electron_gsfTrack_d0[n]	= electron[i].gsfTrack_d0;
      electron_gsfTrack_dz[n]	= electron[i].gsfTrack_dz;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < genparticlehelper.size(); ++i)
    {
      if ( ! genparticlehelper[i].selected ) continue;
      genparticlehelper_firstMother[n]	= genparticlehelper[i].firstMother;
      genparticlehelper_lastMother[n]	= genparticlehelper[i].lastMother;
      genparticlehelper_firstDaughter[n]	= genparticlehelper[i].firstDaughter;
      genparticlehelper_lastDaughter[n]	= genparticlehelper[i].lastDaughter;
      genparticlehelper_charge[n]	= genparticlehelper[i].charge;
      genparticlehelper_pdgId[n]	= genparticlehelper[i].pdgId;
      genparticlehelper_status[n]	= genparticlehelper[i].status;
      genparticlehelper_pt[n]	= genparticlehelper[i].pt;
      genparticlehelper_eta[n]	= genparticlehelper[i].eta;
      genparticlehelper_phi[n]	= genparticlehelper[i].phi;
      genparticlehelper_mass[n]	= genparticlehelper[i].mass;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < gsfelectron.size(); ++i)
    {
      if ( ! gsfelectron[i].selected ) continue;
      gsfelectron_p[n]	= gsfelectron[i].p;
      gsfelectron_energy[n]	= gsfelectron[i].energy;
      gsfelectron_et[n]	= gsfelectron[i].et;
      gsfelectron_px[n]	= gsfelectron[i].px;
      gsfelectron_py[n]	= gsfelectron[i].py;
      gsfelectron_pz[n]	= gsfelectron[i].pz;
      gsfelectron_pt[n]	= gsfelectron[i].pt;
      gsfelectron_phi[n]	= gsfelectron[i].phi;
      gsfelectron_eta[n]	= gsfelectron[i].eta;
      gsfelectron_eSuperClusterOverP[n]	= gsfelectron[i].eSuperClusterOverP;
      gsfelectron_deltaEtaSuperClusterTrackAtVtx[n]	= gsfelectron[i].deltaEtaSuperClusterTrackAtVtx;
      gsfelectron_deltaPhiSuperClusterTrackAtVtx[n]	= gsfelectron[i].deltaPhiSuperClusterTrackAtVtx;
      gsfelectron_sigmaIetaIeta[n]	= gsfelectron[i].sigmaIetaIeta;
      gsfelectron_scE1x5[n]	= gsfelectron[i].scE1x5;
      gsfelectron_scE2x5Max[n]	= gsfelectron[i].scE2x5Max;
      gsfelectron_scE5x5[n]	= gsfelectron[i].scE5x5;
      gsfelectron_hadronicOverEm[n]	= gsfelectron[i].hadronicOverEm;
      gsfelectron_dr04TkSumPt[n]	= gsfelectron[i].dr04TkSumPt;
      gsfelectron_dr04EcalRecHitSumEt[n]	= gsfelectron[i].dr04EcalRecHitSumEt;
      gsfelectron_gsfTrack_dxy[n]	= gsfelectron[i].gsfTrack_dxy;
      gsfelectron_gsfTrack_d0[n]	= gsfelectron[i].gsfTrack_d0;
      gsfelectron_gsfTrack_dz[n]	= gsfelectron[i].gsfTrack_dz;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < jet.size(); ++i)
    {
      if ( ! jet[i].selected ) continue;
      jet_charge[n]	= jet[i].charge;
      jet_p[n]	= jet[i].p;
      jet_energy[n]	= jet[i].energy;
      jet_et[n]	= jet[i].et;
      jet_px[n]	= jet[i].px;
      jet_py[n]	= jet[i].py;
      jet_pz[n]	= jet[i].pz;
      jet_pt[n]	= jet[i].pt;
      jet_phi[n]	= jet[i].phi;
      jet_eta[n]	= jet[i].eta;
      jet_neutralHadronEnergy[n]	= jet[i].neutralHadronEnergy;
      jet_chargedHadronEnergyFraction[n]	= jet[i].chargedHadronEnergyFraction;
      jet_neutralHadronEnergyFraction[n]	= jet[i].neutralHadronEnergyFraction;
      jet_chargedEmEnergyFraction[n]	= jet[i].chargedEmEnergyFraction;
      jet_neutralEmEnergyFraction[n]	= jet[i].neutralEmEnergyFraction;
      jet_photonEnergy[n]	= jet[i].photonEnergy;
      jet_photonEnergyFraction[n]	= jet[i].photonEnergyFraction;
      jet_electronEnergy[n]	= jet[i].electronEnergy;
      jet_electronEnergyFraction[n]	= jet[i].electronEnergyFraction;
      jet_muonEnergy[n]	= jet[i].muonEnergy;
      jet_muonEnergyFraction[n]	= jet[i].muonEnergyFraction;
      jet_HFHadronEnergy[n]	= jet[i].HFHadronEnergy;
      jet_HFHadronEnergyFraction[n]	= jet[i].HFHadronEnergyFraction;
      jet_HFEMEnergy[n]	= jet[i].HFEMEnergy;
      jet_HFEMEnergyFraction[n]	= jet[i].HFEMEnergyFraction;
      jet_chargedHadronMultiplicity[n]	= jet[i].chargedHadronMultiplicity;
      jet_neutralHadronMultiplicity[n]	= jet[i].neutralHadronMultiplicity;
      jet_photonMultiplicity[n]	= jet[i].photonMultiplicity;
      jet_electronMultiplicity[n]	= jet[i].electronMultiplicity;
      jet_HFHadronMultiplicity[n]	= jet[i].HFHadronMultiplicity;
      jet_HFEMMultiplicity[n]	= jet[i].HFEMMultiplicity;
      jet_numberOfDaughters[n]	= jet[i].numberOfDaughters;
      jet_bDiscriminator_impactParameterTagInfos[n]	= jet[i].bDiscriminator_impactParameterTagInfos;
      jet_bDiscriminator_secondaryVertexTagInfos[n]	= jet[i].bDiscriminator_secondaryVertexTagInfos;
      jet_bDiscriminator_softMuonTagInfos[n]	= jet[i].bDiscriminator_softMuonTagInfos;
      jet_bDiscriminator_secondaryVertexNegativeTagInfos[n]	= jet[i].bDiscriminator_secondaryVertexNegativeTagInfos;
      jet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos[n]	= jet[i].bDiscriminator_inclusiveSecondaryVertexFinderTagInfos;
      jet_bDiscriminator_softElectronTagInfos[n]	= jet[i].bDiscriminator_softElectronTagInfos;
      jet_bDiscriminator_jetBProbabilityBJetTags[n]	= jet[i].bDiscriminator_jetBProbabilityBJetTags;
      jet_bDiscriminator_jetProbabilityBJetTags[n]	= jet[i].bDiscriminator_jetProbabilityBJetTags;
      jet_bDiscriminator_trackCountingHighPurBJetTags[n]	= jet[i].bDiscriminator_trackCountingHighPurBJetTags;
      jet_bDiscriminator_trackCountingHighEffBJetTags[n]	= jet[i].bDiscriminator_trackCountingHighEffBJetTags;
      jet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags[n]	= jet[i].bDiscriminator_simpleSecondaryVertexHighEffBJetTags;
      jet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags[n]	= jet[i].bDiscriminator_simpleSecondaryVertexHighPurBJetTags;
      jet_bDiscriminator_combinedSecondaryVertexBJetTags[n]	= jet[i].bDiscriminator_combinedSecondaryVertexBJetTags;
      jet_bDiscriminator_combinedSecondaryVertexMVABJetTags[n]	= jet[i].bDiscriminator_combinedSecondaryVertexMVABJetTags;
      jet_bDiscriminator_softMuonBJetTags[n]	= jet[i].bDiscriminator_softMuonBJetTags;
      jet_bDiscriminator_softMuonByPtBJetTags[n]	= jet[i].bDiscriminator_softMuonByPtBJetTags;
      jet_bDiscriminator_softMuonByIP3dBJetTags[n]	= jet[i].bDiscriminator_softMuonByIP3dBJetTags;
      jet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags[n]	= jet[i].bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags;
      jet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags[n]	= jet[i].bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags;
      jet_bDiscriminator_negativeTrackCountingHighEffJetTags[n]	= jet[i].bDiscriminator_negativeTrackCountingHighEffJetTags;
      jet_bDiscriminator_negativeTrackCountingHighPurJetTags[n]	= jet[i].bDiscriminator_negativeTrackCountingHighPurJetTags;
      jet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags[n]	= jet[i].bDiscriminator_combinedInclusiveSecondaryVertexBJetTags;
      jet_bDiscriminator_combinedMVABJetTags[n]	= jet[i].bDiscriminator_combinedMVABJetTags;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < met.size(); ++i)
    {
      if ( ! met[i].selected ) continue;
      met_p[n]	= met[i].p;
      met_energy[n]	= met[i].energy;
      met_et[n]	= met[i].et;
      met_px[n]	= met[i].px;
      met_py[n]	= met[i].py;
      met_pz[n]	= met[i].pz;
      met_pt[n]	= met[i].pt;
      met_phi[n]	= met[i].phi;
      met_eta[n]	= met[i].eta;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < muon.size(); ++i)
    {
      if ( ! muon[i].selected ) continue;
      muon_p[n]	= muon[i].p;
      muon_energy[n]	= muon[i].energy;
      muon_et[n]	= muon[i].et;
      muon_px[n]	= muon[i].px;
      muon_py[n]	= muon[i].py;
      muon_pz[n]	= muon[i].pz;
      muon_pt[n]	= muon[i].pt;
      muon_phi[n]	= muon[i].phi;
      muon_eta[n]	= muon[i].eta;
      muon_isGlobalMuon[n]	= muon[i].isGlobalMuon;
      muon_isTrackerMuon[n]	= muon[i].isTrackerMuon;
      muon_isPFMuon[n]	= muon[i].isPFMuon;
      muon_pfIsolationR03_sumChargedHadronPt[n]	= muon[i].pfIsolationR03_sumChargedHadronPt;
      muon_pfIsolationR03_sumChargedParticlePt[n]	= muon[i].pfIsolationR03_sumChargedParticlePt;
      muon_pfIsolationR03_sumNeutralHadronEt[n]	= muon[i].pfIsolationR03_sumNeutralHadronEt;
      muon_pfIsolationR03_sumNeutralHadronEtHighThreshold[n]	= muon[i].pfIsolationR03_sumNeutralHadronEtHighThreshold;
      muon_pfIsolationR03_sumPhotonEt[n]	= muon[i].pfIsolationR03_sumPhotonEt;
      muon_pfIsolationR03_sumPhotonEtHighThreshold[n]	= muon[i].pfIsolationR03_sumPhotonEtHighThreshold;
      muon_pfIsolationR03_sumPUPt[n]	= muon[i].pfIsolationR03_sumPUPt;
      muon_pfIsolationR04_sumChargedHadronPt[n]	= muon[i].pfIsolationR04_sumChargedHadronPt;
      muon_pfIsolationR04_sumChargedParticlePt[n]	= muon[i].pfIsolationR04_sumChargedParticlePt;
      muon_pfIsolationR04_sumNeutralHadronEt[n]	= muon[i].pfIsolationR04_sumNeutralHadronEt;
      muon_pfIsolationR04_sumNeutralHadronEtHighThreshold[n]	= muon[i].pfIsolationR04_sumNeutralHadronEtHighThreshold;
      muon_pfIsolationR04_sumPhotonEt[n]	= muon[i].pfIsolationR04_sumPhotonEt;
      muon_pfIsolationR04_sumPhotonEtHighThreshold[n]	= muon[i].pfIsolationR04_sumPhotonEtHighThreshold;
      muon_pfIsolationR04_sumPUPt[n]	= muon[i].pfIsolationR04_sumPUPt;
      muon_numberOfMatchedStations[n]	= muon[i].numberOfMatchedStations;
      muon_innerTrack_normalizedChi2[n]	= muon[i].innerTrack_normalizedChi2;
      muon_innerTrack_dxy[n]	= muon[i].innerTrack_dxy;
      muon_innerTrack_dz[n]	= muon[i].innerTrack_dz;
      muon_innerTrack_hitPattern_numberOfValidPixelHits[n]	= muon[i].innerTrack_hitPattern_numberOfValidPixelHits;
      muon_innerTrack_hitPattern_pixelLayersWithMeasurement[n]	= muon[i].innerTrack_hitPattern_pixelLayersWithMeasurement;
      muon_globalTrack_normalizedChi2[n]	= muon[i].globalTrack_normalizedChi2;
      muon_globalTrack_hitPattern_numberOfValidMuonHits[n]	= muon[i].globalTrack_hitPattern_numberOfValidMuonHits;
      muon_muonBestTrack_dxy[n]	= muon[i].muonBestTrack_dxy;
      muon_muonBestTrack_dz[n]	= muon[i].muonBestTrack_dz;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < pfmet.size(); ++i)
    {
      if ( ! pfmet[i].selected ) continue;
      pfmet_p[n]	= pfmet[i].p;
      pfmet_energy[n]	= pfmet[i].energy;
      pfmet_et[n]	= pfmet[i].et;
      pfmet_px[n]	= pfmet[i].px;
      pfmet_py[n]	= pfmet[i].py;
      pfmet_pz[n]	= pfmet[i].pz;
      pfmet_pt[n]	= pfmet[i].pt;
      pfmet_phi[n]	= pfmet[i].phi;
      pfmet_eta[n]	= pfmet[i].eta;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < pfmet2.size(); ++i)
    {
      if ( ! pfmet2[i].selected ) continue;
      pfmet2_p[n]	= pfmet2[i].p;
      pfmet2_energy[n]	= pfmet2[i].energy;
      pfmet2_et[n]	= pfmet2[i].et;
      pfmet2_px[n]	= pfmet2[i].px;
      pfmet2_py[n]	= pfmet2[i].py;
      pfmet2_pz[n]	= pfmet2[i].pz;
      pfmet2_pt[n]	= pfmet2[i].pt;
      pfmet2_phi[n]	= pfmet2[i].phi;
      pfmet2_eta[n]	= pfmet2[i].eta;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < pileupsummaryinfo.size(); ++i)
    {
      if ( ! pileupsummaryinfo[i].selected ) continue;
      pileupsummaryinfo_getBunchCrossing[n]	= pileupsummaryinfo[i].getBunchCrossing;
      pileupsummaryinfo_getPU_NumInteractions[n]	= pileupsummaryinfo[i].getPU_NumInteractions;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < tau.size(); ++i)
    {
      if ( ! tau[i].selected ) continue;
      tau_charge[n]	= tau[i].charge;
      tau_p[n]	= tau[i].p;
      tau_energy[n]	= tau[i].energy;
      tau_et[n]	= tau[i].et;
      tau_px[n]	= tau[i].px;
      tau_py[n]	= tau[i].py;
      tau_pz[n]	= tau[i].pz;
      tau_pt[n]	= tau[i].pt;
      tau_phi[n]	= tau[i].phi;
      tau_eta[n]	= tau[i].eta;
      tau_tauID_byIsolationMVAraw[n]	= tau[i].tauID_byIsolationMVAraw;
      tau_tauID_byMediumCombinedIsolationDeltaBetaCorr[n]	= tau[i].tauID_byMediumCombinedIsolationDeltaBetaCorr;
      tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[n]	= tau[i].tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits;
      tau_tauID_againstMuonMedium[n]	= tau[i].tauID_againstMuonMedium;
      tau_tauID_againstElectronTightMVA3[n]	= tau[i].tauID_againstElectronTightMVA3;
      tau_tauID_againstElectronTightMVA2[n]	= tau[i].tauID_againstElectronTightMVA2;
      tau_tauID_byLooseIsolationMVA2[n]	= tau[i].tauID_byLooseIsolationMVA2;
      tau_tauID_againstMuonTight[n]	= tau[i].tauID_againstMuonTight;
      tau_tauID_againstMuonLoose2[n]	= tau[i].tauID_againstMuonLoose2;
      tau_tauID_byTightIsolationMVA[n]	= tau[i].tauID_byTightIsolationMVA;
      tau_tauID_byLooseIsolation[n]	= tau[i].tauID_byLooseIsolation;
      tau_tauID_byLooseCombinedIsolationDeltaBetaCorr[n]	= tau[i].tauID_byLooseCombinedIsolationDeltaBetaCorr;
      tau_tauID_againstElectronLooseMVA3[n]	= tau[i].tauID_againstElectronLooseMVA3;
      tau_tauID_againstElectronLooseMVA2[n]	= tau[i].tauID_againstElectronLooseMVA2;
      tau_tauID_againstElectronTight[n]	= tau[i].tauID_againstElectronTight;
      tau_tauID_byVLooseCombinedIsolationDeltaBetaCorr[n]	= tau[i].tauID_byVLooseCombinedIsolationDeltaBetaCorr;
      tau_tauID_againstElectronVTightMVA3[n]	= tau[i].tauID_againstElectronVTightMVA3;
      tau_tauID_againstElectronMediumMVA3[n]	= tau[i].tauID_againstElectronMediumMVA3;
      tau_tauID_againstElectronMediumMVA2[n]	= tau[i].tauID_againstElectronMediumMVA2;
      tau_tauID_againstElectronMVA[n]	= tau[i].tauID_againstElectronMVA;
      tau_tauID_againstMuonLoose[n]	= tau[i].tauID_againstMuonLoose;
      tau_tauID_againstMuonTight2[n]	= tau[i].tauID_againstMuonTight2;
      tau_tauID_againstElectronMedium[n]	= tau[i].tauID_againstElectronMedium;
      tau_tauID_againstElectronVLooseMVA2[n]	= tau[i].tauID_againstElectronVLooseMVA2;
      tau_tauID_againstMuonMedium2[n]	= tau[i].tauID_againstMuonMedium2;
      tau_tauID_byMediumIsolationMVA[n]	= tau[i].tauID_byMediumIsolationMVA;
      tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[n]	= tau[i].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits;
      tau_tauID_byLooseIsolationDeltaBetaCorr[n]	= tau[i].tauID_byLooseIsolationDeltaBetaCorr;
      tau_tauID_byIsolationMVA2raw[n]	= tau[i].tauID_byIsolationMVA2raw;
      tau_tauID_byTightIsolationMVA2[n]	= tau[i].tauID_byTightIsolationMVA2;
      tau_tauID_againstElectronMVA2category[n]	= tau[i].tauID_againstElectronMVA2category;
      tau_tauID_byTightIsolationDeltaBetaCorr[n]	= tau[i].tauID_byTightIsolationDeltaBetaCorr;
      tau_tauID_againstElectronDeadECAL[n]	= tau[i].tauID_againstElectronDeadECAL;
      tau_tauID_againstElectronMVA3category[n]	= tau[i].tauID_againstElectronMVA3category;
      tau_tauID_byVLooseIsolationDeltaBetaCorr[n]	= tau[i].tauID_byVLooseIsolationDeltaBetaCorr;
      tau_tauID_againstElectronMVA2raw[n]	= tau[i].tauID_againstElectronMVA2raw;
      tau_tauID_byTightCombinedIsolationDeltaBetaCorr[n]	= tau[i].tauID_byTightCombinedIsolationDeltaBetaCorr;
      tau_tauID_againstElectronMVA3raw[n]	= tau[i].tauID_againstElectronMVA3raw;
      tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[n]	= tau[i].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits;
      tau_tauID_byMediumIsolationMVA2[n]	= tau[i].tauID_byMediumIsolationMVA2;
      tau_tauID_byMediumIsolationDeltaBetaCorr[n]	= tau[i].tauID_byMediumIsolationDeltaBetaCorr;
      tau_tauID_againstElectronLoose[n]	= tau[i].tauID_againstElectronLoose;
      tau_tauID_byTightIsolation[n]	= tau[i].tauID_byTightIsolation;
      tau_tauID_byVLooseIsolation[n]	= tau[i].tauID_byVLooseIsolation;
      tau_tauID_byLooseIsolationMVA[n]	= tau[i].tauID_byLooseIsolationMVA;
      tau_tauID_byCombinedIsolationDeltaBetaCorrRaw[n]	= tau[i].tauID_byCombinedIsolationDeltaBetaCorrRaw;
      tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[n]	= tau[i].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits;
      tau_tauID_decayModeFinding[n]	= tau[i].tauID_decayModeFinding;
      tau_tauID_byMediumIsolation[n]	= tau[i].tauID_byMediumIsolation;
      tau_leadPFChargedHadrCand_p[n]	= tau[i].leadPFChargedHadrCand_p;
      tau_leadPFChargedHadrCand_energy[n]	= tau[i].leadPFChargedHadrCand_energy;
      tau_leadPFChargedHadrCand_et[n]	= tau[i].leadPFChargedHadrCand_et;
      tau_leadPFChargedHadrCand_mass[n]	= tau[i].leadPFChargedHadrCand_mass;
      tau_leadPFChargedHadrCand_massSqr[n]	= tau[i].leadPFChargedHadrCand_massSqr;
      tau_leadPFChargedHadrCand_mt[n]	= tau[i].leadPFChargedHadrCand_mt;
      tau_leadPFChargedHadrCand_mtSqr[n]	= tau[i].leadPFChargedHadrCand_mtSqr;
      tau_leadPFChargedHadrCand_px[n]	= tau[i].leadPFChargedHadrCand_px;
      tau_leadPFChargedHadrCand_py[n]	= tau[i].leadPFChargedHadrCand_py;
      tau_leadPFChargedHadrCand_pz[n]	= tau[i].leadPFChargedHadrCand_pz;
      tau_leadPFChargedHadrCand_pt[n]	= tau[i].leadPFChargedHadrCand_pt;
      tau_leadPFChargedHadrCand_phi[n]	= tau[i].leadPFChargedHadrCand_phi;
      tau_leadPFChargedHadrCand_theta[n]	= tau[i].leadPFChargedHadrCand_theta;
      tau_leadPFChargedHadrCand_eta[n]	= tau[i].leadPFChargedHadrCand_eta;
      tau_leadPFChargedHadrCand_rapidity[n]	= tau[i].leadPFChargedHadrCand_rapidity;
      tau_leadPFChargedHadrCand_y[n]	= tau[i].leadPFChargedHadrCand_y;
      tau_signalPFChargedHadrCands_size[n]	= tau[i].signalPFChargedHadrCands_size;
      n++;
    }

  n = 0;
  for(unsigned int i=0; i < vertex.size(); ++i)
    {
      if ( ! vertex[i].selected ) continue;
      vertex_isFake[n]	= vertex[i].isFake;
      vertex_ndof[n]	= vertex[i].ndof;
      vertex_x[n]	= vertex[i].x;
      vertex_y[n]	= vertex[i].y;
      vertex_z[n]	= vertex[i].z;
      n++;
    }
  fillObjectsCalled = false;
}

//-----------------------------------------------------------------------------
// -- Select variables to be read
//-----------------------------------------------------------------------------
void selectVariables(itreestream& stream)
{
  stream.select("recoBeamSpot_offlineBeamSpot.x0", beamspot_x0);
  stream.select("recoBeamSpot_offlineBeamSpot.y0", beamspot_y0);
  stream.select("recoBeamSpot_offlineBeamSpot.z0", beamspot_z0);
  stream.select("patElectron_patElectrons.deltaEtaSuperClusterTrackAtVtx", electron_deltaEtaSuperClusterTrackAtVtx);
  stream.select("patElectron_patElectrons.deltaPhiSuperClusterTrackAtVtx", electron_deltaPhiSuperClusterTrackAtVtx);
  stream.select("patElectron_patElectrons.dr04EcalRecHitSumEt", electron_dr04EcalRecHitSumEt);
  stream.select("patElectron_patElectrons.dr04TkSumPt", electron_dr04TkSumPt);
  stream.select("patElectron_patElectrons.eSuperClusterOverP", electron_eSuperClusterOverP);
  stream.select("patElectron_patElectrons.energy", electron_energy);
  stream.select("patElectron_patElectrons.et", electron_et);
  stream.select("patElectron_patElectrons.eta", electron_eta);
  stream.select("patElectron_patElectrons.gsfTrack_d0", electron_gsfTrack_d0);
  stream.select("patElectron_patElectrons.gsfTrack_dxy", electron_gsfTrack_dxy);
  stream.select("patElectron_patElectrons.gsfTrack_dz", electron_gsfTrack_dz);
  stream.select("patElectron_patElectrons.hadronicOverEm", electron_hadronicOverEm);
  stream.select("patElectron_patElectrons.p", electron_p);
  stream.select("patElectron_patElectrons.phi", electron_phi);
  stream.select("patElectron_patElectrons.pt", electron_pt);
  stream.select("patElectron_patElectrons.px", electron_px);
  stream.select("patElectron_patElectrons.py", electron_py);
  stream.select("patElectron_patElectrons.pz", electron_pz);
  stream.select("patElectron_patElectrons.scE1x5", electron_scE1x5);
  stream.select("patElectron_patElectrons.scE2x5Max", electron_scE2x5Max);
  stream.select("patElectron_patElectrons.scE5x5", electron_scE5x5);
  stream.select("patElectron_patElectrons.sigmaIetaIeta", electron_sigmaIetaIeta);
  stream.select("edmEventHelper_info.bunchCrossing", eventhelper_bunchCrossing);
  stream.select("edmEventHelper_info.event", eventhelper_event);
  stream.select("edmEventHelper_info.isRealData", eventhelper_isRealData);
  stream.select("edmEventHelper_info.luminosityBlock", eventhelper_luminosityBlock);
  stream.select("edmEventHelper_info.orbitNumber", eventhelper_orbitNumber);
  stream.select("edmEventHelper_info.run", eventhelper_run);
  stream.select("recoGenParticleHelper_genParticles.charge", genparticlehelper_charge);
  stream.select("recoGenParticleHelper_genParticles.eta", genparticlehelper_eta);
  stream.select("recoGenParticleHelper_genParticles.firstDaughter", genparticlehelper_firstDaughter);
  stream.select("recoGenParticleHelper_genParticles.firstMother", genparticlehelper_firstMother);
  stream.select("recoGenParticleHelper_genParticles.lastDaughter", genparticlehelper_lastDaughter);
  stream.select("recoGenParticleHelper_genParticles.lastMother", genparticlehelper_lastMother);
  stream.select("recoGenParticleHelper_genParticles.mass", genparticlehelper_mass);
  stream.select("recoGenParticleHelper_genParticles.pdgId", genparticlehelper_pdgId);
  stream.select("recoGenParticleHelper_genParticles.phi", genparticlehelper_phi);
  stream.select("recoGenParticleHelper_genParticles.pt", genparticlehelper_pt);
  stream.select("recoGenParticleHelper_genParticles.status", genparticlehelper_status);
  stream.select("GenRunInfoProduct_generator.crossSection", genruninfoproduct_crossSection);
  stream.select("GenRunInfoProduct_generator.filterEfficiency", genruninfoproduct_filterEfficiency);
  stream.select("GenRunInfoProduct_generator.internalXSec_value", genruninfoproduct_internalXSec_value);
  stream.select("recoGsfElectron_gsfElectrons.deltaEtaSuperClusterTrackAtVtx", gsfelectron_deltaEtaSuperClusterTrackAtVtx);
  stream.select("recoGsfElectron_gsfElectrons.deltaPhiSuperClusterTrackAtVtx", gsfelectron_deltaPhiSuperClusterTrackAtVtx);
  stream.select("recoGsfElectron_gsfElectrons.dr04EcalRecHitSumEt", gsfelectron_dr04EcalRecHitSumEt);
  stream.select("recoGsfElectron_gsfElectrons.dr04TkSumPt", gsfelectron_dr04TkSumPt);
  stream.select("recoGsfElectron_gsfElectrons.eSuperClusterOverP", gsfelectron_eSuperClusterOverP);
  stream.select("recoGsfElectron_gsfElectrons.energy", gsfelectron_energy);
  stream.select("recoGsfElectron_gsfElectrons.et", gsfelectron_et);
  stream.select("recoGsfElectron_gsfElectrons.eta", gsfelectron_eta);
  stream.select("recoGsfElectron_gsfElectrons.gsfTrack_d0", gsfelectron_gsfTrack_d0);
  stream.select("recoGsfElectron_gsfElectrons.gsfTrack_dxy", gsfelectron_gsfTrack_dxy);
  stream.select("recoGsfElectron_gsfElectrons.gsfTrack_dz", gsfelectron_gsfTrack_dz);
  stream.select("recoGsfElectron_gsfElectrons.hadronicOverEm", gsfelectron_hadronicOverEm);
  stream.select("recoGsfElectron_gsfElectrons.p", gsfelectron_p);
  stream.select("recoGsfElectron_gsfElectrons.phi", gsfelectron_phi);
  stream.select("recoGsfElectron_gsfElectrons.pt", gsfelectron_pt);
  stream.select("recoGsfElectron_gsfElectrons.px", gsfelectron_px);
  stream.select("recoGsfElectron_gsfElectrons.py", gsfelectron_py);
  stream.select("recoGsfElectron_gsfElectrons.pz", gsfelectron_pz);
  stream.select("recoGsfElectron_gsfElectrons.scE1x5", gsfelectron_scE1x5);
  stream.select("recoGsfElectron_gsfElectrons.scE2x5Max", gsfelectron_scE2x5Max);
  stream.select("recoGsfElectron_gsfElectrons.scE5x5", gsfelectron_scE5x5);
  stream.select("recoGsfElectron_gsfElectrons.sigmaIetaIeta", gsfelectron_sigmaIetaIeta);
  stream.select("patJet_selectedPatJets.HFEMEnergy", jet_HFEMEnergy);
  stream.select("patJet_selectedPatJets.HFEMEnergyFraction", jet_HFEMEnergyFraction);
  stream.select("patJet_selectedPatJets.HFEMMultiplicity", jet_HFEMMultiplicity);
  stream.select("patJet_selectedPatJets.HFHadronEnergy", jet_HFHadronEnergy);
  stream.select("patJet_selectedPatJets.HFHadronEnergyFraction", jet_HFHadronEnergyFraction);
  stream.select("patJet_selectedPatJets.HFHadronMultiplicity", jet_HFHadronMultiplicity);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedInclusiveSecondaryVertexBJetTags", jet_bDiscriminator_combinedInclusiveSecondaryVertexBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedMVABJetTags", jet_bDiscriminator_combinedMVABJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedSecondaryVertexBJetTags", jet_bDiscriminator_combinedSecondaryVertexBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_combinedSecondaryVertexMVABJetTags", jet_bDiscriminator_combinedSecondaryVertexMVABJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_impactParameterTagInfos", jet_bDiscriminator_impactParameterTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_inclusiveSecondaryVertexFinderTagInfos", jet_bDiscriminator_inclusiveSecondaryVertexFinderTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_jetBProbabilityBJetTags", jet_bDiscriminator_jetBProbabilityBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_jetProbabilityBJetTags", jet_bDiscriminator_jetProbabilityBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_negativeTrackCountingHighEffJetTags", jet_bDiscriminator_negativeTrackCountingHighEffJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_negativeTrackCountingHighPurJetTags", jet_bDiscriminator_negativeTrackCountingHighPurJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_secondaryVertexNegativeTagInfos", jet_bDiscriminator_secondaryVertexNegativeTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_secondaryVertexTagInfos", jet_bDiscriminator_secondaryVertexTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexHighEffBJetTags", jet_bDiscriminator_simpleSecondaryVertexHighEffBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexHighPurBJetTags", jet_bDiscriminator_simpleSecondaryVertexHighPurBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags", jet_bDiscriminator_simpleSecondaryVertexNegativeHighEffBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags", jet_bDiscriminator_simpleSecondaryVertexNegativeHighPurBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softElectronTagInfos", jet_bDiscriminator_softElectronTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonBJetTags", jet_bDiscriminator_softMuonBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonByIP3dBJetTags", jet_bDiscriminator_softMuonByIP3dBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonByPtBJetTags", jet_bDiscriminator_softMuonByPtBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_softMuonTagInfos", jet_bDiscriminator_softMuonTagInfos);
  stream.select("patJet_selectedPatJets.bDiscriminator_trackCountingHighEffBJetTags", jet_bDiscriminator_trackCountingHighEffBJetTags);
  stream.select("patJet_selectedPatJets.bDiscriminator_trackCountingHighPurBJetTags", jet_bDiscriminator_trackCountingHighPurBJetTags);
  stream.select("patJet_selectedPatJets.charge", jet_charge);
  stream.select("patJet_selectedPatJets.chargedEmEnergyFraction", jet_chargedEmEnergyFraction);
  stream.select("patJet_selectedPatJets.chargedHadronEnergyFraction", jet_chargedHadronEnergyFraction);
  stream.select("patJet_selectedPatJets.chargedHadronMultiplicity", jet_chargedHadronMultiplicity);
  stream.select("patJet_selectedPatJets.electronEnergy", jet_electronEnergy);
  stream.select("patJet_selectedPatJets.electronEnergyFraction", jet_electronEnergyFraction);
  stream.select("patJet_selectedPatJets.electronMultiplicity", jet_electronMultiplicity);
  stream.select("patJet_selectedPatJets.energy", jet_energy);
  stream.select("patJet_selectedPatJets.et", jet_et);
  stream.select("patJet_selectedPatJets.eta", jet_eta);
  stream.select("patJet_selectedPatJets.muonEnergy", jet_muonEnergy);
  stream.select("patJet_selectedPatJets.muonEnergyFraction", jet_muonEnergyFraction);
  stream.select("patJet_selectedPatJets.neutralEmEnergyFraction", jet_neutralEmEnergyFraction);
  stream.select("patJet_selectedPatJets.neutralHadronEnergy", jet_neutralHadronEnergy);
  stream.select("patJet_selectedPatJets.neutralHadronEnergyFraction", jet_neutralHadronEnergyFraction);
  stream.select("patJet_selectedPatJets.neutralHadronMultiplicity", jet_neutralHadronMultiplicity);
  stream.select("patJet_selectedPatJets.numberOfDaughters", jet_numberOfDaughters);
  stream.select("patJet_selectedPatJets.p", jet_p);
  stream.select("patJet_selectedPatJets.phi", jet_phi);
  stream.select("patJet_selectedPatJets.photonEnergy", jet_photonEnergy);
  stream.select("patJet_selectedPatJets.photonEnergyFraction", jet_photonEnergyFraction);
  stream.select("patJet_selectedPatJets.photonMultiplicity", jet_photonMultiplicity);
  stream.select("patJet_selectedPatJets.pt", jet_pt);
  stream.select("patJet_selectedPatJets.px", jet_px);
  stream.select("patJet_selectedPatJets.py", jet_py);
  stream.select("patJet_selectedPatJets.pz", jet_pz);
  stream.select("patMET_patMETs.energy", met_energy);
  stream.select("patMET_patMETs.et", met_et);
  stream.select("patMET_patMETs.eta", met_eta);
  stream.select("patMET_patMETs.p", met_p);
  stream.select("patMET_patMETs.phi", met_phi);
  stream.select("patMET_patMETs.pt", met_pt);
  stream.select("patMET_patMETs.px", met_px);
  stream.select("patMET_patMETs.py", met_py);
  stream.select("patMET_patMETs.pz", met_pz);
  stream.select("patMuon_patMuons.energy", muon_energy);
  stream.select("patMuon_patMuons.et", muon_et);
  stream.select("patMuon_patMuons.eta", muon_eta);
  stream.select("patMuon_patMuons.globalTrack_hitPattern_numberOfValidMuonHits", muon_globalTrack_hitPattern_numberOfValidMuonHits);
  stream.select("patMuon_patMuons.globalTrack_normalizedChi2", muon_globalTrack_normalizedChi2);
  stream.select("patMuon_patMuons.innerTrack_dxy", muon_innerTrack_dxy);
  stream.select("patMuon_patMuons.innerTrack_dz", muon_innerTrack_dz);
  stream.select("patMuon_patMuons.innerTrack_hitPattern_numberOfValidPixelHits", muon_innerTrack_hitPattern_numberOfValidPixelHits);
  stream.select("patMuon_patMuons.innerTrack_hitPattern_pixelLayersWithMeasurement", muon_innerTrack_hitPattern_pixelLayersWithMeasurement);
  stream.select("patMuon_patMuons.innerTrack_normalizedChi2", muon_innerTrack_normalizedChi2);
  stream.select("patMuon_patMuons.isGlobalMuon", muon_isGlobalMuon);
  stream.select("patMuon_patMuons.isPFMuon", muon_isPFMuon);
  stream.select("patMuon_patMuons.isTrackerMuon", muon_isTrackerMuon);
  stream.select("patMuon_patMuons.muonBestTrack_dxy", muon_muonBestTrack_dxy);
  stream.select("patMuon_patMuons.muonBestTrack_dz", muon_muonBestTrack_dz);
  stream.select("patMuon_patMuons.numberOfMatchedStations", muon_numberOfMatchedStations);
  stream.select("patMuon_patMuons.p", muon_p);
  stream.select("patMuon_patMuons.pfIsolationR03_sumChargedHadronPt", muon_pfIsolationR03_sumChargedHadronPt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumChargedParticlePt", muon_pfIsolationR03_sumChargedParticlePt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumNeutralHadronEt", muon_pfIsolationR03_sumNeutralHadronEt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumNeutralHadronEtHighThreshold", muon_pfIsolationR03_sumNeutralHadronEtHighThreshold);
  stream.select("patMuon_patMuons.pfIsolationR03_sumPUPt", muon_pfIsolationR03_sumPUPt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumPhotonEt", muon_pfIsolationR03_sumPhotonEt);
  stream.select("patMuon_patMuons.pfIsolationR03_sumPhotonEtHighThreshold", muon_pfIsolationR03_sumPhotonEtHighThreshold);
  stream.select("patMuon_patMuons.pfIsolationR04_sumChargedHadronPt", muon_pfIsolationR04_sumChargedHadronPt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumChargedParticlePt", muon_pfIsolationR04_sumChargedParticlePt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumNeutralHadronEt", muon_pfIsolationR04_sumNeutralHadronEt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumNeutralHadronEtHighThreshold", muon_pfIsolationR04_sumNeutralHadronEtHighThreshold);
  stream.select("patMuon_patMuons.pfIsolationR04_sumPUPt", muon_pfIsolationR04_sumPUPt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumPhotonEt", muon_pfIsolationR04_sumPhotonEt);
  stream.select("patMuon_patMuons.pfIsolationR04_sumPhotonEtHighThreshold", muon_pfIsolationR04_sumPhotonEtHighThreshold);
  stream.select("patMuon_patMuons.phi", muon_phi);
  stream.select("patMuon_patMuons.pt", muon_pt);
  stream.select("patMuon_patMuons.px", muon_px);
  stream.select("patMuon_patMuons.py", muon_py);
  stream.select("patMuon_patMuons.pz", muon_pz);
  stream.select("npatElectron_patElectrons", nelectron);
  stream.select("nrecoGenParticleHelper_genParticles", ngenparticlehelper);
  stream.select("nrecoGsfElectron_gsfElectrons", ngsfelectron);
  stream.select("npatJet_selectedPatJets", njet);
  stream.select("npatMET_patMETs", nmet);
  stream.select("npatMuon_patMuons", nmuon);
  stream.select("nrecoPFMET_pfType1CorrectedMet", npfmet);
  stream.select("nrecoPFMET_pfType1p2CorrectedMet", npfmet2);
  stream.select("nPileupSummaryInfo_addPileupInfo", npileupsummaryinfo);
  stream.select("npatTauHelper_patTaus", ntau);
  stream.select("nrecoVertex_offlinePrimaryVertices", nvertex);
  stream.select("recoPFMET_pfType1p2CorrectedMet.energy", pfmet2_energy);
  stream.select("recoPFMET_pfType1p2CorrectedMet.et", pfmet2_et);
  stream.select("recoPFMET_pfType1p2CorrectedMet.eta", pfmet2_eta);
  stream.select("recoPFMET_pfType1p2CorrectedMet.p", pfmet2_p);
  stream.select("recoPFMET_pfType1p2CorrectedMet.phi", pfmet2_phi);
  stream.select("recoPFMET_pfType1p2CorrectedMet.pt", pfmet2_pt);
  stream.select("recoPFMET_pfType1p2CorrectedMet.px", pfmet2_px);
  stream.select("recoPFMET_pfType1p2CorrectedMet.py", pfmet2_py);
  stream.select("recoPFMET_pfType1p2CorrectedMet.pz", pfmet2_pz);
  stream.select("recoPFMET_pfType1CorrectedMet.energy", pfmet_energy);
  stream.select("recoPFMET_pfType1CorrectedMet.et", pfmet_et);
  stream.select("recoPFMET_pfType1CorrectedMet.eta", pfmet_eta);
  stream.select("recoPFMET_pfType1CorrectedMet.p", pfmet_p);
  stream.select("recoPFMET_pfType1CorrectedMet.phi", pfmet_phi);
  stream.select("recoPFMET_pfType1CorrectedMet.pt", pfmet_pt);
  stream.select("recoPFMET_pfType1CorrectedMet.px", pfmet_px);
  stream.select("recoPFMET_pfType1CorrectedMet.py", pfmet_py);
  stream.select("recoPFMET_pfType1CorrectedMet.pz", pfmet_pz);
  stream.select("PileupSummaryInfo_addPileupInfo.getBunchCrossing", pileupsummaryinfo_getBunchCrossing);
  stream.select("PileupSummaryInfo_addPileupInfo.getPU_NumInteractions", pileupsummaryinfo_getPU_NumInteractions);
  stream.select("patTauHelper_patTaus.charge", tau_charge);
  stream.select("patTauHelper_patTaus.energy", tau_energy);
  stream.select("patTauHelper_patTaus.et", tau_et);
  stream.select("patTauHelper_patTaus.eta", tau_eta);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_energy", tau_leadPFChargedHadrCand_energy);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_et", tau_leadPFChargedHadrCand_et);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_eta", tau_leadPFChargedHadrCand_eta);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_mass", tau_leadPFChargedHadrCand_mass);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_massSqr", tau_leadPFChargedHadrCand_massSqr);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_mt", tau_leadPFChargedHadrCand_mt);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_mtSqr", tau_leadPFChargedHadrCand_mtSqr);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_p", tau_leadPFChargedHadrCand_p);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_phi", tau_leadPFChargedHadrCand_phi);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_pt", tau_leadPFChargedHadrCand_pt);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_px", tau_leadPFChargedHadrCand_px);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_py", tau_leadPFChargedHadrCand_py);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_pz", tau_leadPFChargedHadrCand_pz);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_rapidity", tau_leadPFChargedHadrCand_rapidity);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_theta", tau_leadPFChargedHadrCand_theta);
  stream.select("patTauHelper_patTaus.leadPFChargedHadrCand_y", tau_leadPFChargedHadrCand_y);
  stream.select("patTauHelper_patTaus.p", tau_p);
  stream.select("patTauHelper_patTaus.phi", tau_phi);
  stream.select("patTauHelper_patTaus.pt", tau_pt);
  stream.select("patTauHelper_patTaus.px", tau_px);
  stream.select("patTauHelper_patTaus.py", tau_py);
  stream.select("patTauHelper_patTaus.pz", tau_pz);
  stream.select("patTauHelper_patTaus.signalPFChargedHadrCands_size", tau_signalPFChargedHadrCands_size);
  stream.select("patTauHelper_patTaus.tauID_againstElectronDeadECAL", tau_tauID_againstElectronDeadECAL);
  stream.select("patTauHelper_patTaus.tauID_againstElectronLoose", tau_tauID_againstElectronLoose);
  stream.select("patTauHelper_patTaus.tauID_againstElectronLooseMVA2", tau_tauID_againstElectronLooseMVA2);
  stream.select("patTauHelper_patTaus.tauID_againstElectronLooseMVA3", tau_tauID_againstElectronLooseMVA3);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMVA", tau_tauID_againstElectronMVA);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMVA2category", tau_tauID_againstElectronMVA2category);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMVA2raw", tau_tauID_againstElectronMVA2raw);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMVA3category", tau_tauID_againstElectronMVA3category);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMVA3raw", tau_tauID_againstElectronMVA3raw);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMedium", tau_tauID_againstElectronMedium);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMediumMVA2", tau_tauID_againstElectronMediumMVA2);
  stream.select("patTauHelper_patTaus.tauID_againstElectronMediumMVA3", tau_tauID_againstElectronMediumMVA3);
  stream.select("patTauHelper_patTaus.tauID_againstElectronTight", tau_tauID_againstElectronTight);
  stream.select("patTauHelper_patTaus.tauID_againstElectronTightMVA2", tau_tauID_againstElectronTightMVA2);
  stream.select("patTauHelper_patTaus.tauID_againstElectronTightMVA3", tau_tauID_againstElectronTightMVA3);
  stream.select("patTauHelper_patTaus.tauID_againstElectronVLooseMVA2", tau_tauID_againstElectronVLooseMVA2);
  stream.select("patTauHelper_patTaus.tauID_againstElectronVTightMVA3", tau_tauID_againstElectronVTightMVA3);
  stream.select("patTauHelper_patTaus.tauID_againstMuonLoose", tau_tauID_againstMuonLoose);
  stream.select("patTauHelper_patTaus.tauID_againstMuonLoose2", tau_tauID_againstMuonLoose2);
  stream.select("patTauHelper_patTaus.tauID_againstMuonMedium", tau_tauID_againstMuonMedium);
  stream.select("patTauHelper_patTaus.tauID_againstMuonMedium2", tau_tauID_againstMuonMedium2);
  stream.select("patTauHelper_patTaus.tauID_againstMuonTight", tau_tauID_againstMuonTight);
  stream.select("patTauHelper_patTaus.tauID_againstMuonTight2", tau_tauID_againstMuonTight2);
  stream.select("patTauHelper_patTaus.tauID_byCombinedIsolationDeltaBetaCorrRaw", tau_tauID_byCombinedIsolationDeltaBetaCorrRaw);
  stream.select("patTauHelper_patTaus.tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits", tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits);
  stream.select("patTauHelper_patTaus.tauID_byIsolationMVA2raw", tau_tauID_byIsolationMVA2raw);
  stream.select("patTauHelper_patTaus.tauID_byIsolationMVAraw", tau_tauID_byIsolationMVAraw);
  stream.select("patTauHelper_patTaus.tauID_byLooseCombinedIsolationDeltaBetaCorr", tau_tauID_byLooseCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits", tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolation", tau_tauID_byLooseIsolation);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolationDeltaBetaCorr", tau_tauID_byLooseIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolationMVA", tau_tauID_byLooseIsolationMVA);
  stream.select("patTauHelper_patTaus.tauID_byLooseIsolationMVA2", tau_tauID_byLooseIsolationMVA2);
  stream.select("patTauHelper_patTaus.tauID_byMediumCombinedIsolationDeltaBetaCorr", tau_tauID_byMediumCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits", tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolation", tau_tauID_byMediumIsolation);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolationDeltaBetaCorr", tau_tauID_byMediumIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolationMVA", tau_tauID_byMediumIsolationMVA);
  stream.select("patTauHelper_patTaus.tauID_byMediumIsolationMVA2", tau_tauID_byMediumIsolationMVA2);
  stream.select("patTauHelper_patTaus.tauID_byTightCombinedIsolationDeltaBetaCorr", tau_tauID_byTightCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byTightCombinedIsolationDeltaBetaCorr3Hits", tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolation", tau_tauID_byTightIsolation);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolationDeltaBetaCorr", tau_tauID_byTightIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolationMVA", tau_tauID_byTightIsolationMVA);
  stream.select("patTauHelper_patTaus.tauID_byTightIsolationMVA2", tau_tauID_byTightIsolationMVA2);
  stream.select("patTauHelper_patTaus.tauID_byVLooseCombinedIsolationDeltaBetaCorr", tau_tauID_byVLooseCombinedIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_byVLooseIsolation", tau_tauID_byVLooseIsolation);
  stream.select("patTauHelper_patTaus.tauID_byVLooseIsolationDeltaBetaCorr", tau_tauID_byVLooseIsolationDeltaBetaCorr);
  stream.select("patTauHelper_patTaus.tauID_decayModeFinding", tau_tauID_decayModeFinding);
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
  stream.select("recoVertex_offlinePrimaryVertices.isFake", vertex_isFake);
  stream.select("recoVertex_offlinePrimaryVertices.ndof", vertex_ndof);
  stream.select("recoVertex_offlinePrimaryVertices.x", vertex_x);
  stream.select("recoVertex_offlinePrimaryVertices.y", vertex_y);
  stream.select("recoVertex_offlinePrimaryVertices.z", vertex_z);

}
//-----------------------------------------------------------------------------
// -- Utilities
//-----------------------------------------------------------------------------
void
error(std::string message)
{
  std::cout << "** error ** " << message << std::endl;
  exit(0);
}

std::string 
strip(std::string line)
{
  int l = line.size();
  if ( l == 0 ) return std::string("");
  int n = 0;
  while (((line[n] == 0)    ||
	  (line[n] == ' ' ) ||
	  (line[n] == '\n') ||
	  (line[n] == '\t')) && n < l) n++;

  int m = l-1;
  while (((line[m] == 0)    ||
	  (line[m] == ' ')  ||
	  (line[m] == '\n') ||
	  (line[m] == '\t')) && m > 0) m--;
  return line.substr(n,m-n+1);
}

std::string
nameonly(std::string filename)
{
  int i = filename.rfind("/");
  int j = filename.rfind(".");
  if ( j < 0 ) j = filename.size();
  return filename.substr(i+1,j-i-1);
}
//-----------------------------------------------------------------------------
struct outputFile
{
  outputFile(std::string filename)
   : filename_(filename),
	 file_(new TFile(filename_.c_str(), "recreate")),
	 tree_(0),
	 b_weight_(0),
	 entry_(0),
	 SAVECOUNT_(50000)
  {
	file_->cd();
	hist_ = new TH1F("counts", "", 1,0,1);
	hist_->SetBit(TH1::kCanRebin);
	hist_->SetStats(0);
  }

  outputFile(std::string filename, itreestream& stream, int savecount=50000) 
   : filename_(filename),
	 file_(new TFile(filename.c_str(), "recreate")),
	 tree_(stream.tree()->CloneTree(0)),
	 b_weight_(tree_->Branch("eventWeight", &weight_, "eventWeight/D")),
	 entry_(0),
	 SAVECOUNT_(savecount)
  {
	std::cout << "events will be skimmed to file "
			  << filename_ << std::endl;
	file_->cd();
	hist_ = new TH1F("counts", "", 1,0,1);
	hist_->SetBit(TH1::kCanRebin);
	hist_->SetStats(0);
  }

  void addEvent(double weight=1)
  {
    if ( tree_ == 0 ) return;
	
    weight_ = weight;
	file_   = tree_->GetCurrentFile();
	file_->cd();
	tree_->Fill();

	entry_++;
	if ( entry_ % SAVECOUNT_ == 0 )
	  tree_->AutoSave("SaveSelf");
  }

  void count(std::string cond, double w=1)
  {
    hist_->Fill(cond.c_str(), w);
  }
  
  void close()
  {
  	std::cout << "==> histograms saved to file " << filename_ << std::endl;
    if ( tree_ != 0 )
	  {
	    std::cout << "==> events skimmed to file " << filename_ << std::endl;
	    file_ = tree_->GetCurrentFile();
	  }
	file_->cd();
	//file_->Write("", TObject::kWriteDelete);
	file_->Write();
	file_->ls();
	file_->Close();
  }

  std::string filename_;  
  TFile* file_;
  TTree* tree_;
  TH1F*  hist_;
  TBranch* b_weight_;
  double     weight_;
  int    entry_;
  int    SAVECOUNT_;
};

struct commandLine
{
  std::string progname;
  std::string filelist;
  std::string outputfilename;
};


void
decodeCommandLine(int argc, char** argv, commandLine& cl)
{
  cl.progname = std::string(argv[0]);

  // 1st (optional) argument
  if ( argc > 1 )
	cl.filelist = std::string(argv[1]);
  else
	cl.filelist = std::string("filelist.txt");

  // 2nd (optional) command line argument
  if ( argc > 2 ) 
	cl.outputfilename = std::string(argv[2]);
  else
	cl.outputfilename = cl.progname + std::string("_histograms");

  // Make sure extension is ".root"
  std::string name = cl.outputfilename;
  if ( name.substr(name.size()-5, 5) != std::string(".root") )
    cl.outputfilename += std::string(".root");
}

// Read ntuple filenames from file list

std::vector<std::string>
getFilenames(std::string filelist)
{
  std::ifstream stream(filelist.c_str());
  if ( !stream.good() ) error("unable to open file: " + filelist);

  // Get list of ntuple files to be processed

  std::vector<std::string> v;
  std::string filename;
  while ( stream >> filename )
	if ( strip(filename) != "" ) v.push_back(filename);
  return v;
}

double deltaPhi	( double phi1, double phi2)
{
    double result = phi1 - phi2;
    while (result > M_PI) result -= 2*M_PI;
    while (result <= -M_PI) result += 2*M_PI;
    return result;
}

double deltaR(double eta1, double phi1, double eta2, double phi2)
{
   double deta = eta1 - eta2;
   double dphi = deltaPhi(phi1, phi2);
    return sqrt(deta*deta + dphi*dphi);
}

#endif
