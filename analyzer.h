#ifndef ANALYZER_H
#define ANALYZER_H
//-----------------------------------------------------------------------------
// File:        analyzer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Thu Oct 22 17:50:37 2015 by mkanalyzer.py
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
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"

namespace evt {
//-----------------------------------------------------------------------------
// --- Declare variables
//-----------------------------------------------------------------------------
double	BeamSpot_x0;
double	BeamSpot_y0;
double	BeamSpot_z0;
std::vector<int>	GenParticleHelper_charge(200,0);
std::vector<double>	GenParticleHelper_energy(200,0);
std::vector<float>	GenParticleHelper_eta(200,0);
std::vector<int>	GenParticleHelper_firstDaughter(200,0);
std::vector<int>	GenParticleHelper_firstMother(200,0);
std::vector<int>	GenParticleHelper_lastDaughter(200,0);
std::vector<int>	GenParticleHelper_lastMother(200,0);
std::vector<float>	GenParticleHelper_mass(200,0);
std::vector<int>	GenParticleHelper_pdgId(200,0);
std::vector<float>	GenParticleHelper_phi(200,0);
std::vector<float>	GenParticleHelper_pt(200,0);
std::vector<int>	GenParticleHelper_status(200,0);
std::vector<int>	PileupSummaryInfo_getBunchCrossing(10,0);
std::vector<int>	PileupSummaryInfo_getPU_NumInteractions(10,0);
std::vector<float>	PileupSummaryInfo_getTrueNumInteractions(10,0);
int	edmEventHelper_bunchCrossing;
int	edmEventHelper_event;
int	edmEventHelper_isRealData;
int	edmEventHelper_luminosityBlock;
int	edmEventHelper_orbitNumber;
int	edmEventHelper_run;
std::vector<float>	electron_caloIso(200,0);
std::vector<int>	electron_charge(200,0);
std::vector<float>	electron_deltaEtaSuperClusterTrackAtVtx(200,0);
std::vector<float>	electron_deltaPhiSuperClusterTrackAtVtx(200,0);
std::vector<float>	electron_dr04EcalRecHitSumEt(200,0);
std::vector<float>	electron_dr04TkSumPt(200,0);
std::vector<float>	electron_eSuperClusterOverP(200,0);
std::vector<float>	electron_ecalIso(200,0);
std::vector<double>	electron_energy(200,0);
std::vector<double>	electron_et(200,0);
std::vector<float>	electron_eta(200,0);
std::vector<double>	electron_gsfTrack_d0(200,0);
std::vector<double>	electron_gsfTrack_dxy(200,0);
std::vector<double>	electron_gsfTrack_dz(200,0);
std::vector<float>	electron_hadronicOverEm(200,0);
std::vector<float>	electron_hcalIso(200,0);
std::vector<int>	electron_isPF(200,0);
std::vector<double>	electron_p(200,0);
std::vector<float>	electron_phi(200,0);
std::vector<float>	electron_pt(200,0);
std::vector<double>	electron_px(200,0);
std::vector<double>	electron_py(200,0);
std::vector<double>	electron_pz(200,0);
std::vector<float>	electron_scE1x5(200,0);
std::vector<float>	electron_scE2x5Max(200,0);
std::vector<float>	electron_scE5x5(200,0);
std::vector<float>	electron_trackIso(200,0);
std::vector<float>	jet_HFEMEnergy(200,0);
std::vector<float>	jet_HFEMEnergyFraction(200,0);
std::vector<int>	jet_HFEMMultiplicity(200,0);
std::vector<float>	jet_HFHadronEnergy(200,0);
std::vector<float>	jet_HFHadronEnergyFraction(200,0);
std::vector<int>	jet_HFHadronMultiplicity(200,0);
std::vector<int>	jet_charge(200,0);
std::vector<float>	jet_chargedEmEnergyFraction(200,0);
std::vector<float>	jet_chargedHadronEnergyFraction(200,0);
std::vector<int>	jet_chargedHadronMultiplicity(200,0);
std::vector<float>	jet_chargedMuEnergy(200,0);
std::vector<float>	jet_chargedMuEnergyFraction(200,0);
std::vector<float>	jet_electronEnergy(200,0);
std::vector<float>	jet_electronEnergyFraction(200,0);
std::vector<int>	jet_electronMultiplicity(200,0);
std::vector<double>	jet_energy(200,0);
std::vector<double>	jet_et(200,0);
std::vector<float>	jet_eta(200,0);
std::vector<int>	jet_hadronFlavour(200,0);
std::vector<float>	jet_muonEnergy(200,0);
std::vector<float>	jet_muonEnergyFraction(200,0);
std::vector<float>	jet_neutralEmEnergyFraction(200,0);
std::vector<float>	jet_neutralHadronEnergy(200,0);
std::vector<float>	jet_neutralHadronEnergyFraction(200,0);
std::vector<int>	jet_neutralHadronMultiplicity(200,0);
std::vector<int>	jet_neutralMultiplicity(200,0);
std::vector<size_t>	jet_numberOfDaughters(200,0);
std::vector<double>	jet_p(200,0);
std::vector<int>	jet_partonFlavour(200,0);
std::vector<float>	jet_phi(200,0);
std::vector<float>	jet_photonEnergy(200,0);
std::vector<float>	jet_photonEnergyFraction(200,0);
std::vector<int>	jet_photonMultiplicity(200,0);
std::vector<float>	jet_pt(200,0);
std::vector<double>	jet_px(200,0);
std::vector<double>	jet_py(200,0);
std::vector<double>	jet_pz(200,0);
std::vector<double>	met2_energy(200,0);
std::vector<double>	met2_et(200,0);
std::vector<float>	met2_eta(200,0);
std::vector<double>	met2_p(200,0);
std::vector<float>	met2_phi(200,0);
std::vector<float>	met2_pt(200,0);
std::vector<double>	met2_px(200,0);
std::vector<double>	met2_py(200,0);
std::vector<double>	met2_pz(200,0);
std::vector<int>	muon_charge(200,0);
std::vector<double>	muon_energy(200,0);
std::vector<double>	muon_et(200,0);
std::vector<float>	muon_eta(200,0);
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
std::vector<float>	muon_phi(200,0);
std::vector<float>	muon_pt(200,0);
std::vector<double>	muon_px(200,0);
std::vector<double>	muon_py(200,0);
std::vector<double>	muon_pz(200,0);
int	nGenParticleHelper;
int	nPileupSummaryInfo;
int	nelectron;
int	njet;
int	nmet2;
int	nmuon;
int	ntau;
std::vector<size_t>	ntau_signalChargedHadrCands(200,0);
int	nvertex;
std::vector<int>	tau_charge(200,0);
std::vector<double>	tau_energy(200,0);
std::vector<double>	tau_et(200,0);
std::vector<float>	tau_eta(200,0);
std::vector<double>	tau_leadChargedHadrCand_energy(200,0);
std::vector<double>	tau_leadChargedHadrCand_et(200,0);
std::vector<float>	tau_leadChargedHadrCand_eta(200,0);
std::vector<float>	tau_leadChargedHadrCand_mass(200,0);
std::vector<float>	tau_leadChargedHadrCand_massSqr(200,0);
std::vector<double>	tau_leadChargedHadrCand_mt(200,0);
std::vector<double>	tau_leadChargedHadrCand_mtSqr(200,0);
std::vector<double>	tau_leadChargedHadrCand_p(200,0);
std::vector<float>	tau_leadChargedHadrCand_phi(200,0);
std::vector<float>	tau_leadChargedHadrCand_pt(200,0);
std::vector<double>	tau_leadChargedHadrCand_px(200,0);
std::vector<double>	tau_leadChargedHadrCand_py(200,0);
std::vector<double>	tau_leadChargedHadrCand_pz(200,0);
std::vector<double>	tau_leadChargedHadrCand_rapidity(200,0);
std::vector<double>	tau_leadChargedHadrCand_theta(200,0);
std::vector<double>	tau_leadChargedHadrCand_y(200,0);
std::vector<float>	tau_mass(200,0);
std::vector<double>	tau_p(200,0);
std::vector<float>	tau_phi(200,0);
std::vector<float>	tau_pt(200,0);
std::vector<double>	tau_px(200,0);
std::vector<double>	tau_py(200,0);
std::vector<double>	tau_pz(200,0);
std::vector<float>	tau_tauID_againstElectronLoose(200,0);
std::vector<float>	tau_tauID_againstElectronLooseMVA5(200,0);
std::vector<float>	tau_tauID_againstElectronMVA5category(200,0);
std::vector<float>	tau_tauID_againstElectronMVA5raw(200,0);
std::vector<float>	tau_tauID_againstElectronMedium(200,0);
std::vector<float>	tau_tauID_againstElectronMediumMVA5(200,0);
std::vector<float>	tau_tauID_againstElectronTight(200,0);
std::vector<float>	tau_tauID_againstElectronTightMVA5(200,0);
std::vector<float>	tau_tauID_againstElectronVLooseMVA5(200,0);
std::vector<float>	tau_tauID_againstElectronVTightMVA5(200,0);
std::vector<float>	tau_tauID_againstMuonLoose(200,0);
std::vector<float>	tau_tauID_againstMuonLoose2(200,0);
std::vector<float>	tau_tauID_againstMuonLoose3(200,0);
std::vector<float>	tau_tauID_againstMuonLooseMVA(200,0);
std::vector<float>	tau_tauID_againstMuonMVAraw(200,0);
std::vector<float>	tau_tauID_againstMuonMedium(200,0);
std::vector<float>	tau_tauID_againstMuonMedium2(200,0);
std::vector<float>	tau_tauID_againstMuonMediumMVA(200,0);
std::vector<float>	tau_tauID_againstMuonTight(200,0);
std::vector<float>	tau_tauID_againstMuonTight2(200,0);
std::vector<float>	tau_tauID_againstMuonTight3(200,0);
std::vector<float>	tau_tauID_againstMuonTightMVA(200,0);
std::vector<float>	tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits(200,0);
std::vector<float>	tau_tauID_byIsolationMVA3newDMwLTraw(200,0);
std::vector<float>	tau_tauID_byIsolationMVA3newDMwoLTraw(200,0);
std::vector<float>	tau_tauID_byIsolationMVA3oldDMwLTraw(200,0);
std::vector<float>	tau_tauID_byIsolationMVA3oldDMwoLTraw(200,0);
std::vector<float>	tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	tau_tauID_byLooseIsolationMVA3newDMwLT(200,0);
std::vector<float>	tau_tauID_byLooseIsolationMVA3newDMwoLT(200,0);
std::vector<float>	tau_tauID_byLooseIsolationMVA3oldDMwLT(200,0);
std::vector<float>	tau_tauID_byLooseIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	tau_tauID_byMediumIsolationMVA3newDMwLT(200,0);
std::vector<float>	tau_tauID_byMediumIsolationMVA3newDMwoLT(200,0);
std::vector<float>	tau_tauID_byMediumIsolationMVA3oldDMwLT(200,0);
std::vector<float>	tau_tauID_byMediumIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits(200,0);
std::vector<float>	tau_tauID_byTightIsolationMVA3newDMwLT(200,0);
std::vector<float>	tau_tauID_byTightIsolationMVA3newDMwoLT(200,0);
std::vector<float>	tau_tauID_byTightIsolationMVA3oldDMwLT(200,0);
std::vector<float>	tau_tauID_byTightIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	tau_tauID_byVLooseIsolationMVA3newDMwLT(200,0);
std::vector<float>	tau_tauID_byVLooseIsolationMVA3newDMwoLT(200,0);
std::vector<float>	tau_tauID_byVLooseIsolationMVA3oldDMwLT(200,0);
std::vector<float>	tau_tauID_byVLooseIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	tau_tauID_byVTightIsolationMVA3newDMwLT(200,0);
std::vector<float>	tau_tauID_byVTightIsolationMVA3newDMwoLT(200,0);
std::vector<float>	tau_tauID_byVTightIsolationMVA3oldDMwLT(200,0);
std::vector<float>	tau_tauID_byVTightIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	tau_tauID_byVVTightIsolationMVA3newDMwLT(200,0);
std::vector<float>	tau_tauID_byVVTightIsolationMVA3newDMwoLT(200,0);
std::vector<float>	tau_tauID_byVVTightIsolationMVA3oldDMwLT(200,0);
std::vector<float>	tau_tauID_byVVTightIsolationMVA3oldDMwoLT(200,0);
std::vector<float>	tau_tauID_chargedIsoPtSum(200,0);
std::vector<float>	tau_tauID_decayModeFinding(200,0);
std::vector<float>	tau_tauID_decayModeFindingNewDMs(200,0);
std::vector<float>	tau_tauID_neutralIsoPtSum(200,0);
std::vector<float>	tau_tauID_puCorrPtSum(200,0);
std::vector<double>	vertex_chi2(200,0);
std::vector<int>	vertex_isFake(200,0);
std::vector<int>	vertex_isValid(200,0);
std::vector<double>	vertex_ndof(200,0);
std::vector<double>	vertex_x(200,0);
std::vector<double>	vertex_y(200,0);
std::vector<double>	vertex_z(200,0);

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
struct GenParticleHelper_s
{
  int	charge;
  int	pdgId;
  int	status;
  double	energy;
  float	pt;
  float	phi;
  float	eta;
  float	mass;
  int	firstMother;
  int	lastMother;
  int	firstDaughter;
  int	lastDaughter;
};
std::vector<GenParticleHelper_s> GenParticleHelper(200);

std::ostream& operator<<(std::ostream& os, const GenParticleHelper_s& o)
{
  char r[1024];
  os << "GenParticleHelper" << std::endl;
  sprintf(r, "  %-32s: %f\n", "charge", (double)o.charge); os << r;
  sprintf(r, "  %-32s: %f\n", "pdgId", (double)o.pdgId); os << r;
  sprintf(r, "  %-32s: %f\n", "status", (double)o.status); os << r;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "firstMother", (double)o.firstMother); os << r;
  sprintf(r, "  %-32s: %f\n", "lastMother", (double)o.lastMother); os << r;
  sprintf(r, "  %-32s: %f\n", "firstDaughter", (double)o.firstDaughter); os << r;
  sprintf(r, "  %-32s: %f\n", "lastDaughter", (double)o.lastDaughter); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct PileupSummaryInfo_s
{
  int	getBunchCrossing;
  int	getPU_NumInteractions;
  float	getTrueNumInteractions;
};
std::vector<PileupSummaryInfo_s> PileupSummaryInfo(10);

std::ostream& operator<<(std::ostream& os, const PileupSummaryInfo_s& o)
{
  char r[1024];
  os << "PileupSummaryInfo" << std::endl;
  sprintf(r, "  %-32s: %f\n", "getBunchCrossing", (double)o.getBunchCrossing); os << r;
  sprintf(r, "  %-32s: %f\n", "getPU_NumInteractions", (double)o.getPU_NumInteractions); os << r;
  sprintf(r, "  %-32s: %f\n", "getTrueNumInteractions", (double)o.getTrueNumInteractions); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct electron_s
{
  int	charge;
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  float	pt;
  float	phi;
  float	eta;
  float	trackIso;
  float	ecalIso;
  float	hcalIso;
  float	caloIso;
  int	isPF;
  float	eSuperClusterOverP;
  float	deltaEtaSuperClusterTrackAtVtx;
  float	deltaPhiSuperClusterTrackAtVtx;
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
  sprintf(r, "  %-32s: %f\n", "trackIso", (double)o.trackIso); os << r;
  sprintf(r, "  %-32s: %f\n", "ecalIso", (double)o.ecalIso); os << r;
  sprintf(r, "  %-32s: %f\n", "hcalIso", (double)o.hcalIso); os << r;
  sprintf(r, "  %-32s: %f\n", "caloIso", (double)o.caloIso); os << r;
  sprintf(r, "  %-32s: %f\n", "isPF", (double)o.isPF); os << r;
  sprintf(r, "  %-32s: %f\n", "eSuperClusterOverP", (double)o.eSuperClusterOverP); os << r;
  sprintf(r, "  %-32s: %f\n", "deltaEtaSuperClusterTrackAtVtx", (double)o.deltaEtaSuperClusterTrackAtVtx); os << r;
  sprintf(r, "  %-32s: %f\n", "deltaPhiSuperClusterTrackAtVtx", (double)o.deltaPhiSuperClusterTrackAtVtx); os << r;
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
  float	pt;
  float	phi;
  float	eta;
  int	partonFlavour;
  int	hadronFlavour;
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
  float	chargedMuEnergy;
  float	chargedMuEnergyFraction;
  int	neutralMultiplicity;
  size_t	numberOfDaughters;
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
  sprintf(r, "  %-32s: %f\n", "partonFlavour", (double)o.partonFlavour); os << r;
  sprintf(r, "  %-32s: %f\n", "hadronFlavour", (double)o.hadronFlavour); os << r;
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
  sprintf(r, "  %-32s: %f\n", "chargedMuEnergy", (double)o.chargedMuEnergy); os << r;
  sprintf(r, "  %-32s: %f\n", "chargedMuEnergyFraction", (double)o.chargedMuEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "neutralMultiplicity", (double)o.neutralMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "numberOfDaughters", (double)o.numberOfDaughters); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct met2_s
{
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  float	pt;
  float	phi;
  float	eta;
};
std::vector<met2_s> met2(200);

std::ostream& operator<<(std::ostream& os, const met2_s& o)
{
  char r[1024];
  os << "met2" << std::endl;
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
  int	charge;
  double	p;
  double	energy;
  double	et;
  double	px;
  double	py;
  double	pz;
  float	pt;
  float	phi;
  float	eta;
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
  float	pt;
  float	phi;
  float	eta;
  float	mass;
  double	leadChargedHadrCand_p;
  double	leadChargedHadrCand_energy;
  double	leadChargedHadrCand_et;
  float	leadChargedHadrCand_mass;
  float	leadChargedHadrCand_massSqr;
  double	leadChargedHadrCand_mt;
  double	leadChargedHadrCand_mtSqr;
  double	leadChargedHadrCand_px;
  double	leadChargedHadrCand_py;
  double	leadChargedHadrCand_pz;
  float	leadChargedHadrCand_pt;
  float	leadChargedHadrCand_phi;
  double	leadChargedHadrCand_theta;
  float	leadChargedHadrCand_eta;
  double	leadChargedHadrCand_rapidity;
  double	leadChargedHadrCand_y;
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
  float	tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits;
  float	tauID_byIsolationMVA3newDMwLTraw;
  float	tauID_byIsolationMVA3newDMwoLTraw;
  float	tauID_byIsolationMVA3oldDMwLTraw;
  float	tauID_byIsolationMVA3oldDMwoLTraw;
  float	tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byLooseIsolationMVA3newDMwLT;
  float	tauID_byLooseIsolationMVA3newDMwoLT;
  float	tauID_byLooseIsolationMVA3oldDMwLT;
  float	tauID_byLooseIsolationMVA3oldDMwoLT;
  float	tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byMediumIsolationMVA3newDMwLT;
  float	tauID_byMediumIsolationMVA3newDMwoLT;
  float	tauID_byMediumIsolationMVA3oldDMwLT;
  float	tauID_byMediumIsolationMVA3oldDMwoLT;
  float	tauID_byTightCombinedIsolationDeltaBetaCorr3Hits;
  float	tauID_byTightIsolationMVA3newDMwLT;
  float	tauID_byTightIsolationMVA3newDMwoLT;
  float	tauID_byTightIsolationMVA3oldDMwLT;
  float	tauID_byTightIsolationMVA3oldDMwoLT;
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
  float	tauID_neutralIsoPtSum;
  float	tauID_puCorrPtSum;
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
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_p", (double)o.leadChargedHadrCand_p); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_energy", (double)o.leadChargedHadrCand_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_et", (double)o.leadChargedHadrCand_et); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_mass", (double)o.leadChargedHadrCand_mass); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_massSqr", (double)o.leadChargedHadrCand_massSqr); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_mt", (double)o.leadChargedHadrCand_mt); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_mtSqr", (double)o.leadChargedHadrCand_mtSqr); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_px", (double)o.leadChargedHadrCand_px); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_py", (double)o.leadChargedHadrCand_py); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_pz", (double)o.leadChargedHadrCand_pz); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_pt", (double)o.leadChargedHadrCand_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_phi", (double)o.leadChargedHadrCand_phi); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_theta", (double)o.leadChargedHadrCand_theta); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_eta", (double)o.leadChargedHadrCand_eta); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_rapidity", (double)o.leadChargedHadrCand_rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "leadChargedHadrCand_y", (double)o.leadChargedHadrCand_y); os << r;
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
  sprintf(r, "  %-32s: %f\n", "tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits", (double)o.tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3newDMwLTraw", (double)o.tauID_byIsolationMVA3newDMwLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3newDMwoLTraw", (double)o.tauID_byIsolationMVA3newDMwoLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3oldDMwLTraw", (double)o.tauID_byIsolationMVA3oldDMwLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byIsolationMVA3oldDMwoLTraw", (double)o.tauID_byIsolationMVA3oldDMwoLTraw); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3newDMwLT", (double)o.tauID_byLooseIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3newDMwoLT", (double)o.tauID_byLooseIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3oldDMwLT", (double)o.tauID_byLooseIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byLooseIsolationMVA3oldDMwoLT", (double)o.tauID_byLooseIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3newDMwLT", (double)o.tauID_byMediumIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3newDMwoLT", (double)o.tauID_byMediumIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3oldDMwLT", (double)o.tauID_byMediumIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byMediumIsolationMVA3oldDMwoLT", (double)o.tauID_byMediumIsolationMVA3oldDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightCombinedIsolationDeltaBetaCorr3Hits", (double)o.tauID_byTightCombinedIsolationDeltaBetaCorr3Hits); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3newDMwLT", (double)o.tauID_byTightIsolationMVA3newDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3newDMwoLT", (double)o.tauID_byTightIsolationMVA3newDMwoLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3oldDMwLT", (double)o.tauID_byTightIsolationMVA3oldDMwLT); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_byTightIsolationMVA3oldDMwoLT", (double)o.tauID_byTightIsolationMVA3oldDMwoLT); os << r;
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
  sprintf(r, "  %-32s: %f\n", "tauID_neutralIsoPtSum", (double)o.tauID_neutralIsoPtSum); os << r;
  sprintf(r, "  %-32s: %f\n", "tauID_puCorrPtSum", (double)o.tauID_puCorrPtSum); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct vertex_s
{
  int	isValid;
  int	isFake;
  double	chi2;
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
  sprintf(r, "  %-32s: %f\n", "isValid", (double)o.isValid); os << r;
  sprintf(r, "  %-32s: %f\n", "isFake", (double)o.isFake); os << r;
  sprintf(r, "  %-32s: %f\n", "chi2", (double)o.chi2); os << r;
  sprintf(r, "  %-32s: %f\n", "ndof", (double)o.ndof); os << r;
  sprintf(r, "  %-32s: %f\n", "x", (double)o.x); os << r;
  sprintf(r, "  %-32s: %f\n", "y", (double)o.y); os << r;
  sprintf(r, "  %-32s: %f\n", "z", (double)o.z); os << r;
  return os;
}
//-----------------------------------------------------------------------------

inline void fillGenParticleHelper()
{
  GenParticleHelper.resize(GenParticleHelper_charge.size());
  for(unsigned int i=0; i < GenParticleHelper.size(); ++i)
    {
      GenParticleHelper[i].charge	= GenParticleHelper_charge[i];
      GenParticleHelper[i].pdgId	= GenParticleHelper_pdgId[i];
      GenParticleHelper[i].status	= GenParticleHelper_status[i];
      GenParticleHelper[i].energy	= GenParticleHelper_energy[i];
      GenParticleHelper[i].pt	= GenParticleHelper_pt[i];
      GenParticleHelper[i].phi	= GenParticleHelper_phi[i];
      GenParticleHelper[i].eta	= GenParticleHelper_eta[i];
      GenParticleHelper[i].mass	= GenParticleHelper_mass[i];
      GenParticleHelper[i].firstMother	= GenParticleHelper_firstMother[i];
      GenParticleHelper[i].lastMother	= GenParticleHelper_lastMother[i];
      GenParticleHelper[i].firstDaughter	= GenParticleHelper_firstDaughter[i];
      GenParticleHelper[i].lastDaughter	= GenParticleHelper_lastDaughter[i];
    }
}

inline void fillPileupSummaryInfo()
{
  PileupSummaryInfo.resize(PileupSummaryInfo_getBunchCrossing.size());
  for(unsigned int i=0; i < PileupSummaryInfo.size(); ++i)
    {
      PileupSummaryInfo[i].getBunchCrossing	= PileupSummaryInfo_getBunchCrossing[i];
      PileupSummaryInfo[i].getPU_NumInteractions	= PileupSummaryInfo_getPU_NumInteractions[i];
      PileupSummaryInfo[i].getTrueNumInteractions	= PileupSummaryInfo_getTrueNumInteractions[i];
    }
}

inline void fillelectron()
{
  electron.resize(electron_charge.size());
  for(unsigned int i=0; i < electron.size(); ++i)
    {
      electron[i].charge	= electron_charge[i];
      electron[i].p	= electron_p[i];
      electron[i].energy	= electron_energy[i];
      electron[i].et	= electron_et[i];
      electron[i].px	= electron_px[i];
      electron[i].py	= electron_py[i];
      electron[i].pz	= electron_pz[i];
      electron[i].pt	= electron_pt[i];
      electron[i].phi	= electron_phi[i];
      electron[i].eta	= electron_eta[i];
      electron[i].trackIso	= electron_trackIso[i];
      electron[i].ecalIso	= electron_ecalIso[i];
      electron[i].hcalIso	= electron_hcalIso[i];
      electron[i].caloIso	= electron_caloIso[i];
      electron[i].isPF	= electron_isPF[i];
      electron[i].eSuperClusterOverP	= electron_eSuperClusterOverP[i];
      electron[i].deltaEtaSuperClusterTrackAtVtx	= electron_deltaEtaSuperClusterTrackAtVtx[i];
      electron[i].deltaPhiSuperClusterTrackAtVtx	= electron_deltaPhiSuperClusterTrackAtVtx[i];
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
}

inline void filljet()
{
  jet.resize(jet_charge.size());
  for(unsigned int i=0; i < jet.size(); ++i)
    {
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
      jet[i].partonFlavour	= jet_partonFlavour[i];
      jet[i].hadronFlavour	= jet_hadronFlavour[i];
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
      jet[i].chargedMuEnergy	= jet_chargedMuEnergy[i];
      jet[i].chargedMuEnergyFraction	= jet_chargedMuEnergyFraction[i];
      jet[i].neutralMultiplicity	= jet_neutralMultiplicity[i];
      jet[i].numberOfDaughters	= jet_numberOfDaughters[i];
    }
}

inline void fillmet2()
{
  met2.resize(met2_p.size());
  for(unsigned int i=0; i < met2.size(); ++i)
    {
      met2[i].p	= met2_p[i];
      met2[i].energy	= met2_energy[i];
      met2[i].et	= met2_et[i];
      met2[i].px	= met2_px[i];
      met2[i].py	= met2_py[i];
      met2[i].pz	= met2_pz[i];
      met2[i].pt	= met2_pt[i];
      met2[i].phi	= met2_phi[i];
      met2[i].eta	= met2_eta[i];
    }
}

inline void fillmuon()
{
  muon.resize(muon_charge.size());
  for(unsigned int i=0; i < muon.size(); ++i)
    {
      muon[i].charge	= muon_charge[i];
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
}

inline void filltau()
{
  tau.resize(tau_charge.size());
  for(unsigned int i=0; i < tau.size(); ++i)
    {
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
      tau[i].mass	= tau_mass[i];
      tau[i].leadChargedHadrCand_p	= tau_leadChargedHadrCand_p[i];
      tau[i].leadChargedHadrCand_energy	= tau_leadChargedHadrCand_energy[i];
      tau[i].leadChargedHadrCand_et	= tau_leadChargedHadrCand_et[i];
      tau[i].leadChargedHadrCand_mass	= tau_leadChargedHadrCand_mass[i];
      tau[i].leadChargedHadrCand_massSqr	= tau_leadChargedHadrCand_massSqr[i];
      tau[i].leadChargedHadrCand_mt	= tau_leadChargedHadrCand_mt[i];
      tau[i].leadChargedHadrCand_mtSqr	= tau_leadChargedHadrCand_mtSqr[i];
      tau[i].leadChargedHadrCand_px	= tau_leadChargedHadrCand_px[i];
      tau[i].leadChargedHadrCand_py	= tau_leadChargedHadrCand_py[i];
      tau[i].leadChargedHadrCand_pz	= tau_leadChargedHadrCand_pz[i];
      tau[i].leadChargedHadrCand_pt	= tau_leadChargedHadrCand_pt[i];
      tau[i].leadChargedHadrCand_phi	= tau_leadChargedHadrCand_phi[i];
      tau[i].leadChargedHadrCand_theta	= tau_leadChargedHadrCand_theta[i];
      tau[i].leadChargedHadrCand_eta	= tau_leadChargedHadrCand_eta[i];
      tau[i].leadChargedHadrCand_rapidity	= tau_leadChargedHadrCand_rapidity[i];
      tau[i].leadChargedHadrCand_y	= tau_leadChargedHadrCand_y[i];
      tau[i].tauID_againstElectronLoose	= tau_tauID_againstElectronLoose[i];
      tau[i].tauID_againstElectronLooseMVA5	= tau_tauID_againstElectronLooseMVA5[i];
      tau[i].tauID_againstElectronMVA5category	= tau_tauID_againstElectronMVA5category[i];
      tau[i].tauID_againstElectronMVA5raw	= tau_tauID_againstElectronMVA5raw[i];
      tau[i].tauID_againstElectronMedium	= tau_tauID_againstElectronMedium[i];
      tau[i].tauID_againstElectronMediumMVA5	= tau_tauID_againstElectronMediumMVA5[i];
      tau[i].tauID_againstElectronTight	= tau_tauID_againstElectronTight[i];
      tau[i].tauID_againstElectronTightMVA5	= tau_tauID_againstElectronTightMVA5[i];
      tau[i].tauID_againstElectronVLooseMVA5	= tau_tauID_againstElectronVLooseMVA5[i];
      tau[i].tauID_againstElectronVTightMVA5	= tau_tauID_againstElectronVTightMVA5[i];
      tau[i].tauID_againstMuonLoose	= tau_tauID_againstMuonLoose[i];
      tau[i].tauID_againstMuonLoose2	= tau_tauID_againstMuonLoose2[i];
      tau[i].tauID_againstMuonLoose3	= tau_tauID_againstMuonLoose3[i];
      tau[i].tauID_againstMuonLooseMVA	= tau_tauID_againstMuonLooseMVA[i];
      tau[i].tauID_againstMuonMVAraw	= tau_tauID_againstMuonMVAraw[i];
      tau[i].tauID_againstMuonMedium	= tau_tauID_againstMuonMedium[i];
      tau[i].tauID_againstMuonMedium2	= tau_tauID_againstMuonMedium2[i];
      tau[i].tauID_againstMuonMediumMVA	= tau_tauID_againstMuonMediumMVA[i];
      tau[i].tauID_againstMuonTight	= tau_tauID_againstMuonTight[i];
      tau[i].tauID_againstMuonTight2	= tau_tauID_againstMuonTight2[i];
      tau[i].tauID_againstMuonTight3	= tau_tauID_againstMuonTight3[i];
      tau[i].tauID_againstMuonTightMVA	= tau_tauID_againstMuonTightMVA[i];
      tau[i].tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits	= tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[i];
      tau[i].tauID_byIsolationMVA3newDMwLTraw	= tau_tauID_byIsolationMVA3newDMwLTraw[i];
      tau[i].tauID_byIsolationMVA3newDMwoLTraw	= tau_tauID_byIsolationMVA3newDMwoLTraw[i];
      tau[i].tauID_byIsolationMVA3oldDMwLTraw	= tau_tauID_byIsolationMVA3oldDMwLTraw[i];
      tau[i].tauID_byIsolationMVA3oldDMwoLTraw	= tau_tauID_byIsolationMVA3oldDMwoLTraw[i];
      tau[i].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits	= tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byLooseIsolationMVA3newDMwLT	= tau_tauID_byLooseIsolationMVA3newDMwLT[i];
      tau[i].tauID_byLooseIsolationMVA3newDMwoLT	= tau_tauID_byLooseIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byLooseIsolationMVA3oldDMwLT	= tau_tauID_byLooseIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byLooseIsolationMVA3oldDMwoLT	= tau_tauID_byLooseIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits	= tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byMediumIsolationMVA3newDMwLT	= tau_tauID_byMediumIsolationMVA3newDMwLT[i];
      tau[i].tauID_byMediumIsolationMVA3newDMwoLT	= tau_tauID_byMediumIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byMediumIsolationMVA3oldDMwLT	= tau_tauID_byMediumIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byMediumIsolationMVA3oldDMwoLT	= tau_tauID_byMediumIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits	= tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[i];
      tau[i].tauID_byTightIsolationMVA3newDMwLT	= tau_tauID_byTightIsolationMVA3newDMwLT[i];
      tau[i].tauID_byTightIsolationMVA3newDMwoLT	= tau_tauID_byTightIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byTightIsolationMVA3oldDMwLT	= tau_tauID_byTightIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byTightIsolationMVA3oldDMwoLT	= tau_tauID_byTightIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byVLooseIsolationMVA3newDMwLT	= tau_tauID_byVLooseIsolationMVA3newDMwLT[i];
      tau[i].tauID_byVLooseIsolationMVA3newDMwoLT	= tau_tauID_byVLooseIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byVLooseIsolationMVA3oldDMwLT	= tau_tauID_byVLooseIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byVLooseIsolationMVA3oldDMwoLT	= tau_tauID_byVLooseIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byVTightIsolationMVA3newDMwLT	= tau_tauID_byVTightIsolationMVA3newDMwLT[i];
      tau[i].tauID_byVTightIsolationMVA3newDMwoLT	= tau_tauID_byVTightIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byVTightIsolationMVA3oldDMwLT	= tau_tauID_byVTightIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byVTightIsolationMVA3oldDMwoLT	= tau_tauID_byVTightIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_byVVTightIsolationMVA3newDMwLT	= tau_tauID_byVVTightIsolationMVA3newDMwLT[i];
      tau[i].tauID_byVVTightIsolationMVA3newDMwoLT	= tau_tauID_byVVTightIsolationMVA3newDMwoLT[i];
      tau[i].tauID_byVVTightIsolationMVA3oldDMwLT	= tau_tauID_byVVTightIsolationMVA3oldDMwLT[i];
      tau[i].tauID_byVVTightIsolationMVA3oldDMwoLT	= tau_tauID_byVVTightIsolationMVA3oldDMwoLT[i];
      tau[i].tauID_chargedIsoPtSum	= tau_tauID_chargedIsoPtSum[i];
      tau[i].tauID_decayModeFinding	= tau_tauID_decayModeFinding[i];
      tau[i].tauID_decayModeFindingNewDMs	= tau_tauID_decayModeFindingNewDMs[i];
      tau[i].tauID_neutralIsoPtSum	= tau_tauID_neutralIsoPtSum[i];
      tau[i].tauID_puCorrPtSum	= tau_tauID_puCorrPtSum[i];
    }
}

inline void fillvertex()
{
  vertex.resize(vertex_isValid.size());
  for(unsigned int i=0; i < vertex.size(); ++i)
    {
      vertex[i].isValid	= vertex_isValid[i];
      vertex[i].isFake	= vertex_isFake[i];
      vertex[i].chi2	= vertex_chi2[i];
      vertex[i].ndof	= vertex_ndof[i];
      vertex[i].x	= vertex_x[i];
      vertex[i].y	= vertex_y[i];
      vertex[i].z	= vertex_z[i];
    }
}


void fillObjects()
{
  fillGenParticleHelper();
  fillPileupSummaryInfo();
  fillelectron();
  filljet();
  fillmet2();
  fillmuon();
  filltau();
  fillvertex();
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
       n = indexmap["GenParticleHelper"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["GenParticleHelper"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          GenParticleHelper_charge[i]	= GenParticleHelper_charge[j];
          GenParticleHelper_pdgId[i]	= GenParticleHelper_pdgId[j];
          GenParticleHelper_status[i]	= GenParticleHelper_status[j];
          GenParticleHelper_energy[i]	= GenParticleHelper_energy[j];
          GenParticleHelper_pt[i]	= GenParticleHelper_pt[j];
          GenParticleHelper_phi[i]	= GenParticleHelper_phi[j];
          GenParticleHelper_eta[i]	= GenParticleHelper_eta[j];
          GenParticleHelper_mass[i]	= GenParticleHelper_mass[j];
          GenParticleHelper_firstMother[i]	= GenParticleHelper_firstMother[j];
          GenParticleHelper_lastMother[i]	= GenParticleHelper_lastMother[j];
          GenParticleHelper_firstDaughter[i]	= GenParticleHelper_firstDaughter[j];
          GenParticleHelper_lastDaughter[i]	= GenParticleHelper_lastDaughter[j];
        }
      nGenParticleHelper = n;
    }

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
          PileupSummaryInfo_getTrueNumInteractions[i]	= PileupSummaryInfo_getTrueNumInteractions[j];
        }
      nPileupSummaryInfo = n;
    }

  n = 0;
  try
    {
       n = indexmap["electron"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["electron"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          electron_charge[i]	= electron_charge[j];
          electron_p[i]	= electron_p[j];
          electron_energy[i]	= electron_energy[j];
          electron_et[i]	= electron_et[j];
          electron_px[i]	= electron_px[j];
          electron_py[i]	= electron_py[j];
          electron_pz[i]	= electron_pz[j];
          electron_pt[i]	= electron_pt[j];
          electron_phi[i]	= electron_phi[j];
          electron_eta[i]	= electron_eta[j];
          electron_trackIso[i]	= electron_trackIso[j];
          electron_ecalIso[i]	= electron_ecalIso[j];
          electron_hcalIso[i]	= electron_hcalIso[j];
          electron_caloIso[i]	= electron_caloIso[j];
          electron_isPF[i]	= electron_isPF[j];
          electron_eSuperClusterOverP[i]	= electron_eSuperClusterOverP[j];
          electron_deltaEtaSuperClusterTrackAtVtx[i]	= electron_deltaEtaSuperClusterTrackAtVtx[j];
          electron_deltaPhiSuperClusterTrackAtVtx[i]	= electron_deltaPhiSuperClusterTrackAtVtx[j];
          electron_scE1x5[i]	= electron_scE1x5[j];
          electron_scE2x5Max[i]	= electron_scE2x5Max[j];
          electron_scE5x5[i]	= electron_scE5x5[j];
          electron_hadronicOverEm[i]	= electron_hadronicOverEm[j];
          electron_dr04TkSumPt[i]	= electron_dr04TkSumPt[j];
          electron_dr04EcalRecHitSumEt[i]	= electron_dr04EcalRecHitSumEt[j];
          electron_gsfTrack_dxy[i]	= electron_gsfTrack_dxy[j];
          electron_gsfTrack_d0[i]	= electron_gsfTrack_d0[j];
          electron_gsfTrack_dz[i]	= electron_gsfTrack_dz[j];
        }
      nelectron = n;
    }

  n = 0;
  try
    {
       n = indexmap["jet"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["jet"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          jet_charge[i]	= jet_charge[j];
          jet_p[i]	= jet_p[j];
          jet_energy[i]	= jet_energy[j];
          jet_et[i]	= jet_et[j];
          jet_px[i]	= jet_px[j];
          jet_py[i]	= jet_py[j];
          jet_pz[i]	= jet_pz[j];
          jet_pt[i]	= jet_pt[j];
          jet_phi[i]	= jet_phi[j];
          jet_eta[i]	= jet_eta[j];
          jet_partonFlavour[i]	= jet_partonFlavour[j];
          jet_hadronFlavour[i]	= jet_hadronFlavour[j];
          jet_neutralHadronEnergy[i]	= jet_neutralHadronEnergy[j];
          jet_chargedHadronEnergyFraction[i]	= jet_chargedHadronEnergyFraction[j];
          jet_neutralHadronEnergyFraction[i]	= jet_neutralHadronEnergyFraction[j];
          jet_chargedEmEnergyFraction[i]	= jet_chargedEmEnergyFraction[j];
          jet_neutralEmEnergyFraction[i]	= jet_neutralEmEnergyFraction[j];
          jet_photonEnergy[i]	= jet_photonEnergy[j];
          jet_photonEnergyFraction[i]	= jet_photonEnergyFraction[j];
          jet_electronEnergy[i]	= jet_electronEnergy[j];
          jet_electronEnergyFraction[i]	= jet_electronEnergyFraction[j];
          jet_muonEnergy[i]	= jet_muonEnergy[j];
          jet_muonEnergyFraction[i]	= jet_muonEnergyFraction[j];
          jet_HFHadronEnergy[i]	= jet_HFHadronEnergy[j];
          jet_HFHadronEnergyFraction[i]	= jet_HFHadronEnergyFraction[j];
          jet_HFEMEnergy[i]	= jet_HFEMEnergy[j];
          jet_HFEMEnergyFraction[i]	= jet_HFEMEnergyFraction[j];
          jet_chargedHadronMultiplicity[i]	= jet_chargedHadronMultiplicity[j];
          jet_neutralHadronMultiplicity[i]	= jet_neutralHadronMultiplicity[j];
          jet_photonMultiplicity[i]	= jet_photonMultiplicity[j];
          jet_electronMultiplicity[i]	= jet_electronMultiplicity[j];
          jet_HFHadronMultiplicity[i]	= jet_HFHadronMultiplicity[j];
          jet_HFEMMultiplicity[i]	= jet_HFEMMultiplicity[j];
          jet_chargedMuEnergy[i]	= jet_chargedMuEnergy[j];
          jet_chargedMuEnergyFraction[i]	= jet_chargedMuEnergyFraction[j];
          jet_neutralMultiplicity[i]	= jet_neutralMultiplicity[j];
          jet_numberOfDaughters[i]	= jet_numberOfDaughters[j];
        }
      njet = n;
    }

  n = 0;
  try
    {
       n = indexmap["met2"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["met2"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          met2_p[i]	= met2_p[j];
          met2_energy[i]	= met2_energy[j];
          met2_et[i]	= met2_et[j];
          met2_px[i]	= met2_px[j];
          met2_py[i]	= met2_py[j];
          met2_pz[i]	= met2_pz[j];
          met2_pt[i]	= met2_pt[j];
          met2_phi[i]	= met2_phi[j];
          met2_eta[i]	= met2_eta[j];
        }
      nmet2 = n;
    }

  n = 0;
  try
    {
       n = indexmap["muon"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["muon"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          muon_charge[i]	= muon_charge[j];
          muon_p[i]	= muon_p[j];
          muon_energy[i]	= muon_energy[j];
          muon_et[i]	= muon_et[j];
          muon_px[i]	= muon_px[j];
          muon_py[i]	= muon_py[j];
          muon_pz[i]	= muon_pz[j];
          muon_pt[i]	= muon_pt[j];
          muon_phi[i]	= muon_phi[j];
          muon_eta[i]	= muon_eta[j];
          muon_isGlobalMuon[i]	= muon_isGlobalMuon[j];
          muon_isTrackerMuon[i]	= muon_isTrackerMuon[j];
          muon_isPFMuon[i]	= muon_isPFMuon[j];
          muon_pfIsolationR03_sumChargedHadronPt[i]	= muon_pfIsolationR03_sumChargedHadronPt[j];
          muon_pfIsolationR03_sumChargedParticlePt[i]	= muon_pfIsolationR03_sumChargedParticlePt[j];
          muon_pfIsolationR03_sumNeutralHadronEt[i]	= muon_pfIsolationR03_sumNeutralHadronEt[j];
          muon_pfIsolationR03_sumNeutralHadronEtHighThreshold[i]	= muon_pfIsolationR03_sumNeutralHadronEtHighThreshold[j];
          muon_pfIsolationR03_sumPhotonEt[i]	= muon_pfIsolationR03_sumPhotonEt[j];
          muon_pfIsolationR03_sumPhotonEtHighThreshold[i]	= muon_pfIsolationR03_sumPhotonEtHighThreshold[j];
          muon_pfIsolationR03_sumPUPt[i]	= muon_pfIsolationR03_sumPUPt[j];
          muon_pfIsolationR04_sumChargedHadronPt[i]	= muon_pfIsolationR04_sumChargedHadronPt[j];
          muon_pfIsolationR04_sumChargedParticlePt[i]	= muon_pfIsolationR04_sumChargedParticlePt[j];
          muon_pfIsolationR04_sumNeutralHadronEt[i]	= muon_pfIsolationR04_sumNeutralHadronEt[j];
          muon_pfIsolationR04_sumNeutralHadronEtHighThreshold[i]	= muon_pfIsolationR04_sumNeutralHadronEtHighThreshold[j];
          muon_pfIsolationR04_sumPhotonEt[i]	= muon_pfIsolationR04_sumPhotonEt[j];
          muon_pfIsolationR04_sumPhotonEtHighThreshold[i]	= muon_pfIsolationR04_sumPhotonEtHighThreshold[j];
          muon_pfIsolationR04_sumPUPt[i]	= muon_pfIsolationR04_sumPUPt[j];
          muon_numberOfMatchedStations[i]	= muon_numberOfMatchedStations[j];
          muon_innerTrack_normalizedChi2[i]	= muon_innerTrack_normalizedChi2[j];
          muon_innerTrack_dxy[i]	= muon_innerTrack_dxy[j];
          muon_innerTrack_dz[i]	= muon_innerTrack_dz[j];
          muon_innerTrack_hitPattern_numberOfValidPixelHits[i]	= muon_innerTrack_hitPattern_numberOfValidPixelHits[j];
          muon_innerTrack_hitPattern_pixelLayersWithMeasurement[i]	= muon_innerTrack_hitPattern_pixelLayersWithMeasurement[j];
          muon_globalTrack_normalizedChi2[i]	= muon_globalTrack_normalizedChi2[j];
          muon_globalTrack_hitPattern_numberOfValidMuonHits[i]	= muon_globalTrack_hitPattern_numberOfValidMuonHits[j];
          muon_muonBestTrack_dxy[i]	= muon_muonBestTrack_dxy[j];
          muon_muonBestTrack_dz[i]	= muon_muonBestTrack_dz[j];
        }
      nmuon = n;
    }

  n = 0;
  try
    {
       n = indexmap["tau"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["tau"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          tau_charge[i]	= tau_charge[j];
          tau_p[i]	= tau_p[j];
          tau_energy[i]	= tau_energy[j];
          tau_et[i]	= tau_et[j];
          tau_px[i]	= tau_px[j];
          tau_py[i]	= tau_py[j];
          tau_pz[i]	= tau_pz[j];
          tau_pt[i]	= tau_pt[j];
          tau_phi[i]	= tau_phi[j];
          tau_eta[i]	= tau_eta[j];
          tau_mass[i]	= tau_mass[j];
          tau_leadChargedHadrCand_p[i]	= tau_leadChargedHadrCand_p[j];
          tau_leadChargedHadrCand_energy[i]	= tau_leadChargedHadrCand_energy[j];
          tau_leadChargedHadrCand_et[i]	= tau_leadChargedHadrCand_et[j];
          tau_leadChargedHadrCand_mass[i]	= tau_leadChargedHadrCand_mass[j];
          tau_leadChargedHadrCand_massSqr[i]	= tau_leadChargedHadrCand_massSqr[j];
          tau_leadChargedHadrCand_mt[i]	= tau_leadChargedHadrCand_mt[j];
          tau_leadChargedHadrCand_mtSqr[i]	= tau_leadChargedHadrCand_mtSqr[j];
          tau_leadChargedHadrCand_px[i]	= tau_leadChargedHadrCand_px[j];
          tau_leadChargedHadrCand_py[i]	= tau_leadChargedHadrCand_py[j];
          tau_leadChargedHadrCand_pz[i]	= tau_leadChargedHadrCand_pz[j];
          tau_leadChargedHadrCand_pt[i]	= tau_leadChargedHadrCand_pt[j];
          tau_leadChargedHadrCand_phi[i]	= tau_leadChargedHadrCand_phi[j];
          tau_leadChargedHadrCand_theta[i]	= tau_leadChargedHadrCand_theta[j];
          tau_leadChargedHadrCand_eta[i]	= tau_leadChargedHadrCand_eta[j];
          tau_leadChargedHadrCand_rapidity[i]	= tau_leadChargedHadrCand_rapidity[j];
          tau_leadChargedHadrCand_y[i]	= tau_leadChargedHadrCand_y[j];
          tau_tauID_againstElectronLoose[i]	= tau_tauID_againstElectronLoose[j];
          tau_tauID_againstElectronLooseMVA5[i]	= tau_tauID_againstElectronLooseMVA5[j];
          tau_tauID_againstElectronMVA5category[i]	= tau_tauID_againstElectronMVA5category[j];
          tau_tauID_againstElectronMVA5raw[i]	= tau_tauID_againstElectronMVA5raw[j];
          tau_tauID_againstElectronMedium[i]	= tau_tauID_againstElectronMedium[j];
          tau_tauID_againstElectronMediumMVA5[i]	= tau_tauID_againstElectronMediumMVA5[j];
          tau_tauID_againstElectronTight[i]	= tau_tauID_againstElectronTight[j];
          tau_tauID_againstElectronTightMVA5[i]	= tau_tauID_againstElectronTightMVA5[j];
          tau_tauID_againstElectronVLooseMVA5[i]	= tau_tauID_againstElectronVLooseMVA5[j];
          tau_tauID_againstElectronVTightMVA5[i]	= tau_tauID_againstElectronVTightMVA5[j];
          tau_tauID_againstMuonLoose[i]	= tau_tauID_againstMuonLoose[j];
          tau_tauID_againstMuonLoose2[i]	= tau_tauID_againstMuonLoose2[j];
          tau_tauID_againstMuonLoose3[i]	= tau_tauID_againstMuonLoose3[j];
          tau_tauID_againstMuonLooseMVA[i]	= tau_tauID_againstMuonLooseMVA[j];
          tau_tauID_againstMuonMVAraw[i]	= tau_tauID_againstMuonMVAraw[j];
          tau_tauID_againstMuonMedium[i]	= tau_tauID_againstMuonMedium[j];
          tau_tauID_againstMuonMedium2[i]	= tau_tauID_againstMuonMedium2[j];
          tau_tauID_againstMuonMediumMVA[i]	= tau_tauID_againstMuonMediumMVA[j];
          tau_tauID_againstMuonTight[i]	= tau_tauID_againstMuonTight[j];
          tau_tauID_againstMuonTight2[i]	= tau_tauID_againstMuonTight2[j];
          tau_tauID_againstMuonTight3[i]	= tau_tauID_againstMuonTight3[j];
          tau_tauID_againstMuonTightMVA[i]	= tau_tauID_againstMuonTightMVA[j];
          tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[i]	= tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits[j];
          tau_tauID_byIsolationMVA3newDMwLTraw[i]	= tau_tauID_byIsolationMVA3newDMwLTraw[j];
          tau_tauID_byIsolationMVA3newDMwoLTraw[i]	= tau_tauID_byIsolationMVA3newDMwoLTraw[j];
          tau_tauID_byIsolationMVA3oldDMwLTraw[i]	= tau_tauID_byIsolationMVA3oldDMwLTraw[j];
          tau_tauID_byIsolationMVA3oldDMwoLTraw[i]	= tau_tauID_byIsolationMVA3oldDMwoLTraw[j];
          tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[i]	= tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits[j];
          tau_tauID_byLooseIsolationMVA3newDMwLT[i]	= tau_tauID_byLooseIsolationMVA3newDMwLT[j];
          tau_tauID_byLooseIsolationMVA3newDMwoLT[i]	= tau_tauID_byLooseIsolationMVA3newDMwoLT[j];
          tau_tauID_byLooseIsolationMVA3oldDMwLT[i]	= tau_tauID_byLooseIsolationMVA3oldDMwLT[j];
          tau_tauID_byLooseIsolationMVA3oldDMwoLT[i]	= tau_tauID_byLooseIsolationMVA3oldDMwoLT[j];
          tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[i]	= tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits[j];
          tau_tauID_byMediumIsolationMVA3newDMwLT[i]	= tau_tauID_byMediumIsolationMVA3newDMwLT[j];
          tau_tauID_byMediumIsolationMVA3newDMwoLT[i]	= tau_tauID_byMediumIsolationMVA3newDMwoLT[j];
          tau_tauID_byMediumIsolationMVA3oldDMwLT[i]	= tau_tauID_byMediumIsolationMVA3oldDMwLT[j];
          tau_tauID_byMediumIsolationMVA3oldDMwoLT[i]	= tau_tauID_byMediumIsolationMVA3oldDMwoLT[j];
          tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[i]	= tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits[j];
          tau_tauID_byTightIsolationMVA3newDMwLT[i]	= tau_tauID_byTightIsolationMVA3newDMwLT[j];
          tau_tauID_byTightIsolationMVA3newDMwoLT[i]	= tau_tauID_byTightIsolationMVA3newDMwoLT[j];
          tau_tauID_byTightIsolationMVA3oldDMwLT[i]	= tau_tauID_byTightIsolationMVA3oldDMwLT[j];
          tau_tauID_byTightIsolationMVA3oldDMwoLT[i]	= tau_tauID_byTightIsolationMVA3oldDMwoLT[j];
          tau_tauID_byVLooseIsolationMVA3newDMwLT[i]	= tau_tauID_byVLooseIsolationMVA3newDMwLT[j];
          tau_tauID_byVLooseIsolationMVA3newDMwoLT[i]	= tau_tauID_byVLooseIsolationMVA3newDMwoLT[j];
          tau_tauID_byVLooseIsolationMVA3oldDMwLT[i]	= tau_tauID_byVLooseIsolationMVA3oldDMwLT[j];
          tau_tauID_byVLooseIsolationMVA3oldDMwoLT[i]	= tau_tauID_byVLooseIsolationMVA3oldDMwoLT[j];
          tau_tauID_byVTightIsolationMVA3newDMwLT[i]	= tau_tauID_byVTightIsolationMVA3newDMwLT[j];
          tau_tauID_byVTightIsolationMVA3newDMwoLT[i]	= tau_tauID_byVTightIsolationMVA3newDMwoLT[j];
          tau_tauID_byVTightIsolationMVA3oldDMwLT[i]	= tau_tauID_byVTightIsolationMVA3oldDMwLT[j];
          tau_tauID_byVTightIsolationMVA3oldDMwoLT[i]	= tau_tauID_byVTightIsolationMVA3oldDMwoLT[j];
          tau_tauID_byVVTightIsolationMVA3newDMwLT[i]	= tau_tauID_byVVTightIsolationMVA3newDMwLT[j];
          tau_tauID_byVVTightIsolationMVA3newDMwoLT[i]	= tau_tauID_byVVTightIsolationMVA3newDMwoLT[j];
          tau_tauID_byVVTightIsolationMVA3oldDMwLT[i]	= tau_tauID_byVVTightIsolationMVA3oldDMwLT[j];
          tau_tauID_byVVTightIsolationMVA3oldDMwoLT[i]	= tau_tauID_byVVTightIsolationMVA3oldDMwoLT[j];
          tau_tauID_chargedIsoPtSum[i]	= tau_tauID_chargedIsoPtSum[j];
          tau_tauID_decayModeFinding[i]	= tau_tauID_decayModeFinding[j];
          tau_tauID_decayModeFindingNewDMs[i]	= tau_tauID_decayModeFindingNewDMs[j];
          tau_tauID_neutralIsoPtSum[i]	= tau_tauID_neutralIsoPtSum[j];
          tau_tauID_puCorrPtSum[i]	= tau_tauID_puCorrPtSum[j];
        }
      ntau = n;
    }

  n = 0;
  try
    {
       n = indexmap["vertex"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["vertex"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          vertex_isValid[i]	= vertex_isValid[j];
          vertex_isFake[i]	= vertex_isFake[j];
          vertex_chi2[i]	= vertex_chi2[j];
          vertex_ndof[i]	= vertex_ndof[j];
          vertex_x[i]	= vertex_x[j];
          vertex_y[i]	= vertex_y[j];
          vertex_z[i]	= vertex_z[j];
        }
      nvertex = n;
    }
}

//-----------------------------------------------------------------------------
// --- Select variables to be read
//-----------------------------------------------------------------------------
void selectVariables(itreestream& stream)
{
  stream.select("recoBeamSpot_offlineBeamSpot.x0", BeamSpot_x0);
  stream.select("recoBeamSpot_offlineBeamSpot.y0", BeamSpot_y0);
  stream.select("recoBeamSpot_offlineBeamSpot.z0", BeamSpot_z0);
  stream.select("recoGenParticleHelper2_prunedGenParticles.charge", GenParticleHelper_charge);
  stream.select("recoGenParticleHelper2_prunedGenParticles.energy", GenParticleHelper_energy);
  stream.select("recoGenParticleHelper2_prunedGenParticles.eta", GenParticleHelper_eta);
  stream.select("recoGenParticleHelper2_prunedGenParticles.firstDaughter", GenParticleHelper_firstDaughter);
  stream.select("recoGenParticleHelper2_prunedGenParticles.firstMother", GenParticleHelper_firstMother);
  stream.select("recoGenParticleHelper2_prunedGenParticles.lastDaughter", GenParticleHelper_lastDaughter);
  stream.select("recoGenParticleHelper2_prunedGenParticles.lastMother", GenParticleHelper_lastMother);
  stream.select("recoGenParticleHelper2_prunedGenParticles.mass", GenParticleHelper_mass);
  stream.select("recoGenParticleHelper2_prunedGenParticles.pdgId", GenParticleHelper_pdgId);
  stream.select("recoGenParticleHelper2_prunedGenParticles.phi", GenParticleHelper_phi);
  stream.select("recoGenParticleHelper2_prunedGenParticles.pt", GenParticleHelper_pt);
  stream.select("recoGenParticleHelper2_prunedGenParticles.status", GenParticleHelper_status);
  stream.select("PileupSummaryInfo_addPileupInfo.getBunchCrossing", PileupSummaryInfo_getBunchCrossing);
  stream.select("PileupSummaryInfo_addPileupInfo.getPU_NumInteractions", PileupSummaryInfo_getPU_NumInteractions);
  stream.select("PileupSummaryInfo_addPileupInfo.getTrueNumInteractions", PileupSummaryInfo_getTrueNumInteractions);
  stream.select("edmEventHelper_info.bunchCrossing", edmEventHelper_bunchCrossing);
  stream.select("edmEventHelper_info.event", edmEventHelper_event);
  stream.select("edmEventHelper_info.isRealData", edmEventHelper_isRealData);
  stream.select("edmEventHelper_info.luminosityBlock", edmEventHelper_luminosityBlock);
  stream.select("edmEventHelper_info.orbitNumber", edmEventHelper_orbitNumber);
  stream.select("edmEventHelper_info.run", edmEventHelper_run);
  stream.select("patElectron_slimmedElectrons.caloIso", electron_caloIso);
  stream.select("patElectron_slimmedElectrons.charge", electron_charge);
  stream.select("patElectron_slimmedElectrons.deltaEtaSuperClusterTrackAtVtx", electron_deltaEtaSuperClusterTrackAtVtx);
  stream.select("patElectron_slimmedElectrons.deltaPhiSuperClusterTrackAtVtx", electron_deltaPhiSuperClusterTrackAtVtx);
  stream.select("patElectron_slimmedElectrons.dr04EcalRecHitSumEt", electron_dr04EcalRecHitSumEt);
  stream.select("patElectron_slimmedElectrons.dr04TkSumPt", electron_dr04TkSumPt);
  stream.select("patElectron_slimmedElectrons.eSuperClusterOverP", electron_eSuperClusterOverP);
  stream.select("patElectron_slimmedElectrons.ecalIso", electron_ecalIso);
  stream.select("patElectron_slimmedElectrons.energy", electron_energy);
  stream.select("patElectron_slimmedElectrons.et", electron_et);
  stream.select("patElectron_slimmedElectrons.eta", electron_eta);
  stream.select("patElectron_slimmedElectrons.gsfTrack_d0", electron_gsfTrack_d0);
  stream.select("patElectron_slimmedElectrons.gsfTrack_dxy", electron_gsfTrack_dxy);
  stream.select("patElectron_slimmedElectrons.gsfTrack_dz", electron_gsfTrack_dz);
  stream.select("patElectron_slimmedElectrons.hadronicOverEm", electron_hadronicOverEm);
  stream.select("patElectron_slimmedElectrons.hcalIso", electron_hcalIso);
  stream.select("patElectron_slimmedElectrons.isPF", electron_isPF);
  stream.select("patElectron_slimmedElectrons.p", electron_p);
  stream.select("patElectron_slimmedElectrons.phi", electron_phi);
  stream.select("patElectron_slimmedElectrons.pt", electron_pt);
  stream.select("patElectron_slimmedElectrons.px", electron_px);
  stream.select("patElectron_slimmedElectrons.py", electron_py);
  stream.select("patElectron_slimmedElectrons.pz", electron_pz);
  stream.select("patElectron_slimmedElectrons.scE1x5", electron_scE1x5);
  stream.select("patElectron_slimmedElectrons.scE2x5Max", electron_scE2x5Max);
  stream.select("patElectron_slimmedElectrons.scE5x5", electron_scE5x5);
  stream.select("patElectron_slimmedElectrons.trackIso", electron_trackIso);
  stream.select("patJet_slimmedJets.HFEMEnergy", jet_HFEMEnergy);
  stream.select("patJet_slimmedJets.HFEMEnergyFraction", jet_HFEMEnergyFraction);
  stream.select("patJet_slimmedJets.HFEMMultiplicity", jet_HFEMMultiplicity);
  stream.select("patJet_slimmedJets.HFHadronEnergy", jet_HFHadronEnergy);
  stream.select("patJet_slimmedJets.HFHadronEnergyFraction", jet_HFHadronEnergyFraction);
  stream.select("patJet_slimmedJets.HFHadronMultiplicity", jet_HFHadronMultiplicity);
  stream.select("patJet_slimmedJets.charge", jet_charge);
  stream.select("patJet_slimmedJets.chargedEmEnergyFraction", jet_chargedEmEnergyFraction);
  stream.select("patJet_slimmedJets.chargedHadronEnergyFraction", jet_chargedHadronEnergyFraction);
  stream.select("patJet_slimmedJets.chargedHadronMultiplicity", jet_chargedHadronMultiplicity);
  stream.select("patJet_slimmedJets.chargedMuEnergy", jet_chargedMuEnergy);
  stream.select("patJet_slimmedJets.chargedMuEnergyFraction", jet_chargedMuEnergyFraction);
  stream.select("patJet_slimmedJets.electronEnergy", jet_electronEnergy);
  stream.select("patJet_slimmedJets.electronEnergyFraction", jet_electronEnergyFraction);
  stream.select("patJet_slimmedJets.electronMultiplicity", jet_electronMultiplicity);
  stream.select("patJet_slimmedJets.energy", jet_energy);
  stream.select("patJet_slimmedJets.et", jet_et);
  stream.select("patJet_slimmedJets.eta", jet_eta);
  stream.select("patJet_slimmedJets.hadronFlavour", jet_hadronFlavour);
  stream.select("patJet_slimmedJets.muonEnergy", jet_muonEnergy);
  stream.select("patJet_slimmedJets.muonEnergyFraction", jet_muonEnergyFraction);
  stream.select("patJet_slimmedJets.neutralEmEnergyFraction", jet_neutralEmEnergyFraction);
  stream.select("patJet_slimmedJets.neutralHadronEnergy", jet_neutralHadronEnergy);
  stream.select("patJet_slimmedJets.neutralHadronEnergyFraction", jet_neutralHadronEnergyFraction);
  stream.select("patJet_slimmedJets.neutralHadronMultiplicity", jet_neutralHadronMultiplicity);
  stream.select("patJet_slimmedJets.neutralMultiplicity", jet_neutralMultiplicity);
  stream.select("patJet_slimmedJets.numberOfDaughters", jet_numberOfDaughters);
  stream.select("patJet_slimmedJets.p", jet_p);
  stream.select("patJet_slimmedJets.partonFlavour", jet_partonFlavour);
  stream.select("patJet_slimmedJets.phi", jet_phi);
  stream.select("patJet_slimmedJets.photonEnergy", jet_photonEnergy);
  stream.select("patJet_slimmedJets.photonEnergyFraction", jet_photonEnergyFraction);
  stream.select("patJet_slimmedJets.photonMultiplicity", jet_photonMultiplicity);
  stream.select("patJet_slimmedJets.pt", jet_pt);
  stream.select("patJet_slimmedJets.px", jet_px);
  stream.select("patJet_slimmedJets.py", jet_py);
  stream.select("patJet_slimmedJets.pz", jet_pz);
  stream.select("patMET_slimmedMETs.energy", met2_energy);
  stream.select("patMET_slimmedMETs.et", met2_et);
  stream.select("patMET_slimmedMETs.eta", met2_eta);
  stream.select("patMET_slimmedMETs.p", met2_p);
  stream.select("patMET_slimmedMETs.phi", met2_phi);
  stream.select("patMET_slimmedMETs.pt", met2_pt);
  stream.select("patMET_slimmedMETs.px", met2_px);
  stream.select("patMET_slimmedMETs.py", met2_py);
  stream.select("patMET_slimmedMETs.pz", met2_pz);
  stream.select("patMuon_slimmedMuons.charge", muon_charge);
  stream.select("patMuon_slimmedMuons.energy", muon_energy);
  stream.select("patMuon_slimmedMuons.et", muon_et);
  stream.select("patMuon_slimmedMuons.eta", muon_eta);
  stream.select("patMuon_slimmedMuons.globalTrack_hitPattern_numberOfValidMuonHits", muon_globalTrack_hitPattern_numberOfValidMuonHits);
  stream.select("patMuon_slimmedMuons.globalTrack_normalizedChi2", muon_globalTrack_normalizedChi2);
  stream.select("patMuon_slimmedMuons.innerTrack_dxy", muon_innerTrack_dxy);
  stream.select("patMuon_slimmedMuons.innerTrack_dz", muon_innerTrack_dz);
  stream.select("patMuon_slimmedMuons.innerTrack_hitPattern_numberOfValidPixelHits", muon_innerTrack_hitPattern_numberOfValidPixelHits);
  stream.select("patMuon_slimmedMuons.innerTrack_hitPattern_pixelLayersWithMeasurement", muon_innerTrack_hitPattern_pixelLayersWithMeasurement);
  stream.select("patMuon_slimmedMuons.innerTrack_normalizedChi2", muon_innerTrack_normalizedChi2);
  stream.select("patMuon_slimmedMuons.isGlobalMuon", muon_isGlobalMuon);
  stream.select("patMuon_slimmedMuons.isPFMuon", muon_isPFMuon);
  stream.select("patMuon_slimmedMuons.isTrackerMuon", muon_isTrackerMuon);
  stream.select("patMuon_slimmedMuons.muonBestTrack_dxy", muon_muonBestTrack_dxy);
  stream.select("patMuon_slimmedMuons.muonBestTrack_dz", muon_muonBestTrack_dz);
  stream.select("patMuon_slimmedMuons.numberOfMatchedStations", muon_numberOfMatchedStations);
  stream.select("patMuon_slimmedMuons.p", muon_p);
  stream.select("patMuon_slimmedMuons.pfIsolationR03_sumChargedHadronPt", muon_pfIsolationR03_sumChargedHadronPt);
  stream.select("patMuon_slimmedMuons.pfIsolationR03_sumChargedParticlePt", muon_pfIsolationR03_sumChargedParticlePt);
  stream.select("patMuon_slimmedMuons.pfIsolationR03_sumNeutralHadronEt", muon_pfIsolationR03_sumNeutralHadronEt);
  stream.select("patMuon_slimmedMuons.pfIsolationR03_sumNeutralHadronEtHighThreshold", muon_pfIsolationR03_sumNeutralHadronEtHighThreshold);
  stream.select("patMuon_slimmedMuons.pfIsolationR03_sumPUPt", muon_pfIsolationR03_sumPUPt);
  stream.select("patMuon_slimmedMuons.pfIsolationR03_sumPhotonEt", muon_pfIsolationR03_sumPhotonEt);
  stream.select("patMuon_slimmedMuons.pfIsolationR03_sumPhotonEtHighThreshold", muon_pfIsolationR03_sumPhotonEtHighThreshold);
  stream.select("patMuon_slimmedMuons.pfIsolationR04_sumChargedHadronPt", muon_pfIsolationR04_sumChargedHadronPt);
  stream.select("patMuon_slimmedMuons.pfIsolationR04_sumChargedParticlePt", muon_pfIsolationR04_sumChargedParticlePt);
  stream.select("patMuon_slimmedMuons.pfIsolationR04_sumNeutralHadronEt", muon_pfIsolationR04_sumNeutralHadronEt);
  stream.select("patMuon_slimmedMuons.pfIsolationR04_sumNeutralHadronEtHighThreshold", muon_pfIsolationR04_sumNeutralHadronEtHighThreshold);
  stream.select("patMuon_slimmedMuons.pfIsolationR04_sumPUPt", muon_pfIsolationR04_sumPUPt);
  stream.select("patMuon_slimmedMuons.pfIsolationR04_sumPhotonEt", muon_pfIsolationR04_sumPhotonEt);
  stream.select("patMuon_slimmedMuons.pfIsolationR04_sumPhotonEtHighThreshold", muon_pfIsolationR04_sumPhotonEtHighThreshold);
  stream.select("patMuon_slimmedMuons.phi", muon_phi);
  stream.select("patMuon_slimmedMuons.pt", muon_pt);
  stream.select("patMuon_slimmedMuons.px", muon_px);
  stream.select("patMuon_slimmedMuons.py", muon_py);
  stream.select("patMuon_slimmedMuons.pz", muon_pz);
  stream.select("nrecoGenParticleHelper2_prunedGenParticles", nGenParticleHelper);
  stream.select("nPileupSummaryInfo_addPileupInfo", nPileupSummaryInfo);
  stream.select("npatElectron_slimmedElectrons", nelectron);
  stream.select("npatJet_slimmedJets", njet);
  stream.select("npatMET_slimmedMETs", nmet2);
  stream.select("npatMuon_slimmedMuons", nmuon);
  stream.select("npatTauHelper_slimmedTaus", ntau);
  stream.select("patTauHelper_slimmedTaus.signalChargedHadrCands_size", ntau_signalChargedHadrCands);
  stream.select("nrecoVertex_offlineSlimmedPrimaryVertices", nvertex);
  stream.select("patTauHelper_slimmedTaus.charge", tau_charge);
  stream.select("patTauHelper_slimmedTaus.energy", tau_energy);
  stream.select("patTauHelper_slimmedTaus.et", tau_et);
  stream.select("patTauHelper_slimmedTaus.eta", tau_eta);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_energy", tau_leadChargedHadrCand_energy);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_et", tau_leadChargedHadrCand_et);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_eta", tau_leadChargedHadrCand_eta);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_mass", tau_leadChargedHadrCand_mass);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_massSqr", tau_leadChargedHadrCand_massSqr);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_mt", tau_leadChargedHadrCand_mt);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_mtSqr", tau_leadChargedHadrCand_mtSqr);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_p", tau_leadChargedHadrCand_p);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_phi", tau_leadChargedHadrCand_phi);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_pt", tau_leadChargedHadrCand_pt);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_px", tau_leadChargedHadrCand_px);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_py", tau_leadChargedHadrCand_py);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_pz", tau_leadChargedHadrCand_pz);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_rapidity", tau_leadChargedHadrCand_rapidity);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_theta", tau_leadChargedHadrCand_theta);
  stream.select("patTauHelper_slimmedTaus.leadChargedHadrCand_y", tau_leadChargedHadrCand_y);
  stream.select("patTauHelper_slimmedTaus.mass", tau_mass);
  stream.select("patTauHelper_slimmedTaus.p", tau_p);
  stream.select("patTauHelper_slimmedTaus.phi", tau_phi);
  stream.select("patTauHelper_slimmedTaus.pt", tau_pt);
  stream.select("patTauHelper_slimmedTaus.px", tau_px);
  stream.select("patTauHelper_slimmedTaus.py", tau_py);
  stream.select("patTauHelper_slimmedTaus.pz", tau_pz);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronLoose", tau_tauID_againstElectronLoose);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronLooseMVA5", tau_tauID_againstElectronLooseMVA5);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronMVA5category", tau_tauID_againstElectronMVA5category);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronMVA5raw", tau_tauID_againstElectronMVA5raw);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronMedium", tau_tauID_againstElectronMedium);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronMediumMVA5", tau_tauID_againstElectronMediumMVA5);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronTight", tau_tauID_againstElectronTight);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronTightMVA5", tau_tauID_againstElectronTightMVA5);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronVLooseMVA5", tau_tauID_againstElectronVLooseMVA5);
  stream.select("patTauHelper_slimmedTaus.tauID_againstElectronVTightMVA5", tau_tauID_againstElectronVTightMVA5);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonLoose", tau_tauID_againstMuonLoose);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonLoose2", tau_tauID_againstMuonLoose2);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonLoose3", tau_tauID_againstMuonLoose3);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonLooseMVA", tau_tauID_againstMuonLooseMVA);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonMVAraw", tau_tauID_againstMuonMVAraw);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonMedium", tau_tauID_againstMuonMedium);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonMedium2", tau_tauID_againstMuonMedium2);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonMediumMVA", tau_tauID_againstMuonMediumMVA);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonTight", tau_tauID_againstMuonTight);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonTight2", tau_tauID_againstMuonTight2);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonTight3", tau_tauID_againstMuonTight3);
  stream.select("patTauHelper_slimmedTaus.tauID_againstMuonTightMVA", tau_tauID_againstMuonTightMVA);
  stream.select("patTauHelper_slimmedTaus.tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits", tau_tauID_byCombinedIsolationDeltaBetaCorrRaw3Hits);
  stream.select("patTauHelper_slimmedTaus.tauID_byIsolationMVA3newDMwLTraw", tau_tauID_byIsolationMVA3newDMwLTraw);
  stream.select("patTauHelper_slimmedTaus.tauID_byIsolationMVA3newDMwoLTraw", tau_tauID_byIsolationMVA3newDMwoLTraw);
  stream.select("patTauHelper_slimmedTaus.tauID_byIsolationMVA3oldDMwLTraw", tau_tauID_byIsolationMVA3oldDMwLTraw);
  stream.select("patTauHelper_slimmedTaus.tauID_byIsolationMVA3oldDMwoLTraw", tau_tauID_byIsolationMVA3oldDMwoLTraw);
  stream.select("patTauHelper_slimmedTaus.tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits", tau_tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_slimmedTaus.tauID_byLooseIsolationMVA3newDMwLT", tau_tauID_byLooseIsolationMVA3newDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byLooseIsolationMVA3newDMwoLT", tau_tauID_byLooseIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byLooseIsolationMVA3oldDMwLT", tau_tauID_byLooseIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byLooseIsolationMVA3oldDMwoLT", tau_tauID_byLooseIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits", tau_tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_slimmedTaus.tauID_byMediumIsolationMVA3newDMwLT", tau_tauID_byMediumIsolationMVA3newDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byMediumIsolationMVA3newDMwoLT", tau_tauID_byMediumIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byMediumIsolationMVA3oldDMwLT", tau_tauID_byMediumIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byMediumIsolationMVA3oldDMwoLT", tau_tauID_byMediumIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byTightCombinedIsolationDeltaBetaCorr3Hits", tau_tauID_byTightCombinedIsolationDeltaBetaCorr3Hits);
  stream.select("patTauHelper_slimmedTaus.tauID_byTightIsolationMVA3newDMwLT", tau_tauID_byTightIsolationMVA3newDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byTightIsolationMVA3newDMwoLT", tau_tauID_byTightIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byTightIsolationMVA3oldDMwLT", tau_tauID_byTightIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byTightIsolationMVA3oldDMwoLT", tau_tauID_byTightIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVLooseIsolationMVA3newDMwLT", tau_tauID_byVLooseIsolationMVA3newDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVLooseIsolationMVA3newDMwoLT", tau_tauID_byVLooseIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVLooseIsolationMVA3oldDMwLT", tau_tauID_byVLooseIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVLooseIsolationMVA3oldDMwoLT", tau_tauID_byVLooseIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVTightIsolationMVA3newDMwLT", tau_tauID_byVTightIsolationMVA3newDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVTightIsolationMVA3newDMwoLT", tau_tauID_byVTightIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVTightIsolationMVA3oldDMwLT", tau_tauID_byVTightIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVTightIsolationMVA3oldDMwoLT", tau_tauID_byVTightIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVVTightIsolationMVA3newDMwLT", tau_tauID_byVVTightIsolationMVA3newDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVVTightIsolationMVA3newDMwoLT", tau_tauID_byVVTightIsolationMVA3newDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVVTightIsolationMVA3oldDMwLT", tau_tauID_byVVTightIsolationMVA3oldDMwLT);
  stream.select("patTauHelper_slimmedTaus.tauID_byVVTightIsolationMVA3oldDMwoLT", tau_tauID_byVVTightIsolationMVA3oldDMwoLT);
  stream.select("patTauHelper_slimmedTaus.tauID_chargedIsoPtSum", tau_tauID_chargedIsoPtSum);
  stream.select("patTauHelper_slimmedTaus.tauID_decayModeFinding", tau_tauID_decayModeFinding);
  stream.select("patTauHelper_slimmedTaus.tauID_decayModeFindingNewDMs", tau_tauID_decayModeFindingNewDMs);
  stream.select("patTauHelper_slimmedTaus.tauID_neutralIsoPtSum", tau_tauID_neutralIsoPtSum);
  stream.select("patTauHelper_slimmedTaus.tauID_puCorrPtSum", tau_tauID_puCorrPtSum);
  stream.select("recoVertex_offlineSlimmedPrimaryVertices.chi2", vertex_chi2);
  stream.select("recoVertex_offlineSlimmedPrimaryVertices.isFake", vertex_isFake);
  stream.select("recoVertex_offlineSlimmedPrimaryVertices.isValid", vertex_isValid);
  stream.select("recoVertex_offlineSlimmedPrimaryVertices.ndof", vertex_ndof);
  stream.select("recoVertex_offlineSlimmedPrimaryVertices.x", vertex_x);
  stream.select("recoVertex_offlineSlimmedPrimaryVertices.y", vertex_y);
  stream.select("recoVertex_offlineSlimmedPrimaryVertices.z", vertex_z);

}
}; // end namespace evt
#endif
