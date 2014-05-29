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
#include "CutConfiguration.h"
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
	TH1::SetDefaultSumw2();
	
	TFile file_PU("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/PUreweightHistogram.root", "read");
	
	TH1F *PUweights = (TH1F*)file_PU.Get("ratio");
	
	double weight = 1.;

	MyHistoCollection myHistoColl_Skim 		(ofile.file_, "Skim");
	
	MyHistoCollection myHistoColl_OS_SignalRegion	(ofile.file_, "OS_SignalRegion");        
	
	MyHistoCollection myHistoColl_LS_SignalRegion	(ofile.file_, "LS_SignalRegion");        

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

//PU weights
if(!eventhelper_isRealData){
 //weight=PUweights->GetBinContent(PUweights->FindBin(PileupSummaryInfo_getPU_NumInteractions[0]));
 //std::cout<<"NVtx="<<PileupSummaryInfo_getPU_NumInteractions[0]<<", weight="<<weight<<std::endl;
} 

baselineObjectSelectionCollection.NVtx 		= nrecoVertex;
TauTightIsoObjectSelectionCollection.NVtx 	= nrecoVertex;
Tau1TightIsoObjectSelectionCollection.NVtx 	= nrecoVertex;
TauMediumIsoObjectSelectionCollection.NVtx 	= nrecoVertex;
TauLooseIsoObjectSelectionCollection.NVtx 	= nrecoVertex;
TauNoIsoObjectSelectionCollection.NVtx 		= nrecoVertex;

baselineObjectSelectionCollection.PUinteractions 	= PileupSummaryInfo_getPU_NumInteractions[0];
TauTightIsoObjectSelectionCollection.PUinteractions 	= PileupSummaryInfo_getPU_NumInteractions[0];
Tau1TightIsoObjectSelectionCollection.PUinteractions 	= PileupSummaryInfo_getPU_NumInteractions[0];
TauMediumIsoObjectSelectionCollection.PUinteractions 	= PileupSummaryInfo_getPU_NumInteractions[0];
TauLooseIsoObjectSelectionCollection.PUinteractions 	= PileupSummaryInfo_getPU_NumInteractions[0];
TauNoIsoObjectSelectionCollection.PUinteractions 	= PileupSummaryInfo_getPU_NumInteractions[0];

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
	     || (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v1 == 1)

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
	  bool debug = false;
	  if (( met2[0].pt > 37.439)&&( met2[0].pt < 37.44) )debug = true;
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronMediumMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonLoose3 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFindingNewDMs > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
            baselineObjectSelectionCollection.tau.push_back(&tau[t]);
	    if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT  <= 0.5)) tights.push_back(t);
	    else if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT  <= 0.5)) mediums.push_back(t);
	    else if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT  <= 0.5)) looses.push_back(t);
	    //else nones.push_back(t);
          }
	  if(tights.size()==2) for(unsigned int t =0;t<tights.size();++t) {int i=tights[t]; TauTightIsoObjectSelectionCollection.tau.push_back(&tau[i]);}
	  else if(tights.size()==1 && (mediums.size()+looses.size()+nones.size())==1) {tights.insert(tights.end(),mediums.begin(), mediums.end()); tights.insert(tights.end(),looses.begin(), looses.end()); tights.insert(tights.end(),nones.begin(), nones.end()); for(unsigned int t =0;t<tights.size();++t) {int i=tights[t]; Tau1TightIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(mediums.size()>=1 && (mediums.size()+looses.size()+nones.size())==2) {mediums.insert(mediums.end(), looses.begin(), looses.end()); mediums.insert(mediums.end(), nones.begin(), nones.end()); for(unsigned int t =0;t<mediums.size();++t) {int i=mediums[t]; TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(looses.size()>=1 && (looses.size()+nones.size())==2) {looses.insert(looses.end(), nones.begin(), nones.end()); for(unsigned int t =0;t<looses.size();++t) {int i=looses[t]; TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(nones.size()==2) for(unsigned int t =0;t<nones.size();++t) {int i=nones[t]; TauNoIsoObjectSelectionCollection.tau.push_back(&tau[i]);}
	  
	  realTauMass(TauTightIsoObjectSelectionCollection);
	  realTauMass(Tau1TightIsoObjectSelectionCollection);
	  realTauMass(TauMediumIsoObjectSelectionCollection);
	  realTauMass(TauLooseIsoObjectSelectionCollection);
	  realTauMass(TauNoIsoObjectSelectionCollection);
	  
	  if ( debug ) {
		cout << "------- Taus after object selection--------"<<endl;
		for (unsigned int i = 0; i < TauTightIsoObjectSelectionCollection.tau.size(); i++ ){
			cout << "Jet#" << i << ": Pt " << TauTightIsoObjectSelectionCollection.tau[i]->pt << 
						" Eta " << TauTightIsoObjectSelectionCollection.tau[i]->eta <<
						" Phi " << TauTightIsoObjectSelectionCollection.tau[i]->phi <<
						" Energy " << TauTightIsoObjectSelectionCollection.tau[i]->energy << endl;
		}
		cout << endl;
	  }

          // jet && bjet selection
	  // ? id ?
	  if ( debug ) {
		cout << "-------Jets before object selection--------"<<endl;
		for (unsigned int i = 0; i < jet.size(); i++ ){
			cout << "Jet#" << i << ": Pt " << jet[i].pt << 
						" Eta " << jet[i].eta <<
						" Phi " << jet[i].phi <<
						" Energy " << jet[i].energy << endl;
		}
		cout << endl;	
	  } 
	  for(unsigned int j = 0;j<jet.size();++j){
	    if (debug) cout << endl;
	    if (debug) cout << "Object selection Cuts for Jet#" << j << ":" <<endl;
	    if(!(      jet[j].pt >= 30.                                                	)) {if (debug) cout << "----Pt cut FAILED" <<endl;continue;}  // Original value 20
	    if (debug) cout << "----Pt cut passed" <<endl;
	    if(!(      fabs(jet[j].eta) <= 5.0                                          )) {if (debug) cout << "----Eta cut FAILED" <<endl;continue;}
	    if (debug) cout << "----Eta cut passed" <<endl;
	    double baseDistance = TauJetMinDistance(baselineObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double mainDistance = TauJetMinDistance(TauTightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double T1Distance = TauJetMinDistance(Tau1TightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double mediumDistance = TauJetMinDistance(TauMediumIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double looseDistance = TauJetMinDistance(TauLooseIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double NoDistance = TauJetMinDistance(TauNoIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
            bool jetid=true;
	    bool failcutnotification = false;
	    if(!(      (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99      )) jetid=false;
	    if (debug && jetid) cout << "----(neutralHadE+HFHadE)/energy cut passed" <<endl;
	    if (debug && !(jetid) ) { cout << "(neutralHadE+HFHadE)/energy = " << ((jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy) <<endl;}
	    if (debug && !(jetid) && !(failcutnotification)) {failcutnotification = true; cout << "----(neutralHadE+HFHadE)/energy cut FAILED" <<endl;}
	    if(!(      jet[j].neutralEmEnergyFraction < 0.99                                            )) jetid=false;
	    if (debug && jetid) cout << "----neutralEmEnergyFraction cut passed" <<endl;
	    if (debug && !(jetid) && !(failcutnotification)) {failcutnotification = true; cout << "----neutralEmEnergyFraction cut FAILED" <<endl;}
	    if(!(      jet[j].numberOfDaughters > 1                                                     )) jetid=false;
	    if (debug && jetid) cout << "----numberOfDaughters cut passed" <<endl;
	    if (debug && !(jetid) && !(failcutnotification)) {failcutnotification = true; cout << "----numberOfDaughters cut FAILED" <<endl;}
	    if(fabs(jet[j].eta) < 2.4) {
              if(!(      jet[j].chargedHadronEnergyFraction > 0                        			)) jetid=false;
	      if (debug && jetid) cout << "----eta < 2.4 + chargedHadronEnergyFraction cut passed" <<endl;
	    if (debug && !(jetid) && !(failcutnotification)) {failcutnotification = true; cout << "----eta < 2.4 + chargedHadronEnergyFraction cut FAILED" <<endl;}
              if(!(      jet[j].chargedEmEnergyFraction < 0.99                            		)) jetid=false;
	      if (debug && jetid) cout << "----eta < 2.4 + chargedEmEnergyFraction cut passed" <<endl;
	    if (debug && !(jetid) && !(failcutnotification)) {failcutnotification = true; cout << "----eta < 2.4 + chargedEmEnergyFraction cut FAILED" <<endl;}
              if(!(      jet[j].chargedMultiplicity > 0                                 		)) jetid=false;
	      if (debug && jetid) cout << "----eta < 2.4 + chargedMultiplicity cut passed" <<endl;
	    if (debug && !(jetid) && !(failcutnotification)) {failcutnotification = true; cout << "----eta < 2.4 + chargedMultiplicity cut FAILED" <<endl;}
            }
            if(      /*jet[j].pt >= 50.  &&*/ jetid		){
              if(	baseDistance >= 0.3	) baselineObjectSelectionCollection.jet.push_back(&jet[j]);	
	      if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      if (debug && jetid ) cout << "Jet-Tau distance: " << mainDistance << endl;
	      if (debug && jetid && mainDistance >= 0.3) cout << "----Tau isolation cut passed" <<endl;
	      if (debug && !(mainDistance >= 0.3) && !(failcutnotification)) {failcutnotification = true; cout << "----Tau isolation cut FAILED" <<endl;}
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
	      if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
            }
	  }
	  //MET selection
	  baselineObjectSelectionCollection.met2.push_back(&met2[0]);
	  TauTightIsoObjectSelectionCollection.met2.push_back(&met2[0]);
	  Tau1TightIsoObjectSelectionCollection.met2.push_back(&met2[0]);
	  TauMediumIsoObjectSelectionCollection.met2.push_back(&met2[0]);
	  TauLooseIsoObjectSelectionCollection.met2.push_back(&met2[0]);
	  TauNoIsoObjectSelectionCollection.met2.push_back(&met2[0]);

	  //Event Count
	  ofile.count("NoCuts");

	  // ------------------------
	  // -- Skimming Studies   --
	  // ------------------------

	  //myHistoColl_Skim.h_count->Fill("NoCuts",0);
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",0);

	  //NoCuts
	  //myHistoColl_Skim.h_count->Fill("NoCuts",1);

	  //AtLeast2Loostau
	  //if(!(             ( (int)baselineObjectSelectionCollection.tau.size() >= 2 )                 )) break;
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",1);

	  //fillHistoCollection (myHistoColl_Skim, baselineObjectSelectionCollection,weight);



//set sign	
bool LS=false; 	
	
// ---------------------
// -- Signal Region --
// ---------------------
Selection OS_Signal("OS_Signal"); //label and initialisation
OS_Signal.InputCollection 		= &TauTightIsoObjectSelectionCollection;//input collection
OS_Signal.OutputCollection 		= &myHistoColl_OS_SignalRegion;        	//output collection
OS_Signal.RealData        		= eventhelper_isRealData;        	//pass information if event is real data
OS_Signal.RunData        		= false;        			//real data allowed
OS_Signal.RequireTriggers          	= true;       				//require at least one of the triggers fired
OS_Signal.weight        		= weight;      				//event weight
CutConfiguration(&OS_Signal, true, LS); 					//selection, VBF, LS
OS_Signal.METMin = 30.;

//OS_Signal.select();        							//do selection, fill histograms

(myHistoColl_OS_SignalRegion).h_count->Fill("NoCuts",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("TriggerRequirement",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("AtLeastNtaus",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("DiTauDeltaRCut", 0);
(myHistoColl_OS_SignalRegion).h_count->Fill("DiTauSignCut",0);	  
(myHistoColl_OS_SignalRegion).h_count->Fill("NoBTag",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("MinMETCut",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("LeadJetCut",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("SecondJetCut",0);	  
(myHistoColl_OS_SignalRegion).h_count->Fill("DiJetDeltaRCut",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("DiJetInvMassCut",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("DiJetEtaSignCut",0);
(myHistoColl_OS_SignalRegion).h_count->Fill("DiJetDetaCut",0);	  

while (true) {
	(myHistoColl_OS_SignalRegion).h_count->Fill("NoCuts",weight);
	if(!(TauTightIsoObjectSelectionCollection).passedTrigger) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("TriggerRequirement",weight);
	  
	//Tau requirements
	  
	if(!((int)(TauTightIsoObjectSelectionCollection).tau.size()  >= 2 )) break;
		else {
		(myHistoColl_OS_SignalRegion).h_count->Fill("AtLeastNtaus",weight);
		}

	//find ditau properties
	TauProperties Inv2t = Inv2tMassIndex((TauTightIsoObjectSelectionCollection));

	if(!(Inv2t.dR       >       0.3)) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("DiTauDeltaRCut", weight);

	if(!(Inv2t.charge   ==   -1 )) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("DiTauSignCut",weight);
	  
	if(((int)(TauTightIsoObjectSelectionCollection).bjet.size() > 0 )) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("NoBTag",weight);

	if(!( (double)(TauTightIsoObjectSelectionCollection).met2[0]->pt) > 30.) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("MinMETCut",weight);

	if (( (TauTightIsoObjectSelectionCollection).met2[0]->pt > 37.439)&&( (TauTightIsoObjectSelectionCollection).met2[0]->pt < 37.44) ) {
		cout << endl;
		cout << "Jets used after object selection for VB selection" << endl;
		for (unsigned int i = 0; i < (TauTightIsoObjectSelectionCollection).jet.size(); i++ ){
		
			cout << "Jet#" << i << ": Pt " << (double)(TauTightIsoObjectSelectionCollection).jet[i]->pt << 
						" Eta " << (double)(TauTightIsoObjectSelectionCollection).jet[i]->eta <<
						" Phi " << (double)(TauTightIsoObjectSelectionCollection).jet[i]->phi <<
						" Energy " << (double)(TauTightIsoObjectSelectionCollection).jet[i]->energy << endl;
		
		}
	
	
	}

	//find index of leading jets
	pair<unsigned int,unsigned int> jetIndex=LeadingJets((TauTightIsoObjectSelectionCollection));

	//old leading jet cuts version
	
	//LeadJet
	if (jetIndex.first==99999) break;
	double leadJetPt = (TauTightIsoObjectSelectionCollection).jet[jetIndex.first]->pt;
	double leadJetEta = (TauTightIsoObjectSelectionCollection).jet[jetIndex.first]->eta;
	bool leadJet = true;
	if(!(fabs(leadJetEta)	<	5.))			leadJet = false;
	if(!(leadJetPt		>=	30.))			leadJet = false;
	if(!leadJet) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("LeadJetCut",weight);


	//SubLeadJet
	if (jetIndex.second==99999) break;
	double subLeadJetPt = (TauTightIsoObjectSelectionCollection).jet[jetIndex.second]->pt;
	double subLeadJetEta = (TauTightIsoObjectSelectionCollection).jet[jetIndex.second]->eta;
	bool subLeadJet = true;
	if(!(fabs(subLeadJetEta)	<	5.))			subLeadJet = false;
	if(!subLeadJet) break; 
		else (myHistoColl_OS_SignalRegion).h_count->Fill("SecondJetCut",weight);


	//new highest invariant mass jets version
	//find properties of dijet-system
	MassAndIndex Inv2j = Inv2jMassIndex((TauTightIsoObjectSelectionCollection));

	//LeadJet
	//double leadJetPt = (TauTightIsoObjectSelectionCollection).jet[Inv2j.first]->pt;
	//double leadJetEta = (TauTightIsoObjectSelectionCollection).jet[Inv2j.first]->eta;
	//SubLeadJet
	//double subLeadJetPt = (TauTightIsoObjectSelectionCollection).jet[Inv2j.second]->pt;
	//double subLeadJetEta = (TauTightIsoObjectSelectionCollection).jet[Inv2j.second]->eta;	  	  

	//check jet pt requirements

	bool DiJetDr = true;
	if(!(Inv2j.dR		>=	3.9)) 			DiJetDr = false; //check dijet separation

	if(!DiJetDr) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("DiJetDeltaRCut",weight);

	bool DiJetMass = true;
	if(!(Inv2j.Mass		>	250.))		DiJetMass = false; //check minimal dijet inv. mass

	if(!DiJetMass) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("DiJetInvMassCut",weight);

	if(Inv2j.signEta != -1) break;					//check whether jets go in opposite directions in the detector
		else (myHistoColl_OS_SignalRegion).h_count->Fill("DiJetEtaSignCut",weight);

	bool DiJetDeta = true;
	if(!(Inv2j.dEta		>	4.2))			DiJetDeta = false; //check eta separation of jets

	if(!DiJetDeta) break;
		else (myHistoColl_OS_SignalRegion).h_count->Fill("DiJetDetaCut",weight);
	break;
}

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

