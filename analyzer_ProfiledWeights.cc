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

  //TH1F* h_mindeltaR = new TH1F("h_mindeltaR", "h_mindeltaR", 50,0. , 3.);

  double ptedges[21]={22.5,23.7,25.,26.5,28.1,30.,32.1,34.6,37.5,40.9,45.,50.,56.3,64.3,75.,90.,112.5,150.,225.,450.,2500.};

  TProfile *RescaleWeightN=new TProfile("RescaleWeightN", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightN->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightN->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightN->Sumw2();
  TProfile *RescaleWeightL=new TProfile("RescaleWeightL", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightL->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightL->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightL->Sumw2();  
  TProfile *RescaleWeightLi=new TProfile("RescaleWeightLi", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightLi->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightLi->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightLi->Sumw2();
  TProfile *RescaleWeightM=new TProfile("RescaleWeightM", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightM->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightM->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightM->Sumw2();
  TProfile *RescaleWeightMi=new TProfile("RescaleWeightMi", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightMi->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightMi->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightMi->Sumw2();
  TProfile *RescaleWeightT=new TProfile("RescaleWeightT", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightT->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightT->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightT->Sumw2();
  
  TProfile *ScaleFactorN=new TProfile("ScaleFactorN", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorN->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorN->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  ScaleFactorN->Sumw2();
  TProfile *ScaleFactorL=new TProfile("ScaleFactorL", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorL->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorL->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  ScaleFactorL->Sumw2();  
  TProfile *ScaleFactorLi=new TProfile("ScaleFactorLi", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorLi->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorLi->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  ScaleFactorLi->Sumw2();
  TProfile *ScaleFactorM=new TProfile("ScaleFactorM", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorM->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorM->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  ScaleFactorM->Sumw2();
  TProfile *ScaleFactorMi=new TProfile("ScaleFactorMi", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorMi->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorMi->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  ScaleFactorMi->Sumw2();
  TProfile *ScaleFactorT=new TProfile("ScaleFactorT", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorT->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorT->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  ScaleFactorT->Sumw2();  
    
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
            //if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA5 > 0.5                				)) continue;
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

          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.7                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}

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
		if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta) <=2.1){ //only count isolated jets
		  if( deltaRt.first < 0.3 ){
		    if(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt>=45){
		      RescaleWeightT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    }
		    else RescaleWeightT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		  }	
		  if( deltaRm.first < 0.3 ){
		    if(TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt>=45){
		      RescaleWeightM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);		      
		    }
		    else{
		      RescaleWeightM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		    }
		  }		  
		  if( deltaRl.first < 0.3 ){
		    if(TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt>=45){
		      RescaleWeightL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);		      
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);		      		      
		    }
		    else{
		      RescaleWeightL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		    }
		  }
		  if( deltaRn.first < 0.3 ){
		    if(TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt>=45){
		      RescaleWeightN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);		      
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      ScaleFactorLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt/JetLooseIsoObjectSelectionCollection.jet[j]->pt);		      		      
		    }
		    else{
		      RescaleWeightN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0);
		    }
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

