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
	  
	  //fill tau charge and  cosdeltaphi
          inputHistoCollection.h_ditaucharge ->Fill(Inv2t.charge,weight);
          inputHistoCollection.h_ditaucosdeltaphi ->Fill(Inv2t.cosDphi,weight);	
	  inputHistoCollection.h_ditaudeltaeta->Fill(Inv2t.dEta,weight);  
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

} 

#endif
