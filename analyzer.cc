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
#include "analyzer.h"

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

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------

  TH2F* h2_Trigger = new TH2F("h2_Trigger", "Triggered in CRs", 2, -0.5, 1.5, 10, 0.5, 10.5);
  h2_Trigger->GetXaxis()->SetTitle("triggered");
  h2_Trigger->GetYaxis()->SetTitle("CR");
  h2_Trigger->Sumw2();

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

	double weight = 1.;

	MyHistoCollection myHistoColl_Skim (ofile.file_, "Skim");
	/*
	MyHistoCollection myHistoColl_SignalRegion(ofile.file_, "SignalRegion");
	MyHistoCollection myHistoColl_CR1 (ofile.file_, "Ztautau_CR1");
	MyHistoCollection myHistoColl_CR2 (ofile.file_, "Central_invertedVBF_CR2");
	MyHistoCollection myHistoColl_CR3 (ofile.file_, "Central_invertedVBF_TauMediumIso_CR3");	
	MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_TauLooseIso_CR4");
	MyHistoCollection myHistoColl_CR5 (ofile.file_, "Central_invertedVBF_NoIso_CR5");

	MyEventCollection baselineObjectSelectionCollection ("baselineObjectSelection");
	MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
	MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
	MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
	MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");*/
	
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

	MyEventCollection baselineObjectSelectionCollection ("baselineObjectSelection");
	MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
	MyEventCollection Tau1TightIsoObjectSelectionCollection ("Tau1TightIsoObjectSelection");
	MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
	MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
	MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");

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
	baselineObjectSelectionCollection.goodVertex = true;
	TauTightIsoObjectSelectionCollection.goodVertex = true;
	Tau1TightIsoObjectSelectionCollection.goodVertex = true;
	TauMediumIsoObjectSelectionCollection.goodVertex = true;
	TauLooseIsoObjectSelectionCollection.goodVertex = true;
	TauNoIsoObjectSelectionCollection.goodVertex = true;
}

          //trigger selection
   
          if(
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1)

            ) { 	baselineObjectSelectionCollection.passedTrigger = true;	
            		TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        	Tau1TightIsoObjectSelectionCollection.passedTrigger = true;
	        	TauMediumIsoObjectSelectionCollection.passedTrigger = true;
			TauLooseIsoObjectSelectionCollection.passedTrigger = true;
			TauNoIsoObjectSelectionCollection.passedTrigger = true;
              }

// electron selection
for(unsigned int e = 0;e<electron.size();++e){
	baselineObjectSelectionCollection.electron.push_back(&electron[e]);
	TauTightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	Tau1TightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauMediumIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauLooseIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	TauNoIsoObjectSelectionCollection.electron.push_back(&electron[e]);
}

// muon selection
for(unsigned int m =0;m<muon.size();++m){
	if(!( fabs(muon[m].eta) < 2.4 )) 					continue;
	if(!( muon[m].pt > 20 )) 						continue;
	if(!( muon[m].isGlobalMuon )) 						continue;
	if(!( muon[m].isTrackerMuon )) 						continue;
	if(!( muon[m].isPFMuon )) 						continue;
	if(!( muon[m].numberOfMatchedStations > 1 )) 				continue;
	if(!(( fabs(muon[m].muonBestTrack_dxy) < 0.2 )) &&
             ( fabs(muon[m]. muonBestTrack_dz) < 0.5 )) 			continue;
	if(!( muon[m].globalTrack_normalizedChi2 < 10. )) 			continue;
	if(!( muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0 )) 	continue;
	if(!( muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0 )) 	continue;
	if(!( muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5 )) 	continue;
	if(!( muon[m].innerTrack_normalizedChi2 < 1.8 )) 			continue;
	if(!( fabs(muon[m].innerTrack_dxy) < 3. )) 				continue;
	if(!( fabs(muon[m].innerTrack_dz) < 30. )) 				continue;
	baselineObjectSelectionCollection.muon.push_back(&muon[m]);
	TauTightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	Tau1TightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauNoIsoObjectSelectionCollection.muon.push_back(&muon[m]);
}     

	std::vector<int> tights;
	std::vector<int> mediums;
	std::vector<int> looses;
	std::vector<int> nones;
	
          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
            baselineObjectSelectionCollection.tau.push_back(&tau[t]);
	    if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) tights.push_back(t);
	    else if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) mediums.push_back(t);
	    else if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) looses.push_back(t);
	    else nones.push_back(t);
          }
          
	  if(tights.size()==2) for(unsigned int t =0;t<tights.size();++t) {int i=tights[t]; TauTightIsoObjectSelectionCollection.tau.push_back(&tau[i]);}
	  else if(tights.size()==1 && (mediums.size()+looses.size()+nones.size())==1) {tights.insert(tights.end(),mediums.begin(), mediums.end()); tights.insert(tights.end(),looses.begin(), looses.end()); tights.insert(tights.end(),nones.begin(), nones.end()); for(unsigned int t =0;t<tights.size();++t) {int i=tights[t]; Tau1TightIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(mediums.size()>=1 && (mediums.size()+looses.size()+nones.size())==2) {mediums.insert(mediums.end(), looses.begin(), looses.end()); mediums.insert(mediums.end(), nones.begin(), nones.end()); for(unsigned int t =0;t<mediums.size();++t) {int i=mediums[t]; TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(looses.size()>=1 && (looses.size()+nones.size())==2) {looses.insert(looses.end(), nones.begin(), nones.end()); for(unsigned int t =0;t<looses.size();++t) {int i=looses[t]; TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(nones.size()==2) for(unsigned int t =0;t<nones.size();++t) {int i=nones[t]; TauNoIsoObjectSelectionCollection.tau.push_back(&tau[i]);}
	  
          // jet && bjet selection
	  // ? id ?
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                	)) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 5.0                                          )) continue;
	    double baseDistance = TauJetMinDistance(baselineObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double mainDistance = TauJetMinDistance(TauTightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double T1Distance = TauJetMinDistance(Tau1TightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double mediumDistance = TauJetMinDistance(TauMediumIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double looseDistance = TauJetMinDistance(TauLooseIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double NoDistance = TauJetMinDistance(TauNoIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
            bool jetid=true;
	    if(!(      (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99      )) jetid=false;
	    if(!(      jet[j].neutralEmEnergyFraction < 0.99                                            )) jetid=false;
	    if(!(      jet[j].numberOfDaughters > 1                                                     )) jetid=false;
	    if(fabs(jet[j].eta) < 2.4) {
              if(!(      jet[j].chargedHadronEnergyFraction > 0                        			)) jetid=false;
              if(!(      jet[j].chargedEmEnergyFraction < 0.99                            		)) jetid=false;
              if(!(      jet[j].chargedHadronMultiplicity > 0                             		)) jetid=false;
            }
            if(      /*jet[j].pt >= 50.  &&*/ jetid		){
              if(	baseDistance >= 0.3	) baselineObjectSelectionCollection.jet.push_back(&jet[j]);	
	      if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	T1Distance >= 0.3	) Tau1TightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	mediumDistance >= 0.3	) TauMediumIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
            }
            if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244    ){
              if(	baseDistance >= 0.3	) baselineObjectSelectionCollection.bjet.push_back(&jet[j]);	
              if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	T1Distance >= 0.3	) Tau1TightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	mediumDistance >= 0.3	) TauMediumIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
            }
	  }

	  //MET selection
	  baselineObjectSelectionCollection.met.push_back(&met[0]);
	  TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);
	  Tau1TightIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);

	  //Event Count
	  ofile.count("NoCuts");

	  // ------------------------
	  // -- Skimming Studies   --
	  // ------------------------

	  myHistoColl_Skim.h_count->Fill("NoCuts",0);
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",0);

	  while (true){

		//NoCuts
		myHistoColl_Skim.h_count->Fill("NoCuts",1);

		//AtLeast2Loostau
		//if(!(             ( (int)baselineObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		//myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",1);

		fillHistoCollection (myHistoColl_Skim, baselineObjectSelectionCollection,weight);

		break;		

	}

// ---------------------
// -- Signal Region --
// ---------------------

Selection Signal("Signal"); //label and initialisation
Signal.InputCollection 		= &TauTightIsoObjectSelectionCollection;        //input collection
Signal.OutputCollection 	= &myHistoColl_SignalRegion;        //output collection
Signal.RealData        		= edmEventHelper_isRealData;        //pass information if event is real data
Signal.RunData        		= false;        //real data allowed
Signal.NumberTauMin        	= 2;        //require at least N tau
Signal.NumberTauMax        	= 3;        //require at less than N taus
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
Signal.weight        		= 1.;        //event weight
Signal.invertTauRequirements    = false;        //invert number of taus requirement
Signal.invertTauProperties      = false;        //invert ditau properties (dR, sign)
Signal.invertBtagRequirement    = false;        //invert number of b-jets required
Signal.invertJetRequirements    = false;        //invert jet pt requirements
Signal.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

Signal.select();        //do selection, fill histograms

if(Signal.passed) h2_Trigger->Fill(TauTightIsoObjectSelectionCollection.passedTrigger, 1);

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection InvertedVBF_CR2("InvertedVBF_CR2"); //label and initialisation
InvertedVBF_CR2.InputCollection 	= &TauTightIsoObjectSelectionCollection;        //input collection
InvertedVBF_CR2.OutputCollection 	= &myHistoColl_CR2;        //output collection
InvertedVBF_CR2.RealData        	= edmEventHelper_isRealData;        //pass information if event is real data
InvertedVBF_CR2.RunData        		= true;        //real data allowed
InvertedVBF_CR2.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_CR2.NumberTauMax        	= 3;        //require at less than N taus
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
InvertedVBF_CR2.weight        		= 1.;        //event weight
InvertedVBF_CR2.invertTauRequirements   = false;        //invert number of taus requirement
InvertedVBF_CR2.invertTauProperties     = false;        //invert ditau properties (dR, sign)
InvertedVBF_CR2.invertBtagRequirement   = false;        //invert number of b-jets required
InvertedVBF_CR2.invertJetRequirements   = true;        //invert jet pt requirements
InvertedVBF_CR2.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_CR2.select();        //do selection, fill histograms

if(InvertedVBF_CR2.passed) h2_Trigger->Fill(TauTightIsoObjectSelectionCollection.passedTrigger, 2);

// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------

Selection oneTightTau_CR3("oneTightTau_CR3"); //label and initialisation
oneTightTau_CR3.InputCollection 	= &Tau1TightIsoObjectSelectionCollection;        //input collection
oneTightTau_CR3.OutputCollection 	= &myHistoColl_CR3;        //output collection
oneTightTau_CR3.RealData        	= edmEventHelper_isRealData;        //pass information if event is real data
oneTightTau_CR3.RunData        		= true;        //real data allowed
oneTightTau_CR3.NumberTauMin        	= 2;        //require at least N tau
oneTightTau_CR3.NumberTauMax        	= 3;        //require at less than N taus
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
oneTightTau_CR3.weight        		= 1.;        //event weight
oneTightTau_CR3.invertTauRequirements   = false;        //invert number of taus requirement
oneTightTau_CR3.invertTauProperties     = false;        //invert ditau properties (dR, sign)
oneTightTau_CR3.invertBtagRequirement   = false;        //invert number of b-jets required
oneTightTau_CR3.invertJetRequirements   = false;        //invert jet pt requirements
oneTightTau_CR3.invertDijetProperties   = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

oneTightTau_CR3.select();        //do selection, fill histograms

if(oneTightTau_CR3.passed) h2_Trigger->Fill(Tau1TightIsoObjectSelectionCollection.passedTrigger, 3);

// ---------------------------------------------
// -- CENTRAL + InvertedVBF + 1 Tight Tau CR4 --
// ---------------------------------------------

Selection InvertedVBF_oneTightTau_CR4("InvertedVBF_oneTightTau_CR4"); //label and initialisation
InvertedVBF_oneTightTau_CR4.InputCollection 		= &Tau1TightIsoObjectSelectionCollection;        //input collection
InvertedVBF_oneTightTau_CR4.OutputCollection 		= &myHistoColl_CR4;        //output collection
InvertedVBF_oneTightTau_CR4.RealData        		= edmEventHelper_isRealData;        //pass information if event is real data
InvertedVBF_oneTightTau_CR4.RunData        		= true;        //real data allowed
InvertedVBF_oneTightTau_CR4.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_oneTightTau_CR4.NumberTauMax        	= 3;        //require at less than N taus
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
InvertedVBF_oneTightTau_CR4.weight        		= 1.;        //event weight
InvertedVBF_oneTightTau_CR4.invertTauRequirements       = false;        //invert number of taus requirement
InvertedVBF_oneTightTau_CR4.invertTauProperties         = false;        //invert ditau properties (dR, sign)
InvertedVBF_oneTightTau_CR4.invertBtagRequirement       = false;        //invert number of b-jets required
InvertedVBF_oneTightTau_CR4.invertJetRequirements       = true;        //invert jet pt requirements
InvertedVBF_oneTightTau_CR4.invertDijetProperties       = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_oneTightTau_CR4.select();        //do selection, fill histograms

if(InvertedVBF_oneTightTau_CR4.passed) h2_Trigger->Fill(Tau1TightIsoObjectSelectionCollection.passedTrigger, 4);

// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------

Selection AntiTightTau_CR5("AntiTightTau_CR5"); //label and initialisation
AntiTightTau_CR5.InputCollection 		= &TauMediumIsoObjectSelectionCollection;        //input collection
AntiTightTau_CR5.OutputCollection 		= &myHistoColl_CR5;        //output collection
AntiTightTau_CR5.RealData        		= edmEventHelper_isRealData;        //pass information if event is real data
AntiTightTau_CR5.RunData        		= true;        //real data allowed
AntiTightTau_CR5.NumberTauMin        		= 2;        //require at least N tau
AntiTightTau_CR5.NumberTauMax        		= 3;        //require at less than N taus
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
AntiTightTau_CR5.weight        			= 1.;        //event weight
AntiTightTau_CR5.invertTauRequirements        	= false;        //invert number of taus requirement
AntiTightTau_CR5.invertTauProperties        	= false;        //invert ditau properties (dR, sign)
AntiTightTau_CR5.invertBtagRequirement        	= false;        //invert number of b-jets required
AntiTightTau_CR5.invertJetRequirements        	= false;        //invert jet pt requirements
AntiTightTau_CR5.invertDijetProperties        	= false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

AntiTightTau_CR5.select();        //do selection, fill histograms

if(AntiTightTau_CR5.passed) h2_Trigger->Fill(TauMediumIsoObjectSelectionCollection.passedTrigger, 5);

// ------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Tight Tau CR6 --
// ------------------------------------------------

Selection InvertedVBF_AntiTightTau_CR6("InvertedVBF_AntiTightTau_CR6"); //label and initialisation
InvertedVBF_AntiTightTau_CR6.InputCollection 		= &TauMediumIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiTightTau_CR6.OutputCollection 		= &myHistoColl_CR6;        //output collection
InvertedVBF_AntiTightTau_CR6.RealData        		= edmEventHelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiTightTau_CR6.RunData        		= true;        //real data allowed
InvertedVBF_AntiTightTau_CR6.NumberTauMin       	= 2;        //require at least N tau
InvertedVBF_AntiTightTau_CR6.NumberTauMax       	= 3;        //require at less than N taus
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
InvertedVBF_AntiTightTau_CR6.weight        		= 1.;        //event weight
InvertedVBF_AntiTightTau_CR6.invertTauRequirements      = false;        //invert number of taus requirement
InvertedVBF_AntiTightTau_CR6.invertTauProperties        = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiTightTau_CR6.invertBtagRequirement      = false;        //invert number of b-jets required
InvertedVBF_AntiTightTau_CR6.invertJetRequirements      = true;        //invert jet pt requirements
InvertedVBF_AntiTightTau_CR6.invertDijetProperties      = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiTightTau_CR6.select();        //do selection, fill histograms

if(InvertedVBF_AntiTightTau_CR6.passed) h2_Trigger->Fill(TauMediumIsoObjectSelectionCollection.passedTrigger, 6);

// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------

Selection AntiMediumTau_CR7("AntiMediumTau_CR7"); //label and initialisation
AntiMediumTau_CR7.InputCollection 	= &TauLooseIsoObjectSelectionCollection;        //input collection
AntiMediumTau_CR7.OutputCollection 	= &myHistoColl_CR7;        //output collection
AntiMediumTau_CR7.RealData        	= edmEventHelper_isRealData;        //pass information if event is real data
AntiMediumTau_CR7.RunData        	= true;        //real data allowed
AntiMediumTau_CR7.NumberTauMin        	= 2;        //require at least N tau
AntiMediumTau_CR7.NumberTauMax        	= 3;        //require at less than N taus
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
AntiMediumTau_CR7.weight        	= 1.;        //event weight
AntiMediumTau_CR7.invertTauRequirements = false;        //invert number of taus requirement
AntiMediumTau_CR7.invertTauProperties   = false;        //invert ditau properties (dR, sign)
AntiMediumTau_CR7.invertBtagRequirement = false;        //invert number of b-jets required
AntiMediumTau_CR7.invertJetRequirements = false;        //invert jet pt requirements
AntiMediumTau_CR7.invertDijetProperties = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

AntiMediumTau_CR7.select();        //do selection, fill histograms

if(AntiMediumTau_CR7.passed) h2_Trigger->Fill(TauLooseIsoObjectSelectionCollection.passedTrigger, 7);

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Medium Tau CR8 --
// -------------------------------------------------

Selection InvertedVBF_AntiMediumTau_CR8("InvertedVBF_AntiMediumTau_CR8"); //label and initialisation
InvertedVBF_AntiMediumTau_CR8.InputCollection 		= &TauLooseIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiMediumTau_CR8.OutputCollection 		= &myHistoColl_CR8;        //output collection
InvertedVBF_AntiMediumTau_CR8.RealData        		= edmEventHelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiMediumTau_CR8.RunData        		= true;        //real data allowed
InvertedVBF_AntiMediumTau_CR8.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_AntiMediumTau_CR8.NumberTauMax        	= 3;        //require at less than N taus
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
InvertedVBF_AntiMediumTau_CR8.weight        		= 1.;        //event weight
InvertedVBF_AntiMediumTau_CR8.invertTauRequirements     = false;        //invert number of taus requirement
InvertedVBF_AntiMediumTau_CR8.invertTauProperties       = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiMediumTau_CR8.invertBtagRequirement     = false;        //invert number of b-jets required
InvertedVBF_AntiMediumTau_CR8.invertJetRequirements     = true;        //invert jet pt requirements
InvertedVBF_AntiMediumTau_CR8.invertDijetProperties     = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiMediumTau_CR8.select();        //do selection, fill histograms

if(InvertedVBF_AntiMediumTau_CR8.passed) h2_Trigger->Fill(TauLooseIsoObjectSelectionCollection.passedTrigger, 8);

// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------

Selection AntiLooseTau_CR9("AntiLooseTau_CR9"); //label and initialisation
AntiLooseTau_CR9.InputCollection 	= &TauNoIsoObjectSelectionCollection;        //input collection
AntiLooseTau_CR9.OutputCollection 	= &myHistoColl_CR9;        //output collection
AntiLooseTau_CR9.RealData        	= edmEventHelper_isRealData;        //pass information if event is real data
AntiLooseTau_CR9.RunData        	= true;        //real data allowed
AntiLooseTau_CR9.NumberTauMin        	= 2;        //require at least N tau
AntiLooseTau_CR9.NumberTauMax        	= 3;        //require at less than N taus
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
AntiLooseTau_CR9.weight        		= 1.;        //event weight
AntiLooseTau_CR9.invertTauRequirements  = false;        //invert number of taus requirement
AntiLooseTau_CR9.invertTauProperties    = false;        //invert ditau properties (dR, sign)
AntiLooseTau_CR9.invertBtagRequirement  = false;        //invert number of b-jets required
AntiLooseTau_CR9.invertJetRequirements  = false;        //invert jet pt requirements
AntiLooseTau_CR9.invertDijetProperties  = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

AntiLooseTau_CR9.select();        //do selection, fill histograms

if(AntiLooseTau_CR9.passed) h2_Trigger->Fill(TauNoIsoObjectSelectionCollection.passedTrigger, 9);

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Loose Tau CR10 --
// -------------------------------------------------

Selection InvertedVBF_AntiLooseTau_CR10("InvertedVBF_AntiLooseTau_CR10"); //label and initialisation
InvertedVBF_AntiLooseTau_CR10.InputCollection 		= &TauNoIsoObjectSelectionCollection;        //input collection
InvertedVBF_AntiLooseTau_CR10.OutputCollection 		= &myHistoColl_CR10;        //output collection
InvertedVBF_AntiLooseTau_CR10.RealData        		= edmEventHelper_isRealData;        //pass information if event is real data
InvertedVBF_AntiLooseTau_CR10.RunData        		= true;        //real data allowed
InvertedVBF_AntiLooseTau_CR10.NumberTauMin        	= 2;        //require at least N tau
InvertedVBF_AntiLooseTau_CR10.NumberTauMax        	= 3;        //require at less than N taus
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
InvertedVBF_AntiLooseTau_CR10.weight        		= 1.;        //event weight
InvertedVBF_AntiLooseTau_CR10.invertTauRequirements     = false;        //invert number of taus requirement
InvertedVBF_AntiLooseTau_CR10.invertTauProperties       = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiLooseTau_CR10.invertBtagRequirement     = false;        //invert number of b-jets required
InvertedVBF_AntiLooseTau_CR10.invertJetRequirements     = true;        //invert jet pt requirements
InvertedVBF_AntiLooseTau_CR10.invertDijetProperties     = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiLooseTau_CR10.select();        //do selection, fill histograms

if(InvertedVBF_AntiLooseTau_CR10.passed) h2_Trigger->Fill(TauNoIsoObjectSelectionCollection.passedTrigger, 10);

// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_CR1("Ztautau_CR1"); //label and initialisation
Ztautau_CR1.InputCollection 		= &TauTightIsoObjectSelectionCollection;        //input collection
Ztautau_CR1.OutputCollection 		= &myHistoColl_CR1;        //output collection
Ztautau_CR1.RealData        		= edmEventHelper_isRealData;        //pass information if event is real data
Ztautau_CR1.RunData        		= true;        //real data allowed
Ztautau_CR1.NumberTauMin        	= 2;        //require at least N tau
Ztautau_CR1.NumberTauMax        	= 3;        //require at less than N taus
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

//Clearing Object Collections
TauTightIsoObjectSelectionCollection.clear();
Tau1TightIsoObjectSelectionCollection.clear();
TauMediumIsoObjectSelectionCollection.clear();
TauLooseIsoObjectSelectionCollection.clear();
TauNoIsoObjectSelectionCollection.clear();
baselineObjectSelectionCollection.clear();
}
  stream.close();
  ofile.close();
  return 0;
}

