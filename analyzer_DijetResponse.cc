//-----------------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for ntuples created by TheNtupleMaker
// Created:     Fri Apr  5 13:23:28 2013 by mkntanalyzer.py
// Author:      Daniele Marconi
//-----------------------------------------------------------------------------

#ifdef PROJECT_NAME
#include "PhysicsTools/TheNtupleMaker/interface/pdg.h"
#else
#include "pdg.h"
#endif

#include "CommonHistoCollection.h"
#include "selection.h"
#include "TVector2.h"

// Structs useful for Analyzer



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
  ofile.count("DualEntry",0.);
  ofile.count("DiJetTrigger",0.); 
  ofile.count("DeltaPhiCut",0.);   
  ofile.count("AlphaCut",0.);

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------

  TH2F* h2_Trigger = new TH2F("h2_Trigger", "Triggered in CRs", 2, -0.5, 1.5, 10, 0.5, 10.5);
  h2_Trigger->GetXaxis()->SetTitle("triggered");
  h2_Trigger->GetYaxis()->SetTitle("CR");
  h2_Trigger->Sumw2();
  
  double etaedges[5]={0.,1.4,1.6,2.,2.2};
  double ptedges[12]={0.,30.,45.,55.,75.,100.,250.,400.,600.,900.,1500.,2500.};
  double respEdges[29]={0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,1.50};

  TH2F* h2_tauResponseN = new TH2F("h2_tauResponseN", "NoIso #tau response", 11, ptedges, 60, 0, 3);
  TH2F* h2_tauResponseL = new TH2F("h2_tauResponseL", "LooseIso #tau response", 11, ptedges, 60, 0, 3);
  TH2F* h2_tauResponseM = new TH2F("h2_tauResponseM", "MediumIso #tau response", 11, ptedges, 60, 0, 3);
  TH2F* h2_tauResponseT = new TH2F("h2_tauResponseT", "TightIso #tau response", 11, ptedges, 60, 0, 3); 
  h2_tauResponseN->Sumw2();
  h2_tauResponseL->Sumw2();  
  h2_tauResponseM->Sumw2();
  h2_tauResponseT->Sumw2();
  h2_tauResponseN->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_tauResponseN->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h2_tauResponseL->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_tauResponseL->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h2_tauResponseM->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_tauResponseM->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h2_tauResponseT->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_tauResponseT->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  
  TH2F* h2_tauNumberByIDtight = new TH2F("h2_tauNumberByIDtight", "2 tight #tau ID + N occurence", 5, -0.5, 4.5, 21, -0.5, 20.5);
  h2_tauNumberByIDtight->GetXaxis()->SetTitle("exclusive ID_{#tau}");
  h2_tauNumberByIDtight->GetYaxis()->SetTitle("N_{#tau} per ID in collection");
  h2_tauNumberByIDtight->Sumw2();
  
  TH2F* h2_tauNumberByID1tight = new TH2F("h2_tauNumberByID1tight", "1 tight #tau ID + N occurence", 5, -0.5, 4.5, 21, -0.5, 20.5);
  h2_tauNumberByID1tight->GetXaxis()->SetTitle("exclusive ID_{#tau}");
  h2_tauNumberByID1tight->GetYaxis()->SetTitle("N_{#tau} per ID in collection");
  h2_tauNumberByID1tight->Sumw2();  
  
  TH2F* h2_tauNumberByIDmedium = new TH2F("h2_tauNumberByIDmedium", "1 medium #tau ID + N occurence", 5, -0.5, 4.5, 21, -0.5, 20.5);
  h2_tauNumberByIDmedium->GetXaxis()->SetTitle("exclusive ID_{#tau}");
  h2_tauNumberByIDmedium->GetYaxis()->SetTitle("N_{#tau} per ID in collection");
  h2_tauNumberByIDmedium->Sumw2();
  
  TH2F* h2_tauNumberByIDloose = new TH2F("h2_tauNumberByIDloose", "1 loose #tau ID + N occurence", 5, -0.5, 4.5, 21, -0.5, 20.5);
  h2_tauNumberByIDloose->GetXaxis()->SetTitle("exclusive ID_{#tau}");
  h2_tauNumberByIDloose->GetYaxis()->SetTitle("N_{#tau} per ID in collection");
  h2_tauNumberByIDloose->Sumw2(); 
  
  TH2F* h2_tauNumberByIDN = new TH2F("h2_tauNumberByIDN", "1 NoIso #tau ID + N occurence", 5, -0.5, 4.5, 21, -0.5, 20.5);
  h2_tauNumberByIDN->GetXaxis()->SetTitle("exclusive ID_{#tau}");
  h2_tauNumberByIDN->GetYaxis()->SetTitle("N_{#tau} per ID in collection");
  h2_tauNumberByIDN->Sumw2();  
  
  TH1F* h1_TriggerNoIso = new TH1F("h1_TriggerNoIso", "Triggered NN", 11, ptedges);
  h1_TriggerNoIso->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_TriggerNoIso->Sumw2();
  
  TH1F* h1_TriggerLoose = new TH1F("h1_TriggerLoose", "Triggered LN/LL", 11, ptedges);
  h1_TriggerLoose->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_TriggerLoose->Sumw2();
  
  TH1F* h1_TriggerMedium = new TH1F("h1_TriggerMedium", "Triggered MM/ML/MN", 11, ptedges);
  h1_TriggerMedium->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_TriggerMedium->Sumw2();
  
  TH1F* h1_Trigger1Tight = new TH1F("h1_Trigger1Tight", "Triggered TM/TL/TN", 11, ptedges);
  h1_Trigger1Tight->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_Trigger1Tight->Sumw2();
  
  TH1F* h1_Trigger2Tight = new TH1F("h1_Trigger2Tight", "Triggered TT", 11, ptedges);
  h1_Trigger2Tight->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_Trigger2Tight->Sumw2();
  
  TH1F* h1_NoTriggerNoIso = new TH1F("h1_NoTriggerNoIso", "NoTriggered NN", 11, ptedges);
  h1_NoTriggerNoIso->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_NoTriggerNoIso->Sumw2();
  
  TH1F* h1_NoTriggerLoose = new TH1F("h1_NoTriggerLoose", "NoTriggered LN/LL", 11, ptedges);
  h1_NoTriggerLoose->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_NoTriggerLoose->Sumw2();
  
  TH1F* h1_NoTriggerMedium = new TH1F("h1_NoTriggerMedium", "NoTriggered MM/ML/MN", 11, ptedges);
  h1_NoTriggerMedium->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_NoTriggerMedium->Sumw2();
  
  TH1F* h1_NoTrigger1Tight = new TH1F("h1_NoTrigger1Tight", "NoTriggered TM/TL/TN", 11, ptedges);
  h1_NoTrigger1Tight->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_NoTrigger1Tight->Sumw2();
  
  TH1F* h1_NoTrigger2Tight = new TH1F("h1_NoTrigger2Tight", "NoTriggered TT", 11, ptedges);
  h1_NoTrigger2Tight->GetXaxis()->SetTitle("p_{T}^{jet}");
  h1_NoTrigger2Tight->Sumw2();
  
  TH1F* h1_dphi = new TH1F("h1_dphi", "#Delta#phi", 65, -3.2, 3.2);
  h1_dphi->GetXaxis()->SetTitle("#Delta#phi");
  h1_dphi->Sumw2();
  
  TH2F* h2_phi = new TH2F("h2_phi", "#phi vs N_{jet}", 65, -3.2, 3.2, 21, -0.5, 20.5);
  h2_phi->GetXaxis()->SetTitle("#phi");
  h2_phi->GetXaxis()->SetTitle("N_{jet}");
  h2_phi->Sumw2();
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------
	double weight=1.;
	MyEventCollection DijetObjectSelectionCollection ("DijetObjectSelection");
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
if( goodVertex ) {
	TauTightIsoObjectSelectionCollection.goodVertex = true;
	TauMediumIsoObjectSelectionCollection.goodVertex = true;
	TauLooseIsoObjectSelectionCollection.goodVertex = true;
	TauNoIsoObjectSelectionCollection.goodVertex = true;
}//std::cout<<DijetObjectSelectionCollection.jet.size()<<std::endl;
	ofile.count("NoCuts");
          //dijet trigger selection
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.         )) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 5.0  )) continue;   
	    bool jetid=true;
	    if(!(      (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99      )) jetid=false;
	    if(!(      jet[j].neutralEmEnergyFraction < 0.99                                            )) jetid=false;
	    if(!(      jet[j].numberOfDaughters > 1                                                     )) jetid=false;
	    if(fabs(jet[j].eta) < 2.4) {
              if(!(      jet[j].chargedHadronEnergyFraction > 0                        			)) jetid=false;
              if(!(      jet[j].chargedEmEnergyFraction < 0.99                            		)) jetid=false;
              if(!(      jet[j].chargedHadronMultiplicity > 0                             		)) jetid=false;
            }
	  //if(JetJetMinDistance(DijetObjectSelectionCollection,jet[j].eta,jet[j].phi)<0.5) {if(DijetObjectSelectionCollection.jet.size()==1) ofile.count("DualEntry");continue;}
	  if(jetid) DijetObjectSelectionCollection.jet.push_back(&jet[j]);
	  //std::cout<<DijetObjectSelectionCollection.jet.size()<<std::endl;
	  }
	  
	  bool TwoJets=true;
	  for(int j=0; j<DijetObjectSelectionCollection.jet.size(); j++)h2_phi->Fill(DijetObjectSelectionCollection.jet[j]->phi, j);
	  double ptave = 0.;
	  if(DijetObjectSelectionCollection.jet.size()>=2) ptave=(DijetObjectSelectionCollection.jet[0]->pt+DijetObjectSelectionCollection.jet[1]->pt)/2;
	  else TwoJets=false;
          if(((triggerresultshelper_value_HLT_DiPFJetAve40_v1 == 1) ||
             (triggerresultshelper_value_HLT_DiPFJetAve40_v2 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve40_v3 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve40_v4 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v5 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v6 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v7 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v8 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v9 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v10 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v11 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v12 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v13 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v14 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v15 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v16 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v17 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v18 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v19 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve40_v20 == 1))&&
	     ptave>60){
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v1>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v1;
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v2>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v2;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v3>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v3;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v4>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v4;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v5>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v5;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v6>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v6;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v7>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v7;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v8>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v8;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v9>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v9;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v10>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v10;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v11>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v11;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v12>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v12;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v13>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v13;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v14>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v14;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v15>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v15;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v16>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v16;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v17>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v17;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v18>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v18;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v19>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v19;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve40_v20>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve40_v20;	     
	     	DijetObjectSelectionCollection.passedTrigger = true;
	        TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	        TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	        TauNoIsoObjectSelectionCollection.passedTrigger = true;
	     }
          if(((triggerresultshelper_value_HLT_DiPFJetAve80_v1 == 1) ||
             (triggerresultshelper_value_HLT_DiPFJetAve80_v2 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve80_v3 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve80_v4 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v5 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v6 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v7 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v8 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v9 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v10 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v11 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v12 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v13 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v14 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v15 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v16 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v17 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v18 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v19 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve80_v20 == 1))&&
	     ptave>105){
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v1>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v1;
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v2>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v2;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v3>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v3;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v4>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v4;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v5>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v5;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v6>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v6;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v7>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v7;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v8>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v8;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v9>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v9;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v10>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v10;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v11>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v11;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v12>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v12;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v13>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v13;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v14>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v14;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v15>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v15;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v16>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v16;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v17>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v17;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v18>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v18;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v19>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v19;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve80_v20>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve80_v20;	     
	     	DijetObjectSelectionCollection.passedTrigger = true;
	        TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	        TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	        TauNoIsoObjectSelectionCollection.passedTrigger = true;
	     }	     
          if(((triggerresultshelper_value_HLT_DiPFJetAve140_v1 == 1) ||
             (triggerresultshelper_value_HLT_DiPFJetAve140_v2 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve140_v3 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve140_v4 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v5 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v6 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v7 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v8 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v9 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v10 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v11 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v12 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v13 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v14 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v15 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v16 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v17 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v18 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v19 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve140_v20 == 1))&&
	     ptave>174){
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v1>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v1;
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v2>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v2;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v3>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v3;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v4>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v4;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v5>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v5;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v6>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v6;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v7>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v7;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v8>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v8;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v9>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v9;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v10>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v10;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v11>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v11;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v12>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v12;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v13>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v13;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v14>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v14;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v15>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v15;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v16>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v16;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v17>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v17;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v18>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v18;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v19>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v19;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve140_v20>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve140_v20;	     
	     	DijetObjectSelectionCollection.passedTrigger = true;
	        TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	        TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	        TauNoIsoObjectSelectionCollection.passedTrigger = true;
	     }	     	     
          if(((triggerresultshelper_value_HLT_DiPFJetAve200_v1 == 1) ||
             (triggerresultshelper_value_HLT_DiPFJetAve200_v2 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve200_v3 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve200_v4 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v5 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v6 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v7 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v8 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v9 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v10 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v11 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v12 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v13 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v14 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v15 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v16 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v17 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v18 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v19 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve200_v20 == 1))&&
	     ptave>242){
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v1>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v1;
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v2>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v2;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v3>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v3;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v4>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v4;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v5>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v5;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v6>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v6;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v7>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v7;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v8>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v8;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v9>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v9;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v10>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v10;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v11>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v11;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v12>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v12;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v13>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v13;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v14>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v14;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v15>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v15;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v16>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v16;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v17>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v17;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v18>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v18;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v19>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v19;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve200_v20>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve200_v20;	     
	     	DijetObjectSelectionCollection.passedTrigger = true;
	        TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	        TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	        TauNoIsoObjectSelectionCollection.passedTrigger = true;
	     }	     
          if(((triggerresultshelper_value_HLT_DiPFJetAve260_v1 == 1) ||
             (triggerresultshelper_value_HLT_DiPFJetAve260_v2 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve260_v3 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve260_v4 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v5 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v6 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v7 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v8 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v9 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v10 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v11 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v12 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v13 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v14 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v15 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v16 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v17 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v18 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v19 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve260_v20 == 1))&&
	     ptave>311){
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v1>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v1;
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v2>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v2;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v3>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v3;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v4>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v4;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v5>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v5;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v6>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v6;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v7>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v7;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v8>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v8;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v9>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v9;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v10>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v10;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v11>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v11;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v12>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v12;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v13>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v13;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v14>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v14;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v15>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v15;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v16>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v16;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v17>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v17;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v18>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v18;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v19>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v19;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve260_v20>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve260_v20;	     
	     	DijetObjectSelectionCollection.passedTrigger = true;
	        TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	        TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	        TauNoIsoObjectSelectionCollection.passedTrigger = true;
	     }   
          if(((triggerresultshelper_value_HLT_DiPFJetAve320_v1 == 1) ||
             (triggerresultshelper_value_HLT_DiPFJetAve320_v2 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve320_v3 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve320_v4 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v5 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v6 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v7 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v8 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v9 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v10 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v11 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v12 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v13 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v14 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v15 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v16 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v17 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v18 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v19 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve320_v20 == 1))&&
	     ptave>380){
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v1>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v1;
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v2>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v2;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v3>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v3;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v4>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v4;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v5>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v5;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v6>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v6;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v7>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v7;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v8>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v8;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v9>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v9;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v10>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v10;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v11>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v11;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v12>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v12;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v13>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v13;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v14>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v14;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v15>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v15;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v16>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v16;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v17>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v17;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v18>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v18;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v19>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v19;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve320_v20>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve320_v20;	     
	     	DijetObjectSelectionCollection.passedTrigger = true;
	        TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	        TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	        TauNoIsoObjectSelectionCollection.passedTrigger = true;
	     }
          if(((triggerresultshelper_value_HLT_DiPFJetAve400_v1 == 1) ||
             (triggerresultshelper_value_HLT_DiPFJetAve400_v2 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve400_v3 == 1) ||	     
             (triggerresultshelper_value_HLT_DiPFJetAve400_v4 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v5 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v6 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v7 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v8 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v9 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v10 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v11 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v12 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v13 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v14 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v15 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v16 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v17 == 1) ||	     
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v18 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v19 == 1) ||
	     (triggerresultshelper_value_HLT_DiPFJetAve400_v20 == 1))&&
	     ptave>486){
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v1>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v1;
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v2>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v2;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v3>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v3;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v4>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v4;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v5>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v5;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v6>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v6;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v7>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v7;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v8>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v8;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v9>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v9;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v10>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v10;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v11>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v11;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v12>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v12;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v13>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v13;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v14>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v14;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v15>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v15;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v16>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v16;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v17>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v17;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v18>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v18;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v19>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v19;	     
	     if(triggerresultshelper_prescale_HLT_DiPFJetAve400_v20>0) weight=triggerresultshelper_prescale_HLT_DiPFJetAve400_v20;	     
	     	DijetObjectSelectionCollection.passedTrigger = true;
	        TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	        TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	        TauNoIsoObjectSelectionCollection.passedTrigger = true;
	     }
	     if(DijetObjectSelectionCollection.passedTrigger) ofile.count("DiJetTrigger");  
	      bool TauTrigger=false;
	      if(triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1 ||
	      	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1 ||
	      	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1 ||
	      	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1 ||
	      	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1 ||
	      	triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1) TauTrigger=true;

	//perform rough dijet selection to ensure it is really QCD!
	bool passDijet=false;
	if(TwoJets && DijetObjectSelectionCollection.passedTrigger)
	  {
	    if(fabs(TVector2::Phi_mpi_pi(DijetObjectSelectionCollection.jet[0]->phi-DijetObjectSelectionCollection.jet[1]->phi))>=2.7) passDijet=true;
	    //std::cout<<DijetObjectSelectionCollection.jet[0]->phi<<" - "<<DijetObjectSelectionCollection.jet[1]->phi<<" = "<<TVector2::Phi_mpi_pi(DijetObjectSelectionCollection.jet[0]->phi-DijetObjectSelectionCollection.jet[1]->phi)<<" is "<<passDijet<<std::endl;
	    if(passDijet) ofile.count("DeltaPhiCut");  
	    h1_dphi->Fill(TVector2::Phi_mpi_pi(DijetObjectSelectionCollection.jet[0]->phi-DijetObjectSelectionCollection.jet[1]->phi), weight);
	    if(DijetObjectSelectionCollection.jet.size()>=3){
	      if(passDijet &&  ptave>0.4*DijetObjectSelectionCollection.jet[2]->pt) passDijet=true;
	      else passDijet=false;
	    }
	   if(passDijet) ofile.count("AlphaCut");   
	  }

	//if(!passDijet) continue;
	  double tight =0;
	  double medium=0;
	  double loose =0;
	  double NoIso =0;

          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA3 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5))  TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5))  TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else TauNoIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    //section for exclusive tau ID plot
	    if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) tight++;
	    else if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) medium++;
	    else if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) loose++;
	    else NoIso++;
          }
	  if(passDijet){
	  if(tight>=2)
	    {
	      h2_tauNumberByIDtight->Fill(3.,tight-2,weight);
	      h2_tauNumberByIDtight->Fill(2.,medium,weight);
	      h2_tauNumberByIDtight->Fill(1.,loose,weight);
	      h2_tauNumberByIDtight->Fill(0.,NoIso,weight); 
	      h2_tauNumberByIDtight->Fill(4.,NoIso+loose+medium+tight-2,weight);
	    }
	  if(tight>=1)
	    {
	      h2_tauNumberByID1tight->Fill(3.,tight-1,weight);
	      h2_tauNumberByID1tight->Fill(2.,medium,weight);
	      h2_tauNumberByID1tight->Fill(1.,loose,weight);
	      h2_tauNumberByID1tight->Fill(0.,NoIso,weight); 
	      h2_tauNumberByID1tight->Fill(4.,NoIso+loose+medium+tight-2,weight);
	    }	  
	  if(medium>=1)
	    {
	      h2_tauNumberByIDmedium->Fill(3.,tight,weight);
	      h2_tauNumberByIDmedium->Fill(2.,medium-1,weight);
	      h2_tauNumberByIDmedium->Fill(1.,loose,weight);
	      h2_tauNumberByIDmedium->Fill(0.,NoIso,weight); 
	      h2_tauNumberByIDmedium->Fill(4.,NoIso+loose+medium+tight-2,weight);
	    }
	  if(loose>=1)
	    {
	      h2_tauNumberByIDloose->Fill(3.,tight,weight);
	      h2_tauNumberByIDloose->Fill(2.,medium,weight);
	      h2_tauNumberByIDloose->Fill(1.,loose-1,weight);
	      h2_tauNumberByIDloose->Fill(0.,NoIso,weight);
	      h2_tauNumberByIDloose->Fill(4.,NoIso+loose+medium+tight-2,weight); 
	    } 
	  if(NoIso>=1)
	    {
	      h2_tauNumberByIDN->Fill(3.,tight,weight);
	      h2_tauNumberByIDN->Fill(2.,medium,weight);
	      h2_tauNumberByIDN->Fill(1.,loose,weight);
	      h2_tauNumberByIDN->Fill(0.,NoIso-1,weight); 
	      h2_tauNumberByIDN->Fill(4.,NoIso+loose+medium+tight-2,weight);
	    } 
	}
          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.7                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}



	// ------------------------
	// --   Tau Response   --
	// ------------------------

	if(passDijet)for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){	
		double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRt = TauJetMinDistanceExtended(TauTightIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRm = TauJetMinDistanceExtended(TauMediumIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRl = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRn = TauJetMinDistanceExtended(TauNoIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		if(jetMindR > 0.5){ //only count isolated jets
		  if( deltaRt.first < 0.1 ){
			h2_tauResponseT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }	
		  if( deltaRm.first < 0.1 ){
			h2_tauResponseM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }		  
		  if( deltaRl.first < 0.1 ){
			h2_tauResponseL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }
		  if( deltaRn.first < 0.1 ){
			h2_tauResponseN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }
		  if(tight==2 && (medium+loose+NoIso)==0 &&  deltaRt.first < 0.1 ){
	      	    if(TauTrigger) h1_Trigger2Tight->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		    else h1_NoTrigger2Tight->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
	    	  }	
		  else if(tight==1 && (medium+loose+NoIso)==1 &&  (deltaRt.first < 0.1  || deltaRm.first < 0.1 || deltaRl.first < 0.1 || deltaRn.first < 0.1)){	
		    if(TauTrigger) h1_Trigger1Tight->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		    else h1_NoTrigger1Tight->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }  
		  else if(tight==0 && medium>=1 && (medium+loose+NoIso)==2){
		    if(TauTrigger) h1_TriggerMedium->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		    else h1_NoTriggerMedium->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }
		  else if((tight+medium)==0 && loose>=1 && (loose+NoIso)==2){
		    if(TauTrigger) h1_TriggerLoose->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		    else h1_NoTriggerLoose->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }
		  else if((tight+medium+loose)==0 && NoIso==2){
		    if(TauTrigger) h1_TriggerNoIso->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		    else h1_NoTriggerNoIso->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		  }
		}
	}

	//Clearing Object Collections
	DijetObjectSelectionCollection.clear();
	TauTightIsoObjectSelectionCollection.clear();
	TauMediumIsoObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();
	TauNoIsoObjectSelectionCollection.clear();
	JetLooseIsoObjectSelectionCollection.clear();
}
  stream.close();
  ofile.close();
  return 0;
}

