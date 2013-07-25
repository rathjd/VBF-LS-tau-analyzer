#ifndef COMMONHISTOCOLLECTION_H
#define COMMONHISTOCOLLECTION_H

#include "methods.h"

void fillHistoCollection (MyHistoCollection &inputHistoCollection, MyEventCollection inputEventCollection, double weight) {

	// ---------------------
	// -- fill histograms --
	// ---------------------	  
	  
	  
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
           double deltaeta =  fabs (inputEventCollection.jet[Inv2j.first]->eta - inputEventCollection.jet[Inv2j.second]->eta);
           inputHistoCollection.h_dijetinvariantmass ->Fill(Inv2j.Mass,weight);
           inputHistoCollection.h_dijetdeltaeta ->Fill(deltaeta,weight);
        }

	//fill ht distribution
	inputHistoCollection.h_ht -> Fill(ht_jets,weight);
	 
//____________________________________________________________________________________________

        //TAUS

	//find index of leading taus
	pair<unsigned int,unsigned int> tauIndex=LeadingTaus(inputEventCollection);
	
	TLorentzVector tau1_4v;
	TLorentzVector tau2_4v;
         
	//set ht of taus to default
	double ht_jetsPtau=ht_jets;
	 
	for(unsigned int t =0;t<inputEventCollection.tau.size();++t){
	  //add up scalar sum of tau pt to ht
	  ht_jetsPtau+=inputEventCollection.tau[t]->pt;
	}

	if ( (tauIndex.first < 99999) && (tauIndex.second < 99999) ) {
	  //determine leading two tau invariant mass
	  inputHistoCollection.h_ditauinvariantmass ->Fill(tauMass(inputEventCollection, tauIndex.first, tauIndex.second),weight);
	  
	  //fill tau charge and  cosdeltaphi
	  pair<double,double> diTauProperties = ChargeCosDeltaPhi(inputEventCollection, tauIndex.first, tauIndex.second);
          inputHistoCollection.h_ditaucharge ->Fill(diTauProperties.first,weight);
          inputHistoCollection.h_ditaucosdeltaphi ->Fill(diTauProperties.second,weight);	  
	}

	//fill tau pt and eta
        if (tauIndex.first < 99999) {
          inputHistoCollection.h_tau1pt->Fill(inputEventCollection.tau[tauIndex.first]->pt,weight);
          inputHistoCollection.h_tau1eta->Fill(inputEventCollection.tau[tauIndex.first]->eta,weight);
        }
        if (tauIndex.second < 99999) {
          inputHistoCollection.h_tau2pt->Fill(inputEventCollection.tau[tauIndex.second]->pt,weight);
          inputHistoCollection.h_tau2eta->Fill(inputEventCollection.tau[tauIndex.second]->eta,weight);
        }
	
	//fill ht with taus included
	inputHistoCollection.h_ht_withtau -> Fill(ht_jetsPtau,weight);

        // MET
        inputHistoCollection.h_met -> Fill(inputEventCollection.met[0]->pt,weight);

} 

#endif
