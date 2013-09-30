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

  
  TH2F* h2_tauResponse_loose = new TH2F("h2_tauResponse_loose", "h2_tauResponse_loose", 11, ptedges, 60, 0, 3);
  TH2F* h2_tauResponse = new TH2F("h2_tauResponse", "h2_tauResponse", 11, ptedges, 60, 0, 3);  
  h2_tauResponse_loose->Sumw2();
  h2_tauResponse->Sumw2();  
  h2_tauResponse->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_tauResponse->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  h2_tauResponse_loose->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_tauResponse_loose->GetYaxis()->SetTitle("p_{T}^{#tau}/p_{T}^{jet}");
  
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
  
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

        

	MyEventCollection mainObjectSelectionCollection ("mainObjectSelection");
	MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
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
		mainObjectSelectionCollection.goodVertex = true;
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

             ) { mainObjectSelectionCollection.passedTrigger = true;
               }

          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA3 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) mainObjectSelectionCollection.tau.push_back(&tau[t]);
	    if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
          }

          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.7                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}

	  //MET selection
	  mainObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// --   Tau Efficency    --
	// ------------------------

	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){	
		double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaR = TauJetMinDistanceExtended(mainObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		if(jetMindR > 0.5){ //only count isolated jets
		  if( deltaR.first < 0.1 ){
			h2_tauResponse->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, mainObjectSelectionCollection.tau[deltaR.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h3_tauComplete->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, mainObjectSelectionCollection.tau[deltaR.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta));
		  }	
		  pair <double, unsigned int>deltaRloose = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		  if( deltaRloose.first < 0.1 ){
			h2_tauResponse_loose->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			h3_tauComplete_loose->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRloose.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta));
		  }
		}
	}
	
	//Clearing Object Collections 
	mainObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();
	JetLooseIsoObjectSelectionCollection.clear();
	}

  stream.close();
  ofile.close();
  return 0;
}

