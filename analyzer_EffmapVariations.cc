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

#include "CommonHistoCollection.h"
#include "TH3.h"

using namespace std;

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

  //int nevents = 1000;
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

  //TH1F* h_mindeltaR = new TH1F("h_mindeltaR", "h_mindeltaR", 50,0. , 3.);

  double etaedges[5]={0.,1.4,1.6,2.,2.2};
  double etaExtended[23]={0.,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2};
  double ptedges[12]={0.,30.,45.,55.,75.,100.,250.,400.,600.,900.,1500.,2500.};
  double respEdges[29]={0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,1.50};
  double Nedges[31]={0,1,2,3,4,5,6,7,8,10,12,14,16,20,24,28,32,36,40,45,50,55,60,70,80,90,100,120,140,170,200};
  double FractionEdges[17]={0.0,0.05,0.1,0.15,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.8,0.85,0.9,0.95,1., 1.01};

  TH2F* h2_Nq_Fq_num = new TH2F("h2_Nq_Fq_num", "h2_Nq_Fq_num", 30, Nedges, 16, FractionEdges);
  TH2F* h2_Nq_Fq_den = new TH2F("h2_Nq_Fq_den", "h2_Nq_Fq_den", 30, Nedges, 16, FractionEdges);
  h2_Nq_Fq_num->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Fq_den->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Fq_num->GetYaxis()->SetTitle("F^{q}");
  h2_Nq_Fq_den->GetYaxis()->SetTitle("F^{q}");  
  h2_Nq_Fq_num->Sumw2();
  h2_Nq_Fq_den->Sumw2();
  
  TH2F* h2_Nq_pT_num = new TH2F("h2_Nq_pT_num", "h2_Nq_pT_num", 30, Nedges, 11, ptedges);
  TH2F* h2_Nq_pT_den = new TH2F("h2_Nq_pT_den", "h2_Nq_pT_den", 30, Nedges, 11, ptedges);
  h2_Nq_pT_num->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_pT_den->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_pT_num->GetYaxis()->SetTitle("p_{T}");
  h2_Nq_pT_den->GetYaxis()->SetTitle("p_{T}");  
  h2_Nq_pT_num->Sumw2();
  h2_Nq_pT_den->Sumw2(); 
  
  TH2F* h2_Nq_Abseta_num = new TH2F("h2_Nq_Abseta_num", "h2_Nq_Abseta_num", 30, Nedges, 4, etaedges);
  TH2F* h2_Nq_Abseta_den = new TH2F("h2_Nq_Abseta_den", "h2_Nq_Abseta_den", 30, Nedges, 4, etaedges);
  h2_Nq_Abseta_num->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Abseta_den->GetXaxis()->SetTitle("N^{q}");
  h2_Nq_Abseta_num->GetYaxis()->SetTitle("|#eta|");
  h2_Nq_Abseta_den->GetYaxis()->SetTitle("|#eta|");  
  h2_Nq_Abseta_num->Sumw2();
  h2_Nq_Abseta_den->Sumw2();  
  
  TH2F* h2_Fq_pT_num = new TH2F("h2_Fq_pT_num", "h2_Fq_pT_num", 16, FractionEdges, 11, ptedges);
  TH2F* h2_Fq_pT_den = new TH2F("h2_Fq_pT_den", "h2_Fq_pT_den", 16, FractionEdges, 11, ptedges);
  h2_Fq_pT_num->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_pT_den->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_pT_num->GetYaxis()->SetTitle("p_{T}");
  h2_Fq_pT_den->GetYaxis()->SetTitle("p_{T}");  
  h2_Fq_pT_num->Sumw2();
  h2_Fq_pT_den->Sumw2();    
  
  TH2F* h2_Fq_Abseta_num = new TH2F("h2_Fq_Abseta_num", "h2_Fq_Abseta_num", 16, FractionEdges, 4, etaedges);
  TH2F* h2_Fq_Abseta_den = new TH2F("h2_Fq_Abseta_den", "h2_Fq_Abseta_den", 16, FractionEdges, 4, etaedges);
  h2_Fq_Abseta_num->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_Abseta_den->GetXaxis()->SetTitle("F^{q}");
  h2_Fq_Abseta_num->GetYaxis()->SetTitle("|#eta|");
  h2_Fq_Abseta_den->GetYaxis()->SetTitle("|#eta|");  
  h2_Fq_Abseta_num->Sumw2();
  h2_Fq_Abseta_den->Sumw2();   

  TH2F* h2_pT_Abseta_num = new TH2F("h2_pT_Abseta_num", "h2_pT_Abseta_num", 11, ptedges, 4, etaedges);
  TH2F* h2_pT_Abseta_den = new TH2F("h2_pT_Abseta_den", "h2_pT_Abseta_den", 11, ptedges, 4, etaedges);
  h2_pT_Abseta_num->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_pT_Abseta_den->GetXaxis()->SetTitle("p_{T}^{jet}");
  h2_pT_Abseta_num->GetYaxis()->SetTitle("|#eta|");
  h2_pT_Abseta_den->GetYaxis()->SetTitle("|#eta|");  
  h2_pT_Abseta_num->Sumw2();
  h2_pT_Abseta_den->Sumw2();  
  
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

  TFile file_Pt("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseFactors_InclAndExclIsos_Jet30Tau45_NoPt15-30_Lukas_MC.root", "read");       

  MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
  /*MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
  MyEventCollection TauMediumInclIsoObjectSelectionCollection ("TauMediumInclIsoObjectSelection");
  MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
  MyEventCollection TauLooseInclIsoObjectSelectionCollection ("TauLooseInclIsoObjectSelection");
  MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");*/
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
	  if( goodVertex ) {
		TauTightIsoObjectSelectionCollection.goodVertex = true;
		/*TauMediumIsoObjectSelectionCollection.goodVertex = true;
		TauMediumInclIsoObjectSelectionCollection.goodVertex = true;
		TauLooseIsoObjectSelectionCollection.goodVertex = true;
		TauLooseInclIsoObjectSelectionCollection.goodVertex = true;
		TauNoIsoObjectSelectionCollection.goodVertex = true;*/
	  }

          //trigger selection
   
          if (
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1)

             ) { TauTightIsoObjectSelectionCollection.passedTrigger = true;
	         /*TauMediumIsoObjectSelectionCollection.passedTrigger = true;
		 TauMediumInclIsoObjectSelectionCollection.goodVertex = true;
	         TauLooseIsoObjectSelectionCollection.passedTrigger = true;
		 TauLooseInclIsoObjectSelectionCollection.goodVertex = true;
	         TauNoIsoObjectSelectionCollection.passedTrigger = true;*/
               }

          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            //if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5))  TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    /*else if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)){
	      TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
	    else if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)){
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
	    else{
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauNoIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }*/
          }

          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.7                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}

	  //MET selection
	  TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);
	  /*TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauMediumInclIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseInclIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);*/

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// --   Tau Efficency    --
	// ------------------------
	//TH1F* ReweightFactorN = (TH1F*)(file_Pt.Get("RescaleWeightN"));
	//TH1F* ReweightFactorL = (TH1F*)(file_Pt.Get("RescaleWeightL"));
	//TH1F* ReweightFactorLi = (TH1F*)(file_Pt.Get("RescaleWeightLi"));
	//TH1F* ReweightFactorM = (TH1F*)(file_Pt.Get("RescaleWeightM"));
	//TH1F* ReweightFactorMi = (TH1F*)(file_Pt.Get("RescaleWeightMi"));
	TH1F* ReweightFactorT = (TH1F*)(file_Pt.Get("RescaleWeightT"));

	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){	
		double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRt = TauJetMinDistanceExtended(TauTightIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		/*pair <double, unsigned int>deltaRm = TauJetMinDistanceExtended(TauMediumIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRmi = TauJetMinDistanceExtended(TauMediumInclIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRl = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRli = TauJetMinDistanceExtended(TauLooseInclIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRn = TauJetMinDistanceExtended(TauNoIsoObjectSelectionCollection,
		JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);*/
		//int nRescaleBinN= ReweightFactorN->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		//int nRescaleBinL= ReweightFactorL->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		//int nRescaleBinLi= ReweightFactorLi->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		//int nRescaleBinM= ReweightFactorM->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		//int nRescaleBinMi= ReweightFactorMi->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		int nRescaleBinT= ReweightFactorT->FindBin(JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		/*double weightN=1;//ReweightFactorN->GetBinContent(nRescaleBinN);
		double weightL=1;//ReweightFactorL->GetBinContent(nRescaleBinL);
		double weightLi=1;//ReweightFactorLi->GetBinContent(nRescaleBinLi);
		double weightM=1;//ReweightFactorM->GetBinContent(nRescaleBinM);
		double weightMi=1;//ReweightFactorMi->GetBinContent(nRescaleBinMi);*/
		double weightT=ReweightFactorT->GetBinContent(nRescaleBinT);
		double Nq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity;
		double Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;		
		/*if(Fq>1){std::cout<<"!!!scream!!!"<<std::endl;
		std::cout<<Fq<<" out of EM="<<JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction<<", Emu="<<JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction<<", Ehad="<<JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction<<std::endl;}*/
		if(jetMindR > 0.5){ //only count isolated jets
		  if( deltaRt.first < 0.1 ){
		  	h2_Nq_Fq_num->Fill(Nq,Fq,weightT);
			h2_Nq_pT_num->Fill(Nq,JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
			h2_Nq_Abseta_num->Fill(Nq,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
			h2_Fq_pT_num->Fill(Fq,JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
			h2_Fq_Abseta_num->Fill(Fq,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
			h2_pT_Abseta_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),1);
			//if(Fq==1)std::cout<<"num"<<std::endl;
		  }
		  /*if( deltaRm.first < 0.1 ) ChargeMapM_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightM);
		  if( deltaRmi.first < 0.1 ) ChargeMapMi_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightMi);
		  if( deltaRl.first < 0.1 ) ChargeMapL_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightL);		  
		  if( deltaRli.first < 0.1 ) ChargeMapLi_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightLi);		  
		  if( deltaRn.first < 0.1 ) ChargeMapN_num->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronMultiplicity+JetLooseIsoObjectSelectionCollection.jet[j]->electronMultiplicity,JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction,weightN);*/		  		  
		  if(fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta)<2.2)
		    {
		      //if(Fq==1)std::cout<<"den"<<std::endl;
		      h2_Nq_Fq_den->Fill(Nq,Fq,weightT);
		      h2_Nq_pT_den->Fill(Nq,JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      h2_Nq_Abseta_den->Fill(Nq,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
		      h2_Fq_pT_den->Fill(Fq,JetLooseIsoObjectSelectionCollection.jet[j]->pt,1);
		      h2_Fq_Abseta_den->Fill(Fq,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),weightT);
		      h2_pT_Abseta_den->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta),1);
		      /*if(fabs(JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction-1)>0.01){
		      std::cout<<"jet "<<j<<std::endl;
		      std::cout<<"charged EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction<<std::endl;
		      std::cout<<"neutral EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->neutralEmEnergyFraction<<std::endl;
		      std::cout<<"photon EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->photonEnergyFraction<<std::endl;
		      std::cout<<"muon EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction<<std::endl;
		      std::cout<<"electron EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->electronEnergyFraction<<std::endl;
		      std::cout<<"HF EM fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->HFEMEnergyFraction<<std::endl;
		      std::cout<<"charged Had fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction<<std::endl;
		      std::cout<<"neutral Had fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->neutralHadronEnergyFraction<<std::endl;
		      std::cout<<"HF Had fraction: "<<JetLooseIsoObjectSelectionCollection.jet[j]->HFHadronEnergyFraction<<std::endl;
		      }*/
		      //double R_MPF=RMPF(mainObjectSelectionCollection.met[0]->pt,mainObjectSelectionCollection.met[0]->phi,JetLooseIsoObjectSelectionCollection.jet[j]->pt,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		      //MetProjFrac_den->Fill(R_MPF,weight);
		    }
		}
	}
	
	//Clearing Object Collections 
	TauTightIsoObjectSelectionCollection.clear();
	/*TauMediumIsoObjectSelectionCollection.clear();
	TauMediumInclIsoObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();
	TauLooseInclIsoObjectSelectionCollection.clear();
	TauNoIsoObjectSelectionCollection.clear();*/
	JetLooseIsoObjectSelectionCollection.clear();
	}

  stream.close();
  ofile.close();
  return 0;
}

