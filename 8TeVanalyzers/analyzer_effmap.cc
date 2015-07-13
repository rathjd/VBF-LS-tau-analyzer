//-----------------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for ntuples created by TheNtupleMaker
// Created:     Fri Apr  5 13:23:28 2013 by mkntanalyzer.py
// Author:      Daniele Marconi
//-----------------------------------------------------------------------------
#include "analyzer.h"

#ifdef PROJECT_NAME
#include "PhysicsTools/TheNtupleMaker/interface/pdg.h"
#else
#include "pdg.h"
#endif

#include "CommonHistoCollection.h"
#include "TH3.h"

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

  //int nevents = 1000;
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

  //TH1F* h_mindeltaR = new TH1F("h_mindeltaR", "h_mindeltaR", 50,0. , 3.);

  double etaedges[5]={0.,1.4,1.6,2.,2.2};
  double etaExtended[23]={0.,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2};
  double ptedges[12]={0.,30.,45.,55.,75.,100.,250.,400.,600.,900.,1500.,2500.};
  double respEdges[29]={0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,1.50};
  double Nedges[31]={0,1,2,3,4,5,6,7,8,10,12,14,16,20,24,28,32,36,40,45,50,55,60,70,80,90,100,120,140,170,200};
  double FractionEdges[16]={0.0,0.05,0.1,0.15,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.8,0.85,0.9,0.95,1.};


  TH1F* h1_jetpt = new TH1F("h1_jetpt", "h1_jetpt", 50, 0., 500.);
  TH1F* h1_jet1pt = new TH1F("h1_jet1pt", "h1_jet1pt", 50, 0., 500.);
  TH1F* h1_jet2pt = new TH1F("h1_jet2pt", "h1_jet2pt", 50, 0., 500.);

  TH2F* h2_taufakerate_num = new TH2F("h2_taufakerate_num", "h2_taufakerate_num", 11, ptedges, 4, etaedges);
  TH2F* h2_taufakerate_den = new TH2F("h2_taufakerate_den", "h2_taufakerate_den", 11, ptedges, 4, etaedges);
  h2_taufakerate_num->Sumw2();
  h2_taufakerate_den->Sumw2();
  
  TH1F* h1_taufakerate_pt_num = new TH1F("h1_taufakerate_pt_num", "h1_taufakerate_pt_num", 11, ptedges);
  TH1F* h1_taufakerate_pt_den = new TH1F("h1_taufakerate_pt_den", "h1_taufakerate_pt_den", 11, ptedges);
  h1_taufakerate_pt_num->Sumw2();
  h1_taufakerate_pt_den->Sumw2();

  TH1F* h1_taufakerate_ptjet1_num = new TH1F("h1_taufakerate_ptjet1_num", "h1_taufakerate_ptjet1_num", 10, ptedges);
  TH1F* h1_taufakerate_ptjet1_den = new TH1F("h1_taufakerate_ptjet1_den", "h1_taufakerate_ptjet1_den", 10, ptedges);
  h1_taufakerate_ptjet1_num->Sumw2();
  h1_taufakerate_ptjet1_den->Sumw2();

  TH1F* h1_taufakerate_ptjet2_num = new TH1F("h1_taufakerate_ptjet2_num", "h1_taufakerate_ptjet2_num", 10, ptedges);
  TH1F* h1_taufakerate_ptjet2_den = new TH1F("h1_taufakerate_ptjet2_den", "h1_taufakerate_ptjet2_den", 10, ptedges);
  h1_taufakerate_ptjet2_num->Sumw2();
  h1_taufakerate_ptjet2_den->Sumw2();

  TH1F* h1_taufakerate_ptjet3_num = new TH1F("h1_taufakerate_ptjet3_num", "h1_taufakerate_ptjet3_num", 10, ptedges);
  TH1F* h1_taufakerate_ptjet3_den = new TH1F("h1_taufakerate_ptjet3_den", "h1_taufakerate_ptjet3_den", 10, ptedges);
  h1_taufakerate_ptjet3_num->Sumw2();
  h1_taufakerate_ptjet3_den->Sumw2();

  TH1F* h1_taufakerate_ptjet4_num = new TH1F("h1_taufakerate_ptjet4_num", "h1_taufakerate_ptjet4_num", 10, ptedges);
  TH1F* h1_taufakerate_ptjet4_den = new TH1F("h1_taufakerate_ptjet4_den", "h1_taufakerate_ptjet4_den", 10, ptedges);
  h1_taufakerate_ptjet4_num->Sumw2();
  h1_taufakerate_ptjet4_den->Sumw2();

  TH1F* h1_taufakerate_jetrank_num = new TH1F("h1_taufakerate_jetrank_num", "h1_taufakerate_jetrank_num", 6, 0.5, 6.5);
  TH1F* h1_taufakerate_jetrank_den = new TH1F("h1_taufakerate_jetrank_den", "h1_taufakerate_jetrank_den", 6, 0.5, 6.5);
  h1_taufakerate_jetrank_num->Sumw2();
  h1_taufakerate_jetrank_den->Sumw2();
 
  TH2F* h2_taufakerate_dR_num = new TH2F("h2_taufakerate_dR_num", "h2_taufakerate_dR_num", 11, ptedges, 25, 0., 0.5);
  TH2F* h2_taufakerate_dRl_num = new TH2F("h2_taufakerate_dRl_num", "h2_taufakerate_dRl_num", 11, ptedges, 25, 0., 0.5);  
  TH2F* h2_taufakerate_dR_den = new TH2F("h2_taufakerate_dR_den", "h2_taufakerate_dR_den", 11, ptedges, 25, 0., 0.5);  
  
  TH2F* h2_taufakerate_loose_num = new TH2F("h2_taufakerate_loose_num", "h2_taufakerate_loose_num", 11, ptedges, 4, etaedges);
  h2_taufakerate_loose_num->Sumw2();
  TH2F* h2_taufakerate_loose_den = new TH2F("h2_taufakerate_loose_den", "h2_taufakerate_loose_den", 11, ptedges, 4, etaedges);
  h2_taufakerate_loose_den->Sumw2();  
  
  TH1F* h1_taufakescale_num = new TH1F("h1_taufakescale_num", "h1_taufakescale_num", 4, etaedges);
  TH1F* h1_taufakescale_den = new TH1F("h1_taufakescale_den", "h1_taufakescale_den", 4, etaedges);  
  h1_taufakescale_num->Sumw2();
  h1_taufakescale_den->Sumw2();
  
  TH1F* h1_taufakescale_pt_num = new TH1F("h1_taufakescale_pt_num", "h1_taufakescale_pt_num", 11, ptedges);
  TH1F* h1_taufakescale_pt_den = new TH1F("h1_taufakescale_pt_den", "h1_taufakescale_pt_den", 11, ptedges);  
  h1_taufakescale_pt_num->Sumw2();
  h1_taufakescale_pt_den->Sumw2();  
  
  TH1F* h1_taufakescale_loose_num = new TH1F("h1_taufakescale_loose_num", "h1_taufakescale_loose_num", 4, etaedges);
  TH1F* h1_taufakescale_loose_den = new TH1F("h1_taufakescale_loose_den", "h1_taufakescale_loose_den", 4, etaedges);
  h1_taufakescale_loose_num->Sumw2();
  h1_taufakescale_loose_den->Sumw2();
  
  TH1F* h1_taufakescale_loose_pt_num = new TH1F("h1_taufakescale_loose_pt_num", "h1_taufakescale_loose_pt_num", 11, ptedges);
  TH1F* h1_taufakescale_loose_pt_den = new TH1F("h1_taufakescale_loose_pt_den", "h1_taufakescale_loose_pt_den", 11, ptedges);  
  h1_taufakescale_loose_pt_num->Sumw2();
  h1_taufakescale_loose_pt_den->Sumw2();     
  
  TH2F* h2_taufakerate_dRjet_num = new TH2F("h2_taufakerate_dRjet_num", "h2_taufakerate_dRjet_num", 11, ptedges,50, 0., 1.);
  h2_taufakerate_dRjet_num->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_taufakerate_dRjet_num->GetYaxis()->SetTitle("dR(jet,jet)");
  TH2F* h2_taufakerate_dRjetl_num = new TH2F("h2_taufakerate_dRjetl_num", "h2_taufakerate_dRjetl_num", 11, ptedges,50, 0., 1.);  
  h2_taufakerate_dRjetl_num->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_taufakerate_dRjetl_num->GetYaxis()->SetTitle("dR(jet,jet)");
  TH2F* h2_taufakerate_dRjet_den = new TH2F("h2_taufakerate_dRjet_den", "h2_taufakerate_dRjet_den", 11, ptedges, 50, 0., 1.);    
  h2_taufakerate_dRjet_den->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_taufakerate_dRjet_den->GetYaxis()->SetTitle("dR(jet,jet)");
  
  TH2F* h2_tauResponse_loose = new TH2F("h2_tauResponse_loose", "h2_tauResponse_loose", 11, ptedges, 60, 0, 3);
  TH2F* h2_tauResponse = new TH2F("h2_tauResponse", "h2_tauResponse", 11, ptedges, 60, 0, 3);  
  h2_tauResponse_loose->Sumw2();
  h2_tauResponse->Sumw2();    
  h2_tauResponse->GetXaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h2_tauResponse_loose->GetXaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  
  TH3F* h3_tauComplete = new TH3F("h3_tauComplete","h3_tauComplete", 11, ptedges, 28, respEdges, 4, etaedges); 
  h3_tauComplete->GetXaxis()->SetTitle("p_{T}^{jet}");
  h3_tauComplete->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h3_tauComplete->GetZaxis()->SetTitle("|#eta|");
  h3_tauComplete->Sumw2();
  
  TH3F* h3_tauComplete_loose = new TH3F("h3_tauComplete_loose","h3_tauComplete_loose", 11, ptedges, 28, respEdges, 4, etaedges); 
  h3_tauComplete_loose->GetXaxis()->SetTitle("p_{T}^{jet}");
  h3_tauComplete_loose->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h3_tauComplete_loose->GetZaxis()->SetTitle("|#eta|");
  h3_tauComplete_loose->Sumw2();  
  
  TH2F* NjetNtau = new TH2F("NjetNtau","number of jets vs number of fake taus", 20, 0, 20, 4, 0, 3);
  NjetNtau->GetXaxis()->SetTitle("N_{jet}");
  NjetNtau->GetYaxis()->SetTitle("N_{#tau}");
  NjetNtau->Sumw2();
  TH2F* NjetNtauLoose = new TH2F("NjetNtauLoose","number of jets vs number of loose fake taus", 20, 0, 20, 4, 0, 3);
  NjetNtauLoose->GetXaxis()->SetTitle("N_{jet}");
  NjetNtauLoose->GetYaxis()->SetTitle("N_{#tau}");
  NjetNtauLoose->Sumw2();  
  
  TH1F* Nod_num = new TH1F("Nod_num","jet number of daughters", 200, 0, 200);
  Nod_num->GetXaxis()->SetTitle("number of daughters");
  Nod_num->Sumw2();
  TH1F* Nod_loose_num = new TH1F("Nod_loose_num","jet number of daughters", 200, 0, 200);
  Nod_loose_num->GetXaxis()->SetTitle("number of daughters");
  Nod_loose_num->Sumw2();  
  TH1F* Nod_den = new TH1F("Nod_den","jet number of daughters", 200, 0, 200);
  Nod_den->GetXaxis()->SetTitle("number of daughters");
  Nod_den->Sumw2();  
  
  TH3F* NOD_charge_num = new TH3F("NOD_charge_num","jet number of daughters by charges", 200, 0, 200, 200, 0, 200, 200, 0, 200);
  NOD_charge_num->GetXaxis()->SetTitle("charged hadron multiplicity");
  NOD_charge_num->GetYaxis()->SetTitle("neutral hadron multiplicity");
  NOD_charge_num->GetZaxis()->SetTitle("EM charged energy fraction x NOD");
  NOD_charge_num->Sumw2();
  TH3F* NOD_charge_loose_num = new TH3F("NOD_charge_loose_num","jet number of daughters by charges", 200, 0, 200, 200, 0, 200, 200, 0, 200);
  NOD_charge_loose_num->GetXaxis()->SetTitle("charged hadron multiplicity");
  NOD_charge_loose_num->GetYaxis()->SetTitle("neutral hadron multiplicity");
  NOD_charge_loose_num->GetZaxis()->SetTitle("EM charged energy fraction x NOD");
  NOD_charge_loose_num->Sumw2();  
  TH3F* NOD_charge_den = new TH3F("NOD_charge_den","jet number of daughters by charges", 200, 0, 200, 200, 0, 200, 200, 0, 200);
  NOD_charge_den->GetXaxis()->SetTitle("charged hadron multiplicity");
  NOD_charge_den->GetYaxis()->SetTitle("neutral hadron multiplicity");
  NOD_charge_den->GetZaxis()->SetTitle("charged EM multiplicity");
  NOD_charge_den->Sumw2(); 
  
  TH2F* Efrac_num = new TH2F("Efrac_num","charged energy vs neutral energy fraction", 100, 0, 1, 100, 0, 1);
  Efrac_num->GetXaxis()->SetTitle("charged EM and hadronic energy fraction");
  Efrac_num->GetYaxis()->SetTitle("neutral EM and hadronic energy fraction");
  Efrac_num->Sumw2();
  TH2F* Efrac_den = new TH2F("Efrac_den","charged energy vs neutral energy fraction", 100, 0, 1, 100, 0, 1);
  Efrac_den->GetXaxis()->SetTitle("charged EM and hadronic energy fraction");
  Efrac_den->GetYaxis()->SetTitle("neutral EM and hadronic energy fraction");
  Efrac_den->Sumw2();  
  
  TH2F* Etype_num = new TH2F("Etype_num","charged energy vs neutral energy fraction", 100, 0, 1, 100, 0, 1);
  Etype_num->GetXaxis()->SetTitle("EM energy fraction");
  Etype_num->GetYaxis()->SetTitle("hadronic energy fraction");
  Etype_num->Sumw2();
  TH2F* Etype_den = new TH2F("Etype_den","EM energy vs hadronic energy fraction", 100, 0, 1, 100, 0, 1);
  Etype_den->GetXaxis()->SetTitle("EM energy fraction");
  Etype_den->GetYaxis()->SetTitle("hadronic energy fraction");
  Etype_den->Sumw2();    
  
  TH2F* ChargeMapN_num = new TH2F("ChargeMapN_num","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);
  ChargeMapN_num->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapN_num->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapN_num->Sumw2();
  TH2F* ChargeMapL_num = new TH2F("ChargeMapL_num","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);
  ChargeMapL_num->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapL_num->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapL_num->Sumw2();  
  TH2F* ChargeMapLi_num = new TH2F("ChargeMapLi_num","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);
  ChargeMapLi_num->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapLi_num->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapLi_num->Sumw2();    
  TH2F* ChargeMapM_num = new TH2F("ChargeMapM_num","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);
  ChargeMapM_num->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapM_num->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapM_num->Sumw2();
  TH2F* ChargeMapMi_num = new TH2F("ChargeMapMi_num","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);
  ChargeMapMi_num->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapMi_num->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapMi_num->Sumw2(); 
  TH2F* ChargeMapT_num = new TH2F("ChargeMapT_num","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);
  ChargeMapT_num->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapT_num->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapT_num->Sumw2();    
  TH2F* ChargeMapN_den = new TH2F("ChargeMapN_den","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);  
  ChargeMapN_den->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapN_den->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapN_den->Sumw2();
  TH2F* ChargeMapL_den = new TH2F("ChargeMapL_den","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);  
  ChargeMapL_den->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapL_den->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapL_den->Sumw2();  
  TH2F* ChargeMapLi_den = new TH2F("ChargeMapLi_den","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);  
  ChargeMapLi_den->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapLi_den->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapLi_den->Sumw2();   
  TH2F* ChargeMapM_den = new TH2F("ChargeMapM_den","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);  
  ChargeMapM_den->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapM_den->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapM_den->Sumw2();  
  TH2F* ChargeMapMi_den = new TH2F("ChargeMapMi_den","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);  
  ChargeMapMi_den->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapMi_den->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapMi_den->Sumw2();   
  TH2F* ChargeMapT_den = new TH2F("ChargeMapT_den","number of charged daughters versus charged energy fraction", 30, Nedges, 15, FractionEdges);  
  ChargeMapT_den->GetXaxis()->SetTitle("number of charged particles");
  ChargeMapT_den->GetYaxis()->SetTitle("charged EM and hadronic energy fraction");
  ChargeMapT_den->Sumw2();  
  
  TH2F*ChargedPt_num = new TH2F("ChargedPt_num","number of charged daughters versus p_{T}", 30, Nedges, 11, ptedges);
  ChargedPt_num->GetXaxis()->SetTitle("number of charged hadrons");
  ChargedPt_num->GetYaxis()->SetTitle("p_{T}");  
  ChargedPt_num->Sumw2();
  TH2F*ChargedPt_den = new TH2F("ChargedPt_den","number of charged daughters versus p_{T}", 30, Nedges, 11, ptedges);
  ChargedPt_den->GetXaxis()->SetTitle("number of charged hadrons");
  ChargedPt_den->GetYaxis()->SetTitle("p_{T}");  
  ChargedPt_den->Sumw2();  
  TH2F*ChargedEta_num = new TH2F("ChargedEta_num","number of charged daughters versus #eta", 30, Nedges, 22, etaExtended);
  ChargedEta_num->GetXaxis()->SetTitle("number of charged hadrons");
  ChargedEta_num->GetYaxis()->SetTitle("#eta");  
  ChargedEta_num->Sumw2();
  TH2F*ChargedEta_den = new TH2F("ChargedEta_den","number of charged daughters versus #eta", 30, Nedges, 22, etaExtended);
  ChargedEta_den->GetXaxis()->SetTitle("number of charged hadrons");
  ChargedEta_den->GetYaxis()->SetTitle("#eta");  
  ChargedEta_den->Sumw2();    
  
  /*TH1F*MetProjFrac_num = new TH1F("MetProjFrac_num","projection of jet pt on met", 60,0,3);
  MetProjFrac_num->GetXaxis()->SetTitle("R_MPF");
  MetProjFrac_num->Sumw2();
  TH1F*MetProjFrac_den = new TH1F("MetProjFrac_den","projection of jet pt on met", 60,0,3);
  MetProjFrac_den->GetXaxis()->SetTitle("R_MPF");
  MetProjFrac_den->Sumw2();  */
  
  TH2F*JetIndex_num=new TH2F("JetIndex_num","jet index vs jet count", 20,0,20,20,0,20);
  JetIndex_num->GetXaxis()->SetTitle("Index_{jet}");
  JetIndex_num->GetYaxis()->SetTitle("N_{jet}");
  JetIndex_num->Sumw2(); 
  TH2F*JetIndex_den=new TH2F("JetIndex_den","jet index vs jet count", 20,0,20,20,0,20);
  JetIndex_den->GetXaxis()->SetTitle("Index_{jet}");
  JetIndex_den->GetYaxis()->SetTitle("N_{jet}");
  JetIndex_den->Sumw2();    
  
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

  TFile file_Pt("/afs/naf.desy.de/user/r/rathjd/public/VBFAnalyzer/ResponseFactors_InclAndExclIsos_Jet30Tau45_15up.root", "read");       

  MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
  MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
  MyEventCollection TauMediumInclIsoObjectSelectionCollection ("TauMediumInclIsoObjectSelection");
  MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
  MyEventCollection TauLooseInclIsoObjectSelectionCollection ("TauLooseInclIsoObjectSelection");
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

          if(!(         vertex.size() > 0                                 )) goodVertex = false;
	  if(goodVertex){
	    if( goodVertex ) {
		TauTightIsoObjectSelectionCollection.goodVertex = true;
		TauMediumIsoObjectSelectionCollection.goodVertex = true;
		TauMediumInclIsoObjectSelectionCollection.goodVertex = true;
		TauLooseIsoObjectSelectionCollection.goodVertex = true;
		TauLooseInclIsoObjectSelectionCollection.goodVertex = true;
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
		 TauMediumInclIsoObjectSelectionCollection.goodVertex = true;
	         TauLooseIsoObjectSelectionCollection.passedTrigger = true;
		 TauLooseInclIsoObjectSelectionCollection.goodVertex = true;
	         TauNoIsoObjectSelectionCollection.passedTrigger = true;
               }

          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA3 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5))  TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)){
	      TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
	    else if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)){
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
	    else{
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauNoIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
          }

          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.7                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}

	  //MET selection
	  TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauMediumInclIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseInclIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// --   Tau Efficency    --
	// ------------------------
	TH1F* ReweightFactorN = (TH1F*)(file_Pt.Get("RescaleWeightN"));
	TH1F* ReweightFactorL = (TH1F*)(file_Pt.Get("RescaleWeightL"));
	TH1F* ReweightFactorLi = (TH1F*)(file_Pt.Get("RescaleWeightLi"));
	TH1F* ReweightFactorM = (TH1F*)(file_Pt.Get("RescaleWeightM"));
	TH1F* ReweightFactorMi = (TH1F*)(file_Pt.Get("RescaleWeightMi"));
	TH1F* ReweightFactorT = (TH1F*)(file_Pt.Get("RescaleWeightT"));
	

	if (JetLooseIsoObjectSelectionCollection.jet.size() >= 2) {
		h1_jet1pt->Fill(JetLooseIsoObjectSelectionCollection.jet[0]->pt);
		h1_jet2pt->Fill(JetLooseIsoObjectSelectionCollection.jet[1]->pt);
	}

	int count=0;
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
		h1_jetpt->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);	
		double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRt = TauJetMinDistanceExtended(TauTightIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRm = TauJetMinDistanceExtended(TauMediumIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRmi = TauJetMinDistanceExtended(TauMediumInclIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRl = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRli = TauJetMinDistanceExtended(TauLooseInclIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRn = TauJetMinDistanceExtended(TauNoIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		int nRescaleBinN= ReweightFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		int nRescaleBinL= ReweightFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		int nRescaleBinLi= ReweightFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		int nRescaleBinM= ReweightFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		int nRescaleBinMi= ReweightFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		int nRescaleBinT= ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		double weightN=ReweightFactorN->GetBinContent(nRescaleBinN);
		double weightL=ReweightFactorL->GetBinContent(nRescaleBinL);
		double weightLi=ReweightFactorLi->GetBinContent(nRescaleBinLi);
		double weightM=ReweightFactorM->GetBinContent(nRescaleBinM);
		double weightMi=ReweightFactorMi->GetBinContent(nRescaleBinMi);
		double weightT=ReweightFactorT->GetBinContent(nRescaleBinT);
		if(jetMindR > 0.5){ //only count isolated jets
		  if( deltaRt.first < 0.1 ){
		 	h2_taufakerate_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
			h1_taufakerate_pt_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weightT);
			h1_taufakerate_jetrank_num->Fill(j,weightT);
			h2_taufakerate_dR_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, deltaRt.first,weightT);
			if (j == 0) h1_taufakerate_ptjet1_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			if (j == 1) h1_taufakerate_ptjet2_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			if (j == 2) h1_taufakerate_ptjet3_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			if (j == 3) h1_taufakerate_ptjet4_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h1_taufakescale_num->Fill(fabs(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->eta), TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h1_taufakescale_den->Fill(fabs(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->eta));
			h1_taufakescale_pt_num->Fill(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h2_tauResponse->Fill(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weightT);
			h1_taufakescale_pt_den->Fill(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt);
			h2_taufakerate_dRjet_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, JetJetMinDistance(JetLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi),weightT);
			h3_tauComplete->Fill(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
			Nod_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->numberOfDaughters,weightT);
			NOD_charge_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,weightT);
			Efrac_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction,weightT);
			Etype_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction,JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction,weightT);
		
			ChargeMapT_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightT);
			ChargedPt_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->pt,weightT);
			ChargedEta_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
			
			//double R_MPF=RMPF(TauTightIsoObjectSelectionCollection.met[0]->pt,TauTightIsoObjectSelectionCollection.met[0]->phi,JetLooseIsoObjectSelectionCollection.jet[j]->pt,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
			//MetProjFrac_num->Fill(R_MPF,weightT);
			
			JetIndex_num->Fill(j,JetLooseIsoObjectSelectionCollection.jet.size(),weightT);
		  }
		  if( deltaRm.first < 0.1 ) ChargeMapM_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightM);
		  if( deltaRmi.first < 0.1 ) ChargeMapMi_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightMi);
		  if( deltaRl.first < 0.1 ) ChargeMapL_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightL);		  
		  if( deltaRli.first < 0.1 ) ChargeMapLi_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightLi);		  
		  if( deltaRn.first < 0.1 ) ChargeMapN_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightN);		  		  
		  pair <double, unsigned int>deltaRloose = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		  if( deltaRl.first < 0.1 ){
			h2_taufakerate_loose_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightL);
			h2_taufakerate_dRl_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,deltaRl.first,weightL);
			h1_taufakescale_loose_num->Fill(TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->eta,TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h1_taufakescale_loose_den->Fill(TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->eta);
			h1_taufakescale_loose_pt_num->Fill(TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt, TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h1_taufakescale_loose_pt_den->Fill(TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt);
			h2_tauResponse_loose->Fill(TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weightL);
			h2_taufakerate_dRjetl_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi),weightL);			
			h3_tauComplete_loose->Fill(TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightL);
			Nod_loose_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->numberOfDaughters,weightL);
			NOD_charge_loose_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,weightL);
		  }
		  h2_taufakerate_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);	
		  h2_taufakerate_dR_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,
		  deltaRt.first,weightT);	
		  h2_taufakerate_dRjet_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,
		  JetJetMinDistance(JetLooseIsoObjectSelectionCollection,
		  JetLooseIsoObjectSelectionCollection.jet[j]->eta,
		  JetLooseIsoObjectSelectionCollection.jet[j]->phi),weightT);
		  ChargedPt_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->pt,weightT);
		  if(fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta)<2.2)
		    {
		      NOD_charge_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,weightT);
		      Nod_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->numberOfDaughters,weightT);
		      Efrac_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction,weightT);
		      Etype_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction,JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction,weightT);
		      ChargeMapN_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightN);
		      ChargeMapL_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightL);
		      ChargeMapLi_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightLi);
		      ChargeMapM_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightM);
		      ChargeMapMi_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightMi);
		      ChargeMapT_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightT);
		      ChargedEta_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
		      JetIndex_den->Fill(j,JetLooseIsoObjectSelectionCollection.jet.size(),weightT);
		      /*if(fabs(JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction-1)>0.01){
		      std::cout<<"jet "<<j<<std::endl;
		      std::cout<<"charged EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction<<std::endl;
		      std::cout<<"neutral EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction<<std::endl;
		      std::cout<<"photon EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->photonEnergyFraction<<std::endl;
		      std::cout<<"muon EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction<<std::endl;
		      std::cout<<"electron EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->electronEnergyFraction<<std::endl;
		      std::cout<<"HF EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction<<std::endl;
		      std::cout<<"charged Had fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction<<std::endl;
		      std::cout<<"neutral Had fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction<<std::endl;
		      std::cout<<"HF Had fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction<<std::endl;
		      }*/
		      //double R_MPF=RMPF(mainObjectSelectionCollection.met[0]->pt,mainObjectSelectionCollection.met[0]->phi,JetLooseIsoObjectSelectionCollection.jet[j]->pt,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		      //MetProjFrac_den->Fill(R_MPF,weight);
		    }
		  count++;
		}
		h1_taufakerate_pt_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weightT);
		h1_taufakerate_jetrank_den->Fill(j,weightT);
		h2_taufakerate_dR_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, deltaRt.first,weightT);	
		h2_taufakerate_dRjet_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi),weightT);
		if (j == 0) h1_taufakerate_ptjet1_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		if (j == 1) h1_taufakerate_ptjet2_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		if (j == 2) h1_taufakerate_ptjet3_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		if (j == 3) h1_taufakerate_ptjet4_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
	}
	
	NjetNtau->Fill(count,TauTightIsoObjectSelectionCollection.tau.size());
	NjetNtauLoose->Fill(count,TauLooseIsoObjectSelectionCollection.tau.size());
	
	//Clearing Object Collections 
	TauTightIsoObjectSelectionCollection.clear();
	TauMediumIsoObjectSelectionCollection.clear();
	TauMediumInclIsoObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();
	TauLooseInclIsoObjectSelectionCollection.clear();
	TauNoIsoObjectSelectionCollection.clear();
	JetLooseIsoObjectSelectionCollection.clear();
	}

  stream.close();
  ofile.close();
  return 0;
}

