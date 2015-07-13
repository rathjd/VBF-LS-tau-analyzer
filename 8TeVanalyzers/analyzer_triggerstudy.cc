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

	MyHistoCollection myHistoColl_Skim_noIso_wiTrigger (ofile.file_, "Skim_noIso_wiTrigger");
	MyHistoCollection myHistoColl_Skim_noIso_woTrigger (ofile.file_, "Skim_noIso_woTrigger");
	MyHistoCollection myHistoColl_Skim_looseIso_wiTrigger (ofile.file_, "Skim_looseIso_wiTrigger");
	MyHistoCollection myHistoColl_Skim_looseIso_woTrigger (ofile.file_, "Skim_looseIso_woTrigger");
	MyHistoCollection myHistoColl_Skim_mediumIso_wiTrigger (ofile.file_, "Skim_mediumIso_wiTrigger");
	MyHistoCollection myHistoColl_Skim_mediumIso_woTrigger (ofile.file_, "Skim_mediumIso_woTrigger");
	MyHistoCollection myHistoColl_Skim_tightIso_wiTrigger (ofile.file_, "Skim_tightIso_wiTrigger");
	MyHistoCollection myHistoColl_Skim_tightIso_woTrigger (ofile.file_, "Skim_tightIso_woTrigger");
	
	MyHistoCollection myHistoColl_SignalRegion_wiTrigger(ofile.file_, "SignalRegion_wiTrigger");
	MyHistoCollection myHistoColl_SignalRegion_woTrigger(ofile.file_, "SignalRegion_woTrigger");

	MyEventCollection baselineObjectSelectionCollection_noIso ("baselineObjectSelection_noIso");
	MyEventCollection baselineObjectSelectionCollection_looseIso ("baselineObjectSelection_looseIso");
	MyEventCollection baselineObjectSelectionCollection_mediumIso ("baselineObjectSelection_mediumIso");
	MyEventCollection baselineObjectSelectionCollection_tightIso ("baselineObjectSelection_tightIso");
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
	baselineObjectSelectionCollection_noIso.goodVertex = true;
	baselineObjectSelectionCollection_looseIso.goodVertex = true; 
	baselineObjectSelectionCollection_mediumIso.goodVertex = true;
	baselineObjectSelectionCollection_tightIso.goodVertex = true;
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

            ) { 	baselineObjectSelectionCollection_noIso.passedTrigger = true;	
			baselineObjectSelectionCollection_looseIso.passedTrigger = true; 
			baselineObjectSelectionCollection_mediumIso.passedTrigger = true;
			baselineObjectSelectionCollection_tightIso.passedTrigger = true;
            		TauTightIsoObjectSelectionCollection.passedTrigger = true;
	        	Tau1TightIsoObjectSelectionCollection.passedTrigger = true;
	        	TauMediumIsoObjectSelectionCollection.passedTrigger = true;
			TauLooseIsoObjectSelectionCollection.passedTrigger = true;
			TauNoIsoObjectSelectionCollection.passedTrigger = true;
              }

// electron selection
for(unsigned int e = 0;e<electron.size();++e){
	baselineObjectSelectionCollection_noIso.electron.push_back(&electron[e]);
	baselineObjectSelectionCollection_looseIso.electron.push_back(&electron[e]);
	baselineObjectSelectionCollection_mediumIso.electron.push_back(&electron[e]);
	baselineObjectSelectionCollection_tightIso.electron.push_back(&electron[e]);
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
	baselineObjectSelectionCollection_noIso.muon.push_back(&muon[m]);
	baselineObjectSelectionCollection_looseIso.muon.push_back(&muon[m]); 
	baselineObjectSelectionCollection_mediumIso.muon.push_back(&muon[m]);
	baselineObjectSelectionCollection_tightIso.muon.push_back(&muon[m]);
	TauTightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	Tau1TightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	TauNoIsoObjectSelectionCollection.muon.push_back(&muon[m]);
}     

          //smart tau selection


	  bool genMatchedTau = false;
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            //if(!(       tau[t].pt >= 40.                                            				)) continue;
            if(!(       tau[t].pt >= 5.                                            				)) continue;

	  //Gen Tau Matching
	  for (unsigned int g = 0; g < genparticlehelper.size(); g++){
			if (  !(fabs(genparticlehelper[g].status) ==  3)  ) continue;
			if (  !(fabs(genparticlehelper[g].pdgId)  == 15)  ) continue;

	    		TLorentzVector taureco_4v;
	    		TLorentzVector taugen_4v;		  

	    		taureco_4v.SetPtEtaPhiE(tau[t].pt,tau[t].eta,tau[t].phi,tau[t].energy);
	    		taugen_4v.SetPtEtaPhiM(genparticlehelper[g].pt,genparticlehelper[g].eta,genparticlehelper[g].phi,genparticlehelper[g].mass);

			if (taureco_4v.DeltaR(taugen_4v) <= 0.3 ) genMatchedTau = true;
	    }

	    if(!(       genMatchedTau            )) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
            baselineObjectSelectionCollection_noIso.tau.push_back(&tau[t]);
	    if(tau[t].tauID_byTightIsolationMVA3newDMwLT  > 0.5) {baselineObjectSelectionCollection_tightIso.tau.push_back(&tau[t]);}
	    if(tau[t].tauID_byMediumIsolationMVA3newDMwLT  > 0.5) {baselineObjectSelectionCollection_mediumIso.tau.push_back(&tau[t]);}
	    if(tau[t].tauID_byLooseIsolationMVA3newDMwLT  > 0.5) {baselineObjectSelectionCollection_looseIso.tau.push_back(&tau[t]);}

          }
          
          // jet && bjet selection
	  // ? id ?
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                	)) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 5.0                                          )) continue;
	    double baseDistance_noIso = TauJetMinDistance(baselineObjectSelectionCollection_noIso, jet[j].eta, jet[j].phi);
	    double baseDistance_looseIso = TauJetMinDistance(baselineObjectSelectionCollection_looseIso, jet[j].eta, jet[j].phi);
	    double baseDistance_mediumIso = TauJetMinDistance(baselineObjectSelectionCollection_mediumIso, jet[j].eta, jet[j].phi);
	    double baseDistance_tightIso = TauJetMinDistance(baselineObjectSelectionCollection_tightIso, jet[j].eta, jet[j].phi);
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
              if(	baseDistance_noIso >= 0.3	) baselineObjectSelectionCollection_noIso.jet.push_back(&jet[j]);	
              if(	baseDistance_looseIso >= 0.3	) baselineObjectSelectionCollection_looseIso.jet.push_back(&jet[j]);	
              if(	baseDistance_mediumIso >= 0.3	) baselineObjectSelectionCollection_mediumIso.jet.push_back(&jet[j]);	
              if(	baseDistance_tightIso >= 0.3	) baselineObjectSelectionCollection_tightIso.jet.push_back(&jet[j]);	
	      if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	T1Distance >= 0.3	) Tau1TightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	mediumDistance >= 0.3	) TauMediumIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
            }
            if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244    ){
              if(	baseDistance_noIso >= 0.3	) baselineObjectSelectionCollection_noIso.bjet.push_back(&jet[j]);	
              if(	baseDistance_looseIso >= 0.3	) baselineObjectSelectionCollection_looseIso.bjet.push_back(&jet[j]);	
              if(	baseDistance_mediumIso >= 0.3	) baselineObjectSelectionCollection_mediumIso.bjet.push_back(&jet[j]);	
              if(	baseDistance_tightIso >= 0.3	) baselineObjectSelectionCollection_tightIso.bjet.push_back(&jet[j]);	
              if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	T1Distance >= 0.3	) Tau1TightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	mediumDistance >= 0.3	) TauMediumIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
            }
	  }

	  //MET selection
	  baselineObjectSelectionCollection_noIso.met.push_back(&met[0]);
	  baselineObjectSelectionCollection_looseIso.met.push_back(&met[0]);
	  baselineObjectSelectionCollection_mediumIso.met.push_back(&met[0]);
	  baselineObjectSelectionCollection_tightIso.met.push_back(&met[0]);
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

	myHistoColl_Skim_noIso_woTrigger.h_count->Fill("NoCuts",0);
	myHistoColl_Skim_looseIso_woTrigger.h_count->Fill("NoCuts",0);
	myHistoColl_Skim_mediumIso_woTrigger.h_count->Fill("NoCuts",0);
	myHistoColl_Skim_tightIso_woTrigger.h_count->Fill("NoCuts",0);


	//NoCuts
	myHistoColl_Skim_noIso_woTrigger.h_count->Fill("NoCuts",1);
	myHistoColl_Skim_looseIso_woTrigger.h_count->Fill("NoCuts",1);
	myHistoColl_Skim_mediumIso_woTrigger.h_count->Fill("NoCuts",1);
	myHistoColl_Skim_tightIso_woTrigger.h_count->Fill("NoCuts",1);
	fillHistoCollection (myHistoColl_Skim_noIso_woTrigger, baselineObjectSelectionCollection_noIso,weight);
	fillHistoCollection (myHistoColl_Skim_looseIso_woTrigger, baselineObjectSelectionCollection_looseIso,weight);
	fillHistoCollection (myHistoColl_Skim_mediumIso_woTrigger, baselineObjectSelectionCollection_mediumIso,weight);
	fillHistoCollection (myHistoColl_Skim_tightIso_woTrigger, baselineObjectSelectionCollection_tightIso,weight);

	//Requiring trigger fired
	if ( baselineObjectSelectionCollection_noIso.passedTrigger     ) {

          myHistoColl_Skim_noIso_wiTrigger.h_count->Fill("NoCuts",0);
	  myHistoColl_Skim_looseIso_wiTrigger.h_count->Fill("NoCuts",0);
	  myHistoColl_Skim_mediumIso_wiTrigger.h_count->Fill("NoCuts",0);
	  myHistoColl_Skim_tightIso_wiTrigger.h_count->Fill("NoCuts",0);


	  myHistoColl_Skim_noIso_wiTrigger.h_count->Fill("NoCuts",1);
	  myHistoColl_Skim_looseIso_wiTrigger.h_count->Fill("NoCuts",1);
	  myHistoColl_Skim_mediumIso_wiTrigger.h_count->Fill("NoCuts",1);
	  myHistoColl_Skim_tightIso_wiTrigger.h_count->Fill("NoCuts",1);
	  fillHistoCollection (myHistoColl_Skim_noIso_wiTrigger, baselineObjectSelectionCollection_noIso,weight);
	  fillHistoCollection (myHistoColl_Skim_looseIso_wiTrigger, baselineObjectSelectionCollection_looseIso,weight);
	  fillHistoCollection (myHistoColl_Skim_mediumIso_wiTrigger, baselineObjectSelectionCollection_mediumIso,weight);
	  fillHistoCollection (myHistoColl_Skim_tightIso_wiTrigger, baselineObjectSelectionCollection_tightIso,weight);
	}
// ---------------------
// -- Signal Region --
// ---------------------

Selection Signal("Signal"); //label and initialisation
Signal.InputCollection 		= &TauTightIsoObjectSelectionCollection;        //input collection
Signal.OutputCollection 	= &myHistoColl_SignalRegion_woTrigger;        //output collection
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

//Requiring trigger fired
if ( baselineObjectSelectionCollection_noIso.passedTrigger     ) {
	Signal.OutputCollection 	= &myHistoColl_SignalRegion_wiTrigger;        //output collection
	Signal.select();        //do selection, fill histograms
}

if(Signal.passed) h2_Trigger->Fill(TauTightIsoObjectSelectionCollection.passedTrigger, 1);


//Clearing Object Collections
TauTightIsoObjectSelectionCollection.clear();
Tau1TightIsoObjectSelectionCollection.clear();
TauMediumIsoObjectSelectionCollection.clear();
TauLooseIsoObjectSelectionCollection.clear();
TauNoIsoObjectSelectionCollection.clear();
baselineObjectSelectionCollection_noIso.clear();
baselineObjectSelectionCollection_looseIso.clear(); 
baselineObjectSelectionCollection_mediumIso.clear();
baselineObjectSelectionCollection_tightIso.clear();
}
  stream.close();
  ofile.close();
  return 0;
}

