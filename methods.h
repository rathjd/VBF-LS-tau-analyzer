#ifndef METHODS_H
#define METHODS_H

#include "structures.h"

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
//2-jet max inv. mass finder
//__________________________

MassAndIndex Inv2jMassIndex(MyEventCollection collection)
  {	
    struct MassAndIndex Inv2jMass("Inv2jMass");
    TLorentzVector jet1_4v;
    TLorentzVector jet2_4v; 
    bool filled=false;
    
    double Mass=0.;
    unsigned int first=99999;
    unsigned int second=99999;
    
    for(unsigned int j1=1; j1<collection.jet.size(); j1++)
      {
        for(unsigned int j2=0; j2<j1; j2++)
	  {
	    jet1_4v.SetPtEtaPhiE(collection.jet[j1]->pt, collection.jet[j1]->eta, collection.jet[j1]->phi, collection.jet[j1]->energy);
	    jet2_4v.SetPtEtaPhiE(collection.jet[j2]->pt, collection.jet[j2]->eta, collection.jet[j2]->phi, collection.jet[j2]->energy);
	    
	    TLorentzVector dijet_4v = jet1_4v + jet2_4v;
	    if(Mass < dijet_4v.M()) { filled = true; Mass = dijet_4v.M(); first = j1; second = j2; }
	  }
      }
    if(!filled) Inv2jMass.Mass=-1;
    else Inv2jMass.Mass=Mass;
    Inv2jMass.first=first;
    Inv2jMass.second=second;
    
    return Inv2jMass;
  }
  
//--------------------------
//2-tau invariant mass
//__________________________

double tauMass(MyEventCollection collection, unsigned int t1, unsigned int t2)
  {
    TLorentzVector tau1_4v;
    TLorentzVector tau2_4v;
    
    tau1_4v.SetPtEtaPhiE(collection.tau[t1]->pt, collection.tau[t1]->eta, collection.tau[t1]->phi, collection.tau[t1]->energy);
    tau2_4v.SetPtEtaPhiE(collection.tau[t2]->pt, collection.tau[t2]->eta, collection.tau[t2]->phi, collection.tau[t2]->energy);//add up scalar pt to ht
    
    TLorentzVector ditau_4v = tau1_4v + tau2_4v;
    
    return ditau_4v.M();
  }
  
//--------------------------
//2-tau charge and CosDeltaPhi
//__________________________
  
pair<double,double> ChargeCosDeltaPhi(MyEventCollection collection, unsigned int t1, unsigned int t2)
  {
    double charge = collection.tau[t1]->charge * collection.tau[t2]->charge;
    
    TLorentzVector tau1_4v;
    TLorentzVector tau2_4v;
    
    tau1_4v.SetPtEtaPhiE(collection.tau[t1]->pt, collection.tau[t1]->eta, collection.tau[t1]->phi, collection.tau[t1]->energy);
    tau2_4v.SetPtEtaPhiE(collection.tau[t2]->pt, collection.tau[t2]->eta, collection.tau[t2]->phi, collection.tau[t2]->energy);//add up scalar pt to ht
    double cosdeltaphiDiTau = cos(tau1_4v.DeltaPhi(tau2_4v));
    
    return std::make_pair(charge,cosdeltaphiDiTau);
  }
  
#endif
