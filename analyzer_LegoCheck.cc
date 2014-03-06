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
    double ptedges[21]={22.5,23.7,25.,26.5,28.1,30.,32.1,34.6,37.5,40.9,45.,50.,56.3,64.3,75.,90.,112.5,150.,225.,450.,2500.};
    
//jet distributions
TH1F* pTjet_baseline = new TH1F("pTjet_baseline","inclusive jet distribution, all permutations in", 20,ptedges);
pTjet_baseline->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjet_baseline->Sumw2();
TH1F* pTjet_Nq_Fq = new TH1F("pTjet_Nq_Fq","inclusive jet distribution, all permutations in", 20,ptedges);
pTjet_Nq_Fq->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjet_Nq_Fq->Sumw2();
TH1F* pTjet_Nq_pT = new TH1F("pTjet_Nq_pT","inclusive jet distribution, all permutations in", 20,ptedges);
pTjet_Nq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjet_Nq_pT->Sumw2();
TH1F* pTjet_Nq_Abseta = new TH1F("pTjet_Nq_Abseta","inclusive jet distribution, all permutations in", 20,ptedges);
pTjet_Nq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjet_Nq_Abseta->Sumw2();
TH1F* pTjet_Fq_pT = new TH1F("pTjet_Fq_pT","inclusive jet distribution, all permutations in", 20,ptedges);
pTjet_Fq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjet_Fq_pT->Sumw2();
TH1F* pTjet_Fq_Abseta = new TH1F("pTjet_Fq_Abseta","inclusive jet distribution, all permutations in", 20,ptedges);
pTjet_Fq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjet_Fq_Abseta->Sumw2();
TH1F* pTjet_pT_Abseta = new TH1F("pTjet_pT_Abseta","inclusive jet distribution, all permutations in", 20,ptedges);
pTjet_pT_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjet_pT_Abseta->Sumw2();

//predicted jet distributions
TH1F* pTjetPredicted_Nq_Fq = new TH1F("pTjetPredicted_Nq_Fq","inclusive jet distribution, all permutations in", 20,ptedges);
pTjetPredicted_Nq_Fq->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjetPredicted_Nq_Fq->Sumw2();
TH1F* pTjetPredicted_Nq_pT = new TH1F("pTjetPredicted_Nq_pT","inclusive jet distribution, all permutations in", 20,ptedges);
pTjetPredicted_Nq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjetPredicted_Nq_pT->Sumw2();
TH1F* pTjetPredicted_Nq_Abseta = new TH1F("pTjetPredicted_Nq_Abseta","inclusive jet distribution, all permutations in", 20,ptedges);
pTjetPredicted_Nq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjetPredicted_Nq_Abseta->Sumw2();
TH1F* pTjetPredicted_Fq_pT = new TH1F("pTjetPredicted_Fq_pT","inclusive jet distribution, all permutations in", 20,ptedges);
pTjetPredicted_Fq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjetPredicted_Fq_pT->Sumw2();
TH1F* pTjetPredicted_Fq_Abseta = new TH1F("pTjetPredicted_Fq_Abseta","inclusive jet distribution, all permutations in", 20,ptedges);
pTjetPredicted_Fq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjetPredicted_Fq_Abseta->Sumw2();
TH1F* pTjetPredicted_pT_Abseta = new TH1F("pTjetPredicted_pT_Abseta","inclusive jet distribution, all permutations in", 20,ptedges);
pTjetPredicted_pT_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTjetPredicted_pT_Abseta->Sumw2();

//tau distributions
TH1F* pTtau_baseline = new TH1F("pTtau_baseline","inclusive tau distribution, all permutations in", 20,ptedges);
pTtau_baseline->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtau_baseline->Sumw2();
TH1F* pTtau_Nq_Fq = new TH1F("pTtau_Nq_Fq","inclusive tau distribution, all permutations in", 20,ptedges);
pTtau_Nq_Fq->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtau_Nq_Fq->Sumw2();
TH1F* pTtau_Nq_pT = new TH1F("pTtau_Nq_pT","inclusive tau distribution, all permutations in", 20,ptedges);
pTtau_Nq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtau_Nq_pT->Sumw2();
TH1F* pTtau_Nq_Abseta = new TH1F("pTtau_Nq_Abseta","inclusive tau distribution, all permutations in", 20,ptedges);
pTtau_Nq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtau_Nq_Abseta->Sumw2();
TH1F* pTtau_Fq_pT = new TH1F("pTtau_Fq_pT","inclusive tau distribution, all permutations in", 20,ptedges);
pTtau_Fq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtau_Fq_pT->Sumw2();
TH1F* pTtau_Fq_Abseta = new TH1F("pTtau_Fq_Abseta","inclusive tau distribution, all permutations in", 20,ptedges);
pTtau_Fq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtau_Fq_Abseta->Sumw2();
TH1F* pTtau_pT_Abseta = new TH1F("pTtau_pT_Abseta","inclusive tau distribution, all permutations in", 20,ptedges);
pTtau_pT_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtau_pT_Abseta->Sumw2();

//scaled tau distributions
TH1F* pTtauScaled_baseline = new TH1F("pTtauScaled_baseline","inclusive tau distribution, all permutations in", 20,ptedges);
pTtauScaled_baseline->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauScaled_baseline->Sumw2();
TH1F* pTtauScaled_Nq_Fq = new TH1F("pTtauScaled_Nq_Fq","inclusive tau scaled distribution, all permutations in", 20,ptedges);
pTtauScaled_Nq_Fq->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauScaled_Nq_Fq->Sumw2();
TH1F* pTtauScaled_Nq_pT = new TH1F("pTtauScaled_Nq_pT","inclusive tau scaled distribution, all permutations in", 20,ptedges);
pTtauScaled_Nq_pT->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauScaled_Nq_pT->Sumw2();
TH1F* pTtauScaled_Nq_Abseta = new TH1F("pTtauScaled_Nq_Abseta","inclusive tau scaled distribution, all permutations in", 20,ptedges);
pTtauScaled_Nq_Abseta->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauScaled_Nq_Abseta->Sumw2();
TH1F* pTtauScaled_Fq_pT = new TH1F("pTtauScaled_Fq_pT","inclusive tau scaled distribution, all permutations in", 20,ptedges);
pTtauScaled_Fq_pT->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauScaled_Fq_pT->Sumw2();
TH1F* pTtauScaled_Fq_Abseta = new TH1F("pTtauScaled_Fq_Abseta","inclusive tau scaled distribution, all permutations in", 20,ptedges);
pTtauScaled_Fq_Abseta->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauScaled_Fq_Abseta->Sumw2();
TH1F* pTtauScaled_pT_Abseta = new TH1F("pTtauScaled_pT_Abseta","inclusive tau scaled distribution, all permutations in", 20,ptedges);
pTtauScaled_pT_Abseta->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauScaled_pT_Abseta->Sumw2();

//reweighted
TH1F* pTtauReweighted_Nq_Fq = new TH1F("pTtauReweighted_Nq_Fq","inclusive tau Reweighted distribution, all permutations in", 20,ptedges);
pTtauReweighted_Nq_Fq->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtauReweighted_Nq_Fq->Sumw2();
TH1F* pTtauReweighted_Nq_pT = new TH1F("pTtauReweighted_Nq_pT","inclusive tau Reweighted distribution, all permutations in", 20,ptedges);
pTtauReweighted_Nq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtauReweighted_Nq_pT->Sumw2();
TH1F* pTtauReweighted_Nq_Abseta = new TH1F("pTtauReweighted_Nq_Abseta","inclusive tau Reweighted distribution, all permutations in", 20,ptedges);
pTtauReweighted_Nq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtauReweighted_Nq_Abseta->Sumw2();
TH1F* pTtauReweighted_Fq_pT = new TH1F("pTtauReweighted_Fq_pT","inclusive tau Reweighted distribution, all permutations in", 20,ptedges);
pTtauReweighted_Fq_pT->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtauReweighted_Fq_pT->Sumw2();
TH1F* pTtauReweighted_Fq_Abseta = new TH1F("pTtauReweighted_Fq_Abseta","inclusive tau Reweighted distribution, all permutations in", 20,ptedges);
pTtauReweighted_Fq_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtauReweighted_Fq_Abseta->Sumw2();
TH1F* pTtauReweighted_pT_Abseta = new TH1F("pTtauReweighted_pT_Abseta","inclusive tau Reweighted distribution, all permutations in", 20,ptedges);
pTtauReweighted_pT_Abseta->GetXaxis()->SetTitle("p_{T}^{jet}");
pTtauReweighted_pT_Abseta->Sumw2();

//predicted tau distributions
TH1F* pTtauPredicted_Nq_Fq = new TH1F("pTtauPredicted_Nq_Fq","inclusive tau Predicted distribution, all permutations in", 20,ptedges);
pTtauPredicted_Nq_Fq->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauPredicted_Nq_Fq->Sumw2();
TH1F* pTtauPredicted_Nq_pT = new TH1F("pTtauPredicted_Nq_pT","inclusive tau Predicted distribution, all permutations in", 20,ptedges);
pTtauPredicted_Nq_pT->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauPredicted_Nq_pT->Sumw2();
TH1F* pTtauPredicted_Nq_Abseta = new TH1F("pTtauPredicted_Nq_Abseta","inclusive tau Predicted distribution, all permutations in", 20,ptedges);
pTtauPredicted_Nq_Abseta->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauPredicted_Nq_Abseta->Sumw2();
TH1F* pTtauPredicted_Fq_pT = new TH1F("pTtauPredicted_Fq_pT","inclusive tau Predicted distribution, all permutations in", 20,ptedges);
pTtauPredicted_Fq_pT->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauPredicted_Fq_pT->Sumw2();
TH1F* pTtauPredicted_Fq_Abseta = new TH1F("pTtauPredicted_Fq_Abseta","inclusive tau Predicted distribution, all permutations in", 20,ptedges);
pTtauPredicted_Fq_Abseta->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauPredicted_Fq_Abseta->Sumw2();
TH1F* pTtauPredicted_pT_Abseta = new TH1F("pTtauPredicted_pT_Abseta","inclusive tau Predicted distribution, all permutations in", 20,ptedges);
pTtauPredicted_pT_Abseta->GetXaxis()->SetTitle("p_{T}^{#tau}");
pTtauPredicted_pT_Abseta->Sumw2();

//response
TProfile *response=new TProfile("response", "profile histogram", 20,ptedges);
response->GetXaxis()->SetTitle("p_{T}^{jet}");
response->Sumw2();

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

TH1::SetDefaultSumw2();

//TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/EffmapVariations_AlternateV1.root", "read");
TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/EffmapVariationsEta21Ptg30_50-80only.root", "read");
TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseFactors_InclAndExclIsos_50-80only_Jet30Lukas_MC_Tau45_eta21.root", "read");

MyEventCollection JetLooseIsoObjectSelectionCollection("JetLooseIsoObjectSelectionCollection");
MyEventCollection baselineObjectSelectionCollection("baselineObjectSelectionCollection");

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

// jet baseline selection
for(unsigned int j = 0;j<jet.size();++j){
	if(!( fabs(jet[j].eta) <= 2.7 )) 	continue;
	if(!( jet[j].pt >= 30. )) 		continue;
	JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
}

for(unsigned int t =0;t<tau.size();++t){
  if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
  //if(!(       tau[t].pt >= 45.                                            				)) continue;
  if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
  if(!(       tau[t].tauID_againstElectronTightMVA5 > 0.5                				)) continue;
  if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
  if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
  if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5))  baselineObjectSelectionCollection.tau.push_back(&tau[t]);
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
TProfile* ScaleFactorT = (TProfile*)(file_Resp.Get("ScaleFactorT"));

vector<double> jet_taufakerate_Nq_Fq;
vector<double> jet_taufakerate_Nq_pT;
vector<double> jet_taufakerate_Nq_Abseta;
vector<double> jet_taufakerate_Fq_pT;
vector<double> jet_taufakerate_Fq_Abseta;
vector<double> jet_taufakerate_pT_Abseta;
vector<double> jet_taufakerateReweighted_Nq_Fq;
vector<double> jet_taufakerateReweighted_Nq_pT;
vector<double> jet_taufakerateReweighted_Nq_Abseta;
vector<double> jet_taufakerateReweighted_Fq_pT;
vector<double> jet_taufakerateReweighted_Fq_Abseta;
vector<double> jet_taufakerateReweighted_pT_Abseta;


for(unsigned int i  = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
  double jetMindR   = JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
  double Nq	    = JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity;
  double Fq	    = JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction;
  int nRescaleBinT  = ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
  int nbinNq_Fq     = Nq_Fq->FindBin(Nq,Fq);
  int nbinNq_pT     = Nq_pT->FindBin(Nq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
  int nbinNq_Abseta = Nq_Abseta->FindBin(Nq,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
  int nbinFq_pT     = Fq_pT->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
  int nbinFq_Abseta = Fq_Abseta->FindBin(Fq,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
  int nbinpT_Abseta = pT_Abseta->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
  if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.1)
    {
      jet_taufakerate_Nq_Fq.push_back(Nq_Fq->GetBinContent(nbinNq_Fq));//*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerate_Nq_pT.push_back(Nq_pT->GetBinContent(nbinNq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerate_Nq_Abseta.push_back(Nq_Abseta->GetBinContent(nbinNq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerate_Fq_pT.push_back(Fq_pT->GetBinContent(nbinFq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerate_Fq_Abseta.push_back(Fq_Abseta->GetBinContent(nbinFq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerate_pT_Abseta.push_back(pT_Abseta->GetBinContent(nbinpT_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerateReweighted_Nq_Fq.push_back(Nq_Fq->GetBinContent(nbinNq_Fq)*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerateReweighted_Nq_pT.push_back(Nq_pT->GetBinContent(nbinNq_pT)*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerateReweighted_Nq_Abseta.push_back(Nq_Abseta->GetBinContent(nbinNq_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerateReweighted_Fq_pT.push_back(Fq_pT->GetBinContent(nbinFq_pT)*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerateReweighted_Fq_Abseta.push_back(Fq_Abseta->GetBinContent(nbinFq_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
      jet_taufakerateReweighted_pT_Abseta.push_back(pT_Abseta->GetBinContent(nbinpT_Abseta)*ReweightFactorT->GetBinContent(nRescaleBinT));
    }
  else
    {
      /*double jetMindR2=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
      if(jetMindR > 0.5 && jetMindR2 > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.2)
        {
    	  jet_taufakerate_Nq_Fq.push_back(Nq_Fq->GetBinContent(nbinNq_Fq));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    	  jet_taufakerate_Nq_pT.push_back(Nq_pT->GetBinContent(nbinNq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    	  jet_taufakerate_Nq_Abseta.push_back(Nq_Abseta->GetBinContent(nbinNq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    	  jet_taufakerate_Fq_pT.push_back(Fq_pT->GetBinContent(nbinFq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    	  jet_taufakerate_Fq_Abseta.push_back(Fq_Abseta->GetBinContent(nbinFq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    	  jet_taufakerate_pT_Abseta.push_back(pT_Abseta->GetBinContent(nbinpT_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
      }
    else
      {*/
    	jet_taufakerate_Nq_Fq.push_back(0.);
    	jet_taufakerate_Nq_pT.push_back(0.);
    	jet_taufakerate_Nq_Abseta.push_back(0.);
    	jet_taufakerate_Fq_pT.push_back(0.);
    	jet_taufakerate_Fq_Abseta.push_back(0.);
    	jet_taufakerate_pT_Abseta.push_back(0.);
    	jet_taufakerateReweighted_Nq_Fq.push_back(0.);
    	jet_taufakerateReweighted_Nq_pT.push_back(0.);
    	jet_taufakerateReweighted_Nq_Abseta.push_back(0.);
    	jet_taufakerateReweighted_Fq_pT.push_back(0.);
    	jet_taufakerateReweighted_Fq_Abseta.push_back(0.);
    	jet_taufakerateReweighted_pT_Abseta.push_back(0.);	
      //}
  }
}

//baseline enter all permutations
for(unsigned int i=0; i<baselineObjectSelectionCollection.tau.size(); i++){
  for(unsigned int j=0; j<jet.size(); j++){
    bool jetpass=true;
    if(jet[j].pt < 50)        jetpass=false;
    if(fabs(jet[j].eta) > 5.) jetpass=false;
    if((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy)/jet[j].energy >=0.99) jetpass=false;
    if(jet[j].neutralEmEnergyFraction >= 0.99) jetpass=false;
    if(jet[j].numberOfDaughters <=1) jetpass=false;
    if( fabs(jet[j].eta < 2.4) && (jet[j].chargedHadronEnergyFraction <= 0 || jet[j].chargedEmEnergyFraction >=0.99 || jet[j].chargedHadronMultiplicity <=0)) jetpass=false;
    double dR = deltaR(jet[j].eta, jet[j].phi, baselineObjectSelectionCollection.tau[i]->eta, baselineObjectSelectionCollection.tau[i]->phi); 
    //std::cout<<dR<<std::endl;
    if(dR >= 0.3){
      if(jetpass) pTjet_baseline->Fill(jet[j].pt); //take jets that are not the tau i
    }
    else{
      if(baselineObjectSelectionCollection.tau[i]->pt>=45 && fabs(jet[j].eta) <=2.1){
        pTtau_baseline->Fill(jet[j].pt); //take jet version of tight taus
	pTtauScaled_baseline->Fill(baselineObjectSelectionCollection.tau[i]->pt);
        response->Fill(jet[j].pt, 1.);
      }
      else{
        if(jetpass) pTjet_baseline->Fill(jet[j].pt);
        if(fabs(jet[j].eta) <=2.1) response->Fill(jet[j].pt, 0.);
      }
    }
  }
}

for(unsigned int i=0; i<jet_taufakerate_Nq_Fq.size(); i++){
  if(jet_taufakerate_Nq_Fq[i]==0) continue;
  for(unsigned int j=0; j<jet.size(); j++){
    if(i==j){
        pTtau_Nq_Fq->Fill(jet[j].pt, jet_taufakerate_Nq_Fq[i]);
	pTtauReweighted_Nq_Fq->Fill(jet[j].pt, jet_taufakerateReweighted_Nq_Fq[i]);
        int ScaleBinT  = ScaleFactorT->FindBin(jet[j].pt);
        double scale=ScaleFactorT->GetBinContent(ScaleBinT);
	if(jet[j].pt*scale>=45){
          pTtauScaled_Nq_Fq->Fill(jet[j].pt*scale, jet_taufakerate_Nq_Fq[i]);
	  pTtauPredicted_Nq_Fq->Fill(jet[j].pt*scale, jet_taufakerateReweighted_Nq_Fq[i]);
	}
      }
    else{
      if(jet[j].pt < 50)        continue;
      if(fabs(jet[j].eta) > 5.) continue;
      if((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy)/jet[j].energy >=0.99) continue;
      if(jet[j].neutralEmEnergyFraction >= 0.99) continue;
      if(jet[j].numberOfDaughters <=1) continue;
      if( fabs(jet[j].eta < 2.4) && (jet[j].chargedHadronEnergyFraction <= 0 || jet[j].chargedEmEnergyFraction >=0.99 || jet[j].chargedHadronMultiplicity <=0)) continue;
      pTjet_Nq_Fq->Fill(jet[j].pt, jet_taufakerate_Nq_Fq[i]);
      pTjetPredicted_Nq_Fq->Fill(jet[j].pt, jet_taufakerateReweighted_Nq_Fq[i]);
    }
  }
}

for(unsigned int i=0; i<jet_taufakerate_Nq_pT.size(); i++){
  if(jet_taufakerate_Nq_pT[i]==0) continue;
  for(unsigned int j=0; j<jet.size(); j++){
    if(i==j){
      pTtau_Nq_pT->Fill(jet[j].pt, jet_taufakerate_Nq_pT[i]);
      pTtauReweighted_Nq_pT->Fill(jet[j].pt, jet_taufakerateReweighted_Nq_pT[i]);
      int ScaleBinT  = ScaleFactorT->FindBin(jet[j].pt);
      double scale=ScaleFactorT->GetBinContent(ScaleBinT);
      pTtauScaled_Nq_pT->Fill(jet[j].pt*scale, jet_taufakerate_Nq_pT[i]);
      pTtauPredicted_Nq_pT->Fill(jet[j].pt*scale, jet_taufakerateReweighted_Nq_pT[i]);
    }
    else{
      if(jet[j].pt < 50)        continue;
      if(fabs(jet[j].eta) > 5.) continue;
      if((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy)/jet[j].energy >=0.99) continue;
      if(jet[j].neutralEmEnergyFraction >= 0.99) continue;
      if(jet[j].numberOfDaughters <=1) continue;
      if( fabs(jet[j].eta < 2.4) && (jet[j].chargedHadronEnergyFraction <= 0 || jet[j].chargedEmEnergyFraction >=0.99 || jet[j].chargedHadronMultiplicity <=0)) continue;
      pTjet_Nq_pT->Fill(jet[j].pt, jet_taufakerate_Nq_pT[i]);
      pTjetPredicted_Nq_pT->Fill(jet[j].pt, jet_taufakerateReweighted_Nq_pT[i]);
    }
  }
}

for(unsigned int i=0; i<jet_taufakerate_Nq_Abseta.size(); i++){
  if(jet_taufakerate_Nq_Abseta[i]==0) continue;
  for(unsigned int j=0; j<jet.size(); j++){
    if(i==j){
        pTtau_Nq_Abseta->Fill(jet[j].pt, jet_taufakerate_Nq_Abseta[i]);
	pTtauReweighted_Nq_Abseta->Fill(jet[j].pt, jet_taufakerateReweighted_Nq_Abseta[i]);
        int ScaleBinT  = ScaleFactorT->FindBin(jet[j].pt);
        double scale=ScaleFactorT->GetBinContent(ScaleBinT);
        pTtauScaled_Nq_Abseta->Fill(jet[j].pt*scale, jet_taufakerate_Nq_Abseta[i]);
	pTtauPredicted_Nq_Abseta->Fill(jet[j].pt*scale, jet_taufakerateReweighted_Nq_Abseta[i]);
      }
    else{
      if(jet[j].pt < 50)        continue;
      if(fabs(jet[j].eta) > 5.) continue;
      if((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy)/jet[j].energy >=0.99) continue;
      if(jet[j].neutralEmEnergyFraction >= 0.99) continue;
      if(jet[j].numberOfDaughters <=1) continue;
      if( fabs(jet[j].eta < 2.4) && (jet[j].chargedHadronEnergyFraction <= 0 || jet[j].chargedEmEnergyFraction >=0.99 || jet[j].chargedHadronMultiplicity <=0)) continue;
      pTjet_Nq_Abseta->Fill(jet[j].pt, jet_taufakerate_Nq_Abseta[i]);
      pTjetPredicted_Nq_Abseta->Fill(jet[j].pt, jet_taufakerateReweighted_Nq_Abseta[i]);
    }
  }
}

for(unsigned int i=0; i<jet_taufakerate_Fq_pT.size(); i++){
  if(jet_taufakerate_Fq_pT[i]==0) continue;
  for(unsigned int j=0; j<jet.size(); j++){
    if(i==j){
        pTtau_Fq_pT->Fill(jet[j].pt, jet_taufakerate_Fq_pT[i]);
	pTtauReweighted_Fq_pT->Fill(jet[j].pt, jet_taufakerateReweighted_Fq_pT[i]);
        int ScaleBinT  = ScaleFactorT->FindBin(jet[j].pt);
        double scale=ScaleFactorT->GetBinContent(ScaleBinT);
        pTtauScaled_Fq_pT->Fill(jet[j].pt*scale, jet_taufakerate_Fq_pT[i]);
	pTtauPredicted_Fq_pT->Fill(jet[j].pt*scale, jet_taufakerateReweighted_Fq_pT[i]);
      }
    else{
      if(jet[j].pt < 50)        continue;
      if(fabs(jet[j].eta) > 5.) continue;
      if((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy)/jet[j].energy >=0.99) continue;
      if(jet[j].neutralEmEnergyFraction >= 0.99) continue;
      if(jet[j].numberOfDaughters <=1) continue;
      if( fabs(jet[j].eta < 2.4) && (jet[j].chargedHadronEnergyFraction <= 0 || jet[j].chargedEmEnergyFraction >=0.99 || jet[j].chargedHadronMultiplicity <=0)) continue;
      pTjet_Fq_pT->Fill(jet[j].pt, jet_taufakerate_Fq_pT[i]);
      pTjetPredicted_Fq_pT->Fill(jet[j].pt, jet_taufakerateReweighted_Fq_pT[i]);
    }
  }
}

for(unsigned int i=0; i<jet_taufakerate_Fq_Abseta.size(); i++){
  if(jet_taufakerate_Fq_Abseta[i]==0) continue;
  for(unsigned int j=0; j<jet.size(); j++){
    if(i==j){
        pTtau_Fq_Abseta->Fill(jet[j].pt, jet_taufakerate_Fq_Abseta[i]);
	pTtauReweighted_Fq_Abseta->Fill(jet[j].pt, jet_taufakerateReweighted_Fq_Abseta[i]);
	int ScaleBinT  = ScaleFactorT->FindBin(jet[j].pt);
        double scale=ScaleFactorT->GetBinContent(ScaleBinT);
        pTtauScaled_Fq_Abseta->Fill(jet[j].pt*scale, jet_taufakerate_Fq_Abseta[i]);
	pTtauPredicted_Fq_Abseta->Fill(jet[j].pt*scale, jet_taufakerateReweighted_Fq_Abseta[i]);
      }
    else{
      if(jet[j].pt < 50)        continue;
      if(fabs(jet[j].eta) > 5.) continue;
      if((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy)/jet[j].energy >=0.99) continue;
      if(jet[j].neutralEmEnergyFraction >= 0.99) continue;
      if(jet[j].numberOfDaughters <=1) continue;
      if( fabs(jet[j].eta < 2.4) && (jet[j].chargedHadronEnergyFraction <= 0 || jet[j].chargedEmEnergyFraction >=0.99 || jet[j].chargedHadronMultiplicity <=0)) continue;
      pTjet_Fq_Abseta->Fill(jet[j].pt, jet_taufakerate_Fq_Abseta[i]);
      pTjetPredicted_Fq_Abseta->Fill(jet[j].pt, jet_taufakerateReweighted_Fq_Abseta[i]);
    }
  }
}

for(unsigned int i=0; i<jet_taufakerate_pT_Abseta.size(); i++){
  if(jet_taufakerate_pT_Abseta[i]==0) continue;
  for(unsigned int j=0; j<jet.size(); j++){
    if(i==j){
        pTtau_pT_Abseta->Fill(jet[j].pt, jet_taufakerate_pT_Abseta[i]);
	pTtauReweighted_pT_Abseta->Fill(jet[j].pt, jet_taufakerateReweighted_pT_Abseta[i]);
	int ScaleBinT  = ScaleFactorT->FindBin(jet[j].pt);
        double scale=ScaleFactorT->GetBinContent(ScaleBinT);
        pTtauScaled_pT_Abseta->Fill(jet[j].pt*scale, jet_taufakerate_pT_Abseta[i]);
	pTtauPredicted_pT_Abseta->Fill(jet[j].pt*scale, jet_taufakerateReweighted_pT_Abseta[i]);
      }
    else{
      if(jet[j].pt < 50)        continue;
      if(fabs(jet[j].eta) > 5.) continue;
      if((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy)/jet[j].energy >=0.99) continue;
      if(jet[j].neutralEmEnergyFraction >= 0.99) continue;
      if(jet[j].numberOfDaughters <=1) continue;
      if( fabs(jet[j].eta < 2.4) && (jet[j].chargedHadronEnergyFraction <= 0 || jet[j].chargedEmEnergyFraction >=0.99 || jet[j].chargedHadronMultiplicity <=0)) continue;
      pTjet_pT_Abseta->Fill(jet[j].pt, jet_taufakerate_pT_Abseta[i]);
      pTjetPredicted_pT_Abseta->Fill(jet[j].pt, jet_taufakerateReweighted_pT_Abseta[i]);
    }
  }
}

//Event Count
ofile.count("NoCuts");

//Clearing Object Collections 
JetLooseIsoObjectSelectionCollection.clear();
baselineObjectSelectionCollection.clear();
}

  stream.close();
  ofile.close();
  return 0;
}

