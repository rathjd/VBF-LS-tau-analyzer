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
#include "TProfile.h"
#include "TString.h"

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

  //TH1F* h_mindeltaR = new TH1F("h_mindeltaR", "h_mindeltaR", 50,0. , 3.);

  double ptedges[21]={22.5,23.7,25.,26.5,28.1,30.,32.1,34.6,37.5,40.9,45.,50.,56.3,64.3,75.,90.,112.5,150.,225.,450.,2500.};
  double AbsEtaEdges[7]={0.,0.7,1,1.3,1.6,1.8,2.1};

  TProfile *RescaleWeightN=new TProfile("RescaleWeightN", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightN->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightN->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightN->Sumw2();
  TProfile *RescaleWeightL=new TProfile("RescaleWeightL", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightL->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightL->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightL->Sumw2();  
  TProfile *RescaleWeightLi=new TProfile("RescaleWeightLi", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightLi->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightLi->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightLi->Sumw2();
  TProfile *RescaleWeightM=new TProfile("RescaleWeightM", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightM->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightM->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightM->Sumw2();
  TProfile *RescaleWeightMi=new TProfile("RescaleWeightMi", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightMi->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightMi->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightMi->Sumw2();
  TProfile *RescaleWeightT=new TProfile("RescaleWeightT", "probability to pass p_{T}^{#tau}#geq 45", 20,ptedges);
  RescaleWeightT->GetXaxis()->SetTitle("p_{T}^{jet}");
  RescaleWeightT->GetYaxis()->SetTitle("P(p_{T}^{#tau}#geq 45)");
  RescaleWeightT->Sumw2();
  
  TProfile* RescaleWeightN_Uds = (TProfile*) RescaleWeightN->Clone("RescaleWeightN_Uds");
  TProfile* RescaleWeightN_C   = (TProfile*) RescaleWeightN->Clone("RescaleWeightN_C");
  TProfile* RescaleWeightN_B   = (TProfile*) RescaleWeightN->Clone("RescaleWeightN_B");
  TProfile* RescaleWeightN_G   = (TProfile*) RescaleWeightN->Clone("RescaleWeightN_G");
  TProfile* RescaleWeightN_Un  = (TProfile*) RescaleWeightN->Clone("RescaleWeightN_Un");
  
  TProfile* RescaleWeightL_Uds = (TProfile*) RescaleWeightL->Clone("RescaleWeightL_Uds");
  TProfile* RescaleWeightL_C   = (TProfile*) RescaleWeightL->Clone("RescaleWeightL_C");
  TProfile* RescaleWeightL_B   = (TProfile*) RescaleWeightL->Clone("RescaleWeightL_B");
  TProfile* RescaleWeightL_G   = (TProfile*) RescaleWeightL->Clone("RescaleWeightL_G");
  TProfile* RescaleWeightL_Un  = (TProfile*) RescaleWeightL->Clone("RescaleWeightL_Un");
  
  TProfile* RescaleWeightM_Uds = (TProfile*) RescaleWeightM->Clone("RescaleWeightM_Uds");
  TProfile* RescaleWeightM_C   = (TProfile*) RescaleWeightM->Clone("RescaleWeightM_C");
  TProfile* RescaleWeightM_B   = (TProfile*) RescaleWeightM->Clone("RescaleWeightM_B");
  TProfile* RescaleWeightM_G   = (TProfile*) RescaleWeightM->Clone("RescaleWeightM_G");
  TProfile* RescaleWeightM_Un  = (TProfile*) RescaleWeightM->Clone("RescaleWeightM_Un");
  
  TProfile* RescaleWeightT_Uds = (TProfile*) RescaleWeightT->Clone("RescaleWeightT_Uds");
  TProfile* RescaleWeightT_C   = (TProfile*) RescaleWeightT->Clone("RescaleWeightT_C");
  TProfile* RescaleWeightT_B   = (TProfile*) RescaleWeightT->Clone("RescaleWeightT_B");
  TProfile* RescaleWeightT_G   = (TProfile*) RescaleWeightT->Clone("RescaleWeightT_G");
  TProfile* RescaleWeightT_Un  = (TProfile*) RescaleWeightT->Clone("RescaleWeightT_Un");
  
  TProfile *ScaleFactorN=new TProfile("ScaleFactorN", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorN->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorN->GetYaxis()->SetTitle("p_{T}^{jet}#rightarrow p_{T}^{#tau}");
  ScaleFactorN->Sumw2();
  TProfile *ScaleFactorL=new TProfile("ScaleFactorL", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorL->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorL->GetYaxis()->SetTitle("p_{T}^{jet}#rightarrow p_{T}^{#tau}");
  ScaleFactorL->Sumw2();  
  TProfile *ScaleFactorLi=new TProfile("ScaleFactorLi", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorLi->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorLi->GetYaxis()->SetTitle("p_{T}^{jet}#rightarrow p_{T}^{#tau}");
  ScaleFactorLi->Sumw2();
  TProfile *ScaleFactorM=new TProfile("ScaleFactorM", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorM->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorM->GetYaxis()->SetTitle("p_{T}^{jet}#rightarrow p_{T}^{#tau}");
  ScaleFactorM->Sumw2();
  TProfile *ScaleFactorMi=new TProfile("ScaleFactorMi", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorMi->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorMi->GetYaxis()->SetTitle("p_{T}^{jet}#rightarrow p_{T}^{#tau}");
  ScaleFactorMi->Sumw2();
  TProfile *ScaleFactorT=new TProfile("ScaleFactorT", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorT->GetXaxis()->SetTitle("p_{T}^{jet}");
  ScaleFactorT->GetYaxis()->SetTitle("p_{T}^{jet}#rightarrow p_{T}^{#tau}");
  ScaleFactorT->Sumw2(); 
  
  TProfile* ScaleFactorN_Uds = (TProfile*) ScaleFactorN->Clone("ScaleFactorN_Uds");
  TProfile* ScaleFactorN_C   = (TProfile*) ScaleFactorN->Clone("ScaleFactorN_C");
  TProfile* ScaleFactorN_B   = (TProfile*) ScaleFactorN->Clone("ScaleFactorN_B");
  TProfile* ScaleFactorN_G   = (TProfile*) ScaleFactorN->Clone("ScaleFactorN_G");
  TProfile* ScaleFactorN_Un  = (TProfile*) ScaleFactorN->Clone("ScaleFactorN_Un");
  
  TProfile* ScaleFactorL_Uds = (TProfile*) ScaleFactorL->Clone("ScaleFactorL_Uds");
  TProfile* ScaleFactorL_C   = (TProfile*) ScaleFactorL->Clone("ScaleFactorL_C");
  TProfile* ScaleFactorL_B   = (TProfile*) ScaleFactorL->Clone("ScaleFactorL_B");
  TProfile* ScaleFactorL_G   = (TProfile*) ScaleFactorL->Clone("ScaleFactorL_G");
  TProfile* ScaleFactorL_Un  = (TProfile*) ScaleFactorL->Clone("ScaleFactorL_Un");
  
  TProfile* ScaleFactorM_Uds = (TProfile*) ScaleFactorM->Clone("ScaleFactorM_Uds");
  TProfile* ScaleFactorM_C   = (TProfile*) ScaleFactorM->Clone("ScaleFactorM_C");
  TProfile* ScaleFactorM_B   = (TProfile*) ScaleFactorM->Clone("ScaleFactorM_B");
  TProfile* ScaleFactorM_G   = (TProfile*) ScaleFactorM->Clone("ScaleFactorM_G");
  TProfile* ScaleFactorM_Un  = (TProfile*) ScaleFactorM->Clone("ScaleFactorM_Un");
  
  TProfile* ScaleFactorT_Uds = (TProfile*) ScaleFactorT->Clone("ScaleFactorT_Uds");
  TProfile* ScaleFactorT_C   = (TProfile*) ScaleFactorT->Clone("ScaleFactorT_C");
  TProfile* ScaleFactorT_B   = (TProfile*) ScaleFactorT->Clone("ScaleFactorT_B");
  TProfile* ScaleFactorT_G   = (TProfile*) ScaleFactorT->Clone("ScaleFactorT_G");
  TProfile* ScaleFactorT_Un  = (TProfile*) ScaleFactorT->Clone("ScaleFactorT_Un");
   
  TProfile *ScaleFactorEnergyN=new TProfile("ScaleFactorEnergyN", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorEnergyN->GetXaxis()->SetTitle("E^{jet}");
  ScaleFactorEnergyN->GetYaxis()->SetTitle("E^{jet}#rightarrow E^{#tau}");
  ScaleFactorEnergyN->Sumw2();
  TProfile *ScaleFactorEnergyL=new TProfile("ScaleFactorEnergyL", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorEnergyL->GetXaxis()->SetTitle("E^{jet}");
  ScaleFactorEnergyL->GetYaxis()->SetTitle("E^{jet}#rightarrow E^{#tau}");
  ScaleFactorEnergyL->Sumw2();  
  TProfile *ScaleFactorEnergyLi=new TProfile("ScaleFactorEnergyLi", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorEnergyLi->GetXaxis()->SetTitle("E^{jet}");
  ScaleFactorEnergyLi->GetYaxis()->SetTitle("E^{jet}#rightarrow E^{#tau}");
  ScaleFactorEnergyLi->Sumw2();
  TProfile *ScaleFactorEnergyM=new TProfile("ScaleFactorEnergyM", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorEnergyM->GetXaxis()->SetTitle("E^{jet}");
  ScaleFactorEnergyM->GetYaxis()->SetTitle("E^{jet}#rightarrow E^{#tau}");
  ScaleFactorEnergyM->Sumw2();
  TProfile *ScaleFactorEnergyMi=new TProfile("ScaleFactorEnergyMi", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorEnergyMi->GetXaxis()->SetTitle("E^{jet}");
  ScaleFactorEnergyMi->GetYaxis()->SetTitle("E^{jet}#rightarrow E^{#tau}");
  ScaleFactorEnergyMi->Sumw2();
  TProfile *ScaleFactorEnergyT=new TProfile("ScaleFactorEnergyT", "p_{T}^{jet}#rightarrow p_{T}^{#tau}", 20,ptedges);
  ScaleFactorEnergyT->GetXaxis()->SetTitle("E^{jet}");
  ScaleFactorEnergyT->GetYaxis()->SetTitle("E^{jet}#rightarrow E^{#tau}");
  ScaleFactorEnergyT->Sumw2();    
  
  TProfile* ScaleFactorEnergyN_Uds = (TProfile*) ScaleFactorEnergyN->Clone(TString::Format("ScaleFactorEnergyN_Uds"));
  TProfile* ScaleFactorEnergyN_C   = (TProfile*) ScaleFactorEnergyN->Clone(TString::Format("ScaleFactorEnergyN_C"));
  TProfile* ScaleFactorEnergyN_B   = (TProfile*) ScaleFactorEnergyN->Clone(TString::Format("ScaleFactorEnergyN_B"));
  TProfile* ScaleFactorEnergyN_G   = (TProfile*) ScaleFactorEnergyN->Clone(TString::Format("ScaleFactorEnergyN_G"));
  TProfile* ScaleFactorEnergyN_Un  = (TProfile*) ScaleFactorEnergyN->Clone(TString::Format("ScaleFactorEnergyN_Un"));

  TProfile* ScaleFactorEnergyL_Uds = (TProfile*) ScaleFactorEnergyL->Clone(TString::Format("ScaleFactorEnergyL_Uds"));
  TProfile* ScaleFactorEnergyL_C   = (TProfile*) ScaleFactorEnergyL->Clone(TString::Format("ScaleFactorEnergyL_C"));
  TProfile* ScaleFactorEnergyL_B   = (TProfile*) ScaleFactorEnergyL->Clone(TString::Format("ScaleFactorEnergyL_B"));
  TProfile* ScaleFactorEnergyL_G   = (TProfile*) ScaleFactorEnergyL->Clone(TString::Format("ScaleFactorEnergyL_G"));
  TProfile* ScaleFactorEnergyL_Un  = (TProfile*) ScaleFactorEnergyL->Clone(TString::Format("ScaleFactorEnergyL_Un"));
  
  TProfile* ScaleFactorEnergyM_Uds = (TProfile*) ScaleFactorEnergyM->Clone(TString::Format("ScaleFactorEnergyM_Uds"));
  TProfile* ScaleFactorEnergyM_C   = (TProfile*) ScaleFactorEnergyM->Clone(TString::Format("ScaleFactorEnergyM_C"));
  TProfile* ScaleFactorEnergyM_B   = (TProfile*) ScaleFactorEnergyM->Clone(TString::Format("ScaleFactorEnergyM_B"));
  TProfile* ScaleFactorEnergyM_G   = (TProfile*) ScaleFactorEnergyM->Clone(TString::Format("ScaleFactorEnergyM_G"));
  TProfile* ScaleFactorEnergyM_Un  = (TProfile*) ScaleFactorEnergyM->Clone(TString::Format("ScaleFactorEnergyM_Un"));
  
  TProfile* ScaleFactorEnergyT_Uds = (TProfile*) ScaleFactorEnergyT->Clone(TString::Format("ScaleFactorEnergyT_Uds"));
  TProfile* ScaleFactorEnergyT_C   = (TProfile*) ScaleFactorEnergyT->Clone(TString::Format("ScaleFactorEnergyT_C"));
  TProfile* ScaleFactorEnergyT_B   = (TProfile*) ScaleFactorEnergyT->Clone(TString::Format("ScaleFactorEnergyT_B"));
  TProfile* ScaleFactorEnergyT_G   = (TProfile*) ScaleFactorEnergyT->Clone(TString::Format("ScaleFactorEnergyT_G")); 
  TProfile* ScaleFactorEnergyT_Un  = (TProfile*) ScaleFactorEnergyT->Clone(TString::Format("ScaleFactorEnergyT_Un")); 
  
  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------
  
  TFile file_PUdata("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/DataPUFile_22Jan2013ReReco_Run2012.root", "read");
  TFile file_PUmc("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/S10MC_PUFile.root", "read");
	
  TH1F *PUweights = (TH1F*)file_PUdata.Get("analyzeHiMassTau/NVertices_0");
  PUweights->Scale(1/PUweights->Integral());
  TH1F *PUmc = (TH1F*)file_PUmc.Get("analyzeHiMassTau/NVertices_0");
  PUmc->Scale(1/PUmc->Integral());
	
  PUweights->Divide(PUmc);
	
  double weight = 1.;
  
  MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
  MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
  MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
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

	//PU weights
	if(!eventhelper_isRealData){
 	  weight=PUweights->GetBinContent(PUweights->FindBin(PileupSummaryInfo_getTrueNumInteractions[0]));
 	  //std::cout<<"NVtx="<<PileupSummaryInfo_getTrueNumInteractions[0]<<", weight="<<weight<<std::endl;
	} 

          // vertex selection
	  bool goodVertex = true;

          if(!(         vertex.size() > 0                                 )) goodVertex = false;
	  if(goodVertex){
	    if( goodVertex ) {
		TauTightIsoObjectSelectionCollection.goodVertex = true;
		TauMediumIsoObjectSelectionCollection.goodVertex = true;
		TauLooseIsoObjectSelectionCollection.goodVertex = true;
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

	  double tight =0;
	  double medium=0;
	  double loose =0;
	  double NoIso =0;

          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            //if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronMediumMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonLoose3 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFindingNewDMs > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
	    if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT  <= 0.5))  TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT  <= 0.5)) TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT  <= 0.5))  TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    else TauNoIsoObjectSelectionCollection.tau.push_back(&tau[t]);
	    //section for exclusive tau ID plot
	    if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT  <= 0.5)) tight++;
	    else if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT  <= 0.5)) medium++;
	    else if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT  <= 0.5)) loose++;
	    else NoIso++;
          }

          // jet baseline selection
	for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                                      )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.6                                                               )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	}

	//Event Count
	ofile.count("NoCuts");

	// ------------------------
	// --   Tau Efficency    --
	// ------------------------
	
	for(unsigned int j = 0;j<JetLooseIsoObjectSelectionCollection.jet.size();++j){
		//remove real tau
		double dR=5.;
	        for(unsigned int i=0; i<genTau.size(); i++){
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
		
		//systematic scale variation
		double var=0.75;
		
		double jetMindR=JetJetMinDistance(JetLooseIsoObjectSelectionCollection,JetLooseIsoObjectSelectionCollection.jet[j]->eta,JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRt = TauJetMinDistanceExtended(TauTightIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRm = TauJetMinDistanceExtended(TauMediumIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRl = TauJetMinDistanceExtended(TauLooseIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		pair <double, unsigned int>deltaRn = TauJetMinDistanceExtended(TauNoIsoObjectSelectionCollection, JetLooseIsoObjectSelectionCollection.jet[j]->eta, JetLooseIsoObjectSelectionCollection.jet[j]->phi);
		if(jetMindR > 0.5 && fabs(JetLooseIsoObjectSelectionCollection.jet[j]->eta) <=2.1){ //only count isolated jets
		  if( deltaRt.first < 0.3 ){
		    if(TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt*var>=45){
		      RescaleWeightT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      if(CulpritCode == 1){
		        RescaleWeightT_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorT_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyT_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 4){
		        RescaleWeightT_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorT_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyT_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 5){
		        RescaleWeightT_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorT_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyT_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 21){
		        RescaleWeightT_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorT_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyT_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 0){
		        RescaleWeightT_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorT_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyT_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauTightIsoObjectSelectionCollection.tau[deltaRt.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		    }
		    else{
		      RescaleWeightT->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      if(CulpritCode == 1) 	 RescaleWeightT_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 4)  RescaleWeightT_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 5)  RescaleWeightT_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 21) RescaleWeightT_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 0)  RescaleWeightT_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		    }
		  }	
		  if( deltaRm.first < 0.3 ){
		    if(TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var>=45){
		      RescaleWeightM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);		      
		      if(CulpritCode == 1){
		        RescaleWeightM_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorM_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyM_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 4){
		        RescaleWeightM_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorM_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyM_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 5){
		        RescaleWeightM_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorM_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyM_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 21){
		        RescaleWeightM_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorM_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyM_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 0){
		        RescaleWeightM_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorM_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyM_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauMediumIsoObjectSelectionCollection.tau[deltaRm.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		    }
		    else{
		      RescaleWeightM->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      if(CulpritCode == 1) 	 RescaleWeightM_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 4)  RescaleWeightM_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 5)  RescaleWeightM_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 21) RescaleWeightM_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 0)  RescaleWeightM_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight); 
		    }
		  }		  
		  if( deltaRl.first < 0.3 ){
		    if(TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var>=45){
		      RescaleWeightL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);		      
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);	
		      if(CulpritCode == 1){
		        RescaleWeightL_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorL_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyL_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 4){
		        RescaleWeightL_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorL_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyL_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 5){
		        RescaleWeightL_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorL_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyL_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 21){
		        RescaleWeightL_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorL_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyL_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }	      	
		      else if(CulpritCode == 0){
		        RescaleWeightL_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorL_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyL_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauLooseIsoObjectSelectionCollection.tau[deltaRl.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }	      
		    }
		    else{
		      RescaleWeightL->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      if(CulpritCode == 1) 	 RescaleWeightL_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 4)  RescaleWeightL_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 5)  RescaleWeightL_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 21) RescaleWeightL_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 0)  RescaleWeightL_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		    }
		  }
		  if( deltaRn.first < 0.3 ){
		    if(TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var>=45){
		      RescaleWeightN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);		      
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		      ScaleFactorLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		      ScaleFactorEnergyLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);	
		      if(CulpritCode == 1){
		        RescaleWeightN_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorN_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyN_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 4){
		        RescaleWeightN_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorN_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyN_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 5){
		        RescaleWeightN_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorN_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyN_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }
		      else if(CulpritCode == 21){
		        RescaleWeightN_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorN_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyN_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }	    
		      else if(CulpritCode == 0){
		        RescaleWeightN_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,1,weight);
		        ScaleFactorN_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->pt*var/JetLooseIsoObjectSelectionCollection.jet[j]->pt,weight);
		        ScaleFactorEnergyN_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->energy,TauNoIsoObjectSelectionCollection.tau[deltaRn.second]->energy*var/JetLooseIsoObjectSelectionCollection.jet[j]->energy,weight);
		      }  		      
		    }
		    else{
		      RescaleWeightN->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      RescaleWeightLi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      RescaleWeightMi->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      if(CulpritCode == 1) 	 RescaleWeightN_Uds->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 4)  RescaleWeightN_C->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 5)  RescaleWeightN_B->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 21) RescaleWeightN_G->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		      else if(CulpritCode == 0)  RescaleWeightN_Un->Fill(JetLooseIsoObjectSelectionCollection.jet[j]->pt,0,weight);
		    }
		  }		  
		}
	}
	
	//Clearing Object Collections 
	TauTightIsoObjectSelectionCollection.clear();
	TauMediumIsoObjectSelectionCollection.clear();
	TauLooseIsoObjectSelectionCollection.clear();
	TauNoIsoObjectSelectionCollection.clear();
	JetLooseIsoObjectSelectionCollection.clear();
	}

  stream.close();
  ofile.close();
  return 0;
}

