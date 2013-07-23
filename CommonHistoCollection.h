#ifndef COMMONHISTOCOLLECTION_H
#define COMMONHISTOCOLLECTION_H


#include "analyzer.h"

using namespace std;

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

void fillHistoCollection (MyHistoCollection &inputHistoCollection, MyEventCollection inputEventCollection) {

	// ---------------------
	// -- fill histograms --
	// ---------------------	  
	  
	  
        //JETS	  
	  
	//set indizes and pt-values for jets to default values
        unsigned int temp_jet1index = 99999;
        unsigned int temp_jet2index = 99999;	  
        double temp_jet1_pt = -99999.;
        double temp_jet2_pt = -99999.;
	  
	//set default value for 2-jet-mass
	double invmassDiJet = 0.;
        unsigned int temp_jet1index_m = 99999;
        unsigned int temp_jet2index_m = 99999;
	TLorentzVector jet1_4v;
        TLorentzVector jet2_4v;
	
	//define ht
	double ht_jets=0.;

        //JET SEL
	for (unsigned int j = 0;j<inputEventCollection.jet.size();++j){
		inputHistoCollection.h_jetpt->Fill(inputEventCollection.jet[j]->pt); //fill jet-pt-histogram
		inputHistoCollection.h_jeteta->Fill(inputEventCollection.jet[j]->eta); //fill jet-eta-histogram
		
		//find first leading jet in pt
		if (temp_jet1_pt < inputEventCollection.jet[j]->pt){
			if(temp_jet2_pt < temp_jet1_pt){temp_jet2_pt=temp_jet1_pt; temp_jet2index=temp_jet1_index;} //if second jet has less pt than the hitherto first jet, replace it
			temp_jet1index = j;
			temp_jet1_pt = inputEventCollection.jet[j]->pt;
		}
		//find second leading jet in pt
                if ( (temp_jet2_pt < inputEventCollection.jet[j]->pt) && (temp_jet1_pt > inputEventCollection.jet[j]->pt)) {temp_jet2index = j; temp_jet2_pt = inputEventCollection.jet[j]->pt;} 
		
		
		
		//do all 2-jet-combinations
		for (unsigned int j2 = 0;j2<j;++j2){
 
	        	jet1_4v.SetPtEtaPhiE(inputEventCollection.jet[j]->pt, inputEventCollection.jet[j]->eta, inputEventCollection.jet[j]->phi, inputEventCollection.jet[j]->energy);
	        	jet2_4v.SetPtEtaPhiE(inputEventCollection.jet[j2]->pt, inputEventCollection.jet[j2]->eta, inputEventCollection.jet[j2]->phi, inputEventCollection.jet[j2]->energy);

            		TLorentzVector dijet_4v = jet1_4v + jet2_4v;

			double temp_invmassDiJet =  dijet_4v.M(); 
			//find highest 2-jet-inv. mass
			if (     invmassDiJet < temp_invmassDiJet   ) {invmassDiJet = temp_invmassDiJet; temp_jet1index_m = j; temp_jet2index_m = j2;}

		}
		
		//add up scalar pt to ht
	        ht_jets+=inputEventCollection.jet[j]->pt;
         }
	 

	 //fill jet count
         inputHistoCollection.h_njet->Fill( (int)inputEventCollection.jet.size() );

	 //fill jet pt indizes
         if (temp_jet1index < 99999) {
             inputHistoCollection.h_jet1pt->Fill(inputEventCollection.jet[temp_jet1index]->pt);
             inputHistoCollection.h_jet1eta->Fill(inputEventCollection.jet[temp_jet1index]->eta);
          }
         if (temp_jet2index < 99999) {
            inputHistoCollection.h_jet2pt->Fill(inputEventCollection.jet[temp_jet2index]->pt);
            inputHistoCollection.h_jet2eta->Fill(inputEventCollection.jet[temp_jet2index]->eta);
         }


	 //fill 2-jet-event inv. mass and eta-difference
         if ( (temp_jet1index_m < 99999) && (temp_jet2index_m < 99999) ) {

            double deltaeta =  fabs (inputEventCollection.jet[temp_jet1index_m]->eta - inputEventCollection.jet[temp_jet2index_m]->eta);
            inputHistoCollection.h_dijetinvariantmass ->Fill(invmassDiJet);
            inputHistoCollection.h_dijetdeltaeta ->Fill(deltaeta);

         }

	 //fill ht distribution
	 inputHistoCollection.h_ht -> Fill(ht_jets);
	 
//____________________________________________________________________________________________

         //TAUS

         //set indizes and pt-values for taus to default values
	 unsigned int temp_tau1index = 99999;
	 unsigned int temp_tau2index = 99999;
	 double temp_tau1_pt = -99999.;
	 double temp_tau2_pt = -99999.;
	 TLorentzVector tau1_4v;
	 TLorentzVector tau2_4v;
         
	 //set ht of taus to default
	 double ht_jetsPtau=ht_jets;
	 
	 for(unsigned int t =0;t<inputEventCollection.tau.size();++t){
	    //find two leading taus in pt
	    if (temp_tau1_pt < inputEventCollection.tau[t]->pt) {
	    	if(temp_tau2_pt < temp_tau1_pt){temp_tau2_pt=temp_tau1_pt; temp_tau2index=temp_tau1_index;} //if second tau has less pt than the hitherto first tau, replace it
	    	temp_tau1index = t; 
	    	temp_tau1_pt = inputEventCollection.tau[t]->pt;
	    } 
            if ( (temp_tau2_pt < inputEventCollection.tau[t]->pt) && ( temp_tau1_pt > inputEventCollection.tau[t]->pt) ) {temp_tau2index = t; temp_tau2_pt = inputEventCollection.tau[t]->pt;} 
	    
	    //add up scalar sum of tau pt to ht
	    ht_jetsPtau+=inputEventCollection.tau[t]->pt;
	 }

         //determine leading two tau invariant mass
	 double invmassDiTau = 99999.;

	 if ( (temp_tau1index < 99999) && (temp_tau2index < 99999) ) {

 
	      tau1_4v.SetPtEtaPhiE(inputEventCollection.tau[temp_tau1index]->pt, inputEventCollection.tau[temp_tau1index]->eta, inputEventCollection.tau[temp_tau1index]->phi, inputEventCollection.tau[temp_tau1index]->energy);
	      tau2_4v.SetPtEtaPhiE(inputEventCollection.tau[temp_tau2index]->pt, inputEventCollection.tau[temp_tau2index]->eta, inputEventCollection.tau[temp_tau2index]->phi, inputEventCollection.tau[temp_tau2index]->energy);

	      TLorentzVector ditau_4v = tau1_4v + tau2_4v;

	      invmassDiTau = ditau_4v.M();
	      inputHistoCollection.h_ditauinvariantmass ->Fill(invmassDiTau);
	 }

	 //fill tau pt and eta
         if (temp_tau1index < 99999) {
              inputHistoCollection.h_tau1pt->Fill(inputEventCollection.tau[temp_tau1index]->pt);
              inputHistoCollection.h_tau1eta->Fill(inputEventCollection.tau[temp_tau1index]->eta);
         }
         if (temp_tau2index < 99999) {
              inputHistoCollection.h_tau2pt->Fill(inputEventCollection.tau[temp_tau2index]->pt);
              inputHistoCollection.h_tau2eta->Fill(inputEventCollection.tau[temp_tau2index]->eta);
         }

         //fill tau charge and  cosdeltaphi
         if ( (temp_tau1index < 99999) && (temp_tau2index < 99999) ) {

              double chargeDiTau = inputEventCollection.tau[temp_tau1index]->charge * inputEventCollection.tau[temp_tau2index]->charge;
              double cosdeltaphiDiTau = cos(tau1_4v.DeltaPhi(tau2_4v));
	      
              inputHistoCollection.h_ditaucharge ->Fill(chargeDiTau);
              inputHistoCollection.h_ditaucosdeltaphi ->Fill(cosdeltaphiDiTau);

         }
	
	//fill ht with taus included
	inputHistoCollection.h_ht_withtau -> Fill(ht_jetsPtau);

        // MET

        inputHistoCollection.h_met -> Fill(inputEventCollection.met[0]->pt);

} 

#endif
