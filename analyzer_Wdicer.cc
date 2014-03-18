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
	double weight = 1.;
	TFile file_eff("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Efficiency/ChargeMap_Fq-pT_30up.root", "read");
	TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseProfilesV2.root", "read");
	
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
double eff_fake_N=0.052;
double eff_fake_L=0.46;
double eff_fake_M=0.64;
double eff_fake_T=0.72;

double eff_real_N=0.43;
double eff_real_L=0.7;
double eff_real_M=0.88;
double eff_real_T=1;

//make scaled ChargeMaps
TH2F* ChargeMapN_eff = (TH2F*)(file_eff.Get("ChargeMapN_eff"));
ChargeMapN_eff->Scale(eff_fake_N); //out of Wjets

TH2F* ChargeMapL_eff = (TH2F*)(file_eff.Get("ChargeMapL_eff"));
ChargeMapL_eff->Scale(eff_fake_L); //out of Wjets

TH2F* ChargeMapLi_eff = (TH2F*)(file_eff.Get("ChargeMapL_num")->Clone("ChargeMapLi_eff"));
ChargeMapLi_eff->Scale(eff_fake_L); //out of Wjets
ChargeMapLi_eff->Add((TH2F*)file_eff.Get("ChargeMapN_num"),eff_fake_N); //out of Wjets
ChargeMapLi_eff->Divide((TH2F*)file_eff.Get("ChargeMapLi_den"));

TH2F* ChargeMapM_eff = (TH2F*)(file_eff.Get("ChargeMapM_eff"));
ChargeMapM_eff->Scale(eff_fake_M); //out of Wjets

TH2F* ChargeMapMi_eff = (TH2F*)(file_eff.Get("ChargeMapM_num")->Clone("ChargeMapMi_eff"));
ChargeMapMi_eff->Scale(eff_fake_M); //out of Wjets
ChargeMapMi_eff->Add((TH2F*)file_eff.Get("ChargeMapL_num"),eff_fake_L); //out of Wjets
ChargeMapMi_eff->Add((TH2F*)file_eff.Get("ChargeMapN_num"),eff_fake_N); //out of Wjets
ChargeMapMi_eff->Divide((TH2F*)file_eff.Get("ChargeMapMi_den"));

TH2F* ChargeMapT_eff = (TH2F*)(file_eff.Get("ChargeMapT_eff"));
ChargeMapT_eff->Scale(eff_fake_T); //out of Wjets

//make correctly combined ReweightFactors
TProfile* ReweightFactorN = (TProfile*)(file_Resp.Get("RescaleWeightN"));

TProfile* ReweightFactorL = (TProfile*)(file_Resp.Get("RescaleWeightL"));

TProfile* ReweightFactorLi = (TProfile*)(file_Resp.Get("RescaleWeightLi")->Clone("ReweightFactorLi"));
TProfile* ReweightFactorMi = (TProfile*)(file_Resp.Get("RescaleWeightMi")->Clone("ReweightFactorMi"));
for(int i=0; i<ReweightFactorLi->GetNbinsX(); i++) {
double L=((TProfile*)file_Resp.Get("RescaleWeightL"))->GetBinContent(i+1);
double Nl=((TProfile*)file_Resp.Get("RescaleWeightL"))->GetBinEntries(i+1);
double N=((TProfile*)file_Resp.Get("RescaleWeightN"))->GetBinContent(i+1);
double Nn=((TProfile*)file_Resp.Get("RescaleWeightN"))->GetBinEntries(i+1);
double M=((TProfile*)file_Resp.Get("RescaleWeightM"))->GetBinContent(i+1);
double Nm=((TProfile*)file_Resp.Get("RescaleWeightM"))->GetBinEntries(i+1);
if(Nl+Nn>0) {ReweightFactorLi->SetBinContent(i+1, (eff_fake_L*Nl*L+eff_fake_N*Nn*N)/(eff_fake_L*Nl+eff_fake_N*Nn)); ReweightFactorLi->SetBinEntries(i+1, 1);}
if(Nm+Nl+Nn>0) {ReweightFactorMi->SetBinContent(i+1, (eff_fake_M*Nm*M+eff_fake_L*Nl*L+eff_fake_N*Nn*N)/(eff_fake_M*Nm+eff_fake_L*Nl+eff_fake_N*Nn)); ReweightFactorMi->SetBinEntries(i+1, 1);}
}

for(int i=0; i<ReweightFactorLi->GetNbinsX(); i++) if(verbose)std::cout<<ReweightFactorLi->GetBinContent(i+1)<<std::endl;
TProfile* ReweightFactorM = (TProfile*)(file_Resp.Get("RescaleWeightM"));

TProfile* ReweightFactorT = (TProfile*)(file_Resp.Get("RescaleWeightT"));

//make correctly combined scale factors
TProfile* ScaleFactorN = (TProfile*)(file_Resp.Get("ScaleFactorN"));

TProfile* ScaleFactorL = (TProfile*)(file_Resp.Get("ScaleFactorL"));

TProfile* ScaleFactorLi = (TProfile*)(file_Resp.Get("ScaleFactorLi")->Clone("ScaleFactorLi")); 
TProfile* ScaleFactorMi = (TProfile*)(file_Resp.Get("ScaleFactorMi")->Clone("ScaleFactorMi"));
for(int i=0; i<ScaleFactorLi->GetNbinsX(); i++) {
double L=((TProfile*)file_Resp.Get("ScaleFactorL"))->GetBinContent(i+1);
double Nl=((TProfile*)file_Resp.Get("ScaleFactorL"))->GetBinEntries(i+1);
double N=((TProfile*)file_Resp.Get("ScaleFactorN"))->GetBinContent(i+1);
double Nn=((TProfile*)file_Resp.Get("ScaleFactorN"))->GetBinEntries(i+1);
double M=((TProfile*)file_Resp.Get("ScaleFactorM"))->GetBinContent(i+1);
double Nm=((TProfile*)file_Resp.Get("ScaleFactorM"))->GetBinEntries(i+1);
if(Nl+Nn>0) {ScaleFactorLi->SetBinContent(i+1, (eff_fake_L*Nl*L+eff_fake_N*Nn*N)/(eff_fake_L*Nl+eff_fake_N*Nn)); ScaleFactorLi->SetBinEntries(i+1, 1);}
if(Nm+Nl+Nn>0) {ScaleFactorMi->SetBinContent(i+1, (eff_fake_M*Nm*M+eff_fake_L*Nl*L+eff_fake_N*Nn*N)/(eff_fake_M*Nm+eff_fake_L*Nl+eff_fake_N*Nn)); ScaleFactorMi->SetBinEntries(i+1, 1);}
}

TProfile* ScaleFactorM = (TProfile*)(file_Resp.Get("ScaleFactorM"));

TProfile* ScaleFactorT = (TProfile*)(file_Resp.Get("ScaleFactorT"));

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
	  
        for (unsigned int g = 0; g < genparticlehelper.size(); g++){
		  if (  !(fabs(genparticlehelper[g].status)==3)  ) continue;
		  if (fabs(genparticlehelper[g].pdgId) == 15) genTau.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) == 13) genMu.push_back(&genparticlehelper[g]);
		  if (fabs(genparticlehelper[g].pdgId) == 11) genE.push_back(&genparticlehelper[g]);		  
		}
	
        // vertex selection
	/*bool goodVertex = true;

	if(!( vertex.size() > 0 )) goodVertex = false;
	if( goodVertex ) {
	  TauTightIsoObjectSelectionCollection.passedTrigger = true;
	  Tau1TightIsoObjectSelectionCollection.passedTrigger = true;
	  TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	  TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	  TauNoIsoObjectSelectionCollection.passedTrigger = true;
	}
	
	;*/

	
         /* //trigger selection
   
          if(
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1) ||
             (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1)

            )baselineObjectSelectionCollection.passedTrigger = true;*/

	// electron selection
	/*for(unsigned int e = 0;e<electron.size();++e){
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
	  if(!( muon[m].isGlobalMuon )) 					continue;
	  if(!( muon[m].isTrackerMuon )) 					continue;
	  if(!( muon[m].isPFMuon )) 						continue;
	  if(!( muon[m].numberOfMatchedStations > 1 )) 				continue;
	  if(!(( fabs(muon[m].muonBestTrack_dxy) < 0.2 )) &&
            ( fabs(muon[m]. muonBestTrack_dz) < 0.5 )) 				continue;
	  if(!( muon[m].globalTrack_normalizedChi2 < 10. )) 			continue;
	  if(!( muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0 )) 	continue;
	  if(!( muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0 )) 	continue;
	  if(!( muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5 )) continue;
	  if(!( muon[m].innerTrack_normalizedChi2 < 1.8 )) 			continue;
	  if(!( fabs(muon[m].innerTrack_dxy) < 3. )) 				continue;
	  if(!( fabs(muon[m].innerTrack_dz) < 30. )) 				continue;
	  TauTightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	  Tau1TightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	  TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	  TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	  TauNoIsoObjectSelectionCollection.muon.push_back(&muon[m]);
}
	*/
          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
	    
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    double dR=5.;
	    if(genTau.size()>0) dR=deltaR(tau[t].eta, tau[t].phi, genTau[0]->eta, genTau[0]->phi);
            if(dR<0.3){
	      if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      else if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      else if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      else TauNoIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
          }
	vector<double> jet_taufakerateT;
	vector<double> jet_taufakerateMi;
	vector<double> jet_taufakerateM;
	vector<double> jet_taufakerateLi;
	vector<double> jet_taufakerateL;
	vector<double> jet_taufakerateN;
	
	// jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	  double dR=5.;
	  if(genTau.size()>0) dR=deltaR(jet[j].eta, jet[j].phi, genTau[0]->eta, genTau[0]->phi);
	  if(dR<0.5) continue;
	  if(!( jet[j].pt >= 30. )) 		continue;
	  if(!( fabs(jet[j].eta) <= 2.7 )) 	continue;
	  JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}
	
	for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
	  double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[i]->eta,JetLooseIsoObjectSelectionCollection.jet[i]->phi);
	  double Fq=JetLooseIsoObjectSelectionCollection.jet[i]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[i]->chargedHadronEnergyFraction;		
	  int nbinN = ChargeMapN_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nRescaleBinN= ReweightFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nbinL = ChargeMapL_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nRescaleBinL= ReweightFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nbinLi = ChargeMapLi_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nRescaleBinLi= ReweightFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nbinM = ChargeMapM_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nRescaleBinM= ReweightFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nbinMi = ChargeMapMi_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nRescaleBinMi= ReweightFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nbinT = ChargeMapT_eff->FindBin(Fq,JetLooseIsoObjectSelectionCollection.jet[i]->pt);
	  int nRescaleBinT= ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);          
	  if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta) <=2.1)
  	    {
    	      jet_taufakerateN.push_back(ChargeMapN_eff->GetBinContent(nbinN)*ReweightFactorN->GetBinContent(nRescaleBinN));
    	      jet_taufakerateL.push_back(ChargeMapL_eff->GetBinContent(nbinL)*ReweightFactorL->GetBinContent(nRescaleBinL));
    	      jet_taufakerateLi.push_back(ChargeMapLi_eff->GetBinContent(nbinLi)*ReweightFactorLi->GetBinContent(nRescaleBinLi));
    	      jet_taufakerateM.push_back(ChargeMapM_eff->GetBinContent(nbinM)*ReweightFactorM->GetBinContent(nRescaleBinM));
    	      jet_taufakerateMi.push_back(ChargeMapMi_eff->GetBinContent(nbinMi)*ReweightFactorMi->GetBinContent(nRescaleBinMi));
    	      jet_taufakerateT.push_back(ChargeMapT_eff->GetBinContent(nbinT)*ReweightFactorT->GetBinContent(nRescaleBinT));
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
      	        }
    	      else
      	        {
        	  jet_taufakerateN.push_back(0);
    		  jet_taufakerateL.push_back(0);
		  jet_taufakerateLi.push_back(0);
		  jet_taufakerateM.push_back(0);
		  jet_taufakerateMi.push_back(0);
		  jet_taufakerateT.push_back(0);
      		}
	    }
	}
	
	if(genTau.size()==1){
	if(verbose)std::cout<<"enter genTau scenario"<<std::endl;
	//choose scenario, then roll fakes
	//T+T || Mi
	if(TauTightIsoObjectSelectionCollection.tau.size()==1){
	  if(verbose)std::cout<<"1 tight"<<std::endl;
	  //dice T for TT
	  double maxProbT=0.;
	  int wrongsT=0;
	  for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	    if(verbose)std::cout<<i<<": "<<jet_taufakerateT[i]<<std::endl;
	    double permutation=jet_taufakerateT[i];
	    for(unsigned int j=0; j<jet_taufakerateT.size(); j++) if(i!=j) permutation*=1-jet_taufakerateT[j];
	    weightTT+=permutation;
	    if(jet_taufakerateT[i]==0) wrongsT++;
	    else maxProbT+=jet_taufakerateT[i];
	  }
	  weightTT*=eff_real_T;
	  if(wrongsT < jet_taufakerateT.size()){
	    if(verbose)std::cout<<"start T + T dicing"<<std::endl;
	    std::uniform_real_distribution<double> distribution(0.0, maxProbT);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	      temp+=jet_taufakerateT[i];
	      if(jet_taufakerateT[i]==0) continue;
	      if(temp>=Toss){
	        if(verbose)std::cout<<"chosen jet "<<i<<std::endl;
	        tau_s faketauT;
	        int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightTT=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauT.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauT.charge = -1;
		faketauT.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauT.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauT.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauT.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauT.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauT.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauT.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauT.pt < 45) weightTT=0;
		faketauT.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(verbose)std::cout<<"assigning memory"<<std::endl;
		if(TauTightIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
		  TauTTIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);
		  TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT);
		}
		else{
		  TauTTIsoObjectSelectionCollection.tau.push_back(&faketauT);
		  TauTTIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);	
		}
	        break;
		if(verbose)std::cout<<"THIS SHOULD NEVER NEVER EVER SHOW UP"<<std::endl;
	      }
	    }
	  }
	  //dice Mi for TMi
	  double maxProbMi=0.;
	  int wrongsMi=0;
	  for(unsigned int i=0; i<jet_taufakerateMi.size(); i++){
	    double permutation=jet_taufakerateMi[i];
	    for(unsigned int j=0; j<jet_taufakerateMi.size(); j++) if(i!=j) permutation*=1-jet_taufakerateMi[j];
	    weightTMi+=permutation;
	    if(jet_taufakerateMi[i]==0) wrongsMi++;
	    else maxProbMi+=jet_taufakerateMi[i];
	  }
	  weightTMi*=eff_real_T;
	  if(wrongsMi<jet_taufakerateMi.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbMi);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateMi.size(); i++){
	      temp+=jet_taufakerateMi[i];
	      if(jet_taufakerateMi[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauMi;
	        int nScaleBin	  = ScaleFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorMi->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightTMi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauMi.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauMi.charge = -1;
		faketauMi.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauMi.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauMi.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauMi.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauMi.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauMi.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauMi.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauMi.pt < 45) weightTMi=0;
		faketauMi.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauMi.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauMi.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauTightIsoObjectSelectionCollection.tau[0]->pt > faketauMi.pt){
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);
		}
		else{
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);		
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);
		}
	        break;
	      }
	    }
	  }
	}
	//M+T || Mi
	if(TauMediumIsoObjectSelectionCollection.tau.size()==1){
	  if(verbose)std::cout<<"1 medium"<<std::endl;
	  //dice T for TMi
	  double maxProbT=0.;
	  int wrongsT=0;
	  for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	    double permutation=jet_taufakerateT[i];
	    for(unsigned int j=0; j<jet_taufakerateT.size(); j++) if(i!=j) permutation*=1-jet_taufakerateT[j];
	    weightTMi+=permutation;
	    if(jet_taufakerateT[i]==0) wrongsT++;
	    else maxProbT+=jet_taufakerateT[i];
	  }
	  weightTMi*=eff_real_M;
	  if(wrongsT < jet_taufakerateT.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbT);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	      temp+=jet_taufakerateT[i];
	      if(jet_taufakerateT[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauT;
	        int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightTMi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauT.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauT.charge = -1;
		faketauT.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauT.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauT.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauT.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauT.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauT.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauT.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauT.pt < 45) weightTT=0;
		faketauT.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauMediumIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
		}
		else{
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);	
		}
	        break;
	      }
	    }
	  }
	  //dice Mi for MMi
	  double maxProbMi=0.;
	  int wrongsMi=0;
	  for(unsigned int i=0; i<jet_taufakerateMi.size(); i++){
	    double permutation=jet_taufakerateMi[i];
	    for(unsigned int j=0; j<jet_taufakerateMi.size(); j++) if(i!=j) permutation*=1-jet_taufakerateMi[j];
	    weightMMi+=permutation;
	    if(jet_taufakerateMi[i]==0) wrongsMi++;
	    else maxProbMi+=jet_taufakerateMi[i];
	  }
	  weightMMi*=eff_real_M;
	  if(wrongsMi<jet_taufakerateMi.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbMi);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateMi.size(); i++){
	      temp+=jet_taufakerateMi[i];
	      if(jet_taufakerateMi[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauMi;
	        int nScaleBin	  = ScaleFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorMi->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightMMi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauMi.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauMi.charge = -1;
		faketauMi.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauMi.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauMi.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauMi.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauMi.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauMi.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauMi.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauMi.pt < 45) weightTMi=0;
		faketauMi.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauMi.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauMi.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauMediumIsoObjectSelectionCollection.tau[0]->pt > faketauMi.pt){
		  TauMMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);
		  TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);
		}
		else{
		  TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauMi);		
		  TauMMiIsoObjectSelectionCollection.tau.push_back(TauMediumIsoObjectSelectionCollection.tau[0]);
		}
	        break;
	      }
	    }
	  }
	}
	//L+T || M || Li
	if(TauLooseIsoObjectSelectionCollection.tau.size()==1){
	  if(verbose)std::cout<<"1 loose"<<std::endl;
	  //dice T for TMi
	  double maxProbT=0.;
	  int wrongsT=0;
	  for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	    double permutation=jet_taufakerateT[i];
	    for(unsigned int j=0; j<jet_taufakerateT.size(); j++) if(i!=j) permutation*=1-jet_taufakerateT[j];
	    weightTMi+=permutation;
	    if(jet_taufakerateT[i]==0) wrongsT++;
	    else maxProbT+=jet_taufakerateT[i];
	  }
	  weightTMi*=eff_real_L;
	  if(wrongsT < jet_taufakerateT.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbT);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	      temp+=jet_taufakerateT[i];
	      if(jet_taufakerateT[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauT;
	        int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightTMi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauT.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauT.charge = -1;
		faketauT.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauT.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauT.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauT.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauT.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauT.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauT.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauT.pt < 45) weightTT=0;
		faketauT.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauLooseIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
		}
		else{
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);	
		}
	        break;
	      }
	    }
	  }
	  //dice M for MMi
	  double maxProbM=0.;
	  int wrongsM=0;
	  for(unsigned int i=0; i<jet_taufakerateM.size(); i++){
	    double permutation=jet_taufakerateM[i];
	    for(unsigned int j=0; j<jet_taufakerateM.size(); j++) if(i!=j) permutation*=1-jet_taufakerateM[j];
	    weightMMi+=permutation;
	    if(jet_taufakerateM[i]==0) wrongsM++;
	    else maxProbM+=jet_taufakerateM[i];
	  }
	  weightMMi*=eff_real_L;
	  if(wrongsM<jet_taufakerateM.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbM);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateM.size(); i++){
	      temp+=jet_taufakerateM[i];
	      if(jet_taufakerateM[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauM;
	        int nScaleBin	  = ScaleFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorM->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightMMi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauM.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauM.charge = -1;
		faketauM.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauM.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauM.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauM.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauM.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauM.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauM.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauM.pt < 45) weightTMi=0;
		faketauM.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauM.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauM.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauLooseIsoObjectSelectionCollection.tau[0]->pt > faketauM.pt){
		  TauMMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
		  TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);
		}
		else{
		  TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);		
		  TauMMiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
		}
	        break;
	      }
	    }
	  }
	  //dice Li for LLi
	  double maxProbLi=0.;
	  int wrongsLi=0;
	  for(unsigned int i=0; i<jet_taufakerateLi.size(); i++){
	    double permutation=jet_taufakerateLi[i];
	    for(unsigned int j=0; j<jet_taufakerateLi.size(); j++) if(i!=j) permutation*=1-jet_taufakerateLi[j];
	    weightLLi+=permutation;
	    if(jet_taufakerateLi[i]==0) wrongsLi++;
	    else maxProbLi+=jet_taufakerateLi[i];
	  }
	  weightLLi*=eff_real_L;
	  if(wrongsLi<jet_taufakerateLi.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbLi);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateLi.size(); i++){
	      temp+=jet_taufakerateLi[i];
	      if(jet_taufakerateLi[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauLi;
	        int nScaleBin	  = ScaleFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorLi->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightLLi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauLi.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauLi.charge = -1;
		faketauLi.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauLi.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauLi.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauLi.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauLi.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauLi.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauLi.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauLi.pt < 45) weightTMi=0;
		faketauLi.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauLi.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauLi.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauLooseIsoObjectSelectionCollection.tau[0]->pt > faketauLi.pt){
		  TauLLiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
		  TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauLi);
		}
		else{
		  TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauLi);		
		  TauLLiIsoObjectSelectionCollection.tau.push_back(TauLooseIsoObjectSelectionCollection.tau[0]);
		}
	        break;
	      }
	    }
	  }
	}
	//N+T || M || L || N
	if(TauNoIsoObjectSelectionCollection.tau.size()==1){
	  if(verbose)std::cout<<"1 no iso"<<std::endl;
	  //dice T for TMi
	  double maxProbT=0.;
	  int wrongsT=0;
	  for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	    double permutation=jet_taufakerateT[i];
	    for(unsigned int j=0; j<jet_taufakerateT.size(); j++) if(i!=j) permutation*=1-jet_taufakerateT[j];
	    weightTMi+=permutation;
	    if(jet_taufakerateT[i]==0) wrongsT++;
	    else maxProbT+=jet_taufakerateT[i];
	  }
	  weightTMi*=eff_real_N;
	  if(wrongsT < jet_taufakerateT.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbT);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateT.size(); i++){
	      temp+=jet_taufakerateT[i];
	      if(jet_taufakerateT[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauT;
	        int nScaleBin	  = ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorT->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightTMi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauT.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauT.charge = -1;
		faketauT.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauT.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauT.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauT.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauT.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauT.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauT.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauT.pt < 45) weightTT=0;
		faketauT.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauT.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauT.pt){
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
		}
		else{
		  TauTMiIsoObjectSelectionCollection.tau.push_back(&faketauT);
		  TauTMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);	
		}
	        break;
	      }
	    }
	  }
	  //dice M for MMi
	  double maxProbM=0.;
	  int wrongsM=0;
	  for(unsigned int i=0; i<jet_taufakerateM.size(); i++){
	    double permutation=jet_taufakerateM[i];
	    for(unsigned int j=0; j<jet_taufakerateM.size(); j++) if(i!=j) permutation*=1-jet_taufakerateM[j];
	    weightMMi+=permutation;
	    if(jet_taufakerateM[i]==0) wrongsM++;
	    else maxProbM+=jet_taufakerateM[i];
	  }
	  weightMMi*=eff_real_N;
	  if(wrongsM<jet_taufakerateM.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbM);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateM.size(); i++){
	      temp+=jet_taufakerateM[i];
	      if(jet_taufakerateM[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauM;
	        int nScaleBin	  = ScaleFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorM->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightMMi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauM.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauM.charge = -1;
		faketauM.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauM.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauM.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauM.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauM.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauM.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauM.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauM.pt < 45) weightTMi=0;
		faketauM.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauM.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauM.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauM.pt){
		  TauMMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
		  TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);
		}
		else{
		  TauMMiIsoObjectSelectionCollection.tau.push_back(&faketauM);		
		  TauMMiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
		}
	        break;
	      }
	    }
	  }
	  //dice L for LLi
	  double maxProbL=0.;
	  int wrongsL=0;
	  for(unsigned int i=0; i<jet_taufakerateL.size(); i++){
	    double permutation=jet_taufakerateL[i];
	    for(unsigned int j=0; j<jet_taufakerateL.size(); j++) if(i!=j) permutation*=1-jet_taufakerateL[j];
	    weightLLi+=permutation;
	    if(jet_taufakerateL[i]==0) wrongsL++;
	    else maxProbL+=jet_taufakerateL[i];
	  }
	  weightLLi*=eff_real_N;
	  if(wrongsL<jet_taufakerateL.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbL);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateL.size(); i++){
	      temp+=jet_taufakerateL[i];
	      if(jet_taufakerateL[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauL;
	        int nScaleBin	  = ScaleFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorL->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightLLi=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauL.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauL.charge = -1;
		faketauL.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauL.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauL.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauL.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauL.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauL.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauL.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauL.pt < 45) weightTMi=0;
		faketauL.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauL.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauL.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauL.pt){
		  TauLLiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
		  TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauL);
		}
		else{
		  TauLLiIsoObjectSelectionCollection.tau.push_back(&faketauL);		
		  TauLLiIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
		}
	        break;
	      }
	    }
	  }
	  //dice N for NN
	  double maxProbN=0.;
	  int wrongsN=0;
	  for(unsigned int i=0; i<jet_taufakerateN.size(); i++){
	    double permutation=jet_taufakerateN[i];
	    for(unsigned int j=0; j<jet_taufakerateN.size(); j++) if(i!=j) permutation*=1-jet_taufakerateN[j];
	    weightNN+=permutation;
	    if(jet_taufakerateN[i]==0) wrongsN++;
	    else maxProbN+=jet_taufakerateN[i];
	  }
	  weightNN*=eff_real_N;
	  if(wrongsN<jet_taufakerateN.size()){
	    std::uniform_real_distribution<double> distribution(0.0, maxProbN);
	    std::random_device rd;
	    std::mt19937 engine(rd()); // Mersenne twister MT19937
	    double Toss=distribution(engine);
	    double temp=0.;
	    for(unsigned int i=0; i<jet_taufakerateN.size(); i++){
	      temp+=jet_taufakerateN[i];
	      if(jet_taufakerateN[i]==0) continue;
	      if(temp>=Toss){
	        tau_s faketauN;
	        int nScaleBin	  = ScaleFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt);
		double scale 	  = ScaleFactorN->GetBinContent(nScaleBin);
		if(scale == 0) {scale = 0.851; weightNN=0;}

		if(JetLooseIsoObjectSelectionCollection.jet[i]->charge >= 0 )
		faketauN.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[i]->charge < 0 )
		faketauN.charge = -1;
		faketauN.p = JetLooseIsoObjectSelectionCollection.jet[i]->p;
		faketauN.energy = JetLooseIsoObjectSelectionCollection.jet[i]->energy;
		faketauN.et = JetLooseIsoObjectSelectionCollection.jet[i]->et;
		faketauN.px = JetLooseIsoObjectSelectionCollection.jet[i]->px;
		faketauN.py = JetLooseIsoObjectSelectionCollection.jet[i]->py;
		faketauN.pz = JetLooseIsoObjectSelectionCollection.jet[i]->pz;
		faketauN.pt = JetLooseIsoObjectSelectionCollection.jet[i]->pt * scale;
		if(faketauN.pt < 45) weightTMi=0;
		faketauN.phi = JetLooseIsoObjectSelectionCollection.jet[i]->phi;
		if(JetLooseIsoObjectSelectionCollection.jet[i]->eta<=2.1) faketauN.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta;
		else faketauN.eta = JetLooseIsoObjectSelectionCollection.jet[i]->eta/fabs(JetLooseIsoObjectSelectionCollection.jet[i]->eta)*2.1;
		if(TauNoIsoObjectSelectionCollection.tau[0]->pt > faketauN.pt){
		  TauNNIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
		  TauNNIsoObjectSelectionCollection.tau.push_back(&faketauN);
		}
		else{
		  TauNNIsoObjectSelectionCollection.tau.push_back(&faketauN);		
		  TauNNIsoObjectSelectionCollection.tau.push_back(TauNoIsoObjectSelectionCollection.tau[0]);
		}
	        break;
	      }
	    }
	  }
	}
	if(verbose)std::cout<<"end of all scenarios for 1 gen tau"<<std::endl;			  
    }
    //beginning 3+jets scenario -  only needed if Wjets is a sizeable contribution!
    else if(genMu.size()+genE.size()+genTau.size()==0){
        if(verbose)std::cout<<"enter 0 lepton scenario"<<std::endl;
    	Fake FakeTausN("FakeTaus");
	FakeTausN.generate(jet_taufakerateN,jet_taufakerateN, true);

	tau_s faketau1N;
	tau_s faketau2N;

	if ( FakeTausN.index.first >= 0 && FakeTausN.index.second >= 0 ) {

	  double scale = ScaleFactorN->GetBinContent(ScaleFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.first]->pt)); 
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

	  double scale2 = ScaleFactorN->GetBinContent(ScaleFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausN.index.second]->pt));
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

	  double scale = ScaleFactorL->GetBinContent(ScaleFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.first]->pt)); 
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

	  double scale2 = ScaleFactorLi->GetBinContent(ScaleFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausL.index.second]->pt));
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
	  weightLLi=FakeTausL.weight;
	}

	Fake FakeTausM("FakeTausM");

	FakeTausM.generate(jet_taufakerateM,jet_taufakerateMi, false);

	tau_s faketau1M;
	tau_s faketau2M;

	if ( FakeTausM.index.first >= 0 && FakeTausM.index.second >= 0 ) {

	  double scale = ScaleFactorM->GetBinContent(ScaleFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.first]->pt)); 
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

	  double scale2 = ScaleFactorMi->GetBinContent(ScaleFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausM.index.second]->pt));
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
	  weightMMi=FakeTausM.weight;
	}

	Fake FakeTausT("FakeTausT");
	FakeTausT.generate(jet_taufakerateT,jet_taufakerateMi, false);

	tau_s faketau1T;
	tau_s faketau2T;

	if ( FakeTausT.index.first >= 0 && FakeTausT.index.second >= 0 ) {

	  double scale = ScaleFactorT->GetBinContent(ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.first]->pt)); 
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

	  double scale2 = ScaleFactorMi->GetBinContent(ScaleFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausT.index.second]->pt));
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

	  double scale = ScaleFactorT->GetBinContent(ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.first]->pt)); 
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

	  double scale2 = ScaleFactorT->GetBinContent(ScaleFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[FakeTausTT.index.second]->pt));
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
	  double Distance1T = TauJetMinDistance(TauTMiIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
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
if(verbose)std::cout<<"selection starts"<<std::endl;
// ---------------------
// -- Signal Region --
// ---------------------
if(TauTTIsoObjectSelectionCollection.jet.size()>=2){
Selection Signal("Signal"); //label and initialisation
Signal.InputCollection 		= &TauTTIsoObjectSelectionCollection;        //input collection
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
Signal.METMin                   = 30.;      // minimum MET requirement
Signal.METMax                   = -1;       // maximum MET requirement
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
Signal.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
Signal.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
Signal.weight        		= weightTT;        //event weight
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
InvertedVBF_CR2.InputCollection 	= &TauTTIsoObjectSelectionCollection;        //input collection
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
InvertedVBF_CR2.METMin                   = 30.;      // minimum MET requirement
InvertedVBF_CR2.METMax                   = -1;       // maximum MET requirement
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
InvertedVBF_CR2.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_CR2.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_CR2.weight        		= weightTT;        //event weight
InvertedVBF_CR2.invertTauRequirements   = false;        //invert number of taus requirement
InvertedVBF_CR2.invertTauProperties     = false;        //invert ditau properties (dR, sign)
InvertedVBF_CR2.invertBtagRequirement   = false;        //invert number of b-jets required
InvertedVBF_CR2.invertJetRequirements   = true;        //invert jet pt requirements
InvertedVBF_CR2.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_CR2.select();        //do selection, fill histograms
}
// -------------------------------
// -- CENTRAL + 1 Tight Tau CR3 --
// -------------------------------
if(TauTMiIsoObjectSelectionCollection.jet.size()>=2){
Selection oneTightTau_CR3("oneTightTau_CR3"); //label and initialisation
oneTightTau_CR3.InputCollection 	= &TauTMiIsoObjectSelectionCollection;        //input collection
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
oneTightTau_CR3.METMin                   = 30.;      // minimum MET requirement
oneTightTau_CR3.METMax                   = -1;       // maximum MET requirement
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
oneTightTau_CR3.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
oneTightTau_CR3.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
oneTightTau_CR3.weight        		= weightTMi;        //event weight
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
InvertedVBF_oneTightTau_CR4.InputCollection 		= &TauTMiIsoObjectSelectionCollection;        //input collection
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
InvertedVBF_oneTightTau_CR4.METMin                   = 30.;      // minimum MET requirement
InvertedVBF_oneTightTau_CR4.METMax                   = -1;       // maximum MET requirement
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
InvertedVBF_oneTightTau_CR4.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_oneTightTau_CR4.weight        		= weightTMi;        //event weight
InvertedVBF_oneTightTau_CR4.invertTauRequirements       = false;        //invert number of taus requirement
InvertedVBF_oneTightTau_CR4.invertTauProperties         = false;        //invert ditau properties (dR, sign)
InvertedVBF_oneTightTau_CR4.invertBtagRequirement       = false;        //invert number of b-jets required
InvertedVBF_oneTightTau_CR4.invertJetRequirements       = true;        //invert jet pt requirements
InvertedVBF_oneTightTau_CR4.invertDijetProperties       = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_oneTightTau_CR4.select();        //do selection, fill histograms
}
// ----------------------------------
// -- CENTRAL + Anti Tight Tau CR5 --
// ----------------------------------
if(TauMMiIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiTightTau_CR5("AntiTightTau_CR5"); //label and initialisation
AntiTightTau_CR5.InputCollection 		= &TauMMiIsoObjectSelectionCollection;        //input collection
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
AntiTightTau_CR5.METMin                   = 30.;      // minimum MET requirement
AntiTightTau_CR5.METMax                   = -1;       // maximum MET requirement
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
AntiTightTau_CR5.DiJetDetaMin        		= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
AntiTightTau_CR5.DiJetDetaMax        		= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
AntiTightTau_CR5.weight        			= weightMMi;        //event weight
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
InvertedVBF_AntiTightTau_CR6.InputCollection 		= &TauMMiIsoObjectSelectionCollection;        //input collection
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
InvertedVBF_AntiTightTau_CR6.METMin                   = 30.;      // minimum MET requirement
InvertedVBF_AntiTightTau_CR6.METMax                   = -1;       // maximum MET requirement
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
InvertedVBF_AntiTightTau_CR6.DiJetDetaMin       	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.DiJetDetaMax       	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_AntiTightTau_CR6.weight        		= weightMMi;        //event weight
InvertedVBF_AntiTightTau_CR6.invertTauRequirements      = false;        //invert number of taus requirement
InvertedVBF_AntiTightTau_CR6.invertTauProperties        = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiTightTau_CR6.invertBtagRequirement      = false;        //invert number of b-jets required
InvertedVBF_AntiTightTau_CR6.invertJetRequirements      = true;        //invert jet pt requirements
InvertedVBF_AntiTightTau_CR6.invertDijetProperties      = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiTightTau_CR6.select();        //do selection, fill histograms
}
// -----------------------------------
// -- CENTRAL + Anti Medium Tau CR7 --
// -----------------------------------
if(TauLLiIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiMediumTau_CR7("AntiMediumTau_CR7"); //label and initialisation
AntiMediumTau_CR7.InputCollection 	= &TauLLiIsoObjectSelectionCollection;        //input collection
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
AntiMediumTau_CR7.METMin                   = 30.;      // minimum MET requirement
AntiMediumTau_CR7.METMax                   = -1;       // maximum MET requirement
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
AntiMediumTau_CR7.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
AntiMediumTau_CR7.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
AntiMediumTau_CR7.weight        	= weightLLi;        //event weight
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
InvertedVBF_AntiMediumTau_CR8.InputCollection 		= &TauLLiIsoObjectSelectionCollection;        //input collection
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
InvertedVBF_AntiMediumTau_CR8.METMin                   = 30.;      // minimum MET requirement
InvertedVBF_AntiMediumTau_CR8.METMax                   = -1;       // maximum MET requirement
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
InvertedVBF_AntiMediumTau_CR8.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_AntiMediumTau_CR8.weight        		= weightLLi;        //event weight
InvertedVBF_AntiMediumTau_CR8.invertTauRequirements     = false;        //invert number of taus requirement
InvertedVBF_AntiMediumTau_CR8.invertTauProperties       = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiMediumTau_CR8.invertBtagRequirement     = false;        //invert number of b-jets required
InvertedVBF_AntiMediumTau_CR8.invertJetRequirements     = true;        //invert jet pt requirements
InvertedVBF_AntiMediumTau_CR8.invertDijetProperties     = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiMediumTau_CR8.select();        //do selection, fill histograms
}
// -----------------------------------
// -- CENTRAL + Anti Loose Tau CR9 ---
// -----------------------------------
if(TauNNIsoObjectSelectionCollection.jet.size()>=2){
Selection AntiLooseTau_CR9("AntiLooseTau_CR9"); //label and initialisation
AntiLooseTau_CR9.InputCollection 	= &TauNNIsoObjectSelectionCollection;        //input collection
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
AntiLooseTau_CR9.METMin                   = 30.;      // minimum MET requirement
AntiLooseTau_CR9.METMax                   = -1;       // maximum MET requirement
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
AntiLooseTau_CR9.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
AntiLooseTau_CR9.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
AntiLooseTau_CR9.weight        		= weightNN;        //event weight
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
InvertedVBF_AntiLooseTau_CR10.InputCollection 		= &TauNNIsoObjectSelectionCollection;        //input collection
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
InvertedVBF_AntiLooseTau_CR10.METMin                   = 30.;      // minimum MET requirement
InvertedVBF_AntiLooseTau_CR10.METMax                   = -1;       // maximum MET requirement
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
InvertedVBF_AntiLooseTau_CR10.DiJetDetaMin        	= 4.2;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
InvertedVBF_AntiLooseTau_CR10.weight        		= weightNN;        //event weight
InvertedVBF_AntiLooseTau_CR10.invertTauRequirements     = false;        //invert number of taus requirement
InvertedVBF_AntiLooseTau_CR10.invertTauProperties       = false;        //invert ditau properties (dR, sign)
InvertedVBF_AntiLooseTau_CR10.invertBtagRequirement     = false;        //invert number of b-jets required
InvertedVBF_AntiLooseTau_CR10.invertJetRequirements     = true;        //invert jet pt requirements
InvertedVBF_AntiLooseTau_CR10.invertDijetProperties     = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

InvertedVBF_AntiLooseTau_CR10.select();        //do selection, fill histograms
}  

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

