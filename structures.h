#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "analyzer.h"

using namespace std;

struct MassAndIndex {
	std::string label;
	unsigned int first;
	unsigned int second;
	double Mass;
	
	MassAndIndex (const std::string & inputlabel){
	  label = inputlabel;
	  first = 99999;
	  second = 99999;
	  Mass =0.;
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

	TH1F* h_met;

	TH1F* h_ht;
	TH1F* h_ht_withtau;

	MyHistoCollection(TFile * f, const std::string & inputlabel) {

		label = inputlabel;
		f->mkdir(inputlabel.c_str());
        	f->cd(inputlabel.c_str());

		h_count = new TH1F("counts", "", 1,0,1);
		h_count->SetBit(TH1::kCanRebin);
		h_count->SetStats(0);
		h_njet = new TH1F("h_njet", "h_njet", 21, -0.5, 20.5);
		h_jetpt = new TH1F("h_jetpt", "h_jetpt", 50, 0., 500.);
		h_jeteta = new TH1F("h_jeteta", "h_jeteta", 30 , -5., 5.);
		h_jet1pt = new TH1F("h_jet1pt", "h_jet1pt", 50, 0., 500.);
		h_jet1eta = new TH1F("h_jet1eta", "h_jet1eta", 50 , -5., 5.);
		h_jet2pt = new TH1F("h_jet2pt", "h_jet2pt", 50, 0., 500.);
		h_jet2eta = new TH1F("h_jet2eta", "h_jet2eta", 50 , -5., 5.);
		h_dijetinvariantmass = new TH1F("h_dijetinvariantmass","h_dijetinvariantmass", 50, 0., 2750.);
		h_dijetdeltaeta = new TH1F ("h_dijetdeltaeta", "h_dijetdeltaeta", 20, 0., 10.);

		h_tau1pt = new TH1F("h_tau1pt", "h_tau1pt", 50, 0., 500.);
		h_tau1eta = new TH1F("h_tau1eta", "h_tau1eta", 30 , -3., 3.);
		h_tau2pt = new TH1F("h_tau2pt", "h_tau2pt", 50, 0., 500.);
		h_tau2eta = new TH1F("h_tau2eta", "h_tau2eta", 30 , -3., 3.);
		h_ditauinvariantmass = new TH1F("h_ditauinvariantmass", "h_ditauinvariantmass", 20, 0., 140.);
		h_ditaucharge = new TH1F("h_ditaucharge", "h_ditaucharge", 5, -4., 6.);
		h_ditaucosdeltaphi = new TH1F("h_ditaucosdeltaphi", "h_ditaucosdeltaphi", 50, -1.1, 1.1);

		h_met = new TH1F("h_met", "h_met", 6, 0., 120.);

		h_ht = new TH1F("h_ht", "h_ht", 50, 0., 1300.);
		h_ht_withtau = new TH1F("h_ht_withtau", "h_ht_withtau", 50, 0., 1300.);
	}
};

#endif
