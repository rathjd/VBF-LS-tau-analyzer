#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "analyzer.h"
#include "TProfile.h"

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
        vector <met2_s*> met;
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
		h_jetpt->GetXaxis()->SetTitle("p_{T}^{jet} [GeV]");
		h_jeteta = new TH1F("h_jeteta", "h_jeteta", 30 , -5., 5.);
		h_jeteta->GetXaxis()->SetTitle("#eta^{jet}");
		h_jet1pt = new TH1F("h_jet1pt", "h_jet1pt", 50, 0., 500.);
		h_jet1pt->GetXaxis()->SetTitle("p_{T}^{jet 1} [GeV]");
		h_jet1eta = new TH1F("h_jet1eta", "h_jet1eta", 50 , -5., 5.);
		h_jet1eta->GetXaxis()->SetTitle("#eta^{jet 1}");
		h_jet2pt = new TH1F("h_jet2pt", "h_jet2pt", 50, 0., 500.);
		h_jet2pt->GetXaxis()->SetTitle("p_{T}^{jet 2} [GeV]");
		h_jet2eta = new TH1F("h_jet2eta", "h_jet2eta", 50 , -5., 5.);
		h_jet2eta->GetXaxis()->SetTitle("#eta^{jet 2}");
		h_dijetinvariantmass = new TH1F("h_dijetinvariantmass","h_dijetinvariantmass", 10, 0., 2500.);
		h_dijetinvariantmass->GetXaxis()->SetTitle("M^{(jet,jet)} [GeV]");
		h_dijetdeltaeta = new TH1F ("h_dijetdeltaeta", "h_dijetdeltaeta", 20, 0., 10.);
		h_dijetdeltaeta->GetXaxis()->SetTitle("#Delta#eta^{jj}");

		h_tau1pt = new TH1F("h_tau1pt", "h_tau1pt", 50, 0., 500.);
		h_tau1pt->GetXaxis()->SetTitle("p_{T}^{#tau 1} [GeV]");
		h_tau1eta = new TH1F("h_tau1eta", "h_tau1eta", 30 , -3., 3.);
		h_tau1eta->GetXaxis()->SetTitle("#eta^{#tau 1}");
		h_tau2pt = new TH1F("h_tau2pt", "h_tau2pt", 50, 0., 500.);
		h_tau2pt->GetXaxis()->SetTitle("p_{T}^{#tau 2} [GeV]");
		h_tau2eta = new TH1F("h_tau2eta", "h_tau2eta", 30 , -3., 3.);
		h_tau2eta->GetXaxis()->SetTitle("#eta^{#tau 2}");
		h_ditauinvariantmass = new TH1F("h_ditauinvariantmass", "h_ditauinvariantmass", 50, 0., 500.);
		h_ditauinvariantmass->GetXaxis()->SetTitle("M^{(#tau,#tau)} [GeV]");
		h_ditaucharge = new TH1F("h_ditaucharge", "h_ditaucharge", 5, -4., 6.);
		h_ditaucharge->GetXaxis()->SetTitle("sign(#tau^{1}) #upoint sign(#tau^{2})");
		h_ditaucosdeltaphi = new TH1F("h_ditaucosdeltaphi", "h_ditaucosdeltaphi", 50, -1.1, 1.1);
		h_ditaucosdeltaphi->GetXaxis()->SetTitle("cos(#Delta#phi(#tau,#tau))");
		h_ditaudeltaeta = new TH1F ("h_ditaudeltaeta", "h_ditaudeltaeta", 20, 0., 10.);
		h_ditaudeltaeta->GetXaxis()->SetTitle("#Delta#eta(#tau,#tau)");

		h_met = new TH1F("h_met", "h_met", 24, 0., 240.);
		h_met->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");

		h_ht = new TH1F("h_ht", "h_ht", 50, 0., 1300.);
		h_ht->GetXaxis()->SetTitle("H_{T} [GeV]");
		h_ht_withtau = new TH1F("h_ht_withtau", "h_ht_withtau", 50, 0., 1300.);
		h_ht_withtau->GetXaxis()->SetTitle("H_{T}+#Sigma p_{T}^{#tau} [GeV]");
		
		h_jetTauDistanceFirst = new TH1F("h_jetTauDistanceFirst", "h_jetTauDistanceFirst", 25, 0., 0.5);
		h_jetTauDistanceFirst->GetXaxis()->SetTitle("#DeltaR(jet,#tau^{1})");
		h_jetTauDistanceSecond = new TH1F("h_jetTauDistanceSecond", "h_jetTauDistanceSecond", 25, 0., 0.5);
		h_jetTauDistanceSecond->GetXaxis()->SetTitle("#DeltaR(jet,#tau^{2})");

		h2_DiJetInvMass_vs_DiJetDEta = new TH2F("h2_DiJetInvMass_vs_DiJetDEta","h2_DiJetInvMass_vs_DiJetDEta", 20, 0., 10., 10, 0., 2500.);
		h2_DiJetInvMass_vs_DiJetDEta->GetXaxis()->SetTitle("#Delta#eta^{jj}");
		h2_DiJetInvMass_vs_DiJetDEta->GetYaxis()->SetTitle("M^{(jet,jet)} [GeV]");
		h2_tau1pt_vs_tau2pt = new TH2F("h2_tau1pt_vs_tau2pt","correlation of first and second p_{T}^{#tau}", 50, 0., 500., 50, 0., 500.);
		h2_tau1pt_vs_tau2pt->GetXaxis()->SetTitle("p_{T}^{#tau 1}");
		h2_tau1pt_vs_tau2pt->GetYaxis()->SetTitle("p_{T}^{#tau 2}");
		
		h_NVtx = new TH1F("h_NVtx","number of reco vertices", 100, -0.5,99.5);
		h_NVtx->GetXaxis()->SetTitle("NVtx");
		
		h_PU_NumInteractions = new TH1F("h_PUTrueInteractions","number of in-time true pileup", 100, -0.5,99.5);
		h_PU_NumInteractions->GetXaxis()->SetTitle("NVtx^{true}");
	}
};

struct MyProfileCollection {

	std::string label;
	TProfile* p_count;
	TProfile* p_njet;
	TProfile* p_jetpt;
	TProfile* p_jeteta;
	TProfile* p_jet1pt;
	TProfile* p_jet1eta;
	TProfile* p_jet2pt;
	TProfile* p_jet2eta;
	TProfile* p_dijetinvariantmass;
	TProfile* p_dijetdeltaeta;

	TProfile* p_tau1pt;
	TProfile* p_tau1eta;
	TProfile* p_tau2pt;
	TProfile* p_tau2eta;
	TProfile* p_ditauinvariantmass;
	TProfile* p_ditaucharge;
	TProfile* p_ditaucosdeltaphi;
	TProfile* p_ditaudeltaeta;

	TProfile* p_met;

	TProfile* p_ht;
	TProfile* p_ht_withtau;
	
	TProfile* p_jetTauDistanceFirst;
	TProfile* p_jetTauDistanceSecond;
	
	TProfile* p_NVtx;
	TProfile* p_PU_NumInteractions;

	MyProfileCollection(TFile * f, const std::string & inputlabel) {

		label = inputlabel;
		f->mkdir(inputlabel.c_str());
        	f->cd(inputlabel.c_str());

		p_count = new TProfile("counts", "", 1,0,1);
		p_count->SetBit(TH1::kCanRebin);
		p_count->SetStats(0);
		p_njet = new TProfile("p_njet", "p_njet", 21, -0.5, 20.5);
		p_njet->GetXaxis()->SetTitle("number of jets not matched to #tau");
		p_jetpt = new TProfile("p_jetpt", "p_jetpt", 50, 0., 500.);
		p_jetpt->GetXaxis()->SetTitle("p_{T}^{jet} [GeV]");
		p_jeteta = new TProfile("p_jeteta", "p_jeteta", 30 , -5., 5.);
		p_jeteta->GetXaxis()->SetTitle("#eta^{jet}");
		p_jet1pt = new TProfile("p_jet1pt", "p_jet1pt", 50, 0., 500.);
		p_jet1pt->GetXaxis()->SetTitle("p_{T}^{jet 1} [GeV]");
		p_jet1eta = new TProfile("p_jet1eta", "p_jet1eta", 50 , -5., 5.);
		p_jet1eta->GetXaxis()->SetTitle("#eta^{jet 1}");
		p_jet2pt = new TProfile("p_jet2pt", "p_jet2pt", 50, 0., 500.);
		p_jet2pt->GetXaxis()->SetTitle("p_{T}^{jet 2} [GeV]");
		p_jet2eta = new TProfile("p_jet2eta", "p_jet2eta", 50 , -5., 5.);
		p_jet2eta->GetXaxis()->SetTitle("#eta^{jet 2}");
		p_dijetinvariantmass = new TProfile("p_dijetinvariantmass","p_dijetinvariantmass", 10, 0., 2500.);
		p_dijetinvariantmass->GetXaxis()->SetTitle("M^{(jet,jet)} [GeV]");
		p_dijetdeltaeta = new TProfile ("p_dijetdeltaeta", "p_dijetdeltaeta", 20, 0., 10.);
		p_dijetdeltaeta->GetXaxis()->SetTitle("#Delta#eta^{jj}");

		p_tau1pt = new TProfile("p_tau1pt", "p_tau1pt", 50, 0., 500.);
		p_tau1pt->GetXaxis()->SetTitle("p_{T}^{#tau 1} [GeV]");
		p_tau1eta = new TProfile("p_tau1eta", "p_tau1eta", 30 , -3., 3.);
		p_tau1eta->GetXaxis()->SetTitle("#eta^{#tau 1}");
		p_tau2pt = new TProfile("p_tau2pt", "p_tau2pt", 50, 0., 500.);
		p_tau2pt->GetXaxis()->SetTitle("p_{T}^{#tau 2} [GeV]");
		p_tau2eta = new TProfile("p_tau2eta", "p_tau2eta", 30 , -3., 3.);
		p_tau2eta->GetXaxis()->SetTitle("#eta^{#tau 2}");
		p_ditauinvariantmass = new TProfile("p_ditauinvariantmass", "p_ditauinvariantmass", 50, 0., 500.);
		p_ditauinvariantmass->GetXaxis()->SetTitle("M^{(#tau,#tau)} [GeV]");
		p_ditaucharge = new TProfile("p_ditaucharge", "p_ditaucharge", 5, -4., 6.);
		p_ditaucharge->GetXaxis()->SetTitle("sign(#tau^{1}) #upoint sign(#tau^{2})");
		p_ditaucosdeltaphi = new TProfile("p_ditaucosdeltaphi", "p_ditaucosdeltaphi", 50, -1.1, 1.1);
		p_ditaucosdeltaphi->GetXaxis()->SetTitle("cos(#Delta#phi(#tau,#tau))");
		p_ditaudeltaeta = new TProfile ("p_ditaudeltaeta", "p_ditaudeltaeta", 20, 0., 10.);
		p_ditaudeltaeta->GetXaxis()->SetTitle("#Delta#eta(#tau,#tau)");

		p_met = new TProfile("p_met", "p_met", 24, 0., 240.);
		p_met->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");

		p_ht = new TProfile("p_ht", "p_ht", 50, 0., 1300.);
		p_ht->GetXaxis()->SetTitle("p_{T} [GeV]");
		p_ht_withtau = new TProfile("p_ht_withtau", "p_ht_withtau", 50, 0., 1300.);
		p_ht_withtau->GetXaxis()->SetTitle("p_{T}+#Sigma p_{T}^{#tau} [GeV]");
		
		p_NVtx = new TProfile("p_NVtx","number of reco vertices", 100, -0.5,99.5);
		p_NVtx->GetXaxis()->SetTitle("NVtx");
		
		p_PU_NumInteractions = new TProfile("p_PUTrueInteractions","number of in-time true pileup", 100, -0.5,99.5);
		p_PU_NumInteractions->GetXaxis()->SetTitle("NVtx^{true}");
	}
};

#endif
