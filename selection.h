#ifndef SELECTION_H
#define SELECTION_H

#include "methods.h"
#include "structures.h"
#include "CommonHistoCollection.h"

struct Selection {
	std::string label;
	MyEventCollection *InputCollection;
	MyHistoCollection *OutputCollection;
	bool RealData;
	bool RunData;
	int NumberTauMin;
	int NumberTauMax;
	float DiTauDeltaRmin;
	float DiTauInvMassMin;
	float DiTauInvMassMax;
	float DiTauSign;
	int Btag;
	float JetEtaMax;
	float LeadJetPtMin;
	float LeadJetPtMax;
	float SubLeadJetPtMin;
	float SubLeadJetPtMax;
	float DiJetDrMin;
	float DiJetDrMax;
	float DiJetInvMassMin;
	float DiJetInvMassMax;
	int DiJetSignEta;
	float DiJetDetaMin;
	float DiJetDetaMax;
	float weight;
	bool invertJetRequirements;
	bool invertTauRequirements;
	bool invertTauProperties;
	bool invertDijetProperties;
	bool invertBtagRequirement;
	
	Selection (const std::string & inputlabel){
	  label = inputlabel;
	  RealData = true;
	  RunData = false;
	  NumberTauMin = 2;
	  NumberTauMax = -1;
	  DiTauDeltaRmin = 0.3;
	  DiTauInvMassMin = -1;
	  DiTauInvMassMax = -1;
	  DiTauSign = -1;
	  Btag = 0;
	  JetEtaMax = 5.;
	  LeadJetPtMin = 75.;
	  LeadJetPtMax = -1;
	  SubLeadJetPtMin = 50;
	  SubLeadJetPtMax = -1;
	  DiJetDrMin = 0.3;
	  DiJetDrMax = -1;
	  DiJetInvMassMin = 700;
	  DiJetInvMassMax = -1;
	  DiJetSignEta = -1;
	  DiJetDetaMin = 4.2;
	  DiJetDetaMin = -1;
	  weight = 0;
	  invertJetRequirements = false;
	  invertTauRequirements = false;
	  invertTauProperties = false;
	  invertDijetProperties = false;
	  invertBtagRequirement = false;
	}
	
	void select() {
	  (*OutputCollection).h_count->Fill("NoCuts",0);
	  if(RealData)(*OutputCollection).h_count->Fill("TriggerRequirement",0);
	  if(invertTauRequirements){
	    if(NumberTauMin >= 0)(*OutputCollection).h_count->Fill("InverseAtLeastNtaus",0);
	    if(NumberTauMax >= 0)(*OutputCollection).h_count->Fill("InverseAtMostNtaus",0);
	  }
	  else{
	    if(NumberTauMin >= 0)(*OutputCollection).h_count->Fill("AtLeastNtaus",0);
	    if(NumberTauMax >= 0)(*OutputCollection).h_count->Fill("AtMostNtaus",0);
	  }
	  if(invertTauProperties){
	    if(DiTauDeltaRmin > 0)(*OutputCollection).h_count->Fill("InverseDiTauDeltaRCut", 0);
	    if(DiTauInvMassMin > 0) (*OutputCollection).h_count->Fill("InverseDiTauInvMassMinCut", 0);
	    if(DiTauInvMassMax > 0) (*OutputCollection).h_count->Fill("InverseDiTauInvMassMaxCut", 0);
	    if(DiTauSign !=0)(*OutputCollection).h_count->Fill("InverseDiTauSignCut",0);
	  }
	  else{
	    if(DiTauDeltaRmin > 0)(*OutputCollection).h_count->Fill("DiTauDeltaRCut", 0);
	    if(DiTauInvMassMin > 0) (*OutputCollection).h_count->Fill("DiTauInvMassMinCut", 0);
	    if(DiTauInvMassMax > 0) (*OutputCollection).h_count->Fill("DiTauInvMassMaxCut", 0);
	    if(DiTauSign !=0)(*OutputCollection).h_count->Fill("DiTauSignCut",0);	  
	  }
	  if(invertBtagRequirement && Btag >= 0) (*OutputCollection).h_count->Fill("InverseNoBTag",0);
	  else if(Btag >= 0) (*OutputCollection).h_count->Fill("NoBTag",0);
	  if(invertJetRequirements){
	    if(LeadJetPtMin > 0 || LeadJetPtMax > 0) (*OutputCollection).h_count->Fill("InverseLeadJetCut",0);
	    if(SubLeadJetPtMin > 0 || SubLeadJetPtMax > 0) (*OutputCollection).h_count->Fill("InverseSecondJetCut",0);
	  }
	  else{
	    if(LeadJetPtMin > 0 || LeadJetPtMax > 0) (*OutputCollection).h_count->Fill("LeadJetCut",0);
	    if(SubLeadJetPtMin > 0 || SubLeadJetPtMax > 0) (*OutputCollection).h_count->Fill("SecondJetCut",0);	  
	  }
	  if(invertDijetProperties){
	    if(DiJetDrMin > 0 || DiJetDrMax > 0)(*OutputCollection).h_count->Fill("InverseDiJetDeltaRCut",0);
	    if(DiJetInvMassMin > 0 || DiJetInvMassMax > 0)(*OutputCollection).h_count->Fill("InverseDiJetInvMassCut",0);
	    if(DiJetSignEta != 0)(*OutputCollection).h_count->Fill("InverseDiJetEtaSignCut",0);
	    if(DiJetDetaMin > 0 || DiJetDetaMax > 0)(*OutputCollection).h_count->Fill("InverseDiJetEtaCut",0);
	  }
	  else{
	    if(DiJetDrMin > 0 || DiJetDrMax > 0)(*OutputCollection).h_count->Fill("DiJetDeltaRCut",0);
	    if(DiJetInvMassMin > 0 || DiJetInvMassMax > 0)(*OutputCollection).h_count->Fill("DiJetInvMassCut",0);
	    if(DiJetSignEta != 0)(*OutputCollection).h_count->Fill("DiJetEtaSignCut",0);
	    if(DiJetDetaMin > 0 || DiJetDetaMax > 0)(*OutputCollection).h_count->Fill("DiJetEtaCut",0);	  
	  }
	  
	  if(!RunData && RealData)	 					return; //check if sample is real data and whether you want to run on real data
	  else (*OutputCollection).h_count->Fill("NoCuts",weight);
	  
	  if(RealData		&& !(*InputCollection).passedTrigger) 		return; //check on trigger pass, if sample is real data
	  else if(RealData) (*OutputCollection).h_count->Fill("TriggerRequirement",weight);
	  
	  //Tau requirements
	  
	  if(NumberTauMin >= 0){
	    if(!((int)(*InputCollection).tau.size() >= NumberTauMin)){			//check if there is at least 1 tau in the event
	      if(invertTauRequirements) {
	        (*OutputCollection).h_count->Fill("InverseAtLeastNtaus",1);
		fillHistoCollection((*OutputCollection), (*InputCollection), weight);
		return;
	      }
	      else return;
	    }
	    else if(!invertTauRequirements) (*OutputCollection).h_count->Fill("AtLeastNtaus",1);
	  }
	  
	  if(NumberTauMax >= 0){
	    if(!((int)(*InputCollection).tau.size()  < NumberTauMax)){	 		//check if there are at least 2 taus in the event
	      if(invertTauRequirements) {
	        (*OutputCollection).h_count->Fill("InverseAtMostNtaus",1);
		fillHistoCollection((*OutputCollection), (*InputCollection), weight);
		return;
	      }
	      else return;
	    }
	    else if(!invertTauRequirements) (*OutputCollection).h_count->Fill("AtMostNtaus",weight);
	  }
	  
	  //find ditau properties
	  TauProperties Inv2t = Inv2tMassIndex((*InputCollection));

	  if(DiTauDeltaRmin > 0){
	    if(!(Inv2t.dR 	> 	DiTauDeltaRmin)){ 			 	//check minimal distance between two taus
	      if(invertTauProperties) {
	        (*OutputCollection).h_count->Fill("InverseDiTauDeltaRCut", 1);
		fillHistoCollection((*OutputCollection), (*InputCollection), weight);
		return;
	      }
	      else return;
	    }
	    else if(!invertTauProperties) (*OutputCollection).h_count->Fill("DiTauDeltaRCut", 1);
	  }
	  
	  if(DiTauInvMassMin > 0){
	    if(!(Inv2t.Mass >= DiTauInvMassMin)){					//check minimal ditau mass
	      if(invertTauProperties){
	        (*OutputCollection).h_count->Fill("InverseDiTauInvMassMinCut", 1);
		fillHistoCollection((*OutputCollection), (*InputCollection), weight);
		return;
	      }
	      else return;
	    }
	    else if(!invertTauProperties) (*OutputCollection).h_count->Fill("DiTauInvMassMinCut", 1);
	  }
	  ;
	  if(DiTauInvMassMax > 0){
	    if(!(Inv2t.Mass < DiTauInvMassMax)){					//check maximum ditau mass
	      if(invertTauProperties){
	        (*OutputCollection).h_count->Fill("InverseDiTauInvMassMaxCut", 1);
		fillHistoCollection((*OutputCollection), (*InputCollection), weight);
		return;
	      }
	      else return;
	    }
	    else if(!invertTauProperties) (*OutputCollection).h_count->Fill("DiTauInvMassMaxCut", 1);
	  }	  
	  
	  if(DiTauSign !=0){
	    if(!(Inv2t.charge 	== 	DiTauSign)){ 					//check ditau sign
	      if(invertTauProperties) {
	        (*OutputCollection).h_count->Fill("InverseDiTauSignCut",1);
		fillHistoCollection((*OutputCollection), (*InputCollection), weight);
		return;
	      }
	      else return;
	    }
	    else if(!invertTauProperties) (*OutputCollection).h_count->Fill("DiTauSignCut",1);
	  }
	  
	  if(Btag >= 0){
	    if(!(Btag 		==	(int)(*InputCollection).bjet.size())){		//check number of btagged jets
	      if(invertBtagRequirement){
	        (*OutputCollection).h_count->Fill("InverseNoBTag",weight);
		fillHistoCollection((*OutputCollection), (*InputCollection), weight);
		return;
	      }
	      else return;
	    }
	    else if(!invertBtagRequirement) (*OutputCollection).h_count->Fill("NoBTag",weight);
	  }
	  
	  //find index of leading jets
	  pair<unsigned int,unsigned int> jetIndex=LeadingJets((*InputCollection));
	  
	  if(jetIndex.first==99999 || jetIndex.second==99999) return;
	  
	  //LeadJet
	  double leadJetPt = (*InputCollection).jet[jetIndex.first]->pt;
	  double leadJetEta = (*InputCollection).jet[jetIndex.first]->eta;
	  //SubLeadJet
	  double subLeadJetPt = (*InputCollection).jet[jetIndex.second]->pt;
	  double subLeadJetEta = (*InputCollection).jet[jetIndex.second]->eta;
	  
	  bool leadJet = true;
	  bool subLeadJet = true;
	  if(JetEtaMax > 0){							//check jet eta requirements
	    if(!(fabs(leadJetEta)	<	JetEtaMax))			leadJet = false;
	    if(!(fabs(subLeadJetEta)	<	JetEtaMax))			subLeadJet = false;
	  }
	  if((!leadJet || !subLeadJet) && invertJetRequirements) return;
	  
	  //check jet pt requirements
	  if(LeadJetPtMin > 0){
	    if(!(leadJetPt		>=	LeadJetPtMin))			leadJet = false;
	  }
	  
	  if(LeadJetPtMax > 0){
	    if(!(leadJetPt		<	LeadJetPtMax))			leadJet = false;
	  }
	  	  
	  if(!leadJet){
	    if(invertJetRequirements){
	      (*OutputCollection).h_count->Fill("InverseLeadJetCut",1);
	      fillHistoCollection((*OutputCollection), (*InputCollection), weight);
	      return;
	    }
	    else return;
	  }
	  else if(!invertJetRequirements) (*OutputCollection).h_count->Fill("LeadJetCut",1);
	  
	  if(SubLeadJetPtMin > 0){
	    if(!(subLeadJetPt		>=	SubLeadJetPtMin))		subLeadJet = false;
	  }
	  
	  if(SubLeadJetPtMax > 0){
	    if(!(subLeadJetPt		<	SubLeadJetPtMax))		subLeadJet = false;
	  }

	  if(!subLeadJet){
	    if(invertJetRequirements){
	      (*OutputCollection).h_count->Fill("InverseSecondJetCut",weight);
	      fillHistoCollection((*OutputCollection), (*InputCollection), weight);
	      return;
	    }
	    else return;
	  }
	  else if(!invertJetRequirements) (*OutputCollection).h_count->Fill("SecondJetCut",weight);
	  
	  //find properties of dijet-system
          MassAndIndex Inv2j = Inv2jMassIndex((*InputCollection));
	  
	  bool DiJetDr = true;
	  if(DiJetDrMin > 0){
	    if(!(Inv2j.dR		>=	DiJetDrMin)) 			DiJetDr = false; //check dijet separation
	  }
	  
	  if(DiJetDrMax > 0){
	    if(!(Inv2j.dR		<	DiJetDrMax)) 			DiJetDr = false; //check dijet separation
	  }	  
	  
	  if(!DiJetDr){
	    if(invertDijetProperties){
	      (*OutputCollection).h_count->Fill("InverseDiJetDeltaRCut",weight);
	      fillHistoCollection((*OutputCollection), (*InputCollection), weight);
	      return;
	    }
	    else return;
	  }
	  else if(!invertDijetProperties) (*OutputCollection).h_count->Fill("DiJetDeltaRCut",weight);
	  
	  bool DiJetMass = true;
	  if(DiJetInvMassMin > 0){
	    if(!(Inv2j.Mass		>	DiJetInvMassMin))		DiJetMass = false; //check minimal dijet inv. mass
	  }
	  
	  if(DiJetInvMassMax > 0){
	    if(!(Inv2j.Mass		<=	DiJetInvMassMax))		DiJetMass = false; //check maximum dijet inv. mass
	  }
	  
	  if(!DiJetMass){
	    if(invertDijetProperties){
	      (*OutputCollection).h_count->Fill("InverseDiJetInvMassCut",weight);
	      fillHistoCollection((*OutputCollection), (*InputCollection), weight);
	      return;
	    }
	    else return;
	  }
	  else if(!invertDijetProperties) (*OutputCollection).h_count->Fill("DiJetInvMassCut",weight);
	  
	  if(DiJetSignEta != Inv2j.signEta){					//check whether jets go in opposite directions in the detector
	    if(invertDijetProperties) {
	      (*OutputCollection).h_count->Fill("InverseDiJetEtaSignCut",weight);
	      fillHistoCollection((*OutputCollection), (*InputCollection), weight);
	      return;
	    }
	    else return; 
	  }
	  else if(!invertDijetProperties) (*OutputCollection).h_count->Fill("DiJetEtaSignCut",weight);
	  
	  bool DiJetDeta = true;
	  if(DiJetDetaMin > 0){
	    if(!(Inv2j.dEta		>	DiJetDetaMin))			DiJetDeta = false; //check eta separation of jets
	  }
	  
	  if(DiJetDetaMax > 0){
	    if(!(Inv2j.dEta		<=	DiJetDetaMax))			DiJetDeta = false; //check eta separation of jets
	  }	  
	  
	  if(!DiJetDeta){
	    if(invertDijetProperties) {
	      (*OutputCollection).h_count->Fill("InverseDiJetDetaCut",weight);
	      fillHistoCollection((*OutputCollection), (*InputCollection), weight);
	      return;
	    }
	    else return;
	  }  
	  else if(!invertDijetProperties) (*OutputCollection).h_count->Fill("DiJetDetaCut",weight);
	  
	  fillHistoCollection((*OutputCollection), (*InputCollection), weight);
	}
};

#endif
