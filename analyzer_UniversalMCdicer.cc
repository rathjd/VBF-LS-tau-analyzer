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
#include "TProfile.h"
#include "FakeTau.h"
// Structs useful for Analyzer



//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  bool verbose=false; //set to true for getting debugging output

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
	//TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/V2-FlavouredMaps.root", "read");
	//TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/V2-ReducedFlavourResponseProfiles_25down.root", "read");
	
	TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/AmandeepID_Maps_AllFlavours.root", "read");
	TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/AmandeepID_ProfiledResponses_AllFlavours.root", "read");
	
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
	
	//preliminary selection collections
	MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
	MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
	MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
	MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");
	MyEventCollection JetLooseIsoObjectSelectionCollection ("JetLooseIsoObjectSelection");
	
	//final object collections
	MyEventCollection TauTTIsoObjectSelectionCollection ("TauTTIsoObjectSelection");
	MyEventCollection TauTMiIsoObjectSelectionCollection ("TauTMiIsoObjectSelection");
	MyEventCollection TauMMiIsoObjectSelectionCollection ("TauMMiIsoObjectSelection");
	MyEventCollection TauLLiIsoObjectSelectionCollection ("TauLLiIsoObjectSelection");
	MyEventCollection TauNNIsoObjectSelectionCollection ("TauNNIsoObjectSelection");
	

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------

//declare efficiencies
double eff_real_T=0.834;//1;
double eff_real_M=0.45*eff_real_T;//0.88;
double eff_real_L=0.405*eff_real_T;//0.7;
double eff_real_N=0.217*eff_real_T;//0.43;

double eff_fake_N=0.045/eff_real_T;//0.052;
double eff_fake_L=0.344/eff_real_T;//0.46;
double eff_fake_M=0.566/eff_real_T;//0.64;
double eff_fake_T=0.613/eff_real_T;//0.72;

//scale ChargeMaps with Trigger efficiencies
TH2F *ChargeMapN_eff_Uds = (TH2F*)file_eff.Get("ChargeMapN_eff_Uds");
TH2F *ChargeMapN_eff_C   = (TH2F*)file_eff.Get("ChargeMapN_eff_C");
TH2F *ChargeMapN_eff_B   = (TH2F*)file_eff.Get("ChargeMapN_eff_B");
TH2F *ChargeMapN_eff_G   = (TH2F*)file_eff.Get("ChargeMapN_eff_G");
TH2F *ChargeMapN_eff_Un  = (TH2F*)file_eff.Get("ChargeMapN_eff_Un");
ChargeMapN_eff_Uds->Scale(eff_fake_N);
ChargeMapN_eff_C->Scale(eff_fake_N);
ChargeMapN_eff_B->Scale(eff_fake_N);
ChargeMapN_eff_G->Scale(eff_fake_N);
ChargeMapN_eff_Un->Scale(eff_fake_N);

TH2F *ChargeMapL_eff_Uds = (TH2F*)file_eff.Get("ChargeMapL_eff_Uds");
TH2F *ChargeMapL_eff_C   = (TH2F*)file_eff.Get("ChargeMapL_eff_C");
TH2F *ChargeMapL_eff_B   = (TH2F*)file_eff.Get("ChargeMapL_eff_B");
TH2F *ChargeMapL_eff_G   = (TH2F*)file_eff.Get("ChargeMapL_eff_G");
TH2F *ChargeMapL_eff_Un  = (TH2F*)file_eff.Get("ChargeMapL_eff_Un");
ChargeMapL_eff_Uds->Scale(eff_fake_L);
ChargeMapL_eff_C->Scale(eff_fake_L);
ChargeMapL_eff_B->Scale(eff_fake_L);
ChargeMapL_eff_G->Scale(eff_fake_L);
ChargeMapL_eff_Un->Scale(eff_fake_L);

TH2F *ChargeMapM_eff_Uds = (TH2F*)file_eff.Get("ChargeMapM_eff_Uds");
TH2F *ChargeMapM_eff_C   = (TH2F*)file_eff.Get("ChargeMapM_eff_C");
TH2F *ChargeMapM_eff_B   = (TH2F*)file_eff.Get("ChargeMapM_eff_B");
TH2F *ChargeMapM_eff_G   = (TH2F*)file_eff.Get("ChargeMapM_eff_G");
TH2F *ChargeMapM_eff_Un  = (TH2F*)file_eff.Get("ChargeMapM_eff_Un");
ChargeMapM_eff_Uds->Scale(eff_fake_M);
ChargeMapM_eff_C->Scale(eff_fake_M);
ChargeMapM_eff_B->Scale(eff_fake_M);
ChargeMapM_eff_G->Scale(eff_fake_M);
ChargeMapM_eff_Un->Scale(eff_fake_M);

TH2F *ChargeMapT_eff_Uds = (TH2F*)file_eff.Get("ChargeMapT_eff_Uds");
TH2F *ChargeMapT_eff_C   = (TH2F*)file_eff.Get("ChargeMapT_eff_C");
TH2F *ChargeMapT_eff_B   = (TH2F*)file_eff.Get("ChargeMapT_eff_B");
TH2F *ChargeMapT_eff_G   = (TH2F*)file_eff.Get("ChargeMapT_eff_G");
TH2F *ChargeMapT_eff_Un  = (TH2F*)file_eff.Get("ChargeMapT_eff_Un");
ChargeMapT_eff_Uds->Scale(eff_fake_T);
ChargeMapT_eff_C->Scale(eff_fake_T);
ChargeMapT_eff_B->Scale(eff_fake_T);
ChargeMapT_eff_G->Scale(eff_fake_T);
ChargeMapT_eff_Un->Scale(eff_fake_T);

//load Rescale Weight profiles
TProfile *RescaleWeightN_Uds = (TProfile*)file_Resp.Get("RescaleWeightN_Uds");
TProfile *RescaleWeightN_C   = (TProfile*)file_Resp.Get("RescaleWeightN_C");
TProfile *RescaleWeightN_B   = (TProfile*)file_Resp.Get("RescaleWeightN_B");
TProfile *RescaleWeightN_G   = (TProfile*)file_Resp.Get("RescaleWeightN_G");
TProfile *RescaleWeightN_Un  = (TProfile*)file_Resp.Get("RescaleWeightN_Un");

TProfile *RescaleWeightL_Uds = (TProfile*)file_Resp.Get("RescaleWeightL_Uds");
TProfile *RescaleWeightL_C   = (TProfile*)file_Resp.Get("RescaleWeightL_C");
TProfile *RescaleWeightL_B   = (TProfile*)file_Resp.Get("RescaleWeightL_B");
TProfile *RescaleWeightL_G   = (TProfile*)file_Resp.Get("RescaleWeightL_G");
TProfile *RescaleWeightL_Un  = (TProfile*)file_Resp.Get("RescaleWeightL_Un");

TProfile *RescaleWeightM_Uds = (TProfile*)file_Resp.Get("RescaleWeightM_Uds");
TProfile *RescaleWeightM_C   = (TProfile*)file_Resp.Get("RescaleWeightM_C");
TProfile *RescaleWeightM_B   = (TProfile*)file_Resp.Get("RescaleWeightM_B");
TProfile *RescaleWeightM_G   = (TProfile*)file_Resp.Get("RescaleWeightM_G");
TProfile *RescaleWeightM_Un  = (TProfile*)file_Resp.Get("RescaleWeightM_Un");

TProfile *RescaleWeightT_Uds = (TProfile*)file_Resp.Get("RescaleWeightT_Uds");
TProfile *RescaleWeightT_C   = (TProfile*)file_Resp.Get("RescaleWeightT_C");
TProfile *RescaleWeightT_B   = (TProfile*)file_Resp.Get("RescaleWeightT_B");
TProfile *RescaleWeightT_G   = (TProfile*)file_Resp.Get("RescaleWeightT_G");
TProfile *RescaleWeightT_Un  = (TProfile*)file_Resp.Get("RescaleWeightT_Un");

//load Scale Factors pT profiles
TProfile *ScaleFactorN_Uds = (TProfile*)file_Resp.Get("ScaleFactorN_Uds");
TProfile *ScaleFactorN_C   = (TProfile*)file_Resp.Get("ScaleFactorN_C");
TProfile *ScaleFactorN_B   = (TProfile*)file_Resp.Get("ScaleFactorN_B");
TProfile *ScaleFactorN_G   = (TProfile*)file_Resp.Get("ScaleFactorN_G");
TProfile *ScaleFactorN_Un  = (TProfile*)file_Resp.Get("ScaleFactorN_Un");

TProfile *ScaleFactorL_Uds = (TProfile*)file_Resp.Get("ScaleFactorL_Uds");
TProfile *ScaleFactorL_C   = (TProfile*)file_Resp.Get("ScaleFactorL_C");
TProfile *ScaleFactorL_B   = (TProfile*)file_Resp.Get("ScaleFactorL_B");
TProfile *ScaleFactorL_G   = (TProfile*)file_Resp.Get("ScaleFactorL_G");
TProfile *ScaleFactorL_Un  = (TProfile*)file_Resp.Get("ScaleFactorL_Un");

TProfile *ScaleFactorM_Uds = (TProfile*)file_Resp.Get("ScaleFactorM_Uds");
TProfile *ScaleFactorM_C   = (TProfile*)file_Resp.Get("ScaleFactorM_C");
TProfile *ScaleFactorM_B   = (TProfile*)file_Resp.Get("ScaleFactorM_B");
TProfile *ScaleFactorM_G   = (TProfile*)file_Resp.Get("ScaleFactorM_G");
TProfile *ScaleFactorM_Un  = (TProfile*)file_Resp.Get("ScaleFactorM_Un");

TProfile *ScaleFactorT_Uds = (TProfile*)file_Resp.Get("ScaleFactorT_Uds");
TProfile *ScaleFactorT_C   = (TProfile*)file_Resp.Get("ScaleFactorT_C");
TProfile *ScaleFactorT_B   = (TProfile*)file_Resp.Get("ScaleFactorT_B");
TProfile *ScaleFactorT_G   = (TProfile*)file_Resp.Get("ScaleFactorT_G");
TProfile *ScaleFactorT_Un  = (TProfile*)file_Resp.Get("ScaleFactorT_Un");

//load Scale Factors energy profiles
TProfile *ScaleFactorEnergyN_Uds = (TProfile*)file_Resp.Get("ScaleFactorEnergyN_Uds");
TProfile *ScaleFactorEnergyN_C   = (TProfile*)file_Resp.Get("ScaleFactorEnergyN_C");
TProfile *ScaleFactorEnergyN_B   = (TProfile*)file_Resp.Get("ScaleFactorEnergyN_B");
TProfile *ScaleFactorEnergyN_G   = (TProfile*)file_Resp.Get("ScaleFactorEnergyN_G");
TProfile *ScaleFactorEnergyN_Un  = (TProfile*)file_Resp.Get("ScaleFactorEnergyN_Un");

TProfile *ScaleFactorEnergyL_Uds = (TProfile*)file_Resp.Get("ScaleFactorEnergyL_Uds");
TProfile *ScaleFactorEnergyL_C   = (TProfile*)file_Resp.Get("ScaleFactorEnergyL_C");
TProfile *ScaleFactorEnergyL_B   = (TProfile*)file_Resp.Get("ScaleFactorEnergyL_B");
TProfile *ScaleFactorEnergyL_G   = (TProfile*)file_Resp.Get("ScaleFactorEnergyL_G");
TProfile *ScaleFactorEnergyL_Un  = (TProfile*)file_Resp.Get("ScaleFactorEnergyL_Un");

TProfile *ScaleFactorEnergyM_Uds = (TProfile*)file_Resp.Get("ScaleFactorEnergyM_Uds");
TProfile *ScaleFactorEnergyM_C   = (TProfile*)file_Resp.Get("ScaleFactorEnergyM_C");
TProfile *ScaleFactorEnergyM_B   = (TProfile*)file_Resp.Get("ScaleFactorEnergyM_B");
TProfile *ScaleFactorEnergyM_G   = (TProfile*)file_Resp.Get("ScaleFactorEnergyM_G");
TProfile *ScaleFactorEnergyM_Un  = (TProfile*)file_Resp.Get("ScaleFactorEnergyM_Un");

TProfile *ScaleFactorEnergyT_Uds = (TProfile*)file_Resp.Get("ScaleFactorEnergyT_Uds");
TProfile *ScaleFactorEnergyT_C   = (TProfile*)file_Resp.Get("ScaleFactorEnergyT_C");
TProfile *ScaleFactorEnergyT_B   = (TProfile*)file_Resp.Get("ScaleFactorEnergyT_B");
TProfile *ScaleFactorEnergyT_G   = (TProfile*)file_Resp.Get("ScaleFactorEnergyT_G");
TProfile *ScaleFactorEnergyT_Un  = (TProfile*)file_Resp.Get("ScaleFactorEnergyT_Un");

  for(int entry=0; entry < nevents; ++entry)
	{
	if(verbose)std::cout<<entry<<std::endl;
	//initialize event weights
	double weightTT=0.;
	double weightTMi=0.;
	double weightMMi=0.;
	double weightLLi=0.;
	double weightNN=0.;
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
	  
	  
	//search for gentaus
	std::vector<genparticlehelper_s*> genTau; 
	std::vector<genparticlehelper_s*> genMu;
	std::vector<genparticlehelper_s*> genE;
	std::vector<genparticlehelper_s*> genUds; 
	std::vector<genparticlehelper_s*> genC; 
	std::vector<genparticlehelper_s*> genB; 
	std::vector<genparticlehelper_s*> genG; 
	  
        for (unsigned int g = 0; g < genparticlehelper.size(); g++){
		  if (  !(fabs(genparticlehelper[g].status)==3)  ) continue;
		  if (fabs(genparticlehelper[g].pdgId) == 15) 						genTau.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) == 13) 						genMu.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) == 11) 						genE.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) <= 3 &&  fabs(genparticlehelper[g].pdgId) >=1) 	genUds.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) == 4) 						genC.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) == 5) 						genB.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) == 21) 						genG.push_back(&genparticlehelper[g]); 
		}
	
          //smart tau selection of real matched generator taus
	  for(unsigned int t =0;t<tau.size();++t){
	    
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronMediumMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonLoose3 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFindingNewDMs > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    double dR=5.;
	    if(genTau.size()>0) dR=deltaR(tau[t].eta, tau[t].phi, genTau[0]->eta, genTau[0]->phi);
            if(dR<0.3){
	      if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT  <= 0.5)) TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      else if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT  <= 0.5)) TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      else if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT  <= 0.5)) TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      else TauNoIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
          }
	  
	realTauMass(TauTightIsoObjectSelectionCollection);
	realTauMass(TauMediumIsoObjectSelectionCollection);
	realTauMass(TauLooseIsoObjectSelectionCollection);
	realTauMass(TauNoIsoObjectSelectionCollection);  
	  
	vector<double> jet_taufakerateT;
	vector<double> jet_taufakerateM;
	vector<double> jet_taufakerateMi;
	vector<double> jet_taufakerateL;
	vector<double> jet_taufakerateLi;
	vector<double> jet_taufakerateN;
	vector<int>    Flavour;
	
	// jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	  double dR=5.;
	  if(genTau.size()>0) dR=deltaR(jet[j].eta, jet[j].phi, genTau[0]->eta, genTau[0]->phi); //remove real taus out of jet sample
	  for(int i=0; i<genMu.size(); i++){
	    double dRtemp = deltaR(jet[j].eta, jet[j].phi, genMu[i]->eta, genMu[i]->phi);
	    if(dRtemp<dR) dR;
	  }
	  for(int i=0; i<genE.size(); i++){
	    double dRtemp = deltaR(jet[j].eta, jet[j].phi, genE[i]->eta, genE[i]->phi);
	    if(dRtemp<dR) dR;
	  }
	  if(dR<0.3) continue;
	  if(!( jet[j].pt >= 30. )) 		continue;
	  if(!( fabs(jet[j].eta) <= 2.6 )) 	continue;
	  JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}
	
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
	  //search for most likely origin parton
	  double dRorigin=5.;
	  int CulpritCode=0;
	  for(unsigned int i=0; i<genUds.size(); i++){
	    double dRtemp=deltaR(jet[j].eta, jet[j].phi, genUds[i]->eta, genUds[i]->phi);
	    if(dRtemp<dRorigin){
	      dRorigin=dRtemp;
	      if(dRorigin<0.3) CulpritCode=1;
	    }  
	  }
	  for(unsigned int i=0; i<genC.size(); i++){
	    double dRtemp=deltaR(jet[j].eta, jet[j].phi, genC[i]->eta, genC[i]->phi);
	    if(dRtemp<dRorigin){
	      dRorigin=dRtemp;
	      if(dRorigin<0.3) CulpritCode=4;
	    }  
	  }
	  for(unsigned int i=0; i<genB.size(); i++){
	    double dRtemp=deltaR(jet[j].eta, jet[j].phi, genB[i]->eta, genB[i]->phi);
	    if(dRtemp<dRorigin){
	      dRorigin=dRtemp;
	      if(dRorigin<0.3) CulpritCode=5;
	    }  
	  }
	  for(unsigned int i=0; i<genG.size(); i++){
	    double dRtemp=deltaR(jet[j].eta, jet[j].phi, genG[i]->eta, genG[i]->phi);
	    if(dRtemp<dRorigin){
	      dRorigin=dRtemp;
	      if(dRorigin<0.3) CulpritCode=21;
	    }  
	  }
	  Flavour.push_back(CulpritCode);
	  
	  double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
	  double Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;		
	  int nChargeBin = ChargeMapN_eff_Uds->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[j]->pt);
	  int nRescaleBin= RescaleWeightN_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
	  if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta) <=2.1)
  	    {
	      if(CulpritCode==1){
    	        jet_taufakerateN.push_back(ChargeMapN_eff_Uds->GetBinContent(nChargeBin)	*RescaleWeightN_Uds->GetBinContent(nRescaleBin));
    	        jet_taufakerateL.push_back(ChargeMapL_eff_Uds->GetBinContent(nChargeBin)	*RescaleWeightL_Uds->GetBinContent(nRescaleBin));
    	        jet_taufakerateM.push_back(ChargeMapM_eff_Uds->GetBinContent(nChargeBin)	*RescaleWeightM_Uds->GetBinContent(nRescaleBin));
    	        jet_taufakerateT.push_back(ChargeMapT_eff_Uds->GetBinContent(nChargeBin)	*RescaleWeightT_Uds->GetBinContent(nRescaleBin));
		if(verbose) std::cout<<"Uds: "<<jet_taufakerateN[j]<<std::endl;
	      }
	      else if(CulpritCode==4){
	        jet_taufakerateN.push_back(ChargeMapN_eff_C->GetBinContent(nChargeBin)		*RescaleWeightN_C->GetBinContent(nRescaleBin));
    	        jet_taufakerateL.push_back(ChargeMapL_eff_C->GetBinContent(nChargeBin)		*RescaleWeightL_C->GetBinContent(nRescaleBin));
    	        jet_taufakerateM.push_back(ChargeMapM_eff_C->GetBinContent(nChargeBin)		*RescaleWeightM_C->GetBinContent(nRescaleBin));
    	        jet_taufakerateT.push_back(ChargeMapT_eff_C->GetBinContent(nChargeBin)		*RescaleWeightT_C->GetBinContent(nRescaleBin));
		if(verbose) std::cout<<"C: "<<jet_taufakerateN[j]<<std::endl;
	      }
	      else if(CulpritCode==5){
	        jet_taufakerateN.push_back(ChargeMapN_eff_B->GetBinContent(nChargeBin)		*RescaleWeightN_B->GetBinContent(nRescaleBin));
    	        jet_taufakerateL.push_back(ChargeMapL_eff_B->GetBinContent(nChargeBin)		*RescaleWeightL_B->GetBinContent(nRescaleBin));
    	        jet_taufakerateM.push_back(ChargeMapM_eff_B->GetBinContent(nChargeBin)		*RescaleWeightM_B->GetBinContent(nRescaleBin));
    	        jet_taufakerateT.push_back(ChargeMapT_eff_B->GetBinContent(nChargeBin)		*RescaleWeightT_B->GetBinContent(nRescaleBin));
		if(verbose) std::cout<<"B: "<<jet_taufakerateN[j]<<std::endl;
	      }
	     else if(CulpritCode==21){
	        jet_taufakerateN.push_back(ChargeMapN_eff_G->GetBinContent(nChargeBin)		*RescaleWeightN_G->GetBinContent(nRescaleBin));
    	        jet_taufakerateL.push_back(ChargeMapL_eff_G->GetBinContent(nChargeBin)		*RescaleWeightL_G->GetBinContent(nRescaleBin));
    	        jet_taufakerateM.push_back(ChargeMapM_eff_G->GetBinContent(nChargeBin)		*RescaleWeightM_G->GetBinContent(nRescaleBin));
    	        jet_taufakerateT.push_back(ChargeMapT_eff_G->GetBinContent(nChargeBin)		*RescaleWeightT_G->GetBinContent(nRescaleBin));
		if(verbose) std::cout<<"G: "<<jet_taufakerateN[j]<<std::endl;
	      }
	     else if(CulpritCode==0){
	        jet_taufakerateN.push_back(ChargeMapN_eff_Un->GetBinContent(nChargeBin)		*RescaleWeightN_Un->GetBinContent(nRescaleBin));
    	        jet_taufakerateL.push_back(ChargeMapL_eff_Un->GetBinContent(nChargeBin)		*RescaleWeightL_Un->GetBinContent(nRescaleBin));
    	        jet_taufakerateM.push_back(ChargeMapM_eff_Un->GetBinContent(nChargeBin)		*RescaleWeightM_Un->GetBinContent(nRescaleBin));
    	        jet_taufakerateT.push_back(ChargeMapT_eff_Un->GetBinContent(nChargeBin)		*RescaleWeightT_Un->GetBinContent(nRescaleBin));
		if(verbose) std::cout<<"Un: "<<jet_taufakerateN[j]<<std::endl;
	      } 
	     else{
	          jet_taufakerateN.push_back(0);
    		  jet_taufakerateL.push_back(0);
		  jet_taufakerateM.push_back(0);
		  jet_taufakerateT.push_back(0);
		  if(verbose)std::cout<<"no match found"<<std::endl;
	     } 
  	    }
	  else
  	    {
    	      /*double jetMindR2=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
    	      if(jetMindR > 0.5 && jetMindR2 > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.2)
      	        {	      
        	  jet_taufakerateN.push_back(ChargeMapN_eff->GetBinContent(nChargebin)*ReweightFactorN->GetBinContent(nRescaleBin));
        	  jet_taufakerateL.push_back(ChargeMapL_eff->GetBinContent(nChargebin)*ReweightFactorL->GetBinContent(nRescaleBin));
        	  jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nChargebin)*ReweightFactorM->GetBinContent(nRescaleBin));
        	  jet_taufakerateT.push_back(ChargeMapT_eff->GetBinContent(nChargebin)*ReweightFactorT->GetBinContent(nRescaleBin));
      	        }
    	      else
      	        {*/
        	  jet_taufakerateN.push_back(0);
    		  jet_taufakerateL.push_back(0);
		  jet_taufakerateM.push_back(0);
		  jet_taufakerateT.push_back(0);
      		//}
	    }
	    //fill common vectors
	    jet_taufakerateLi.push_back(jet_taufakerateL[j]+jet_taufakerateN[j]);
	    jet_taufakerateMi.push_back(jet_taufakerateM[j]+jet_taufakerateLi[j]);
	    if(jet_taufakerateLi[j]>1)std::cout<<"Li>1 error!"<<std::endl;
	    if(verbose) std::cout<<j<<": "<<jet_taufakerateN[j]<<", "<<jet_taufakerateL[j]<<", "<<jet_taufakerateM[j]<<", "<<jet_taufakerateT[j]<<std::endl;
	}
	if(verbose) std::cout<<"---------------"<<std::endl;
	if(genTau.size()==1){
	if(verbose)std::cout<<"enter one genTau scenario"<<std::endl;
	
	//choose scenario, then roll fakes
	if(TauTightIsoObjectSelectionCollection.tau.size()==1){
	
	  //T+T || Mi
	  if(verbose)std::cout<<"1 tight"<<std::endl;
	  
	  //dice T for TT
	  SingleFake TforTT("TforTT");
	  TforTT.generateSingle(jet_taufakerateT, eff_real_T);
	  weightTT=TforTT.weight;
	  if(verbose) std::cout<<"jet #"<<TforTT.index<<std::endl;
	  if(TforTT.index >=0){
	    int nScaleBinP	  		= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTT.index]->pt);
	    if(verbose) std::cout<<nScaleBinP<<std::endl;
	    double scaleP 	  		= 0.;
	    if(Flavour[TforTT.index] == 1) 	scaleP = ScaleFactorT_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTT.index] == 4)	scaleP = ScaleFactorT_C->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTT.index] == 5)	scaleP = ScaleFactorT_B->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTT.index] == 21)scaleP = ScaleFactorT_G->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTT.index] == 0) scaleP = ScaleFactorT_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE	  		= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTT.index]->energy);
	    double scaleE 	  		= 0.;
	    if(Flavour[TforTT.index] == 1) 	scaleE = ScaleFactorEnergyT_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTT.index] == 4)	scaleE = ScaleFactorEnergyT_C->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTT.index] == 5)	scaleE = ScaleFactorEnergyT_B->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTT.index] == 21)scaleE = ScaleFactorEnergyT_G->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTT.index] == 0) scaleE = ScaleFactorEnergyT_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightTT=0;}
	  
	    tau_s faketauT = fakeTau(JetLooseIsoObjectSelectionCollection, TforTT.index, scaleP, scaleE);
	    if(TauTightIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
	      TauTTIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);
	      TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT);
	    }
	    else{
	      TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT);
	      TauTTIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightTT=0.;
	  
	  //dice Mi for TMi
	  SingleFake MiforTMi("MiforTMi");
	  MiforTMi.generateSingle(jet_taufakerateMi, eff_real_T);
	  weightTMi=MiforTMi.weight;
	  
	  if(MiforTMi.index >=0){
	    int nScaleBinP	  	= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MiforTMi.index]->pt);
	    double scaleP 	  	= 0.;
	    if(Flavour[MiforTMi.index] == 1){
	      scaleP += ScaleFactorM_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforTMi.index];
	      scaleP += ScaleFactorL_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforTMi.index];
	      scaleP += ScaleFactorN_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforTMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 4){
	      scaleP += ScaleFactorM_C->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforTMi.index];
	      scaleP += ScaleFactorL_C->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforTMi.index];
	      scaleP += ScaleFactorN_C->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforTMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 5){
	      scaleP += ScaleFactorM_B->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforTMi.index];
	      scaleP += ScaleFactorL_B->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforTMi.index];
	      scaleP += ScaleFactorN_B->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforTMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 21){
	      scaleP += ScaleFactorM_G->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforTMi.index];
	      scaleP += ScaleFactorL_G->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforTMi.index];
	      scaleP += ScaleFactorN_G->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforTMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 0){
	      scaleP += ScaleFactorM_Un->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforTMi.index];
	      scaleP += ScaleFactorL_Un->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforTMi.index];
	      scaleP += ScaleFactorN_Un->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforTMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    int nScaleBinE	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MiforTMi.index]->energy);
	    double scaleE 	  	= 0.;
	    if(Flavour[MiforTMi.index] == 1){
	      scaleE += ScaleFactorEnergyM_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateM[MiforTMi.index];
	      scaleE += ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateL[MiforTMi.index];
	      scaleE += ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateN[MiforTMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 4){
	      scaleE += ScaleFactorEnergyM_C->GetBinContent(nScaleBinE)		*jet_taufakerateM[MiforTMi.index];
	      scaleE += ScaleFactorEnergyL_C->GetBinContent(nScaleBinE)		*jet_taufakerateL[MiforTMi.index];
	      scaleE += ScaleFactorEnergyN_C->GetBinContent(nScaleBinE)		*jet_taufakerateN[MiforTMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 5){
	      scaleE += ScaleFactorEnergyM_B->GetBinContent(nScaleBinE)		*jet_taufakerateM[MiforTMi.index];
	      scaleE += ScaleFactorEnergyL_B->GetBinContent(nScaleBinE)		*jet_taufakerateL[MiforTMi.index];
	      scaleE += ScaleFactorEnergyN_B->GetBinContent(nScaleBinE)		*jet_taufakerateN[MiforTMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 21){
	      scaleE += ScaleFactorEnergyM_G->GetBinContent(nScaleBinE)		*jet_taufakerateM[MiforTMi.index];
	      scaleE += ScaleFactorEnergyL_G->GetBinContent(nScaleBinE)		*jet_taufakerateL[MiforTMi.index];
	      scaleE += ScaleFactorEnergyN_G->GetBinContent(nScaleBinE)		*jet_taufakerateN[MiforTMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }
	    else if(Flavour[MiforTMi.index] == 0){
	      scaleE += ScaleFactorEnergyM_Un->GetBinContent(nScaleBinE)	*jet_taufakerateM[MiforTMi.index];
	      scaleE += ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE)	*jet_taufakerateL[MiforTMi.index];
	      scaleE += ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE)	*jet_taufakerateN[MiforTMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforTMi.index]);
	    }		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightTMi=0;}
	  
	    tau_s faketauMi = fakeTau(JetLooseIsoObjectSelectionCollection, MiforTMi.index, scaleP, scaleE);
	    if(TauTightIsoObjectSelectionCollection.tau[0]->pt > faketauMi.pt){
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);
	    }
	    else{
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightTMi=0.;
	}
	
	//M+T || Mi
	if(TauMediumIsoObjectSelectionCollection.tau.size()==1){
	  if(verbose)std::cout<<"1 medium"<<std::endl;
	  
	  //dice T for TMi
	  SingleFake TforTMi("TforTMi");
	  TforTMi.generateSingle(jet_taufakerateT, eff_real_M);
	  weightTMi=TforTMi.weight;
	  
	  if(TforTMi.index >=0){
	    int nScaleBinP	  			= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTMi.index]->pt);
	    double scaleP 	  			= 0.;
	    if(Flavour[TforTMi.index] == 1) 		scaleP = ScaleFactorT_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 4)	scaleP = ScaleFactorT_C->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 5)	scaleP = ScaleFactorT_B->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 21)	scaleP = ScaleFactorT_G->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] ==0) 	scaleP = ScaleFactorT_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE	  			= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTMi.index]->energy);
	    double scaleE 	  			= 0.;
	    if(Flavour[TforTMi.index] == 1) 		scaleE = ScaleFactorEnergyT_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 4)	scaleE = ScaleFactorEnergyT_C->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 5)	scaleE = ScaleFactorEnergyT_B->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 21)	scaleE = ScaleFactorEnergyT_G->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 0)	scaleE = ScaleFactorEnergyT_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightTMi=0;}
	  
	    tau_s faketauT = fakeTau(JetLooseIsoObjectSelectionCollection, TforTMi.index, scaleP, scaleE);
	    if(TauMediumIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
	    }
	    else{
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightTMi=0.;
	  
	  //dice Mi for MMi
	  SingleFake MiforMMi("MiforMMi");
	  MiforMMi.generateSingle(jet_taufakerateMi, eff_real_M);
	  weightMMi=MiforMMi.weight;
	  
	  if(MiforMMi.index >= 0){
	    int nScaleBinP	  	= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MiforMMi.index]->pt);
	    double scaleP 	  	= 0.;
	    if(Flavour[MiforMMi.index] == 1){
	      scaleP += ScaleFactorM_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforMMi.index];
	      scaleP += ScaleFactorL_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforMMi.index];
	      scaleP += ScaleFactorN_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforMMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 4){
	      scaleP += ScaleFactorM_C->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforMMi.index];
	      scaleP += ScaleFactorL_C->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforMMi.index];
	      scaleP += ScaleFactorN_C->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforMMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 5){
	      scaleP += ScaleFactorM_B->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforMMi.index];
	      scaleP += ScaleFactorL_B->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforMMi.index];
	      scaleP += ScaleFactorN_B->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforMMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 21){
	      scaleP += ScaleFactorM_G->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforMMi.index];
	      scaleP += ScaleFactorL_G->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforMMi.index];
	      scaleP += ScaleFactorN_G->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforMMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 0){
	      scaleP += ScaleFactorM_Un->GetBinContent(nScaleBinP)	*jet_taufakerateM[MiforMMi.index];
	      scaleP += ScaleFactorL_Un->GetBinContent(nScaleBinP)	*jet_taufakerateL[MiforMMi.index];
	      scaleP += ScaleFactorN_Un->GetBinContent(nScaleBinP)	*jet_taufakerateN[MiforMMi.index];
	      scaleP *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    int nScaleBinE	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MiforMMi.index]->energy);
	    double scaleE 	  	= 0.;
	    if(Flavour[MiforMMi.index] == 1){
	      scaleE += ScaleFactorEnergyM_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateM[MiforMMi.index];
	      scaleE += ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateL[MiforMMi.index];
	      scaleE += ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateN[MiforMMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 4){
	      scaleE += ScaleFactorEnergyM_C->GetBinContent(nScaleBinE)		*jet_taufakerateM[MiforMMi.index];
	      scaleE += ScaleFactorEnergyL_C->GetBinContent(nScaleBinE)		*jet_taufakerateL[MiforMMi.index];
	      scaleE += ScaleFactorEnergyN_C->GetBinContent(nScaleBinE)		*jet_taufakerateN[MiforMMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 5){
	      scaleE += ScaleFactorEnergyM_B->GetBinContent(nScaleBinE)		*jet_taufakerateM[MiforMMi.index];
	      scaleE += ScaleFactorEnergyL_B->GetBinContent(nScaleBinE)		*jet_taufakerateL[MiforMMi.index];
	      scaleE += ScaleFactorEnergyN_B->GetBinContent(nScaleBinE)		*jet_taufakerateN[MiforMMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 21){
	      scaleE += ScaleFactorEnergyM_G->GetBinContent(nScaleBinE)		*jet_taufakerateM[MiforMMi.index];
	      scaleE += ScaleFactorEnergyL_G->GetBinContent(nScaleBinE)		*jet_taufakerateL[MiforMMi.index];
	      scaleE += ScaleFactorEnergyN_G->GetBinContent(nScaleBinE)		*jet_taufakerateN[MiforMMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }
	    else if(Flavour[MiforMMi.index] == 0){
	      scaleE += ScaleFactorEnergyM_Un->GetBinContent(nScaleBinE)	*jet_taufakerateM[MiforMMi.index];
	      scaleE += ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE)	*jet_taufakerateL[MiforMMi.index];
	      scaleE += ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE)	*jet_taufakerateN[MiforMMi.index];
	      scaleE *= 1/(jet_taufakerateMi[MiforMMi.index]);
	    }		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightMMi=0;}
	  
	    tau_s faketauMi = fakeTau(JetLooseIsoObjectSelectionCollection, MiforMMi.index, scaleP, scaleE);
	    if(TauMediumIsoObjectSelectionCollection.tau[0]->pt > faketauMi.pt){
	      TauMMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);
	      TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);
	    }
	    else{
	      TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);
	      TauMMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightMMi=0.;
	}
	
	//L+T || M || Li
	if(TauLooseIsoObjectSelectionCollection.tau.size()==1){
	  if(verbose)std::cout<<"1 loose"<<std::endl;
	  
	  //dice T for TMi
	  SingleFake TforTMi("TforTMi");
	  TforTMi.generateSingle(jet_taufakerateT, eff_real_L);
	  weightTMi=TforTMi.weight;
	  
	  if(TforTMi.index >=0){
	    int nScaleBinP	  			= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTMi.index]->pt);
	    double scaleP 	  			= 0.;
	    if(Flavour[TforTMi.index] == 1) 		scaleP = ScaleFactorT_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 4)	scaleP = ScaleFactorT_C->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 5)	scaleP = ScaleFactorT_B->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 21)	scaleP = ScaleFactorT_G->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 0)	scaleP = ScaleFactorT_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE	  			= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTMi.index]->energy);
	    double scaleE 	  			= 0.;
	    if(Flavour[TforTMi.index] == 1) 		scaleE = ScaleFactorEnergyT_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 4)	scaleE = ScaleFactorEnergyT_C->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 5)	scaleE = ScaleFactorEnergyT_B->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 21)	scaleE = ScaleFactorEnergyT_G->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 0)	scaleE = ScaleFactorEnergyT_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightTMi=0;}
	  
	    tau_s faketauT = fakeTau(JetLooseIsoObjectSelectionCollection, TforTMi.index, scaleP, scaleE);
	    if(TauLooseIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
	    }
	    else{
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightTMi=0.;
	  
	  //dice M for MMi
	  SingleFake MforMMi("MforMMi");
	  MforMMi.generateSingle(jet_taufakerateM, eff_real_L);
	  weightMMi=MforMMi.weight;
	  
	  if(MforMMi.index >=0){
	    int nScaleBinP	  			= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MforMMi.index]->pt);
	    double scaleP 	  			= 0.;
	    if(Flavour[MforMMi.index] == 1) 		scaleP = ScaleFactorM_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 4)	scaleP = ScaleFactorM_C->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 5)	scaleP = ScaleFactorM_B->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 21)	scaleP = ScaleFactorM_G->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 0)	scaleP = ScaleFactorM_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE	  			= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MforMMi.index]->energy);
	    double scaleE 	  			= 0.;
	    if(Flavour[MforMMi.index] == 1) 		scaleE = ScaleFactorEnergyM_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 4)	scaleE = ScaleFactorEnergyM_C->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 5)	scaleE = ScaleFactorEnergyM_B->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 21)	scaleE = ScaleFactorEnergyM_G->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 0)	scaleE = ScaleFactorEnergyM_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightMMi=0;}
	  
	    tau_s faketauM = fakeTau(JetLooseIsoObjectSelectionCollection, MforMMi.index, scaleP, scaleE);
	    if(TauLooseIsoObjectSelectionCollection.tau[0]->pt > faketauM.pt){
	      TauMMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
	      TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);
	    }
	    else{
	      TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);
	      TauMMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightMMi=0.;
	  
	  //dice Li for LLi
	  SingleFake LiforLLi("LiforLLi");
	  LiforLLi.generateSingle(jet_taufakerateLi, eff_real_L);
	  weightLLi=LiforLLi.weight;
	  
	  if(LiforLLi.index >= 0){
	    int nScaleBinP	  = ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[LiforLLi.index]->pt);
	    double scaleP 	  = 0.;
	    if(Flavour[LiforLLi.index] == 1){
	      scaleP += ScaleFactorL_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateL[LiforLLi.index];
	      scaleP += ScaleFactorN_Uds->GetBinContent(nScaleBinP)	*jet_taufakerateN[LiforLLi.index];
	      scaleP *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 4){
	      scaleP += ScaleFactorL_C->GetBinContent(nScaleBinP)	*jet_taufakerateL[LiforLLi.index];
	      scaleP += ScaleFactorN_C->GetBinContent(nScaleBinP)	*jet_taufakerateN[LiforLLi.index];
	      scaleP *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 5){
	      scaleP += ScaleFactorL_B->GetBinContent(nScaleBinP)	*jet_taufakerateL[LiforLLi.index];
	      scaleP += ScaleFactorN_B->GetBinContent(nScaleBinP)	*jet_taufakerateN[LiforLLi.index];
	      scaleP *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 21){
	      scaleP += ScaleFactorL_G->GetBinContent(nScaleBinP)	*jet_taufakerateL[LiforLLi.index];
	      scaleP += ScaleFactorN_G->GetBinContent(nScaleBinP)	*jet_taufakerateN[LiforLLi.index];
	      scaleP *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 0){
	      scaleP += ScaleFactorL_Un->GetBinContent(nScaleBinP)	*jet_taufakerateL[LiforLLi.index];
	      scaleP += ScaleFactorN_Un->GetBinContent(nScaleBinP)	*jet_taufakerateN[LiforLLi.index];
	      scaleP *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    int nScaleBinE	  = ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[LiforLLi.index]->energy);
	    double scaleE 	  = 0.;
	    if(Flavour[LiforLLi.index] == 1){
	      scaleE += ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateL[LiforLLi.index];
	      scaleE += ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE)	*jet_taufakerateN[LiforLLi.index];
	      scaleE *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 4){
	      scaleE += ScaleFactorEnergyL_C->GetBinContent(nScaleBinE)		*jet_taufakerateL[LiforLLi.index];
	      scaleE += ScaleFactorEnergyN_C->GetBinContent(nScaleBinE)		*jet_taufakerateN[LiforLLi.index];
	      scaleE *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 5){
	      scaleE += ScaleFactorEnergyL_B->GetBinContent(nScaleBinE)		*jet_taufakerateL[LiforLLi.index];
	      scaleE += ScaleFactorEnergyN_B->GetBinContent(nScaleBinE)		*jet_taufakerateN[LiforLLi.index];
	      scaleE *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 21){
	      scaleE += ScaleFactorEnergyL_G->GetBinContent(nScaleBinE)		*jet_taufakerateL[LiforLLi.index];
	      scaleE += ScaleFactorEnergyN_G->GetBinContent(nScaleBinE)		*jet_taufakerateN[LiforLLi.index];
	      scaleE *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }
	    else if(Flavour[LiforLLi.index] == 0){
	      scaleE += ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE)	*jet_taufakerateL[LiforLLi.index];
	      scaleE += ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE)	*jet_taufakerateN[LiforLLi.index];
	      scaleE *= 1/(jet_taufakerateLi[LiforLLi.index]);
	    }		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightLLi=0;}
	  
	    tau_s faketauLi = fakeTau(JetLooseIsoObjectSelectionCollection, LiforLLi.index, scaleP, scaleE);
	    if(TauLooseIsoObjectSelectionCollection.tau[0]->pt > faketauLi.pt){
	      TauLLiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
	      TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauLi);
	    }
	    else{
	      TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauLi);
	      TauLLiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightLLi=0.;
	}
	
	//N+T || M || L || N
	if(TauNoIsoObjectSelectionCollection.tau.size()==1){
	  if(verbose)std::cout<<"1 no iso"<<std::endl;
	  
	  //dice T for TMi
	  SingleFake TforTMi("TforTMi");
	  TforTMi.generateSingle(jet_taufakerateT, eff_real_N);
	  weightTMi=TforTMi.weight;
	  
	  if(TforTMi.index >= 0){
	    int nScaleBinP	  			= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTMi.index]->pt);
	    double scaleP 	  			= 0.;
	    if(Flavour[TforTMi.index] == 1) 		scaleP = ScaleFactorT_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 4)	scaleP = ScaleFactorT_C->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 5)	scaleP = ScaleFactorT_B->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 21)	scaleP = ScaleFactorT_G->GetBinContent(nScaleBinP);
	    else if(Flavour[TforTMi.index] == 0)	scaleP = ScaleFactorT_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE	  			= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[TforTMi.index]->energy);
	    double scaleE 	  			= 0.;
	    if(Flavour[TforTMi.index] == 1) 		scaleE = ScaleFactorEnergyT_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 4)	scaleE = ScaleFactorEnergyT_C->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 5)	scaleE = ScaleFactorEnergyT_B->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 21)	scaleE = ScaleFactorEnergyT_G->GetBinContent(nScaleBinE);
	    else if(Flavour[TforTMi.index] == 0)	scaleE = ScaleFactorEnergyT_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightTMi=0;}
	  
	    tau_s faketauT = fakeTau(JetLooseIsoObjectSelectionCollection, TforTMi.index, scaleP, scaleE);
	    if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
	    }
	    else{
	      TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
	      TauTMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightTMi=0.;
	  
	  //dice M for MMi
	  SingleFake MforMMi("MforMMi");
	  MforMMi.generateSingle(jet_taufakerateM, eff_real_N);
	  weightMMi=MforMMi.weight;
	  
	  if(MforMMi.index >= 0){
	    int nScaleBinP	  			= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MforMMi.index]->pt);
	    double scaleP 	  			= 0.;
	    if(Flavour[MforMMi.index] == 1) 		scaleP = ScaleFactorM_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 4)	scaleP = ScaleFactorM_C->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 5)	scaleP = ScaleFactorM_B->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 21)	scaleP = ScaleFactorM_G->GetBinContent(nScaleBinP);
	    else if(Flavour[MforMMi.index] == 0)	scaleP = ScaleFactorM_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE	  			= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[MforMMi.index]->energy);
	    double scaleE 	  			= 0.;
	    if(Flavour[MforMMi.index] == 1) 		scaleE = ScaleFactorEnergyM_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 4)	scaleE = ScaleFactorEnergyM_C->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 5)	scaleE = ScaleFactorEnergyM_B->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 21)	scaleE = ScaleFactorEnergyM_G->GetBinContent(nScaleBinE);
	    else if(Flavour[MforMMi.index] == 0)	scaleE = ScaleFactorEnergyM_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightMMi=0;}
	  
	    tau_s faketauM = fakeTau(JetLooseIsoObjectSelectionCollection, MforMMi.index, scaleP, scaleE);
	    if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauM.pt){
	      TauMMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
	      TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);
	    }
	    else{
	      TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);
	      TauMMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightMMi=0.;
	  
	  //dice L for LLi
	  SingleFake LforLLi("LforLLi");
	  LforLLi.generateSingle(jet_taufakerateL, eff_real_N);
	  weightLLi=LforLLi.weight;
	  
	  if(LforLLi.index >= 0){
	    int nScaleBinP  				= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[LforLLi.index]->pt);
	    double scaleP  				= 0.;
	    if(Flavour[LforLLi.index] == 1) 		scaleP = ScaleFactorL_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[LforLLi.index] == 4)	scaleP = ScaleFactorL_C->GetBinContent(nScaleBinP);
	    else if(Flavour[LforLLi.index] == 5)	scaleP = ScaleFactorL_B->GetBinContent(nScaleBinP);
	    else if(Flavour[LforLLi.index] == 21)	scaleP = ScaleFactorL_G->GetBinContent(nScaleBinP);
	    else if(Flavour[LforLLi.index] == 0)	scaleP = ScaleFactorL_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE  				= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[LforLLi.index]->energy);
	    double scaleE  				= 0.;
	    if(Flavour[LforLLi.index] == 1) 		scaleE = ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[LforLLi.index] == 4)	scaleE = ScaleFactorEnergyL_C->GetBinContent(nScaleBinE);
	    else if(Flavour[LforLLi.index] == 5)	scaleE = ScaleFactorEnergyL_B->GetBinContent(nScaleBinE);
	    else if(Flavour[LforLLi.index] == 21)	scaleE = ScaleFactorEnergyL_G->GetBinContent(nScaleBinE);
	    else if(Flavour[LforLLi.index] == 0)	scaleE = ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightLLi=0;}
	  
	    tau_s faketauL = fakeTau(JetLooseIsoObjectSelectionCollection, LforLLi.index, scaleP, scaleE);
	    if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauL.pt){
	      TauLLiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
	      TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauL);
	    }
	    else{
	      TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauL);
	      TauLLiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightLLi=0.;
	  
	  //dice N for NN
	  SingleFake NforNN("NforNN");
	  NforNN.generateSingle(jet_taufakerateN, eff_real_N);
	  weightNN=NforNN.weight;
	  
	  if(NforNN.index >=0){
	    int nScaleBinP  			= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[NforNN.index]->pt);
	    double scaleP  			= 0.;
	    if(Flavour[NforNN.index] == 1) 	scaleP = ScaleFactorN_Uds->GetBinContent(nScaleBinP);
	    else if(Flavour[NforNN.index] == 4)	scaleP = ScaleFactorN_C->GetBinContent(nScaleBinP);
	    else if(Flavour[NforNN.index] == 5)	scaleP = ScaleFactorN_B->GetBinContent(nScaleBinP);
	    else if(Flavour[NforNN.index] == 21)scaleP = ScaleFactorN_G->GetBinContent(nScaleBinP);
	    else if(Flavour[NforNN.index] == 0) scaleP = ScaleFactorN_Un->GetBinContent(nScaleBinP);
	    int nScaleBinE	  		= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[NforNN.index]->energy);
	    double scaleE 	  		= 0.;
	    if(Flavour[NforNN.index] == 1) 	scaleE = ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE);
	    else if(Flavour[NforNN.index] == 4)	scaleE = ScaleFactorEnergyN_C->GetBinContent(nScaleBinE);
	    else if(Flavour[NforNN.index] == 5)	scaleE = ScaleFactorEnergyN_B->GetBinContent(nScaleBinE);
	    else if(Flavour[NforNN.index] == 21)scaleE = ScaleFactorEnergyN_G->GetBinContent(nScaleBinE);
	    else if(Flavour[NforNN.index] == 0) scaleE = ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE);		
	    if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE = 1.; weightNN=0;}
	  
	    tau_s faketauN = fakeTau(JetLooseIsoObjectSelectionCollection, NforNN.index, scaleP, scaleE);
	    if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauN.pt){
	      TauNNIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
	      TauNNIsoObjectSelectionCollection.tau.push_back(&faketauN);
	    }
	    else{
	      TauNNIsoObjectSelectionCollection.tau.push_back(&faketauN);
	      TauNNIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);	
	    }
	  }
	  else weightNN=0.;
	}
	if(verbose)std::cout<<"end of all scenarios for 1 gen tau"<<std::endl;			  
    }
    
    //beginning 0 lepton scenario for QCD, W+jets and Single Top hadronic
    else if(genTau.size()==0){//if(genMu.size()+genE.size()+genTau.size()==0){
        if(verbose)std::cout<<"enter 0 tau scenario"<<std::endl;
    	Fake FakeTausN("FakeTaus");
	FakeTausN.generate(jet_taufakerateN,jet_taufakerateN, true);

	tau_s faketau1N;
	tau_s faketau2N;

	if ( FakeTausN.index.first >= 0 && FakeTausN.index.second >= 0 ) {
	  int nScaleBinP = ScaleFactorN_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt);
	  double scaleP 	  	= 0.;
	  if(Flavour[FakeTausN.index.first] == 1) 	scaleP = ScaleFactorN_Uds->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausN.index.first] == 4)	scaleP = ScaleFactorN_C->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausN.index.first] == 5)	scaleP = ScaleFactorN_B->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausN.index.first] == 21)	scaleP = ScaleFactorN_G->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausN.index.first] == 0)	scaleP = ScaleFactorN_Un->GetBinContent(nScaleBinP);
	  int nScaleBinE	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->energy);
	  double scaleE 	  	= 0.;
	  if(Flavour[FakeTausN.index.first] == 1) 	scaleE = ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausN.index.first] == 4)	scaleE = ScaleFactorEnergyN_C->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausN.index.first] == 5)	scaleE = ScaleFactorEnergyN_B->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausN.index.first] == 21)	scaleE = ScaleFactorEnergyN_G->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausN.index.first] == 0)	scaleE = ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE);
	   
	  if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausN.weight=0;}
	  faketau1N = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausN.index.first, scaleP, scaleE);
	  
	  int nScaleBinP2 = ScaleFactorN_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt);
	  double scaleP2 	  	= 0.;
	  if(Flavour[FakeTausN.index.second] == 1) 		scaleP2 = ScaleFactorN_Uds->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausN.index.second] == 4)		scaleP2 = ScaleFactorN_C->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausN.index.second] == 5)		scaleP2 = ScaleFactorN_B->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausN.index.second] == 21)	scaleP2 = ScaleFactorN_G->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausN.index.second] == 0) 	scaleP2 = ScaleFactorN_Un->GetBinContent(nScaleBinP2);
	  int nScaleBinE2	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->energy);
	  double scaleE2 	  	= 0.;
	  if(Flavour[FakeTausN.index.second] == 1) 		scaleE2 = ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausN.index.second] == 4)		scaleE2 = ScaleFactorEnergyN_C->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausN.index.second] == 5)		scaleE2 = ScaleFactorEnergyN_B->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausN.index.second] == 21)	scaleE2 = ScaleFactorEnergyN_G->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausN.index.second] == 0) 	scaleE2 = ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE2);

	  if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausN.weight=0;}
	  faketau2N = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausN.index.second, scaleP2, scaleE2);

	  if(faketau1N.pt > faketau2N.pt){
  	    TauNNIsoObjectSelectionCollection.tau.push_back(&faketau1N);
  	    TauNNIsoObjectSelectionCollection.tau.push_back(&faketau2N);
	  }
	  else{
  	    TauNNIsoObjectSelectionCollection.tau.push_back(&faketau2N);
  	    TauNNIsoObjectSelectionCollection.tau.push_back(&faketau1N);
	  }
	  weightNN=FakeTausN.weight;
	}

	Fake FakeTausL("FakeTaus");

	FakeTausL.generate(jet_taufakerateL,jet_taufakerateLi, false);

	tau_s faketau1L;
	tau_s faketau2L;

	if ( FakeTausL.index.first >= 0 && FakeTausL.index.second >= 0 ) {
	  
	  int nScaleBinP = ScaleFactorL_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt);
	  double scaleP 	  	= 0.;
	  if(Flavour[FakeTausL.index.first] == 1) 	scaleP = ScaleFactorL_Uds->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausL.index.first] == 4)	scaleP = ScaleFactorL_C->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausL.index.first] == 5)	scaleP = ScaleFactorL_B->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausL.index.first] == 21)	scaleP = ScaleFactorL_G->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausL.index.first] == 0)	scaleP = ScaleFactorL_Un->GetBinContent(nScaleBinP);
	  int nScaleBinE	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->energy);
	  double scaleE 	  	= 0.;
	  if(Flavour[FakeTausL.index.first] == 1) 	scaleE = ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausL.index.first] == 4)	scaleE = ScaleFactorEnergyL_C->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausL.index.first] == 5)	scaleE = ScaleFactorEnergyL_B->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausL.index.first] == 21)	scaleE = ScaleFactorEnergyL_G->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausL.index.first] == 0)	scaleE = ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE);
	  
	  if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausL.weight=0;}
	  faketau1L = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausL.index.first, scaleP, scaleE);
	  
	  int nScaleBinP2	  	= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt);
	  double scaleP2 	  	= 0.;
	  if(Flavour[FakeTausL.index.second] == 1){
	    scaleP2 += ScaleFactorL_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausL.index.second];
	    scaleP2 += ScaleFactorN_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausL.index.second];
	    scaleP2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 4){
	    scaleP2 += ScaleFactorL_C->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausL.index.second];
	    scaleP2 += ScaleFactorN_C->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausL.index.second];
	    scaleP2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 5){
	    scaleP2 += ScaleFactorL_B->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausL.index.second];
	    scaleP2 += ScaleFactorN_B->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausL.index.second];
	    scaleP2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 21){
	    scaleP2 += ScaleFactorL_G->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausL.index.second];
	    scaleP2 += ScaleFactorN_G->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausL.index.second];
	    scaleP2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 0){
	    scaleP2 += ScaleFactorL_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausL.index.second];
	    scaleP2 += ScaleFactorN_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausL.index.second];
	    scaleP2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  int nScaleBinE2	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->energy);
	  double scaleE2 	  	= 0.;
	  if(Flavour[FakeTausL.index.second] == 1){
	    scaleE2 += ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateL[FakeTausL.index.second];
	    scaleE2 += ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateN[FakeTausL.index.second];
	    scaleE2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 4){
	    scaleE2 += ScaleFactorEnergyL_C->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausL.index.second];
	    scaleE2 += ScaleFactorEnergyN_C->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausL.index.second];
	    scaleE2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 5){
	    scaleE2 += ScaleFactorEnergyL_B->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausL.index.second];
	    scaleE2 += ScaleFactorEnergyN_B->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausL.index.second];
	    scaleE2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 21){
	    scaleE2 += ScaleFactorEnergyL_G->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausL.index.second];
	    scaleE2 += ScaleFactorEnergyN_G->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausL.index.second];
	    scaleE2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  else if(Flavour[FakeTausL.index.second] == 0){
	    scaleE2 += ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE2)	*jet_taufakerateL[FakeTausL.index.second];
	    scaleE2 += ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE2)	*jet_taufakerateN[FakeTausL.index.second];
	    scaleE2 *= 1/(jet_taufakerateLi[FakeTausL.index.second]);
	  }
	  
	  if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausL.weight=0;}
	  faketau2L = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausL.index.second, scaleP2, scaleE2);

	  if(faketau1L.pt > faketau2L.pt){
  	    TauLLiIsoObjectSelectionCollection.tau.push_back(&faketau1L);
  	    TauLLiIsoObjectSelectionCollection.tau.push_back(&faketau2L);
	  }
	  else{
  	    TauLLiIsoObjectSelectionCollection.tau.push_back(&faketau2L);
  	    TauLLiIsoObjectSelectionCollection.tau.push_back(&faketau1L);
	  }
	  weightLLi=FakeTausL.weight;
	}

	Fake FakeTausM("FakeTausM");

	FakeTausM.generate(jet_taufakerateM,jet_taufakerateMi, false);

	tau_s faketau1M;
	tau_s faketau2M;

	if ( FakeTausM.index.first >= 0 && FakeTausM.index.second >= 0 ) {

	  int nScaleBinP = ScaleFactorM_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt);
	  double scaleP 	  	= 0.;
	  if(Flavour[FakeTausM.index.first] == 1) 	scaleP = ScaleFactorM_Uds->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausM.index.first] == 4)	scaleP = ScaleFactorM_C->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausM.index.first] == 5)	scaleP = ScaleFactorM_B->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausM.index.first] == 21)	scaleP = ScaleFactorM_G->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausM.index.first] == 0)	scaleP = ScaleFactorM_Un->GetBinContent(nScaleBinP);
	  int nScaleBinE	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->energy);
	  double scaleE 	  	= 0.;
	  if(Flavour[FakeTausM.index.first] == 1) 	scaleE = ScaleFactorEnergyM_Uds->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausM.index.first] == 4)	scaleE = ScaleFactorEnergyM_C->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausM.index.first] == 5)	scaleE = ScaleFactorEnergyM_B->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausM.index.first] == 21)	scaleE = ScaleFactorEnergyM_G->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausM.index.first] == 0)	scaleE = ScaleFactorEnergyM_Un->GetBinContent(nScaleBinE);
	   
	  if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausM.weight=0;}
	  faketau1M = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausM.index.first, scaleP, scaleE);

	  int nScaleBinP2	  	= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt);
	  double scaleP2 	  	= 0.;
	  if(Flavour[FakeTausM.index.second] == 1){
	    scaleP2 += ScaleFactorM_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausM.index.second];
	    scaleP2 += ScaleFactorL_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausM.index.second];
	    scaleP2 += ScaleFactorN_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausM.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  else if(Flavour[FakeTausM.index.second] == 4){
	    scaleP2 += ScaleFactorM_C->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausM.index.second];
	    scaleP2 += ScaleFactorL_C->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausM.index.second];
	    scaleP2 += ScaleFactorN_C->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausM.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  else if(Flavour[FakeTausM.index.second] == 5){
	    scaleP2 += ScaleFactorM_B->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausM.index.second];
	    scaleP2 += ScaleFactorL_B->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausM.index.second];
	    scaleP2 += ScaleFactorN_B->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausM.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  else if(Flavour[FakeTausM.index.second] == 21){
	    scaleP2 += ScaleFactorM_G->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausM.index.second];
	    scaleP2 += ScaleFactorL_G->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausM.index.second];
	    scaleP2 += ScaleFactorN_G->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausM.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  else if(Flavour[FakeTausM.index.second] == 0){
	    scaleP2 += ScaleFactorM_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausM.index.second];
	    scaleP2 += ScaleFactorL_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausM.index.second];
	    scaleP2 += ScaleFactorN_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausM.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  int nScaleBinE2	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->energy);
	  double scaleE2 	  	= 0.;
	  if(Flavour[FakeTausM.index.second] == 1){
	    scaleE2 += ScaleFactorEnergyM_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateM[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateL[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateN[FakeTausM.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  else if(Flavour[FakeTausM.index.second] == 4){
	    scaleE2 += ScaleFactorEnergyM_C->GetBinContent(nScaleBinE2)		*jet_taufakerateM[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyL_C->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyN_C->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausM.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  else if(Flavour[FakeTausM.index.second] == 5){
	    scaleE2 += ScaleFactorEnergyM_B->GetBinContent(nScaleBinE2)		*jet_taufakerateM[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyL_B->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyN_B->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausM.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  else if(Flavour[FakeTausM.index.second] == 21){
	    scaleE2 += ScaleFactorEnergyM_G->GetBinContent(nScaleBinE2)		*jet_taufakerateM[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyL_G->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyN_G->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausM.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	else if(Flavour[FakeTausM.index.second] == 0){
	    scaleE2 += ScaleFactorEnergyM_Un->GetBinContent(nScaleBinE2)		*jet_taufakerateM[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausM.index.second];
	    scaleE2 += ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausM.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausM.index.second]);
	  }
	  if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausM.weight=0;}
	  faketau2M = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausM.index.second, scaleP2, scaleE2);

	  if(faketau1M.pt > faketau2M.pt){
  	    TauMMiIsoObjectSelectionCollection.tau.push_back(&faketau1M);
  	    TauMMiIsoObjectSelectionCollection.tau.push_back(&faketau2M);
	  }
	  else{
  	    TauMMiIsoObjectSelectionCollection.tau.push_back(&faketau2M);
  	    TauMMiIsoObjectSelectionCollection.tau.push_back(&faketau1M);
	  }
	  weightMMi=FakeTausM.weight;
	}

	Fake FakeTausT("FakeTausT");
	FakeTausT.generate(jet_taufakerateT,jet_taufakerateMi, false);

	tau_s faketau1T;
	tau_s faketau2T;

	if ( FakeTausT.index.first >= 0 && FakeTausT.index.second >= 0 ) {

	  int nScaleBinP = ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt);
	  double scaleP 	  	= 0.;
	  if(Flavour[FakeTausT.index.first] == 1) 	scaleP = ScaleFactorT_Uds->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausT.index.first] == 4)	scaleP = ScaleFactorT_C->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausT.index.first] == 5)	scaleP = ScaleFactorT_B->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausT.index.first] == 21)	scaleP = ScaleFactorT_G->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausT.index.first] == 0)	scaleP = ScaleFactorT_Un->GetBinContent(nScaleBinP);
	  int nScaleBinE	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->energy);
	  double scaleE 	  	= 0.;
	  if(Flavour[FakeTausT.index.first] == 1) 	scaleE = ScaleFactorEnergyT_Uds->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausT.index.first] == 4)	scaleE = ScaleFactorEnergyT_C->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausT.index.first] == 5)	scaleE = ScaleFactorEnergyT_B->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausT.index.first] == 21)	scaleE = ScaleFactorEnergyT_G->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausT.index.first] == 0)	scaleE = ScaleFactorEnergyT_Un->GetBinContent(nScaleBinE);
	  
	  if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausT.weight=0;}
	  faketau1T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausT.index.first, scaleP, scaleE);

	  int nScaleBinP2	  	= ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt);
	  double scaleP2 	  	= 0.;
	  if(Flavour[FakeTausT.index.second] == 1){
	    scaleP2 += ScaleFactorM_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausT.index.second];
	    scaleP2 += ScaleFactorL_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausT.index.second];
	    scaleP2 += ScaleFactorN_Uds->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausT.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 4){
	    scaleP2 += ScaleFactorM_C->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausT.index.second];
	    scaleP2 += ScaleFactorL_C->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausT.index.second];
	    scaleP2 += ScaleFactorN_C->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausT.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 5){
	    scaleP2 += ScaleFactorM_B->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausT.index.second];
	    scaleP2 += ScaleFactorL_B->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausT.index.second];
	    scaleP2 += ScaleFactorN_B->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausT.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 21){
	    scaleP2 += ScaleFactorM_G->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausT.index.second];
	    scaleP2 += ScaleFactorL_G->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausT.index.second];
	    scaleP2 += ScaleFactorN_G->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausT.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 0){
	    scaleP2 += ScaleFactorM_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateM[FakeTausT.index.second];
	    scaleP2 += ScaleFactorL_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateL[FakeTausT.index.second];
	    scaleP2 += ScaleFactorN_Un->GetBinContent(nScaleBinP2)	*jet_taufakerateN[FakeTausT.index.second];
	    scaleP2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  int nScaleBinE2	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->energy);
	  double scaleE2 	  	= 0.;
	  if(Flavour[FakeTausT.index.second] == 1){
	    scaleE2 += ScaleFactorEnergyM_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateM[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyL_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateL[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyN_Uds->GetBinContent(nScaleBinE2)	*jet_taufakerateN[FakeTausT.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 4){
	    scaleE2 += ScaleFactorEnergyM_C->GetBinContent(nScaleBinE2)		*jet_taufakerateM[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyL_C->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyN_C->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausT.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 5){
	    scaleE2 += ScaleFactorEnergyM_B->GetBinContent(nScaleBinE2)		*jet_taufakerateM[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyL_B->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyN_B->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausT.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 21){
	    scaleE2 += ScaleFactorEnergyM_G->GetBinContent(nScaleBinE2)		*jet_taufakerateM[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyL_G->GetBinContent(nScaleBinE2)		*jet_taufakerateL[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyN_G->GetBinContent(nScaleBinE2)		*jet_taufakerateN[FakeTausT.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  else if(Flavour[FakeTausT.index.second] == 0){
	    scaleE2 += ScaleFactorEnergyM_Un->GetBinContent(nScaleBinE2)	*jet_taufakerateM[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyL_Un->GetBinContent(nScaleBinE2)	*jet_taufakerateL[FakeTausT.index.second];
	    scaleE2 += ScaleFactorEnergyN_Un->GetBinContent(nScaleBinE2)	*jet_taufakerateN[FakeTausT.index.second];
	    scaleE2 *= 1/(jet_taufakerateMi[FakeTausT.index.second]);
	  }
	  
	  if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausT.weight=0;}
	  faketau2T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausT.index.second, scaleP2, scaleE2);

	  if(faketau1T.pt > faketau2T.pt){
  	    TauTMiIsoObjectSelectionCollection.tau.push_back(&faketau1T);
  	    TauTMiIsoObjectSelectionCollection.tau.push_back(&faketau2T);
	  }
	  else{
  	    TauTMiIsoObjectSelectionCollection.tau.push_back(&faketau2T);
  	    TauTMiIsoObjectSelectionCollection.tau.push_back(&faketau1T);
	  }
	  weightTMi=FakeTausT.weight;
	}

	Fake FakeTausTT("FakeTausTT");
	FakeTausTT.generate(jet_taufakerateT,jet_taufakerateT, true);

	tau_s faketauT1T;
	tau_s faketauT2T;

	if ( FakeTausTT.index.first >= 0 && FakeTausTT.index.second >= 0 ) {
	
	  int nScaleBinP = ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->pt);
	  double scaleP 	  	= 0.;
	  if(Flavour[FakeTausTT.index.first] == 1) 	scaleP = ScaleFactorT_Uds->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausTT.index.first] == 4)	scaleP = ScaleFactorT_C->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausTT.index.first] == 5)	scaleP = ScaleFactorT_B->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausTT.index.first] == 21)scaleP = ScaleFactorT_G->GetBinContent(nScaleBinP);
	  else if(Flavour[FakeTausTT.index.first] == 0) scaleP = ScaleFactorT_Un->GetBinContent(nScaleBinP);
	  int nScaleBinE	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->energy);
	  double scaleE 	  	= 0.;
	  if(Flavour[FakeTausTT.index.first] == 1) 	scaleE = ScaleFactorEnergyT_Uds->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausTT.index.first] == 4)	scaleE = ScaleFactorEnergyT_C->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausTT.index.first] == 5)	scaleE = ScaleFactorEnergyT_B->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausT.index.first] == 21)	scaleE = ScaleFactorEnergyT_G->GetBinContent(nScaleBinE);
	  else if(Flavour[FakeTausT.index.first] == 0)	scaleE = ScaleFactorEnergyT_Un->GetBinContent(nScaleBinE);
	  
	  if(scaleP == 0 || scaleE == 0) {scaleP = 1.; scaleE=1.; FakeTausTT.weight=0;}
	  faketauT1T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausTT.index.first, scaleP, scaleE);

	  int nScaleBinP2 = ScaleFactorT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->pt);
	  double scaleP2 	  	= 0.;
	  if(Flavour[FakeTausTT.index.second] == 1) 		scaleP2 = ScaleFactorT_Uds->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausTT.index.second] == 4)	scaleP2 = ScaleFactorT_C->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausTT.index.second] == 5)	scaleP2 = ScaleFactorT_B->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausTT.index.second] == 21)	scaleP2 = ScaleFactorT_G->GetBinContent(nScaleBinP2);
	  else if(Flavour[FakeTausTT.index.second] == 0)	scaleP2 = ScaleFactorT_Un->GetBinContent(nScaleBinP2);
	  int nScaleBinE2	  	= ScaleFactorEnergyT_Uds->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->energy);
	  double scaleE2 	  	= 0.;
	  if(Flavour[FakeTausTT.index.second] == 1) 		scaleE2 = ScaleFactorEnergyT_Uds->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausTT.index.second] == 4)	scaleE2 = ScaleFactorEnergyT_C->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausTT.index.second] == 5)	scaleE2 = ScaleFactorEnergyT_B->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausT.index.second] == 21)	scaleE2 = ScaleFactorEnergyT_G->GetBinContent(nScaleBinE2);
	  else if(Flavour[FakeTausT.index.second] == 0) 	scaleE2 = ScaleFactorEnergyT_Un->GetBinContent(nScaleBinE2);
	  
	  if(scaleP2 == 0 || scaleE2 == 0) {scaleP2 = 1.; scaleE2=1.; FakeTausTT.weight=0;}
	  faketauT2T = fakeTau(JetLooseIsoObjectSelectionCollection, FakeTausTT.index.second, scaleP2, scaleE2);

	  if(faketauT1T.pt > faketauT2T.pt){
  	    TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT1T);
  	    TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT2T);
	  }
	  else{
  	    TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT2T);
  	    TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT1T);
	  }
	  weightTT=FakeTausTT.weight;
	}    
    }
    if(verbose)std::cout<<"start jet search"<<std::endl;
    	// jet && bjet selection
	// ? id ?
	for(unsigned int j = 0;j<jet.size();++j){
	  if(!( jet[j].pt >= 30. )) continue; // Original value 20
	  if(!( fabs(jet[j].eta) <= 5.0 )) continue;
	  double DistanceN = TauJetMinDistance(TauNNIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	  double DistanceL = TauJetMinDistance(TauLLiIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	  double DistanceM = TauJetMinDistance(TauMMiIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	  double Distance1T= TauJetMinDistance(TauTMiIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
	  double DistanceT = TauJetMinDistance(TauTTIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
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
  	    if(	DistanceN >= 0.3	) TauNNIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  	    if(	DistanceL >= 0.3	) TauLLiIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  	    if(	DistanceM >= 0.3	) TauMMiIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  	    if(	Distance1T >= 0.3	) TauTMiIsoObjectSelectionCollection.jet.push_back(&jet[j]);
  	    if(	DistanceT >= 0.3	) TauTTIsoObjectSelectionCollection.jet.push_back(&jet[j]);
          }
	  if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244 ){
  	    if(	DistanceN >= 0.3	) TauNNIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  	    if(	DistanceL >= 0.3	) TauLLiIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  	    if(	DistanceM >= 0.3	) TauMMiIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  	    if(	Distance1T >= 0.3	) TauTMiIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
  	    if(	DistanceT >= 0.3	) TauTTIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
          }
	}

	//MET selection
	TauNNIsoObjectSelectionCollection.met.push_back(&met[0]);
	TauLLiIsoObjectSelectionCollection.met.push_back(&met[0]);
	TauMMiIsoObjectSelectionCollection.met.push_back(&met[0]);
	TauTMiIsoObjectSelectionCollection.met.push_back(&met[0]);
	TauTTIsoObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");
if(verbose) std::cout<<"NN: "<<weightNN<<std::endl;
if(verbose) std::cout<<"_________________________"<<std::endl;
if(verbose)std::cout<<"selection starts"<<std::endl;
//set sign	
bool LS=true; 	
	
// ---------------------
// -- Signal Region --
// ---------------------
if(TauTTIsoObjectSelectionCollection.jet.size()>=2){
Selection LS_Signal("LS_Signal"); 					//label and initialisation
LS_Signal.InputCollection 	= &TauTTIsoObjectSelectionCollection;	//input collection
LS_Signal.OutputCollection 	= &myHistoColl_LS_SignalRegion;        	//output collection
LS_Signal.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
LS_Signal.RunData        	= false;        			//real data allowed
LS_Signal.RequireTriggers       = false;       				//require at least one of the triggers fired
LS_Signal.weight        	= weightTT;       			//event weight
CutConfiguration(&LS_Signal, true, LS); 				//selection, VBF, LS

LS_Signal.select();        						//do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection InvertedVBF_LS_CR2("InvertedVBF_LS_CR2"); 				//label and initialisation
InvertedVBF_LS_CR2.InputCollection 	= &TauTTIsoObjectSelectionCollection;	//input collection
InvertedVBF_LS_CR2.OutputCollection 	= &myHistoColl_LS_CR2;        		//output collection
InvertedVBF_LS_CR2.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_LS_CR2.RunData        	= false;        			//real data allowed
InvertedVBF_LS_CR2.RequireTriggers      = false;       				//require at least one of the triggers fired
InvertedVBF_LS_CR2.weight        	= weightTT;        			//event weight
CutConfiguration(&InvertedVBF_LS_CR2, false, LS); 				//selection, VBF, LS

InvertedVBF_LS_CR2.select();        						//do selection, fill histograms
}

// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------
if(TauTMiIsoObjectSelectionCollection.jet.size()>=2){
Selection oneTightTau_LS_CR3("oneTightTau_LS_CR3"); 					//label and initialisation
oneTightTau_LS_CR3.InputCollection 	= &TauTMiIsoObjectSelectionCollection;		//input collection
oneTightTau_LS_CR3.OutputCollection 	= &myHistoColl_LS_CR3;        			//output collection
oneTightTau_LS_CR3.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
oneTightTau_LS_CR3.RunData        	= false;        				//real data allowed
oneTightTau_LS_CR3.RequireTriggers      = false;       					//require at least one of the triggers fired
oneTightTau_LS_CR3.weight        	= weightTMi;        				//event weight
CutConfiguration(&oneTightTau_LS_CR3, true, LS); 					//selection, VBF, LS

oneTightTau_LS_CR3.select();        							//do selection, fill histograms

// ---------------------------------------------
// -- CENTRAL + InvertedVBF + 1 Tight Tau CR4 --
// ---------------------------------------------
Selection InvertedVBF_oneTightTau_LS_CR4("InvertedVBF_oneTightTau_LS_CR4"); 			//label and initialisation
InvertedVBF_oneTightTau_LS_CR4.InputCollection 	= &TauTMiIsoObjectSelectionCollection;       	//input collection
InvertedVBF_oneTightTau_LS_CR4.OutputCollection = &myHistoColl_LS_CR4;        			//output collection
InvertedVBF_oneTightTau_LS_CR4.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_oneTightTau_LS_CR4.RunData        	= false;        				//real data allowed
InvertedVBF_oneTightTau_LS_CR4.RequireTriggers  = false;       					//require at least one of the triggers fired
InvertedVBF_oneTightTau_LS_CR4.weight        	= weightTMi;        				//event weight
CutConfiguration(&InvertedVBF_oneTightTau_LS_CR4, false, LS); 					//selection, VBF, LS

InvertedVBF_oneTightTau_LS_CR4.select();        						//do selection, fill histograms
}

// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------
if(TauMMiIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiTightTau_LS_CR5("AntiTightTau_LS_CR5"); 					//label and initialisation
AntiTightTau_LS_CR5.InputCollection 	= &TauMMiIsoObjectSelectionCollection;		//input collection
AntiTightTau_LS_CR5.OutputCollection 	= &myHistoColl_LS_CR5;        			//output collection
AntiTightTau_LS_CR5.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
AntiTightTau_LS_CR5.RunData        	= false;        				//real data allowed
AntiTightTau_LS_CR5.RequireTriggers     = false;       					//require at least one of the triggers fired
AntiTightTau_LS_CR5.weight        	= weightMMi;        				//event weight
CutConfiguration(&AntiTightTau_LS_CR5, true, LS); 					//selection, VBF, LS

AntiTightTau_LS_CR5.select();        							//do selection, fill histograms

// ------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Tight Tau CR6 --
// ------------------------------------------------

Selection InvertedVBF_AntiTightTau_LS_CR6("InvertedVBF_AntiTightTau_LS_CR6"); 			//label and initialisation
InvertedVBF_AntiTightTau_LS_CR6.InputCollection 	= &TauMMiIsoObjectSelectionCollection;	//input collection
InvertedVBF_AntiTightTau_LS_CR6.OutputCollection 	= &myHistoColl_LS_CR6;        		//output collection
InvertedVBF_AntiTightTau_LS_CR6.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiTightTau_LS_CR6.RunData        		= false;        			//real data allowed
InvertedVBF_AntiTightTau_LS_CR6.RequireTriggers         = false;       				//require at least one of the triggers fired
InvertedVBF_AntiTightTau_LS_CR6.weight        		= weightMMi;        			//event weight
CutConfiguration(&InvertedVBF_AntiTightTau_LS_CR6, false, LS); 					//selection, VBF, LS

InvertedVBF_AntiTightTau_LS_CR6.select();        						//do selection, fill histograms
}	

// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------
if(TauLLiIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiMediumTau_LS_CR7("AntiMediumTau_LS_CR7"); 			//label and initialisation
AntiMediumTau_LS_CR7.InputCollection 	= &TauLLiIsoObjectSelectionCollection;	//input collection
AntiMediumTau_LS_CR7.OutputCollection 	= &myHistoColl_LS_CR7;        		//output collection
AntiMediumTau_LS_CR7.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiMediumTau_LS_CR7.RunData        	= false;        				//real data allowed
AntiMediumTau_LS_CR7.RequireTriggers    = false;       				//require at least one of the triggers fired
AntiMediumTau_LS_CR7.weight        	= weightLLi;        				//event weight
CutConfiguration(&AntiMediumTau_LS_CR7, true, LS); 				//selection, VBF, LS

AntiMediumTau_LS_CR7.select();        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Medium Tau CR8 --
// -------------------------------------------------

Selection InvertedVBF_AntiMediumTau_LS_CR8("InvertedVBF_AntiMediumTauLS_CR8"); 			//label and initialisation
InvertedVBF_AntiMediumTau_LS_CR8.InputCollection 	= &TauLLiIsoObjectSelectionCollection;	//input collection
InvertedVBF_AntiMediumTau_LS_CR8.OutputCollection 	= &myHistoColl_LS_CR8;        		//output collection
InvertedVBF_AntiMediumTau_LS_CR8.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiMediumTau_LS_CR8.RunData        	= false;        			//real data allowed
InvertedVBF_AntiMediumTau_LS_CR8.RequireTriggers        = false;       				//require at least one of the triggers fired
InvertedVBF_AntiMediumTau_LS_CR8.weight        		= weightLLi;        			//event weight
CutConfiguration(&InvertedVBF_AntiMediumTau_LS_CR8, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiMediumTau_LS_CR8.select();        						//do selection, fill histograms
}

// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------
if(TauNNIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiLooseTau_LS_CR9("AntiLooseTauLS_CR9"); 				//label and initialisation
AntiLooseTau_LS_CR9.InputCollection 	= &TauNNIsoObjectSelectionCollection;	//input collection
AntiLooseTau_LS_CR9.OutputCollection 	= &myHistoColl_LS_CR9;        		//output collection
AntiLooseTau_LS_CR9.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiLooseTau_LS_CR9.RunData        	= false;        			//real data allowed
AntiLooseTau_LS_CR9.RequireTriggers     = false;       				//require at least one of the triggers fired
AntiLooseTau_LS_CR9.weight        	= weightNN;        			//event weight
CutConfiguration(&AntiLooseTau_LS_CR9, true, LS); 				//selection, VBF, LS

AntiLooseTau_LS_CR9.select();        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Loose Tau CR10 --
// -------------------------------------------------

Selection InvertedVBF_AntiLooseTau_LS_CR10("InvertedVBF_AntiLooseTauLS_CR10"); 			//label and initialisation
InvertedVBF_AntiLooseTau_LS_CR10.InputCollection 	= &TauNNIsoObjectSelectionCollection;   //input collection
InvertedVBF_AntiLooseTau_LS_CR10.OutputCollection 	= &myHistoColl_LS_CR10;        		//output collection
InvertedVBF_AntiLooseTau_LS_CR10.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiLooseTau_LS_CR10.RunData        	= false;        			//real data allowed
InvertedVBF_AntiLooseTau_LS_CR10.RequireTriggers        = false;       				//require at least one of the triggers fired
InvertedVBF_AntiLooseTau_LS_CR10.weight        		= weightNN;        			//event weight
CutConfiguration(&InvertedVBF_AntiLooseTau_LS_CR10, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiLooseTau_LS_CR10.select();        						//do selection, fill histograms
}

// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_LS_CR1("Ztautau_LS_CR1"); //label and initialisation
Ztautau_LS_CR1.InputCollection 		= &TauTTIsoObjectSelectionCollection;	//input collection
Ztautau_LS_CR1.OutputCollection 	= &myHistoColl_LS_CR1;        		//output collection
Ztautau_LS_CR1.RealData        		= eventhelper_isRealData;        	//pass information if event is real data
Ztautau_LS_CR1.RunData        		= false;        			//real data allowed
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
Ztautau_LS_CR1.weight        		= weightTT;        			//event weight
Ztautau_LS_CR1.invertTauRequirements    = false;        			//invert number of taus requirement
Ztautau_LS_CR1.invertTauProperties      = false;        			//invert ditau properties (dR, sign)
Ztautau_LS_CR1.invertBtagRequirement    = false;        			//invert number of b-jets required
Ztautau_LS_CR1.invertJetRequirements    = false;        			//invert jet pt requirements
Ztautau_LS_CR1.invertDijetProperties    = false;        			//invert dijet system properties (dR, inv mass, sign eta, dEta)

Ztautau_LS_CR1.select();        						//do selection, fill histograms

//_____________________________________________
//-------------------OS SECTION----------------
//_____________________________________________

LS=false;

// ---------------------
// -- Signal Region --
// ---------------------
if(TauTTIsoObjectSelectionCollection.jet.size()>=2){
Selection OS_Signal("OS_Signal"); //label and initialisation
OS_Signal.InputCollection 		= &TauTTIsoObjectSelectionCollection;	//input collection
OS_Signal.OutputCollection 		= &myHistoColl_OS_SignalRegion;        	//output collection
OS_Signal.RealData        		= eventhelper_isRealData;        	//pass information if event is real data
OS_Signal.RunData        		= false;        			//real data allowed
OS_Signal.RequireTriggers          	= false;       				//require at least one of the triggers fired
OS_Signal.weight        		= weightTT;        			//event weight
CutConfiguration(&OS_Signal, true, LS); 					//selection, VBF, LS

OS_Signal.select();        							//do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection InvertedVBF_OS_CR2("InvertedVBF_OS_CR2"); 				//label and initialisation
InvertedVBF_OS_CR2.InputCollection 	= &TauTTIsoObjectSelectionCollection;	//input collection
InvertedVBF_OS_CR2.OutputCollection 	= &myHistoColl_OS_CR2;        		//output collection
InvertedVBF_OS_CR2.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_OS_CR2.RunData        	= false;        			//real data allowed
InvertedVBF_OS_CR2.RequireTriggers      = false;       				//require at least one of the triggers fired
InvertedVBF_OS_CR2.weight        	= weightTT;        			//event weight
CutConfiguration(&InvertedVBF_OS_CR2, false, LS); 				//selection, VBF, LS

InvertedVBF_OS_CR2.select();        						//do selection, fill histograms
}

// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------
if(TauTMiIsoObjectSelectionCollection.jet.size()>=2){
Selection oneTightTau_OS_CR3("oneTightTau_OS_CR3"); 					//label and initialisation
oneTightTau_OS_CR3.InputCollection 	= &TauTMiIsoObjectSelectionCollection;		//input collection
oneTightTau_OS_CR3.OutputCollection 	= &myHistoColl_OS_CR3;        			//output collection
oneTightTau_OS_CR3.RealData        	= eventhelper_isRealData;        		//pass information if event is real data
oneTightTau_OS_CR3.RunData        	= false;        				//real data allowed
oneTightTau_OS_CR3.RequireTriggers      = false;       					//require at least one of the triggers fired
oneTightTau_OS_CR3.weight        	= weightTMi;        				//event weight
CutConfiguration(&oneTightTau_OS_CR3, true, LS); 					//selection, VBF, LS

oneTightTau_OS_CR3.select();        							//do selection, fill histograms

// ---------------------------------------------
// -- CENTRAL + InvertedVBF + 1 Tight Tau CR4 --
// ---------------------------------------------
Selection InvertedVBF_oneTightTau_OS_CR4("InvertedVBF_oneTightTau_OS_CR4"); 				//label and initialisation
InvertedVBF_oneTightTau_OS_CR4.InputCollection 		= &TauTMiIsoObjectSelectionCollection;       	//input collection
InvertedVBF_oneTightTau_OS_CR4.OutputCollection 	= &myHistoColl_OS_CR4;        			//output collection
InvertedVBF_oneTightTau_OS_CR4.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
InvertedVBF_oneTightTau_OS_CR4.RunData        		= false;        				//real data allowed
InvertedVBF_oneTightTau_OS_CR4.RequireTriggers          = false;       					//require at least one of the triggers fired
InvertedVBF_oneTightTau_OS_CR4.weight        		= weightTMi;        				//event weight
CutConfiguration(&InvertedVBF_oneTightTau_OS_CR4, false, LS); 						//selection, VBF, LS

InvertedVBF_oneTightTau_OS_CR4.select();        							//do selection, fill histograms
}

// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------
if(TauMMiIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiTightTau_OS_CR5("AntiTightTau_OS_CR5"); 						//label and initialisation
AntiTightTau_OS_CR5.InputCollection 		= &TauMMiIsoObjectSelectionCollection;		//input collection
AntiTightTau_OS_CR5.OutputCollection 		= &myHistoColl_OS_CR5;        			//output collection
AntiTightTau_OS_CR5.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
AntiTightTau_OS_CR5.RunData        		= false;        				//real data allowed
AntiTightTau_OS_CR5.RequireTriggers             = false;       					//require at least one of the triggers fired
AntiTightTau_OS_CR5.weight        		= weightMMi;        				//event weight
CutConfiguration(&AntiTightTau_OS_CR5, true, LS); 						//selection, VBF, LS

AntiTightTau_OS_CR5.select();        								//do selection, fill histograms

// ------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Tight Tau CR6 --
// ------------------------------------------------

Selection InvertedVBF_AntiTightTau_OS_CR6("InvertedVBF_AntiTightTau_OS_CR6"); 			//label and initialisation
InvertedVBF_AntiTightTau_OS_CR6.InputCollection 	= &TauMMiIsoObjectSelectionCollection;	//input collection
InvertedVBF_AntiTightTau_OS_CR6.OutputCollection 	= &myHistoColl_OS_CR6;        		//output collection
InvertedVBF_AntiTightTau_OS_CR6.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiTightTau_OS_CR6.RunData        		= false;        			//real data allowed
InvertedVBF_AntiTightTau_OS_CR6.RequireTriggers 	= false;       				//require at least one of the triggers fired
InvertedVBF_AntiTightTau_OS_CR6.weight        		= weightMMi;        			//event weight
CutConfiguration(&InvertedVBF_AntiTightTau_OS_CR6, false, LS); 					//selection, VBF, LS

InvertedVBF_AntiTightTau_OS_CR6.select();        						//do selection, fill histograms
}	

// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------
if(TauLLiIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiMediumTau_OS_CR7("AntiMediumTau_OS_CR7"); 			//label and initialisation
AntiMediumTau_OS_CR7.InputCollection 	= &TauLLiIsoObjectSelectionCollection;	//input collection
AntiMediumTau_OS_CR7.OutputCollection 	= &myHistoColl_OS_CR7;        		//output collection
AntiMediumTau_OS_CR7.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiMediumTau_OS_CR7.RunData        	= false;        			//real data allowed
AntiMediumTau_OS_CR7.RequireTriggers    = false;       				//require at least one of the triggers fired
AntiMediumTau_OS_CR7.weight        	= weightLLi;        			//event weight
CutConfiguration(&AntiMediumTau_OS_CR7, true, LS); 				//selection, VBF, LS

AntiMediumTau_OS_CR7.select();        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Medium Tau CR8 --
// -------------------------------------------------

Selection InvertedVBF_AntiMediumTau_OS_CR8("InvertedVBF_AntiMediumTau_OS_CR8"); 		//label and initialisation
InvertedVBF_AntiMediumTau_OS_CR8.InputCollection 	= &TauLLiIsoObjectSelectionCollection;	//input collection
InvertedVBF_AntiMediumTau_OS_CR8.OutputCollection 	= &myHistoColl_OS_CR8;        		//output collection
InvertedVBF_AntiMediumTau_OS_CR8.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiMediumTau_OS_CR8.RunData        	= false;        			//real data allowed
InvertedVBF_AntiMediumTau_OS_CR8.RequireTriggers        = false;       				//require at least one of the triggers fired
InvertedVBF_AntiMediumTau_OS_CR8.weight        		= weightLLi;        			//event weight
CutConfiguration(&InvertedVBF_AntiMediumTau_OS_CR8, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiMediumTau_OS_CR8.select();        						//do selection, fill histograms
}

// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------
if(TauNNIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiLooseTau_OS_CR9("AntiLooseTau_OS_CR9"); 				//label and initialisation
AntiLooseTau_OS_CR9.InputCollection 	= &TauNNIsoObjectSelectionCollection;	//input collection
AntiLooseTau_OS_CR9.OutputCollection 	= &myHistoColl_OS_CR9;        		//output collection
AntiLooseTau_OS_CR9.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
AntiLooseTau_OS_CR9.RunData        	= false;        			//real data allowed
AntiLooseTau_OS_CR9.RequireTriggers     = false;       				//require at least one of the triggers fired
AntiLooseTau_OS_CR9.weight        	= weightNN;        			//event weight
CutConfiguration(&AntiLooseTau_OS_CR9, true, LS); 				//selection, VBF, LS

AntiLooseTau_OS_CR9.select();        						//do selection, fill histograms

// -------------------------------------------------
// -- CENTRAL + InvertedVBF + Anti Loose Tau CR10 --
// -------------------------------------------------

Selection InvertedVBF_AntiLooseTau_OS_CR10("InvertedVBF_AntiLooseTau_OS_CR10"); 		//label and initialisation
InvertedVBF_AntiLooseTau_OS_CR10.InputCollection 	= &TauNNIsoObjectSelectionCollection;   //input collection
InvertedVBF_AntiLooseTau_OS_CR10.OutputCollection 	= &myHistoColl_OS_CR10;        		//output collection
InvertedVBF_AntiLooseTau_OS_CR10.RealData        	= eventhelper_isRealData;        	//pass information if event is real data
InvertedVBF_AntiLooseTau_OS_CR10.RunData        	= false;        			//real data allowed
InvertedVBF_AntiLooseTau_OS_CR10.RequireTriggers        = false;       				//require at least one of the triggers fired
InvertedVBF_AntiLooseTau_OS_CR10.weight        		= weightNN;        			//event weight
CutConfiguration(&InvertedVBF_AntiLooseTau_OS_CR10, false, LS); 				//selection, VBF, LS

InvertedVBF_AntiLooseTau_OS_CR10.select();        						//do selection, fill histograms
}

// ---------------------
// -- Z -> TauTau CR --
// ---------------------

Selection Ztautau_OS_CR1("Ztautau_OS_CR1"); 						//label and initialisation
Ztautau_OS_CR1.InputCollection 		= &TauTTIsoObjectSelectionCollection;		//input collection
Ztautau_OS_CR1.OutputCollection 	= &myHistoColl_OS_CR1;        			//output collection
Ztautau_OS_CR1.RealData        		= eventhelper_isRealData;        		//pass information if event is real data
Ztautau_OS_CR1.RunData        		= false;        				//real data allowed
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
Ztautau_OS_CR1.weight        		= weightTT;        				//event weight
Ztautau_OS_CR1.invertTauRequirements    = false;        				//invert number of taus requirement
Ztautau_OS_CR1.invertTauProperties      = false;        				//invert ditau properties (dR, sign)
Ztautau_OS_CR1.invertBtagRequirement	= false;        				//invert number of b-jets required
Ztautau_OS_CR1.invertJetRequirements    = false;        				//invert jet pt requirements
Ztautau_OS_CR1.invertDijetProperties    = false;        				//invert dijet system properties (dR, inv mass, sign eta, dEta)

Ztautau_OS_CR1.select();


//Clearing Object Collections
TauTightIsoObjectSelectionCollection.clear();
TauMediumIsoObjectSelectionCollection.clear();
TauLooseIsoObjectSelectionCollection.clear();
TauNoIsoObjectSelectionCollection.clear();
JetLooseIsoObjectSelectionCollection.clear();

TauTTIsoObjectSelectionCollection.clear();
TauTMiIsoObjectSelectionCollection.clear();
TauMMiIsoObjectSelectionCollection.clear();
TauLLiIsoObjectSelectionCollection.clear();
TauNNIsoObjectSelectionCollection.clear();
}
  stream.close();
  ofile.close();
  return 0;
}

