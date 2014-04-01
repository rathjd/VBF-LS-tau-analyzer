//-----------------------------------------------------------------------------
// File: analyzer.cc
// Description: Analyzer for ntuples created by TheNtupleMaker
// Created: Fri Apr 5 13:23:28 2013 by mkntanalyzer.py
// Author: Daniele Marconi
//-----------------------------------------------------------------------------
#ifdef PROJECT_NAME
#include "PhysicsTools/TheNtupleMaker/interface/pdg.h"
#else
#include "pdg.h"
#endif

#include "CommonHistoCollection.h"
#include "FakeTau.h"
#include "CutConfiguration.h"
#include "TProfile.h"

using namespace std;

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // Get file list and histogram filename from command line

  commandLine cmdline;
  decodeCommandLine(argc, argv, cmdline);

  // Get names of ntuple files to be processed and open chain of ntuples

  vector<string> filenames = getFilenames(cmdline.filelist);
  itreestream stream(filenames, "Events");
  if ( !stream.good() ) error("unable to open ntuple file(s)");

  // Get number of events to be read

  //int nevents = 100;
  int nevents = stream.size();
  cout << "Number of events: " << nevents << endl;

  // Select variables to be read

  selectVariables(stream);


  // The root application is needed to make canvases visible during
  // program execution. If this is not needed, just comment out the following
  // line

  TApplication app("analyzer", &argc, argv);

  /*
Notes:
1. Use
ofile = outputFile(cmdline.outputfile, stream)
to skim events to output file in addition to writing out histograms.
2. Use
ofile.addEvent(event-weight)
to specify that the current event is to be added to the output file.
If omitted, the event-weight is defaulted to 1.
3. Use
ofile.count(cut-name, event-weight)
to keep track, in the count histogram, of the number of events
passing a given cut. If omitted, the event-weight is taken to be 1.
If you want the counts in the count histogram to appear in a given
order, specify the order, before entering the event loop, as in
the example below
ofile.count("NoCuts", 0)
ofile.count("GoodEvent", 0)
ofile.count("Vertex", 0)
ofile.count("MET", 0)
*/
  
  //___________________//
  //Switch for LS or OS//
  //___________________//
  bool LS=true;
  
  
  outputFile ofile(cmdline.outputfilename);
  ofile.count("NoCuts",0.);

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------
  TH1F* h1_WeightDiff = new TH1F("h1_WeightDiff", "p_event-p(exactly these 2 fake tau)", 11,-0.5,10.5);
  h1_WeightDiff->GetXaxis()->SetTitle("N_{jets}");
  h1_WeightDiff->GetYaxis()->SetTitle("#Sigma(p_event-p(exactly these 2 fake tau))");
  h1_WeightDiff->Sumw2();
  
  double charges[4]={-1000.,-0.5,0.5,1000.};
  TH1F *charge=new TH1F("charge","charge dist after dicing charge", 3, charges);
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

TH1::SetDefaultSumw2();
TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/ChargeMap_Fq-pT_30up.root", "read");
//TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/ChargeMap_AlteredpTbinning_taug45.root", "read");
//TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/ChargeMap_Default_Jet30Tau45_MC.root", "read");
//TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/ChargeMap_Lukas_Jet30_MC.root", "read");
//TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseFactors_InclAndExclIsos_Jet30Tau45_MC.root", "read");
//TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseFactors_InclAndExclIsos_Jet30Tau45_NoPt15-30_Lukas_MC.root", "read");
TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseProfilesEnergy.root", "read");

MyHistoCollection myHistoColl_SignalRegion(ofile.file_, "SignalRegion");        
MyHistoCollection myHistoColl_CR2 (ofile.file_, "Central_invertedVBF_2TightIso_CR2");
MyHistoCollection myHistoColl_CR3 (ofile.file_, "Central_1TightIso_CR3");
MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_1TightIso_CR4");
MyHistoCollection myHistoColl_CR5 (ofile.file_, "Central_AntiTightIso_CR5");
MyHistoCollection myHistoColl_CR6 (ofile.file_, "Central_invertedVBF_AntiTightIso_CR6");
MyHistoCollection myHistoColl_CR7 (ofile.file_, "Central_AntiMediumIso_CR7");
MyHistoCollection myHistoColl_CR8 (ofile.file_, "Central_invertedVBF_AntiMediumIso_CR8");
MyHistoCollection myHistoColl_CR9 (ofile.file_, "Central_AntiLooseIso_CR9");
MyHistoCollection myHistoColl_CR10 (ofile.file_, "Central_invertedVBF_AntiLooseIso_CR10");

MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
MyEventCollection Tau1TightIsoObjectSelectionCollection ("Tau1TightIsoObjectSelection");
MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");
MyEventCollection JetLooseIsoObjectSelectionCollection ("JetLooseIsoObjectSelection");


  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------
  
double EffNfake=0.052;
double EffLfake=0.46;
double EffMfake=0.64;
double EffTfake=0.72;
  
//make scaled ChargeMaps
TH2F* ChargeMapN_eff = (TH2F*)(file_eff.Get("ChargeMapN_eff"));
ChargeMapN_eff->Scale(EffNfake); //out of Wjets

TH2F* ChargeMapL_eff = (TH2F*)(file_eff.Get("ChargeMapL_eff"));
ChargeMapL_eff->Scale(EffLfake); //out of Wjets

TH2F* ChargeMapLi_eff = (TH2F*)(file_eff.Get("ChargeMapL_num")->Clone("ChargeMapLi_eff"));
ChargeMapLi_eff->Scale(EffLfake); //out of Wjets
ChargeMapLi_eff->Add((TH2F*)file_eff.Get("ChargeMapN_num"),EffNfake); //out of Wjets
ChargeMapLi_eff->Divide((TH2F*)file_eff.Get("ChargeMapLi_den"));

TH2F* ChargeMapM_eff = (TH2F*)(file_eff.Get("ChargeMapM_eff"));
ChargeMapM_eff->Scale(EffMfake); //out of Wjets

TH2F* ChargeMapMi_eff = (TH2F*)(file_eff.Get("ChargeMapM_num")->Clone("ChargeMapMi_eff"));
ChargeMapMi_eff->Scale(EffMfake); //out of Wjets
ChargeMapMi_eff->Add((TH2F*)file_eff.Get("ChargeMapL_num"),EffLfake); //out of Wjets
ChargeMapMi_eff->Add((TH2F*)file_eff.Get("ChargeMapN_num"),EffNfake); //out of Wjets
ChargeMapMi_eff->Divide((TH2F*)file_eff.Get("ChargeMapMi_den"));

TH2F* ChargeMapT_eff = (TH2F*)(file_eff.Get("ChargeMapT_eff"));
ChargeMapT_eff->Scale(EffTfake); //out of Wjets

//make correctly combined ReweightFactors
TProfile* ReweightFactorN = (TProfile*)(file_Resp.Get("RescaleWeightN"));

TProfile* ReweightFactorL = (TProfile*)(file_Resp.Get("RescaleWeightL"));

TProfile* ReweightFactorLi = (TProfile*)(file_Resp.Get("RescaleWeightLi")->Clone("ReweightFactorLi"));
TProfile* ReweightFactorMi = (TProfile*)(file_Resp.Get("RescaleWeightMi")->Clone("ReweightFactorMi"));
for(int i=0; i<ReweightFactorLi->GetNbinsX(); i++) {
double L=((TProfile*)file_Resp.Get("RescaleWeightL"))->GetBinContent(i+1);
double Nl=((TProfile*)file_Resp.Get("RescaleWeightL"))->GetBinEntries(i+1);
double N=((TProfile*)file_Resp.Get("RescaleWeightN"))->GetBinContent(i+1);
double Nn=((TProfile*)file_Resp.Get("RescaleWeightN"))->GetBinEntries(i+1);
double M=((TProfile*)file_Resp.Get("RescaleWeightM"))->GetBinContent(i+1);
double Nm=((TProfile*)file_Resp.Get("RescaleWeightM"))->GetBinEntries(i+1);
if(Nl+Nn>0) {ReweightFactorLi->SetBinContent(i+1, (EffLfake*Nl*L+EffNfake*Nn*N)/(EffLfake*Nl+EffNfake*Nn)); ReweightFactorLi->SetBinEntries(i+1, 1);}
if(Nm+Nl+Nn>0) {ReweightFactorMi->SetBinContent(i+1, (EffMfake*Nm*M+EffLfake*Nl*L+EffNfake*Nn*N)/(EffMfake*Nm+EffLfake*Nl+EffNfake*Nn)); ReweightFactorMi->SetBinEntries(i+1, 1);}
}

for(int i=0; i<ReweightFactorLi->GetNbinsX(); i++) std::cout<<ReweightFactorLi->GetBinContent(i+1)<<std::endl;
TProfile* ReweightFactorM = (TProfile*)(file_Resp.Get("RescaleWeightM"));

TProfile* ReweightFactorT = (TProfile*)(file_Resp.Get("RescaleWeightT"));

//make correctly combined scale factors
TProfile* ScaleFactorN = (TProfile*)(file_Resp.Get("ScaleFactorN"));

TProfile* ScaleFactorL = (TProfile*)(file_Resp.Get("ScaleFactorL"));

TProfile* ScaleFactorLi = (TProfile*)(file_Resp.Get("ScaleFactorLi")->Clone("ScaleFactorLi")); 
TProfile* ScaleFactorMi = (TProfile*)(file_Resp.Get("ScaleFactorMi")->Clone("ScaleFactorMi"));
for(int i=0; i<ScaleFactorLi->GetNbinsX(); i++) {
double L=((TProfile*)file_Resp.Get("ScaleFactorL"))->GetBinContent(i+1);
double Nl=((TProfile*)file_Resp.Get("ScaleFactorL"))->GetBinEntries(i+1);
double N=((TProfile*)file_Resp.Get("ScaleFactorN"))->GetBinContent(i+1);
double Nn=((TProfile*)file_Resp.Get("ScaleFactorN"))->GetBinEntries(i+1);
double M=((TProfile*)file_Resp.Get("ScaleFactorM"))->GetBinContent(i+1);
double Nm=((TProfile*)file_Resp.Get("ScaleFactorM"))->GetBinEntries(i+1);
if(Nl+Nn>0) {ScaleFactorLi->SetBinContent(i+1, (EffLfake*Nl*L+EffNfake*Nn*N)/(EffLfake*Nl+EffNfake*Nn)); ScaleFactorLi->SetBinEntries(i+1, 1);}
if(Nm+Nl+Nn>0) {ScaleFactorMi->SetBinContent(i+1, (EffMfake*Nm*M+EffLfake*Nl*L+EffNfake*Nn*N)/(EffMfake*Nm+EffLfake*Nl+EffNfake*Nn)); ScaleFactorMi->SetBinEntries(i+1, 1);}
}

TProfile* ScaleFactorM = (TProfile*)(file_Resp.Get("ScaleFactorM"));

TProfile* ScaleFactorT = (TProfile*)(file_Resp.Get("ScaleFactorT"));

//make correctly combined energy scale factors
TProfile* ScaleFactorEnergyN = (TProfile*)(file_Resp.Get("ScaleFactorEnergyN"));

TProfile* ScaleFactorEnergyL = (TProfile*)(file_Resp.Get("ScaleFactorEnergyL"));

TProfile* ScaleFactorEnergyLi = (TProfile*)(file_Resp.Get("ScaleFactorEnergyLi")->Clone("ScaleFactorEnergyLi")); 
TProfile* ScaleFactorEnergyMi = (TProfile*)(file_Resp.Get("ScaleFactorEnergyMi")->Clone("ScaleFactorEnergyMi"));
for(int i=0; i<ScaleFactorEnergyLi->GetNbinsX(); i++) {
double L=((TProfile*)file_Resp.Get("ScaleFactorEnergyL"))->GetBinContent(i+1);
double Nl=((TProfile*)file_Resp.Get("ScaleFactorEnergyL"))->GetBinEntries(i+1);
double N=((TProfile*)file_Resp.Get("ScaleFactorEnergyN"))->GetBinContent(i+1);
double Nn=((TProfile*)file_Resp.Get("ScaleFactorEnergyN"))->GetBinEntries(i+1);
double M=((TProfile*)file_Resp.Get("ScaleFactorEnergyM"))->GetBinContent(i+1);
double Nm=((TProfile*)file_Resp.Get("ScaleFactorEnergyM"))->GetBinEntries(i+1);
if(Nl+Nn>0) {ScaleFactorEnergyLi->SetBinContent(i+1, (EffLfake*Nl*L+EffNfake*Nn*N)/(EffLfake*Nl+EffNfake*Nn)); ScaleFactorEnergyLi->SetBinEntries(i+1, 1);}
if(Nm+Nl+Nn>0) {ScaleFactorEnergyMi->SetBinContent(i+1, (EffMfake*Nm*M+EffLfake*Nl*L+EffNfake*Nn*N)/(EffMfake*Nm+EffLfake*Nl+EffNfake*Nn)); ScaleFactorEnergyMi->SetBinEntries(i+1, 1);}
}

TProfile* ScaleFactorEnergyM = (TProfile*)(file_Resp.Get("ScaleFactorEnergyM"));

TProfile* ScaleFactorEnergyT = (TProfile*)(file_Resp.Get("ScaleFactorEnergyT"));

for(int entry=0; entry < nevents; ++entry)
{
// Read event into memory
stream.read(entry);

// Uncomment the following line if you wish to copy variables into
// structs. See the header file analyzer.h to find out what structs
// are available. Each struct contains the field "selected", which
// can be set as needed. Call saveSelectedObjects() before a call to
// addEvent if you wish to save only the selected objects.

fillObjects();
           
//if(entry%1000==0)
//cout << "--processing entry " << entry << " of " << nevents << endl;
// ----------------------
// -- object selection --
// ----------------------

          // vertex selection
bool goodVertex = true;

if(!( vertex.size() > 0 )) goodVertex = false;
if(goodVertex){
	TauTightIsoObjectSelectionCollection.goodVertex = true;
	Tau1TightIsoObjectSelectionCollection.goodVertex = true;
	TauMediumIsoObjectSelectionCollection.goodVertex = true;
	TauLooseIsoObjectSelectionCollection.goodVertex = true;
	TauNoIsoObjectSelectionCollection.goodVertex = true;
}

//trigger selection
   
if(
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1)
  ){
	TauTightIsoObjectSelectionCollection.passedTrigger = true;
	Tau1TightIsoObjectSelectionCollection.passedTrigger = true;
	TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	TauNoIsoObjectSelectionCollection.passedTrigger = true;
   }

// electron selection
for(unsigned int e = 0;e<electron.size();++e){
	TauTightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	Tau1TightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauMediumIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauLooseIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauNoIsoObjectSelectionCollection.electron.push_back(&electron[e]);
}

// muon selection
for(unsigned int m =0;m<muon.size();++m){
	if(!( fabs(muon[m].eta) < 2.4 )) 					continue;
	if(!( muon[m].pt > 20 ))			 			continue;
	if(!( muon[m].isGlobalMuon )) 						continue;
	if(!( muon[m].isTrackerMuon )) 						continue;
	if(!( muon[m].isPFMuon )) 						continue;
	if(!( muon[m].numberOfMatchedStations > 1 )) 				continue;
	if(!(( fabs(muon[m].muonBestTrack_dxy) < 0.2 )) &&
            ( fabs(muon[m]. muonBestTrack_dz) < 0.5 )) 				continue;
	if(!( muon[m].globalTrack_normalizedChi2 < 10. )) 			continue;
	if(!( muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0 )) 	continue;
	if(!( muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0 )) 	continue;
	if(!( muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5 )) 	continue;
	if(!( muon[m].innerTrack_normalizedChi2 < 1.8 )) 			continue;
	if(!( fabs(muon[m].innerTrack_dxy) < 3. )) 				continue;
	if(!( fabs(muon[m].innerTrack_dz) < 30. )) 				continue;
	TauTightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	Tau1TightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauNoIsoObjectSelectionCollection.muon.push_back(&muon[m]);
}

// jet baseline selection
for(unsigned int j = 0;j<jet.size();++j){
	if(!( jet[j].pt >= 30. )) 		continue;
	if(!( fabs(jet[j].eta) <= 2.7 )) 	continue;
	JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
}


// --------------------------
// -- QCD Event Weighting --
// --------------------------

bool verbose=false;
if(verbose)std::cout<<"Event: "<<eventhelper_event<<std::endl;


vector<double> jet_taufakerateN;
vector<double> jet_taufakerateL;
vector<double> jet_taufakerateLi;
vector<double> jet_taufakerateM;
vector<double> jet_taufakerateMi;
vector<double> jet_taufakerateT;

for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
double Fq=JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction;		
int nbinN = ChargeMapN_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nRescaleBinN= ReweightFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinL = ChargeMapL_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nRescaleBinL= ReweightFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinLi = ChargeMapLi_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nRescaleBinLi= ReweightFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinM = ChargeMapM_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nRescaleBinM= ReweightFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinMi = ChargeMapMi_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nRescaleBinMi= ReweightFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinT = ChargeMapT_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nRescaleBinT= ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
if(verbose)std::cout<<"Jet "<<i<<" out of "<<JetLooseIsoObjectSelectionCollection.jet.size()<<": pT="<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", eta="<<JetLooseIsoObjectSelectionCollection.jet[i]->eta<<", phi="<<JetLooseIsoObjectSelectionCollection.jet[i]->phi<<std::endl;
if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.1)
  {
    jet_taufakerateN.push_back(ChargeMapN_eff->GetBinContent(nbinN)*ReweightFactorN->GetBinContent(nRescaleBinN));
    jet_taufakerateL.push_back(ChargeMapL_eff->GetBinContent(nbinL)*ReweightFactorL->GetBinContent(nRescaleBinL));
    jet_taufakerateLi.push_back(ChargeMapLi_eff->GetBinContent(nbinLi)*ReweightFactorLi->GetBinContent(nRescaleBinLi));
    jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nbinM)*ReweightFactorM->GetBinContent(nRescaleBinM));
    jet_taufakerateMi.push_back(ChargeMapMi_eff->GetBinContent(nbinMi)*ReweightFactorMi->GetBinContent(nRescaleBinMi));
    jet_taufakerateT.push_back(ChargeMapT_eff->GetBinContent(nbinT)*ReweightFactorT->GetBinContent(nRescaleBinT));
    if(verbose)std::cout<<"MindR and eta<=2.1 pass: N_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity<<", F_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction<<", P(N_q,F_q)="<<ChargeMapT_eff->GetBinContent(nbinT)<<", P(pT)="<<ReweightFactorT->GetBinContent(nRescaleBinT)<<std::endl;
  }
else
  {
    double jetMindR2=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
    if(jetMindR > 0.5 && jetMindR2 > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.2)
      {
        jet_taufakerateN.push_back(ChargeMapN_eff->GetBinContent(nbinN)*ReweightFactorN->GetBinContent(nRescaleBinN));
        jet_taufakerateL.push_back(ChargeMapL_eff->GetBinContent(nbinL)*ReweightFactorL->GetBinContent(nRescaleBinL));
	jet_taufakerateLi.push_back(ChargeMapLi_eff->GetBinContent(nbinLi)*ReweightFactorLi->GetBinContent(nRescaleBinLi));
        jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nbinM)*ReweightFactorM->GetBinContent(nRescaleBinM));
	jet_taufakerateMi.push_back(ChargeMapMi_eff->GetBinContent(nbinMi)*ReweightFactorMi->GetBinContent(nRescaleBinMi));
        jet_taufakerateT.push_back(ChargeMapT_eff->GetBinContent(nbinT)*ReweightFactorT->GetBinContent(nRescaleBinT));
	if(verbose)std::cout<<"MindR2 and 2.1<eta<=2.2 pass: N_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity<<", F_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction<<", P(N_q,F_q)="<<ChargeMapT_eff->GetBinContent(nbinT)<<", P(pT)="<<ReweightFactorT->GetBinContent(nRescaleBinT)<<std::endl;
      }
    else
      {
        jet_taufakerateN.push_back(0);
    	jet_taufakerateL.push_back(0);
	jet_taufakerateLi.push_back(0);
	jet_taufakerateM.push_back(0);
	jet_taufakerateMi.push_back(0);
	jet_taufakerateT.push_back(0);
	if(verbose)std::cout<<"Failed: P=0!"<<std::endl;
      }
  }
}



Fake FakeTausN("FakeTaus");
if(verbose)std::cout<<"Dice NoIso"<<std::endl;
FakeTausN.generate(jet_taufakerateN,jet_taufakerateN, true);

tau_s faketau1N;
tau_s faketau2N;

if ( FakeTausN.index.first >= 0 && FakeTausN.index.second >= 0 ) {

double scaleP = ScaleFactorN->GetBinContent(ScaleFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt));
double scaleE = ScaleFactorEnergyN->GetBinContent(ScaleFactorEnergyN->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt)); 
if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausN.weight=0;}
//if(faketau1N.pt < 45) FakeTausN.weight=0;

faketau1N = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausN.index.first, scaleP, scaleE);
/*if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->charge > 0 ) faketau1N.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->charge < 0 ) faketau1N.charge = -1; else{ faketau1N.charge=+1; FakeTausN.weight=0;}
faketau1N.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->p;
faketau1N.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->energy;
faketau1N.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->et;
faketau1N.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->px;
faketau1N.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->py;
faketau1N.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pz;
faketau1N.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt * scale;*/
/*faketau1N.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta<=2.1) faketau1N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta;
else faketau1N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta)*2.1;*/

double scaleP2 = ScaleFactorN->GetBinContent(ScaleFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt));
double scaleE2 = ScaleFactorEnergyN->GetBinContent(ScaleFactorEnergyN->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt));
if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausN.weight=0;}
faketau2N = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausN.index.second, scaleP2, scaleE2);

if(faketau1N.pt > faketau2N.pt){
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau1N);
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau2N);
}
else{
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau2N);
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau1N);
}

if(verbose)std::cout<<"Jet "<<FakeTausN.index.first<<" to FTau1: pTScale="<<scaleP<<", pT="<<faketau1N.pt<<", eta="<<faketau1N.eta<<", phi="<<faketau1N.phi<<", charge"<<faketau1N.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausN.index.second<<" to FTau2: pTScale="<<scaleP2<<", pT="<<faketau2N.pt<<", eta="<<faketau2N.eta<<", phi="<<faketau2N.phi<<", charge"<<faketau2N.charge<<std::endl;
}


Fake FakeTausL("FakeTaus");
if(verbose)std::cout<<"Dice LooseIso"<<std::endl;

FakeTausL.generate(jet_taufakerateL,jet_taufakerateLi, false);

tau_s faketau1L;
tau_s faketau2L;

if ( FakeTausL.index.first >= 0 && FakeTausL.index.second >= 0 ) {

double scaleP = ScaleFactorL->GetBinContent(ScaleFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt)); 
double scaleE = ScaleFactorEnergyL->GetBinContent(ScaleFactorEnergyL->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt));
if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausL.weight=0;}
faketau1L = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausL.index.first, scaleP, scaleE); 

double scaleP2 = ScaleFactorLi->GetBinContent(ScaleFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt));
double scaleE2 = ScaleFactorEnergyL->GetBinContent(ScaleFactorEnergyL->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt));
if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausL.weight=0;}
faketau2L = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausL.index.second, scaleP2, scaleE2);

if(faketau1L.pt > faketau2L.pt){
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau1L);
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau2L);
}
else{
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau2L);
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau1L);
}

if(verbose)std::cout<<"Jet "<<FakeTausL.index.first<<" to FTau1: pTScale="<<scaleP<<", pT="<<faketau1L.pt<<", eta="<<faketau1L.eta<<", phi="<<faketau1L.phi<<", charge"<<faketau1L.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausL.index.second<<" to FTau2: pTScale="<<scaleP2<<", pT="<<faketau2L.pt<<", eta="<<faketau2L.eta<<", phi="<<faketau2L.phi<<", charge"<<faketau2L.charge<<std::endl;
}


Fake FakeTausM("FakeTausM");
if(verbose)std::cout<<"Dice MediumIso"<<std::endl;

FakeTausM.generate(jet_taufakerateM,jet_taufakerateMi, false);

tau_s faketau1M;
tau_s faketau2M;

if ( FakeTausM.index.first >= 0 && FakeTausM.index.second >= 0 ) {

double scaleP = ScaleFactorM->GetBinContent(ScaleFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt));
double scaleE = ScaleFactorEnergyM->GetBinContent(ScaleFactorEnergyM->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt)); 
if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausM.weight=0;}
faketau1M = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausM.index.first, scaleP, scaleE);

double scaleP2 = ScaleFactorMi->GetBinContent(ScaleFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt));
double scaleE2 = ScaleFactorEnergyMi->GetBinContent(ScaleFactorEnergyMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt));
if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausM.weight=0;}
faketau2M = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausM.index.second, scaleP2, scaleE2);

if(faketau1M.pt > faketau2M.pt){
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau1M);
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau2M);
}
else{
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau2M);
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau1M);
}

if(verbose)std::cout<<"Jet "<<FakeTausM.index.first<<" to FTau1: pTScale="<<scaleP<<", pT="<<faketau1M.pt<<", eta="<<faketau1M.eta<<", phi="<<faketau1M.phi<<", charge"<<faketau1M.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausM.index.second<<" to FTau2: pTScale="<<scaleP2<<", pT="<<faketau2M.pt<<", eta="<<faketau2M.eta<<", phi="<<faketau2M.phi<<", charge"<<faketau2M.charge<<std::endl;
}


Fake FakeTausT("FakeTausT");
if(verbose)std::cout<<"Dice 1TightIso"<<std::endl;
FakeTausT.generate(jet_taufakerateT,jet_taufakerateMi, false);

tau_s faketau1T;
tau_s faketau2T;

if ( FakeTausT.index.first >= 0 && FakeTausT.index.second >= 0 ) {

double scaleP = ScaleFactorT->GetBinContent(ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt)); 
double scaleE = ScaleFactorEnergyT->GetBinContent(ScaleFactorEnergyT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt));
if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausT.weight=0;}
faketau1T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausT.index.first, scaleP, scaleE);

double scaleP2 = ScaleFactorMi->GetBinContent(ScaleFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt));
double scaleE2 = ScaleFactorEnergyMi->GetBinContent(ScaleFactorEnergyMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt));
if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausT.weight=0;}
faketau2T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausT.index.second, scaleP2, scaleE2);

if(faketau1T.pt > faketau2T.pt){
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau1T);
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau2T);
}
else{
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau2T);
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau1T);
}
charge->Fill(faketau1T.charge*faketau2T.charge,FakeTausT.weight);
if(verbose)std::cout<<"Jet "<<FakeTausT.index.first<<" to FTau1: pTScale="<<scaleP<<", pT="<<faketau1T.pt<<", eta="<<faketau1T.eta<<", phi="<<faketau1T.phi<<", charge"<<faketau1T.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausT.index.second<<" to FTau2: pTScale="<<scaleP2<<", pT="<<faketau2T.pt<<", eta="<<faketau2T.eta<<", phi="<<faketau2T.phi<<", charge"<<faketau2T.charge<<std::endl;
}


Fake FakeTausTT("FakeTausTT");
if(verbose)std::cout<<"Dice 2TightIso"<<std::endl;
FakeTausTT.generate(jet_taufakerateT,jet_taufakerateT, true);

tau_s faketauT1T;
tau_s faketauT2T;

if ( FakeTausTT.index.first >= 0 && FakeTausTT.index.second >= 0 ) {

double scaleP = ScaleFactorT->GetBinContent(ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->pt));
double scaleE = ScaleFactorEnergyT->GetBinContent(ScaleFactorEnergyT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->pt));
if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausTT.weight=0;}
faketauT1T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausTT.index.first, scaleP, scaleE);

double scaleP2 = ScaleFactorT->GetBinContent(ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->pt));
double scaleE2 = ScaleFactorEnergyT->GetBinContent(ScaleFactorEnergyT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->pt));
if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausTT.weight=0;}
faketauT2T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausTT.index.second, scaleP2, scaleE2);

if(faketauT1T.pt > faketauT2T.pt){
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT1T);
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT2T);
}
else{
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT2T);
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT1T);
}

if(verbose)std::cout<<"Jet "<<FakeTausTT.index.first<<" to FTau1: pTScale="<<scaleP<<", pT="<<faketauT1T.pt<<", eta="<<faketauT1T.eta<<", phi="<<faketauT1T.phi<<", charge"<<faketauT1T.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausTT.index.second<<" to FTau2: pTScale="<<scaleP2<<", pT="<<faketauT2T.pt<<", eta="<<faketauT2T.eta<<", phi="<<faketauT2T.phi<<", charge"<<faketauT2T.charge<<std::endl;
}

// jet && bjet selection
// ? id ?
for(unsigned int j = 0;j<jet.size();++j){
if(!( jet[j].pt >= 30. )) continue; // Original value 20
if(!( fabs(jet[j].eta) <= 5.0 )) continue;
double DistanceN = TauJetMinDistance(TauNoIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceL = TauJetMinDistance(TauLooseIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceM = TauJetMinDistance(TauMediumIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double Distance1T = TauJetMinDistance(Tau1TightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceT = TauJetMinDistance(TauTightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
bool jetid=true;
if(!( (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99 )) jetid=false;
if(!( jet[j].neutralEmEnergyFraction < 0.99 )) jetid=false;
if(!( jet[j].numberOfDaughters > 1 )) jetid=false;
if(fabs(jet[j].eta) < 2.4) {
   if(!( jet[j].chargedHadronEnergyFraction > 0 )) jetid=false;
   if(!( jet[j].chargedEmEnergyFraction < 0.99 ))  jetid=false;
   if(!( jet[j].chargedHadronMultiplicity > 0 ))   jetid=false;
 }
if( /*jet[j].pt >= 50. &&*/ jetid	){
  if(	DistanceN >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceL >= 0.3	) TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceM >= 0.3	) TauMediumIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	Distance1T >= 0.3	) Tau1TightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceT >= 0.3	) {TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]); if(verbose)std::cout<<"Jet "<<j<<" in tight jet coll: pt="<<jet[j].pt<<", eta="<<jet[j].eta<<", phi"<<jet[j].phi<<std::endl;}
            }
if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244 ){
  if(	DistanceN >= 0.3	) TauNoIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceL >= 0.3	) TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceM >= 0.3	) TauMediumIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	Distance1T >= 0.3	) Tau1TightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceT >= 0.3	) {TauTightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);if(verbose)std::cout<<"Jet "<<j<<" in tight b-jet coll: pt="<<jet[j].pt<<", eta="<<jet[j].eta<<", phi"<<jet[j].phi<<std::endl;}
            }
}
if(verbose)std::cout<<TauTightIsoObjectSelectionCollection.jet.size()<<" jets in tightIso jet collection and "<<TauTightIsoObjectSelectionCollection.bjet.size()<<" in bjet collection"<<std::endl;

//MET selection
TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);
TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
Tau1TightIsoObjectSelectionCollection.met.push_back(&met[0]);
TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);

//Event Count
ofile.count("NoCuts");

// ---------------------
// -- Signal Region --
// ---------------------
if(TauTightIsoObjectSelectionCollection.jet.size()>=2){
Selection Signal("Signal"); //label and initialisation
Signal.InputCollection 		= &TauTightIsoObjectSelectionCollection;//input collection
Signal.OutputCollection 	= &myHistoColl_SignalRegion;        	//output collection
Signal.RealData        		= eventhelper_isRealData;        	//pass information if event is real data
Signal.RunData        		= false;        			//real data allowed
Signal.weight        		= FakeTausTT.weight;        		//event weight
CutConfiguration(&Signal, true, LS); 					//selection, VBF, LS

Signal.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection InvertedVBF_CR2("InvertedVBF_CR2"); //label and initialisation
InvertedVBF_CR2.InputCollection 	= &TauTightIsoObjectSelectionCollection;//input collection
InvertedVBF_CR2.OutputCollection 	= &myHistoColl_CR2;        		//output collection
InvertedVBF_CR2.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_CR2.RunData        		= true;        				//real data allowed
InvertedVBF_CR2.weight        		= FakeTausTT.weight;        		//event weight
CutConfiguration(&InvertedVBF_CR2, false, LS); 					//selection, VBF, LS

InvertedVBF_CR2.select();        //do selection, fill histograms
}

// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------
if(Tau1TightIsoObjectSelectionCollection.jet.size()>=2){
if(verbose)std::cout<<"_____________________"<<std::endl;
if(verbose)std::cout<<FakeTausT.weight<<std::endl;
Selection oneTightTau_CR3("oneTightTau_CR3"); //label and initialisation
oneTightTau_CR3.InputCollection 	= &Tau1TightIsoObjectSelectionCollection;	//input collection
oneTightTau_CR3.OutputCollection 	= &myHistoColl_CR3;        			//output collection
oneTightTau_CR3.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
oneTightTau_CR3.RunData        		= true;        					//real data allowed
oneTightTau_CR3.weight        		= FakeTausT.weight;        			//event weight
CutConfiguration(&oneTightTau_CR3, true, LS); 						//selection, VBF, LS

oneTightTau_CR3.select();        //do selection, fill histograms

// ---------------------------------------------
// -- CENTRAL + InvertedVBF + 1 Tight Tau CR4 --
// ---------------------------------------------
if(verbose)std::cout<<FakeTausT.weight<<std::endl;
Selection InvertedVBF_oneTightTau_CR4("InvertedVBF_oneTightTau_CR4"); 					//label and initialisation
InvertedVBF_oneTightTau_CR4.InputCollection 		= &Tau1TightIsoObjectSelectionCollection;       //input collection
InvertedVBF_oneTightTau_CR4.OutputCollection 		= &myHistoColl_CR4;        			//output collection
InvertedVBF_oneTightTau_CR4.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_oneTightTau_CR4.RunData        		= true;        					//real data allowed
InvertedVBF_oneTightTau_CR4.weight        		= FakeTausT.weight;        			//event weight
CutConfiguration(&InvertedVBF_oneTightTau_CR4, false, LS); 						//selection, VBF, LS

InvertedVBF_oneTightTau_CR4.select();        //do selection, fill histograms
}

// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------
if(TauMediumIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiTightTau_CR5("AntiTightTau_CR5"); //label and initialisation
AntiTightTau_CR5.InputCollection 		= &TauMediumIsoObjectSelectionCollection;	//input collection
AntiTightTau_CR5.OutputCollection 		= &myHistoColl_CR5;        			//output collection
AntiTightTau_CR5.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
AntiTightTau_CR5.RunData        		= true;        					//real data allowed
AntiTightTau_CR5.weight        			= FakeTausM.weight;        			//event weight
CutConfiguration(&AntiTightTau_CR5, true, LS); 							//selection, VBF, LS

AntiTightTau_CR5.select();        //do selection, fill histograms

// ------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Tight Tau CR6 --
// ------------------------------------------------

Selection InvertedVBF_AntiTightTau_CR6("InvertedVBF_AntiTightTau_CR6"); //label and initialisation
InvertedVBF_AntiTightTau_CR6.InputCollection 		= &TauMediumIsoObjectSelectionCollection;	//input collection
InvertedVBF_AntiTightTau_CR6.OutputCollection 		= &myHistoColl_CR6;        			//output collection
InvertedVBF_AntiTightTau_CR6.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_AntiTightTau_CR6.RunData        		= true;        					//real data allowed
InvertedVBF_AntiTightTau_CR6.weight        		= FakeTausM.weight;        			//event weight
CutConfiguration(&InvertedVBF_AntiTightTau_CR6, false, LS); 						//selection, VBF, LS

InvertedVBF_AntiTightTau_CR6.select();        //do selection, fill histograms
}

// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------
if(TauLooseIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiMediumTau_CR7("AntiMediumTau_CR7"); //label and initialisation
AntiMediumTau_CR7.InputCollection 	= &TauLooseIsoObjectSelectionCollection;//input collection
AntiMediumTau_CR7.OutputCollection 	= &myHistoColl_CR7;        		//output collection
AntiMediumTau_CR7.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiMediumTau_CR7.RunData        	= true;        				//real data allowed
AntiMediumTau_CR7.weight        	= FakeTausL.weight;        		//event weight
CutConfiguration(&AntiMediumTau_CR7, true, LS); 				//selection, VBF, LS

AntiMediumTau_CR7.select();        //do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Medium Tau CR8 --
// -------------------------------------------------

Selection InvertedVBF_AntiMediumTau_CR8("InvertedVBF_AntiMediumTau_CR8"); //label and initialisation
InvertedVBF_AntiMediumTau_CR8.InputCollection 		= &TauLooseIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiMediumTau_CR8.OutputCollection 		= &myHistoColl_CR8;        //output collection
InvertedVBF_AntiMediumTau_CR8.RealData        		= eventhelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiMediumTau_CR8.RunData        		= true;        //real data allowed
InvertedVBF_AntiMediumTau_CR8.weight        		= FakeTausL.weight;        //event weight
CutConfiguration(&InvertedVBF_AntiMediumTau_CR8, false, LS); //selection, VBF, LS

InvertedVBF_AntiMediumTau_CR8.select();        //do selection, fill histograms
}
// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------
if(TauNoIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiLooseTau_CR9("AntiLooseTau_CR9"); //label and initialisation
AntiLooseTau_CR9.InputCollection 	= &TauNoIsoObjectSelectionCollection;        //input collection
AntiLooseTau_CR9.OutputCollection 	= &myHistoColl_CR9;        //output collection
AntiLooseTau_CR9.RealData        	= eventhelper_isRealData;        //pass information if event is real data
AntiLooseTau_CR9.RunData        	= true;        //real data allowed
AntiLooseTau_CR9.weight        		= FakeTausN.weight;        //event weight
CutConfiguration(&AntiLooseTau_CR9, true, LS); //selection, VBF, LS

AntiLooseTau_CR9.select();        //do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Loose Tau CR10 --
// -------------------------------------------------

Selection InvertedVBF_AntiLooseTau_CR10("InvertedVBF_AntiLooseTau_CR10"); //label and initialisation
InvertedVBF_AntiLooseTau_CR10.InputCollection 		= &TauNoIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiLooseTau_CR10.OutputCollection 		= &myHistoColl_CR10;        //output collection
InvertedVBF_AntiLooseTau_CR10.RealData        		= eventhelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiLooseTau_CR10.RunData        		= true;        //real data allowed
InvertedVBF_AntiLooseTau_CR10.weight        		= FakeTausN.weight;        //event weight
CutConfiguration(&InvertedVBF_AntiLooseTau_CR10, false, LS); //selection, VBF, LS

InvertedVBF_AntiLooseTau_CR10.select();        //do selection, fill histograms
}

//Clearing Object Collections
TauTightIsoObjectSelectionCollection.clear();
Tau1TightIsoObjectSelectionCollection.clear();
TauMediumIsoObjectSelectionCollection.clear();
TauLooseIsoObjectSelectionCollection.clear();
TauNoIsoObjectSelectionCollection.clear();
JetLooseIsoObjectSelectionCollection.clear();

if(verbose)std::cout<<"_______________________________________________"<<std::endl;
}

  stream.close();
  ofile.close();
  return 0;
}

