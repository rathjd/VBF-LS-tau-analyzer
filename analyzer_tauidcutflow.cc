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
#include "analyzer.h"
#endif

#include "CommonHistoCollection.h"
#include "selection.h"


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

  //int nevents = 10000;
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
//ofile.count("1TauElectronVeto",0.);
ofile.count("RecoTaus",0.);
ofile.count("ElectronVeto",0.);
//ofile.count("1TauMuonVeto",0.);
ofile.count("MuonVeto",0.);
//ofile.count("1TauDecayMode",0.);
ofile.count("DecayMode",0.);
//ofile.count("1TauChargeHadrCandPt",0.);
ofile.count("ChargeHadrCandPt",0.);
//ofile.count("1TauLooseIso",0.);
ofile.count("LooseIso",0.);
//ofile.count("1TauMediumIso",0.);
ofile.count("MediumIso",0.);
//ofile.count("1TauTightIso",0.);
ofile.count("TightIso",0.);
//ofile.count("1TauEtaCut",0.);
ofile.count("EtaCut",0.);
//ofile.count("1TauPtCut",0.);
ofile.count("PtCut",0.);
	

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------

  TH1F* h_electronveto_count;
  TH1F* h_tauid_count;
  TH1F* h_gentauid_count;

  TH2F* h2_genTaueta_vs_genTaupt;

  TGraphAsymmErrors* h_genTanMatching_eff_vs_pt;
  TH1F* h_genTanMatching_eff_vs_pt_num;
  TH1F* h_genTanMatching_eff_vs_pt_den;

  TH1F* h_1tauid_taupt;
  TH1F* h_1tauid_taueta;

  TH1F* h_2tauid_tau1pt;
  TH1F* h_2tauid_tau1eta;
  TH1F* h_2tauid_tau2pt;
  TH1F* h_2tauid_tau2eta;
  TH1F* h_2tauid_ditauinvariantmass;  


  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------
  
  h_electronveto_count = new TH1F("h_electronveto_count", "", 1,0,1);
  h_electronveto_count->SetBit(TH1::kCanRebin);
  h_electronveto_count->SetStats(0);
  h_electronveto_count->Fill("AllTaus",0.);
  h_electronveto_count->Fill("ElectronVeto",0.);
  h_electronveto_count->Fill("ElectronVeto_electron",0.);
  h_electronveto_count->Fill("ElectronVeto_noelectron",0.);

  h2_genTaueta_vs_genTaupt = new  TH2F("h2_genTaueta_vs_genTaupt","h2_genTaueta_vs_genTaupt", 50, 0., 500., 30, -3., 3.);
  h2_genTaueta_vs_genTaupt->SetStats(0);
  h2_genTaueta_vs_genTaupt->GetXaxis()->SetTitle("gen #tau pt [GeV]"); 
  h2_genTaueta_vs_genTaupt->GetYaxis()->SetTitle("gen #tau #eta"); 

  h_genTanMatching_eff_vs_pt_num = new TH1F("h_genTanMatching_eff_vs_pt_num", "h_genTanMatching_eff_vs_pt_num", 50, 0., 500.);
  h_genTanMatching_eff_vs_pt_den = new TH1F("h_genTanMatching_eff_vs_pt_den", "h_genTanMatching_eff_vs_pt_den", 50, 0., 500.);

  h_tauid_count = new TH1F("h_tauid_count", "", 1,0,1);
  h_tauid_count->SetBit(TH1::kCanRebin);
  h_tauid_count->SetStats(0);
  h_tauid_count->Fill("AllTaus",0.);
  h_tauid_count->Fill("Matched_NoCuts",0.);
  h_tauid_count->Fill("ElectronVeto",0.);
  h_tauid_count->Fill("MuonVeto",0.);
  h_tauid_count->Fill("DecayMode",0.);
  h_tauid_count->Fill("ChargeHadrCandPt",0.);
  h_tauid_count->Fill("LooseIso",0.);
  h_tauid_count->Fill("MediumIso",0.);
  h_tauid_count->Fill("TightIso",0.);
  h_tauid_count->Fill("EtaCut",0.);
  h_tauid_count->Fill("PtCut",0.);
  
  h_gentauid_count = new TH1F("h_gentauid_count", "", 1,0,1);
  h_gentauid_count->SetBit(TH1::kCanRebin);
  h_gentauid_count->SetStats(0);
  h_gentauid_count->Fill("AllGenTaus",0.);
  h_gentauid_count->Fill("Matched_NoCuts",0.);
  h_gentauid_count->Fill("ElectronVeto",0.);
  h_gentauid_count->Fill("MuonVeto",0.);
  h_gentauid_count->Fill("DecayMode",0.);
  h_gentauid_count->Fill("ChargeHadrCandPt",0.);
  h_gentauid_count->Fill("LooseIso",0.);
  h_gentauid_count->Fill("MediumIso",0.);
  h_gentauid_count->Fill("TightIso",0.);
  h_gentauid_count->Fill("EtaCut",0.);
  h_gentauid_count->Fill("PtCut",0.);
  
  h_1tauid_taupt = new TH1F("h_1tauid_taupt", "h_1tauid_taupt", 50, 0., 500.);
  h_1tauid_taueta = new TH1F("h_1tauid_taueta", "h_1tauid_taueta", 30 , -3., 3.);

  h_2tauid_tau1pt = new TH1F("h_2tauid_tau1pt", "h_2tauid_tau1pt", 50, 0., 500.);
  h_2tauid_tau1eta = new TH1F("h_2tauid_tau1eta", "h_2tauid_tau1eta", 30 , -3., 3.);
  h_2tauid_tau2pt = new TH1F("h_2tauid_tau2pt", "h_2tauid_tau2pt", 50, 0., 500.);
  h_2tauid_tau2eta = new TH1F("h_2tauid_tau2eta", "h_2tauid_tau2eta", 30 , -3., 3.);
  h_2tauid_ditauinvariantmass = new TH1F("h_2tauid_ditauinvariantmass", "h_2tauid_ditauinvariantmass", 30, 0., 300.); 

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------

  double weight = 1.;

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
	  //Event Count

	  // --------------------------
	  // -- Gen Tau ID CUtFlow   --
	  // --------------------------

	  vector<unsigned int> selectedtaus;
	  selectedtaus.clear();


	  // GenTau matching.

	  cout << "-----------------------EVENT----------------------" <<endl;

	  for (unsigned int g = 0; g < GenParticleHelper.size(); g++){

		 // if (  !( (fabs(GenParticleHelper[g].status) > 20) && (fabs(GenParticleHelper[g].status) < 30) )  ) continue;
		  if (  !( (fabs(GenParticleHelper[g].status) > 0) && (fabs(GenParticleHelper[g].status) < 11) )  ) continue;
		  if ( !(fabs(GenParticleHelper[g].pdgId) == 15) ) continue;
		  //cout << "Tau mom: " << GenParticleHelper[(GenParticleHelper[g].firstMother)].pdgId <<endl;
		  bool isNotHadTau = false;
		  for (int  i = (GenParticleHelper[g].firstDaughter) ; i < (GenParticleHelper[g].lastDaughter) + 1 ; i++){
		  //	cout << "Tau daughter: " << GenParticleHelper[i].pdgId <<endl;
			if (fabs(GenParticleHelper[i].pdgId) == 15 ) isNotHadTau = true;
			if (fabs(GenParticleHelper[i].pdgId) == 13 ) { cout << "--- Decays into muon" << endl; isNotHadTau = true;}
			if (fabs(GenParticleHelper[i].pdgId) == 11 ) { cout << "--- Decays into electron" << endl; isNotHadTau = true;}
		  }
		  
		  
		  cout << "GEN TAU pt: " << GenParticleHelper[g].pt << " GEN TAU eta: " << GenParticleHelper[g].eta << " GEN TAU phi: " << GenParticleHelper[g].phi <<endl;
		  for (int  i = (GenParticleHelper[g].firstDaughter) ; i < (GenParticleHelper[g].lastDaughter) + 1 ; i++){
		  //	cout << "Tau daughter: " << GenParticleHelper[i].pdgId <<endl;
			if (fabs(GenParticleHelper[i].pdgId) == 12 || fabs(GenParticleHelper[i].pdgId) == 14 || fabs(GenParticleHelper[i].pdgId) == 16) 
				cout << "---Neutrino pt: " << GenParticleHelper[i].pt << " Neutrino eta: " << GenParticleHelper[i].eta << " Neutrino phi: " << GenParticleHelper[i].phi << endl;
		  }

		  if (isNotHadTau) continue;

		  TLorentzVector v_genTauVisible;

		  for (int  i = (GenParticleHelper[g].firstDaughter) ; i < (GenParticleHelper[g].lastDaughter) + 1 ; i++){
		  
			  TLorentzVector v_genTauVisible_temp;
			  //if (fabs(GenParticleHelper[i].pdgId) == 15 ) continue;
			  //if (fabs(GenParticleHelper[i].pdgId) == 13 ) continue;
			  //if (fabs(GenParticleHelper[i].pdgId) == 11 ) continue;
			  if (fabs(GenParticleHelper[i].pdgId) == 12 || fabs(GenParticleHelper[i].pdgId) == 14 || fabs(GenParticleHelper[i].pdgId) == 16) continue;

			  v_genTauVisible_temp.SetPtEtaPhiM (GenParticleHelper[i].pt, GenParticleHelper[i].eta, GenParticleHelper[i].phi, GenParticleHelper[i].mass);
			  
		  	  v_genTauVisible = v_genTauVisible + v_genTauVisible_temp;
		  }

		  if (   !(v_genTauVisible.Pt() > 20.)   ) continue;

		  h_gentauid_count->Fill("AllGenTaus", weight);
	          h_genTanMatching_eff_vs_pt_den->Fill(v_genTauVisible.Pt());
		  h2_genTaueta_vs_genTaupt->Fill(GenParticleHelper[g].pt,GenParticleHelper[g].eta);
		  
		  for(unsigned int t =0;t<tau.size();++t){

			  if(!( tau[t].tauID_decayModeFindingNewDMs > 0.5) ) continue;
			  if(! (tau[t].pt > 18.)) continue;

			  TLorentzVector v_genTau;
			  TLorentzVector v_recoTau;
			  

			  cout << "------RECO Tau pt: " << tau[t].pt << " RECO TAU eta: " << tau[t].eta << " RECO TAU phi: " << tau[t].phi <<endl;
			  v_genTau.SetPtEtaPhiM (GenParticleHelper[g].pt, GenParticleHelper[g].eta, GenParticleHelper[g].phi, GenParticleHelper[g].mass);	
			  v_recoTau.SetPtEtaPhiE (tau[t].pt, tau[t].eta, tau[t].phi, tau[t].energy);

			  double temp_deltaR = v_genTau.DeltaR(v_recoTau);
			  if (temp_deltaR < 0.3) {
				  selectedtaus.push_back(t);
				  h_genTanMatching_eff_vs_pt_num->Fill(v_genTauVisible.Pt());
				  cout << "------MATCHED!!!" << endl;
				  break;
			  } 
		  }
	  }

	  for (unsigned int t = 0; t < selectedtaus.size(); t++){

		  h_gentauid_count->Fill("Matched_NoCuts",weight);
	  //Appliying the Electro veto
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( (tau[ (selectedtaus[i]) ].tauID_againstElectronVLooseMVA5 > 0.5 ))) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauElectronVeto", weight);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("ElectronVeto",weight);

	  //Appliying the Muon veto
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( tau[(selectedtaus[i])].tauID_againstMuonLoose3 > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauMuonVeto",weight);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("MuonVeto",weight);

	  //Appliying the Decay mode finding
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( (tau[(selectedtaus[i])].tauID_decayModeFindingNewDMs > 0.5)/*&& (tau[t].signalPFChargedHadrCands_size > 0)*/)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauDecayMode",weight);		
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("DecayMode",weight);




	  //Appliying the read Cherged Hadron candidate
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( tau[(selectedtaus[i])].leadChargedHadrCand_pt >= 5.0)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauChargeHadrCandPt", weight);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("ChargeHadrCandPt",weight);

	  //Appliying the Loose Isolation cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!(tau[(selectedtaus[i])].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauLooseIso",0.);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("LooseIso",weight);

	  //Appliying the Medium Isolation cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!(tau[(selectedtaus[i])].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauMediumIso",0.);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("MediumIso",weight);

	  //Appliying the Tight Isolation cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!(tau[(selectedtaus[i])].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TautightIso",0.);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("TightIso",weight);

	  //Appliying the Eta cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( fabs(tau[(selectedtaus[i])].eta) <= 2.1 )) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauEtaCut", weight);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("EtaCut",weight);

	  //Appliying the Pt cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( fabs(tau[(selectedtaus[i])].pt) >= 20. )) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauPtCut", weight);
	  if (selectedtaus.size() > 1 ) h_gentauid_count->Fill("PtCut",weight);

	  }

	  // ------------------------
	  // -- Tau ID CUtFlow     --
	  // ------------------------

	  ofile.count("NoCuts",weight);

	  selectedtaus.clear();

	  for(unsigned int t =0;t<tau.size();++t){

		  h_tauid_count->Fill("AllTaus",weight);

		  // GenTau matching.


		  double deltaR = 999999.;

		  for (unsigned int g = 0; g < GenParticleHelper.size(); g++){

			  if (  !( (fabs(GenParticleHelper[g].status) > 20) && (fabs(GenParticleHelper[g].status) < 30) )  ) continue;
			  if ( !(fabs(GenParticleHelper[g].pdgId) == 15) ) continue;

			  //h_genTanMatching_eff_vs_pt_den->Fill(GenParticleHelper[g].pt);
			  //h2_genTaueta_vs_genTaupt->Fill(GenParticleHelper[g].pt,GenParticleHelper[g].eta);

			  TLorentzVector v_genTau;
			  TLorentzVector v_recoTau;

			  //cout << "GenParticleHelper[g].pt: " << GenParticleHelper[g].pt << " GenParticleHelper[g].eta: " << GenParticleHelper[g].eta <<  " GenParticleHelper[g].phi: " << GenParticleHelper[g].phi << " GenParticleHelper[g].mass: " << GenParticleHelper[g].mass << endl;

			  v_genTau.SetPtEtaPhiM (GenParticleHelper[g].pt, GenParticleHelper[g].eta, GenParticleHelper[g].phi, GenParticleHelper[g].mass);	
			  v_recoTau.SetPtEtaPhiE (tau[t].pt, tau[t].eta, tau[t].phi, tau[t].energy);

			  double temp_deltaR = v_genTau.DeltaR(v_recoTau);
			  //if (temp_deltaR < 0.3) h_genTanMatching_eff_vs_pt_num->Fill(GenParticleHelper[g].pt);
			  if (temp_deltaR < deltaR) deltaR = temp_deltaR;

		  }

		  if ( !(deltaR < 0.3) ) continue;

		  h_tauid_count->Fill("Matched_NoCuts", weight);


		  if(!( tau[t].tauID_againstElectronVLooseMVA5 > 0.5                                 )) continue;
		  h_tauid_count->Fill("ElectronVeto",weight);
		  if(!( tau[t].tauID_againstMuonLoose3 > 0.5                                 )) continue;
		  h_tauid_count->Fill("MuonVeto",weight);
		  if(!( (tau[t].tauID_decayModeFindingNewDMs > 0.5) /*&& (tau[t].signalPFChargedHadrCands_size == 1)*/        )) continue;
		  h_tauid_count->Fill("DecayMode",weight);
		  if(!( tau[t].leadChargedHadrCand_pt >= 5.0                                 )) continue;
		  h_tauid_count->Fill("ChargeHadrCandPt",weight);
		  if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5)) continue;
		  h_tauid_count->Fill("LooseIso",weight);
		  if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits > 0.5)) continue;
		  h_tauid_count->Fill("MediumIso",weight);
		  if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits > 0.5)) continue;
		  h_tauid_count->Fill("TightIso",weight);
		  if(!(        fabs(tau[t].eta) <= 2.1                                         )) continue;
		  h_tauid_count->Fill("EtaCut",weight);
		  if(!(       tau[t].pt >= 20.                                            				)) continue;
		  h_tauid_count->Fill("PtCut",weight);


	  }
	  // Filling selected taus vector
	  for(unsigned int t =0;t<tau.size();++t){
		  selectedtaus.push_back(t);
		  h_electronveto_count->Fill("AllTaus",weight);

		  if (!(tau[t].tauID_againstElectronVLooseMVA5 > 0.5)) continue;



		  h_electronveto_count->Fill("ElectronVeto",weight);


		  h_electronveto_count->Fill("ElectronVeto_electron",0.);
		  h_electronveto_count->Fill("ElectronVeto_noelectron",0.);

	  }

	  //Just reconstructed taus
	  if (selectedtaus.size() > 1 ) ofile.count("RecoTaus",weight);

	  //Appliying the Electro veto
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( (tau[ (selectedtaus[i]) ].tauID_againstElectronVLooseMVA5 > 0.5 ))) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauElectronVeto", weight);
	  if (selectedtaus.size() > 1 ) ofile.count("ElectronVeto",weight);

	  //Appliying the Muon veto
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( tau[(selectedtaus[i])].tauID_againstMuonLoose3 > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauMuonVeto",weight);
	  if (selectedtaus.size() > 1 ) ofile.count("MuonVeto",weight);

	  //Appliying the Decay mode finding
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( (tau[(selectedtaus[i])].tauID_decayModeFindingNewDMs > 0.5)/*&& (tau[t].signalPFChargedHadrCands_size > 0)*/)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauDecayMode",weight);		
	  if (selectedtaus.size() > 1 ) ofile.count("DecayMode",weight);




	  //Appliying the read Cherged Hadron candidate
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( tau[(selectedtaus[i])].leadChargedHadrCand_pt >= 5.0)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauChargeHadrCandPt", weight);
	  if (selectedtaus.size() > 1 ) ofile.count("ChargeHadrCandPt", weight);

	  //Appliying the Loose Isolation cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!(tau[(selectedtaus[i])].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauLooseIso",0.);
	  if (selectedtaus.size() > 1 ) ofile.count("LooseIso", weight);

	  //Appliying the Medium Isolation cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!(tau[(selectedtaus[i])].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauMediumIso",0.);
	  if (selectedtaus.size() > 1 ) ofile.count("MediumIso", weight);

	  //Appliying the Tight Isolation cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!(tau[(selectedtaus[i])].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits > 0.5)) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TautightIso",0.);
	  if (selectedtaus.size() > 1 ) ofile.count("TightIso", weight);

	  //Appliying the Eta cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( fabs(tau[(selectedtaus[i])].eta) <= 2.1 )) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauEtaCut", weight);
	  if (selectedtaus.size() > 1 ) ofile.count("EtaCut", weight);

	  //Appliying the Pt cut
	  for(unsigned int i =0;i<selectedtaus.size();++i){

		  if(!( fabs(tau[(selectedtaus[i])].pt) >= 20. )) selectedtaus.erase(selectedtaus.begin() + i);

	  }

	  //if (selectedtaus.size() > 0 ) ofile.count("1TauPtCut", weight);
	  if (selectedtaus.size() > 1 ) ofile.count("PtCut", weight);



  }

  //h_genTanMatching_eff_vs_pt->Divide(h_genTanMatching_eff_vs_pt_num,h_genTanMatching_eff_vs_pt_den);
  h_genTanMatching_eff_vs_pt = new TGraphAsymmErrors(h_genTanMatching_eff_vs_pt_num, h_genTanMatching_eff_vs_pt_den); 
  //h_genTanMatching_eff_vs_pt = new TGraph("h_genTanMatching_eff_vs_pt", "h_genTanMatching_eff_vs_pt", 50, 0., 500.);
  //h_genTanMatching_eff_vs_pt->SetStats(0);
  h_genTanMatching_eff_vs_pt->GetXaxis()->SetTitle("gen #tau pt [GeV]");
  h_genTanMatching_eff_vs_pt->GetYaxis()->SetTitle("#epsilon");
  h_genTanMatching_eff_vs_pt->Write();

  stream.close();
  ofile.close();
  return 0;
}
