//---------------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for simple ntuples, such as those created by
//              TheNtupleMaker
// Created:     Mon Jun 29 15:52:41 2015 by mkanalyzer.py
// Author:      Daniele Marconi
//----------------------------------------------------------------------------
#include "tnm.h"
using namespace std;
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("analyzer", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);
    
  // Get names of ntuple files to be processed
  vector<string> filenames = fileNames(cl.filelist);

  // Create tree reader
  itreestream stream(filenames, "Events");
  if ( !stream.good() ) error("can't read root input files");

  // Create a buffer to receive events from the stream
  eventBuffer ev(stream);
  
  int nevents = ev.size();
  cout << "number of events: " << nevents << endl;

  // Create output file for histograms; see notes in header 
  outputFile of(cl.outputfilename);

  // -------------------------------------------------------------------------
  // Define histograms
  // -------------------------------------------------------------------------
  //setStyle();

  // -------------------------------------------------------------------------
  // Loop over events
  // -------------------------------------------------------------------------
  
  for(int entry=0; entry < nevents; entry++)
    {
      // read an event into event buffer
      ev.read(entry);

      // Uncomment the following line if you wish to copy variables into
      // structs. See the file eventBuffer.h to find out what structs
      // are available. Alternatively, you can call individual fill functions,
      // such as, ev.fillElectrons().
      //ev.fillObjects();

      // analysis
    }
    
  ev.close();
  of.close();
  return 0;
}
