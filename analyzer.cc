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

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

	double weight = 1.;

	MyHistoCollection myHistoColl_Skim (ofile.file_, "Skim");

	MyHistoCollection myHistoColl_SignalRegion(ofile.file_, "SignalRegion");
	MyHistoCollection myHistoColl_CR1 (ofile.file_, "Ztautau_CR1");
	MyHistoCollection myHistoColl_CR2 (ofile.file_, "Central_invertedVBF_CR2");
	MyHistoCollection myHistoColl_CR3 (ofile.file_, "Central_invertedVBF_TauMediumIso_CR3");
	MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_TauLooseIso_CR4");
        

	MyEventCollection baselineObjectSelectionCollection ("baselineObjectSelection");
	MyEventCollection mainObjectSelectionCollection ("mainObjectSelection");
	MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
	MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");

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
		mainObjectSelectionCollection.goodVertex = true;
	        TauMediumIsoObjectSelectionCollection.goodVertex = true;
	        TauLooseIsoObjectSelectionCollection.goodVertex = true;
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

             ) { mainObjectSelectionCollection.passedTrigger = true;
	         TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	         TauLooseIsoObjectSelectionCollection.passedTrigger = true;
               }

	  // electron selection
	  for(unsigned int e = 0;e<electron.size();++e){
	    mainObjectSelectionCollection.electron.push_back(&electron[e]);
	    TauMediumIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	    TauLooseIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	  }

	  // muon selection
	  for(unsigned int m =0;m<muon.size();++m){
	    if(!(       fabs(muon[m].eta) < 2.4                                        )) continue;
	    if(!(       muon[m].pt > 20                                                )) continue;
	    if(!(       muon[m].isGlobalMuon                                           )) continue;
	    if(!(       muon[m].isTrackerMuon                                          )) continue;
	    if(!(       muon[m].isPFMuon                                               )) continue;
	    if(!(       muon[m].numberOfMatchedStations > 1                            )) continue;
	    if(!((       fabs(muon[m].muonBestTrack_dxy) < 0.2           ))  &&
                 (       fabs(muon[m]. muonBestTrack_dz) < 0.5                         )) continue;
	    if(!(       muon[m].globalTrack_normalizedChi2 < 10.                       )) continue;
	    if(!(       muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0       )) continue;
	    if(!(       muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0       )) continue;
	    if(!(       muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5   )) continue;
	    if(!(       muon[m].innerTrack_normalizedChi2 < 1.8                        )) continue;
	    if(!(       fabs(muon[m].innerTrack_dxy) < 3.                              )) continue;
	    if(!(       fabs(muon[m].innerTrack_dz) < 30.                              )) continue;
	    mainObjectSelectionCollection.muon.push_back(&muon[m]);
	    TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	    TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	  }

          // tau main selection
          for(unsigned int t =0;t<tau.size();++t){
            if(!(          fabs(tau[t].eta) <= 2.1                                     )) continue;
            if(!(          tau[t].pt >= 45.                                            )) continue;
            if(!(          tau[t].leadPFChargedHadrCand_pt >= 5.0                      )) continue;
            if(!(          tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits > 0.5     )) continue;
            if(!(          tau[t].tauID_againstElectronTightMVA3 > 0.5                )) continue;
            if(!(          tau[t].tauID_againstMuonTight2 > 0.5                        )) continue;
            if(!(          (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)                         )) continue;
	    mainObjectSelectionCollection.tau.push_back(&tau[t]);
          }

          // tau Medium Iso selection
          for(unsigned int t =0;t<tau.size();++t){
            if(!(          fabs(tau[t].eta) <= 2.1                                     )) continue;
            if(!(          tau[t].pt >= 45.                                            )) continue;
            if(!(          tau[t].leadPFChargedHadrCand_pt >= 5.0                      )) continue;
            if(!(          tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits > 0.5     )) continue;
            if(!(          tau[t].tauID_againstElectronTightMVA3 > 0.5                )) continue;
            if(!(          tau[t].tauID_againstMuonTight2 > 0.5                        )) continue;
            if(!(          (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)                         )) continue;
	    TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
          }

          // tau Loose Iso selection
          for(unsigned int t =0;t<tau.size();++t){
            if(!(          fabs(tau[t].eta) <= 2.1                                     )) continue;
            if(!(          tau[t].pt >= 45.                                            )) continue;
            if(!(          tau[t].leadPFChargedHadrCand_pt >= 5.0                      )) continue;
            if(!(          tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5     )) continue;
            if(!(          tau[t].tauID_againstElectronTightMVA3 > 0.5                )) continue;
            if(!(          tau[t].tauID_againstMuonTight2 > 0.5                        )) continue;
            if(!(          (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)                         )) continue;
	    TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
          }

          // tau baseline selection
          for(unsigned int t =0;t<tau.size();++t){
            if(!(          fabs(tau[t].eta) <= 2.1                                     )) continue;
            if(!(          tau[t].pt >= 45.                                            )) continue;
            if(!(          tau[t].leadPFChargedHadrCand_pt >= 5.0                      )) continue;
	    baselineObjectSelectionCollection.tau.push_back(&tau[t]);
          }

          // jet selection
	  // ? id ?
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 50.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 5.0                                                               )) continue;
	    if(!(      (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99           )) continue;
	    if(!(      jet[j].neutralEmEnergyFraction < 0.99                                                 )) continue;
	    if(!(      jet[j].numberOfDaughters > 1                                                          )) continue;
	    if(fabs(jet[j].eta) < 2.4) {
               if(!(      jet[j].chargedHadronEnergyFraction > 0                                             )) continue;
               if(!(      jet[j].chargedEmEnergyFraction < 0.99                                              )) continue;
               if(!(      jet[j].chargedHadronMultiplicity > 0                                               )) continue;
            }
            double mindeltaRtaujet = 99999.;  
            for(unsigned int t =0;t<tau.size();++t){
                   if (!(       tau[t].selected    )) continue;
                   double temp_mindeltaRtaujet = deltaR(jet[j].eta, jet[j].phi, tau[t].eta, tau[t].phi); 
                   if (temp_mindeltaRtaujet < mindeltaRtaujet) mindeltaRtaujet = temp_mindeltaRtaujet;
            }
            if(!(       mindeltaRtaujet >= 0.3                                                                  )) continue;
	    mainObjectSelectionCollection.jet.push_back(&jet[j]);
	    TauMediumIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	    TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	  }


          // btag selection
          for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 2.4                                                               )) continue;
	    if(!(      jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244                         )) continue;
            double mindeltaRtaujet = 99999.;  
            for(unsigned int t =0;t<tau.size();++t){
                   if (!(       tau[t].selected    )) continue;
                   double temp_mindeltaRtaujet = deltaR(jet[j].eta, jet[j].phi, tau[t].eta, tau[t].phi); 
                   if (temp_mindeltaRtaujet < mindeltaRtaujet) mindeltaRtaujet = temp_mindeltaRtaujet;
            }
            if(!(       (mindeltaRtaujet >= 0.3) &&  (mindeltaRtaujet < 99999.)                              )) continue;
	    mainObjectSelectionCollection.bjet.push_back(&jet[j]);
	    TauMediumIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
	    TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
          }

	  //MET selection
	  mainObjectSelectionCollection.met.push_back(&met[0]);
	  TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// -- Skimming Studies   --
	// ------------------------

	myHistoColl_Skim.h_count->Fill("NoCuts",0);
	myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",0);

	while (true){

		//NoCuts
		myHistoColl_Skim.h_count->Fill("NoCuts",1);

		//AtLeast2Loostau
		if(!(             ( (int)baselineObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",1);

		fillHistoCollection (myHistoColl_Skim, mainObjectSelectionCollection,weight);

		break;		

	}

	// ---------------------
	// -- Signal Region   --
	// ---------------------

	myHistoColl_SignalRegion.h_count->Fill("NoCuts",0);
	myHistoColl_SignalRegion.h_count->Fill("TriggerRequirement",0);
	myHistoColl_SignalRegion.h_count->Fill("AtLeast1tau",0);
	myHistoColl_SignalRegion.h_count->Fill("AtLeast2tau",0);
	myHistoColl_SignalRegion.h_count->Fill("DiTauDeltaRCut", 0);
	myHistoColl_SignalRegion.h_count->Fill("DiTauSignCut",0);
	myHistoColl_SignalRegion.h_count->Fill("NoBTag",0);
	myHistoColl_SignalRegion.h_count->Fill("LeadJetCut",0);
	myHistoColl_SignalRegion.h_count->Fill("SecondJetCut",0);
	myHistoColl_SignalRegion.h_count->Fill("DiJetDeltaRCut",0);
	myHistoColl_SignalRegion.h_count->Fill("DiJetInvMassCut",0);
	myHistoColl_SignalRegion.h_count->Fill("DiJetEtaSignCut",0);
	myHistoColl_SignalRegion.h_count->Fill("DiJetEtaCut",0);
	
	while (true){

		//DATA MUST BE BLINDED!!!!!!!!! (FOR NOW)
		if (eventhelper_isRealData) break;

		//NoCuts
		myHistoColl_SignalRegion.h_count->Fill("NoCuts",1);

		//Trigger Requirement (ONLY FOR DATA)
		if (eventhelper_isRealData) {
			if(!(                     mainObjectSelectionCollection.passedTrigger                   )) break;
		}
		myHistoColl_SignalRegion.h_count->Fill("TriggerRequirement",1);

		//AtLeast1tau
		if(!(             ( (int)mainObjectSelectionCollection.tau.size() >= 1 )                 )) break;
		myHistoColl_SignalRegion.h_count->Fill("AtLeast1tau",1);

		//AtLeast2tau
		if(!(             ( (int)mainObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		myHistoColl_SignalRegion.h_count->Fill("AtLeast2tau",1);

		unsigned int temp_tau1index = 99999;
		unsigned int temp_tau2index = 99999;
		double temp_tau1_pt = -99999.;
		double temp_tau2_pt = -99999.;
		TLorentzVector tau1_4v;
		TLorentzVector tau2_4v;

		for(unsigned int t =0;t<mainObjectSelectionCollection.tau.size();++t){
			if (temp_tau1_pt < mainObjectSelectionCollection.tau[t]->pt) {temp_tau1index = t; temp_tau1_pt = mainObjectSelectionCollection.tau[t]->pt;}
		}

		for(unsigned int t =0;t<mainObjectSelectionCollection.tau.size();++t){
			if ( (temp_tau2_pt < mainObjectSelectionCollection.tau[t]->pt) && ( temp_tau1_pt > mainObjectSelectionCollection.tau[t]->pt) ) {temp_tau2index = t; temp_tau2_pt = mainObjectSelectionCollection.tau[t]->pt;}
		}
		if (  (temp_tau1index < 99999)  && (temp_tau2index < 99999)  ) {
			tau1_4v.SetPtEtaPhiE(mainObjectSelectionCollection.tau[temp_tau1index]->pt, mainObjectSelectionCollection.tau[temp_tau1index]->eta, mainObjectSelectionCollection.tau[temp_tau1index]->phi, mainObjectSelectionCollection.tau[temp_tau1index]->energy);
			tau2_4v.SetPtEtaPhiE(mainObjectSelectionCollection.tau[temp_tau2index]->pt, mainObjectSelectionCollection.tau[temp_tau2index]->eta, mainObjectSelectionCollection.tau[temp_tau2index]->phi, mainObjectSelectionCollection.tau[temp_tau2index]->energy);
		}

		//DiTauDeltaRCut
		double DiTauDeltaR = tau1_4v.DeltaR(tau2_4v);

		if(!(           ( DiTauDeltaR > 0.3)                                                     )) break;
		myHistoColl_SignalRegion.h_count->Fill("DiTauDeltaRCut", 1);

	         //DiTauSignCut
	         int chargeDiTau = mainObjectSelectionCollection.tau[temp_tau1index]->charge * mainObjectSelectionCollection.tau[temp_tau2index]->charge;
	         if(!(                          chargeDiTau > 0.                                          )) break; //NOW REQUIRING SAME SIGN
	         myHistoColl_SignalRegion.h_count->Fill("DiTauSignCut",1);

		//NoBTag
		if(!(            (int)mainObjectSelectionCollection.bjet.size() == 0                     )) break;
		myHistoColl_SignalRegion.h_count->Fill("NoBTag",1);

		//LeadJet
		double leadjetpt = 0.;
		double leadjeteta = 0.;

		for(unsigned int j = 0;j<mainObjectSelectionCollection.jet.size();++j){
			if (leadjetpt < mainObjectSelectionCollection.jet[j]->pt) {leadjetpt = mainObjectSelectionCollection.jet[j]->pt; leadjeteta = mainObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (leadjetpt >= 75.) && (fabs(leadjeteta) < 5.)              )) break;
		myHistoColl_SignalRegion.h_count->Fill("LeadJetCut",1);

		//SubLeadJet
		double subleadjetpt = 0.;
		double subleadjeteta = 0.;

		for(unsigned int j = 0;j<mainObjectSelectionCollection.jet.size();++j){
			if ((subleadjetpt < mainObjectSelectionCollection.jet[j]->pt) && (leadjetpt > mainObjectSelectionCollection.jet[j]->pt)) {subleadjetpt = mainObjectSelectionCollection.jet[j]->pt; subleadjeteta = mainObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.)          )) break;
		myHistoColl_SignalRegion.h_count->Fill("SecondJetCut",1);

		//DiJetCuts

		bool passedDiJetEtaSignCut = false;
		bool passedDiJetEtaCut = false;
		bool passedDiJetMassCut = false;
		bool passedDiJetDeltaRCut = false;

		unsigned int jet1index = 99999;
		unsigned int jet2index = 99999;

		double invmassDiJet = 0.;
		double dealtaRDiJet = 0.;

		for(unsigned int j1 = 0;j1<mainObjectSelectionCollection.jet.size();++j1){

			for (unsigned int j2 = 0;j2<mainObjectSelectionCollection.jet.size();++j2){

					if (j1 == j2) continue;

					TLorentzVector jet1_4v;
					TLorentzVector jet2_4v;

					jet1_4v.SetPtEtaPhiE(mainObjectSelectionCollection.jet[j1]->pt, mainObjectSelectionCollection.jet[j1]->eta, mainObjectSelectionCollection.jet[j1]->phi, mainObjectSelectionCollection.jet[j1]->energy);
					jet2_4v.SetPtEtaPhiE(mainObjectSelectionCollection.jet[j2]->pt, mainObjectSelectionCollection.jet[j2]->eta, mainObjectSelectionCollection.jet[j2]->phi, mainObjectSelectionCollection.jet[j2]->energy);

					TLorentzVector dijet_4v = jet1_4v + jet2_4v;

					double temp_invmassDiJet = dijet_4v.M();
					if (     invmassDiJet < temp_invmassDiJet   ) {invmassDiJet = temp_invmassDiJet; jet1index = j1; jet2index = j2; dealtaRDiJet = jet1_4v.DeltaR(jet2_4v);}

			}

		}

		//DiJetDeltaRCut
		if (     dealtaRDiJet >= 0.3   ) passedDiJetDeltaRCut = true;
		if(!(                      passedDiJetDeltaRCut                                       )) break;
		myHistoColl_SignalRegion.h_count->Fill("DiJetDeltaRCut",1);

		//DiJetInvMassCut
		if (     invmassDiJet > 700.   ) passedDiJetMassCut = true;
		if(!(                      passedDiJetMassCut                                         )) break;
		myHistoColl_SignalRegion.h_count->Fill("DiJetInvMassCut",1);

		if (     (mainObjectSelectionCollection.jet[jet1index]->eta * mainObjectSelectionCollection.jet[jet2index]->eta ) < 0.         ) passedDiJetEtaSignCut = true;
		if(!(                      passedDiJetEtaSignCut                                      )) break;
		myHistoColl_SignalRegion.h_count->Fill("DiJetEtaSignCut",1);

		if (      fabs ( mainObjectSelectionCollection.jet[jet1index]->eta - mainObjectSelectionCollection.jet[jet2index]->eta ) > 4.2   ) passedDiJetEtaCut = true;

		if(!(                      passedDiJetEtaCut                                          )) break;
		myHistoColl_SignalRegion.h_count->Fill("DiJetEtaCut",1);


		fillHistoCollection (myHistoColl_SignalRegion, mainObjectSelectionCollection, weight);

		//INVERTED VBF CUT
		//if((    (leadjetpt >= 75.) && (fabs(leadjeteta)< 5.) && (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.) && (passedDiJetDeltaRCut) && (passedDiJetEtaSignCut) && (passedDiJetEtaCut) && (passedDiJetMassCut)   )) continue;
		//ofile.count("invertedvbfcut");


		break;
	}

	// ---------------------------------
	// -- CENTRAL + INVERTED VBF CR   --
	// ---------------------------------

	myHistoColl_CR2.h_count->Fill("NoCuts",0);
	myHistoColl_CR2.h_count->Fill("TriggerRequirement",0);
	myHistoColl_CR2.h_count->Fill("AtLeast1tau",0);
	myHistoColl_CR2.h_count->Fill("AtLeast2tau",0);
	myHistoColl_CR2.h_count->Fill("DiTauDeltaRCut", 0);
	myHistoColl_CR2.h_count->Fill("DiTauSignCut",0);
	myHistoColl_CR2.h_count->Fill("NoBTag",0);
	myHistoColl_CR2.h_count->Fill("InvertedVBFCut",0);
	
	while (true){

		//NoCuts
		myHistoColl_CR2.h_count->Fill("NoCuts",1);

		//Trigger Requirement
		if (eventhelper_isRealData) {
			if(!(                     mainObjectSelectionCollection.passedTrigger                   )) break;
		}
		myHistoColl_CR2.h_count->Fill("TriggerRequirement",1);

		//AtLeast1tau
		if(!(             ( (int)mainObjectSelectionCollection.tau.size() >= 1 )                 )) break;
		myHistoColl_CR2.h_count->Fill("AtLeast1tau",1);

		//AtLeast2tau
		if(!(             ( (int)mainObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		myHistoColl_CR2.h_count->Fill("AtLeast2tau",1);

		unsigned int temp_tau1index = 99999;
		unsigned int temp_tau2index = 99999;
		double temp_tau1_pt = -99999.;
		double temp_tau2_pt = -99999.;
		TLorentzVector tau1_4v;
		TLorentzVector tau2_4v;

		for(unsigned int t =0;t<mainObjectSelectionCollection.tau.size();++t){
			if (temp_tau1_pt < mainObjectSelectionCollection.tau[t]->pt) {temp_tau1index = t; temp_tau1_pt = mainObjectSelectionCollection.tau[t]->pt;}
		}

		for(unsigned int t =0;t<mainObjectSelectionCollection.tau.size();++t){
			if ( (temp_tau2_pt < mainObjectSelectionCollection.tau[t]->pt) && ( temp_tau1_pt > mainObjectSelectionCollection.tau[t]->pt) ) {temp_tau2index = t; temp_tau2_pt = mainObjectSelectionCollection.tau[t]->pt;}
		}
		if (  (temp_tau1index < 99999)  && (temp_tau2index < 99999)  ) {
			tau1_4v.SetPtEtaPhiE(mainObjectSelectionCollection.tau[temp_tau1index]->pt, mainObjectSelectionCollection.tau[temp_tau1index]->eta, mainObjectSelectionCollection.tau[temp_tau1index]->phi, mainObjectSelectionCollection.tau[temp_tau1index]->energy);
			tau2_4v.SetPtEtaPhiE(mainObjectSelectionCollection.tau[temp_tau2index]->pt, mainObjectSelectionCollection.tau[temp_tau2index]->eta, mainObjectSelectionCollection.tau[temp_tau2index]->phi, mainObjectSelectionCollection.tau[temp_tau2index]->energy);
		}

		//DiTauDeltaRCut
		double DiTauDeltaR = tau1_4v.DeltaR(tau2_4v);

		if(!(           ( DiTauDeltaR > 0.3)                                                     )) break;
		myHistoColl_CR2.h_count->Fill("DiTauDeltaRCut", 1);

	         //DiTauSignCut
	         int chargeDiTau = mainObjectSelectionCollection.tau[temp_tau1index]->charge * mainObjectSelectionCollection.tau[temp_tau2index]->charge;
	         if(!(                          chargeDiTau > 0.                                          )) break; //NOW REQUIRING SAME SIGN
	         myHistoColl_CR2.h_count->Fill("DiTauSignCut",1);

		//NoBTag
		if(!(            (int)mainObjectSelectionCollection.bjet.size() == 0                     )) break;
		myHistoColl_CR2.h_count->Fill("NoBTag",1);

		//LeadJet
		double leadjetpt = 0.;
		double leadjeteta = 0.;

		for(unsigned int j = 0;j<mainObjectSelectionCollection.jet.size();++j){
			if (leadjetpt < mainObjectSelectionCollection.jet[j]->pt) {leadjetpt = mainObjectSelectionCollection.jet[j]->pt; leadjeteta = mainObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (leadjetpt >= 75.) && (fabs(leadjeteta) < 5.)              )) {
			myHistoColl_CR2.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR2, mainObjectSelectionCollection, weight);
			break;
		}

		//SubLeadJet
		double subleadjetpt = 0.;
		double subleadjeteta = 0.;

		for(unsigned int j = 0;j<mainObjectSelectionCollection.jet.size();++j){
			if ((subleadjetpt < mainObjectSelectionCollection.jet[j]->pt) && (leadjetpt > mainObjectSelectionCollection.jet[j]->pt)) {subleadjetpt = mainObjectSelectionCollection.jet[j]->pt; subleadjeteta = mainObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.)          )) {
			myHistoColl_CR2.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR2, mainObjectSelectionCollection, weight);
			break;
		}

		//DiJetCuts

		bool passedDiJetEtaSignCut = false;
		bool passedDiJetEtaCut = false;
		bool passedDiJetMassCut = false;
		bool passedDiJetDeltaRCut = false;

		unsigned int jet1index = 99999;
		unsigned int jet2index = 99999;

		double invmassDiJet = 0.;
		double dealtaRDiJet = 0.;

		for(unsigned int j1 = 0;j1<mainObjectSelectionCollection.jet.size();++j1){

			for (unsigned int j2 = 0;j2<mainObjectSelectionCollection.jet.size();++j2){

					if (j1 == j2) continue;

					TLorentzVector jet1_4v;
					TLorentzVector jet2_4v;

					jet1_4v.SetPtEtaPhiE(mainObjectSelectionCollection.jet[j1]->pt, mainObjectSelectionCollection.jet[j1]->eta, mainObjectSelectionCollection.jet[j1]->phi, mainObjectSelectionCollection.jet[j1]->energy);
					jet2_4v.SetPtEtaPhiE(mainObjectSelectionCollection.jet[j2]->pt, mainObjectSelectionCollection.jet[j2]->eta, mainObjectSelectionCollection.jet[j2]->phi, mainObjectSelectionCollection.jet[j2]->energy);

					TLorentzVector dijet_4v = jet1_4v + jet2_4v;

					double temp_invmassDiJet = dijet_4v.M();
					if (     invmassDiJet < temp_invmassDiJet   ) {invmassDiJet = temp_invmassDiJet; jet1index = j1; jet2index = j2; dealtaRDiJet = jet1_4v.DeltaR(jet2_4v);}

			}

		}

		//DiJetDeltaRCut
		if (     dealtaRDiJet >= 0.3   ) passedDiJetDeltaRCut = true;
		if(!(                      passedDiJetDeltaRCut                                       )) {
			myHistoColl_CR2.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR2, mainObjectSelectionCollection, weight);
			break;
		}

		//DiJetInvMassCut
		if (     invmassDiJet > 700.   ) passedDiJetMassCut = true;
		if(!(                      passedDiJetMassCut                                         )) {
			myHistoColl_CR2.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR2, mainObjectSelectionCollection, weight);
			break;
		}

		if (     (mainObjectSelectionCollection.jet[jet1index]->eta * mainObjectSelectionCollection.jet[jet2index]->eta ) < 0.         ) passedDiJetEtaSignCut = true;
		if(!(                      passedDiJetEtaSignCut                                      )) {
			myHistoColl_CR2.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR2, mainObjectSelectionCollection, weight);
			break;
		}

		if (      fabs ( mainObjectSelectionCollection.jet[jet1index]->eta - mainObjectSelectionCollection.jet[jet2index]->eta ) > 4.2   ) passedDiJetEtaCut = true;

		if(!(                      passedDiJetEtaCut                                          )) {
			myHistoColl_CR2.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR2, mainObjectSelectionCollection, weight);
			break;
		}


		//INVERTED VBF CUT
		if((    (leadjetpt >= 75.) && (fabs(leadjeteta)< 5.) && (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.) && (passedDiJetDeltaRCut) && (passedDiJetEtaSignCut) && (passedDiJetEtaCut) && (passedDiJetMassCut)   )) break;
		myHistoColl_CR2.h_count->Fill("InvertedVBFCut",1);

		fillHistoCollection (myHistoColl_CR2, mainObjectSelectionCollection, weight);


		break;
	}

	// ------------------------------------------------------
	// -- CENTRAL + INVERTED VBF CR (with Tau Medium Iso)  --
	// ------------------------------------------------------

	myHistoColl_CR3.h_count->Fill("NoCuts",0);
	myHistoColl_CR3.h_count->Fill("TriggerRequirement",0);
	myHistoColl_CR3.h_count->Fill("AtLeast1tau",0);
	myHistoColl_CR3.h_count->Fill("AtLeast2tau",0);
	myHistoColl_CR3.h_count->Fill("DiTauDeltaRCut", 0);
	myHistoColl_CR3.h_count->Fill("DiTauSignCut",0);
	myHistoColl_CR3.h_count->Fill("NoBTag",0);
	myHistoColl_CR3.h_count->Fill("InvertedVBFCut",0);
	
	while (true){

		//NoCuts
		myHistoColl_CR3.h_count->Fill("NoCuts",1);

		//Trigger Requirement
		if (eventhelper_isRealData) {
			if(!(                     TauMediumIsoObjectSelectionCollection.passedTrigger                   )) break;
		}
		myHistoColl_CR3.h_count->Fill("TriggerRequirement",1);

		//AtLeast1tau
		if(!(             ( (int)TauMediumIsoObjectSelectionCollection.tau.size() >= 1 )                 )) break;
		myHistoColl_CR3.h_count->Fill("AtLeast1tau",1);

		//AtLeast2tau
		if(!(             ( (int)TauMediumIsoObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		myHistoColl_CR3.h_count->Fill("AtLeast2tau",1);

		unsigned int temp_tau1index = 99999;
		unsigned int temp_tau2index = 99999;
		double temp_tau1_pt = -99999.;
		double temp_tau2_pt = -99999.;
		TLorentzVector tau1_4v;
		TLorentzVector tau2_4v;

		for(unsigned int t =0;t<TauMediumIsoObjectSelectionCollection.tau.size();++t){
			if (temp_tau1_pt < TauMediumIsoObjectSelectionCollection.tau[t]->pt) {temp_tau1index = t; temp_tau1_pt = TauMediumIsoObjectSelectionCollection.tau[t]->pt;}
		}

		for(unsigned int t =0;t<TauMediumIsoObjectSelectionCollection.tau.size();++t){
			if ( (temp_tau2_pt < TauMediumIsoObjectSelectionCollection.tau[t]->pt) && ( temp_tau1_pt > TauMediumIsoObjectSelectionCollection.tau[t]->pt) ) {temp_tau2index = t; temp_tau2_pt = TauMediumIsoObjectSelectionCollection.tau[t]->pt;}
		}
		if (  (temp_tau1index < 99999)  && (temp_tau2index < 99999)  ) {
			tau1_4v.SetPtEtaPhiE(TauMediumIsoObjectSelectionCollection.tau[temp_tau1index]->pt, TauMediumIsoObjectSelectionCollection.tau[temp_tau1index]->eta, TauMediumIsoObjectSelectionCollection.tau[temp_tau1index]->phi, TauMediumIsoObjectSelectionCollection.tau[temp_tau1index]->energy);
			tau2_4v.SetPtEtaPhiE(TauMediumIsoObjectSelectionCollection.tau[temp_tau2index]->pt, TauMediumIsoObjectSelectionCollection.tau[temp_tau2index]->eta, TauMediumIsoObjectSelectionCollection.tau[temp_tau2index]->phi, TauMediumIsoObjectSelectionCollection.tau[temp_tau2index]->energy);
		}

		//DiTauDeltaRCut
		double DiTauDeltaR = tau1_4v.DeltaR(tau2_4v);

		if(!(           ( DiTauDeltaR > 0.3)                                                     )) break;
		myHistoColl_CR3.h_count->Fill("DiTauDeltaRCut", 1);

	         //DiTauSignCut
	         int chargeDiTau = TauMediumIsoObjectSelectionCollection.tau[temp_tau1index]->charge * TauMediumIsoObjectSelectionCollection.tau[temp_tau2index]->charge;
	         if(!(                          chargeDiTau > 0.                                          )) break; //NOW REQUIRING SAME SIGN
	         myHistoColl_CR3.h_count->Fill("DiTauSignCut",1);

		//NoBTag
		if(!(            (int)TauMediumIsoObjectSelectionCollection.bjet.size() == 0                     )) break;
		myHistoColl_CR3.h_count->Fill("NoBTag",1);

		//LeadJet
		double leadjetpt = 0.;
		double leadjeteta = 0.;

		for(unsigned int j = 0;j<TauMediumIsoObjectSelectionCollection.jet.size();++j){
			if (leadjetpt < TauMediumIsoObjectSelectionCollection.jet[j]->pt) {leadjetpt = TauMediumIsoObjectSelectionCollection.jet[j]->pt; leadjeteta = TauMediumIsoObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (leadjetpt >= 75.) && (fabs(leadjeteta) < 5.)              )) {
			myHistoColl_CR3.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR3, TauMediumIsoObjectSelectionCollection, weight);
			break;
		}

		//SubLeadJet
		double subleadjetpt = 0.;
		double subleadjeteta = 0.;

		for(unsigned int j = 0;j<TauMediumIsoObjectSelectionCollection.jet.size();++j){
			if ((subleadjetpt < TauMediumIsoObjectSelectionCollection.jet[j]->pt) && (leadjetpt > TauMediumIsoObjectSelectionCollection.jet[j]->pt)) {subleadjetpt = TauMediumIsoObjectSelectionCollection.jet[j]->pt; subleadjeteta = TauMediumIsoObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.)          )) {
			myHistoColl_CR3.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR3, TauMediumIsoObjectSelectionCollection, weight);
			break;
		}

		//DiJetCuts

		bool passedDiJetEtaSignCut = false;
		bool passedDiJetEtaCut = false;
		bool passedDiJetMassCut = false;
		bool passedDiJetDeltaRCut = false;

		unsigned int jet1index = 99999;
		unsigned int jet2index = 99999;

		double invmassDiJet = 0.;
		double dealtaRDiJet = 0.;

		for(unsigned int j1 = 0;j1<TauMediumIsoObjectSelectionCollection.jet.size();++j1){

			for (unsigned int j2 = 0;j2<TauMediumIsoObjectSelectionCollection.jet.size();++j2){

					if (j1 == j2) continue;

					TLorentzVector jet1_4v;
					TLorentzVector jet2_4v;

					jet1_4v.SetPtEtaPhiE(TauMediumIsoObjectSelectionCollection.jet[j1]->pt, TauMediumIsoObjectSelectionCollection.jet[j1]->eta, TauMediumIsoObjectSelectionCollection.jet[j1]->phi, TauMediumIsoObjectSelectionCollection.jet[j1]->energy);
					jet2_4v.SetPtEtaPhiE(TauMediumIsoObjectSelectionCollection.jet[j2]->pt, TauMediumIsoObjectSelectionCollection.jet[j2]->eta, TauMediumIsoObjectSelectionCollection.jet[j2]->phi, TauMediumIsoObjectSelectionCollection.jet[j2]->energy);

					TLorentzVector dijet_4v = jet1_4v + jet2_4v;

					double temp_invmassDiJet = dijet_4v.M();
					if (     invmassDiJet < temp_invmassDiJet   ) {invmassDiJet = temp_invmassDiJet; jet1index = j1; jet2index = j2; dealtaRDiJet = jet1_4v.DeltaR(jet2_4v);}

			}

		}

		//DiJetDeltaRCut
		if (     dealtaRDiJet >= 0.3   ) passedDiJetDeltaRCut = true;
		if(!(                      passedDiJetDeltaRCut                                       )) {
			myHistoColl_CR3.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR3, TauMediumIsoObjectSelectionCollection, weight);
			break;
		}

		//DiJetInvMassCut
		if (     invmassDiJet > 700.   ) passedDiJetMassCut = true;
		if(!(                      passedDiJetMassCut                                         )) {
			myHistoColl_CR3.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR3, TauMediumIsoObjectSelectionCollection, weight);
			break;
		}

		if (     (TauMediumIsoObjectSelectionCollection.jet[jet1index]->eta * TauMediumIsoObjectSelectionCollection.jet[jet2index]->eta ) < 0.         ) passedDiJetEtaSignCut = true;
		if(!(                      passedDiJetEtaSignCut                                      )) {
			myHistoColl_CR3.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR3, TauMediumIsoObjectSelectionCollection, weight);
			break;
		}

		if (      fabs ( TauMediumIsoObjectSelectionCollection.jet[jet1index]->eta - TauMediumIsoObjectSelectionCollection.jet[jet2index]->eta ) > 4.2   ) passedDiJetEtaCut = true;

		if(!(                      passedDiJetEtaCut                                          )) {
			myHistoColl_CR3.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR3, TauMediumIsoObjectSelectionCollection, weight);
			break;
		}


		//INVERTED VBF CUT
		if((    (leadjetpt >= 75.) && (fabs(leadjeteta)< 5.) && (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.) && (passedDiJetDeltaRCut) && (passedDiJetEtaSignCut) && (passedDiJetEtaCut) && (passedDiJetMassCut)   )) break;
		myHistoColl_CR3.h_count->Fill("InvertedVBFCut",1);

		fillHistoCollection (myHistoColl_CR3, TauMediumIsoObjectSelectionCollection, weight);


		break;
	}

	// ------------------------------------------------------
	// -- CENTRAL + INVERTED VBF CR (with Tau Loose Iso)  --
	// ------------------------------------------------------

	myHistoColl_CR4.h_count->Fill("NoCuts",0);
	myHistoColl_CR4.h_count->Fill("TriggerRequirement",0);
	myHistoColl_CR4.h_count->Fill("AtLeast1tau",0);
	myHistoColl_CR4.h_count->Fill("AtLeast2tau",0);
	myHistoColl_CR4.h_count->Fill("DiTauDeltaRCut", 0);
	myHistoColl_CR4.h_count->Fill("DiTauSignCut",0);
	myHistoColl_CR4.h_count->Fill("NoBTag",0);
	myHistoColl_CR4.h_count->Fill("InvertedVBFCut",0);
	
	while (true){

		//NoCuts
		myHistoColl_CR4.h_count->Fill("NoCuts",1);

		//Trigger Requirement
		if (eventhelper_isRealData) {
			if(!(                     TauLooseIsoObjectSelectionCollection.passedTrigger                   )) break;
		}
		myHistoColl_CR4.h_count->Fill("TriggerRequirement",1);

		//AtLeast1tau
		if(!(             ( (int)TauLooseIsoObjectSelectionCollection.tau.size() >= 1 )                 )) break;
		myHistoColl_CR4.h_count->Fill("AtLeast1tau",1);

		//AtLeast2tau
		if(!(             ( (int)TauLooseIsoObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		myHistoColl_CR4.h_count->Fill("AtLeast2tau",1);

		unsigned int temp_tau1index = 99999;
		unsigned int temp_tau2index = 99999;
		double temp_tau1_pt = -99999.;
		double temp_tau2_pt = -99999.;
		TLorentzVector tau1_4v;
		TLorentzVector tau2_4v;

		for(unsigned int t =0;t<TauLooseIsoObjectSelectionCollection.tau.size();++t){
			if (temp_tau1_pt < TauLooseIsoObjectSelectionCollection.tau[t]->pt) {temp_tau1index = t; temp_tau1_pt = TauLooseIsoObjectSelectionCollection.tau[t]->pt;}
		}

		for(unsigned int t =0;t<TauLooseIsoObjectSelectionCollection.tau.size();++t){
			if ( (temp_tau2_pt < TauLooseIsoObjectSelectionCollection.tau[t]->pt) && ( temp_tau1_pt > TauLooseIsoObjectSelectionCollection.tau[t]->pt) ) {temp_tau2index = t; temp_tau2_pt = TauLooseIsoObjectSelectionCollection.tau[t]->pt;}
		}
		if (  (temp_tau1index < 99999)  && (temp_tau2index < 99999)  ) {
			tau1_4v.SetPtEtaPhiE(TauLooseIsoObjectSelectionCollection.tau[temp_tau1index]->pt, TauLooseIsoObjectSelectionCollection.tau[temp_tau1index]->eta, TauLooseIsoObjectSelectionCollection.tau[temp_tau1index]->phi, TauLooseIsoObjectSelectionCollection.tau[temp_tau1index]->energy);
			tau2_4v.SetPtEtaPhiE(TauLooseIsoObjectSelectionCollection.tau[temp_tau2index]->pt, TauLooseIsoObjectSelectionCollection.tau[temp_tau2index]->eta, TauLooseIsoObjectSelectionCollection.tau[temp_tau2index]->phi, TauLooseIsoObjectSelectionCollection.tau[temp_tau2index]->energy);
		}

		//DiTauDeltaRCut
		double DiTauDeltaR = tau1_4v.DeltaR(tau2_4v);

		if(!(           ( DiTauDeltaR > 0.3)                                                     )) break;
		myHistoColl_CR4.h_count->Fill("DiTauDeltaRCut", 1);

	         //DiTauSignCut
	         int chargeDiTau = TauLooseIsoObjectSelectionCollection.tau[temp_tau1index]->charge * TauLooseIsoObjectSelectionCollection.tau[temp_tau2index]->charge;
	         if(!(                          chargeDiTau > 0.                                          )) break; //NOW REQUIRING SAME SIGN
	         myHistoColl_CR4.h_count->Fill("DiTauSignCut",1);

		//NoBTag
		if(!(            (int)TauLooseIsoObjectSelectionCollection.bjet.size() == 0                     )) break;
		myHistoColl_CR4.h_count->Fill("NoBTag",1);

		//LeadJet
		double leadjetpt = 0.;
		double leadjeteta = 0.;

		for(unsigned int j = 0;j<TauLooseIsoObjectSelectionCollection.jet.size();++j){
			if (leadjetpt < TauLooseIsoObjectSelectionCollection.jet[j]->pt) {leadjetpt = TauLooseIsoObjectSelectionCollection.jet[j]->pt; leadjeteta = TauLooseIsoObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (leadjetpt >= 75.) && (fabs(leadjeteta) < 5.)              )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, weight);
			break;
		}

		//SubLeadJet
		double subleadjetpt = 0.;
		double subleadjeteta = 0.;

		for(unsigned int j = 0;j<TauLooseIsoObjectSelectionCollection.jet.size();++j){
			if ((subleadjetpt < TauLooseIsoObjectSelectionCollection.jet[j]->pt) && (leadjetpt > TauLooseIsoObjectSelectionCollection.jet[j]->pt)) {subleadjetpt = TauLooseIsoObjectSelectionCollection.jet[j]->pt; subleadjeteta = TauLooseIsoObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.)          )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, weight);
			break;
		}

		//DiJetCuts

		bool passedDiJetEtaSignCut = false;
		bool passedDiJetEtaCut = false;
		bool passedDiJetMassCut = false;
		bool passedDiJetDeltaRCut = false;

		unsigned int jet1index = 99999;
		unsigned int jet2index = 99999;

		double invmassDiJet = 0.;
		double dealtaRDiJet = 0.;

		for(unsigned int j1 = 0;j1<TauLooseIsoObjectSelectionCollection.jet.size();++j1){

			for (unsigned int j2 = 0;j2<TauLooseIsoObjectSelectionCollection.jet.size();++j2){

					if (j1 == j2) continue;

					TLorentzVector jet1_4v;
					TLorentzVector jet2_4v;

					jet1_4v.SetPtEtaPhiE(TauLooseIsoObjectSelectionCollection.jet[j1]->pt, TauLooseIsoObjectSelectionCollection.jet[j1]->eta, TauLooseIsoObjectSelectionCollection.jet[j1]->phi, TauLooseIsoObjectSelectionCollection.jet[j1]->energy);
					jet2_4v.SetPtEtaPhiE(TauLooseIsoObjectSelectionCollection.jet[j2]->pt, TauLooseIsoObjectSelectionCollection.jet[j2]->eta, TauLooseIsoObjectSelectionCollection.jet[j2]->phi, TauLooseIsoObjectSelectionCollection.jet[j2]->energy);

					TLorentzVector dijet_4v = jet1_4v + jet2_4v;

					double temp_invmassDiJet = dijet_4v.M();
					if (     invmassDiJet < temp_invmassDiJet   ) {invmassDiJet = temp_invmassDiJet; jet1index = j1; jet2index = j2; dealtaRDiJet = jet1_4v.DeltaR(jet2_4v);}

			}

		}

		//DiJetDeltaRCut
		if (     dealtaRDiJet >= 0.3   ) passedDiJetDeltaRCut = true;
		if(!(                      passedDiJetDeltaRCut                                       )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, weight);
			break;
		}

		//DiJetInvMassCut
		if (     invmassDiJet > 700.   ) passedDiJetMassCut = true;
		if(!(                      passedDiJetMassCut                                         )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, weight);
			break;
		}

		if (     (TauLooseIsoObjectSelectionCollection.jet[jet1index]->eta * TauLooseIsoObjectSelectionCollection.jet[jet2index]->eta ) < 0.         ) passedDiJetEtaSignCut = true;
		if(!(                      passedDiJetEtaSignCut                                      )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, weight);
			break;
		}

		if (      fabs ( TauLooseIsoObjectSelectionCollection.jet[jet1index]->eta - TauLooseIsoObjectSelectionCollection.jet[jet2index]->eta ) > 4.2   ) passedDiJetEtaCut = true;

		if(!(                      passedDiJetEtaCut                                          )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",1);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, weight);
			break;
		}


		//INVERTED VBF CUT
		if((    (leadjetpt >= 75.) && (fabs(leadjeteta)< 5.) && (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.) && (passedDiJetDeltaRCut) && (passedDiJetEtaSignCut) && (passedDiJetEtaCut) && (passedDiJetMassCut)   )) break;
		myHistoColl_CR4.h_count->Fill("InvertedVBFCut",1);

		fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, weight);


		break;
	}

	  // ---------------------
	  // -- Z -> TauTau CR  --
	  // ---------------------

	myHistoColl_CR1.h_count->Fill("NoCuts",0.);
	myHistoColl_CR1.h_count->Fill("TriggerRequirement",0.);
	myHistoColl_CR1.h_count->Fill("AtLeast1tau",0.);
	myHistoColl_CR1.h_count->Fill("AtLeast2tau",0.);
	myHistoColl_CR1.h_count->Fill("DiTauDeltaRCut",0.);
	myHistoColl_CR1.h_count->Fill("NoBTag",0.);
	myHistoColl_CR1.h_count->Fill("DiTauInaviantMassCut",0.);
	myHistoColl_CR1.h_count->Fill("DiTauSignCut",0.);

          while (true){                     

	          //NoCuts
	          myHistoColl_CR1.h_count->Fill("NoCuts",1);
          
	          //Trigger Requirement (ONLY FOR DATA)
		if (eventhelper_isRealData) {
			if(!(                     mainObjectSelectionCollection.passedTrigger                   )) break;
		}
	          myHistoColl_CR1.h_count->Fill("TriggerRequirement",1);

	          //AtLeast1tau
	          if(!(             ( (int)mainObjectSelectionCollection.tau.size() >= 1 )                 )) break;
	          myHistoColl_CR1.h_count->Fill("AtLeast1tau",1);

	          //AtLeast2tau
	          if(!(             ( (int)mainObjectSelectionCollection.tau.size() >= 2 )                 )) break;
	          myHistoColl_CR1.h_count->Fill("AtLeast2tau",1);

                  unsigned int temp_tau1index = 99999;
                  unsigned int temp_tau2index = 99999;
                  double temp_tau1_pt = -99999.;
                  double temp_tau2_pt = -99999.;
                  TLorentzVector tau1_4v;
                  TLorentzVector tau2_4v;

                  for(unsigned int t =0;t<mainObjectSelectionCollection.tau.size();++t){
                       if (temp_tau1_pt < mainObjectSelectionCollection.tau[t]->pt) {temp_tau1index = t; temp_tau1_pt = mainObjectSelectionCollection.tau[t]->pt;}
                  }

                  for(unsigned int t =0;t<mainObjectSelectionCollection.tau.size();++t){
                       if ( (temp_tau2_pt < mainObjectSelectionCollection.tau[t]->pt) && ( temp_tau1_pt > mainObjectSelectionCollection.tau[t]->pt) ) {temp_tau2index = t; temp_tau2_pt = mainObjectSelectionCollection.tau[t]->pt;}
                  }
                  if (  (temp_tau1index < 99999)  && (temp_tau2index < 99999)  ) {
	          	tau1_4v.SetPtEtaPhiE(mainObjectSelectionCollection.tau[temp_tau1index]->pt, mainObjectSelectionCollection.tau[temp_tau1index]->eta, mainObjectSelectionCollection.tau[temp_tau1index]->phi, mainObjectSelectionCollection.tau[temp_tau1index]->energy);
	          	tau2_4v.SetPtEtaPhiE(mainObjectSelectionCollection.tau[temp_tau2index]->pt, mainObjectSelectionCollection.tau[temp_tau2index]->eta, mainObjectSelectionCollection.tau[temp_tau2index]->phi, mainObjectSelectionCollection.tau[temp_tau2index]->energy);
		  }

	          //DiTauEtaCut
	          //loop over good taus
	          double DiTauDeltaR = tau1_4v.DeltaR(tau2_4v);

	          if(!(           ( DiTauDeltaR > 0.3)                                                     )) break;
	          myHistoColl_CR1.h_count->Fill("DiTauDeltaRCut", 1);

	          //NoBTag
	          if(!(            (int)mainObjectSelectionCollection.bjet.size() == 0                     )) break;
	          myHistoColl_CR1.h_count->Fill("NoBTag",1);

	          //MET Cut
	          bool metcut = false;
	          if (met[0].pt < 75.) metcut = true;
	          //if(!(                      metcut                                                     )) continue;
	          //ofile.count("METCut");

 
	          //DiTauInaviantMassCut
	          TLorentzVector ditau_4v = tau1_4v + tau2_4v;

	          double invmassDiTau = ditau_4v.M();
	         

	         if(!(                      invmassDiTau < 90.                                             )) break;
	         myHistoColl_CR1.h_count->Fill("DiTauInaviantMassCut",1);
 
	         //DiTauSignCut
	         int chargeDiTau = mainObjectSelectionCollection.tau[temp_tau1index]->charge * mainObjectSelectionCollection.tau[temp_tau2index]->charge;
	         if(!(                          chargeDiTau < 0.                                          )) break; //NOW REQUIRING OPPOSITE SIGN
	         myHistoColl_CR1.h_count->Fill("DiTauSignCut",1);
		 fillHistoCollection (myHistoColl_CR1, mainObjectSelectionCollection, weight);

                 break;
        	}        

	//Clearing Object Collections 
	mainObjectSelectionCollection.clear();
	baselineObjectSelectionCollection.clear();
	TauMediumIsoObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();

	}

  stream.close();
  ofile.close();
  return 0;
}

