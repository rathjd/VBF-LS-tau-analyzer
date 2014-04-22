#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "analyzer.h"

using namespace std;
using namespace evt;

struct MassAndIndex {
	std::string label;
	unsigned int first;
	unsigned int second;
	double Mass;
	double dR;
	int signEta;
	double dEta;
	
	MassAndIndex (const std::string & inputlabel){
	  label = inputlabel;
	  first = 99999;
	  second = 99999;
	  Mass = -1.;
	  dR = 0.;
	  signEta = 1;
	  dEta = 0;
	}
};

struct TauProperties {
	std::string label;
	unsigned int first;
	unsigned int second;
	double Mass;
	double dR;
	double dEta;
	double cosDphi;
	int charge;
	
	TauProperties (const std::string & inputlabel){
	  label = inputlabel;
	  first = 99999;
	  second = 99999;
	  Mass = -1.;
	  dR = 0.;
	  dEta=0.;
	  cosDphi = 1;
	  charge = -1;
	}
};

struct MyEventCollection {

        std::string label;
        bool goodVertex;
	bool passedTrigger;
        vector <electron_s*> electron;
	vector <muon_s*> muon;
	vector <tau_s*> tau;
	vector <jet_s*> jet;
	vector <jet_s*> bjet;
        vector <met_s*> met;
	int NVtx;
	int PUinteractions;

	MyEventCollection(const std::string & inputlabel) {
		label = inputlabel;
                goodVertex = false;
                passedTrigger = false;
	}
	void clear() {
                goodVertex = false;
                passedTrigger = false;
		electron.clear();
		muon.clear();
		tau.clear();
		jet.clear();
		bjet.clear();
		met.clear();
	}
};

struct MyHistoCollection {

	std::string label;
	TH1F* h_count;
	TH1F* h_njet;
	TH1F* h_jetpt;
	TH1F* h_jeteta;
	TH1F* h_jet1pt;
	TH1F* h_jet1eta;
	TH1F* h_jet2pt;
	TH1F* h_jet2eta;
	TH1F* h_dijetinvariantmass;
	TH1F* h_dijetdeltaeta;

	TH1F* h_tau1pt;
	TH1F* h_tau1eta;
	TH1F* h_tau2pt;
	TH1F* h_tau2eta;
	TH1F* h_ditauinvariantmass;
	TH1F* h_ditaucharge;
	TH1F* h_ditaucosdeltaphi;
	TH1F* h_ditaudeltaeta;

	TH1F* h_met;

	TH1F* h_ht;
	TH1F* h_ht_withtau;
	
	TH1F* h_jetTauDistanceFirst;
	TH1F* h_jetTauDistanceSecond;

	TH2F* h2_DiJetInvMass_vs_DiJetDEta;
	TH2F* h2_tau1pt_vs_tau2pt;
	
	TH1F* h_NVtx;
	TH1F* h_PU_NumInteractions;

	MyHistoCollection(TFile * f, const std::string & inputlabel) {

		label = inputlabel;
		f->mkdir(inputlabel.c_str());
        	f->cd(inputlabel.c_str());

		h_count = new TH1F("counts", "", 1,0,1);
		h_count->SetBit(TH1::kCanRebin);
		h_count->SetStats(0);
		h_njet = new TH1F("h_njet", "h_njet", 21, -0.5, 20.5);
		h_njet->GetXaxis()->SetTitle("number of jets not matched to #tau");
		h_jetpt = new TH1F("h_jetpt", "h_jetpt", 50, 0., 500.);
		h_jetpt->GetXaxis()->SetTitle("p_{T}^{jet}");
		h_jeteta = new TH1F("h_jeteta", "h_jeteta", 30 , -5., 5.);
		h_jeteta->GetXaxis()->SetTitle("#eta^{jet}");
		h_jet1pt = new TH1F("h_jet1pt", "h_jet1pt", 50, 0., 500.);
		h_jet1pt->GetXaxis()->SetTitle("p_{T}^{jet 1}");
		h_jet1eta = new TH1F("h_jet1eta", "h_jet1eta", 50 , -5., 5.);
		h_jet1eta->GetXaxis()->SetTitle("#eta^{jet 1}");
		h_jet2pt = new TH1F("h_jet2pt", "h_jet2pt", 50, 0., 500.);
		h_jet2pt->GetXaxis()->SetTitle("p_{T}^{jet 2}");
		h_jet2eta = new TH1F("h_jet2eta", "h_jet2eta", 50 , -5., 5.);
		h_jet2eta->GetXaxis()->SetTitle("#eta^{jet 2}");
		h_dijetinvariantmass = new TH1F("h_dijetinvariantmass","h_dijetinvariantmass", 10, 0., 2500.);
		h_dijetdeltaeta = new TH1F ("h_dijetdeltaeta", "h_dijetdeltaeta", 20, 0., 10.);
		h_dijetdeltaeta->GetXaxis()->SetTitle("#Delta#eta^{jj}");

		h_tau1pt = new TH1F("h_tau1pt", "h_tau1pt", 50, 0., 500.);
		h_tau1eta = new TH1F("h_tau1eta", "h_tau1eta", 30 , -3., 3.);
		h_tau2pt = new TH1F("h_tau2pt", "h_tau2pt", 50, 0., 500.);
		h_tau2eta = new TH1F("h_tau2eta", "h_tau2eta", 30 , -3., 3.);
		h_ditauinvariantmass = new TH1F("h_ditauinvariantmass", "h_ditauinvariantmass", 50, 0., 500.);
		h_ditaucharge = new TH1F("h_ditaucharge", "h_ditaucharge", 5, -4., 6.);
		h_ditaucosdeltaphi = new TH1F("h_ditaucosdeltaphi", "h_ditaucosdeltaphi", 50, -1.1, 1.1);
		h_ditaudeltaeta = new TH1F ("h_ditaudeltaeta", "h_ditaudeltaeta", 20, 0., 10.);

		h_met = new TH1F("h_met", "h_met", 24, 0., 240.);

		h_ht = new TH1F("h_ht", "h_ht", 50, 0., 1300.);
		h_ht_withtau = new TH1F("h_ht_withtau", "h_ht_withtau", 50, 0., 1300.);
		
		h_jetTauDistanceFirst = new TH1F("h_jetTauDistanceFirst", "h_jetTauDistanceFirst", 25, 0., 0.5);
		h_jetTauDistanceSecond = new TH1F("h_jetTauDistanceSecond", "h_jetTauDistanceSecond", 25, 0., 0.5);

		h2_DiJetInvMass_vs_DiJetDEta = new TH2F("h2_DiJetInvMass_vs_DiJetDEta","h2_DiJetInvMass_vs_DiJetDEta", 20, 0., 10., 10, 0., 2500.);
		h2_tau1pt_vs_tau2pt = new TH2F("h2_tau1pt_vs_tau2pt","correlation of first and second p_{T}^{#tau}", 50, 0., 500., 50, 0., 500.);
		h2_tau1pt_vs_tau2pt->GetXaxis()->SetTitle("p_{T}^{#tau 1}");
		h2_tau1pt_vs_tau2pt->GetYaxis()->SetTitle("p_{T}^{#tau 2}");
		
		h_NVtx = new TH1F("h_NVtx","number of reco vertices", 100, -0.5,99.5);
		h_PU_NumInteractions = new TH1F("h_PU_NumInteractions","number of in-time pileup", 100, -0.5,99.5);
	}
};

#endif
