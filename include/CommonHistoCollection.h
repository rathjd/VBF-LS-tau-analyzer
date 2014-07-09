#ifndef COMMONHISTOCOLLECTION_H
#define COMMONHISTOCOLLECTION_H

#include "methods.h"

void fillHistoCollection (MyHistoCollection &inputHistoCollection, MyEventCollection inputEventCollection, double weight) {

	// ---------------------
	// -- fill histograms --
	// ---------------------	  
	  
	bool verbose=false;  
        //JETS	  
	  
	//find index of leading jets
	pair<unsigned int,unsigned int> jetIndex=LeadingJets(inputEventCollection);  
	  
	//find max value for 2-jet-mass
        MassAndIndex Inv2j = Inv2jMassIndex(inputEventCollection);
	
	//define ht
	double ht_jets=0.;

        //JET SEL
	for (unsigned int j = 0;j<inputEventCollection.jet.size();++j){
	  inputHistoCollection.h_jetpt->Fill(inputEventCollection.jet[j]->pt,weight); //fill jet-pt-histogram
	  inputHistoCollection.h_jeteta->Fill(inputEventCollection.jet[j]->eta,weight); //fill jet-eta-histogram
	  ht_jets+=inputEventCollection.jet[j]->pt; //add up scalar pt to ht
	}
	 
	//fill jet count
        inputHistoCollection.h_njet->Fill( (int)inputEventCollection.jet.size(),weight );
	if(verbose)std::cout<<"Pass selection -> Fill njet="<<inputEventCollection.jet.size()<<", weight="<<weight<<std::endl;

	//fill jet pt indizes
        if (jetIndex.first < 99999)  {
           inputHistoCollection.h_jet1pt->Fill(inputEventCollection.jet[jetIndex.first]->pt,weight);
           inputHistoCollection.h_jet1eta->Fill(inputEventCollection.jet[jetIndex.first]->eta,weight);
        }
        if (jetIndex.second < 99999) {
           inputHistoCollection.h_jet2pt->Fill(inputEventCollection.jet[jetIndex.second]->pt,weight);
           inputHistoCollection.h_jet2eta->Fill(inputEventCollection.jet[jetIndex.second]->eta,weight);
        }

	//fill 2-jet-event inv. mass and eta-difference
        if ( Inv2j.Mass >= 0 ) {
           inputHistoCollection.h_dijetinvariantmass ->Fill(Inv2j.Mass,weight);
           inputHistoCollection.h_dijetdeltaeta ->Fill(Inv2j.dEta,weight);
        }

	//fill ht distribution
	inputHistoCollection.h_ht -> Fill(ht_jets,weight);
	
	//fill jet tau distance distribution
	if(jetIndex.first<99999 && jetIndex.second<99999){
	inputHistoCollection.h_jetTauDistanceFirst->Fill(TauJetMinDistance(inputEventCollection,inputEventCollection.jet[jetIndex.first]->eta, inputEventCollection.jet[jetIndex.first]->phi));
	inputHistoCollection.h_jetTauDistanceSecond->Fill(TauJetMinDistance(inputEventCollection,inputEventCollection.jet[jetIndex.second]->eta, inputEventCollection.jet[jetIndex.second]->phi));	 
	}
//____________________________________________________________________________________________

        //TAUS
	
	//find tau properties
	TauProperties Inv2t = Inv2tMassIndex(inputEventCollection);
	TLorentzVector tau1_4v;
	TLorentzVector tau2_4v;
         
	//set ht of taus to default
	double ht_jetsPtau=ht_jets;
	 
	for(unsigned int t =0;t<inputEventCollection.tau.size();++t){
	  //add up scalar sum of tau pt to ht
	  ht_jetsPtau+=inputEventCollection.tau[t]->pt;
	}

	if ( (Inv2t.first < 99999) && (Inv2t.second < 99999) ) {
	  //determine leading two tau invariant mass
	  inputHistoCollection.h_ditauinvariantmass ->Fill(Inv2t.Mass,weight);
	  
	  //fill tau charge and  cosdeltaphi and deltaeta and 2Dpt-plot
          inputHistoCollection.h_ditaucharge ->Fill(Inv2t.charge,weight);
          inputHistoCollection.h_ditaucosdeltaphi ->Fill(Inv2t.cosDphi,weight);	
	  inputHistoCollection.h_ditaudeltaeta->Fill(Inv2t.dEta,weight);
	  inputHistoCollection.h2_tau1pt_vs_tau2pt->Fill(inputEventCollection.tau[Inv2t.first]->pt,inputEventCollection.tau[Inv2t.second]->pt,weight);   
	}

	//fill tau pt and eta
        if (Inv2t.first < 99999) {
          inputHistoCollection.h_tau1pt->Fill(inputEventCollection.tau[Inv2t.first]->pt,weight);
          inputHistoCollection.h_tau1eta->Fill(inputEventCollection.tau[Inv2t.first]->eta,weight);
        }
        if (Inv2t.second < 99999) {
          inputHistoCollection.h_tau2pt->Fill(inputEventCollection.tau[Inv2t.second]->pt,weight);
          inputHistoCollection.h_tau2eta->Fill(inputEventCollection.tau[Inv2t.second]->eta,weight);
        }
	
	//fill ht with taus included
	inputHistoCollection.h_ht_withtau -> Fill(ht_jetsPtau,weight);

        // MET
        inputHistoCollection.h_met -> Fill(inputEventCollection.met[0]->pt,weight);

        //fill DiJetInvMass_vs_DiJetDEta
        inputHistoCollection.h2_DiJetInvMass_vs_DiJetDEta -> Fill(Inv2j.dEta, Inv2j.Mass,weight);

//________________________________________

	//PU	
	inputHistoCollection.h_NVtx->Fill(inputEventCollection.NVtx, weight);
	inputHistoCollection.h_PU_NumInteractions->Fill(inputEventCollection.PUinteractions, weight);
} 

void fillProfileCollection (MyProfileCollection &inputProfileCollection, MyEventCollection inputEventCollection, double pass) {

	// ---------------------
	// -- fill Profilegrams --
	// ---------------------	  
	  
	bool verbose=false;  
        //JETS	  
	  
	//find index of leading jets
	pair<unsigned int,unsigned int> jetIndex=LeadingJets(inputEventCollection);  
	  
	//find max value for 2-jet-mass
        MassAndIndex Inv2j = Inv2jMassIndex(inputEventCollection);
	
	//define ht
	double ht_jets=0.;

        //JET SEL
	for (unsigned int j = 0;j<inputEventCollection.jet.size();++j){
	  inputProfileCollection.p_jetpt->Fill(inputEventCollection.jet[j]->pt,pass); //fill jet-pt-Profilegram
	  inputProfileCollection.p_jeteta->Fill(inputEventCollection.jet[j]->eta,pass); //fill jet-eta-Profilegram
	  ht_jets+=inputEventCollection.jet[j]->pt; //add up scalar pt to ht
	}
	 
	//fill jet count
        inputProfileCollection.p_njet->Fill( (int)inputEventCollection.jet.size(),pass);
	if(verbose)std::cout<<"Profile selection -> Fill njet="<<inputEventCollection.jet.size()<<", pass="<<pass<<std::endl;

	//fill jet pt indizes
        if (jetIndex.first < 99999)  {
           inputProfileCollection.p_jet1pt->Fill(inputEventCollection.jet[jetIndex.first]->pt,pass);
           inputProfileCollection.p_jet1eta->Fill(inputEventCollection.jet[jetIndex.first]->eta,pass);
        }
        if (jetIndex.second < 99999) {
           inputProfileCollection.p_jet2pt->Fill(inputEventCollection.jet[jetIndex.second]->pt,pass);
           inputProfileCollection.p_jet2eta->Fill(inputEventCollection.jet[jetIndex.second]->eta,pass);
        }

	//fill 2-jet-event inv. mass and eta-difference
        if ( Inv2j.Mass >= 0 ) {
           inputProfileCollection.p_dijetinvariantmass ->Fill(Inv2j.Mass,pass);
           inputProfileCollection.p_dijetdeltaeta ->Fill(Inv2j.dEta,pass);
        }

	//fill ht distribution
	inputProfileCollection.p_ht -> Fill(ht_jets,pass);
	
//____________________________________________________________________________________________

        //TAUS
	
	//find tau properties
	TauProperties Inv2t = Inv2tMassIndex(inputEventCollection);
	TLorentzVector tau1_4v;
	TLorentzVector tau2_4v;
         
	//set ht of taus to default
	double ht_jetsPtau=ht_jets;
	 
	for(unsigned int t =0;t<inputEventCollection.tau.size();++t){
	  //add up scalar sum of tau pt to ht
	  ht_jetsPtau+=inputEventCollection.tau[t]->pt;
	}

	if ( (Inv2t.first < 99999) && (Inv2t.second < 99999) ) {
	  //determine leading two tau invariant mass
	  inputProfileCollection.p_ditauinvariantmass ->Fill(Inv2t.Mass,pass);
	  
	  //fill tau charge and  cosdeltaphi and deltaeta and 2Dpt-plot
          inputProfileCollection.p_ditaucharge ->Fill(Inv2t.charge,pass);
          inputProfileCollection.p_ditaucosdeltaphi ->Fill(Inv2t.cosDphi,pass);	
	  inputProfileCollection.p_ditaudeltaeta->Fill(Inv2t.dEta,pass);
	}

	//fill tau pt and eta
        if (Inv2t.first < 99999) {
          inputProfileCollection.p_tau1pt->Fill(inputEventCollection.tau[Inv2t.first]->pt,pass);
          inputProfileCollection.p_tau1eta->Fill(inputEventCollection.tau[Inv2t.first]->eta,pass);
        }
        if (Inv2t.second < 99999) {
          inputProfileCollection.p_tau2pt->Fill(inputEventCollection.tau[Inv2t.second]->pt,pass);
          inputProfileCollection.p_tau2eta->Fill(inputEventCollection.tau[Inv2t.second]->eta,pass);
        }
	
	//fill ht with taus included
	inputProfileCollection.p_ht_withtau -> Fill(ht_jetsPtau,pass);

        // MET
        inputProfileCollection.p_met -> Fill(inputEventCollection.met[0]->pt,pass);


//________________________________________

	//PU	
	inputProfileCollection.p_NVtx->Fill(inputEventCollection.NVtx, pass);
	inputProfileCollection.p_PU_NumInteractions->Fill(inputEventCollection.PUinteractions, pass);
} 

#endif
