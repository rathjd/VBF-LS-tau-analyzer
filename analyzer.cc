//-----------------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for ntuples created by TheNtupleMaker
// Created:     Wed Jul 15 14:54:46 2015 by mkanalyzer.py
// Author:      Daniele Marconi
//-----------------------------------------------------------------------------
#include "CommonHistoCollection.h"
#include "CutConfiguration.h"
#include "analyzer.h"
using namespace std;
using namespace evt;
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

  int nevents = stream.size();
  cout << "Number of events: " << nevents << endl;

  // Select variables to be read

  selectVariables(stream);


  // The root application is needed to make canvases visible during
  // program execution. If this is not needed, just comment out the
  // following line

  TApplication app("analyzer", &argc, argv);

  /**
	 Notes 1
	 -------
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

     Notes 2
	 -------
	 By default all variables are saved. Before the event loop, you can use
  
       select(objectname)
	  
     e.g.,
	
       select("GenParticle")
  
     to declare that you intend to select objects of this type. The
	 selection is done using

       select(objectname, index)
	  
     e.g.,
	  
       select("GenParticle", 3),
  
     which is called within the event loop. Call saveSelectedObjects()
	 before a call to addEvent if you wish to save the selected objects.
	 All other objects are saved by default.
	 
	 NB: If you declare your intention to select objects of a given type
	     by calling select(objectname), but subsequently fail to select
	     them using select(objectname, index) then none will be saved!
  */

  outputFile ofile(cmdline.outputfilename);

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------


  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------


  for(int entry=0; entry < nevents; ++entry)
	{
	  // Read event into memory
	  stream.read(entry);

	  // NB: call to clear object selection map (indexmap)
	  initialize();
	  
	  // Uncomment the following line if you wish to copy variables into
	  // structs. See the header file analyzer.h to find out what structs
	  // are available. Alternatively, you can call individual fill functions.
	  // fillObjects();


	  // ---------------------
	  // -- event selection --
	  // ---------------------


	  
	  // ---------------------
	  // -- fill histograms --
	  // ---------------------	  

	}

  stream.close();
  ofile.close();
  return 0;
}
