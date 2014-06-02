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
  
  /*TH1F* pTchargedHad = new TH1F("pTchargedHad", "leading charged hadron candidate momentum", 100, 0., 100.);
  TH1F* eVeto = new TH1F("eVeto", "electron veto discriminator", 2, -0.5, 1.5);
  TH1F* MuVeto = new TH1F("MuVeto", "muon veto discriminator", 2, -0.5, 1.5);
  TH2F* DMFandProng = new TH2F("DMFandProng", "DecayModeFinding and prongsize", 2, -0.5, 1.5, 10, 0., 10.);
  DMFandProng->GetXaxis()->SetTitle("DecayModeFinding");
  DMFandProng->GetYaxis()->SetTitle("prongs.size()");
  TH1F* TightIso = new TH1F("TightIso", "TightIsolation discriminator", 2, -0.5, 1.5);*/

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------
	TH1::SetDefaultSumw2();
	
	//TFile file_PU("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/PUreweightHistogram.root", "read");
	TFile file_PUdata("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/DataPUFile_Full2012.root", "read");
	TFile file_PUmc("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/S10MC_PUFile.root", "read");
	
	//TH1F *PUweights = (TH1F*)file_PU.Get("ratio");
	TH1F *PUweights = (TH1F*)file_PUmc.Get("analyzeHiMassTau/NVertices_0");
	PUweights->Scale(1/PUweights->Integral());
	TH1F *PUdata = (TH1F*)file_PUdata.Get("analyzeHiMassTau/NVertices_0");
	PUdata->Scale(1/PUdata->Integral());
	
	PUweights->Divide(PUdata);
	
	double weight = 1.;

	MyHistoCollection myHistoColl_Skim 		(ofile.file_, "Skim");
	
	MyHistoCollection myHistoColl_OS_SignalRegion	(ofile.file_, "OS_SignalRegion");        
	MyHistoCollection myHistoColl_OS_CR1 		(ofile.file_, "OS_Ztautau_CR1");
	MyHistoCollection myHistoColl_OS_CR2 		(ofile.file_, "OS_Central_invertedVBF_2TightIso_CR2");
	MyHistoCollection myHistoColl_OS_CR3 		(ofile.file_, "OS_Central_1TightIso_CR3");
	MyHistoCollection myHistoColl_OS_CR4 		(ofile.file_, "OS_Central_invertedVBF_1TightIso_CR4");
	MyHistoCollection myHistoColl_OS_CR5 		(ofile.file_, "OS_Central_AntiTightIso_CR5");
	MyHistoCollection myHistoColl_OS_CR6 		(ofile.file_, "OS_Central_invertedVBF_AntiTightIso_CR6");
	MyHistoCollection myHistoColl_OS_CR7 		(ofile.file_, "OS_Central_AntiMediumIso_CR7");
	MyHistoCollection myHistoColl_OS_CR8 		(ofile.file_, "OS_Central_invertedVBF_AntiMediumIso_CR8");
	MyHistoCollection myHistoColl_OS_CR9 		(ofile.file_, "OS_Central_AntiLooseIso_CR9");
	MyHistoCollection myHistoColl_OS_CR10 		(ofile.file_, "OS_Central_invertedVBF_AntiLooseIso_CR10");
	
	MyHistoCollection myHistoColl_LS_SignalRegion	(ofile.file_, "LS_SignalRegion");        
	MyHistoCollection myHistoColl_LS_CR1 		(ofile.file_, "LS_Ztautau_CR1");
	MyHistoCollection myHistoColl_LS_CR2 		(ofile.file_, "LS_Central_invertedVBF_2TightIso_CR2");
	MyHistoCollection myHistoColl_LS_CR3 		(ofile.file_, "LS_Central_1TightIso_CR3");
	MyHistoCollection myHistoColl_LS_CR4 		(ofile.file_, "LS_Central_invertedVBF_1TightIso_CR4");
	MyHistoCollection myHistoColl_LS_CR5 		(ofile.file_, "LS_Central_AntiTightIso_CR5");
	MyHistoCollection myHistoColl_LS_CR6 		(ofile.file_, "LS_Central_invertedVBF_AntiTightIso_CR6");
	MyHistoCollection myHistoColl_LS_CR7 		(ofile.file_, "LS_Central_AntiMediumIso_CR7");
	MyHistoCollection myHistoColl_LS_CR8 		(ofile.file_, "LS_Central_invertedVBF_AntiMediumIso_CR8");
	MyHistoCollection myHistoColl_LS_CR9 		(ofile.file_, "LS_Central_AntiLooseIso_CR9");
	MyHistoCollection myHistoColl_LS_CR10 		(ofile.file_, "LS_Central_invertedVBF_AntiLooseIso_CR10");	

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

 weight=PUweights->GetBinContent(PUweights->FindBin(PileupSummaryInfo_getTrueNumInteractions[0]));
 std::cout<<"NVtx="<<PileupSummaryInfo_getTrueNumInteractions[0]<<", weight="<<weight<<std::endl;
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
	     //|| (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v1 == 1)

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
            if(!(       tau[t].tauID_againstElectronMediumMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonLoose3 > 0.5                        				)) continue;
	    if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       (tau[t].tauID_decayModeFindingNewDMs > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	  
            baselineObjectSelectionCollection.tau.push_back(&tau[t]);
	    /*pTchargedHad->Fill(tau[t].leadPFChargedHadrCand_pt);
	  eVeto->Fill(tau[t].tauID_againstElectronMediumMVA5);
	  MuVeto->Fill(tau[t].tauID_againstMuonLoose3);
	  DMFandProng->Fill(tau[t].tauID_decayModeFindingNewDMs,tau[t].signalPFChargedHadrCands_size);
	  TightIso->Fill(tau[t].tauID_byTightIsolationMVA3newDMwLT);*/
	    
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
              if(!(      jet[j].chargedMultiplicity > 0							)) jetid=false;
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
	      if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
            }
	  }

	  //MET selection
	  baselineObjectSelectionCollection.met.push_back(&met2[0]);
	  TauTightIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  Tau1TightIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  TauMediumIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  TauNoIsoObjectSelectionCollection.met.push_back(&met2[0]);

	  //Event Count
	  ofile.count("NoCuts");

	  // ------------------------
	  // -- Skimming Studies   --
	  // ------------------------

	  myHistoColl_Skim.h_count->Fill("NoCuts",0);
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",0);

	  //NoCuts
	  myHistoColl_Skim.h_count->Fill("NoCuts",1);

	  //AtLeast2Loostau
	  //if(!(             ( (int)baselineObjectSelectionCollection.tau.size() >= 2 )                 )) break;
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",1);

	  fillHistoCollection (myHistoColl_Skim, baselineObjectSelectionCollection,weight);

//set sign	
bool LS=true; 	
	
// ---------------------
// -- Signal Region --
// ---------------------
if(TauTightIsoObjectSelectionCollection.jet.size()>=2){
Selection LS_Signal("LS_Signal"); 					//label and initialisation
LS_Signal.InputCollection 	= &TauTightIsoObjectSelectionCollection;//input collection
LS_Signal.OutputCollection 	= &myHistoColl_LS_SignalRegion;        	//output collection
LS_Signal.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
LS_Signal.RunData        	= false;        			//real data allowed
LS_Signal.RequireTriggers       = true;       				//require at least one of the triggers fired
LS_Signal.weight        	= weight;      				//event weight
CutConfiguration(&LS_Signal, true, LS); 				//selection, VBF, LS
LS_Signal.METMin = 30.;

LS_Signal.select(false);        						//do selection, fill histograms

if(LS_Signal.passed) h2_Trigger->Fill(TauTightIsoObjectSelectionCollection.passedTrigger, 1);

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection InvertedVBF_LS_CR2("InvertedVBF_LS_CR2"); 				//label and initialisation
InvertedVBF_LS_CR2.InputCollection 	= &TauTightIsoObjectSelectionCollection;//input collection
InvertedVBF_LS_CR2.OutputCollection 	= &myHistoColl_LS_CR2;        		//output collection
InvertedVBF_LS_CR2.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_LS_CR2.RunData        	= true;        				//real data allowed
InvertedVBF_LS_CR2.RequireTriggers      = true;       				//require at least one of the triggers fired
InvertedVBF_LS_CR2.weight        	= weight;      				//event weight
CutConfiguration(&InvertedVBF_LS_CR2, false, LS); 				//selection, VBF, LS
InvertedVBF_LS_CR2.METMin = 30.;

InvertedVBF_LS_CR2.select(false);        						//do selection, fill histograms

if(InvertedVBF_LS_CR2.passed) h2_Trigger->Fill(TauTightIsoObjectSelectionCollection.passedTrigger, 2);
}

// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------
if(Tau1TightIsoObjectSelectionCollection.jet.size()>=2){
Selection oneTightTau_LS_CR3("oneTightTau_LS_CR3"); 					//label and initialisation
oneTightTau_LS_CR3.InputCollection 	= &Tau1TightIsoObjectSelectionCollection;	//input collection
oneTightTau_LS_CR3.OutputCollection 	= &myHistoColl_LS_CR3;        			//output collection
oneTightTau_LS_CR3.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
oneTightTau_LS_CR3.RunData        	= true;        					//real data allowed
oneTightTau_LS_CR3.RequireTriggers      = true;       					//require at least one of the triggers fired
oneTightTau_LS_CR3.weight        	= weight;      					//event weight
CutConfiguration(&oneTightTau_LS_CR3, true, LS); 					//selection, VBF, LS

oneTightTau_LS_CR3.select(false);        							//do selection, fill histograms

// ---------------------------------------------
// -- CENTRAL + InvertedVBF + 1 Tight Tau CR4 --
// ---------------------------------------------
Selection InvertedVBF_oneTightTau_LS_CR4("InvertedVBF_oneTightTau_LS_CR4"); 			//label and initialisation
InvertedVBF_oneTightTau_LS_CR4.InputCollection 	= &Tau1TightIsoObjectSelectionCollection;       //input collection
InvertedVBF_oneTightTau_LS_CR4.OutputCollection = &myHistoColl_LS_CR4;        			//output collection
InvertedVBF_oneTightTau_LS_CR4.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_oneTightTau_LS_CR4.RunData        	= true;        					//real data allowed
InvertedVBF_oneTightTau_LS_CR4.RequireTriggers  = true;       					//require at least one of the triggers fired
InvertedVBF_oneTightTau_LS_CR4.weight        	= weight;      					//event weight
CutConfiguration(&InvertedVBF_oneTightTau_LS_CR4, false, LS); 					//selection, VBF, LS

InvertedVBF_oneTightTau_LS_CR4.select(false);        						//do selection, fill histograms
}

// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------
if(TauMediumIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiTightTau_LS_CR5("AntiTightTau_LS_CR5"); 					//label and initialisation
AntiTightTau_LS_CR5.InputCollection 	= &TauMediumIsoObjectSelectionCollection;	//input collection
AntiTightTau_LS_CR5.OutputCollection 	= &myHistoColl_LS_CR5;        			//output collection
AntiTightTau_LS_CR5.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
AntiTightTau_LS_CR5.RunData        	= true;        					//real data allowed
AntiTightTau_LS_CR5.RequireTriggers     = true;       					//require at least one of the triggers fired
AntiTightTau_LS_CR5.weight        	= weight;      					//event weight
CutConfiguration(&AntiTightTau_LS_CR5, true, LS); 					//selection, VBF, LS

AntiTightTau_LS_CR5.select(false);        							//do selection, fill histograms

// ------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Tight Tau CR6 --
// ------------------------------------------------

Selection InvertedVBF_AntiTightTau_LS_CR6("InvertedVBF_AntiTightTau_LS_CR6"); 				//label and initialisation
InvertedVBF_AntiTightTau_LS_CR6.InputCollection 	= &TauMediumIsoObjectSelectionCollection;	//input collection
InvertedVBF_AntiTightTau_LS_CR6.OutputCollection 	= &myHistoColl_LS_CR6;        			//output collection
InvertedVBF_AntiTightTau_LS_CR6.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_AntiTightTau_LS_CR6.RunData        		= true;        					//real data allowed
InvertedVBF_AntiTightTau_LS_CR6.RequireTriggers         = true;       					//require at least one of the triggers fired
InvertedVBF_AntiTightTau_LS_CR6.weight        		= weight;      					//event weight
CutConfiguration(&InvertedVBF_AntiTightTau_LS_CR6, false, LS); 						//selection, VBF, LS

InvertedVBF_AntiTightTau_LS_CR6.select(false);        							//do selection, fill histograms
}	

// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------
if(TauLooseIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiMediumTau_LS_CR7("AntiMediumTau_LS_CR7"); 			//label and initialisation
AntiMediumTau_LS_CR7.InputCollection 	= &TauLooseIsoObjectSelectionCollection;//input collection
AntiMediumTau_LS_CR7.OutputCollection 	= &myHistoColl_LS_CR7;        		//output collection
AntiMediumTau_LS_CR7.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiMediumTau_LS_CR7.RunData        	= true;        				//real data allowed
AntiMediumTau_LS_CR7.RequireTriggers    = true;       				//require at least one of the triggers fired
AntiMediumTau_LS_CR7.weight        	= weight;      				//event weight
CutConfiguration(&AntiMediumTau_LS_CR7, true, LS); 				//selection, VBF, LS

AntiMediumTau_LS_CR7.select(false);        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Medium Tau CR8 --
// -------------------------------------------------

Selection InvertedVBF_AntiMediumTau_LS_CR8("InvertedVBF_AntiMediumTauLS_CR8"); 			//label and initialisation
InvertedVBF_AntiMediumTau_LS_CR8.InputCollection 	= &TauLooseIsoObjectSelectionCollection;//input collection
InvertedVBF_AntiMediumTau_LS_CR8.OutputCollection 	= &myHistoColl_LS_CR8;        		//output collection
InvertedVBF_AntiMediumTau_LS_CR8.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiMediumTau_LS_CR8.RunData        	= true;        				//real data allowed
InvertedVBF_AntiMediumTau_LS_CR8.RequireTriggers        = true;       				//require at least one of the triggers fired
InvertedVBF_AntiMediumTau_LS_CR8.weight        		= weight;      				//event weight
CutConfiguration(&InvertedVBF_AntiMediumTau_LS_CR8, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiMediumTau_LS_CR8.select(false);        						//do selection, fill histograms
}

// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------
if(TauNoIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiLooseTau_LS_CR9("AntiLooseTauLS_CR9"); 				//label and initialisation
AntiLooseTau_LS_CR9.InputCollection 	= &TauNoIsoObjectSelectionCollection;	//input collection
AntiLooseTau_LS_CR9.OutputCollection 	= &myHistoColl_LS_CR9;        		//output collection
AntiLooseTau_LS_CR9.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiLooseTau_LS_CR9.RunData        	= true;        				//real data allowed
AntiLooseTau_LS_CR9.RequireTriggers     = true;       				//require at least one of the triggers fired
AntiLooseTau_LS_CR9.weight        	= weight;      				//event weight
CutConfiguration(&AntiLooseTau_LS_CR9, true, LS); 				//selection, VBF, LS

AntiLooseTau_LS_CR9.select(false);        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Loose Tau CR10 --
// -------------------------------------------------

Selection InvertedVBF_AntiLooseTau_LS_CR10("InvertedVBF_AntiLooseTauLS_CR10"); 			//label and initialisation
InvertedVBF_AntiLooseTau_LS_CR10.InputCollection 	= &TauNoIsoObjectSelectionCollection;   //input collection
InvertedVBF_AntiLooseTau_LS_CR10.OutputCollection 	= &myHistoColl_LS_CR10;        		//output collection
InvertedVBF_AntiLooseTau_LS_CR10.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiLooseTau_LS_CR10.RunData        	= true;        				//real data allowed
InvertedVBF_AntiLooseTau_LS_CR10.RequireTriggers        = true;       				//require at least one of the triggers fired
InvertedVBF_AntiLooseTau_LS_CR10.weight        		= weight;      				//event weight
CutConfiguration(&InvertedVBF_AntiLooseTau_LS_CR10, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiLooseTau_LS_CR10.select(false);        						//do selection, fill histograms
}

// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_LS_CR1("Ztautau_LS_CR1"); //label and initialisation
Ztautau_LS_CR1.InputCollection 		= &TauTightIsoObjectSelectionCollection;//input collection
Ztautau_LS_CR1.OutputCollection 	= &myHistoColl_LS_CR1;        		//output collection
Ztautau_LS_CR1.RealData        		= eventhelper_isRealData;        	//pass information if event is real data
Ztautau_LS_CR1.RunData        		= true;        				//real data allowed
Ztautau_LS_CR1.NumberTauMin        	= 2;        				//require at least N tau
Ztautau_LS_CR1.NumberTauMax        	= 3;        				//require at less than N taus
Ztautau_LS_CR1.DiTauDeltaRmin        	= 0.3;        				//minimum delta R for tau pair
Ztautau_LS_CR1.DiTauInvMassMin        	= -1.;        				//minimum Di-tau-mass requirement
Ztautau_LS_CR1.DiTauInvMassMax        	= 90.;        				//maximum Di-tau-mass requirement
Ztautau_LS_CR1.DiTauSign        	= -1;        				//1 for LS and -1 for LS, 0 for no requirement
Ztautau_LS_CR1.Btag        		= 0;        				//number of btags required (exact -> 0 = none)
Ztautau_LS_CR1.METMin                   = -1.;      				// minimum MET requirement
Ztautau_LS_CR1.METMax                   = -1;       				// maximum MET requirement
Ztautau_LS_CR1.JetEtaMax        	= -1.;        				//maximum eta for jets, set to -1 for no requirement
Ztautau_LS_CR1.LeadJetPtMin        	= -1.;        				//minimum pt of lead jet, set to -1 for no requirement
Ztautau_LS_CR1.LeadJetPtMax        	= -1.;        				//maximum pt of lead jet, set to -1 for no requirement
Ztautau_LS_CR1.SubLeadJetPtMin        	= -1.;        				//minimum pt of sub lead jet, set to -1 for no requirement
Ztautau_LS_CR1.SubLeadJetPtMax        	= -1.;        				//maximum pt of sub lead jet, set to -1 for no requirement
Ztautau_LS_CR1.DiJetDrMin        	= -1.;        				//Dijet minimum delta R, set to -1 for no requirement
Ztautau_LS_CR1.DiJetDrMax        	= -1.;        				//Dijet maximum delta R, set to -1 for no requirement
Ztautau_LS_CR1.DiJetInvMassMin        	= -1.;        				//Dijet minimal invariant mass, set to -1 for no requirement
Ztautau_LS_CR1.DiJetInvMassMax        	= -1.;        				//Dijet maximum invariant mass, set to -1 for no requirement
Ztautau_LS_CR1.DiJetSignEta        	= 0;        				//Dijet sign eta_1*eta_2
Ztautau_LS_CR1.DiJetDetaMin        	= -1.;        				//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Ztautau_LS_CR1.DiJetDetaMax        	= -1.;        				//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Ztautau_LS_CR1.weight        		= weight;      				//event weight
Ztautau_LS_CR1.invertTauRequirements    = false;        			//invert number of taus requirement
Ztautau_LS_CR1.invertTauProperties      = false;        			//invert ditau properties (dR, sign)
Ztautau_LS_CR1.invertBtagRequirement    = false;        			//invert number of b-jets required
Ztautau_LS_CR1.invertJetRequirements    = false;        			//invert jet pt requirements
Ztautau_LS_CR1.invertDijetProperties    = false;        			//invert dijet system properties (dR, inv mass, sign eta, dEta)

Ztautau_LS_CR1.select(false);        						//do selection, fill histograms

//_____________________________________________
//-------------------OS SECTION----------------
//_____________________________________________

LS=false;

// ---------------------
// -- Signal Region --
// ---------------------
//if(TauTightIsoObjectSelectionCollection.jet.size()>=2){
Selection OS_Signal("OS_Signal"); //label and initialisation
OS_Signal.InputCollection 		= &TauTightIsoObjectSelectionCollection;//input collection
OS_Signal.OutputCollection 		= &myHistoColl_OS_SignalRegion;        	//output collection
OS_Signal.RealData        		= eventhelper_isRealData;        	//pass information if event is real data
OS_Signal.RunData        		= false;        			//real data allowed
OS_Signal.RequireTriggers          	= true;       				//require at least one of the triggers fired
OS_Signal.weight        		= weight;      				//event weight
CutConfiguration(&OS_Signal, true, LS); 					//selection, VBF, LS
OS_Signal.METMin = 30.;

OS_Signal.select(false);        							//do selection, fill histograms

if(OS_Signal.passed) h2_Trigger->Fill(TauTightIsoObjectSelectionCollection.passedTrigger, 1);

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection InvertedVBF_OS_CR2("InvertedVBF_OS_CR2"); 				//label and initialisation
InvertedVBF_OS_CR2.InputCollection 	= &TauTightIsoObjectSelectionCollection;//input collection
InvertedVBF_OS_CR2.OutputCollection 	= &myHistoColl_OS_CR2;        		//output collection
InvertedVBF_OS_CR2.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_OS_CR2.RunData        	= true;        				//real data allowed
InvertedVBF_OS_CR2.RequireTriggers      = true;       				//require at least one of the triggers fired
InvertedVBF_OS_CR2.weight        	= weight;      				//event weight
CutConfiguration(&InvertedVBF_OS_CR2, false, LS); 				//selection, VBF, LS
InvertedVBF_OS_CR2.METMin = 30.;

InvertedVBF_OS_CR2.select(false);        						//do selection, fill histograms

if(InvertedVBF_OS_CR2.passed) h2_Trigger->Fill(TauTightIsoObjectSelectionCollection.passedTrigger, 2);
//}

// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------
if(Tau1TightIsoObjectSelectionCollection.jet.size()>=2){
Selection oneTightTau_OS_CR3("oneTightTau_OS_CR3"); 					//label and initialisation
oneTightTau_OS_CR3.InputCollection 	= &Tau1TightIsoObjectSelectionCollection;	//input collection
oneTightTau_OS_CR3.OutputCollection 	= &myHistoColl_OS_CR3;        			//output collection
oneTightTau_OS_CR3.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
oneTightTau_OS_CR3.RunData        	= true;        					//real data allowed
oneTightTau_OS_CR3.RequireTriggers      = true;       					//require at least one of the triggers fired
oneTightTau_OS_CR3.weight        	= weight;      					//event weight
CutConfiguration(&oneTightTau_OS_CR3, true, LS); 					//selection, VBF, LS

oneTightTau_OS_CR3.select(false);        							//do selection, fill histograms

// ---------------------------------------------
// -- CENTRAL + InvertedVBF + 1 Tight Tau CR4 --
// ---------------------------------------------
Selection InvertedVBF_oneTightTau_OS_CR4("InvertedVBF_oneTightTau_OS_CR4"); 				//label and initialisation
InvertedVBF_oneTightTau_OS_CR4.InputCollection 		= &Tau1TightIsoObjectSelectionCollection;       //input collection
InvertedVBF_oneTightTau_OS_CR4.OutputCollection 	= &myHistoColl_OS_CR4;        			//output collection
InvertedVBF_oneTightTau_OS_CR4.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_oneTightTau_OS_CR4.RunData        		= true;        					//real data allowed
InvertedVBF_oneTightTau_OS_CR4.RequireTriggers          = true;       					//require at least one of the triggers fired
InvertedVBF_oneTightTau_OS_CR4.weight        		= weight;      					//event weight
CutConfiguration(&InvertedVBF_oneTightTau_OS_CR4, false, LS); 						//selection, VBF, LS

InvertedVBF_oneTightTau_OS_CR4.select(false);        							//do selection, fill histograms
}

// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------
if(TauMediumIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiTightTau_OS_CR5("AntiTightTau_OS_CR5"); 						//label and initialisation
AntiTightTau_OS_CR5.InputCollection 		= &TauMediumIsoObjectSelectionCollection;	//input collection
AntiTightTau_OS_CR5.OutputCollection 		= &myHistoColl_OS_CR5;        			//output collection
AntiTightTau_OS_CR5.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
AntiTightTau_OS_CR5.RunData        		= true;        					//real data allowed
AntiTightTau_OS_CR5.RequireTriggers             = true;       					//require at least one of the triggers fired
AntiTightTau_OS_CR5.weight        		= weight;      					//event weight
CutConfiguration(&AntiTightTau_OS_CR5, true, LS); 						//selection, VBF, LS

AntiTightTau_OS_CR5.select(false);        								//do selection, fill histograms

// ------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Tight Tau CR6 --
// ------------------------------------------------

Selection InvertedVBF_AntiTightTau_OS_CR6("InvertedVBF_AntiTightTau_OS_CR6"); 				//label and initialisation
InvertedVBF_AntiTightTau_OS_CR6.InputCollection 	= &TauMediumIsoObjectSelectionCollection;	//input collection
InvertedVBF_AntiTightTau_OS_CR6.OutputCollection 	= &myHistoColl_OS_CR6;        			//output collection
InvertedVBF_AntiTightTau_OS_CR6.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_AntiTightTau_OS_CR6.RunData        		= true;        					//real data allowed
InvertedVBF_AntiTightTau_OS_CR6.RequireTriggers 	= true;       					//require at least one of the triggers fired
InvertedVBF_AntiTightTau_OS_CR6.weight        		= weight;      					//event weight
CutConfiguration(&InvertedVBF_AntiTightTau_OS_CR6, false, LS); 						//selection, VBF, LS

InvertedVBF_AntiTightTau_OS_CR6.select(false);        							//do selection, fill histograms
}	

// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------
if(TauLooseIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiMediumTau_OS_CR7("AntiMediumTau_OS_CR7"); 			//label and initialisation
AntiMediumTau_OS_CR7.InputCollection 	= &TauLooseIsoObjectSelectionCollection;//input collection
AntiMediumTau_OS_CR7.OutputCollection 	= &myHistoColl_OS_CR7;        		//output collection
AntiMediumTau_OS_CR7.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiMediumTau_OS_CR7.RunData        	= true;        				//real data allowed
AntiMediumTau_OS_CR7.RequireTriggers    = true;       				//require at least one of the triggers fired
AntiMediumTau_OS_CR7.weight        	= weight;      				//event weight
CutConfiguration(&AntiMediumTau_OS_CR7, true, LS); 				//selection, VBF, LS

AntiMediumTau_OS_CR7.select(false);        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Medium Tau CR8 --
// -------------------------------------------------

Selection InvertedVBF_AntiMediumTau_OS_CR8("InvertedVBF_AntiMediumTau_OS_CR8"); 		//label and initialisation
InvertedVBF_AntiMediumTau_OS_CR8.InputCollection 	= &TauLooseIsoObjectSelectionCollection;//input collection
InvertedVBF_AntiMediumTau_OS_CR8.OutputCollection 	= &myHistoColl_OS_CR8;        		//output collection
InvertedVBF_AntiMediumTau_OS_CR8.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiMediumTau_OS_CR8.RunData        	= true;        				//real data allowed
InvertedVBF_AntiMediumTau_OS_CR8.RequireTriggers        = true;       				//require at least one of the triggers fired
InvertedVBF_AntiMediumTau_OS_CR8.weight        		= weight;      				//event weight
CutConfiguration(&InvertedVBF_AntiMediumTau_OS_CR8, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiMediumTau_OS_CR8.select(false);        						//do selection, fill histograms
}

// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------
if(TauNoIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiLooseTau_OS_CR9("AntiLooseTau_OS_CR9"); 				//label and initialisation
AntiLooseTau_OS_CR9.InputCollection 	= &TauNoIsoObjectSelectionCollection;	//input collection
AntiLooseTau_OS_CR9.OutputCollection 	= &myHistoColl_OS_CR9;        		//output collection
AntiLooseTau_OS_CR9.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiLooseTau_OS_CR9.RunData        	= true;        				//real data allowed
AntiLooseTau_OS_CR9.RequireTriggers     = true;       				//require at least one of the triggers fired
AntiLooseTau_OS_CR9.weight        	= weight;      				//event weight
CutConfiguration(&AntiLooseTau_OS_CR9, true, LS); 				//selection, VBF, LS

AntiLooseTau_OS_CR9.select(false);        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Loose Tau CR10 --
// -------------------------------------------------

Selection InvertedVBF_AntiLooseTau_OS_CR10("InvertedVBF_AntiLooseTau_OS_CR10"); 		//label and initialisation
InvertedVBF_AntiLooseTau_OS_CR10.InputCollection 	= &TauNoIsoObjectSelectionCollection;   //input collection
InvertedVBF_AntiLooseTau_OS_CR10.OutputCollection 	= &myHistoColl_OS_CR10;        		//output collection
InvertedVBF_AntiLooseTau_OS_CR10.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiLooseTau_OS_CR10.RunData        	= true;        				//real data allowed
InvertedVBF_AntiLooseTau_OS_CR10.RequireTriggers        = true;       				//require at least one of the triggers fired
InvertedVBF_AntiLooseTau_OS_CR10.weight        		= weight;        			//event weight
CutConfiguration(&InvertedVBF_AntiLooseTau_OS_CR10, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiLooseTau_OS_CR10.select(false);        						//do selection, fill histograms
}

// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_OS_CR1("Ztautau_OS_CR1"); 						//label and initialisation
Ztautau_OS_CR1.InputCollection 		= &TauTightIsoObjectSelectionCollection;	//input collection
Ztautau_OS_CR1.OutputCollection 	= &myHistoColl_OS_CR1;        			//output collection
Ztautau_OS_CR1.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
Ztautau_OS_CR1.RunData        		= true;        					//real data allowed
Ztautau_OS_CR1.NumberTauMin        	= 2;        					//require at least N tau
Ztautau_OS_CR1.NumberTauMax        	= 3;        					//require at less than N taus
Ztautau_OS_CR1.DiTauDeltaRmin        	= 0.3;        					//minimum delta R for tau pair
Ztautau_OS_CR1.DiTauInvMassMin        	= -1.;        					//minimum Di-tau-mass requirement
Ztautau_OS_CR1.DiTauInvMassMax        	= 90.;        					//maximum Di-tau-mass requirement
Ztautau_OS_CR1.DiTauSign        	= -1;        					//1 for LS and -1 for OS, 0 for no requirement
Ztautau_OS_CR1.Btag        		= 0;        					//number of btags required (exact -> 0 = none)
Ztautau_OS_CR1.METMin                   = -1.;      					// minimum MET requirement
Ztautau_OS_CR1.METMax                   = -1;       					// maximum MET requirement
Ztautau_OS_CR1.JetEtaMax        	= -1.;        					//maximum eta for jets, set to -1 for no requirement
Ztautau_OS_CR1.LeadJetPtMin        	= -1.;        					//minimum pt of lead jet, set to -1 for no requirement
Ztautau_OS_CR1.LeadJetPtMax        	= -1.;        					//maximum pt of lead jet, set to -1 for no requirement
Ztautau_OS_CR1.SubLeadJetPtMin        	= -1.;        					//minimum pt of sub lead jet, set to -1 for no requirement
Ztautau_OS_CR1.SubLeadJetPtMax        	= -1.;        					//maximum pt of sub lead jet, set to -1 for no requirement
Ztautau_OS_CR1.DiJetDrMin        	= -1.;        					//Dijet minimum delta R, set to -1 for no requirement
Ztautau_OS_CR1.DiJetDrMax        	= -1.;        					//Dijet maximum delta R, set to -1 for no requirement
Ztautau_OS_CR1.DiJetInvMassMin        	= -1.;        					//Dijet minimal invariant mass, set to -1 for no requirement
Ztautau_OS_CR1.DiJetInvMassMax        	= -1.;        					//Dijet maximum invariant mass, set to -1 for no requirement
Ztautau_OS_CR1.DiJetSignEta        	= 0;        					//Dijet sign eta_1*eta_2
Ztautau_OS_CR1.DiJetDetaMin        	= -1.;        					//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Ztautau_OS_CR1.DiJetDetaMax        	= -1.;        					//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Ztautau_OS_CR1.weight        		= weight;      					//event weight
Ztautau_OS_CR1.invertTauRequirements    = false;        				//invert number of taus requirement
Ztautau_OS_CR1.invertTauProperties      = false;        				//invert ditau properties (dR, sign)
Ztautau_OS_CR1.invertBtagRequirement	= false;        				//invert number of b-jets required
Ztautau_OS_CR1.invertJetRequirements    = false;        				//invert jet pt requirements
Ztautau_OS_CR1.invertDijetProperties    = false;        				//invert dijet system properties (dR, inv mass, sign eta, dEta)

Ztautau_OS_CR1.select(false);        							//do selection, fill histograms

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

