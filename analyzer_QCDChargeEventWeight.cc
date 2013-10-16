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
TFile file_eff("/afs/naf.desy.de/user/r/rathjd/public/VBFAnalyzer/ChargeMapAllIsos_Jet30Tau45.root", "read");
TFile file_Resp("/afs/naf.desy.de/user/r/rathjd/public/VBFAnalyzer/ResponseFactorsAllIsos_Jet30Tau45_15up.root", "read");

/*vector<TH1F*> ResponseN;
vector<double> ResponseEdgeN;
TH2F *projectN=(TH2F*)file_Resp.Get("h2_tauResponseN")->Clone("projectN");
for(unsigned int x=0; x<projectN->GetNbinsX(); x++)
  {
    ResponseEdgeN.push_back(projectN->GetXaxis()->GetBinLowEdge(x+1));
    ResponseN.push_back((TH1F*)projectN->ProjectionY(TString::Format("histN_%d",x+1),x+1,x+1));
  }
ResponseEdgeN.push_back(2500);

vector<TH1F*> ResponseL;
vector<double> ResponseEdgeL;
TH2F *projectL=(TH2F*)file_Resp.Get("h2_tauResponseL")->Clone("projectL");
for(unsigned int x=0; x<projectL->GetNbinsX(); x++)
  {
    ResponseEdgeL.push_back(projectL->GetXaxis()->GetBinLowEdge(x+1));
    ResponseL.push_back((TH1F*)projectL->ProjectionY(TString::Format("histL_%d",x+1),x+1,x+1));
  }
ResponseEdgeL.push_back(2500);

vector<TH1F*> ResponseM;
vector<double> ResponseEdgeM;
TH2F *projectM=(TH2F*)file_Resp.Get("h2_tauResponseM")->Clone("projectM");
for(unsigned int x=0; x<projectM->GetNbinsX(); x++)
  {
    ResponseEdgeM.push_back(projectM->GetXaxis()->GetBinLowEdge(x+1));
    ResponseM.push_back((TH1F*)projectM->ProjectionY(TString::Format("histM_%d",x+1),x+1,x+1));
  }
ResponseEdgeM.push_back(2500);

vector<TH1F*> ResponseT;
vector<double> ResponseEdgeT;
TH2F *projectT=(TH2F*)file_Resp.Get("h2_tauResponseT")->Clone("projectT");
for(unsigned int x=0; x<projectT->GetNbinsX(); x++)
  {
    ResponseEdgeT.push_back(projectT->GetXaxis()->GetBinLowEdge(x+1));
    ResponseT.push_back((TH1F*)projectT->ProjectionY(TString::Format("histT_%d",x+1),x+1,x+1));
  }
ResponseEdgeT.push_back(2500);*/


MyHistoCollection myHistoColl_SignalRegion(ofile.file_, "SignalRegion");	
MyHistoCollection myHistoColl_CR1 (ofile.file_, "Ztautau_CR1");
MyHistoCollection myHistoColl_CR2 (ofile.file_, "Central_invertedVBF_CR2");
MyHistoCollection myHistoColl_CR3 (ofile.file_, "Central_invertedVBF_TauMediumIso_CR3");	
MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_TauLooseIso_CR4");
MyHistoCollection myHistoColl_CR5 (ofile.file_, "Central_invertedVBF_NoIso_CR5");


MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");
MyEventCollection JetLooseIsoObjectSelectionCollection ("JetLooseIsoObjectSelection");


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
if( goodVertex ) {
TauTightIsoObjectSelectionCollection.goodVertex = true;
TauMediumIsoObjectSelectionCollection.goodVertex = true;
TauLooseIsoObjectSelectionCollection.goodVertex = true;
TauNoIsoObjectSelectionCollection.goodVertex = true;
}
}

          //trigger selection
   
          if (
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1)

             ) { TauTightIsoObjectSelectionCollection.passedTrigger = true;
	         TauMediumIsoObjectSelectionCollection.passedTrigger = true;
		 TauLooseIsoObjectSelectionCollection.passedTrigger = true;
		 TauNoIsoObjectSelectionCollection.passedTrigger = true;
               }

// electron selection
for(unsigned int e = 0;e<electron.size();++e){
TauTightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
TauMediumIsoObjectSelectionCollection.electron.push_back(&electron[e]);
TauLooseIsoObjectSelectionCollection.electron.push_back(&electron[e]);
TauNoIsoObjectSelectionCollection.electron.push_back(&electron[e]);
}

// muon selection
for(unsigned int m =0;m<muon.size();++m){
if(!( fabs(muon[m].eta) < 2.4 )) continue;
if(!( muon[m].pt > 20 )) continue;
if(!( muon[m].isGlobalMuon )) continue;
if(!( muon[m].isTrackerMuon )) continue;
if(!( muon[m].isPFMuon )) continue;
if(!( muon[m].numberOfMatchedStations > 1 )) continue;
if(!(( fabs(muon[m].muonBestTrack_dxy) < 0.2 )) &&
                 ( fabs(muon[m]. muonBestTrack_dz) < 0.5 )) continue;
if(!( muon[m].globalTrack_normalizedChi2 < 10. )) continue;
if(!( muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0 )) continue;
if(!( muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0 )) continue;
if(!( muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5 )) continue;
if(!( muon[m].innerTrack_normalizedChi2 < 1.8 )) continue;
if(!( fabs(muon[m].innerTrack_dxy) < 3. )) continue;
if(!( fabs(muon[m].innerTrack_dz) < 30. )) continue;
TauTightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
TauNoIsoObjectSelectionCollection.muon.push_back(&muon[m]);
}

          // tau main selection
          /*for(unsigned int t =0;t<tau.size();++t){
if(!( fabs(tau[t].eta) <= 2.1 )) continue;
if(!( tau[t].pt >= 45. )) continue;
if(!( tau[t].leadPFChargedHadrCand_pt >= 5.0 )) continue;
if(!( tau[t].tauID_againstElectronTightMVA3 > 0.5 )) continue;
if(!( tau[t].tauID_againstMuonTight2 > 0.5 )) continue;
if(!( (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1) )) continue;
if( tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits > 0.5 ) TauTightObjectSelectionCollection.tau.push_back(&tau[t]);
}*/ //disregard all "true" fake taus, as they can be randomly faked, again.

          // jet baseline selection
for(unsigned int j = 0;j<jet.size();++j){
if(!( jet[j].pt >= 30. )) continue;
if(!( fabs(jet[j].eta) <= 2.7 )) continue;
JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
}


// --------------------------
// -- QCD Event Weighting --
// --------------------------

bool verbose=false;

TH2F* ChargeMapN_eff = (TH2F*)(file_eff.Get("ChargeMapN_eff"));
TH1F* ReweightFactorN = (TH1F*)(file_Resp.Get("RescaleWeightN"));
vector<double> jet_taufakerateN;

TH2F* ChargeMapL_eff = (TH2F*)(file_eff.Get("ChargeMapL_eff"));
TH1F* ReweightFactorL = (TH1F*)(file_Resp.Get("RescaleWeightL"));
vector<double> jet_taufakerateL;

TH2F* ChargeMapM_eff = (TH2F*)(file_eff.Get("ChargeMapM_eff"));
TH1F* ReweightFactorM = (TH1F*)(file_Resp.Get("RescaleWeightM"));
vector<double> jet_taufakerateM;

TH2F* ChargeMapT_eff = (TH2F*)(file_eff.Get("ChargeMapT_eff"));
TH1F* ReweightFactorT = (TH1F*)(file_Resp.Get("RescaleWeightT"));
vector<double> jet_taufakerateT;


for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
int nbinN = ChargeMapN_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinN= ReweightFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinL = ChargeMapL_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinL= ReweightFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinM = ChargeMapM_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinM= ReweightFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinT = ChargeMapT_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinT= ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
if(verbose)std::cout<<"Jet "<<i<<" out of "<<JetLooseIsoObjectSelectionCollection.jet.size()<<": pT="<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", eta="<<JetLooseIsoObjectSelectionCollection.jet[i]->eta<<", phi="<<JetLooseIsoObjectSelectionCollection.jet[i]->phi<<std::endl;
if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.1)
  {
    jet_taufakerateN.push_back(ChargeMapN_eff->GetBinContent(nbinN)*ReweightFactorN->GetBinContent(nRescaleBinN));
    jet_taufakerateL.push_back(ChargeMapL_eff->GetBinContent(nbinL)*ReweightFactorL->GetBinContent(nRescaleBinL));
    jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nbinM)*ReweightFactorM->GetBinContent(nRescaleBinM));
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
        jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nbinM)*ReweightFactorM->GetBinContent(nRescaleBinM));
        jet_taufakerateT.push_back(ChargeMapT_eff->GetBinContent(nbinT)*ReweightFactorT->GetBinContent(nRescaleBinT));
	if(verbose)std::cout<<"MindR2 and 2.1<eta<=2.2 pass: N_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity<<", F_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction<<", P(N_q,F_q)="<<ChargeMapT_eff->GetBinContent(nbinT)<<", P(pT)="<<ReweightFactorT->GetBinContent(nRescaleBinT)<<std::endl;
      }
    else
      {
        jet_taufakerateN.push_back(0);
    	jet_taufakerateL.push_back(0);
	jet_taufakerateM.push_back(0);
	jet_taufakerateT.push_back(0);
	if(verbose)std::cout<<"Failed: P=0!"<<std::endl;
      }
  }
}



Fake FakeTausN("FakeTaus");
if(verbose)std::cout<<"Dice NoIso"<<std::endl;
FakeTausN.generate(jet_taufakerateN);

tau_s faketau1N;
tau_s faketau2N;

TH1F* h1_taufakescaleN_fac = (TH1F*)(file_Resp.Get("scaleN"));

if ( FakeTausN.index.first >= 0 && FakeTausN.index.second >= 0 ) {

double scale = h1_taufakescaleN_fac->GetBinContent(h1_taufakescaleN_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausN.weight=0;}

/*double scale=1.;
for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTaus.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
if(verbose)std::cout<<"Jet "<<FakeTausN.index.first<<" to FTau1: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->charge >= 0 )
faketau1N.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->charge < 0 )
faketau1N.charge = -1;
faketau1N.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->p;
faketau1N.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->energy;
faketau1N.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->et;
faketau1N.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->px;
faketau1N.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->py;
faketau1N.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pz;
faketau1N.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt * scale;
if(faketau1N.pt < 45) FakeTausN.weight=0;
faketau1N.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta<=2.1) faketau1N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta;
else faketau1N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta)*2.1;
/*for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTausN.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
scale = h1_taufakescaleN_fac->GetBinContent(h1_taufakescaleN_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt));
if(scale == 0) {scale = 0.851; FakeTausN.weight=0;}
if(verbose)std::cout<<"Jet "<<FakeTausN.index.second<<" to FTau2: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->charge >= 0 )
faketau2N.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->charge < 0 )
faketau2N.charge = -1;	
faketau2N.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->p;
faketau2N.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->energy;
faketau2N.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->et;
faketau2N.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->px;
faketau2N.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->py;
faketau2N.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pz;
faketau2N.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt * scale;
if(faketau2N.pt < 45) FakeTausN.weight=0;
faketau2N.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta<=2.1) faketau2N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta;
else faketau2N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta)*2.1;
TauNoIsoObjectSelectionCollection.tau.push_back(&faketau1N);
TauNoIsoObjectSelectionCollection.tau.push_back(&faketau2N);
}

Fake FakeTausL("FakeTaus");
if(verbose)std::cout<<"Dice LooseIso"<<std::endl;
FakeTausL.generate(jet_taufakerateL);

tau_s faketau1L;
tau_s faketau2L;

TH1F* h1_taufakescaleL_fac = (TH1F*)(file_Resp.Get("scaleL"));

if ( FakeTausL.index.first >= 0 && FakeTausL.index.second >= 0 ) {

double scale = h1_taufakescaleL_fac->GetBinContent(h1_taufakescaleL_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausL.weight=0;}

/*double scale=1.;
for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTaus.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
if(verbose)std::cout<<"Jet "<<FakeTausL.index.first<<" to FTau1: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->charge >= 0 )
faketau1L.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->charge < 0 )
faketau1L.charge = -1;
faketau1L.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->p;
faketau1L.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->energy;
faketau1L.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->et;
faketau1L.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->px;
faketau1L.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->py;
faketau1L.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pz;
faketau1L.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt * scale;
if(faketau1L.pt < 45) FakeTausL.weight=0;
faketau1L.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta<=2.1) faketau1L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta;
else faketau1L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta)*2.1;
/*for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTausL.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
scale = h1_taufakescaleL_fac->GetBinContent(h1_taufakescaleL_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt));
if(scale == 0) {scale = 0.851; FakeTausL.weight=0;}
if(verbose)std::cout<<"Jet "<<FakeTausL.index.second<<" to FTau2: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->charge >= 0 )
faketau2L.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->charge < 0 )
faketau2L.charge = -1;	
faketau2L.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->p;
faketau2L.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->energy;
faketau2L.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->et;
faketau2L.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->px;
faketau2L.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->py;
faketau2L.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pz;
faketau2L.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt * scale;
if(faketau2L.pt < 45) FakeTausL.weight=0;
faketau2L.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta<=2.1) faketau2L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta;
else faketau2L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta)*2.1;
TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau1L);
TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau2L);
}

Fake FakeTausM("FakeTaus");
if(verbose)std::cout<<"Dice MediumIso"<<std::endl;
FakeTausM.generate(jet_taufakerateM);

tau_s faketau1M;
tau_s faketau2M;

TH1F* h1_taufakescaleM_fac = (TH1F*)(file_Resp.Get("scaleM"));

if ( FakeTausM.index.first >= 0 && FakeTausM.index.second >= 0 ) {

double scale = h1_taufakescaleM_fac->GetBinContent(h1_taufakescaleM_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausM.weight=0;}

/*double scale=1.;
for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTaus.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
if(verbose)std::cout<<"Jet "<<FakeTausM.index.first<<" to FTau1: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->charge >= 0 )
faketau1M.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->charge < 0 )
faketau1M.charge = -1;
faketau1M.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->p;
faketau1M.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->energy;
faketau1M.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->et;
faketau1M.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->px;
faketau1M.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->py;
faketau1M.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pz;
faketau1M.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt * scale;
if(faketau1M.pt < 45) FakeTausM.weight=0;
faketau1M.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta<=2.1) faketau1M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta;
else faketau1M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta)*2.1;
/*for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTausM.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
scale = h1_taufakescaleM_fac->GetBinContent(h1_taufakescaleM_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt));
if(scale == 0) {scale = 0.851; FakeTausM.weight=0;}
if(verbose)std::cout<<"Jet "<<FakeTausM.index.second<<" to FTau2: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->charge >= 0 )
faketau2M.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->charge < 0 )
faketau2M.charge = -1;	
faketau2M.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->p;
faketau2M.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->energy;
faketau2M.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->et;
faketau2M.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->px;
faketau2M.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->py;
faketau2M.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pz;
faketau2M.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt * scale;
if(faketau2M.pt < 45) FakeTausM.weight=0;
faketau2M.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta<=2.1) faketau2M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta;
else faketau2M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta)*2.1;
TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau1M);
TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau2M);
}

Fake FakeTausT("FakeTaus");
if(verbose)std::cout<<"Dice TightIso"<<std::endl;
FakeTausT.generate(jet_taufakerateT);

/*if(FakeTausT.weight>0){
	  double p2=1;
	  int count=0;
	  for(unsigned int i=0; i<jet_taufakerateT.size(); i++){ //try p2 vs pg2
	  	if(jet_taufakerateT[i]>0){
		  count++;
	  	  if(i==abs(FakeTausT.index.first) || i==abs(FakeTausT.index.second)) p2*=jet_taufakerateT[i];
		  else p2*=(1-jet_taufakerateT[i]);
		}
	  }
	  h1_WeightDiff->Fill(count,FakeTausT.weight-p2);
	  int coefficient=1;
	  if(count==3) coefficient=3;
	  else if(count==4) coefficient=6; 
	  else if(count==5) coefficient=10;
	  else if(count==6) coefficient=15;
	  FakeTausT.weight*=1/coefficient;}*/

tau_s faketau1T;
tau_s faketau2T;

TH1F* h1_taufakescaleT_fac = (TH1F*)(file_Resp.Get("scaleT"));

if ( FakeTausT.index.first >= 0 && FakeTausT.index.second >= 0 ) {

double scale = h1_taufakescaleT_fac->GetBinContent(h1_taufakescaleT_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausT.weight=0;}

/*double scale=1.;
for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTaus.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
if(verbose)std::cout<<"Jet "<<FakeTausT.index.first<<" to FTau1: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->charge >= 0 )
faketau1T.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->charge < 0 )
faketau1T.charge = -1;
faketau1T.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->p;
faketau1T.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->energy;
faketau1T.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->et;
faketau1T.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->px;
faketau1T.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->py;
faketau1T.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pz;
faketau1T.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt * scale;
if(faketau1T.pt < 45) FakeTausT.weight=0;
faketau1T.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta<=2.1) faketau1T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta;
else faketau1T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta)*2.1;
/*for(unsigned int i=0; i<ResponseEdge.size()-1; i++)
  {
    if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt < ResponseEdge[i+1])
      {
        int count=0;
	scale=Response[i]->GetRandom();
        while(scale * JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt < 45)
	  {
	    scale=Response[i]->GetRandom();
	    count++;
	    if(count==1000)
	      {
	        FakeTausT.weight=0;
		break;
	      }
	  }
	break;
      }
  }*/
scale = h1_taufakescaleT_fac->GetBinContent(h1_taufakescaleT_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt));
if(scale == 0) {scale = 0.851; FakeTausT.weight=0;}
if(verbose)std::cout<<"Jet "<<FakeTausT.index.second<<" to FTau2: pTScale="<<scale<<std::endl;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->charge >= 0 )
faketau2T.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->charge < 0 )
faketau2T.charge = -1;	
faketau2T.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->p;
faketau2T.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->energy;
faketau2T.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->et;
faketau2T.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->px;
faketau2T.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->py;
faketau2T.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pz;
faketau2T.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt * scale;
if(faketau2T.pt < 45) FakeTausT.weight=0;
faketau2T.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta<=2.1) faketau2T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta;
else faketau2T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta)*2.1;
TauTightIsoObjectSelectionCollection.tau.push_back(&faketau1T);
TauTightIsoObjectSelectionCollection.tau.push_back(&faketau2T);
}

// jet && bjet selection
// ? id ?
for(unsigned int j = 0;j<jet.size();++j){
if(!( jet[j].pt >= 30. )) continue; // Original value 20
if(!( fabs(jet[j].eta) <= 5.0 )) continue;
double DistanceN = TauJetMinDistance(TauNoIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceL = TauJetMinDistance(TauLooseIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceM = TauJetMinDistance(TauMediumIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
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
if( jet[j].pt >= 50. && jetid	){
  if(	DistanceN >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceL >= 0.3	) TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceM >= 0.3	) TauMediumIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceT >= 0.3	) TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
            }
if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244 ){
  if(	DistanceN >= 0.3	) TauNoIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceL >= 0.3	) TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceM >= 0.3	) TauMediumIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceT >= 0.3	) TauTightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
            }
}
if(verbose)std::cout<<TauTightIsoObjectSelectionCollection.jet.size()<<" jets in tightIso jet collection and "<<TauTightIsoObjectSelectionCollection.bjet.size()<<" in bjet collection"<<std::endl;

//MET selection
TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);
TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);

//Event Count
ofile.count("NoCuts");

// ---------------------
// -- Signal Region --
// ---------------------

Selection Signal("Signal"); //label and initialisation
Signal.InputCollection = &TauTightIsoObjectSelectionCollection;	//input collection
Signal.OutputCollection = &myHistoColl_SignalRegion;	//output collection
Signal.RealData	= eventhelper_isRealData;	//pass information if event is real data
Signal.RunData	= false;	//real data allowed
Signal.NumberTauMin	= 2;	//require at least N tau
Signal.NumberTauMax	= -1;	//require at most N taus
Signal.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
Signal.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
Signal.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
Signal.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
Signal.Btag	= 0;	//number of btags required (exact -> 0 = none)
Signal.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
Signal.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
Signal.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
Signal.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
Signal.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
Signal.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
Signal.DiJetDrMax	= -1;	//Dijet maximum delta R, set to -1 for no requirement
Signal.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
Signal.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
Signal.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
Signal.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Signal.DiJetDetaMax	= -1;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Signal.weight	= FakeTausT.weight;	//event weight
Signal.invertTauRequirements	= false;	//invert number of taus requirement
Signal.invertTauProperties	= false;	//invert ditau properties (dR, sign)
Signal.invertBtagRequirement	= false;	//invert number of b-jets required
Signal.invertJetRequirements	= false;	//invert jet pt requirements
Signal.invertDijetProperties	= false;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"Signal selection"<<std::endl;
Signal.select();	//do selection, fill histograms

// ---------------------------------
// -- CENTRAL + INVERTED VBF CR --
// ---------------------------------

Selection InvertedVBF_CR2("InvertedVBF_CR2"); //label and initialisation
InvertedVBF_CR2.InputCollection = &TauTightIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR2.OutputCollection = &myHistoColl_CR2;	//output collection
InvertedVBF_CR2.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR2.RunData	= true;	//real data allowed
InvertedVBF_CR2.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR2.NumberTauMax	= -1;	//require at most N taus
InvertedVBF_CR2.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR2.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR2.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR2.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR2.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR2.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR2.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR2.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR2.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR2.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR2.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR2.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR2.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR2.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR2.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR2.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR2.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR2.weight	= FakeTausT.weight;	//event weight
InvertedVBF_CR2.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR2.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR2.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR2.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR2.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR2 selection"<<std::endl;
InvertedVBF_CR2.select();	//do selection, fill histograms

// ------------------------------------------------------
// -- CENTRAL + INVERTED VBF CR (with Tau Medium Iso) --
// ------------------------------------------------------

Selection InvertedVBF_CR3("InvertedVBF_TauMediumIso_CR3"); //label and initialisation
InvertedVBF_CR3.InputCollection = &TauMediumIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR3.OutputCollection = &myHistoColl_CR3;	//output collection
InvertedVBF_CR3.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR3.RunData	= true;	//real data allowed
InvertedVBF_CR3.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR3.NumberTauMax	= -1;	//require at most N taus
InvertedVBF_CR3.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR3.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR3.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR3.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR3.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR3.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR3.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR3.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR3.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR3.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR3.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR3.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR3.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR3.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR3.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR3.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR3.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR3.weight	= FakeTausM.weight;	//event weight
InvertedVBF_CR3.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR3.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR3.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR3.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR3.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR3 selection"<<std::endl;
InvertedVBF_CR3.select();	//do selection, fill histograms

// ------------------------------------------------------
// -- CENTRAL + INVERTED VBF CR (with Tau Loose Iso) --
// ------------------------------------------------------

Selection InvertedVBF_CR4("InvertedVBF_TauLooseIso_CR4"); //label and initialisation
InvertedVBF_CR4.InputCollection = &TauLooseIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR4.OutputCollection = &myHistoColl_CR4;	//output collection
InvertedVBF_CR4.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR4.RunData	= true;	//real data allowed
InvertedVBF_CR4.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR4.NumberTauMax	= -1;	//require at most N taus
InvertedVBF_CR4.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR4.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR4.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR4.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR4.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR4.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR4.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR4.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR4.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR4.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR4.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR4.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR4.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR4.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR4.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR4.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR4.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR4.weight	= FakeTausL.weight;	//event weight
InvertedVBF_CR4.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR4.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR4.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR4.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR4.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR4 selection"<<std::endl;
InvertedVBF_CR4.select();	//do selection, fill histograms

// ------------------------------------------------------
// -- CENTRAL + INVERTED VBF CR (without Tau Iso) --
// ------------------------------------------------------

Selection InvertedVBF_CR5("InvertedVBF_TauNoIso_CR5"); //label and initialisation
InvertedVBF_CR5.InputCollection = &TauNoIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR5.OutputCollection = &myHistoColl_CR5;	//output collection
InvertedVBF_CR5.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR5.RunData	= true;	//real data allowed
InvertedVBF_CR5.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR5.NumberTauMax	= -1;	//require at most N taus
InvertedVBF_CR5.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR5.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR5.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR5.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR5.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR5.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR5.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR5.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR5.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR5.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR5.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR5.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR5.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR5.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR5.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR5.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR5.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR5.weight	= FakeTausN.weight;	//event weight
InvertedVBF_CR5.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR5.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR5.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR5.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR5.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR5 selection"<<std::endl;
InvertedVBF_CR5.select();	//do selection, fill histograms

// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_CR1("Ztautau_CR1"); //label and initialisation
Ztautau_CR1.InputCollection = &TauTightIsoObjectSelectionCollection;	//input collection
Ztautau_CR1.OutputCollection = &myHistoColl_CR1;	//output collection
Ztautau_CR1.RealData	= eventhelper_isRealData;	//pass information if event is real data
Ztautau_CR1.RunData	= true;	//real data allowed
Ztautau_CR1.NumberTauMin	= 2;	//require at least N tau
Ztautau_CR1.NumberTauMax	= -1;	//require at most N taus
Ztautau_CR1.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
Ztautau_CR1.DiTauInvMassMin	= -1.;	//minimum Di-tau-mass requirement
Ztautau_CR1.DiTauInvMassMax	= 90.;	//maximum Di-tau-mass requirement
Ztautau_CR1.DiTauSign	= -1;	//1 for LS and -1 for OS, 0 for no requirement
Ztautau_CR1.Btag	= 0;	//number of btags required (exact -> 0 = none)
Ztautau_CR1.JetEtaMax	= -1.;	//maximum eta for jets, set to -1 for no requirement
Ztautau_CR1.LeadJetPtMin	= -1.;	//minimum pt of lead jet, set to -1 for no requirement
Ztautau_CR1.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
Ztautau_CR1.SubLeadJetPtMin	= -1.;	//minimum pt of sub lead jet, set to -1 for no requirement
Ztautau_CR1.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
Ztautau_CR1.DiJetDrMin	= -1.;	//Dijet minimum delta R, set to -1 for no requirement
Ztautau_CR1.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
Ztautau_CR1.DiJetInvMassMin	= -1.;	//Dijet minimal invariant mass, set to -1 for no requirement
Ztautau_CR1.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
Ztautau_CR1.DiJetSignEta	= 0;	//Dijet sign eta_1*eta_2
Ztautau_CR1.DiJetDetaMin	= -1.;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Ztautau_CR1.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Ztautau_CR1.weight	= FakeTausT.weight;	//event weight
Ztautau_CR1.invertTauRequirements	= false;	//invert number of taus requirement
Ztautau_CR1.invertTauProperties	= false;	//invert ditau properties (dR, sign)
Ztautau_CR1.invertBtagRequirement	= false;	//invert number of b-jets required
Ztautau_CR1.invertJetRequirements	= false;	//invert jet pt requirements
Ztautau_CR1.invertDijetProperties	= false;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR1 selection"<<std::endl;
Ztautau_CR1.select();	//do selection, fill histograms

/*// ---------------------
// -- Central Loose Region --
// ---------------------

Selection Central_TauLooseIso_CR5("Central_TauLooseIso_CR5"); //label and initialisation
Central_TauLooseIso_CR5.InputCollection = &TauLooseIsoObjectSelectionCollection;	//input collection
Central_TauLooseIso_CR5.OutputCollection = &myHistoColl_CR5;	//output collection
Central_TauLooseIso_CR5.RealData	= eventhelper_isRealData;	//pass information if event is real data
Central_TauLooseIso_CR5.RunData	= true;	//real data allowed
Central_TauLooseIso_CR5.NumberTauMin	= 2;	//require at least N tau
Central_TauLooseIso_CR5.NumberTauMax	= -1;	//require at most N taus
Central_TauLooseIso_CR5.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
Central_TauLooseIso_CR5.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
Central_TauLooseIso_CR5.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
Central_TauLooseIso_CR5.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
Central_TauLooseIso_CR5.Btag	= 0;	//number of btags required (exact -> 0 = none)
Central_TauLooseIso_CR5.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
Central_TauLooseIso_CR5.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetDrMax	= -1;	//Dijet maximum delta R, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
Central_TauLooseIso_CR5.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetDetaMax	= -1;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Central_TauLooseIso_CR5.weight	= FakeTausL.weight;	//event weight
Central_TauLooseIso_CR5.invertTauRequirements	= false;	//invert number of taus requirement
Central_TauLooseIso_CR5.invertTauProperties	= false;	//invert ditau properties (dR, sign)
Central_TauLooseIso_CR5.invertBtagRequirement	= false;	//invert number of b-jets required
Central_TauLooseIso_CR5.invertJetRequirements	= false;	//invert jet pt requirements
Central_TauLooseIso_CR5.invertDijetProperties	= false;	//invert dijet system properties (dR, inv mass, sign eta, dEta)

Central_TauLooseIso_CR5.select();*/	


//Clearing Object Collections
TauTightIsoObjectSelectionCollection.clear();
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

