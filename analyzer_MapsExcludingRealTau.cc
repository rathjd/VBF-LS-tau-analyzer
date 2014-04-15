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

  double ptedges[21]={22.5,23.7,25.,26.5,28.1,30.,32.1,34.6,37.5,40.9,45.,50.,56.3,64.3,75.,90.,112.5,150.,225.,450.,2500.};
  double FractionEdges[17]={0.0,0.05,0.1,0.15,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.8,0.85,0.9,0.95,1.,1.01};

  TH2F* ChargeMapN_num = new TH2F("ChargeMapN_num","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);
  ChargeMapN_num->GetXaxis()->SetTitle("F^{q}");
  ChargeMapN_num->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapN_num->Sumw2();
  TH2F* ChargeMapL_num = new TH2F("ChargeMapL_num","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);
  ChargeMapL_num->GetXaxis()->SetTitle("F^{q}");
  ChargeMapL_num->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapL_num->Sumw2();  
  TH2F* ChargeMapLi_num = new TH2F("ChargeMapLi_num","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);
  ChargeMapLi_num->GetXaxis()->SetTitle("F^{q}");
  ChargeMapLi_num->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapLi_num->Sumw2();    
  TH2F* ChargeMapM_num = new TH2F("ChargeMapM_num","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);
  ChargeMapM_num->GetXaxis()->SetTitle("F^{q}");
  ChargeMapM_num->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapM_num->Sumw2();
  TH2F* ChargeMapMi_num = new TH2F("ChargeMapMi_num","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);
  ChargeMapMi_num->GetXaxis()->SetTitle("F^{q}");
  ChargeMapMi_num->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapMi_num->Sumw2(); 
  TH2F* ChargeMapT_num = new TH2F("ChargeMapT_num","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);
  ChargeMapT_num->GetXaxis()->SetTitle("F^{q}");
  ChargeMapT_num->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapT_num->Sumw2();    
  TH2F* ChargeMapN_den = new TH2F("ChargeMapN_den","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);  
  ChargeMapN_den->GetXaxis()->SetTitle("F^{q}");
  ChargeMapN_den->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapN_den->Sumw2();
  TH2F* ChargeMapL_den = new TH2F("ChargeMapL_den","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);  
  ChargeMapL_den->GetXaxis()->SetTitle("F^{q}");
  ChargeMapL_den->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapL_den->Sumw2();  
  TH2F* ChargeMapLi_den = new TH2F("ChargeMapLi_den","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);  
  ChargeMapLi_den->GetXaxis()->SetTitle("F^{q}");
  ChargeMapLi_den->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapLi_den->Sumw2();   
  TH2F* ChargeMapM_den = new TH2F("ChargeMapM_den","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);  
  ChargeMapM_den->GetXaxis()->SetTitle("F^{q}");
  ChargeMapM_den->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapM_den->Sumw2();  
  TH2F* ChargeMapMi_den = new TH2F("ChargeMapMi_den","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);  
  ChargeMapMi_den->GetXaxis()->SetTitle("F^{q}");
  ChargeMapMi_den->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapMi_den->Sumw2();   
  TH2F* ChargeMapT_den = new TH2F("ChargeMapT_den","charged energy fraction vs transverse impulse", 16, FractionEdges, 20, ptedges);  
  ChargeMapT_den->GetXaxis()->SetTitle("F^{q}");
  ChargeMapT_den->GetYaxis()->SetTitle("p_{T}^{jet}");
  ChargeMapT_den->Sumw2();  
  
  TH2F* ChargeMapT_num_Uds = (TH2F*) ChargeMapT_num->Clone("ChargeMapT_num_Uds");
  TH2F* ChargeMapT_num_C   = (TH2F*) ChargeMapT_num->Clone("ChargeMapT_num_C");
  TH2F* ChargeMapT_num_B   = (TH2F*) ChargeMapT_num->Clone("ChargeMapT_num_B");
  TH2F* ChargeMapT_num_G   = (TH2F*) ChargeMapT_num->Clone("ChargeMapT_num_G");
  TH2F* ChargeMapT_num_Un  = (TH2F*) ChargeMapT_num->Clone("ChargeMapT_num_Un");  
  
  TH2F* ChargeMapM_num_Uds = (TH2F*) ChargeMapM_num->Clone("ChargeMapM_num_Uds");
  TH2F* ChargeMapM_num_C   = (TH2F*) ChargeMapM_num->Clone("ChargeMapM_num_C");
  TH2F* ChargeMapM_num_B   = (TH2F*) ChargeMapM_num->Clone("ChargeMapM_num_B");
  TH2F* ChargeMapM_num_G   = (TH2F*) ChargeMapM_num->Clone("ChargeMapM_num_G");
  TH2F* ChargeMapM_num_Un  = (TH2F*) ChargeMapM_num->Clone("ChargeMapM_num_Un");  
  
  TH2F* ChargeMapL_num_Uds = (TH2F*) ChargeMapL_num->Clone("ChargeMapL_num_Uds");
  TH2F* ChargeMapL_num_C   = (TH2F*) ChargeMapL_num->Clone("ChargeMapL_num_C");
  TH2F* ChargeMapL_num_B   = (TH2F*) ChargeMapL_num->Clone("ChargeMapL_num_B");
  TH2F* ChargeMapL_num_G   = (TH2F*) ChargeMapL_num->Clone("ChargeMapL_num_G");
  TH2F* ChargeMapL_num_Un  = (TH2F*) ChargeMapL_num->Clone("ChargeMapL_num_Un");  
  
  TH2F* ChargeMapN_num_Uds = (TH2F*) ChargeMapN_num->Clone("ChargeMapN_num_Uds");
  TH2F* ChargeMapN_num_C   = (TH2F*) ChargeMapN_num->Clone("ChargeMapN_num_C");
  TH2F* ChargeMapN_num_B   = (TH2F*) ChargeMapN_num->Clone("ChargeMapN_num_B");
  TH2F* ChargeMapN_num_G   = (TH2F*) ChargeMapN_num->Clone("ChargeMapN_num_G");
  TH2F* ChargeMapN_num_Un  = (TH2F*) ChargeMapN_num->Clone("ChargeMapN_num_Un");  
  
  TH2F* ChargeMapT_den_Uds = (TH2F*) ChargeMapT_den->Clone("ChargeMapT_den_Uds");
  TH2F* ChargeMapT_den_C   = (TH2F*) ChargeMapT_den->Clone("ChargeMapT_den_C");
  TH2F* ChargeMapT_den_B   = (TH2F*) ChargeMapT_den->Clone("ChargeMapT_den_B");
  TH2F* ChargeMapT_den_G   = (TH2F*) ChargeMapT_den->Clone("ChargeMapT_den_G");
  TH2F* ChargeMapT_den_Un  = (TH2F*) ChargeMapT_den->Clone("ChargeMapT_den_Un");  
  
  TH2F* ChargeMapM_den_Uds = (TH2F*) ChargeMapM_den->Clone("ChargeMapM_den_Uds");
  TH2F* ChargeMapM_den_C   = (TH2F*) ChargeMapM_den->Clone("ChargeMapM_den_C");
  TH2F* ChargeMapM_den_B   = (TH2F*) ChargeMapM_den->Clone("ChargeMapM_den_B");
  TH2F* ChargeMapM_den_G   = (TH2F*) ChargeMapM_den->Clone("ChargeMapM_den_G");
  TH2F* ChargeMapM_den_Un  = (TH2F*) ChargeMapM_den->Clone("ChargeMapM_den_Un");  
  
  TH2F* ChargeMapL_den_Uds = (TH2F*) ChargeMapL_den->Clone("ChargeMapL_den_Uds");
  TH2F* ChargeMapL_den_C   = (TH2F*) ChargeMapL_den->Clone("ChargeMapL_den_C");
  TH2F* ChargeMapL_den_B   = (TH2F*) ChargeMapL_den->Clone("ChargeMapL_den_B");
  TH2F* ChargeMapL_den_G   = (TH2F*) ChargeMapL_den->Clone("ChargeMapL_den_G");
  TH2F* ChargeMapL_den_Un  = (TH2F*) ChargeMapL_den->Clone("ChargeMapL_den_Un");  
  
  TH2F* ChargeMapN_den_Uds = (TH2F*) ChargeMapN_den->Clone("ChargeMapN_den_Uds");
  TH2F* ChargeMapN_den_C   = (TH2F*) ChargeMapN_den->Clone("ChargeMapN_den_C");
  TH2F* ChargeMapN_den_B   = (TH2F*) ChargeMapN_den->Clone("ChargeMapN_den_B");
  TH2F* ChargeMapN_den_G   = (TH2F*) ChargeMapN_den->Clone("ChargeMapN_den_G");
  TH2F* ChargeMapN_den_Un  = (TH2F*) ChargeMapN_den->Clone("ChargeMapN_den_Un");          
  
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

  MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
  MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
  MyEventCollection TauMediumInclIsoObjectSelectionCollection ("TauMediumInclIsoObjectSelection");
  MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
  MyEventCollection TauLooseInclIsoObjectSelectionCollection ("TauLooseInclIsoObjectSelection");
  MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");
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
		TauTightIsoObjectSelectionCollection.goodVertex = true;
		TauMediumIsoObjectSelectionCollection.goodVertex = true;
		TauMediumInclIsoObjectSelectionCollection.goodVertex = true;
		TauLooseIsoObjectSelectionCollection.goodVertex = true;
		TauLooseInclIsoObjectSelectionCollection.goodVertex = true;
		TauNoIsoObjectSelectionCollection.goodVertex = true;
	    }
	  }

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

          //trigger selection
   
          if (
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v3 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Prong1_v4 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v2 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v3 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v4 == 1) ||
                (triggerresultshelper_value_HLT_DoubleMediumIsoPFTau35_Trk5_eta2p1_Prong1_v6 == 1)

             ) { TauTightIsoObjectSelectionCollection.passedTrigger = true;
	         TauMediumIsoObjectSelectionCollection.passedTrigger = true;
		 TauMediumInclIsoObjectSelectionCollection.goodVertex = true;
	         TauLooseIsoObjectSelectionCollection.passedTrigger = true;
		 TauLooseInclIsoObjectSelectionCollection.goodVertex = true;
	         TauNoIsoObjectSelectionCollection.passedTrigger = true;
               }

          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            //if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronMediumMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonLoose3 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFindingNewDMs > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT  <= 0.5))  TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT  <= 0.5)){
	      TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
	    else if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT  <= 0.5)){
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
	    else{
	      TauMediumInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauLooseInclIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	      TauNoIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    }
          }

          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    //if(!(      jet[j].pt >= 30.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.6                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}

	  //MET selection
	  TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauMediumIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauMediumInclIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseInclIsoObjectSelectionCollection.met.push_back(&met[0]);
	  TauNoIsoObjectSelectionCollection.met.push_back(&met[0]);

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// --   Tau Efficency    --
	// ------------------------
	
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
		//remove real tau
		double dR=5.;
	        if(genTau.size()>0) for(unsigned int i=0; i<genTau.size(); i++){
		  double dRtemp=deltaR(jet[j].eta, jet[j].phi, genTau[i]->eta, genTau[i]->phi);
		  if(dRtemp<dR) dR=dRtemp;
		}
		if(genMu.size()>0) for(unsigned int i=0; i<genMu.size(); i++){
		  double dRtemp=deltaR(jet[j].eta, jet[j].phi, genMu[i]->eta, genMu[i]->phi);
		  if(dRtemp<dR) dR=dRtemp;
		}
		if(genE.size()>0) for(unsigned int i=0; i<genE.size(); i++){
		  double dRtemp=deltaR(jet[j].eta, jet[j].phi, genE[i]->eta, genE[i]->phi);
		  if(dRtemp<dR) dR=dRtemp;
		}
		if(dR<0.3) continue;
		
		//search for most likely origin parton
		double dRorigin=5.;
		int CulpritCode=0;
		if(genUds.size()>0) for(unsigned int i=0; i<genUds.size(); i++){
		  double dRtemp=deltaR(jet[j].eta, jet[j].phi, genUds[i]->eta, genUds[i]->phi);
		  if(dRtemp<dRorigin){
		    dRorigin=dRtemp;
		    if(dRorigin<0.3) CulpritCode=1;
		  }  
		}
		if(genC.size()>0) for(unsigned int i=0; i<genC.size(); i++){
		  double dRtemp=deltaR(jet[j].eta, jet[j].phi, genC[i]->eta, genC[i]->phi);
		  if(dRtemp<dRorigin){
		    dRorigin=dRtemp;
		    if(dRorigin<0.3) CulpritCode=4;
		  }  
		}
		if(genB.size()>0) for(unsigned int i=0; i<genB.size(); i++){
		  double dRtemp=deltaR(jet[j].eta, jet[j].phi, genB[i]->eta, genB[i]->phi);
		  if(dRtemp<dRorigin){
		    dRorigin=dRtemp;
		    if(dRorigin<0.3) CulpritCode=5;
		  }  
		}
		if(genG.size()>0) for(unsigned int i=0; i<genG.size(); i++){
		  double dRtemp=deltaR(jet[j].eta, jet[j].phi, genG[i]->eta, genG[i]->phi);
		  if(dRtemp<dRorigin){
		    dRorigin=dRtemp;
		    if(dRorigin<0.3) CulpritCode=21;
		  }  
		}
		
		//search for valid entries for the efficiency maps
		double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRt = TauJetMinDistanceExtended(TauTightIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRm = TauJetMinDistanceExtended(TauMediumIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRmi = TauJetMinDistanceExtended(TauMediumInclIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRl = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRli = TauJetMinDistanceExtended(TauLooseInclIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRn = TauJetMinDistanceExtended(TauNoIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		
		double Fq=JetLooseIsoObjectSelectionCollection.jet[j]->chargedEmEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->muonEnergyFraction+JetLooseIsoObjectSelectionCollection.jet[j]->chargedHadronEnergyFraction;		
		if(jetMindR > 0.5){ //only count isolated jets
		  if( deltaRt.first < 0.1  ){
		    ChargeMapT_num->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    if(CulpritCode == 1) 	ChargeMapT_num_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 4)	ChargeMapT_num_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 5)	ChargeMapT_num_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 21)	ChargeMapT_num_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 0) 	ChargeMapT_num_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		  }  
		  if( deltaRm.first < 0.1  ){
		    ChargeMapM_num->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    if(CulpritCode == 1) 	ChargeMapM_num_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 4)	ChargeMapM_num_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 5)	ChargeMapM_num_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 21)	ChargeMapM_num_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 0) 	ChargeMapM_num_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		  }  
		  if( deltaRmi.first < 0.1 ) ChargeMapMi_num->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		  if( deltaRl.first < 0.1  ){
		    ChargeMapL_num->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    if(CulpritCode == 1) 	ChargeMapL_num_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 4)	ChargeMapL_num_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 5)	ChargeMapL_num_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 21)	ChargeMapL_num_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 0) 	ChargeMapL_num_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		  } 
		  if( deltaRli.first < 0.1 ) ChargeMapLi_num->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		  if( deltaRn.first < 0.1  ){
		    ChargeMapN_num->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    if(CulpritCode == 1) 	ChargeMapN_num_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 4)	ChargeMapN_num_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 5)	ChargeMapN_num_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 21)	ChargeMapN_num_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		    else if(CulpritCode == 0) 	ChargeMapN_num_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		  } 
		  if(fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta)<2.1) //only count jets in acceptance in denominator
		    {
		      ChargeMapN_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      ChargeMapL_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      ChargeMapLi_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      ChargeMapM_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      ChargeMapMi_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      ChargeMapT_den->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      if(CulpritCode == 1){
		        ChargeMapT_den_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapM_den_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapL_den_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapN_den_Uds->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      }
		      else if(CulpritCode == 4){
		        ChargeMapT_den_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapM_den_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapL_den_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapN_den_C->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      }
		      else if(CulpritCode == 5){
		        ChargeMapT_den_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapM_den_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapL_den_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapN_den_B->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      }
		      else if(CulpritCode == 21){
		        ChargeMapT_den_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapM_den_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapL_den_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapN_den_G->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      }
		      else if(CulpritCode == 0){
		        ChargeMapT_den_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapM_den_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapL_den_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
			ChargeMapN_den_Un->Fill(Fq, JetLooseIsoObjectSelectionCollection.jet[j]->pt);
		      }
		    }
		}
	}
	
	//Clearing Object Collections 
	TauTightIsoObjectSelectionCollection.clear();
	TauMediumIsoObjectSelectionCollection.clear();
	TauMediumInclIsoObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();
	TauLooseInclIsoObjectSelectionCollection.clear();
	TauNoIsoObjectSelectionCollection.clear();
	JetLooseIsoObjectSelectionCollection.clear();
	}

  stream.close();
  ofile.close();
  return 0;
}

