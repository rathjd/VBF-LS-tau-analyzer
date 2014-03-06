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
ofile.count("ElectronVeto",0.);
ofile.count("MuonVeto",0.);
ofile.count("DecayMode",0.);
ofile.count("ChargeHadrCandPt",0.);
ofile.count("LooseIso",0.);
ofile.count("MediumIso",0.);
ofile.count("TightIso",0.);
ofile.count("EtaCut",0.);
ofile.count("PtCut",0.);
ofile.count("1TauPlusNoCuts",0.);
ofile.count("1TauPlusElectronVeto",0.);
ofile.count("1TauPlusMuonVeto",0.);
ofile.count("1TauPlusDecayMode",0.);
ofile.count("1TauPlusChargeHadrCandPt",0.);
ofile.count("1TauPlusLooseIso",0.);
ofile.count("1TauPlusMediumIso",0.);
ofile.count("1TauPlusTightIso",0.);
ofile.count("1TauPlusEtaCut",0.);
ofile.count("1TauPlusPtCut",0.);
	

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

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
	
	

	  // ------------------------
	  // -- Tau ID CUtFlow     --
	  // ------------------------

		int ntauid = 0;

		for(unsigned int t =0;t<tau.size();++t){

	  		ofile.count("NoCuts",weight);
			if (ntauid == 1) ofile.count("1TauPlusNoCuts",weight);

			if (ntauid == 1) {
			
				if(!( tau[t].tauID_againstElectronTightMVA5 > 0.5                                 )) continue;
				ofile.count("1TauPlusElectronVeto",weight);
				if(!( tau[t].tauID_againstMuonTight2 > 0.5                                 )) continue;
				ofile.count("1TauPlusMuonVeto", weight);
				if(!( (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)        )) continue;
				ofile.count("1TauPlusDecayMode", weight);
				if(!( tau[t].leadPFChargedHadrCand_pt >= 5.0                                 )) continue;
				ofile.count("1TauPlusChargeHadrCandPt", weight);
				if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT > 0.5)) continue;
				ofile.count("1TauPlusLooseIso", weight);
				if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT > 0.5)) continue;
				ofile.count("1TauPlusMediumIso", weight);
				if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT > 0.5)) continue;
				ofile.count("1TauPlusTightIso", weight);
				if(!(        fabs(tau[t].eta) <= 2.1                                         )) continue;
				ofile.count("1TauPlusEtaCut", weight);
				if(!( tau[t].pt >= 45.                                 )) continue;
				ofile.count("1TauPlusPtCut", weight);
				ntauid++;
			
			}

			if (ntauid == 0) {

				if(!( tau[t].tauID_againstElectronTightMVA5 > 0.5                                 )) continue;
				ofile.count("ElectronVeto",weight);
				if(!( tau[t].tauID_againstMuonTight2 > 0.5                                 )) continue;
				ofile.count("MuonVeto", weight);
				if(!( (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)        )) continue;
				ofile.count("DecayMode", weight);
				if(!( tau[t].leadPFChargedHadrCand_pt >= 5.0                                 )) continue;
				ofile.count("ChargeHadrCandPt", weight);
				if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT > 0.5)) continue;
				ofile.count("LooseIso", weight);
				if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT > 0.5)) continue;
				ofile.count("MediumIso", weight);
				if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT > 0.5)) continue;
				ofile.count("TightIso", weight);
				if(!(        fabs(tau[t].eta) <= 2.1                                         )) continue;
				ofile.count("EtaCut", weight);
				if(!( tau[t].pt >= 45.                                 )) continue;
				ofile.count("PtCut", weight);
				ntauid++;

			}

		}


}
  stream.close();
  ofile.close();
  return 0;
}
