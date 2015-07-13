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
#include "selection.h"
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
  
  outputFile ofile(cmdline.outputfilename);
  ofile.count("NoCuts",0.);

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------
  TH1F* h1_WeightDiff = new TH1F("h1_WeightDiff", "p_event-p(exactly these 2 fake tau)", 11,-0.5,10.5);
  h1_WeightDiff->GetXaxis()->SetTitle("N_{jets}");
  h1_WeightDiff->GetYaxis()->SetTitle("#Sigma(p_event-p(exactly these 2 fake tau))");
  h1_WeightDiff->Sumw2();

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

TH1::SetDefaultSumw2();

TFile
file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/EffmapVariations21.root", "read");
//TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseFactors_InclAndExclIsos_Jet30Tau45_NoPt15-30_Lukas_MC.root", "read");
TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseProfilesV2.root", "read");

MyHistoCollection myHistoColl_SR_Nq_Fq (ofile.file_, "SR_Nq_Fq");        
MyHistoCollection myHistoColl_CR_Nq_Fq (ofile.file_, "CR_Nq_Fq");
MyHistoCollection myHistoColl_SR_Nq_pT (ofile.file_, "SR_Nq_pT");        
MyHistoCollection myHistoColl_CR_Nq_pT (ofile.file_, "CR_Nq_pT");
MyHistoCollection myHistoColl_SR_Nq_Abseta (ofile.file_, "SR_Nq_Abseta");        
MyHistoCollection myHistoColl_CR_Nq_Abseta (ofile.file_, "CR_Nq_Abseta");
MyHistoCollection myHistoColl_SR_Fq_pT (ofile.file_, "SR_Fq_pT");        
MyHistoCollection myHistoColl_CR_Fq_pT (ofile.file_, "CR_Fq_pT");
MyHistoCollection myHistoColl_SR_Fq_Abseta (ofile.file_, "SR_Fq_Abseta");        
MyHistoCollection myHistoColl_CR_Fq_Abseta (ofile.file_, "CR_Fq_Abseta");
MyHistoCollection myHistoColl_SR_pT_Abseta (ofile.file_, "SR_pT_Abseta");        
MyHistoCollection myHistoColl_CR_pT_Abseta (ofile.file_, "CR_pT_Abseta");

MyEventCollection JetLooseIsoObjectSelectionCollection("JetLooseIsoObjectSelectionCollection");
MyEventCollection MonoTauIso_Nq_Fq_ObjectSelectionCollection ("MonoTauIso_Nq_Fq_ObjectSelection");
MyEventCollection MonoTauIso_Nq_pT_ObjectSelectionCollection ("MonoTauIso_Nq_pT_ObjectSelection");
MyEventCollection MonoTauIso_Nq_Abseta_ObjectSelectionCollection ("MonoTauIso_Nq_Abseta_ObjectSelection");
MyEventCollection MonoTauIso_Fq_pT_ObjectSelectionCollection ("MonoTauIso_Fq_pT_ObjectSelection");
MyEventCollection MonoTauIso_Fq_Abseta_ObjectSelectionCollection ("MonoTauIso_Fq_Abseta_ObjectSelection");
MyEventCollection MonoTauIso_pT_Abseta_ObjectSelectionCollection ("MonoTauIso_pT_Abseta_ObjectSelection");

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------

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
	MonoTauIso_Nq_Fq_ObjectSelectionCollection.goodVertex = true;
	MonoTauIso_Nq_pT_ObjectSelectionCollection.goodVertex = true;
	MonoTauIso_Nq_Abseta_ObjectSelectionCollection.goodVertex = true;
	MonoTauIso_Fq_pT_ObjectSelectionCollection.goodVertex = true;
	MonoTauIso_Fq_Abseta_ObjectSelectionCollection.goodVertex = true;
	MonoTauIso_pT_Abseta_ObjectSelectionCollection.goodVertex = true;
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
	MonoTauIso_Nq_Fq_ObjectSelectionCollection.passedTrigger = true;
	MonoTauIso_Nq_pT_ObjectSelectionCollection.passedTrigger = true;
	MonoTauIso_Nq_Abseta_ObjectSelectionCollection.passedTrigger = true;
	MonoTauIso_Fq_pT_ObjectSelectionCollection.passedTrigger = true;
	MonoTauIso_Fq_Abseta_ObjectSelectionCollection.passedTrigger = true;
	MonoTauIso_pT_Abseta_ObjectSelectionCollection.passedTrigger = true;  
   }

// electron selection
for(unsigned int e = 0;e<electron.size();++e){
	MonoTauIso_Nq_Fq_ObjectSelectionCollection.electron.push_back(&electron[e]);
	MonoTauIso_Nq_pT_ObjectSelectionCollection.electron.push_back(&electron[e]);
	MonoTauIso_Nq_Abseta_ObjectSelectionCollection.electron.push_back(&electron[e]);
	MonoTauIso_Fq_pT_ObjectSelectionCollection.electron.push_back(&electron[e]);
	MonoTauIso_Fq_Abseta_ObjectSelectionCollection.electron.push_back(&electron[e]);
	MonoTauIso_pT_Abseta_ObjectSelectionCollection.electron.push_back(&electron[e]);  
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
	MonoTauIso_Nq_Fq_ObjectSelectionCollection.muon.push_back(&muon[m]);
	MonoTauIso_Nq_pT_ObjectSelectionCollection.muon.push_back(&muon[m]);
	MonoTauIso_Nq_Abseta_ObjectSelectionCollection.muon.push_back(&muon[m]);
	MonoTauIso_Fq_pT_ObjectSelectionCollection.muon.push_back(&muon[m]);
	MonoTauIso_Fq_Abseta_ObjectSelectionCollection.muon.push_back(&muon[m]);
	MonoTauIso_pT_Abseta_ObjectSelectionCollection.muon.push_back(&muon[m]);  
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

TH2F* Nq_Fq = (TH2F*)(file_eff.Get("h2_Nq_Fq_eff"));
TH2F* Nq_pT = (TH2F*)(file_eff.Get("h2_Nq_pT_eff"));
TH2F* Nq_Abseta = (TH2F*)(file_eff.Get("h2_Nq_Abseta_eff"));
TH2F* Fq_pT = (TH2F*)(file_eff.Get("h2_Fq_pT_eff"));
TH2F* Fq_Abseta = (TH2F*)(file_eff.Get("h2_Fq_Abseta_eff"));
TH2F* pT_Abseta = (TH2F*)(file_eff.Get("h2_pT_Abseta_eff"));

TProfile* ReweightFactorT = (TProfile*)(file_Resp.Get("RescaleWeightT"));
TProfile* ScaleFactorT    = (TProfile*)(file_Resp.Get("ScaleFactorT"));

vector<double> jet_taufakerate_Nq_Fq;
vector<double> jet_taufakerate_Nq_pT;
vector<double> jet_taufakerate_Nq_Abseta;
vector<double> jet_taufakerate_Fq_pT;
vector<double> jet_taufakerate_Fq_Abseta;
vector<double> jet_taufakerate_pT_Abseta;
vector<double> jet_taufakerate_even;

for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
double jetMindR	  = JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
double Nq	  = JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity;
double Fq	  = JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction;
int nRescaleBinT  = ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinNq_Fq 	  = Nq_Fq->FindBin(Nq,Fq);
int nbinNq_pT 	  = Nq_pT->FindBin(Nq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinNq_Abseta = Nq_Abseta->FindBin(Nq,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
int nbinFq_pT 	  = Fq_pT->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinFq_Abseta = Fq_Abseta->FindBin(Fq,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
int nbinpT_Abseta = pT_Abseta->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
if(verbose)std::cout<<"Jet "<<i<<" out of "<<JetLooseIsoObjectSelectionCollection.jet.size()<<": pT="<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", eta="<<JetLooseIsoObjectSelectionCollection.jet[i]->eta<<", phi="<<JetLooseIsoObjectSelectionCollection.jet[i]->phi<<std::endl;
if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.1)
  {
    jet_taufakerate_Nq_Fq.push_back(Nq_Fq->GetBinContent(nbinNq_Fq)*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Nq_pT.push_back(Nq_pT->GetBinContent(nbinNq_pT)*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Nq_Abseta.push_back(Nq_Abseta->GetBinContent(nbinNq_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Fq_pT.push_back(Fq_pT->GetBinContent(nbinFq_pT)*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Fq_Abseta.push_back(Fq_Abseta->GetBinContent(nbinFq_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_pT_Abseta.push_back(pT_Abseta->GetBinContent(nbinpT_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
    if(JetLooseIsoObjectSelectionCollection.jet[i]->pt*scale>45) jet_taufakerate_even.push_back(1.);
    else  jet_taufakerate_even.push_back(0.);                 
  }
/*else
  {
    double jetMindR2=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
    if(jetMindR > 0.5 && jetMindR2 > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.2)
      {
    	jet_taufakerate_Nq_Fq.push_back(Nq_Fq->GetBinContent(nbinNq_Fq)*ReweightFactorT->GetBinContent(nRescaleBinT));
    	jet_taufakerate_Nq_pT.push_back(Nq_pT->GetBinContent(nbinNq_pT)*ReweightFactorT->GetBinContent(nRescaleBinT));
    	jet_taufakerate_Nq_Abseta.push_back(Nq_Abseta->GetBinContent(nbinNq_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
    	jet_taufakerate_Fq_pT.push_back(Fq_pT->GetBinContent(nbinFq_pT)*ReweightFactorT->GetBinContent(nRescaleBinT));
    	jet_taufakerate_Fq_Abseta.push_back(Fq_Abseta->GetBinContent(nbinFq_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
    	jet_taufakerate_pT_Abseta.push_back(pT_Abseta->GetBinContent(nbinpT_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
    	if(JetLooseIsoObjectSelectionCollection.jet[i]->pt*scale>45) jet_taufakerate_even.push_back(1.);
    	else  jet_taufakerate_even.push_back(0.); 
      }*/
    else
      {
    	jet_taufakerate_Nq_Fq.push_back(0.);
    	jet_taufakerate_Nq_pT.push_back(0.);
    	jet_taufakerate_Nq_Abseta.push_back(0.);
    	jet_taufakerate_Fq_pT.push_back(0.);
    	jet_taufakerate_Fq_Abseta.push_back(0.);
    	jet_taufakerate_pT_Abseta.push_back(0.);
    	jet_taufakerate_even.push_back(0.);
      }
  //}
}


Fake FakeTaus_Nq_Fq("FakeTaus_Nq_Fq");

FakeTaus_Nq_Fq.generate(jet_taufakerate_Nq_Fq,jet_taufakerate_even, false);

tau_s faketau1_Nq_Fq;
tau_s faketau2_Nq_Fq;

if ( FakeTaus_Nq_Fq.index.first >= 0 && FakeTaus_Nq_Fq.index.second >= 0 ) {
//recalculate weight
FakeTaus_Nq_Fq.weight=0;
for(int i=0; i<jet_taufakerate_Nq_Fq.size(); i++){
  double temp=jet_taufakerate_Nq_Fq[i];
  for(int j=0; j<jet_taufakerate_Nq_Fq.size(); j++){
    if(i==j) continue;
    temp*=(1-jet_taufakerate_Nq_Fq[j]);
  }
  FakeTaus_Nq_Fq.weight+=temp;
}
//std::cout<<"enter"<<std::endl;
int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->pt);
double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
if(scale == 0) {scale = 0.851; FakeTaus_Nq_Fq.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->charge >= 0 )
faketau1_Nq_Fq.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->charge < 0 )
faketau1_Nq_Fq.charge = -1;
faketau1_Nq_Fq.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->p;
faketau1_Nq_Fq.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->energy;
faketau1_Nq_Fq.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->et;
faketau1_Nq_Fq.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->px;
faketau1_Nq_Fq.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->py;
faketau1_Nq_Fq.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->pz;
faketau1_Nq_Fq.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->pt * scale;
if(faketau1_Nq_Fq.pt < 45) FakeTaus_Nq_Fq.weight=0;
faketau1_Nq_Fq.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->eta<=2.1) faketau1_Nq_Fq.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->eta;
else faketau1_Nq_Fq.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.first]->eta)*2.1;

int nScaleBin2	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->pt);
double scale2 	  = ScaleFactorT->GetBinContent(nScaleBin2);
if(scale2 == 0) {scale2 = 0.851; FakeTaus_Nq_Fq.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->charge >= 0 )
faketau2_Nq_Fq.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->charge < 0 )
faketau2_Nq_Fq.charge = -1;	
faketau2_Nq_Fq.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->p;
faketau2_Nq_Fq.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->energy;
faketau2_Nq_Fq.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->et;
faketau2_Nq_Fq.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->px;
faketau2_Nq_Fq.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->py;
faketau2_Nq_Fq.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->pz;
faketau2_Nq_Fq.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->pt * scale2;
if(faketau2_Nq_Fq.pt < 45) FakeTaus_Nq_Fq.weight=0;
faketau2_Nq_Fq.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->eta<=2.1) faketau2_Nq_Fq.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->eta;
else faketau2_Nq_Fq.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Fq.index.second]->eta)*2.1;

if(faketau1_Nq_Fq.pt > faketau2_Nq_Fq.pt){
  MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau.push_back(&faketau1_Nq_Fq);
  MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau.push_back(&faketau2_Nq_Fq);
}
else{
  MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau.push_back(&faketau2_Nq_Fq);
  MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau.push_back(&faketau1_Nq_Fq);
}

}
else FakeTaus_Nq_Fq.weight=0;

Fake FakeTaus_Nq_pT("FakeTaus_Nq_pT");

FakeTaus_Nq_pT.generate(jet_taufakerate_Nq_pT,jet_taufakerate_even, false);

tau_s faketau1_Nq_pT;
tau_s faketau2_Nq_pT;

if ( FakeTaus_Nq_pT.index.first >= 0 && FakeTaus_Nq_pT.index.second >= 0 ) {
//recalculate weight
FakeTaus_Nq_pT.weight=0;
for(int i=0; i<jet_taufakerate_Nq_pT.size(); i++){
  double temp=jet_taufakerate_Nq_pT[i];
  for(int j=0; j<jet_taufakerate_Nq_pT.size(); j++){
    if(i==j) continue;
    temp*=(1-jet_taufakerate_Nq_pT[j]);
  }
  FakeTaus_Nq_pT.weight+=temp;
}
int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->pt);
double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
if(scale == 0) {scale = 0.851; FakeTaus_Nq_pT.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->charge >= 0 )
faketau1_Nq_pT.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->charge < 0 )
faketau1_Nq_pT.charge = -1;
faketau1_Nq_pT.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->p;
faketau1_Nq_pT.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->energy;
faketau1_Nq_pT.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->et;
faketau1_Nq_pT.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->px;
faketau1_Nq_pT.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->py;
faketau1_Nq_pT.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->pz;
faketau1_Nq_pT.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->pt * scale;
if(faketau1_Nq_pT.pt < 45) FakeTaus_Nq_pT.weight=0;
faketau1_Nq_pT.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->eta<=2.1) faketau1_Nq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->eta;
else faketau1_Nq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.first]->eta)*2.1;

int nScaleBin2	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->pt);
double scale2 	  = ScaleFactorT->GetBinContent(nScaleBin2);
if(scale2 == 0) {scale2 = 0.851; FakeTaus_Nq_pT.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->charge >= 0 )
faketau2_Nq_pT.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->charge < 0 )
faketau2_Nq_pT.charge = -1;	
faketau2_Nq_pT.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->p;
faketau2_Nq_pT.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->energy;
faketau2_Nq_pT.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->et;
faketau2_Nq_pT.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->px;
faketau2_Nq_pT.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->py;
faketau2_Nq_pT.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->pz;
faketau2_Nq_pT.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->pt * scale2;
if(faketau2_Nq_pT.pt < 45) FakeTaus_Nq_pT.weight=0;
faketau2_Nq_pT.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->eta<=2.1) faketau2_Nq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->eta;
else faketau2_Nq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_pT.index.second]->eta)*2.1;

if(faketau1_Nq_pT.pt > faketau2_Nq_pT.pt){
  MonoTauIso_Nq_pT_ObjectSelectionCollection.tau.push_back(&faketau1_Nq_pT);
  MonoTauIso_Nq_pT_ObjectSelectionCollection.tau.push_back(&faketau2_Nq_pT);
}
else{
  MonoTauIso_Nq_pT_ObjectSelectionCollection.tau.push_back(&faketau2_Nq_pT);
  MonoTauIso_Nq_pT_ObjectSelectionCollection.tau.push_back(&faketau1_Nq_pT);
}

}
else FakeTaus_Nq_pT.weight=0;

Fake FakeTaus_Nq_Abseta("FakeTaus_Nq_Abseta");

FakeTaus_Nq_Abseta.generate(jet_taufakerate_Nq_Abseta,jet_taufakerate_even, false);

tau_s faketau1_Nq_Abseta;
tau_s faketau2_Nq_Abseta;

if ( FakeTaus_Nq_Abseta.index.first >= 0 && FakeTaus_Nq_Abseta.index.second >= 0 ) {
//recalculate weight
FakeTaus_Nq_Abseta.weight=0;
for(int i=0; i<jet_taufakerate_Nq_Abseta.size(); i++){
  double temp=jet_taufakerate_Nq_Abseta[i];
  for(int j=0; j<jet_taufakerate_Nq_Abseta.size(); j++){
    if(i==j) continue;
    temp*=(1-jet_taufakerate_Nq_Abseta[j]);
  }
  FakeTaus_Nq_Abseta.weight+=temp;
}
int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->pt);
double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
if(scale == 0) {scale = 0.851; FakeTaus_Nq_Abseta.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->charge >= 0 )
faketau1_Nq_Abseta.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->charge < 0 )
faketau1_Nq_Abseta.charge = -1;
faketau1_Nq_Abseta.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->p;
faketau1_Nq_Abseta.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->energy;
faketau1_Nq_Abseta.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->et;
faketau1_Nq_Abseta.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->px;
faketau1_Nq_Abseta.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->py;
faketau1_Nq_Abseta.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->pz;
faketau1_Nq_Abseta.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->pt * scale;
if(faketau1_Nq_Abseta.pt < 45) FakeTaus_Nq_Abseta.weight=0;
faketau1_Nq_Abseta.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->eta<=2.1) faketau1_Nq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->eta;
else faketau1_Nq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.first]->eta)*2.1;

int nScaleBin2	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->pt);
double scale2 	  = ScaleFactorT->GetBinContent(nScaleBin2);
if(scale2 == 0) {scale2 = 0.851; FakeTaus_Nq_Abseta.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->charge >= 0 )
faketau2_Nq_Abseta.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->charge < 0 )
faketau2_Nq_Abseta.charge = -1;	
faketau2_Nq_Abseta.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->p;
faketau2_Nq_Abseta.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->energy;
faketau2_Nq_Abseta.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->et;
faketau2_Nq_Abseta.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->px;
faketau2_Nq_Abseta.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->py;
faketau2_Nq_Abseta.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->pz;
faketau2_Nq_Abseta.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->pt * scale2;
if(faketau2_Nq_Abseta.pt < 45) FakeTaus_Nq_Abseta.weight=0;
faketau2_Nq_Abseta.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->eta<=2.1) faketau2_Nq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->eta;
else faketau2_Nq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Nq_Abseta.index.second]->eta)*2.1;

if(faketau1_Nq_Abseta.pt > faketau2_Nq_Abseta.pt){
  MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau1_Nq_Abseta);
  MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau2_Nq_Abseta);
}
else{
  MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau2_Nq_Abseta);
  MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau1_Nq_Abseta);
}

}
else FakeTaus_Nq_Abseta.weight=0;

Fake FakeTaus_Fq_pT("FakeTaus_Fq_pT");

FakeTaus_Fq_pT.generate(jet_taufakerate_Fq_pT,jet_taufakerate_even, false);

tau_s faketau1_Fq_pT;
tau_s faketau2_Fq_pT;

if ( FakeTaus_Fq_pT.index.first >= 0 && FakeTaus_Fq_pT.index.second >= 0 ) {
//recalculate weight
FakeTaus_Fq_pT.weight=0;
for(int i=0; i<jet_taufakerate_Fq_pT.size(); i++){
  double temp=jet_taufakerate_Fq_pT[i];
  for(int j=0; j<jet_taufakerate_Fq_pT.size(); j++){
    if(i==j) continue;
    temp*=(1-jet_taufakerate_Fq_pT[j]);
  }
  FakeTaus_Fq_pT.weight+=temp;
}
int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->pt);
double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
if(scale == 0) {scale = 0.851; FakeTaus_Fq_pT.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->charge >= 0 )
faketau1_Fq_pT.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->charge < 0 )
faketau1_Fq_pT.charge = -1;
faketau1_Fq_pT.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->p;
faketau1_Fq_pT.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->energy;
faketau1_Fq_pT.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->et;
faketau1_Fq_pT.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->px;
faketau1_Fq_pT.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->py;
faketau1_Fq_pT.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->pz;
faketau1_Fq_pT.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->pt * scale;
if(faketau1_Fq_pT.pt < 45) FakeTaus_Fq_pT.weight=0;
faketau1_Fq_pT.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->eta<=2.1) faketau1_Fq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->eta;
else faketau1_Fq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.first]->eta)*2.1;

int nScaleBin2	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->pt);
double scale2 	  = ScaleFactorT->GetBinContent(nScaleBin2);
if(scale2 == 0) {scale2 = 0.851; FakeTaus_Fq_pT.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->charge >= 0 )
faketau2_Fq_pT.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->charge < 0 )
faketau2_Fq_pT.charge = -1;	
faketau2_Fq_pT.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->p;
faketau2_Fq_pT.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->energy;
faketau2_Fq_pT.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->et;
faketau2_Fq_pT.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->px;
faketau2_Fq_pT.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->py;
faketau2_Fq_pT.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->pz;
faketau2_Fq_pT.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->pt * scale2;
if(faketau2_Fq_pT.pt < 45) FakeTaus_Fq_pT.weight=0;
faketau2_Fq_pT.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->eta<=2.1) faketau2_Fq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->eta;
else faketau2_Fq_pT.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_pT.index.second]->eta)*2.1;

if(faketau1_Fq_pT.pt > faketau2_Fq_pT.pt){
  MonoTauIso_Fq_pT_ObjectSelectionCollection.tau.push_back(&faketau1_Fq_pT);
  MonoTauIso_Fq_pT_ObjectSelectionCollection.tau.push_back(&faketau2_Fq_pT);
}
else{
  MonoTauIso_Fq_pT_ObjectSelectionCollection.tau.push_back(&faketau2_Fq_pT);
  MonoTauIso_Fq_pT_ObjectSelectionCollection.tau.push_back(&faketau1_Fq_pT);
}

}
else FakeTaus_Fq_pT.weight=0;

Fake FakeTaus_Fq_Abseta("FakeTaus_Fq_Abseta");

FakeTaus_Fq_Abseta.generate(jet_taufakerate_Fq_Abseta,jet_taufakerate_even, false);

tau_s faketau1_Fq_Abseta;
tau_s faketau2_Fq_Abseta;

if ( FakeTaus_Fq_Abseta.index.first >= 0 && FakeTaus_Fq_Abseta.index.second >= 0 ) {
//recalculate weight
FakeTaus_Fq_Abseta.weight=0;
for(int i=0; i<jet_taufakerate_Fq_Abseta.size(); i++){
  double temp=jet_taufakerate_Fq_Abseta[i];
  for(int j=0; j<jet_taufakerate_Fq_Abseta.size(); j++){
    if(i==j) continue;
    temp*=(1-jet_taufakerate_Fq_Abseta[j]);
  }
  FakeTaus_Fq_Abseta.weight+=temp;
}
int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->pt);
double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
if(scale == 0) {scale = 0.851; FakeTaus_Fq_Abseta.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->charge >= 0 )
faketau1_Fq_Abseta.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->charge < 0 )
faketau1_Fq_Abseta.charge = -1;
faketau1_Fq_Abseta.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->p;
faketau1_Fq_Abseta.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->energy;
faketau1_Fq_Abseta.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->et;
faketau1_Fq_Abseta.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->px;
faketau1_Fq_Abseta.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->py;
faketau1_Fq_Abseta.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->pz;
faketau1_Fq_Abseta.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->pt * scale;
if(faketau1_Fq_Abseta.pt < 45) FakeTaus_Fq_Abseta.weight=0;
faketau1_Fq_Abseta.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->eta<=2.1) faketau1_Fq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->eta;
else faketau1_Fq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.first]->eta)*2.1;

int nScaleBin2	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->pt);
double scale2 	  = ScaleFactorT->GetBinContent(nScaleBin2);
if(scale2 == 0) {scale2 = 0.851; FakeTaus_Fq_Abseta.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->charge >= 0 )
faketau2_Fq_Abseta.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->charge < 0 )
faketau2_Fq_Abseta.charge = -1;	
faketau2_Fq_Abseta.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->p;
faketau2_Fq_Abseta.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->energy;
faketau2_Fq_Abseta.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->et;
faketau2_Fq_Abseta.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->px;
faketau2_Fq_Abseta.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->py;
faketau2_Fq_Abseta.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->pz;
faketau2_Fq_Abseta.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->pt * scale2;
if(faketau2_Fq_Abseta.pt < 45) FakeTaus_Fq_Abseta.weight=0;
faketau2_Fq_Abseta.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->eta<=2.1) faketau2_Fq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->eta;
else faketau2_Fq_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_Fq_Abseta.index.second]->eta)*2.1;

if(faketau1_Fq_Abseta.pt > faketau2_Fq_Abseta.pt){
  MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau1_Fq_Abseta);
  MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau2_Fq_Abseta);
}
else{
  MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau2_Fq_Abseta);
  MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau.push_back(&faketau1_Fq_Abseta);
}

}
else FakeTaus_Fq_Abseta.weight=0;

Fake FakeTaus_pT_Abseta("FakeTaus_pT_Abseta");

FakeTaus_pT_Abseta.generate(jet_taufakerate_pT_Abseta,jet_taufakerate_even, false);

tau_s faketau1_pT_Abseta;
tau_s faketau2_pT_Abseta;

if ( FakeTaus_pT_Abseta.index.first >= 0 && FakeTaus_pT_Abseta.index.second >= 0 ) {
//recalculate weight
FakeTaus_pT_Abseta.weight=0;
for(int i=0; i<jet_taufakerate_pT_Abseta.size(); i++){
  double temp=jet_taufakerate_pT_Abseta[i];
  for(int j=0; j<jet_taufakerate_pT_Abseta.size(); j++){
    if(i==j) continue;
    temp*=(1-jet_taufakerate_pT_Abseta[j]);
  }
  FakeTaus_pT_Abseta.weight+=temp;
}
int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->pt);
double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
if(scale == 0) {scale = 0.851; FakeTaus_pT_Abseta.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->charge >= 0 )
faketau1_pT_Abseta.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->charge < 0 )
faketau1_pT_Abseta.charge = -1;
faketau1_pT_Abseta.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->p;
faketau1_pT_Abseta.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->energy;
faketau1_pT_Abseta.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->et;
faketau1_pT_Abseta.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->px;
faketau1_pT_Abseta.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->py;
faketau1_pT_Abseta.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->pz;
faketau1_pT_Abseta.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->pt * scale;
if(faketau1_pT_Abseta.pt < 45) FakeTaus_pT_Abseta.weight=0;
faketau1_pT_Abseta.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->eta<=2.1) faketau1_pT_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->eta;
else faketau1_pT_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.first]->eta)*2.1;

int nScaleBin2	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->pt);
double scale2 	  = ScaleFactorT->GetBinContent(nScaleBin2);
if(scale2 == 0) {scale2 = 0.851; FakeTaus_pT_Abseta.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->charge >= 0 )
faketau2_pT_Abseta.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->charge < 0 )
faketau2_pT_Abseta.charge = -1;	
faketau2_pT_Abseta.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->p;
faketau2_pT_Abseta.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->energy;
faketau2_pT_Abseta.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->et;
faketau2_pT_Abseta.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->px;
faketau2_pT_Abseta.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->py;
faketau2_pT_Abseta.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->pz;
faketau2_pT_Abseta.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->pt * scale2;
if(faketau2_pT_Abseta.pt < 45) FakeTaus_pT_Abseta.weight=0;
faketau2_pT_Abseta.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->eta<=2.1) faketau2_pT_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->eta;
else faketau2_pT_Abseta.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTaus_pT_Abseta.index.second]->eta)*2.1;

if(faketau1_pT_Abseta.pt > faketau2_pT_Abseta.pt){
  MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau.push_back(&faketau1_pT_Abseta);
  MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau.push_back(&faketau2_pT_Abseta);
}
else{
  MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau.push_back(&faketau2_pT_Abseta);
  MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau.push_back(&faketau1_pT_Abseta);
}

}
else FakeTaus_pT_Abseta.weight=0;

int counter = 0;
int exitus = 0;
// jet && bjet selection
// ? id ?
for(unsigned int j = 0;j<jet.size();++j){
if(!( jet[j].pt >= 30. )) continue; // Original value 20
if(!( fabs(jet[j].eta) <= 5.0 )) continue;
double Distance_Nq_Fq 		= TauJetMinDistance(MonoTauIso_Nq_Fq_ObjectSelectionCollection, jet[j].eta, jet[j].phi);
double Distance_Nq_pT 		= TauJetMinDistance(MonoTauIso_Nq_pT_ObjectSelectionCollection, jet[j].eta, jet[j].phi);
double Distance_Nq_Abseta 	= TauJetMinDistance(MonoTauIso_Nq_Abseta_ObjectSelectionCollection, jet[j].eta, jet[j].phi);
double Distance_Fq_pT 		= TauJetMinDistance(MonoTauIso_Fq_pT_ObjectSelectionCollection, jet[j].eta, jet[j].phi);
double Distance_Fq_Abseta 	= TauJetMinDistance(MonoTauIso_Fq_Abseta_ObjectSelectionCollection, jet[j].eta, jet[j].phi);
double Distance_pT_Abseta 	= TauJetMinDistance(MonoTauIso_pT_Abseta_ObjectSelectionCollection, jet[j].eta, jet[j].phi);
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
  if(	Distance_Nq_Fq 		>= 0.3	) MonoTauIso_Nq_Fq_ObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	Distance_Nq_pT 		>= 0.3	) MonoTauIso_Nq_pT_ObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	Distance_Nq_Abseta 	>= 0.3	) MonoTauIso_Nq_Abseta_ObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	Distance_Fq_pT 		>= 0.3	) MonoTauIso_Fq_pT_ObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	Distance_Fq_Abseta	>= 0.3	) MonoTauIso_Fq_Abseta_ObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	Distance_pT_Abseta 	>= 0.3	) MonoTauIso_pT_Abseta_ObjectSelectionCollection.jet.push_back(&jet[j]);
  else exitus++;
  counter++;
            }
if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244 ){
  if(	Distance_Nq_Fq 		>= 0.3	) MonoTauIso_Nq_Fq_ObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	Distance_Nq_pT 		>= 0.3	) MonoTauIso_Nq_pT_ObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	Distance_Nq_Abseta 	>= 0.3	) MonoTauIso_Nq_Abseta_ObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	Distance_Fq_pT 		>= 0.3	) MonoTauIso_Fq_pT_ObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	Distance_Fq_Abseta	>= 0.3	) MonoTauIso_Fq_Abseta_ObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	Distance_pT_Abseta 	>= 0.3	) MonoTauIso_pT_Abseta_ObjectSelectionCollection.bjet.push_back(&jet[j]);
            }
}
//std::cout<<counter<<", "<<exitus<<std::endl;
//std::cout<<MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau.size()<<" yields "<<counter<<" vs "<<MonoTauIso_Nq_Fq_ObjectSelectionCollection.jet.size()<<" with weight = "<< FakeTaus_Nq_Fq.weight<<std::endl;
//MET selection
MonoTauIso_Nq_Fq_ObjectSelectionCollection.met.push_back(&met[0]);
MonoTauIso_Nq_pT_ObjectSelectionCollection.met.push_back(&met[0]);
MonoTauIso_Nq_Abseta_ObjectSelectionCollection.met.push_back(&met[0]);
MonoTauIso_Fq_pT_ObjectSelectionCollection.met.push_back(&met[0]);
MonoTauIso_Fq_Abseta_ObjectSelectionCollection.met.push_back(&met[0]);
MonoTauIso_pT_Abseta_ObjectSelectionCollection.met.push_back(&met[0]);  

//Event Count
ofile.count("NoCuts");
//if(MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau.size()==2 && (MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau[0]->pt < 50 || MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau[1]->pt < 50))MonoTauIso_Nq_Fq_ObjectSelectionCollection.tau.clear();
// ---------------------
// -- Signal Region --
// ---------------------

Selection SR_Nq_Fq("SR_Nq_Fq"); //label and initialisation
SR_Nq_Fq.InputCollection 	= &MonoTauIso_Nq_Fq_ObjectSelectionCollection;        //input collection
SR_Nq_Fq.OutputCollection 	= &myHistoColl_SR_Nq_Fq;        //output collection
SR_Nq_Fq.RealData        	= eventhelper_isRealData;        //pass information if event is real data
SR_Nq_Fq.RunData        	= false;        //real data allowed
SR_Nq_Fq.NumberTauMin        	= 2;        //require at least N tau
SR_Nq_Fq.NumberTauMax        	= 3;        //require at less than N taus
SR_Nq_Fq.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
SR_Nq_Fq.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
SR_Nq_Fq.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
SR_Nq_Fq.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
SR_Nq_Fq.Btag        		= 0;        //number of btags required (exact -> 0 = none)
SR_Nq_Fq.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
SR_Nq_Fq.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
SR_Nq_Fq.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
SR_Nq_Fq.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
SR_Nq_Fq.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
SR_Nq_Fq.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
SR_Nq_Fq.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
SR_Nq_Fq.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
SR_Nq_Fq.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
SR_Nq_Fq.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
SR_Nq_Fq.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
SR_Nq_Fq.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
SR_Nq_Fq.weight        	= FakeTaus_Nq_Fq.weight;        //event weight
SR_Nq_Fq.invertTauRequirements    = false;        //invert number of taus requirement
SR_Nq_Fq.invertTauProperties      = false;        //invert ditau properties (dR, sign)
SR_Nq_Fq.invertBtagRequirement    = false;        //invert number of b-jets required
SR_Nq_Fq.invertJetRequirements    = false;        //invert jet pt requirements
SR_Nq_Fq.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

SR_Nq_Fq.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection CR_Nq_Fq("CR_Nq_Fq"); //label and initialisation
CR_Nq_Fq.InputCollection 	= &MonoTauIso_Nq_Fq_ObjectSelectionCollection;        //input collection
CR_Nq_Fq.OutputCollection 	= &myHistoColl_CR_Nq_Fq;        //output collection
CR_Nq_Fq.RealData        	= eventhelper_isRealData;        //pass information if event is real data
CR_Nq_Fq.RunData        	= true;        //real data allowed
CR_Nq_Fq.NumberTauMin        	= 2;        //require at least N tau
CR_Nq_Fq.NumberTauMax        	= 3;        //require at less than N taus
CR_Nq_Fq.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
CR_Nq_Fq.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
CR_Nq_Fq.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
CR_Nq_Fq.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
CR_Nq_Fq.Btag        		= 0;        //number of btags required (exact -> 0 = none)
CR_Nq_Fq.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
CR_Nq_Fq.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
CR_Nq_Fq.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
CR_Nq_Fq.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
CR_Nq_Fq.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
CR_Nq_Fq.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
CR_Nq_Fq.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
CR_Nq_Fq.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
CR_Nq_Fq.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
CR_Nq_Fq.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
CR_Nq_Fq.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
CR_Nq_Fq.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
CR_Nq_Fq.weight        	= FakeTaus_Nq_Fq.weight;        //event weight
CR_Nq_Fq.invertTauRequirements   = false;        //invert number of taus requirement
CR_Nq_Fq.invertTauProperties     = false;        //invert ditau properties (dR, sign)
CR_Nq_Fq.invertBtagRequirement   = false;        //invert number of b-jets required
CR_Nq_Fq.invertJetRequirements   = true;        //invert jet pt requirements
CR_Nq_Fq.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

CR_Nq_Fq.select();        //do selection, fill histograms

//if(MonoTauIso_Nq_pT_ObjectSelectionCollection.tau.size()==2 && (MonoTauIso_Nq_pT_ObjectSelectionCollection.tau[0]->pt < 50 || MonoTauIso_Nq_pT_ObjectSelectionCollection.tau[1]->pt < 50))MonoTauIso_Nq_pT_ObjectSelectionCollection.tau.clear();
// ---------------------
// -- Signal Region --
// ---------------------

Selection SR_Nq_pT("SR_Nq_pT"); //label and initialisation
SR_Nq_pT.InputCollection 	= &MonoTauIso_Nq_pT_ObjectSelectionCollection;        //input collection
SR_Nq_pT.OutputCollection 	= &myHistoColl_SR_Nq_pT;        //output collection
SR_Nq_pT.RealData        	= eventhelper_isRealData;        //pass information if event is real data
SR_Nq_pT.RunData        	= false;        //real data allowed
SR_Nq_pT.NumberTauMin        	= 2;        //require at least N tau
SR_Nq_pT.NumberTauMax        	= 3;        //require at less than N taus
SR_Nq_pT.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
SR_Nq_pT.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
SR_Nq_pT.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
SR_Nq_pT.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
SR_Nq_pT.Btag        		= 0;        //number of btags required (exact -> 0 = none)
SR_Nq_pT.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
SR_Nq_pT.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
SR_Nq_pT.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
SR_Nq_pT.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
SR_Nq_pT.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
SR_Nq_pT.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
SR_Nq_pT.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
SR_Nq_pT.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
SR_Nq_pT.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
SR_Nq_pT.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
SR_Nq_pT.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
SR_Nq_pT.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
SR_Nq_pT.weight        	= FakeTaus_Nq_pT.weight;        //event weight
SR_Nq_pT.invertTauRequirements    = false;        //invert number of taus requirement
SR_Nq_pT.invertTauProperties      = false;        //invert ditau properties (dR, sign)
SR_Nq_pT.invertBtagRequirement    = false;        //invert number of b-jets required
SR_Nq_pT.invertJetRequirements    = false;        //invert jet pt requirements
SR_Nq_pT.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

SR_Nq_pT.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection CR_Nq_pT("CR_Nq_pT"); //label and initialisation
CR_Nq_pT.InputCollection 	= &MonoTauIso_Nq_pT_ObjectSelectionCollection;        //input collection
CR_Nq_pT.OutputCollection 	= &myHistoColl_CR_Nq_pT;        //output collection
CR_Nq_pT.RealData        	= eventhelper_isRealData;        //pass information if event is real data
CR_Nq_pT.RunData        	= true;        //real data allowed
CR_Nq_pT.NumberTauMin        	= 2;        //require at least N tau
CR_Nq_pT.NumberTauMax        	= 3;        //require at less than N taus
CR_Nq_pT.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
CR_Nq_pT.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
CR_Nq_pT.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
CR_Nq_pT.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
CR_Nq_pT.Btag        		= 0;        //number of btags required (exact -> 0 = none)
CR_Nq_pT.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
CR_Nq_pT.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
CR_Nq_pT.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
CR_Nq_pT.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
CR_Nq_pT.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
CR_Nq_pT.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
CR_Nq_pT.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
CR_Nq_pT.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
CR_Nq_pT.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
CR_Nq_pT.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
CR_Nq_pT.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
CR_Nq_pT.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
CR_Nq_pT.weight        	= FakeTaus_Nq_pT.weight;        //event weight
CR_Nq_pT.invertTauRequirements   = false;        //invert number of taus requirement
CR_Nq_pT.invertTauProperties     = false;        //invert ditau properties (dR, sign)
CR_Nq_pT.invertBtagRequirement   = false;        //invert number of b-jets required
CR_Nq_pT.invertJetRequirements   = true;        //invert jet pt requirements
CR_Nq_pT.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

CR_Nq_pT.select();        //do selection, fill histograms

//if(MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau.size()==2 && (MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau[0]->pt < 50 || MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau[1]->pt < 50))MonoTauIso_Nq_Abseta_ObjectSelectionCollection.tau.clear();
// ---------------------
// -- Signal Region --
// ---------------------

Selection SR_Nq_Abseta("SR_Nq_Abseta"); //label and initialisation
SR_Nq_Abseta.InputCollection 	= &MonoTauIso_Nq_Abseta_ObjectSelectionCollection;        //input collection
SR_Nq_Abseta.OutputCollection 	= &myHistoColl_SR_Nq_Abseta;        //output collection
SR_Nq_Abseta.RealData        	= eventhelper_isRealData;        //pass information if event is real data
SR_Nq_Abseta.RunData        	= false;        //real data allowed
SR_Nq_Abseta.NumberTauMin        	= 2;        //require at least N tau
SR_Nq_Abseta.NumberTauMax        	= 3;        //require at less than N taus
SR_Nq_Abseta.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
SR_Nq_Abseta.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
SR_Nq_Abseta.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
SR_Nq_Abseta.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
SR_Nq_Abseta.Btag        		= 0;        //number of btags required (exact -> 0 = none)
SR_Nq_Abseta.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
SR_Nq_Abseta.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
SR_Nq_Abseta.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
SR_Nq_Abseta.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
SR_Nq_Abseta.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
SR_Nq_Abseta.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
SR_Nq_Abseta.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
SR_Nq_Abseta.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
SR_Nq_Abseta.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
SR_Nq_Abseta.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
SR_Nq_Abseta.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
SR_Nq_Abseta.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
SR_Nq_Abseta.weight        	= FakeTaus_Nq_Abseta.weight;        //event weight
SR_Nq_Abseta.invertTauRequirements    = false;        //invert number of taus requirement
SR_Nq_Abseta.invertTauProperties      = false;        //invert ditau properties (dR, sign)
SR_Nq_Abseta.invertBtagRequirement    = false;        //invert number of b-jets required
SR_Nq_Abseta.invertJetRequirements    = false;        //invert jet pt requirements
SR_Nq_Abseta.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

SR_Nq_Abseta.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection CR_Nq_Abseta("CR_Nq_Abseta"); //label and initialisation
CR_Nq_Abseta.InputCollection 	= &MonoTauIso_Nq_Abseta_ObjectSelectionCollection;        //input collection
CR_Nq_Abseta.OutputCollection 	= &myHistoColl_CR_Nq_Abseta;        //output collection
CR_Nq_Abseta.RealData        	= eventhelper_isRealData;        //pass information if event is real data
CR_Nq_Abseta.RunData        	= true;        //real data allowed
CR_Nq_Abseta.NumberTauMin        	= 2;        //require at least N tau
CR_Nq_Abseta.NumberTauMax        	= 3;        //require at less than N taus
CR_Nq_Abseta.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
CR_Nq_Abseta.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
CR_Nq_Abseta.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
CR_Nq_Abseta.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
CR_Nq_Abseta.Btag        		= 0;        //number of btags required (exact -> 0 = none)
CR_Nq_Abseta.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
CR_Nq_Abseta.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
CR_Nq_Abseta.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
CR_Nq_Abseta.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
CR_Nq_Abseta.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
CR_Nq_Abseta.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
CR_Nq_Abseta.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
CR_Nq_Abseta.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
CR_Nq_Abseta.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
CR_Nq_Abseta.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
CR_Nq_Abseta.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
CR_Nq_Abseta.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
CR_Nq_Abseta.weight        	= FakeTaus_Nq_Abseta.weight;        //event weight
CR_Nq_Abseta.invertTauRequirements   = false;        //invert number of taus requirement
CR_Nq_Abseta.invertTauProperties     = false;        //invert ditau properties (dR, sign)
CR_Nq_Abseta.invertBtagRequirement   = false;        //invert number of b-jets required
CR_Nq_Abseta.invertJetRequirements   = true;        //invert jet pt requirements
CR_Nq_Abseta.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

CR_Nq_Abseta.select();        //do selection, fill histograms

//if(MonoTauIso_Fq_pT_ObjectSelectionCollection.tau.size()==2 && (MonoTauIso_Fq_pT_ObjectSelectionCollection.tau[0]->pt < 50 || MonoTauIso_Fq_pT_ObjectSelectionCollection.tau[1]->pt < 50))MonoTauIso_Fq_pT_ObjectSelectionCollection.tau.clear();
// ---------------------
// -- Signal Region --
// ---------------------

Selection SR_Fq_pT("SR_Fq_pT"); //label and initialisation
SR_Fq_pT.InputCollection 	= &MonoTauIso_Fq_pT_ObjectSelectionCollection;        //input collection
SR_Fq_pT.OutputCollection 	= &myHistoColl_SR_Fq_pT;        //output collection
SR_Fq_pT.RealData        	= eventhelper_isRealData;        //pass information if event is real data
SR_Fq_pT.RunData        	= false;        //real data allowed
SR_Fq_pT.NumberTauMin        	= 2;        //require at least N tau
SR_Fq_pT.NumberTauMax        	= 3;        //require at less than N taus
SR_Fq_pT.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
SR_Fq_pT.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
SR_Fq_pT.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
SR_Fq_pT.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
SR_Fq_pT.Btag        		= 0;        //number of btags required (exact -> 0 = none)
SR_Fq_pT.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
SR_Fq_pT.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
SR_Fq_pT.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
SR_Fq_pT.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
SR_Fq_pT.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
SR_Fq_pT.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
SR_Fq_pT.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
SR_Fq_pT.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
SR_Fq_pT.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
SR_Fq_pT.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
SR_Fq_pT.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
SR_Fq_pT.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
SR_Fq_pT.weight        	= FakeTaus_Fq_pT.weight;        //event weight
SR_Fq_pT.invertTauRequirements    = false;        //invert number of taus requirement
SR_Fq_pT.invertTauProperties      = false;        //invert ditau properties (dR, sign)
SR_Fq_pT.invertBtagRequirement    = false;        //invert number of b-jets required
SR_Fq_pT.invertJetRequirements    = false;        //invert jet pt requirements
SR_Fq_pT.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

SR_Fq_pT.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection CR_Fq_pT("CR_Fq_pT"); //label and initialisation
CR_Fq_pT.InputCollection 	= &MonoTauIso_Fq_pT_ObjectSelectionCollection;        //input collection
CR_Fq_pT.OutputCollection 	= &myHistoColl_CR_Fq_pT;        //output collection
CR_Fq_pT.RealData        	= eventhelper_isRealData;        //pass information if event is real data
CR_Fq_pT.RunData        	= true;        //real data allowed
CR_Fq_pT.NumberTauMin        	= 2;        //require at least N tau
CR_Fq_pT.NumberTauMax        	= 3;        //require at less than N taus
CR_Fq_pT.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
CR_Fq_pT.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
CR_Fq_pT.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
CR_Fq_pT.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
CR_Fq_pT.Btag        		= 0;        //number of btags required (exact -> 0 = none)
CR_Fq_pT.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
CR_Fq_pT.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
CR_Fq_pT.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
CR_Fq_pT.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
CR_Fq_pT.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
CR_Fq_pT.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
CR_Fq_pT.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
CR_Fq_pT.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
CR_Fq_pT.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
CR_Fq_pT.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
CR_Fq_pT.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
CR_Fq_pT.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
CR_Fq_pT.weight        	= FakeTaus_Fq_pT.weight;        //event weight
CR_Fq_pT.invertTauRequirements   = false;        //invert number of taus requirement
CR_Fq_pT.invertTauProperties     = false;        //invert ditau properties (dR, sign)
CR_Fq_pT.invertBtagRequirement   = false;        //invert number of b-jets required
CR_Fq_pT.invertJetRequirements   = true;        //invert jet pt requirements
CR_Fq_pT.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

CR_Fq_pT.select();        //do selection, fill histograms

//if(MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau.size()==2 && (MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau[0]->pt < 50 || MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau[1]->pt < 50))MonoTauIso_Fq_Abseta_ObjectSelectionCollection.tau.clear();
// ---------------------
// -- Signal Region --
// ---------------------

Selection SR_Fq_Abseta("SR_Fq_Abseta"); //label and initialisation
SR_Fq_Abseta.InputCollection 	= &MonoTauIso_Fq_Abseta_ObjectSelectionCollection;        //input collection
SR_Fq_Abseta.OutputCollection 	= &myHistoColl_SR_Fq_Abseta;        //output collection
SR_Fq_Abseta.RealData        	= eventhelper_isRealData;        //pass information if event is real data
SR_Fq_Abseta.RunData        	= false;        //real data allowed
SR_Fq_Abseta.NumberTauMin        	= 2;        //require at least N tau
SR_Fq_Abseta.NumberTauMax        	= 3;        //require at less than N taus
SR_Fq_Abseta.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
SR_Fq_Abseta.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
SR_Fq_Abseta.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
SR_Fq_Abseta.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
SR_Fq_Abseta.Btag        		= 0;        //number of btags required (exact -> 0 = none)
SR_Fq_Abseta.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
SR_Fq_Abseta.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
SR_Fq_Abseta.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
SR_Fq_Abseta.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
SR_Fq_Abseta.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
SR_Fq_Abseta.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
SR_Fq_Abseta.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
SR_Fq_Abseta.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
SR_Fq_Abseta.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
SR_Fq_Abseta.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
SR_Fq_Abseta.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
SR_Fq_Abseta.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
SR_Fq_Abseta.weight        	= FakeTaus_Fq_Abseta.weight;        //event weight
SR_Fq_Abseta.invertTauRequirements    = false;        //invert number of taus requirement
SR_Fq_Abseta.invertTauProperties      = false;        //invert ditau properties (dR, sign)
SR_Fq_Abseta.invertBtagRequirement    = false;        //invert number of b-jets required
SR_Fq_Abseta.invertJetRequirements    = false;        //invert jet pt requirements
SR_Fq_Abseta.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

SR_Fq_Abseta.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection CR_Fq_Abseta("CR_Fq_Abseta"); //label and initialisation
CR_Fq_Abseta.InputCollection 	= &MonoTauIso_Fq_Abseta_ObjectSelectionCollection;        //input collection
CR_Fq_Abseta.OutputCollection 	= &myHistoColl_CR_Fq_Abseta;        //output collection
CR_Fq_Abseta.RealData        	= eventhelper_isRealData;        //pass information if event is real data
CR_Fq_Abseta.RunData        	= true;        //real data allowed
CR_Fq_Abseta.NumberTauMin        	= 2;        //require at least N tau
CR_Fq_Abseta.NumberTauMax        	= 3;        //require at less than N taus
CR_Fq_Abseta.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
CR_Fq_Abseta.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
CR_Fq_Abseta.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
CR_Fq_Abseta.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
CR_Fq_Abseta.Btag        		= 0;        //number of btags required (exact -> 0 = none)
CR_Fq_Abseta.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
CR_Fq_Abseta.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
CR_Fq_Abseta.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
CR_Fq_Abseta.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
CR_Fq_Abseta.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
CR_Fq_Abseta.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
CR_Fq_Abseta.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
CR_Fq_Abseta.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
CR_Fq_Abseta.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
CR_Fq_Abseta.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
CR_Fq_Abseta.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
CR_Fq_Abseta.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
CR_Fq_Abseta.weight        	= FakeTaus_Fq_Abseta.weight;        //event weight
CR_Fq_Abseta.invertTauRequirements   = false;        //invert number of taus requirement
CR_Fq_Abseta.invertTauProperties     = false;        //invert ditau properties (dR, sign)
CR_Fq_Abseta.invertBtagRequirement   = false;        //invert number of b-jets required
CR_Fq_Abseta.invertJetRequirements   = true;        //invert jet pt requirements
CR_Fq_Abseta.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

CR_Fq_Abseta.select();        //do selection, fill histograms

//if(MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau.size()==2 && (MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau[0]->pt < 50 || MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau[1]->pt < 50))MonoTauIso_pT_Abseta_ObjectSelectionCollection.tau.clear();
// ---------------------
// -- Signal Region --
// ---------------------

Selection SR_pT_Abseta("SR_pT_Abseta"); //label and initialisation
SR_pT_Abseta.InputCollection 	= &MonoTauIso_pT_Abseta_ObjectSelectionCollection;        //input collection
SR_pT_Abseta.OutputCollection 	= &myHistoColl_SR_pT_Abseta;        //output collection
SR_pT_Abseta.RealData        	= eventhelper_isRealData;        //pass information if event is real data
SR_pT_Abseta.RunData        	= false;        //real data allowed
SR_pT_Abseta.NumberTauMin        	= 2;        //require at least N tau
SR_pT_Abseta.NumberTauMax        	= 3;        //require at less than N taus
SR_pT_Abseta.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
SR_pT_Abseta.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
SR_pT_Abseta.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
SR_pT_Abseta.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
SR_pT_Abseta.Btag        		= 0;        //number of btags required (exact -> 0 = none)
SR_pT_Abseta.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
SR_pT_Abseta.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
SR_pT_Abseta.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
SR_pT_Abseta.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
SR_pT_Abseta.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
SR_pT_Abseta.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
SR_pT_Abseta.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
SR_pT_Abseta.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
SR_pT_Abseta.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
SR_pT_Abseta.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
SR_pT_Abseta.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
SR_pT_Abseta.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
SR_pT_Abseta.weight        	= FakeTaus_pT_Abseta.weight;        //event weight
SR_pT_Abseta.invertTauRequirements    = false;        //invert number of taus requirement
SR_pT_Abseta.invertTauProperties      = false;        //invert ditau properties (dR, sign)
SR_pT_Abseta.invertBtagRequirement    = false;        //invert number of b-jets required
SR_pT_Abseta.invertJetRequirements    = false;        //invert jet pt requirements
SR_pT_Abseta.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

SR_pT_Abseta.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection CR_pT_Abseta("CR_pT_Abseta"); //label and initialisation
CR_pT_Abseta.InputCollection 	= &MonoTauIso_pT_Abseta_ObjectSelectionCollection;        //input collection
CR_pT_Abseta.OutputCollection 	= &myHistoColl_CR_pT_Abseta;        //output collection
CR_pT_Abseta.RealData        	= eventhelper_isRealData;        //pass information if event is real data
CR_pT_Abseta.RunData        	= true;        //real data allowed
CR_pT_Abseta.NumberTauMin        	= 2;        //require at least N tau
CR_pT_Abseta.NumberTauMax        	= 3;        //require at less than N taus
CR_pT_Abseta.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
CR_pT_Abseta.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
CR_pT_Abseta.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
CR_pT_Abseta.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
CR_pT_Abseta.Btag        		= 0;        //number of btags required (exact -> 0 = none)
CR_pT_Abseta.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
CR_pT_Abseta.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
CR_pT_Abseta.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
CR_pT_Abseta.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
CR_pT_Abseta.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
CR_pT_Abseta.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
CR_pT_Abseta.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
CR_pT_Abseta.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
CR_pT_Abseta.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
CR_pT_Abseta.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
CR_pT_Abseta.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
CR_pT_Abseta.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
CR_pT_Abseta.weight        	= FakeTaus_pT_Abseta.weight;        //event weight
CR_pT_Abseta.invertTauRequirements   = false;        //invert number of taus requirement
CR_pT_Abseta.invertTauProperties     = false;        //invert ditau properties (dR, sign)
CR_pT_Abseta.invertBtagRequirement   = false;        //invert number of b-jets required
CR_pT_Abseta.invertJetRequirements   = true;        //invert jet pt requirements
CR_pT_Abseta.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

CR_pT_Abseta.select();        //do selection, fill histograms

//Clearing Object Collections
MonoTauIso_Nq_Fq_ObjectSelectionCollection.clear();
MonoTauIso_Nq_pT_ObjectSelectionCollection.clear();
MonoTauIso_Nq_Abseta_ObjectSelectionCollection.clear();
MonoTauIso_Fq_pT_ObjectSelectionCollection.clear();
MonoTauIso_Fq_Abseta_ObjectSelectionCollection.clear();
MonoTauIso_pT_Abseta_ObjectSelectionCollection.clear(); 
JetLooseIsoObjectSelectionCollection.clear();

if(verbose)std::cout<<"_______________________________________________"<<std::endl;
}

  stream.close();
  ofile.close();
  return 0;
}

