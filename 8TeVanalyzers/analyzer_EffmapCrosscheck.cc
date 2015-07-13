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
  
  double etaedges[5]={0.,1.4,1.6,2.,2.2};
  double ptedges[12]={0.,30.,45.,55.,75.,100.,250.,400.,600.,900.,1500.,2500.};
  double Nedges[31]={0,1,2,3,4,5,6,7,8,10,12,14,16,20,24,28,32,36,40,45,50,55,60,70,80,90,100,120,140,170,200};
  double FractionEdges[16]={0.0,0.05,0.1,0.15,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.8,0.85,0.9,0.95,1.};

  TH2F* h2_Nq_Fq_num = new TH2F("h2_Nq_Fq_num", "h2_Nq_Fq_num", 30, Nedges, 15, FractionEdges);
  TH2F* h2_Nq_Fq_den = new TH2F("h2_Nq_Fq_den", "h2_Nq_Fq_den", 30, Nedges, 15, FractionEdges);
  h2_Nq_Fq_num->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Fq_den->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Fq_num->GetYaxis()->SetTitle("F^{q}");
  h2_Nq_Fq_den->GetYaxis()->SetTitle("F^{q}");  
  h2_Nq_Fq_num->Sumw2();
  h2_Nq_Fq_den->Sumw2();
  
  TH2F* h2_Nq_pT_num = new TH2F("h2_Nq_pT_num", "h2_Nq_pT_num", 30, Nedges, 11, ptedges);
  TH2F* h2_Nq_pT_den = new TH2F("h2_Nq_pT_den", "h2_Nq_pT_den", 30, Nedges, 11, ptedges);
  h2_Nq_pT_num->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_pT_den->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_pT_num->GetYaxis()->SetTitle("p_{T}");
  h2_Nq_pT_den->GetYaxis()->SetTitle("p_{T}");  
  h2_Nq_pT_num->Sumw2();
  h2_Nq_pT_den->Sumw2(); 
  
  TH2F* h2_Nq_Abseta_num = new TH2F("h2_Nq_Abseta_num", "h2_Nq_Abseta_num", 30, Nedges, 4, etaedges);
  TH2F* h2_Nq_Abseta_den = new TH2F("h2_Nq_Abseta_den", "h2_Nq_Abseta_den", 30, Nedges, 4, etaedges);
  h2_Nq_Abseta_num->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Abseta_den->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Abseta_num->GetYaxis()->SetTitle("|#eta|");
  h2_Nq_Abseta_den->GetYaxis()->SetTitle("|#eta|");  
  h2_Nq_Abseta_num->Sumw2();
  h2_Nq_Abseta_den->Sumw2();  
  
  TH2F* h2_Fq_pT_num = new TH2F("h2_Fq_pT_num", "h2_Fq_pT_num", 15, FractionEdges, 11, ptedges);
  TH2F* h2_Fq_pT_den = new TH2F("h2_Fq_pT_den", "h2_Fq_pT_den", 15, FractionEdges, 11, ptedges);
  h2_Fq_pT_num->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_pT_den->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_pT_num->GetYaxis()->SetTitle("p_{T}");
  h2_Fq_pT_den->GetYaxis()->SetTitle("p_{T}");  
  h2_Fq_pT_num->Sumw2();
  h2_Fq_pT_den->Sumw2();    
  
  TH2F* h2_Fq_Abseta_num = new TH2F("h2_Fq_Abseta_num", "h2_Fq_Abseta_num", 15, FractionEdges, 4, etaedges);
  TH2F* h2_Fq_Abseta_den = new TH2F("h2_Fq_Abseta_den", "h2_Fq_Abseta_den", 15, FractionEdges, 4, etaedges);
  h2_Fq_Abseta_num->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_Abseta_den->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_Abseta_num->GetYaxis()->SetTitle("|#eta|");
  h2_Fq_Abseta_den->GetYaxis()->SetTitle("|#eta|");  
  h2_Fq_Abseta_num->Sumw2();
  h2_Fq_Abseta_den->Sumw2();   

  TH2F* h2_pT_Abseta_num = new TH2F("h2_pT_Abseta_num", "h2_pT_Abseta_num", 11, ptedges, 4, etaedges);
  TH2F* h2_pT_Abseta_den = new TH2F("h2_pT_Abseta_den", "h2_pT_Abseta_den", 11, ptedges, 4, etaedges);
  h2_pT_Abseta_num->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_pT_Abseta_den->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_pT_Abseta_num->GetYaxis()->SetTitle("|#eta|");
  h2_pT_Abseta_den->GetYaxis()->SetTitle("|#eta|");  
  h2_pT_Abseta_num->Sumw2();
  h2_pT_Abseta_den->Sumw2();  

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

TH1::SetDefaultSumw2();
TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/EffmapVariations.root", "read");
TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseFactors_InclAndExclIsos_Jet30Lukas_MC_Tau45.root", "read");

MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
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

ofile.count("NoCuts",1.);

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

TH1F* ReweightFactorT = (TH1F*)(file_Resp.Get("RescaleWeightT"));

vector<double> jet_taufakerate_Nq_Fq;
vector<double> jet_taufakerate_Nq_pT;
vector<double> jet_taufakerate_Nq_Abseta;
vector<double> jet_taufakerate_Fq_pT;
vector<double> jet_taufakerate_Fq_Abseta;
vector<double> jet_taufakerate_pT_Abseta;

for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
double Nq=JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity;
double Fq=JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction;
int nbinNq_Fq = Nq_Fq->FindBin(Nq,Fq);
int nbinNq_pT = Nq_pT->FindBin(Nq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinNq_Abseta = Nq_Abseta->FindBin(Nq,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
int nbinFq_pT = Fq_pT->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinFq_Abseta = Fq_Abseta->FindBin(Fq,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
int nbinpT_Abseta = pT_Abseta->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
int nRescaleBinT= ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
if(verbose)std::cout<<"Jet "<<i<<" out of "<<JetLooseIsoObjectSelectionCollection.jet.size()<<": pT="<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", eta="<<JetLooseIsoObjectSelectionCollection.jet[i]->eta<<", phi="<<JetLooseIsoObjectSelectionCollection.jet[i]->phi<<std::endl;
if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.1)
  {
    jet_taufakerate_Nq_Fq.push_back(Nq_Fq->GetBinContent(nbinNq_Fq));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Nq_pT.push_back(Nq_pT->GetBinContent(nbinNq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Nq_Abseta.push_back(Nq_Abseta->GetBinContent(nbinNq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Fq_pT.push_back(Fq_pT->GetBinContent(nbinFq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_Fq_Abseta.push_back(Fq_Abseta->GetBinContent(nbinFq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
    jet_taufakerate_pT_Abseta.push_back(pT_Abseta->GetBinContent(nbinpT_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));                    
    /*std::cout<<"NF of "<<i<<": "<<Nq<<", "<<Fq<<", "<<Nq_Fq->GetBinContent(nbinNq_Fq)<<std::endl;
    std::cout<<"Np of "<<i<<": "<<Nq<<", "<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", "<<Nq_pT->GetBinContent(nbinNq_pT)<<std::endl;
    std::cout<<"NA of "<<i<<": "<<Nq<<", "<<fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)<<", "<<Nq_Abseta->GetBinContent(nbinNq_Abseta)<<std::endl;
    std::cout<<"Fp of "<<i<<": "<<Fq<<", "<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", "<<Fq_pT->GetBinContent(nbinFq_pT)<<std::endl;
    std::cout<<"FA of "<<i<<": "<<Fq<<", "<<fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)<<", "<<Fq_Abseta->GetBinContent(nbinFq_Abseta)<<std::endl;
    std::cout<<"pA of "<<i<<": "<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", "<<fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)<<",
    "<<pT_Abseta->GetBinContent(nbinpT_Abseta)<<std::endl;    */
    h2_Nq_Fq_den->Fill(Nq, Fq);
    h2_Nq_pT_den->Fill(Nq, JetLooseIsoObjectSelectionCollection.jet[i]->pt);
    h2_Nq_Abseta_den->Fill(Nq, fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
    h2_Fq_pT_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[i]->pt);
    h2_Fq_Abseta_den->Fill(Fq, fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
    h2_pT_Abseta_den->Fill(JetLooseIsoObjectSelectionCollection.jet[i]->pt, fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
  }
else
  {
    double jetMindR2=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
    if(jetMindR > 0.5 && jetMindR2 > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.2)
      {
        jet_taufakerate_Nq_Fq.push_back(Nq_Fq->GetBinContent(nbinNq_Fq));//*ReweightFactorT->GetBinContent(nRescaleBinT));
        jet_taufakerate_Nq_pT.push_back(Nq_pT->GetBinContent(nbinNq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
        jet_taufakerate_Nq_Abseta.push_back(Nq_Abseta->GetBinContent(nbinNq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
        jet_taufakerate_Fq_pT.push_back(Nq_pT->GetBinContent(nbinFq_pT));//*ReweightFactorT->GetBinContent(nRescaleBinT));
        jet_taufakerate_Fq_Abseta.push_back(Fq_Abseta->GetBinContent(nbinFq_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
        jet_taufakerate_pT_Abseta.push_back(pT_Abseta->GetBinContent(nbinpT_Abseta));//*ReweightFactorT->GetBinContent(nRescaleBinT));
	
        h2_Nq_Fq_den->Fill(Nq, Fq);
        h2_Nq_pT_den->Fill(Nq, JetLooseIsoObjectSelectionCollection.jet[i]->pt);
        h2_Nq_Abseta_den->Fill(Nq, fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
        h2_Fq_pT_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[i]->pt);
        h2_Fq_Abseta_den->Fill(Fq, fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));
        h2_pT_Abseta_den->Fill(JetLooseIsoObjectSelectionCollection.jet[i]->pt, fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta));	
      }
    else
      {
        jet_taufakerate_Nq_Fq.push_back(0);
    	jet_taufakerate_Nq_pT.push_back(0);
	jet_taufakerate_Nq_Abseta.push_back(0);
	jet_taufakerate_Fq_pT.push_back(0);
	jet_taufakerate_Fq_Abseta.push_back(0);
	jet_taufakerate_pT_Abseta.push_back(0);
	if(verbose)std::cout<<"Failed: P=0!"<<std::endl;
      }
  }
}

//rederive efficiency maps
Fake FakeTaus_Nq_Fq("FakeTaus_Nq_Fq");
FakeTaus_Nq_Fq.generate(jet_taufakerate_Nq_Fq,jet_taufakerate_Nq_Fq, true);

Fake FakeTaus_Nq_pT("FakeTaus_Nq_pT");
FakeTaus_Nq_pT.generate(jet_taufakerate_Nq_pT,jet_taufakerate_Nq_pT, true);

Fake FakeTaus_Nq_Abseta("FakeTaus_Nq_Abseta");
FakeTaus_Nq_Abseta.generate(jet_taufakerate_Nq_Abseta,jet_taufakerate_Nq_Abseta, true);

Fake FakeTaus_Fq_pT("FakeTaus_Fq_pT");
FakeTaus_Fq_pT.generate(jet_taufakerate_Fq_pT,jet_taufakerate_Fq_pT, true);

Fake FakeTaus_Fq_Abseta("FakeTaus_Fq_Abseta");
FakeTaus_Fq_Abseta.generate(jet_taufakerate_Fq_Abseta,jet_taufakerate_Fq_Abseta, true);

Fake FakeTaus_pT_Abseta("FakeTaus_pT_Abseta");
FakeTaus_pT_Abseta.generate(jet_taufakerate_pT_Abseta,jet_taufakerate_pT_Abseta, true);

if ( FakeTaus_Nq_Fq.index.first >= 0 && FakeTaus_Nq_Fq.index.second >= 0 ) {
int j=FakeTaus_Nq_Fq.index.first;
double Nq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity;
double Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;
h2_Nq_Fq_num->Fill(Nq, Fq, FakeTaus_Nq_Fq.weight);
j=FakeTaus_Nq_Fq.index.second;
Nq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity;
Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;
h2_Nq_Fq_num->Fill(Nq, Fq, FakeTaus_Nq_Fq.weight);
}

if ( FakeTaus_Nq_pT.index.first >= 0 && FakeTaus_Nq_pT.index.second >= 0 ) {
int j=FakeTaus_Nq_pT.index.first;
double Nq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity;
double pT=JetLooseIsoObjectSelectionCollection.jet[j]->pt;
h2_Nq_pT_num->Fill(Nq, pT, FakeTaus_Nq_pT.weight);
j=FakeTaus_Nq_pT.index.second;
Nq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity;
pT=JetLooseIsoObjectSelectionCollection.jet[j]->pt;
h2_Nq_pT_num->Fill(Nq, pT, FakeTaus_Nq_pT.weight);
//std::cout<<"Np: "<<FakeTaus_Nq_pT.index.first<<", "<<FakeTaus_Nq_pT.index.second<<std::endl;
}

if ( FakeTaus_Nq_Abseta.index.first >= 0 && FakeTaus_Nq_Abseta.index.second >= 0 ) {
int j=FakeTaus_Nq_Abseta.index.first;
double Nq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity;
double Abseta=fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta);
h2_Nq_Abseta_num->Fill(Nq, Abseta, FakeTaus_Nq_Abseta.weight);
j=FakeTaus_Nq_Abseta.index.second;
Nq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity;
Abseta=fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta);
h2_Nq_Abseta_num->Fill(Nq, Abseta, FakeTaus_Nq_Abseta.weight);
}

if ( FakeTaus_Fq_pT.index.first >= 0 && FakeTaus_Fq_pT.index.second >= 0 ) {
int j=FakeTaus_Fq_pT.index.first;
double Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;
double pT=JetLooseIsoObjectSelectionCollection.jet[j]->pt;
h2_Fq_pT_num->Fill(Fq, pT, FakeTaus_Fq_pT.weight);
j=FakeTaus_Fq_pT.index.second;
Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;
pT=JetLooseIsoObjectSelectionCollection.jet[j]->pt;
h2_Fq_pT_num->Fill(Fq, pT, FakeTaus_Fq_pT.weight);
}

if ( FakeTaus_Fq_Abseta.index.first >= 0 && FakeTaus_Fq_Abseta.index.second >= 0 ) {
int j=FakeTaus_Fq_Abseta.index.first;
double Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;
double Abseta=fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta);
h2_Fq_Abseta_num->Fill(Fq, Abseta, FakeTaus_Fq_Abseta.weight);
j=FakeTaus_Fq_Abseta.index.second;
Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;
Abseta=fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta);
h2_Fq_Abseta_num->Fill(Fq, Abseta, FakeTaus_Fq_Abseta.weight);
}

if ( FakeTaus_pT_Abseta.index.first >= 0 && FakeTaus_pT_Abseta.index.second >= 0 ) {
int j=FakeTaus_pT_Abseta.index.first;
double pT=JetLooseIsoObjectSelectionCollection.jet[j]->pt;
double Abseta=fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta);
h2_pT_Abseta_num->Fill(pT, Abseta, FakeTaus_pT_Abseta.weight);
j=FakeTaus_pT_Abseta.index.second;
pT=JetLooseIsoObjectSelectionCollection.jet[j]->pt;
Abseta=fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta);
h2_pT_Abseta_num->Fill(pT, Abseta, FakeTaus_pT_Abseta.weight);
//std::cout<<"pAbs: "<<FakeTaus_pT_Abseta.index.first<<", "<<FakeTaus_pT_Abseta.index.second<<std::endl;
}
//std::cout<<"___________________________"<<std::endl;
//Clearing Object Collections
JetLooseIsoObjectSelectionCollection.clear();

if(verbose)std::cout<<"_______________________________________________"<<std::endl;
}

  stream.close();
  ofile.close();
  return 0;
}

