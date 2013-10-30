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
#include "analyzer.h"
#endif

#include "CommonHistoCollection.h"
#include "selection.h"


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

  //int nevents = 10000;
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

  TH1F* h_gentaupt;
  TH1F* h_matchgentaupt;

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

  h_gentaupt = new TH1F("h_gentaupt", "h_gentaupt", 50, 0., 500.);
  h_matchgentaupt = new TH1F("h_matchgentaupt", "h_matchgentaupt", 50, 0., 500.);
  h_tauIsoTight = new TH1F("h_tauIsoTight", "tight tau ID discriminant", 100, 0., 1.);
  h_tauIsoMedium = new TH1F("h_tauIsoMedium", "medium tau ID discriminant", 100, 0., 1.);
  h_tauIsoLoose = new TH1F("h_tauIsoLoose", "loose tau ID discriminant", 100, 0., 1.);

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------

  double weight = 1.;

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
	  //Event Count
	  ofile.count("NoCuts");

	  // ------------------------
	  // -- Genlevel Studies   --
	  // ------------------------

	  std::vector<genparticlehelper_s*> genTau;

	  while (true) {

	
		for (unsigned int g = 0; g < genparticlehelper.size(); g++){
		  if (  !(fabs(genparticlehelper[g].status)==3)  ) continue;
		  if (fabs(genparticlehelper[g].pdgId) == 15) genTau.push_back(&genparticlehelper[g]);
		}

		for (unsigned int i = 0; i < genTau.size(); i++) {
		  h_gentaupt->Fill(genTau[i]->pt,weight);
		  for (unsigned int j = 0; j < tau.size(); j++) {
			
			TLorentzVector gentau_4v;
			TLorentzVector recotau_4v;

		  	gentau_4v.SetPtEtaPhiM(genTau[i]->pt, genTau[i]->eta, genTau[i]->phi, genTau[i]->mass);
			recotau_4v.SetPtEtaPhiE(tau[j].pt, tau[j].eta, tau[j].phi, tau[j].energy);
		    
			double deltaR = gentau_4v.DeltaR(recotau_4v);
		
			if (deltaR < 0.3){
				h_matchgentaupt->Fill(genTau[i]->pt,weight);
				h_tauIsoTight->Fill(tau[j].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits);
				h_tauIsoMedium->Fill(tau[j].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits);
				h_tauIsoLoose->Fill(tau[j].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits);
			}

		  }

		}

		break;

	  }



}
  stream.close();
  ofile.close();
  return 0;
}

