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

  //TH1F* h_mindeltaR = new TH1F("h_mindeltaR", "h_mindeltaR", 50,0. , 3.);

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
  
  TH3F* h3_tauCompleteN = new TH3F("h3_tauCompleteN","NoIso #tau response", 11, ptedges, 28, respEdges, 4, etaedges); 
  h3_tauCompleteN->GetXaxis()->SetTitle("p_{T}^{jet}");
  h3_tauCompleteN->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h3_tauCompleteN->GetZaxis()->SetTitle("|#eta|");
  h3_tauCompleteN->Sumw2();
  
  TH3F* h3_tauCompleteL = new TH3F("h3_tauCompleteL","LooseIso #tau response", 11, ptedges, 28, respEdges, 4, etaedges); 
  h3_tauCompleteL->GetXaxis()->SetTitle("p_{T}^{jet}");
  h3_tauCompleteL->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h3_tauCompleteL->GetZaxis()->SetTitle("|#eta|");
  h3_tauCompleteL->Sumw2();  
  
  TH3F* h3_tauCompleteM = new TH3F("h3_tauCompleteM","MediumIso #tau response", 11, ptedges, 28, respEdges, 4, etaedges); 
  h3_tauCompleteM->GetXaxis()->SetTitle("p_{T}^{jet}");
  h3_tauCompleteM->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h3_tauCompleteM->GetZaxis()->SetTitle("|#eta|");
  h3_tauCompleteM->Sumw2();
  
  TH3F* h3_tauCompleteT = new TH3F("h3_tauCompleteT","LooseIso #tau response", 11, ptedges, 28, respEdges, 4, etaedges); 
  h3_tauCompleteT->GetXaxis()->SetTitle("p_{T}^{jet}");
  h3_tauCompleteT->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h3_tauCompleteT->GetZaxis()->SetTitle("|#eta|");
  h3_tauCompleteT->Sumw2();  
  
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
 
    
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

        

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

          if(!(         vertex.size() > 0                                 )) goodVertex = false;
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
	  
	  if(tight>=2)
	    {
	      h2_tauNumberByIDtight->Fill(3.,tight-2);
	      h2_tauNumberByIDtight->Fill(2.,medium);
	      h2_tauNumberByIDtight->Fill(1.,loose);
	      h2_tauNumberByIDtight->Fill(0.,NoIso); 
	      h2_tauNumberByIDtight->Fill(4.,NoIso+loose+medium+tight-2);
	    }
	  if(tight>=1)
	    {
	      h2_tauNumberByID1tight->Fill(3.,tight-1);
	      h2_tauNumberByID1tight->Fill(2.,medium);
	      h2_tauNumberByID1tight->Fill(1.,loose);
	      h2_tauNumberByID1tight->Fill(0.,NoIso); 
	      h2_tauNumberByID1tight->Fill(4.,NoIso+loose+medium+tight-2);
	    }	  
	  if(medium>=1)
	    {
	      h2_tauNumberByIDmedium->Fill(3.,tight);
	      h2_tauNumberByIDmedium->Fill(2.,medium-1);
	      h2_tauNumberByIDmedium->Fill(1.,loose);
	      h2_tauNumberByIDmedium->Fill(0.,NoIso); 
	      h2_tauNumberByIDmedium->Fill(4.,NoIso+loose+medium+tight-2);
	    }
	  if(loose>=1)
	    {
	      h2_tauNumberByIDloose->Fill(3.,tight);
	      h2_tauNumberByIDloose->Fill(2.,medium);
	      h2_tauNumberByIDloose->Fill(1.,loose-1);
	      h2_tauNumberByIDloose->Fill(0.,NoIso);
	      h2_tauNumberByIDloose->Fill(4.,NoIso+loose+medium+tight-2); 
	    } 
	  if(NoIso>=1)
	    {
	      h2_tauNumberByIDN->Fill(3.,tight);
	      h2_tauNumberByIDN->Fill(2.,medium);
	      h2_tauNumberByIDN->Fill(1.,loose);
	      h2_tauNumberByIDN->Fill(0.,NoIso-1); 
	      h2_tauNumberByIDN->Fill(4.,NoIso+loose+medium+tight-2);
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
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// --   Tau Efficency    --
	// ------------------------

	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){	
		double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRt = TauJetMinDistanceExtended(TauTightIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRm = TauJetMinDistanceExtended(TauMediumIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRl = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRn = TauJetMinDistanceExtended(TauNoIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		if(jetMindR > 0.5){ //only count isolated jets
		  if( deltaRt.first < 0.1 ){
			h2_tauResponseT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h3_tauCompleteT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta));
		  }	
		  if( deltaRm.first < 0.1 ){
			h2_tauResponseM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h3_tauCompleteM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta));
		  }		  
		  if( deltaRl.first < 0.1 ){
			h2_tauResponseL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h3_tauCompleteL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta));
		  }
		  if( deltaRn.first < 0.1 ){
			h2_tauResponseN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h3_tauCompleteN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta));
		  }		  
		}
	}
	
	//Clearing Object Collections 
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

