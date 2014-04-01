#ifndef CUTCONFIGURATION_H
#define CUTCONFIGURATION_H

#include "selection.h"

void CutConfiguration(Selection *Region, bool VBF, bool LS){
  Region->NumberTauMin = 2; //require at least N tau
  Region->NumberTauMax = 3; //require less than N taus
  Region->DiTauDeltaRmin = 0.3; //minimum delta R for tau pair
  Region->DiTauInvMassMin = -1; //minimum Di-tau-mass requirement
  Region->DiTauInvMassMax = -1; //maximum Di-tau-mass requirement
  if(LS) Region->DiTauSign = +1; //1 for LS and -1 for OS, 0 for no requirement
  else   Region->DiTauSign = -1; //1 for LS and -1 for OS, 0 for no requirement
  Region->Btag = 0; //number of btags required (exact -> 0 = none)
  Region->METMin = 30.; // minimum MET requirement
  Region->METMax = -1; // maximum MET requirement
  Region->JetEtaMax = 5.; //maximum eta for jets, set to -1 for no requirement
  Region->LeadJetPtMin = 30.; //minimum pt of lead jet, set to -1 for no requirement
  Region->LeadJetPtMax = -1.; //maximum pt of lead jet, set to -1 for no requirement
  Region->SubLeadJetPtMin = 30.; //minimum pt of sub lead jet, set to -1 for no requirement
  Region->SubLeadJetPtMax = -1.; //maximum pt of sub lead jet, set to -1 for no requirement
  Region->DiJetDrMin = 0.3; //Dijet minimum delta R, set to -1 for no requirement
  Region->DiJetDrMax = -1; //Dijet maximum delta R, set to -1 for no requirement
  Region->DiJetInvMassMin = 250.; //Dijet minimal invariant mass, set to -1 for no requirement
  Region->DiJetInvMassMax = -1.; //Dijet maximum invariant mass, set to -1 for no requirement
  Region->DiJetSignEta = -1; //Dijet sign eta_1*eta_2
  Region->DiJetDetaMin = 4.2; //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
  Region->DiJetDetaMax = -1; //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
  Region->invertTauRequirements = false; //invert number of taus requirement
  Region->invertTauProperties = false; //invert ditau properties (dR, sign)
  Region->invertBtagRequirement = false; //invert number of b-jets required
  if(VBF){
    Region->invertJetRequirements = false; //invert jet pt requirements
    Region->invertDijetProperties = false; //invert dijet system properties (dR, inv mass, sign eta, dEta)
  }
  else{
    Region->invertJetRequirements = true; //invert jet pt requirements
    Region->invertDijetProperties = true; //invert dijet system properties (dR, inv mass, sign eta, dEta)  
  }
  return;
}
