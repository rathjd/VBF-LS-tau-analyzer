#ifndef METHODS_H
#define METHODS_H

#include "structures.h"

//-----------------
//minDeltaR finder jet to tau
//_________________

double TauJetMinDistance(MyEventCollection collection, double jetEta, double jetPhi)
  {
    double minDeltaRtauJet = 99999.;
    for(unsigned int t =0;t<collection.tau.size();++t){
      double temp_mindeltaRtaujet = deltaR(jetEta, jetPhi, collection.tau[t]->eta, collection.tau[t]->phi); 
      if (temp_mindeltaRtaujet < minDeltaRtauJet) minDeltaRtauJet = temp_mindeltaRtaujet;
    } 
    return minDeltaRtauJet;
  }
  
//+ index  
pair<double, unsigned int> TauJetMinDistanceExtended(MyEventCollection collection, double jetEta, double jetPhi)
  {
    double minDeltaRtauJet = 99999.;
    unsigned int tauNr = 99999.;
    for(unsigned int t =0;t<collection.tau.size();++t){
      double temp_mindeltaRtaujet = deltaR(jetEta, jetPhi, collection.tau[t]->eta, collection.tau[t]->phi); 
      if (temp_mindeltaRtaujet < minDeltaRtauJet){
      	minDeltaRtauJet = temp_mindeltaRtaujet;
	tauNr=t;
      }
    } 
    return std::make_pair(minDeltaRtauJet,tauNr);
  }
  
//-----------------
//minDeltaR finder jet to jet
//_________________  

double JetJetMinDistance(MyEventCollection collection, double jetEta, double jetPhi)
  {
    double minDeltaRjetJet = 99999.;
    for(unsigned int j =0;j<collection.jet.size();++j){
      double temp_mindeltaRjetJet = deltaR(jetEta, jetPhi, collection.jet[j]->eta, collection.jet[j]->phi); 
      if (temp_mindeltaRjetJet < minDeltaRjetJet && temp_mindeltaRjetJet!=0) minDeltaRjetJet = temp_mindeltaRjetJet;
    } 
    return minDeltaRjetJet;
  }  
  
//-----------------
//leading jet finder
//_________________

pair<unsigned int,unsigned int> LeadingJets(MyEventCollection collection)
  {
    unsigned int     	j1=99999;
    unsigned int     	j2=99999;
    double 		pt1=-1.;
    double 		pt2=-1.;
    
    for(unsigned int j=0; j<collection.jet.size();j++)
      {
        if(pt1 < collection.jet[j]->pt){
	
	  if(pt2 < pt1){ pt2=pt1; j2=j1; }
	  
	  j1=j;
	  pt1=collection.jet[j]->pt;
	  
	}
	
        if((pt2 < collection.jet[j]->pt) && (pt1 > collection.jet[j]->pt)){ j2=j; pt2=collection.jet[j]->pt; }
      }
      
    return std::make_pair(j1,j2);
  }

//-----------------
//leading tau finder
//_________________
  
pair<unsigned int,unsigned int> LeadingTaus(MyEventCollection collection)
  {
    unsigned int     	t1=99999;
    unsigned int     	t2=99999;
    double 		pt1=-1.;
    double 		pt2=-1.;
    
    for(unsigned int t=0; t<collection.tau.size();t++)
      {
        if(pt1 < collection.tau[t]->pt){
	
	  if(pt2 < pt1){ pt2=pt1; t2=t1; }
	  
	  t1=t;
	  pt1=collection.tau[t]->pt;
	  
	}
	
        if((pt2 < collection.tau[t]->pt) && (pt1 > collection.tau[t]->pt)){ t2=t; pt2=collection.tau[t]->pt; }
      }
      
    return std::make_pair(t1,t2);
  }
  
//--------------------------
//2-jet max inv. mass finder and properties of dijet system
//__________________________

MassAndIndex Inv2jMassIndex(MyEventCollection collection)
  {	
    struct MassAndIndex Inv2jMass("Inv2jMass");
    TLorentzVector jet1_4v;
    TLorentzVector jet2_4v; 
    
    double Mass=0.;
    double dEtaCheck=0.;
    unsigned int first=99999;
    unsigned int second=99999;
    
    bool pass=false; 	//passing all selection cuts for the dijet system
    bool failOne=false;	//failing dijet eta cut
    bool failTwo=false;	//failing dijet eta sign cut
    
    for(unsigned int j1=1; j1<collection.jet.size(); j1++)
      {
        for(unsigned int j2=0; j2<j1; j2++)
	  {
	    jet1_4v.SetPtEtaPhiE(collection.jet[j1]->pt, collection.jet[j1]->eta, collection.jet[j1]->phi, collection.jet[j1]->energy);
	    jet2_4v.SetPtEtaPhiE(collection.jet[j2]->pt, collection.jet[j2]->eta, collection.jet[j2]->phi, collection.jet[j2]->energy);
	    
	    int sign=collection.jet[j1]->eta*collection.jet[j2]->eta;
	    double dEta=fabs(collection.jet[j1]->eta - collection.jet[j2]->eta);
	    
	    TLorentzVector dijet_4v = jet1_4v + jet2_4v;
	    
	    //select the pair of dijets with highest invariant mass passing all cuts
	    if(dEta>=4.2 && sign<0 && dijet_4v.M()>=250+Mass) {Mass = dijet_4v.M(); first = j1; second = j2; pass=true;}
	    else if(!pass){
	       if(dEta>dEtaCheck && sign<0 && dijet_4v.M()>250) {Mass = dijet_4v.M(); first = j1; second = j2; dEtaCheck=dEta; failOne=true;} //search for pair failing only the dijet delta eta cut
	       else if(!failOne)
	       {
	         if(dEta>dEtaCheck && dijet_4v.M()>250) {Mass = dijet_4v.M(); first = j1; second = j2; dEtaCheck=dEta; failTwo=true;} //search for a pair failing dijet delta eta and eta sign cuts
		 else if(!failTwo && dijet_4v.M()>Mass && dEta>dEtaCheck) {Mass = dijet_4v.M(); first = j1; second = j2; dEtaCheck=dEta;}  //failing all cuts
	       }
	    }
	  }
      }
    if(first < 99999 && second < 99999)
      {
        double dR=jet1_4v.DeltaR(jet2_4v);
        int sign=(collection.jet[first]->eta*collection.jet[second]->eta)/fabs(collection.jet[first]->eta*collection.jet[second]->eta);
        double dEta=fabs(collection.jet[first]->eta - collection.jet[second]->eta);
        Inv2jMass.Mass=Mass;
        Inv2jMass.first=first;
        Inv2jMass.second=second;
        Inv2jMass.dR=dR;
        Inv2jMass.signEta=sign;
        Inv2jMass.dEta=dEta;
	//std::cout<<"chose jets "<<first<<" and "<<second<<std::endl;
      }    
    return Inv2jMass;
  }
  
//--------------------------
//2-tau system properties
//__________________________  

TauProperties Inv2tMassIndex(MyEventCollection collection)
  {
    struct TauProperties Inv2tMass("Inv2tMass");
    TLorentzVector tau1_4v;
    TLorentzVector tau2_4v; 
    
    pair<unsigned int,unsigned int> tauIndex=LeadingTaus(collection);
    Inv2tMass.first = tauIndex.first;
    Inv2tMass.second = tauIndex.second;
    
    if(tauIndex.first < 99999 && tauIndex.second < 99999)
      {
    	tau1_4v.SetPtEtaPhiM(collection.tau[tauIndex.first]->pt, collection.tau[tauIndex.first]->eta, collection.tau[tauIndex.first]->phi, collection.tau[tauIndex.first]->mass);
    	tau2_4v.SetPtEtaPhiM(collection.tau[tauIndex.second]->pt, collection.tau[tauIndex.second]->eta, collection.tau[tauIndex.second]->phi, collection.tau[tauIndex.second]->mass);
    
        TLorentzVector ditau_4v = tau1_4v + tau2_4v;
	
         double dR=tau1_4v.DeltaR(tau2_4v);
         int charge = collection.tau[tauIndex.first]->charge * collection.tau[tauIndex.second]->charge;
         double cosdeltaphiDiTau = cos(tau1_4v.DeltaPhi(tau2_4v));
	 double dEta=fabs(collection.tau[tauIndex.first]->eta - collection.tau[tauIndex.second]->eta);
    
         Inv2tMass.Mass = ditau_4v.M();
         Inv2tMass.dR = dR;
         Inv2tMass.charge = charge;
         Inv2tMass.cosDphi = cosdeltaphiDiTau;
	 Inv2tMass.dEta=dEta;
      }
    return Inv2tMass;
  }
  
//--------------------------
// defining real tau mass
//__________________________    
  
void realTauMass(MyEventCollection collection)
  {
    for(unsigned int t=0; t<collection.tau.size(); t++)
      {
        TLorentzVector tau_4v;
	tau_4v.SetPtEtaPhiE(collection.tau[t]->pt, collection.tau[t]->eta, collection.tau[t]->phi, collection.tau[t]->energy);
	collection.tau[t]->mass = tau_4v.M();
      }
    return;
  }  
  
//--------------------------
// defining fake taus
//__________________________    

tau_s fakeTau(MyEventCollection JetColl, unsigned int TauIndex, double pTscale, double Escale)
  {
    tau_s faketau;
    if(JetColl.jet[TauIndex]->charge > 0) faketau.charge=+1;
    else if(JetColl.jet[TauIndex]->charge < 0) faketau.charge=-1;
    else faketau.charge=0;
    faketau.p      = JetColl.jet[TauIndex]->p;
    faketau.energy = JetColl.jet[TauIndex]->energy * Escale;
    faketau.et     = JetColl.jet[TauIndex]->et;
    faketau.px     = JetColl.jet[TauIndex]->px;
    faketau.py     = JetColl.jet[TauIndex]->py;
    faketau.pz     = JetColl.jet[TauIndex]->pz;
    faketau.pt     = JetColl.jet[TauIndex]->pt * pTscale;
    faketau.phi    = JetColl.jet[TauIndex]->phi;
    faketau.eta    = JetColl.jet[TauIndex]->eta;
    faketau.mass   = 0.72;
    return faketau;
  }
  
#endif
