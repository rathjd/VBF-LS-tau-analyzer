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
  double weight=1.;
  TH1F* h1_WeightDiff = new TH1F("h1_WeightDiff", "p_event-p(exactly these 2 fake tau)", 11,-0.5,10.5);
  h1_WeightDiff->GetXaxis()->SetTitle("N_{jets}");
  h1_WeightDiff->GetYaxis()->SetTitle("#Sigma(p_event-p(exactly these 2 fake tau))");
  h1_WeightDiff->Sumw2();

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

TH1::SetDefaultSumw2();
TFile file_eff("/afs/naf.desy.de/user/r/rathjd/public/VBFAnalyzer/ChargeMap_Jet30Tau45_DijetV2.root", "read");
TFile file_Resp("/afs/naf.desy.de/user/r/rathjd/public/VBFAnalyzer/ResponseFactors_InclAndExclIsos_Jet30Tau45_Dijet.root", "read");

MyHistoCollection myHistoColl_SignalRegion(ofile.file_, "SignalRegion");        
MyHistoCollection myHistoColl_CR1 (ofile.file_, "Ztautau_CR1");
MyHistoCollection myHistoColl_CR2 (ofile.file_, "Central_invertedVBF_2TightIso_CR2");
MyHistoCollection myHistoColl_CR3 (ofile.file_, "Central_1TightIso_CR3");
MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_1TightIso_CR4");
MyHistoCollection myHistoColl_CR5 (ofile.file_, "Central_AntiTightIso_CR5");
MyHistoCollection myHistoColl_CR6 (ofile.file_, "Central_invertedVBF_AntiTightIso_CR6");
MyHistoCollection myHistoColl_CR7 (ofile.file_, "Central_AntiMediumIso_CR7");
MyHistoCollection myHistoColl_CR8 (ofile.file_, "Central_invertedVBF_AntiMediumIso_CR8");
MyHistoCollection myHistoColl_CR9 (ofile.file_, "Central_AntiLooseIso_CR9");
MyHistoCollection myHistoColl_CR10 (ofile.file_, "Central_invertedVBF_AntiLooseIso_CR10");
/*MyHistoCollection myHistoColl_SignalRegion(ofile.file_, "SignalRegion");	
MyHistoCollection myHistoColl_CR1 (ofile.file_, "Ztautau_CR1");
MyHistoCollection myHistoColl_CR2 (ofile.file_, "Central_invertedVBF_CR2");
MyHistoCollection myHistoColl_CR3 (ofile.file_, "Central_invertedVBF_TauMediumIso_CR3");	
MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_TauLooseIso_CR4");
MyHistoCollection myHistoColl_CR5 (ofile.file_, "Central_invertedVBF_NoIso_CR5");*/


MyEventCollection DijetObjectSelectionCollection ("DijetObjectSelection");
MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
MyEventCollection Tau1TightIsoObjectSelectionCollection ("Tau1TightIsoObjectSelection");
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
if(goodVertex){
	TauTightIsoObjectSelectionCollection.goodVertex = true;
	Tau1TightIsoObjectSelectionCollection.goodVertex = true;
	TauMediumIsoObjectSelectionCollection.goodVertex = true;
	TauLooseIsoObjectSelectionCollection.goodVertex = true;
	TauNoIsoObjectSelectionCollection.goodVertex = true;
}
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
	  double ptave = 0.;
	  if(DijetObjectSelectionCollection.jet.size()>=2) ptave=(DijetObjectSelectionCollection.jet[0]->pt+DijetObjectSelectionCollection.jet[1]->pt)/2;
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
//if(verbose)std::cout<<"prescale="<<weight<<std::endl;
//trigger selection
   
/*if(
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1) ||
  (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1)
  ){
	TauTightIsoObjectSelectionCollection.passedTrigger = true;
	Tau1TightIsoObjectSelectionCollection.passedTrigger = true;
	TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	TauNoIsoObjectSelectionCollection.passedTrigger = true;
   }*/

// electron selection
for(unsigned int e = 0;e<electron.size();++e){
	TauTightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	Tau1TightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauMediumIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauLooseIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauNoIsoObjectSelectionCollection.electron.push_back(&electron[e]);
}

// muon selection
for(unsigned int m =0;m<muon.size();++m){
	if(!( fabs(muon[m].eta) < 2.4 )) 					continue;
	if(!( muon[m].pt > 20 ))			 			continue;
	if(!( muon[m].isGlobalMuon )) 						continue;
	if(!( muon[m].isTrackerMuon )) 						continue;
	if(!( muon[m].isPFMuon )) 						continue;
	if(!( muon[m].numberOfMatchedStations > 1 )) 				continue;
	if(!(( fabs(muon[m].muonBestTrack_dxy) < 0.2 )) &&
            ( fabs(muon[m]. muonBestTrack_dz) < 0.5 )) 				continue;
	if(!( muon[m].globalTrack_normalizedChi2 < 10. )) 			continue;
	if(!( muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0 )) 	continue;
	if(!( muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0 )) 	continue;
	if(!( muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5 )) 	continue;
	if(!( muon[m].innerTrack_normalizedChi2 < 1.8 )) 			continue;
	if(!( fabs(muon[m].innerTrack_dxy) < 3. )) 				continue;
	if(!( fabs(muon[m].innerTrack_dz) < 30. )) 				continue;
	TauTightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	Tau1TightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauNoIsoObjectSelectionCollection.muon.push_back(&muon[m]);
}

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

TH2F* ChargeMapN_eff = (TH2F*)(file_eff.Get("ChargeMapN_eff"));
TH1F* ReweightFactorN = (TH1F*)(file_Resp.Get("RescaleWeightN"));
vector<double> jet_taufakerateN;

TH2F* ChargeMapL_eff = (TH2F*)(file_eff.Get("ChargeMapL_eff"));
TH1F* ReweightFactorL = (TH1F*)(file_Resp.Get("RescaleWeightL"));
vector<double> jet_taufakerateL;

TH2F* ChargeMapLi_eff = (TH2F*)(file_eff.Get("ChargeMapLi_eff"));
TH1F* ReweightFactorLi = (TH1F*)(file_Resp.Get("RescaleWeightLi"));
vector<double> jet_taufakerateLi;

TH2F* ChargeMapM_eff = (TH2F*)(file_eff.Get("ChargeMapM_eff"));
TH1F* ReweightFactorM = (TH1F*)(file_Resp.Get("RescaleWeightM"));
vector<double> jet_taufakerateM;

TH2F* ChargeMapMi_eff = (TH2F*)(file_eff.Get("ChargeMapMi_eff"));
TH1F* ReweightFactorMi = (TH1F*)(file_Resp.Get("RescaleWeightMi"));
vector<double> jet_taufakerateMi;

TH2F* ChargeMapT_eff = (TH2F*)(file_eff.Get("ChargeMapT_eff"));
TH1F* ReweightFactorT = (TH1F*)(file_Resp.Get("RescaleWeightT"));
vector<double> jet_taufakerateT;

if(DijetObjectSelectionCollection.passedTrigger){ for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
int nbinN = ChargeMapN_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinN= ReweightFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinL = ChargeMapL_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinL= ReweightFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinLi = ChargeMapLi_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinLi= ReweightFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinM = ChargeMapM_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinM= ReweightFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinMi = ChargeMapMi_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinMi= ReweightFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
int nbinT = ChargeMapT_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction);
int nRescaleBinT= ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
if(verbose)std::cout<<"Jet "<<i<<" out of "<<JetLooseIsoObjectSelectionCollection.jet.size()<<": pT="<<JetLooseIsoObjectSelectionCollection.jet[i]->pt<<", eta="<<JetLooseIsoObjectSelectionCollection.jet[i]->eta<<", phi="<<JetLooseIsoObjectSelectionCollection.jet[i]->phi<<std::endl;
if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.1)
  {
    jet_taufakerateN.push_back(ChargeMapN_eff->GetBinContent(nbinN)*ReweightFactorN->GetBinContent(nRescaleBinN));
    jet_taufakerateL.push_back(ChargeMapL_eff->GetBinContent(nbinL)*ReweightFactorL->GetBinContent(nRescaleBinL));
    jet_taufakerateLi.push_back(ChargeMapLi_eff->GetBinContent(nbinLi)*ReweightFactorLi->GetBinContent(nRescaleBinLi));
    jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nbinM)*ReweightFactorM->GetBinContent(nRescaleBinM));
    jet_taufakerateMi.push_back(ChargeMapMi_eff->GetBinContent(nbinMi)*ReweightFactorMi->GetBinContent(nRescaleBinMi));
    jet_taufakerateT.push_back(ChargeMapT_eff->GetBinContent(nbinT)*ReweightFactorT->GetBinContent(nRescaleBinT));
    if(verbose)std::cout<<"MindR and eta<=2.1 pass: N_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity<<", F_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction<<", P(N_q,F_q)="<<ChargeMapT_eff->GetBinContent(nbinT)<<", P(pT)="<<ReweightFactorT->GetBinContent(nRescaleBinT)<<std::endl;
  }
else
  {
    double jetMindR2=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
    if(jetMindR > 0.5 && jetMindR2 > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.2)
      {
        jet_taufakerateN.push_back(ChargeMapN_eff->GetBinContent(nbinN)*ReweightFactorN->GetBinContent(nRescaleBinN));
        jet_taufakerateL.push_back(ChargeMapL_eff->GetBinContent(nbinL)*ReweightFactorL->GetBinContent(nRescaleBinL));
	jet_taufakerateLi.push_back(ChargeMapLi_eff->GetBinContent(nbinLi)*ReweightFactorLi->GetBinContent(nRescaleBinLi));
        jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nbinM)*ReweightFactorM->GetBinContent(nRescaleBinM));
	jet_taufakerateMi.push_back(ChargeMapMi_eff->GetBinContent(nbinMi)*ReweightFactorMi->GetBinContent(nRescaleBinMi));
        jet_taufakerateT.push_back(ChargeMapT_eff->GetBinContent(nbinT)*ReweightFactorT->GetBinContent(nRescaleBinT));
	if(verbose)std::cout<<"MindR2 and 2.1<eta<=2.2 pass: N_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[i]->electronMultiplicity<<", F_q="<<JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction<<", P(N_q,F_q)="<<ChargeMapT_eff->GetBinContent(nbinT)<<", P(pT)="<<ReweightFactorT->GetBinContent(nRescaleBinT)<<std::endl;
      }
    else
      {
        jet_taufakerateN.push_back(0);
    	jet_taufakerateL.push_back(0);
	jet_taufakerateLi.push_back(0);
	jet_taufakerateM.push_back(0);
	jet_taufakerateMi.push_back(0);
	jet_taufakerateT.push_back(0);
	if(verbose)std::cout<<"Failed: P=0!"<<std::endl;
      }
  }
}



Fake FakeTausN("FakeTaus");
if(verbose)std::cout<<"Dice NoIso"<<std::endl;
FakeTausN.generate(jet_taufakerateN,jet_taufakerateN, true);

//apply NN trigger scaling factor out of dijet data:
//std::cout<<"begin "<<FakeTausN.weight<<std::endl;
FakeTausN.weight*=1.65/10000*weight;
//std::cout<<FakeTausN.weight<<std::endl;
tau_s faketau1N;
tau_s faketau2N;

TH1F* h1_taufakescaleN_fac = (TH1F*)(file_Resp.Get("scaleN"));

if ( FakeTausN.index.first >= 0 && FakeTausN.index.second >= 0 ) {

double scale = h1_taufakescaleN_fac->GetBinContent(h1_taufakescaleN_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausN.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->charge >= 0 ) faketau1N.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->charge < 0 ) faketau1N.charge = -1;
faketau1N.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->p;
faketau1N.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->energy;
faketau1N.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->et;
faketau1N.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->px;
faketau1N.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->py;
faketau1N.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pz;
faketau1N.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt * scale;
if(faketau1N.pt < 45) FakeTausN.weight=0;
faketau1N.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta<=2.1) faketau1N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta;
else faketau1N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->eta)*2.1;

double scale2 = h1_taufakescaleN_fac->GetBinContent(h1_taufakescaleN_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt));
if(scale2 == 0) {scale2 = 0.851; FakeTausN.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->charge >= 0 )
faketau2N.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->charge < 0 )
faketau2N.charge = -1;	
faketau2N.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->p;
faketau2N.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->energy;
faketau2N.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->et;
faketau2N.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->px;
faketau2N.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->py;
faketau2N.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pz;
faketau2N.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt * scale2;
if(faketau2N.pt < 45) FakeTausN.weight=0;
faketau2N.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta<=2.1) faketau2N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta;
else faketau2N.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->eta)*2.1;
if(faketau1N.pt > faketau2N.pt){
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau1N);
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau2N);
}
else{
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau2N);
  TauNoIsoObjectSelectionCollection.tau.push_back(&faketau1N);
}

if(verbose)std::cout<<"Jet "<<FakeTausN.index.first<<" to FTau1: pTScale="<<scale<<", pT="<<faketau1N.pt<<", eta="<<faketau1N.eta<<", phi="<<faketau1N.phi<<", charge"<<faketau1N.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausN.index.second<<" to FTau2: pTScale="<<scale2<<", pT="<<faketau2N.pt<<", eta="<<faketau2N.eta<<", phi="<<faketau2N.phi<<", charge"<<faketau2N.charge<<std::endl;
}

Fake FakeTausL("FakeTaus");
if(verbose)std::cout<<"Dice LooseIso"<<std::endl;

FakeTausL.generate(jet_taufakerateL,jet_taufakerateLi, false);

//apply LL,LN trigger scaling factor out of dijet data:
FakeTausL.weight*=2.6/1000*weight;

tau_s faketau1L;
tau_s faketau2L;

TH1F* h1_taufakescaleL_fac = (TH1F*)(file_Resp.Get("scaleL"));

if ( FakeTausL.index.first >= 0 && FakeTausL.index.second >= 0 ) {

double scale = h1_taufakescaleL_fac->GetBinContent(h1_taufakescaleL_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausL.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->charge >= 0 )
faketau1L.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->charge < 0 )
faketau1L.charge = -1;
faketau1L.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->p;
faketau1L.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->energy;
faketau1L.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->et;
faketau1L.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->px;
faketau1L.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->py;
faketau1L.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pz;
faketau1L.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt * scale;
if(faketau1L.pt < 45) FakeTausL.weight=0;
faketau1L.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta<=2.1) faketau1L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta;
else faketau1L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->eta)*2.1;

TH1F* h1_taufakescaleLi_fac = (TH1F*)(file_Resp.Get("scaleLi")); 
double scale2 = h1_taufakescaleLi_fac->GetBinContent(h1_taufakescaleLi_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt));
if(scale2 == 0) {scale2 = 0.851; FakeTausL.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->charge >= 0 )
faketau2L.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->charge < 0 )
faketau2L.charge = -1;	
faketau2L.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->p;
faketau2L.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->energy;
faketau2L.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->et;
faketau2L.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->px;
faketau2L.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->py;
faketau2L.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pz;
faketau2L.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt * scale2;
if(faketau2L.pt < 45) FakeTausL.weight=0;
faketau2L.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta<=2.1) faketau2L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta;
else faketau2L.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->eta)*2.1;

if(faketau1L.pt > faketau2L.pt){
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau1L);
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau2L);
}
else{
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau2L);
  TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau1L);
}

if(verbose)std::cout<<"Jet "<<FakeTausL.index.first<<" to FTau1: pTScale="<<scale<<", pT="<<faketau1L.pt<<", eta="<<faketau1L.eta<<", phi="<<faketau1L.phi<<", charge"<<faketau1L.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausL.index.second<<" to FTau2: pTScale="<<scale2<<", pT="<<faketau2L.pt<<", eta="<<faketau2L.eta<<", phi="<<faketau2L.phi<<", charge"<<faketau2L.charge<<std::endl;
}

Fake FakeTausM("FakeTausM");
if(verbose)std::cout<<"Dice MediumIso"<<std::endl;

FakeTausM.generate(jet_taufakerateM,jet_taufakerateMi, false);

//apply MM,ML,MN trigger scaling factor out of dijet data:
FakeTausM.weight*=6.3/1000*weight;

tau_s faketau1M;
tau_s faketau2M;

TH1F* h1_taufakescaleM_fac = (TH1F*)(file_Resp.Get("scaleM"));

if ( FakeTausM.index.first >= 0 && FakeTausM.index.second >= 0 ) {

double scale = h1_taufakescaleM_fac->GetBinContent(h1_taufakescaleM_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausM.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->charge >= 0 )
faketau1M.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->charge < 0 )
faketau1M.charge = -1;
faketau1M.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->p;
faketau1M.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->energy;
faketau1M.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->et;
faketau1M.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->px;
faketau1M.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->py;
faketau1M.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pz;
faketau1M.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt * scale;
if(faketau1M.pt < 45) FakeTausM.weight=0;
faketau1M.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta<=2.1) faketau1M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta;
else faketau1M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->eta)*2.1;

TH1F* h1_taufakescaleMi_fac = (TH1F*)(file_Resp.Get("scaleMi"));
double scale2 = h1_taufakescaleMi_fac->GetBinContent(h1_taufakescaleMi_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt));
if(scale2 == 0) {scale2 = 0.851; FakeTausM.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->charge >= 0 )
faketau2M.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->charge < 0 )
faketau2M.charge = -1;	
faketau2M.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->p;
faketau2M.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->energy;
faketau2M.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->et;
faketau2M.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->px;
faketau2M.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->py;
faketau2M.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pz;
faketau2M.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt * scale2;
if(faketau2M.pt < 45) FakeTausM.weight=0;
faketau2M.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta<=2.1) faketau2M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta;
else faketau2M.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->eta)*2.1;

if(faketau1M.pt > faketau2M.pt){
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau1M);
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau2M);
}
else{
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau2M);
  TauMediumIsoObjectSelectionCollection.tau.push_back(&faketau1M);
}

if(verbose)std::cout<<"Jet "<<FakeTausM.index.first<<" to FTau1: pTScale="<<scale<<", pT="<<faketau1M.pt<<", eta="<<faketau1M.eta<<", phi="<<faketau1M.phi<<", charge"<<faketau1M.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausM.index.second<<" to FTau2: pTScale="<<scale2<<", pT="<<faketau2M.pt<<", eta="<<faketau2M.eta<<", phi="<<faketau2M.phi<<", charge"<<faketau2M.charge<<std::endl;
}

Fake FakeTausT("FakeTausT");
if(verbose)std::cout<<"Dice 1TightIso"<<std::endl;
FakeTausT.generate(jet_taufakerateT,jet_taufakerateMi, false);

//apply TM,TL,TN trigger scaling factor out of dijet data:
FakeTausT.weight*=5.7/1000*weight;

tau_s faketau1T;
tau_s faketau2T;

TH1F* h1_taufakescaleT_fac = (TH1F*)(file_Resp.Get("scaleT"));

if ( FakeTausT.index.first >= 0 && FakeTausT.index.second >= 0 ) {

double scale = h1_taufakescaleT_fac->GetBinContent(h1_taufakescaleT_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausT.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->charge >= 0 )
faketau1T.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->charge < 0 )
faketau1T.charge = -1;
faketau1T.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->p;
faketau1T.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->energy;
faketau1T.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->et;
faketau1T.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->px;
faketau1T.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->py;
faketau1T.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pz;
faketau1T.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt * scale;
if(faketau1T.pt < 45) FakeTausT.weight=0;
faketau1T.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta<=2.1) faketau1T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta;
else faketau1T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->eta)*2.1;

TH1F* h1_taufakescaleMi_fac = (TH1F*)(file_Resp.Get("scaleMi"));
double scale2 = h1_taufakescaleMi_fac->GetBinContent(h1_taufakescaleMi_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt));
if(scale2 == 0) {scale2 = 0.851; FakeTausT.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->charge >= 0 )
faketau2T.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->charge < 0 )
faketau2T.charge = -1;	
faketau2T.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->p;
faketau2T.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->energy;
faketau2T.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->et;
faketau2T.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->px;
faketau2T.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->py;
faketau2T.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pz;
faketau2T.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt * scale2;
if(faketau2T.pt < 45) FakeTausT.weight=0;
faketau2T.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta<=2.1) faketau2T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta;
else faketau2T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->eta)*2.1;
if(faketau1T.pt > faketau2T.pt){
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau1T);
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau2T);
}
else{
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau2T);
  Tau1TightIsoObjectSelectionCollection.tau.push_back(&faketau1T);
}

if(verbose)std::cout<<"Jet "<<FakeTausT.index.first<<" to FTau1: pTScale="<<scale<<", pT="<<faketau1T.pt<<", eta="<<faketau1T.eta<<", phi="<<faketau1T.phi<<", charge"<<faketau1T.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausT.index.second<<" to FTau2: pTScale="<<scale2<<", pT="<<faketau2T.pt<<", eta="<<faketau2T.eta<<", phi="<<faketau2T.phi<<", charge"<<faketau2T.charge<<std::endl;
}

Fake FakeTausTT("FakeTausTT");
if(verbose)std::cout<<"Dice 2TightIso"<<std::endl;
FakeTausTT.generate(jet_taufakerateT,jet_taufakerateT, true);

//apply TT trigger scaling factor out of dijet data:
FakeTausTT.weight*=weight;
//std::cout<<FakeTausTT.weight<<std::endl;
tau_s faketauT1T;
tau_s faketauT2T;



if ( FakeTausTT.index.first >= 0 && FakeTausTT.index.second >= 0 ) {

TH1F* h1_taufakescaleT_fac = (TH1F*)(file_Resp.Get("scaleT"));
double scale = h1_taufakescaleT_fac->GetBinContent(h1_taufakescaleT_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->pt)); 
if(scale == 0) {scale = 0.851; FakeTausTT.weight=0;}

if(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->charge >= 0 )
faketauT1T.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->charge < 0 )
faketauT1T.charge = -1;
faketauT1T.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->p;
faketauT1T.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->energy;
faketauT1T.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->et;
faketauT1T.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->px;
faketauT1T.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->py;
faketauT1T.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->pz;
faketauT1T.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->pt * scale;
if(faketauT1T.pt < 45) FakeTausTT.weight=0;
faketauT1T.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->eta<=2.1) faketauT1T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->eta;
else faketauT1T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->eta)*2.1;

double scale2 = h1_taufakescaleT_fac->GetBinContent(h1_taufakescaleT_fac->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->pt));
if(scale2 == 0) {scale2 = 0.851; FakeTausTT.weight=0;}
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->charge >= 0 )
faketauT2T.charge = +1;
else if(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->charge < 0 )
faketauT2T.charge = -1;	
faketauT2T.p = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->p;
faketauT2T.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->energy;
faketauT2T.et = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->et;
faketauT2T.px = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->px;
faketauT2T.py = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->py;
faketauT2T.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->pz;
faketauT2T.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->pt * scale2;
if(faketauT2T.pt < 45) FakeTausTT.weight=0;
faketauT2T.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->phi;
if(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->eta<=2.1) faketauT2T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->eta;
else faketauT2T.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->eta)*2.1;
if(faketauT1T.pt > faketauT2T.pt){
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT1T);
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT2T);
}
else{
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT2T);
  TauTightIsoObjectSelectionCollection.tau.push_back(&faketauT1T);
}

if(verbose)std::cout<<"Jet "<<FakeTausTT.index.first<<" to FTau1: pTScale="<<scale<<", pT="<<faketauT1T.pt<<", eta="<<faketauT1T.eta<<", phi="<<faketauT1T.phi<<", charge"<<faketauT1T.charge<<std::endl;
if(verbose)std::cout<<"Jet "<<FakeTausTT.index.second<<" to FTau2: pTScale="<<scale2<<", pT="<<faketauT2T.pt<<", eta="<<faketauT2T.eta<<", phi="<<faketauT2T.phi<<", charge"<<faketauT2T.charge<<std::endl;
}

// jet && bjet selection
// ? id ?
for(unsigned int j = 0;j<jet.size();++j){
if(!( jet[j].pt >= 30. )) continue; // Original value 20
if(!( fabs(jet[j].eta) <= 5.0 )) continue;
double DistanceN = TauJetMinDistance(TauNoIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceL = TauJetMinDistance(TauLooseIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceM = TauJetMinDistance(TauMediumIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double Distance1T = TauJetMinDistance(Tau1TightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
double DistanceT = TauJetMinDistance(TauTightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
bool jetid=true;
if(!( (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99 )) jetid=false;
if(!( jet[j].neutralEmEnergyFraction < 0.99 )) jetid=false;
if(!( jet[j].numberOfDaughters > 1 )) jetid=false;
if(fabs(jet[j].eta) < 2.4) {
   if(!( jet[j].chargedHadronEnergyFraction > 0 )) jetid=false;
   if(!( jet[j].chargedEmEnergyFraction < 0.99 ))  jetid=false;
   if(!( jet[j].chargedHadronMultiplicity > 0 ))   jetid=false;
 }
if( /*jet[j].pt >= 50. &&*/ jetid	){
  if(	DistanceN >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceL >= 0.3	) TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceM >= 0.3	) TauMediumIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	Distance1T >= 0.3	) Tau1TightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  if(	DistanceT >= 0.3	) {TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]); if(verbose)std::cout<<"Jet "<<j<<" in tight jet coll: pt="<<jet[j].pt<<", eta="<<jet[j].eta<<", phi"<<jet[j].phi<<std::endl;}
            }
if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244 ){
  if(	DistanceN >= 0.3	) TauNoIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceL >= 0.3	) TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceM >= 0.3	) TauMediumIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	Distance1T >= 0.3	) Tau1TightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  if(	DistanceT >= 0.3	) {TauTightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);if(verbose)std::cout<<"Jet "<<j<<" in tight b-jet coll: pt="<<jet[j].pt<<", eta="<<jet[j].eta<<", phi"<<jet[j].phi<<std::endl;}
            }
}
if(verbose)std::cout<<TauTightIsoObjectSelectionCollection.jet.size()<<" jets in tightIso jet collection and "<<TauTightIsoObjectSelectionCollection.bjet.size()<<" in bjet collection"<<std::endl;

//MET selection
TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);
TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
Tau1TightIsoObjectSelectionCollection.met.push_back(&met[0]);
TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);

//Event Count
ofile.count("NoCuts");

// ---------------------
// -- Signal Region --
// ---------------------

Selection Signal("Signal"); //label and initialisation
Signal.InputCollection 		= &TauTightIsoObjectSelectionCollection;        //input collection
Signal.OutputCollection 	= &myHistoColl_SignalRegion;        //output collection
Signal.RealData        		= eventhelper_isRealData;        //pass information if event is real data
Signal.RunData        		= false;        //real data allowed
Signal.NumberTauMin        	= 2;        //require at least N tau
Signal.NumberTauMax        	= 3;        //require less than N taus
Signal.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
Signal.DiTauInvMassMin        	= -1;        //minimum Di-tau-mass requirement
Signal.DiTauInvMassMax        	= -1;        //maximum Di-tau-mass requirement
Signal.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
Signal.Btag        		= 0;        //number of btags required (exact -> 0 = none)
Signal.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
Signal.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
Signal.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
Signal.SubLeadJetPtMin        	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
Signal.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
Signal.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
Signal.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
Signal.DiJetInvMassMin        	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
Signal.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
Signal.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
Signal.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Signal.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Signal.weight        		= FakeTausTT.weight;        //event weight
Signal.invertTauRequirements    = false;        //invert number of taus requirement
Signal.invertTauProperties      = false;        //invert ditau properties (dR, sign)
Signal.invertBtagRequirement    = false;        //invert number of b-jets required
Signal.invertJetRequirements    = false;        //invert jet pt requirements
Signal.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

Signal.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection InvertedVBF_CR2("InvertedVBF_CR2"); //label and initialisation
InvertedVBF_CR2.InputCollection 	= &TauTightIsoObjectSelectionCollection;        //input collection
InvertedVBF_CR2.OutputCollection 	= &myHistoColl_CR2;        //output collection
InvertedVBF_CR2.RealData        	= eventhelper_isRealData;        //pass information if event is real data
InvertedVBF_CR2.RunData        		= true;        //real data allowed
InvertedVBF_CR2.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_CR2.NumberTauMax        	= 3;        //require less than N taus
InvertedVBF_CR2.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
InvertedVBF_CR2.DiTauInvMassMin        	= -1;        //minimum Di-tau-mass requirement
InvertedVBF_CR2.DiTauInvMassMax        	= -1;        //maximum Di-tau-mass requirement
InvertedVBF_CR2.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR2.Btag        		= 0;        //number of btags required (exact -> 0 = none)
InvertedVBF_CR2.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR2.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR2.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR2.SubLeadJetPtMin        	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR2.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR2.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR2.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR2.DiJetInvMassMin        	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR2.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR2.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
InvertedVBF_CR2.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR2.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR2.weight        		= FakeTausTT.weight;        //event weight
InvertedVBF_CR2.invertTauRequirements   = false;        //invert number of taus requirement
InvertedVBF_CR2.invertTauProperties     = false;        //invert ditau properties (dR, sign)
InvertedVBF_CR2.invertBtagRequirement   = false;        //invert number of b-jets required
InvertedVBF_CR2.invertJetRequirements   = true;        //invert jet pt requirements
InvertedVBF_CR2.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_CR2.select();        //do selection, fill histograms

// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------

Selection oneTightTau_CR3("oneTightTau_CR3"); //label and initialisation
oneTightTau_CR3.InputCollection 	= &Tau1TightIsoObjectSelectionCollection;        //input collection
oneTightTau_CR3.OutputCollection 	= &myHistoColl_CR3;        //output collection
oneTightTau_CR3.RealData        	= eventhelper_isRealData;        //pass information if event is real data
oneTightTau_CR3.RunData        		= true;        //real data allowed
oneTightTau_CR3.NumberTauMin        	= 2;        //require at least N tau
oneTightTau_CR3.NumberTauMax        	= 3;        //require less than N taus
oneTightTau_CR3.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
oneTightTau_CR3.DiTauInvMassMin        	= -1;        //minimum Di-tau-mass requirement
oneTightTau_CR3.DiTauInvMassMax        	= -1;        //maximum Di-tau-mass requirement
oneTightTau_CR3.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
oneTightTau_CR3.Btag        		= 0;        //number of btags required (exact -> 0 = none)
oneTightTau_CR3.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
oneTightTau_CR3.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
oneTightTau_CR3.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
oneTightTau_CR3.SubLeadJetPtMin       	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
oneTightTau_CR3.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
oneTightTau_CR3.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
oneTightTau_CR3.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
oneTightTau_CR3.DiJetInvMassMin        	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
oneTightTau_CR3.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
oneTightTau_CR3.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
oneTightTau_CR3.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
oneTightTau_CR3.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
oneTightTau_CR3.weight        		= FakeTausT.weight;        //event weight
oneTightTau_CR3.invertTauRequirements   = false;        //invert number of taus requirement
oneTightTau_CR3.invertTauProperties     = false;        //invert ditau properties (dR, sign)
oneTightTau_CR3.invertBtagRequirement   = false;        //invert number of b-jets required
oneTightTau_CR3.invertJetRequirements   = false;        //invert jet pt requirements
oneTightTau_CR3.invertDijetProperties   = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

oneTightTau_CR3.select();        //do selection, fill histograms

// ---------------------------------------------
// -- CENTRAL + InvertedVBF + 1 Tight Tau CR4 --
// ---------------------------------------------

Selection InvertedVBF_oneTightTau_CR4("InvertedVBF_oneTightTau_CR4"); //label and initialisation
InvertedVBF_oneTightTau_CR4.InputCollection 		= &Tau1TightIsoObjectSelectionCollection;        //input collection
InvertedVBF_oneTightTau_CR4.OutputCollection 		= &myHistoColl_CR4;        //output collection
InvertedVBF_oneTightTau_CR4.RealData        		= eventhelper_isRealData;        //pass information if event is real data
InvertedVBF_oneTightTau_CR4.RunData        		= true;        //real data allowed
InvertedVBF_oneTightTau_CR4.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_oneTightTau_CR4.NumberTauMax        	= 3;        //require less than N taus
InvertedVBF_oneTightTau_CR4.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
InvertedVBF_oneTightTau_CR4.DiTauInvMassMin        	= -1;        //minimum Di-tau-mass requirement
InvertedVBF_oneTightTau_CR4.DiTauInvMassMax        	= -1;        //maximum Di-tau-mass requirement
InvertedVBF_oneTightTau_CR4.DiTauSign        		= +1;        //1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_oneTightTau_CR4.Btag        		= 0;        //number of btags required (exact -> 0 = none)
InvertedVBF_oneTightTau_CR4.JetEtaMax        		= 5.;        //maximum eta for jets, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.SubLeadJetPtMin        	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.DiJetDrMin        		= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.DiJetDrMax        		= -1;        //Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.DiJetInvMassMin        	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
InvertedVBF_oneTightTau_CR4.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.weight        		= FakeTausT.weight;        //event weight
InvertedVBF_oneTightTau_CR4.invertTauRequirements       = false;        //invert number of taus requirement
InvertedVBF_oneTightTau_CR4.invertTauProperties         = false;        //invert ditau properties (dR, sign)
InvertedVBF_oneTightTau_CR4.invertBtagRequirement       = false;        //invert number of b-jets required
InvertedVBF_oneTightTau_CR4.invertJetRequirements       = true;        //invert jet pt requirements
InvertedVBF_oneTightTau_CR4.invertDijetProperties       = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_oneTightTau_CR4.select();        //do selection, fill histograms

// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------

Selection AntiTightTau_CR5("AntiTightTau_CR5"); //label and initialisation
AntiTightTau_CR5.InputCollection 		= &TauMediumIsoObjectSelectionCollection;        //input collection
AntiTightTau_CR5.OutputCollection 		= &myHistoColl_CR5;        //output collection
AntiTightTau_CR5.RealData        		= eventhelper_isRealData;        //pass information if event is real data
AntiTightTau_CR5.RunData        		= true;        //real data allowed
AntiTightTau_CR5.NumberTauMin        		= 2;        //require at least N tau
AntiTightTau_CR5.NumberTauMax        		= 3;        //require less than N taus
AntiTightTau_CR5.DiTauDeltaRmin        		= 0.3;        //minimum delta R for tau pair
AntiTightTau_CR5.DiTauInvMassMin        	= -1;        //minimum Di-tau-mass requirement
AntiTightTau_CR5.DiTauInvMassMax        	= -1;        //maximum Di-tau-mass requirement
AntiTightTau_CR5.DiTauSign        		= +1;        //1 for LS and -1 for OS, 0 for no requirement
AntiTightTau_CR5.Btag        			= 0;        //number of btags required (exact -> 0 = none)
AntiTightTau_CR5.JetEtaMax        		= 5.;        //maximum eta for jets, set to -1 for no requirement
AntiTightTau_CR5.LeadJetPtMin        		= 30.;        //minimum pt of lead jet, set to -1 for no requirement
AntiTightTau_CR5.LeadJetPtMax        		= -1.;        //maximum pt of lead jet, set to -1 for no requirement
AntiTightTau_CR5.SubLeadJetPtMin        	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
AntiTightTau_CR5.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
AntiTightTau_CR5.DiJetDrMin        		= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
AntiTightTau_CR5.DiJetDrMax        		= -1;        //Dijet maximum delta R, set to -1 for no requirement
AntiTightTau_CR5.DiJetInvMassMin        	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
AntiTightTau_CR5.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
AntiTightTau_CR5.DiJetSignEta        		= -1;        //Dijet sign eta_1*eta_2
AntiTightTau_CR5.DiJetDetaMin        		= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
AntiTightTau_CR5.DiJetDetaMax        		= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
AntiTightTau_CR5.weight        			= FakeTausM.weight;        //event weight
AntiTightTau_CR5.invertTauRequirements        	= false;        //invert number of taus requirement
AntiTightTau_CR5.invertTauProperties        	= false;        //invert ditau properties (dR, sign)
AntiTightTau_CR5.invertBtagRequirement        	= false;        //invert number of b-jets required
AntiTightTau_CR5.invertJetRequirements        	= false;        //invert jet pt requirements
AntiTightTau_CR5.invertDijetProperties        	= false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

AntiTightTau_CR5.select();        //do selection, fill histograms

// ------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Tight Tau CR6 --
// ------------------------------------------------

Selection InvertedVBF_AntiTightTau_CR6("InvertedVBF_AntiTightTau_CR6"); //label and initialisation
InvertedVBF_AntiTightTau_CR6.InputCollection 		= &TauMediumIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiTightTau_CR6.OutputCollection 		= &myHistoColl_CR6;        //output collection
InvertedVBF_AntiTightTau_CR6.RealData        		= eventhelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiTightTau_CR6.RunData        		= true;        //real data allowed
InvertedVBF_AntiTightTau_CR6.NumberTauMin       	= 2;        //require at least N tau
InvertedVBF_AntiTightTau_CR6.NumberTauMax       	= 3;        //require less than N taus
InvertedVBF_AntiTightTau_CR6.DiTauDeltaRmin     	= 0.3;        //minimum delta R for tau pair
InvertedVBF_AntiTightTau_CR6.DiTauInvMassMin    	= -1;        //minimum Di-tau-mass requirement
InvertedVBF_AntiTightTau_CR6.DiTauInvMassMax    	= -1;        //maximum Di-tau-mass requirement
InvertedVBF_AntiTightTau_CR6.DiTauSign        		= +1;        //1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_AntiTightTau_CR6.Btag        		= 0;        //number of btags required (exact -> 0 = none)
InvertedVBF_AntiTightTau_CR6.JetEtaMax        		= 5.;        //maximum eta for jets, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.LeadJetPtMin       	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.LeadJetPtMax       	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.SubLeadJetPtMin    	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.SubLeadJetPtMax    	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.DiJetDrMin        		= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.DiJetDrMax        		= -1;        //Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.DiJetInvMassMin    	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.DiJetInvMassMax    	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.DiJetSignEta       	= -1;        //Dijet sign eta_1*eta_2
InvertedVBF_AntiTightTau_CR6.DiJetDetaMin       	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.DiJetDetaMax       	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.weight        		= FakeTausM.weight;        //event weight
InvertedVBF_AntiTightTau_CR6.invertTauRequirements      = false;        //invert number of taus requirement
InvertedVBF_AntiTightTau_CR6.invertTauProperties        = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiTightTau_CR6.invertBtagRequirement      = false;        //invert number of b-jets required
InvertedVBF_AntiTightTau_CR6.invertJetRequirements      = true;        //invert jet pt requirements
InvertedVBF_AntiTightTau_CR6.invertDijetProperties      = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiTightTau_CR6.select();        //do selection, fill histograms

// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------

Selection AntiMediumTau_CR7("AntiMediumTau_CR7"); //label and initialisation
AntiMediumTau_CR7.InputCollection 	= &TauLooseIsoObjectSelectionCollection;        //input collection
AntiMediumTau_CR7.OutputCollection 	= &myHistoColl_CR7;        //output collection
AntiMediumTau_CR7.RealData        	= eventhelper_isRealData;        //pass information if event is real data
AntiMediumTau_CR7.RunData        	= true;        //real data allowed
AntiMediumTau_CR7.NumberTauMin        	= 2;        //require at least N tau
AntiMediumTau_CR7.NumberTauMax        	= 3;        //require less than N taus
AntiMediumTau_CR7.DiTauDeltaRmin        = 0.3;        //minimum delta R for tau pair
AntiMediumTau_CR7.DiTauInvMassMin       = -1;        //minimum Di-tau-mass requirement
AntiMediumTau_CR7.DiTauInvMassMax       = -1;        //maximum Di-tau-mass requirement
AntiMediumTau_CR7.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
AntiMediumTau_CR7.Btag        		= 0;        //number of btags required (exact -> 0 = none)
AntiMediumTau_CR7.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
AntiMediumTau_CR7.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
AntiMediumTau_CR7.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
AntiMediumTau_CR7.SubLeadJetPtMin       = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
AntiMediumTau_CR7.SubLeadJetPtMax       = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
AntiMediumTau_CR7.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
AntiMediumTau_CR7.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
AntiMediumTau_CR7.DiJetInvMassMin       = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
AntiMediumTau_CR7.DiJetInvMassMax       = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
AntiMediumTau_CR7.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
AntiMediumTau_CR7.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
AntiMediumTau_CR7.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
AntiMediumTau_CR7.weight        	= FakeTausL.weight;        //event weight
AntiMediumTau_CR7.invertTauRequirements = false;        //invert number of taus requirement
AntiMediumTau_CR7.invertTauProperties   = false;        //invert ditau properties (dR, sign)
AntiMediumTau_CR7.invertBtagRequirement = false;        //invert number of b-jets required
AntiMediumTau_CR7.invertJetRequirements = false;        //invert jet pt requirements
AntiMediumTau_CR7.invertDijetProperties = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

AntiMediumTau_CR7.select();        //do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Medium Tau CR8 --
// -------------------------------------------------

Selection InvertedVBF_AntiMediumTau_CR8("InvertedVBF_AntiMediumTau_CR8"); //label and initialisation
InvertedVBF_AntiMediumTau_CR8.InputCollection 		= &TauLooseIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiMediumTau_CR8.OutputCollection 		= &myHistoColl_CR8;        //output collection
InvertedVBF_AntiMediumTau_CR8.RealData        		= eventhelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiMediumTau_CR8.RunData        		= true;        //real data allowed
InvertedVBF_AntiMediumTau_CR8.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_AntiMediumTau_CR8.NumberTauMax        	= 3;        //require less than N taus
InvertedVBF_AntiMediumTau_CR8.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
InvertedVBF_AntiMediumTau_CR8.DiTauInvMassMin        	= -1;        //minimum Di-tau-mass requirement
InvertedVBF_AntiMediumTau_CR8.DiTauInvMassMax        	= -1;        //maximum Di-tau-mass requirement
InvertedVBF_AntiMediumTau_CR8.DiTauSign        		= +1;        //1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_AntiMediumTau_CR8.Btag        		= 0;        //number of btags required (exact -> 0 = none)
InvertedVBF_AntiMediumTau_CR8.JetEtaMax        		= 5.;        //maximum eta for jets, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.SubLeadJetPtMin        	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.DiJetInvMassMin        	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
InvertedVBF_AntiMediumTau_CR8.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.weight        		= FakeTausL.weight;        //event weight
InvertedVBF_AntiMediumTau_CR8.invertTauRequirements     = false;        //invert number of taus requirement
InvertedVBF_AntiMediumTau_CR8.invertTauProperties       = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiMediumTau_CR8.invertBtagRequirement     = false;        //invert number of b-jets required
InvertedVBF_AntiMediumTau_CR8.invertJetRequirements     = true;        //invert jet pt requirements
InvertedVBF_AntiMediumTau_CR8.invertDijetProperties     = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiMediumTau_CR8.select();        //do selection, fill histograms

// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------

Selection AntiLooseTau_CR9("AntiLooseTau_CR9"); //label and initialisation
AntiLooseTau_CR9.InputCollection 	= &TauNoIsoObjectSelectionCollection;        //input collection
AntiLooseTau_CR9.OutputCollection 	= &myHistoColl_CR9;        //output collection
AntiLooseTau_CR9.RealData        	= eventhelper_isRealData;        //pass information if event is real data
AntiLooseTau_CR9.RunData        	= true;        //real data allowed
AntiLooseTau_CR9.NumberTauMin        	= 2;        //require at least N tau
AntiLooseTau_CR9.NumberTauMax        	= 3;        //require less than N taus
AntiLooseTau_CR9.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
AntiLooseTau_CR9.DiTauInvMassMin        = -1;        //minimum Di-tau-mass requirement
AntiLooseTau_CR9.DiTauInvMassMax        = -1;        //maximum Di-tau-mass requirement
AntiLooseTau_CR9.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
AntiLooseTau_CR9.Btag        		= 0;        //number of btags required (exact -> 0 = none)
AntiLooseTau_CR9.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
AntiLooseTau_CR9.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
AntiLooseTau_CR9.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
AntiLooseTau_CR9.SubLeadJetPtMin        = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
AntiLooseTau_CR9.SubLeadJetPtMax        = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
AntiLooseTau_CR9.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
AntiLooseTau_CR9.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
AntiLooseTau_CR9.DiJetInvMassMin        = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
AntiLooseTau_CR9.DiJetInvMassMax        = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
AntiLooseTau_CR9.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
AntiLooseTau_CR9.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
AntiLooseTau_CR9.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
AntiLooseTau_CR9.weight        		= FakeTausN.weight;        //event weight
AntiLooseTau_CR9.invertTauRequirements  = false;        //invert number of taus requirement
AntiLooseTau_CR9.invertTauProperties    = false;        //invert ditau properties (dR, sign)
AntiLooseTau_CR9.invertBtagRequirement  = false;        //invert number of b-jets required
AntiLooseTau_CR9.invertJetRequirements  = false;        //invert jet pt requirements
AntiLooseTau_CR9.invertDijetProperties  = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

AntiLooseTau_CR9.select();        //do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Loose Tau CR10 --
// -------------------------------------------------

Selection InvertedVBF_AntiLooseTau_CR10("InvertedVBF_AntiLooseTau_CR10"); //label and initialisation
InvertedVBF_AntiLooseTau_CR10.InputCollection 		= &TauNoIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiLooseTau_CR10.OutputCollection 		= &myHistoColl_CR10;        //output collection
InvertedVBF_AntiLooseTau_CR10.RealData        		= eventhelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiLooseTau_CR10.RunData        		= true;        //real data allowed
InvertedVBF_AntiLooseTau_CR10.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_AntiLooseTau_CR10.NumberTauMax        	= 3;        //require less than N taus
InvertedVBF_AntiLooseTau_CR10.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
InvertedVBF_AntiLooseTau_CR10.DiTauInvMassMin        	= -1;        //minimum Di-tau-mass requirement
InvertedVBF_AntiLooseTau_CR10.DiTauInvMassMax        	= -1;        //maximum Di-tau-mass requirement
InvertedVBF_AntiLooseTau_CR10.DiTauSign        		= +1;        //1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_AntiLooseTau_CR10.Btag        		= 0;        //number of btags required (exact -> 0 = none)
InvertedVBF_AntiLooseTau_CR10.JetEtaMax        		= 5.;        //maximum eta for jets, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.SubLeadJetPtMin        	= 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.DiJetInvMassMin        	= 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
InvertedVBF_AntiLooseTau_CR10.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.weight        		= FakeTausN.weight;        //event weight
InvertedVBF_AntiLooseTau_CR10.invertTauRequirements     = false;        //invert number of taus requirement
InvertedVBF_AntiLooseTau_CR10.invertTauProperties       = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiLooseTau_CR10.invertBtagRequirement     = false;        //invert number of b-jets required
InvertedVBF_AntiLooseTau_CR10.invertJetRequirements     = true;        //invert jet pt requirements
InvertedVBF_AntiLooseTau_CR10.invertDijetProperties     = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiLooseTau_CR10.select();        //do selection, fill histograms


// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_CR1("Ztautau_CR1"); //label and initialisation
Ztautau_CR1.InputCollection 		= &TauTightIsoObjectSelectionCollection;        //input collection
Ztautau_CR1.OutputCollection 		= &myHistoColl_CR1;        //output collection
Ztautau_CR1.RealData        		= eventhelper_isRealData;        //pass information if event is real data
Ztautau_CR1.RunData        		= true;        //real data allowed
Ztautau_CR1.NumberTauMin        	= 2;        //require at least N tau
Ztautau_CR1.NumberTauMax        	= 3;        //require less than N taus
Ztautau_CR1.DiTauDeltaRmin        	= 0.3;        //minimum delta R for tau pair
Ztautau_CR1.DiTauInvMassMin        	= -1.;        //minimum Di-tau-mass requirement
Ztautau_CR1.DiTauInvMassMax        	= 90.;        //maximum Di-tau-mass requirement
Ztautau_CR1.DiTauSign        		= -1;        //1 for LS and -1 for OS, 0 for no requirement
Ztautau_CR1.Btag        		= 0;        //number of btags required (exact -> 0 = none)
Ztautau_CR1.JetEtaMax        		= -1.;        //maximum eta for jets, set to -1 for no requirement
Ztautau_CR1.LeadJetPtMin        	= -1.;        //minimum pt of lead jet, set to -1 for no requirement
Ztautau_CR1.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
Ztautau_CR1.SubLeadJetPtMin        	= -1.;        //minimum pt of sub lead jet, set to -1 for no requirement
Ztautau_CR1.SubLeadJetPtMax        	= -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
Ztautau_CR1.DiJetDrMin        		= -1.;        //Dijet minimum delta R, set to -1 for no requirement
Ztautau_CR1.DiJetDrMax        		= -1.;        //Dijet maximum delta R, set to -1 for no requirement
Ztautau_CR1.DiJetInvMassMin        	= -1.;        //Dijet minimal invariant mass, set to -1 for no requirement
Ztautau_CR1.DiJetInvMassMax        	= -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
Ztautau_CR1.DiJetSignEta        	= 0;        //Dijet sign eta_1*eta_2
Ztautau_CR1.DiJetDetaMin        	= -1.;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Ztautau_CR1.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Ztautau_CR1.weight        		= 1.;        //event weight
Ztautau_CR1.invertTauRequirements       = false;        //invert number of taus requirement
Ztautau_CR1.invertTauProperties        	= false;        //invert ditau properties (dR, sign)
Ztautau_CR1.invertBtagRequirement       = false;        //invert number of b-jets required
Ztautau_CR1.invertJetRequirements       = false;        //invert jet pt requirements
Ztautau_CR1.invertDijetProperties       = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

Ztautau_CR1.select();        //do selection, fill histograms
}//end dijet trigger requirement
/*// ---------------------
// -- Signal Region --
// ---------------------

Selection Signal("Signal"); //label and initialisation
Signal.InputCollection = &TauTightIsoObjectSelectionCollection;	//input collection
Signal.OutputCollection = &myHistoColl_SignalRegion;	//output collection
Signal.RealData	= eventhelper_isRealData;	//pass information if event is real data
Signal.RunData	= false;	//real data allowed
Signal.NumberTauMin	= 2;	//require at least N tau
Signal.NumberTauMax	= -1;	//require less than N taus
Signal.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
Signal.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
Signal.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
Signal.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
Signal.Btag	= 0;	//number of btags required (exact -> 0 = none)
Signal.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
Signal.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
Signal.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
Signal.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
Signal.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
Signal.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
Signal.DiJetDrMax	= -1;	//Dijet maximum delta R, set to -1 for no requirement
Signal.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
Signal.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
Signal.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
Signal.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Signal.DiJetDetaMax	= -1;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Signal.weight	= FakeTausT.weight;	//event weight
Signal.invertTauRequirements	= false;	//invert number of taus requirement
Signal.invertTauProperties	= false;	//invert ditau properties (dR, sign)
Signal.invertBtagRequirement	= false;	//invert number of b-jets required
Signal.invertJetRequirements	= false;	//invert jet pt requirements
Signal.invertDijetProperties	= false;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"Signal selection"<<std::endl;
Signal.select();	//do selection, fill histograms

// ---------------------------------
// -- CENTRAL + INVERTED VBF CR --
// ---------------------------------

Selection InvertedVBF_CR2("InvertedVBF_CR2"); //label and initialisation
InvertedVBF_CR2.InputCollection = &TauTightIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR2.OutputCollection = &myHistoColl_CR2;	//output collection
InvertedVBF_CR2.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR2.RunData	= true;	//real data allowed
InvertedVBF_CR2.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR2.NumberTauMax	= -1;	//require less than N taus
InvertedVBF_CR2.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR2.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR2.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR2.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR2.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR2.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR2.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR2.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR2.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR2.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR2.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR2.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR2.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR2.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR2.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR2.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR2.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR2.weight	= FakeTausT.weight;	//event weight
InvertedVBF_CR2.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR2.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR2.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR2.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR2.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR2 selection"<<std::endl;
InvertedVBF_CR2.select();	//do selection, fill histograms

// ------------------------------------------------------
// -- CENTRAL + INVERTED VBF CR (with Tau Medium Iso) --
// ------------------------------------------------------

Selection InvertedVBF_CR3("InvertedVBF_TauMediumIso_CR3"); //label and initialisation
InvertedVBF_CR3.InputCollection = &TauMediumIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR3.OutputCollection = &myHistoColl_CR3;	//output collection
InvertedVBF_CR3.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR3.RunData	= true;	//real data allowed
InvertedVBF_CR3.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR3.NumberTauMax	= -1;	//require less than N taus
InvertedVBF_CR3.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR3.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR3.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR3.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR3.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR3.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR3.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR3.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR3.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR3.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR3.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR3.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR3.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR3.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR3.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR3.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR3.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR3.weight	= FakeTausM.weight;	//event weight
InvertedVBF_CR3.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR3.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR3.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR3.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR3.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR3 selection"<<std::endl;
InvertedVBF_CR3.select();	//do selection, fill histograms

// ------------------------------------------------------
// -- CENTRAL + INVERTED VBF CR (with Tau Loose Iso) --
// ------------------------------------------------------

Selection InvertedVBF_CR4("InvertedVBF_TauLooseIso_CR4"); //label and initialisation
InvertedVBF_CR4.InputCollection = &TauLooseIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR4.OutputCollection = &myHistoColl_CR4;	//output collection
InvertedVBF_CR4.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR4.RunData	= true;	//real data allowed
InvertedVBF_CR4.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR4.NumberTauMax	= -1;	//require less than N taus
InvertedVBF_CR4.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR4.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR4.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR4.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR4.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR4.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR4.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR4.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR4.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR4.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR4.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR4.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR4.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR4.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR4.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR4.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR4.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR4.weight	= FakeTausL.weight;	//event weight
InvertedVBF_CR4.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR4.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR4.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR4.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR4.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR4 selection"<<std::endl;
InvertedVBF_CR4.select();	//do selection, fill histograms

// ------------------------------------------------------
// -- CENTRAL + INVERTED VBF CR (without Tau Iso) --
// ------------------------------------------------------

Selection InvertedVBF_CR5("InvertedVBF_TauNoIso_CR5"); //label and initialisation
InvertedVBF_CR5.InputCollection = &TauNoIsoObjectSelectionCollection;	//input collection
InvertedVBF_CR5.OutputCollection = &myHistoColl_CR5;	//output collection
InvertedVBF_CR5.RealData	= eventhelper_isRealData;	//pass information if event is real data
InvertedVBF_CR5.RunData	= true;	//real data allowed
InvertedVBF_CR5.NumberTauMin	= 2;	//require at least N tau
InvertedVBF_CR5.NumberTauMax	= -1;	//require less than N taus
InvertedVBF_CR5.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
InvertedVBF_CR5.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
InvertedVBF_CR5.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
InvertedVBF_CR5.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
InvertedVBF_CR5.Btag	= 0;	//number of btags required (exact -> 0 = none)
InvertedVBF_CR5.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
InvertedVBF_CR5.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR5.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
InvertedVBF_CR5.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR5.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
InvertedVBF_CR5.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
InvertedVBF_CR5.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
InvertedVBF_CR5.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
InvertedVBF_CR5.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
InvertedVBF_CR5.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
InvertedVBF_CR5.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR5.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR5.weight	= FakeTausN.weight;	//event weight
InvertedVBF_CR5.invertTauRequirements	= false;	//invert number of taus requirement
InvertedVBF_CR5.invertTauProperties	= false;	//invert ditau properties (dR, sign)
InvertedVBF_CR5.invertBtagRequirement	= false;	//invert number of b-jets required
InvertedVBF_CR5.invertJetRequirements	= true;	//invert jet pt requirements
InvertedVBF_CR5.invertDijetProperties	= true;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR5 selection"<<std::endl;
InvertedVBF_CR5.select();	//do selection, fill histograms

// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_CR1("Ztautau_CR1"); //label and initialisation
Ztautau_CR1.InputCollection = &TauTightIsoObjectSelectionCollection;	//input collection
Ztautau_CR1.OutputCollection = &myHistoColl_CR1;	//output collection
Ztautau_CR1.RealData	= eventhelper_isRealData;	//pass information if event is real data
Ztautau_CR1.RunData	= true;	//real data allowed
Ztautau_CR1.NumberTauMin	= 2;	//require at least N tau
Ztautau_CR1.NumberTauMax	= -1;	//require less than N taus
Ztautau_CR1.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
Ztautau_CR1.DiTauInvMassMin	= -1.;	//minimum Di-tau-mass requirement
Ztautau_CR1.DiTauInvMassMax	= 90.;	//maximum Di-tau-mass requirement
Ztautau_CR1.DiTauSign	= -1;	//1 for LS and -1 for OS, 0 for no requirement
Ztautau_CR1.Btag	= 0;	//number of btags required (exact -> 0 = none)
Ztautau_CR1.JetEtaMax	= -1.;	//maximum eta for jets, set to -1 for no requirement
Ztautau_CR1.LeadJetPtMin	= -1.;	//minimum pt of lead jet, set to -1 for no requirement
Ztautau_CR1.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
Ztautau_CR1.SubLeadJetPtMin	= -1.;	//minimum pt of sub lead jet, set to -1 for no requirement
Ztautau_CR1.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
Ztautau_CR1.DiJetDrMin	= -1.;	//Dijet minimum delta R, set to -1 for no requirement
Ztautau_CR1.DiJetDrMax	= -1.;	//Dijet maximum delta R, set to -1 for no requirement
Ztautau_CR1.DiJetInvMassMin	= -1.;	//Dijet minimal invariant mass, set to -1 for no requirement
Ztautau_CR1.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
Ztautau_CR1.DiJetSignEta	= 0;	//Dijet sign eta_1*eta_2
Ztautau_CR1.DiJetDetaMin	= -1.;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Ztautau_CR1.DiJetDetaMax	= -1.;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Ztautau_CR1.weight	= FakeTausT.weight;	//event weight
Ztautau_CR1.invertTauRequirements	= false;	//invert number of taus requirement
Ztautau_CR1.invertTauProperties	= false;	//invert ditau properties (dR, sign)
Ztautau_CR1.invertBtagRequirement	= false;	//invert number of b-jets required
Ztautau_CR1.invertJetRequirements	= false;	//invert jet pt requirements
Ztautau_CR1.invertDijetProperties	= false;	//invert dijet system properties (dR, inv mass, sign eta, dEta)
if(verbose)std::cout<<"CR1 selection"<<std::endl;
Ztautau_CR1.select();	//do selection, fill histograms
*/
/*// ---------------------
// -- Central Loose Region --
// ---------------------

Selection Central_TauLooseIso_CR5("Central_TauLooseIso_CR5"); //label and initialisation
Central_TauLooseIso_CR5.InputCollection = &TauLooseIsoObjectSelectionCollection;	//input collection
Central_TauLooseIso_CR5.OutputCollection = &myHistoColl_CR5;	//output collection
Central_TauLooseIso_CR5.RealData	= eventhelper_isRealData;	//pass information if event is real data
Central_TauLooseIso_CR5.RunData	= true;	//real data allowed
Central_TauLooseIso_CR5.NumberTauMin	= 2;	//require at least N tau
Central_TauLooseIso_CR5.NumberTauMax	= -1;	//require less than N taus
Central_TauLooseIso_CR5.DiTauDeltaRmin	= 0.3;	//minimum delta R for tau pair
Central_TauLooseIso_CR5.DiTauInvMassMin	= -1;	//minimum Di-tau-mass requirement
Central_TauLooseIso_CR5.DiTauInvMassMax	= -1;	//maximum Di-tau-mass requirement
Central_TauLooseIso_CR5.DiTauSign	= +1;	//1 for LS and -1 for OS, 0 for no requirement
Central_TauLooseIso_CR5.Btag	= 0;	//number of btags required (exact -> 0 = none)
Central_TauLooseIso_CR5.JetEtaMax	= 5.;	//maximum eta for jets, set to -1 for no requirement
Central_TauLooseIso_CR5.LeadJetPtMin	= 75.;	//minimum pt of lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.LeadJetPtMax	= -1.;	//maximum pt of lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.SubLeadJetPtMin	= 50.;	//minimum pt of sub lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.SubLeadJetPtMax	= -1.;	//maximum pt of sub lead jet, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetDrMin	= 0.3;	//Dijet minimum delta R, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetDrMax	= -1;	//Dijet maximum delta R, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetInvMassMin	= 700.;	//Dijet minimal invariant mass, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetInvMassMax	= -1.;	//Dijet maximum invariant mass, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetSignEta	= -1;	//Dijet sign eta_1*eta_2
Central_TauLooseIso_CR5.DiJetDetaMin	= 4.2;	//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Central_TauLooseIso_CR5.DiJetDetaMax	= -1;	//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Central_TauLooseIso_CR5.weight	= FakeTausL.weight;	//event weight
Central_TauLooseIso_CR5.invertTauRequirements	= false;	//invert number of taus requirement
Central_TauLooseIso_CR5.invertTauProperties	= false;	//invert ditau properties (dR, sign)
Central_TauLooseIso_CR5.invertBtagRequirement	= false;	//invert number of b-jets required
Central_TauLooseIso_CR5.invertJetRequirements	= false;	//invert jet pt requirements
Central_TauLooseIso_CR5.invertDijetProperties	= false;	//invert dijet system properties (dR, inv mass, sign eta, dEta)

Central_TauLooseIso_CR5.select();*/	


//Clearing Object Collections
DijetObjectSelectionCollection.clear();
TauTightIsoObjectSelectionCollection.clear();
Tau1TightIsoObjectSelectionCollection.clear();
TauMediumIsoObjectSelectionCollection.clear();
TauLooseIsoObjectSelectionCollection.clear();
TauNoIsoObjectSelectionCollection.clear();
JetLooseIsoObjectSelectionCollection.clear();

if(verbose)std::cout<<"_______________________________________________"<<std::endl;
}

  stream.close();
  ofile.close();
  return 0;
}

