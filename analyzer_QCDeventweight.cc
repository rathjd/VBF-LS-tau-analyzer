//-----------------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for ntuples created by TheNtupleMaker
// Created:     Fri Apr  5 13:23:28 2013 by mkntanalyzer.py
// Author:      Daniele Marconi
//-----------------------------------------------------------------------------
#include "analyzer.h"

#ifdef PROJECT_NAME
#include "PhysicsTools/TheNtupleMaker/interface/pdg.h"
#else
#include "pdg.h"
#endif

using namespace std;

// Structs useful for Analyzer

struct MyEventCollection {

        std::string label;
        bool goodVertex;
	bool passedTrigger;
        vector <electron_s*> electron;
	vector <muon_s*> muon;
	vector <tau_s*> tau;
	vector <jet_s*> jet;
	vector <jet_s*> bjet;
        vector <met_s*> met;

	MyEventCollection(const std::string & inputlabel) {
		label = inputlabel;
                goodVertex = false;
                passedTrigger = false;
	}
	void clear() {
                goodVertex = false;
                passedTrigger = false;
		electron.clear();
		muon.clear();
		tau.clear();
		jet.clear();
		bjet.clear();
		met.clear();
	}
};

struct MyHistoCollection {

	std::string label;
	TH1F* h_count;
	TH1F* h_njet;
	TH1F* h_jetpt;
	TH1F* h_jeteta;
	TH1F* h_jet1pt;
	TH1F* h_jet1eta;
	TH1F* h_jet2pt;
	TH1F* h_jet2eta;
	TH1F* h_dijetinvariantmass;
	TH1F* h_dijetdeltaeta;

	TH1F* h_tau1pt;
	TH1F* h_tau1eta;
	TH1F* h_tau2pt;
	TH1F* h_tau2eta;
	TH1F* h_ditauinvariantmass;
	TH1F* h_ditaucharge;
	TH1F* h_ditaucosdeltaphi;

	TH1F* h_met;

	TH1F* h_ht;
	TH1F* h_ht_withtau;

	MyHistoCollection(TFile * f, const std::string & inputlabel) {

		label = inputlabel;
		f->mkdir(inputlabel.c_str());
        	f->cd(inputlabel.c_str());

		h_count = new TH1F("counts", "", 1,0,1);
		h_count->SetBit(TH1::kCanRebin);
		h_count->SetStats(0);
		h_njet = new TH1F("h_njet", "h_njet", 21, -0.5, 20.5);
		h_jetpt = new TH1F("h_jetpt", "h_jetpt", 50, 0., 500.);
		h_jeteta = new TH1F("h_jeteta", "h_jeteta", 30 , -5., 5.);
		h_jet1pt = new TH1F("h_jet1pt", "h_jet1pt", 50, 0., 500.);
		h_jet1eta = new TH1F("h_jet1eta", "h_jet1eta", 50 , -5., 5.);
		h_jet2pt = new TH1F("h_jet2pt", "h_jet2pt", 50, 0., 500.);
		h_jet2eta = new TH1F("h_jet2eta", "h_jet2eta", 50 , -5., 5.);
		h_dijetinvariantmass = new TH1F("h_dijetinvariantmass","h_dijetinvariantmass", 50, 0., 2750.);
		h_dijetdeltaeta = new TH1F ("h_dijetdeltaeta", "h_dijetdeltaeta", 20, 0., 10.);

		h_tau1pt = new TH1F("h_tau1pt", "h_tau1pt", 50, 0., 500.);
		h_tau1eta = new TH1F("h_tau1eta", "h_tau1eta", 30 , -3., 3.);
		h_tau2pt = new TH1F("h_tau2pt", "h_tau2pt", 50, 0., 500.);
		h_tau2eta = new TH1F("h_tau2eta", "h_tau2eta", 30 , -3., 3.);
		h_ditauinvariantmass = new TH1F("h_ditauinvariantmass", "h_ditauinvariantmass", 20, 0., 140.);
		h_ditaucharge = new TH1F("h_ditaucharge", "h_ditaucharge", 5, -4., 6.);
		h_ditaucosdeltaphi = new TH1F("h_ditaucosdeltaphi", "h_ditaucosdeltaphi", 50, -1.1, 1.1);

		h_met = new TH1F("h_met", "h_met", 6, 0., 120.);

		h_ht = new TH1F("h_ht", "h_ht", 50, 0., 1300.);
		h_ht_withtau = new TH1F("h_ht_withtau", "h_ht_withtau", 50, 0., 1300.);
	}
};

void fillHistoCollection (MyHistoCollection &inputHistoCollection, MyEventCollection inputEventCollection,double weight) {

	// ---------------------
	// -- fill histograms --
	// ---------------------	  

          unsigned int temp_jet1index = 99999;
          unsigned int temp_jet2index = 99999;
          double temp_jet1_pt = -99999.;
          double temp_jet2_pt = -99999.;

        //JET SEL
	for (unsigned int j = 0;j<inputEventCollection.jet.size();++j){
		inputHistoCollection.h_jetpt->Fill(inputEventCollection.jet[j]->pt,weight);
		inputHistoCollection.h_jeteta->Fill(inputEventCollection.jet[j]->eta,weight);
		if (temp_jet1_pt < inputEventCollection.jet[j]->pt) {temp_jet1index = j; temp_jet1_pt = inputEventCollection.jet[j]->pt;}
	}

          inputHistoCollection.h_njet->Fill( (int)inputEventCollection.jet.size(),weight );

          if (temp_jet1index < 99999) {
             inputHistoCollection.h_jet1pt->Fill(inputEventCollection.jet[temp_jet1index]->pt,weight);
             inputHistoCollection.h_jet1eta->Fill(inputEventCollection.jet[temp_jet1index]->eta,weight);
          }

         for(unsigned int j = 0;j<inputEventCollection.jet.size();++j){
            if (j == temp_jet1index) continue;
            if ((temp_jet2_pt < inputEventCollection.jet[j]->pt) && (temp_jet1_pt > inputEventCollection.jet[j]->pt)) {temp_jet2index = j; temp_jet2_pt = inputEventCollection.jet[j]->pt;} 
         }

         if (temp_jet2index < 99999) {
            inputHistoCollection.h_jet2pt->Fill(inputEventCollection.jet[temp_jet2index]->pt,weight);
            inputHistoCollection.h_jet2eta->Fill(inputEventCollection.jet[temp_jet2index]->eta,weight);
         }

         if ( (temp_jet1index < 99999) && (temp_jet2index < 99999) ) {
       
		double invmassDiJet = 0.;

		for(unsigned int j1 = 0;j1<inputEventCollection.jet.size();++j1){

			for (unsigned int j2 = 0;j2<inputEventCollection.jet.size();++j2){

				if (j1 == j2) continue;

            			TLorentzVector jet1_4v;
            			TLorentzVector jet2_4v;
 
	        		jet1_4v.SetPtEtaPhiE(inputEventCollection.jet[j1]->pt, inputEventCollection.jet[j1]->eta, inputEventCollection.jet[j1]->phi, inputEventCollection.jet[j1]->energy);
	        		jet2_4v.SetPtEtaPhiE(inputEventCollection.jet[j2]->pt, inputEventCollection.jet[j2]->eta, inputEventCollection.jet[j2]->phi, inputEventCollection.jet[j2]->energy);

            			TLorentzVector dijet_4v = jet1_4v + jet2_4v;

				double temp_invmassDiJet =  dijet_4v.M(); 
				if (     invmassDiJet < temp_invmassDiJet   ) {invmassDiJet = temp_invmassDiJet; temp_jet1index = j1; temp_jet2index = j2;}

			}

		}

            double deltaeta =  fabs (inputEventCollection.jet[temp_jet1index]->eta - inputEventCollection.jet[temp_jet2index]->eta);
            inputHistoCollection.h_dijetinvariantmass ->Fill(invmassDiJet,weight);
            inputHistoCollection.h_dijetdeltaeta ->Fill(deltaeta,weight);

         }

         //TAUS

	          unsigned int temp_tau1index = 99999;
	          unsigned int temp_tau2index = 99999;
	          double temp_tau1_pt = -99999.;
	          double temp_tau2_pt = -99999.;
	          TLorentzVector tau1_4v;
	          TLorentzVector tau2_4v;
         
	          for(unsigned int t =0;t<inputEventCollection.tau.size();++t){
	               if (temp_tau1_pt < inputEventCollection.tau[t]->pt) {temp_tau1index = t; temp_tau1_pt = inputEventCollection.tau[t]->pt;} 
	          }

	          for(unsigned int t =0;t<inputEventCollection.tau.size();++t){
	               if ( (temp_tau2_pt < inputEventCollection.tau[t]->pt) && ( temp_tau1_pt > inputEventCollection.tau[t]->pt) ) {temp_tau2index = t; temp_tau2_pt = inputEventCollection.tau[t]->pt;} 
	          }

	         double invmassDiTau = 99999.;

	         if ( (temp_tau1index < 99999) && (temp_tau2index < 99999) ) {

 
	            tau1_4v.SetPtEtaPhiE(inputEventCollection.tau[temp_tau1index]->pt, inputEventCollection.tau[temp_tau1index]->eta, inputEventCollection.tau[temp_tau1index]->phi, inputEventCollection.tau[temp_tau1index]->energy);
	            tau2_4v.SetPtEtaPhiE(inputEventCollection.tau[temp_tau2index]->pt, inputEventCollection.tau[temp_tau2index]->eta, inputEventCollection.tau[temp_tau2index]->phi, inputEventCollection.tau[temp_tau2index]->energy);

	            TLorentzVector ditau_4v = tau1_4v + tau2_4v;

	            invmassDiTau = ditau_4v.M();
	         }

          if (temp_tau1index < 99999) {
             inputHistoCollection.h_tau1pt->Fill(inputEventCollection.tau[temp_tau1index]->pt,weight);
             inputHistoCollection.h_tau1eta->Fill(inputEventCollection.tau[temp_tau1index]->eta,weight);
          }

          if (temp_tau2index < 99999) {
             inputHistoCollection.h_tau2pt->Fill(inputEventCollection.tau[temp_tau2index]->pt,weight);
             inputHistoCollection.h_tau2eta->Fill(inputEventCollection.tau[temp_tau2index]->eta,weight);
          }

         if ( (temp_tau1index < 99999) && (temp_tau2index < 99999) ) {

            double chargeDiTau = inputEventCollection.tau[temp_tau1index]->charge * inputEventCollection.tau[temp_tau2index]->charge;

            double cosdeltaphiDiTau = cos(tau1_4v.DeltaPhi(tau2_4v));
            inputHistoCollection.h_ditauinvariantmass ->Fill(invmassDiTau,weight);
            inputHistoCollection.h_ditaucharge ->Fill(chargeDiTau,weight);
            inputHistoCollection.h_ditaucosdeltaphi ->Fill(cosdeltaphiDiTau,weight);

         }

        // MET

        inputHistoCollection.h_met -> Fill(inputEventCollection.met[0]->pt,weight);

       // HT NEEDS TO BE DEFINED AND IMPLEMENTED!!!!!!!!!!
	TLorentzVector ht_4v;

	for(unsigned int j = 0;j<inputEventCollection.jet.size();++j){
		TLorentzVector tempjet_4v;
	        tempjet_4v.SetPtEtaPhiE(inputEventCollection.jet[j]->pt, inputEventCollection.jet[j]->eta, inputEventCollection.jet[j]->phi, inputEventCollection.jet[j]->energy);
		ht_4v += tempjet_4v;
	}

	inputHistoCollection.h_ht -> Fill(ht_4v.Pt(),weight);

	for(unsigned int t = 0;t<inputEventCollection.tau.size();++t){

		TLorentzVector temptau_4v;
		temptau_4v.SetPtEtaPhiE(inputEventCollection.tau[t]->pt, inputEventCollection.tau[t]->eta, inputEventCollection.tau[t]->phi, inputEventCollection.tau[t]->energy);
		ht_4v += temptau_4v;
	}

	inputHistoCollection.h_ht_withtau -> Fill(ht_4v.Pt(),weight);
} 

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

	TH1::SetDefaultSumw2();
	TFile file_eff("/afs/naf.desy.de/user/m/marconi/public/VBFAnalyzer/effmap.root", "read");
	MyHistoCollection myHistoColl_CR1 (ofile.file_, "Ztautau_CR1"); 
	MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_TauLooseIso_CR4");

	MyEventCollection mainObjectSelectionCollection ("mainObjectSelection");
	MyEventCollection JetLooseIsoObjectSelectionCollection ("JetLooseIsoObjectSelection");
	MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
	MyEventCollection TauTightObjectSelectionCollection ("TauTightIsoObjectSelection");
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
	         TauLooseIsoObjectSelectionCollection.passedTrigger = true;
               }

	  // electron selection
	  for(unsigned int e = 0;e<electron.size();++e){
	    mainObjectSelectionCollection.electron.push_back(&electron[e]);
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
	    TauTightObjectSelectionCollection.tau.push_back(&tau[t]);
          }

          // jet baseline selection
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 15.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.5                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	  }


	// --------------------------
	// -- QCD Event Weighting  --
	// --------------------------
	
	double eventweight_1tau = 1.;
	double eventweight_2tau = 1.;

	TH2F* h2_taufakerate_eff = (TH2F*)(file_eff.Get("h2_taufakerate_eff"));
	vector<double> jet_taufakerate;

	for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
		int nbin = h2_taufakerate_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt,JetLooseIsoObjectSelectionCollection.jet[i]->eta);
		jet_taufakerate.push_back(h2_taufakerate_eff->GetBinContent(nbin));
	}

	//p0: prob to have no fake taus

	double p0 = 1.;

	for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
	
		p0 *= (1. - jet_taufakerate[i]);

	}

	//p1: prob to have al least 1 fake tau
	double p1 = 0.;

	for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){

		double	tempprob = jet_taufakerate[i];

		for(unsigned int j = 0; j < JetLooseIsoObjectSelectionCollection.jet.size(); ++j){
			if (i == j) continue;

			tempprob *= 1 - jet_taufakerate[j];

		}

		p1 += tempprob;

	}

	//eventweight: prob to have at least 2 fake taus


	eventweight_1tau = 1. - p0;

	eventweight_2tau = 1. - p0 - p1;

	 // --------------------------
	 // -- Fake Tau Creation
	 // --------------------------

	//Creating the fake taus couple
	if(!(                           JetLooseIsoObjectSelectionCollection.jet.size() >= 2           )) break;
	
	unsigned int faketau1index = 99999;		  
	unsigned int faketau2index = 99999;		  
	double fmax =0.;

	/////Selecting first tau
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
		
		fmax += jet_taufakerate[j];

	}

	double randpick = (rand() * fmax) / RAND_MAX;
	
	double ftemp =0.;
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){

		ftemp += jet_taufakerate[j];

		if (ftemp > randpick) {faketau1index = j; continue;}

	}
	////Selecting second tau
	fmax =0.;
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
		if(faketau1index == j) continue;
		fmax += jet_taufakerate[j];
	}
	randpick = (rand() * fmax) / RAND_MAX;
	ftemp =0.;
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
		if(faketau1index == j) continue;
		ftemp += jet_taufakerate[j];
		if (ftemp > randpick) {faketau2index = j; continue;}
	}

	tau_s faketau1;
	tau_s faketau2;

	faketau1.charge = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->charge;
	faketau1.p = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->p;
	faketau1.energy = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->energy;
	faketau1.et = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->et;
	faketau1.px = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->px;
	faketau1.py = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->py;
	faketau1.pz = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->pz;
	faketau1.pt = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->pt;
	faketau1.phi = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->phi;
	faketau1.eta = JetLooseIsoObjectSelectionCollection.jet[faketau1index]->eta;
	
	faketau2.charge = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->charge;
	faketau2.p = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->p;
	faketau2.energy = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->energy;
	faketau2.et = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->et;
	faketau2.px = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->px;
	faketau2.py = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->py;
	faketau2.pz = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->pz;
	faketau2.pt = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->pt;
	faketau2.phi = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->phi;
	faketau2.eta = JetLooseIsoObjectSelectionCollection.jet[faketau2index]->eta;

	mainObjectSelectionCollection.tau.push_back(&faketau1);
	mainObjectSelectionCollection.tau.push_back(&faketau2);

	TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau1);
	TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau2);

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
	    TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	  }

          // btag selection
          for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 2.4                                                               )) continue;
	    if(!(      jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244                         )) continue;
            double mindeltaRtaujet = 99999.;  for(unsigned int t =0;t<tau.size();++t){
                   if (!(       tau[t].selected    )) continue;
                   double temp_mindeltaRtaujet = deltaR(jet[j].eta, jet[j].phi, tau[t].eta, tau[t].phi); 
                   if (temp_mindeltaRtaujet < mindeltaRtaujet) mindeltaRtaujet = temp_mindeltaRtaujet;
            }
            if(!(       (mindeltaRtaujet >= 0.3) &&  (mindeltaRtaujet < 99999.)                              )) continue;
	    mainObjectSelectionCollection.bjet.push_back(&jet[j]);
	    TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
          }

	  //MET selection
	  mainObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");

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
	          myHistoColl_CR1.h_count->Fill("AtLeast1tau",eventweight_1tau);

	          //AtLeast2tau
	          if(!(             ( (int)mainObjectSelectionCollection.tau.size() >= 2 )                 )) break;
	          myHistoColl_CR1.h_count->Fill("AtLeast2tau",eventweight_2tau);

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
	          myHistoColl_CR1.h_count->Fill("DiTauDeltaRCut", eventweight_2tau);

	          //NoBTag
	          if(!(            (int)mainObjectSelectionCollection.bjet.size() == 0                     )) break;
	          myHistoColl_CR1.h_count->Fill("NoBTag",eventweight_2tau);

	          //MET Cut
	          bool metcut = false;
	          if (met[0].pt < 75.) metcut = true;
	          //if(!(                      metcut                                                     )) continue;
	          //ofile.count("METCut");

 
	          //DiTauInaviantMassCut
	          TLorentzVector ditau_4v = tau1_4v + tau2_4v;

	          double invmassDiTau = ditau_4v.M();
	         

	         if(!(                      invmassDiTau < 90.                                             )) break;
	         myHistoColl_CR1.h_count->Fill("DiTauInaviantMassCut",eventweight_2tau);
 
	         //DiTauSignCut
	         int chargeDiTau = mainObjectSelectionCollection.tau[temp_tau1index]->charge * mainObjectSelectionCollection.tau[temp_tau2index]->charge;
	         if(!(                          chargeDiTau < 0.                                          )) break; //NOW REQUIRING OPPOSITE SIGN
	         myHistoColl_CR1.h_count->Fill("DiTauSignCut",eventweight_2tau);
		 fillHistoCollection (myHistoColl_CR1, mainObjectSelectionCollection,eventweight_2tau);

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
		myHistoColl_CR4.h_count->Fill("AtLeast1tau",eventweight_1tau);

		//AtLeast2tau
		if(!(             ( (int)TauLooseIsoObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		myHistoColl_CR4.h_count->Fill("AtLeast2tau",eventweight_2tau);

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
		myHistoColl_CR4.h_count->Fill("DiTauDeltaRCut", eventweight_2tau);

	         //DiTauSignCut
	         int chargeDiTau = TauLooseIsoObjectSelectionCollection.tau[temp_tau1index]->charge * TauLooseIsoObjectSelectionCollection.tau[temp_tau2index]->charge;
	         if(!(                          chargeDiTau > 0.                                          )) break; //NOW REQUIRING SAME SIGN
	         myHistoColl_CR4.h_count->Fill("DiTauSignCut",eventweight_2tau);

		//NoBTag
		if(!(            (int)TauLooseIsoObjectSelectionCollection.bjet.size() == 0                     )) break;
		myHistoColl_CR4.h_count->Fill("NoBTag",eventweight_2tau);

		//LeadJet
		double leadjetpt = 0.;
		double leadjeteta = 0.;

		for(unsigned int j = 0;j<TauLooseIsoObjectSelectionCollection.jet.size();++j){
			if (leadjetpt < TauLooseIsoObjectSelectionCollection.jet[j]->pt) {leadjetpt = TauLooseIsoObjectSelectionCollection.jet[j]->pt; leadjeteta = TauLooseIsoObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (leadjetpt >= 75.) && (fabs(leadjeteta) < 5.)              )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",eventweight_2tau);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection, eventweight_2tau);
			break;
		}

		//SubLeadJet
		double subleadjetpt = 0.;
		double subleadjeteta = 0.;

		for(unsigned int j = 0;j<TauLooseIsoObjectSelectionCollection.jet.size();++j){
			if ((subleadjetpt < TauLooseIsoObjectSelectionCollection.jet[j]->pt) && (leadjetpt > TauLooseIsoObjectSelectionCollection.jet[j]->pt)) {subleadjetpt = TauLooseIsoObjectSelectionCollection.jet[j]->pt; subleadjeteta = TauLooseIsoObjectSelectionCollection.jet[j]->eta;}
		}
		if(!(                      (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.)          )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",eventweight_2tau);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection,eventweight_2tau);
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
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",eventweight_2tau);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection,eventweight_2tau);
			break;
		}

		//DiJetInvMassCut
		if (     invmassDiJet > 700.   ) passedDiJetMassCut = true;
		if(!(                      passedDiJetMassCut                                         )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",eventweight_2tau);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection,eventweight_2tau);
			break;
		}

		if (     (TauLooseIsoObjectSelectionCollection.jet[jet1index]->eta * TauLooseIsoObjectSelectionCollection.jet[jet2index]->eta ) < 0.         ) passedDiJetEtaSignCut = true;
		if(!(                      passedDiJetEtaSignCut                                      )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",eventweight_2tau);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection,eventweight_2tau);
			break;
		}

		if (      fabs ( TauLooseIsoObjectSelectionCollection.jet[jet1index]->eta - TauLooseIsoObjectSelectionCollection.jet[jet2index]->eta ) > 4.2   ) passedDiJetEtaCut = true;

		if(!(                      passedDiJetEtaCut                                          )) {
			myHistoColl_CR4.h_count->Fill("InvertedVBFCut",eventweight_2tau);
			fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection,eventweight_2tau);
			break;
		}


		//INVERTED VBF CUT
		if((    (leadjetpt >= 75.) && (fabs(leadjeteta)< 5.) && (subleadjetpt >= 50.) && (fabs(subleadjeteta) < 5.) && (passedDiJetDeltaRCut) && (passedDiJetEtaSignCut) && (passedDiJetEtaCut) && (passedDiJetMassCut)   )) break;
		myHistoColl_CR4.h_count->Fill("InvertedVBFCut",eventweight_2tau);

		fillHistoCollection (myHistoColl_CR4, TauLooseIsoObjectSelectionCollection,eventweight_2tau);


		break;
	}



	//Clearing Object Collections 
	mainObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();
	TauTightObjectSelectionCollection.tau.clear();
	JetLooseIsoObjectSelectionCollection.clear();
	}

  stream.close();
  ofile.close();
  return 0;
}

