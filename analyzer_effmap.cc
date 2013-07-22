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

void fillHistoCollection (MyHistoCollection &inputHistoCollection, MyEventCollection inputEventCollection) {

	// ---------------------
	// -- fill histograms --
	// ---------------------	  

          unsigned int temp_jet1index = 99999;
          unsigned int temp_jet2index = 99999;
          double temp_jet1_pt = -99999.;
          double temp_jet2_pt = -99999.;

        //JET SEL
	for (unsigned int j = 0;j<inputEventCollection.jet.size();++j){
		inputHistoCollection.h_jetpt->Fill(inputEventCollection.jet[j]->pt);
		inputHistoCollection.h_jeteta->Fill(inputEventCollection.jet[j]->eta);
		if (temp_jet1_pt < inputEventCollection.jet[j]->pt) {temp_jet1index = j; temp_jet1_pt = inputEventCollection.jet[j]->pt;}
	}

          inputHistoCollection.h_njet->Fill( (int)inputEventCollection.jet.size() );

          if (temp_jet1index < 99999) {
             inputHistoCollection.h_jet1pt->Fill(inputEventCollection.jet[temp_jet1index]->pt);
             inputHistoCollection.h_jet1eta->Fill(inputEventCollection.jet[temp_jet1index]->eta);
          }

         for(unsigned int j = 0;j<inputEventCollection.jet.size();++j){
            if (j == temp_jet1index) continue;
            if ((temp_jet2_pt < inputEventCollection.jet[j]->pt) && (temp_jet1_pt > inputEventCollection.jet[j]->pt)) {temp_jet2index = j; temp_jet2_pt = inputEventCollection.jet[j]->pt;} 
         }

         if (temp_jet2index < 99999) {
            inputHistoCollection.h_jet2pt->Fill(inputEventCollection.jet[temp_jet2index]->pt);
            inputHistoCollection.h_jet2eta->Fill(inputEventCollection.jet[temp_jet2index]->eta);
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
            inputHistoCollection.h_dijetinvariantmass ->Fill(invmassDiJet);
            inputHistoCollection.h_dijetdeltaeta ->Fill(deltaeta);

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
             inputHistoCollection.h_tau1pt->Fill(inputEventCollection.tau[temp_tau1index]->pt);
             inputHistoCollection.h_tau1eta->Fill(inputEventCollection.tau[temp_tau1index]->eta);
          }

          if (temp_tau2index < 99999) {
             inputHistoCollection.h_tau2pt->Fill(inputEventCollection.tau[temp_tau2index]->pt);
             inputHistoCollection.h_tau2eta->Fill(inputEventCollection.tau[temp_tau2index]->eta);
          }

         if ( (temp_tau1index < 99999) && (temp_tau2index < 99999) ) {

            double chargeDiTau = inputEventCollection.tau[temp_tau1index]->charge * inputEventCollection.tau[temp_tau2index]->charge;

            double cosdeltaphiDiTau = cos(tau1_4v.DeltaPhi(tau2_4v));
            inputHistoCollection.h_ditauinvariantmass ->Fill(invmassDiTau);
            inputHistoCollection.h_ditaucharge ->Fill(chargeDiTau);
            inputHistoCollection.h_ditaucosdeltaphi ->Fill(cosdeltaphiDiTau);

         }

        // MET

        inputHistoCollection.h_met -> Fill(inputEventCollection.met[0]->pt);

       // HT NEEDS TO BE DEFINED AND IMPLEMENTED!!!!!!!!!!
	TLorentzVector ht_4v;

	for(unsigned int j = 0;j<inputEventCollection.jet.size();++j){
		TLorentzVector tempjet_4v;
	        tempjet_4v.SetPtEtaPhiE(inputEventCollection.jet[j]->pt, inputEventCollection.jet[j]->eta, inputEventCollection.jet[j]->phi, inputEventCollection.jet[j]->energy);
		ht_4v += tempjet_4v;
	}

	inputHistoCollection.h_ht -> Fill(ht_4v.Pt());

	for(unsigned int t = 0;t<inputEventCollection.tau.size();++t){

		TLorentzVector temptau_4v;
		temptau_4v.SetPtEtaPhiE(inputEventCollection.tau[t]->pt, inputEventCollection.tau[t]->eta, inputEventCollection.tau[t]->phi, inputEventCollection.tau[t]->energy);
		ht_4v += temptau_4v;
	}

	inputHistoCollection.h_ht_withtau -> Fill(ht_4v.Pt());
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

  TH1F* h_mindeltaR = new TH1F("h_mindeltaR", "h_mindeltaR", 50,0. , 3.);

  TH2F* h2_taufakerate_num = new TH2F("h2_taufakerate_num", "h2_taufakerate_num", 50, 0., 500., 4, 0., 2.8);
  TH2F* h2_taufakerate_den = new TH2F("h2_taufakerate_den", "h2_taufakerate_den", 50, 0., 500., 4, 0., 2.8);

  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

        

	MyEventCollection mainObjectSelectionCollection ("mainObjectSelection");
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

          if(!(         vertex.size() > 0                                 )) goodVertex = false;
	  if(goodVertex){
	    if( goodVertex ) {
		mainObjectSelectionCollection.goodVertex = true;
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
	  }

          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 15.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.5                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
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
          }

	  //MET selection
	  mainObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// --   Tau Efficency    --
	// ------------------------


	while (true){

		for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
			
			double mindeltaR = 99999.;
				
			for(unsigned int t = 0;t<mainObjectSelectionCollection.tau.size();++t){

				
				TLorentzVector jet_4v;
				TLorentzVector tau_4v;

				jet_4v.SetPtEtaPhiE(JetLooseIsoObjectSelectionCollection.jet[j]->pt, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi, JetLooseIsoObjectSelectionCollection.jet[j]->energy);
				tau_4v.SetPtEtaPhiE(mainObjectSelectionCollection.tau[t]->pt, mainObjectSelectionCollection.tau[t]->eta, mainObjectSelectionCollection.tau[t]->phi, mainObjectSelectionCollection.tau[t]->energy);
				if ( jet_4v.DeltaR(tau_4v) < mindeltaR ) mindeltaR = jet_4v.DeltaR(tau_4v);
				if ( jet_4v.DeltaR(tau_4v) < 0.3 ) h2_taufakerate_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, JetLooseIsoObjectSelectionCollection.jet[j]->eta); 
			}
			if (mindeltaR < 99999.) h_mindeltaR->Fill(mindeltaR);
			h2_taufakerate_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt, JetLooseIsoObjectSelectionCollection.jet[j]->eta); 
		
		}
		break;		

	}


	//Clearing Object Collections 
	mainObjectSelectionCollection.clear();
	JetLooseIsoObjectSelectionCollection.clear();
	}

  stream.close();
  ofile.close();
  return 0;
}

