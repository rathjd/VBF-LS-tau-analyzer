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
#include "FakeTau.h"
#include "selection.h"

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


  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------

	TH1::SetDefaultSumw2();
	TFile file_eff("/afs/naf.desy.de/user/m/marconi/public/VBFAnalyzer/effmap.root", "read");
	
	MyHistoCollection myHistoColl_SignalRegion(ofile.file_, "SignalRegion");	
	MyHistoCollection myHistoColl_CR1 (ofile.file_, "Ztautau_CR1"); 
	MyHistoCollection myHistoColl_CR2 (ofile.file_, "Central_invertedVBF_CR2");	
	MyHistoCollection myHistoColl_CR4 (ofile.file_, "Central_invertedVBF_TauLooseIso_CR4");
        MyHistoCollection myHistoColl_CR5 (ofile.file_, "Central_TauLooseIso_CR5");
	
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
	    TauLooseIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	  }

	  // muon selection
	  for(unsigned int m =0;m<muon.size();++m){
	    if(!(       fabs(muon[m].eta) < 2.4                                        	)) continue;
	    if(!(       muon[m].pt > 20                                                	)) continue;
	    if(!(       muon[m].isGlobalMuon                                           	)) continue;
	    if(!(       muon[m].isTrackerMuon                                          	)) continue;
	    if(!(       muon[m].isPFMuon                                               	)) continue;
	    if(!(       muon[m].numberOfMatchedStations > 1                            	)) continue;
	    if(!((       fabs(muon[m].muonBestTrack_dxy) < 0.2           ))  &&
                 (       fabs(muon[m]. muonBestTrack_dz) < 0.5                         	)) continue;
	    if(!(       muon[m].globalTrack_normalizedChi2 < 10.                       	)) continue;
	    if(!(       muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0       	)) continue;
	    if(!(       muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0       	)) continue;
	    if(!(       muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5   	)) continue;
	    if(!(       muon[m].innerTrack_normalizedChi2 < 1.8                        	)) continue;
	    if(!(       fabs(muon[m].innerTrack_dxy) < 3.                              	)) continue;
	    if(!(       fabs(muon[m].innerTrack_dz) < 30.                              	)) continue;
	    mainObjectSelectionCollection.muon.push_back(&muon[m]);
	    TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	  }

          // tau main selection
          for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                                     	)) continue;
            if(!(       tau[t].pt >= 45.                                            	)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      	)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA3 > 0.5                	)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        	)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)  )) continue;
	    if(       	tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits > 0.5   ) TauTightObjectSelectionCollection.tau.push_back(&tau[t]);
          }

          // jet baseline selection
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 15.                                                 )) continue;
	    if(!(      fabs(jet[j].eta) <= 2.5                                          )) continue;
	    JetLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	  }


	// --------------------------
	// -- QCD Event Weighting  --
	// --------------------------
	
	TH2F* h2_taufakerate_eff = (TH2F*)(file_eff.Get("h2_taufakerate_eff"));
	vector<double> jet_taufakerate;

	for(unsigned int i = 0;i<JetLooseIsoObjectSelectionCollection.jet.size();++i){
		int nbin = h2_taufakerate_eff->FindBin(JetLooseIsoObjectSelectionCollection.jet[i]->pt,JetLooseIsoObjectSelectionCollection.jet[i]->eta);
		jet_taufakerate.push_back(h2_taufakerate_eff->GetBinContent(nbin));
	}
	
	Fake FakeTaus("FakeTaus");
	FakeTaus.generate(jet_taufakerate);

	tau_s faketau1;
	tau_s faketau2;

	if ( FakeTaus.index.first >= 0 && FakeTaus.index.second >= 0 ) {

		if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->charge > 0 )
		faketau1.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->charge < 0 )
		faketau1.charge = -1;
		faketau1.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->p;
		faketau1.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->energy;
		faketau1.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->et;
		faketau1.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->px;
		faketau1.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->py;
		faketau1.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pz;
		faketau1.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->pt;
		faketau1.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->phi;
		faketau1.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.first]->eta;
		
		if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->charge > 0 )
		faketau2.charge = +1;
		else if(JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->charge < 0 ) 
		faketau2.charge = -1;		
		faketau2.p = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->p;
		faketau2.energy = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->energy;
		faketau2.et = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->et;
		faketau2.px = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->px;
		faketau2.py = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->py;
		faketau2.pz = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->pz;
		faketau2.pt = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->pt;
		faketau2.phi = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->phi;
		faketau2.eta = JetLooseIsoObjectSelectionCollection.jet[FakeTaus.index.second]->eta;

		mainObjectSelectionCollection.tau.push_back(&faketau1);
		mainObjectSelectionCollection.tau.push_back(&faketau2);

		TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau1);
		TauLooseIsoObjectSelectionCollection.tau.push_back(&faketau2);
	}
	
	
	  // jet && bjet selection
	  // ? id ?
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                	)) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 5.0                                          )) continue;
	    double mainDistance = TauJetMinDistance(mainObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double looseDistance = TauJetMinDistance(TauLooseIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
            bool jetid=true;
	    if(!(      (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99      )) jetid=false;
	    if(!(      jet[j].neutralEmEnergyFraction < 0.99                                            )) jetid=false;
	    if(!(      jet[j].numberOfDaughters > 1                                                     )) jetid=false;
	    if(fabs(jet[j].eta) < 2.4) {
              if(!(      jet[j].chargedHadronEnergyFraction > 0                        			)) jetid=false;
              if(!(      jet[j].chargedEmEnergyFraction < 0.99                            		)) jetid=false;
              if(!(      jet[j].chargedHadronMultiplicity > 0                             		)) jetid=false;
            }
            if(      jet[j].pt >= 50.  && jetid		){
	      if(	mainDistance >= 0.3	) mainObjectSelectionCollection.jet.push_back(&jet[j]);
	      if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
            }
            if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244    ){
              if(	mainDistance >= 0.3	) mainObjectSelectionCollection.bjet.push_back(&jet[j]);
	      if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
            }
	  }

	  //MET selection
	  mainObjectSelectionCollection.met.push_back(&met[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met[0]);

	  //Event Count
	  ofile.count("NoCuts");

	// ---------------------
	// -- Signal Region   --
	// ---------------------

	Selection Signal("Signal"); 						//label and initialisation
	Signal.InputCollection 		= &mainObjectSelectionCollection;	//input collection
	Signal.OutputCollection 	= &myHistoColl_SignalRegion;		//output collection
	Signal.RealData			= eventhelper_isRealData;		//pass information if event is real data
	Signal.RunData			= false;				//real data allowed
	Signal.NumberTauMin		= 2;					//require at least N tau
	Signal.NumberTauMax		= -1;					//require at most N taus
	Signal.DiTauDeltaRmin		= 0.3;					//minimum delta R for tau pair
	Signal.DiTauInvMassMin		= -1;					//minimum Di-tau-mass requirement
	Signal.DiTauInvMassMax		= -1;					//maximum Di-tau-mass requirement
	Signal.DiTauSign		= +1;					//1 for LS and -1 for OS, 0 for no requirement
	Signal.Btag			= 0;					//number of btags required (exact -> 0 = none)
	Signal.JetEtaMax		= 5.;					//maximum eta for jets, set to -1 for no requirement
	Signal.LeadJetPtMin		= 75.;					//minimum pt of lead jet, set to -1 for no requirement
	Signal.LeadJetPtMax		= -1.;					//maximum pt of lead jet, set to -1 for no requirement
	Signal.SubLeadJetPtMin		= 50.;					//minimum pt of sub lead jet, set to -1 for no requirement
	Signal.SubLeadJetPtMax		= -1.;					//maximum pt of sub lead jet, set to -1 for no requirement
	Signal.DiJetDrMin		= 0.3;					//Dijet minimum delta R, set to -1 for no requirement
	Signal.DiJetDrMax		= -1;					//Dijet maximum delta R, set to -1 for no requirement
	Signal.DiJetInvMassMin		= 700.;					//Dijet minimal invariant mass, set to -1 for no requirement
	Signal.DiJetInvMassMax		= -1.;					//Dijet maximum invariant mass, set to -1 for no requirement
	Signal.DiJetSignEta		= -1;					//Dijet sign eta_1*eta_2
	Signal.DiJetDetaMin		= 4.2;					//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
	Signal.DiJetDetaMax		= -1;					//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
	Signal.weight			= weight;				//event weight
	Signal.invertTauRequirements	= false;				//invert number of taus requirement
	Signal.invertTauProperties	= false;				//invert ditau properties (dR, sign)
	Signal.invertBtagRequirement	= false;				//invert number of b-jets required
	Signal.invertJetRequirements	= false;				//invert jet pt requirements
	Signal.invertDijetProperties	= false;				//invert dijet system properties (dR, inv mass, sign eta, dEta)
		
	Signal.select();							//do selection, fill histograms

	// ---------------------------------
	// -- CENTRAL + INVERTED VBF CR   --
	// ---------------------------------	
	
	Selection InvertedVBF_CR2("InvertedVBF_CR2"); 					//label and initialisation
	InvertedVBF_CR2.InputCollection 	= &mainObjectSelectionCollection;	//input collection
	InvertedVBF_CR2.OutputCollection 	= &myHistoColl_CR2;			//output collection
	InvertedVBF_CR2.RealData		= eventhelper_isRealData;		//pass information if event is real data
	InvertedVBF_CR2.RunData			= true;					//real data allowed
	InvertedVBF_CR2.NumberTauMin		= 2;					//require at least N tau
	InvertedVBF_CR2.NumberTauMax		= -1;					//require at most N taus
	InvertedVBF_CR2.DiTauDeltaRmin		= 0.3;					//minimum delta R for tau pair
	InvertedVBF_CR2.DiTauInvMassMin		= -1;					//minimum Di-tau-mass requirement
	InvertedVBF_CR2.DiTauInvMassMax		= -1;					//maximum Di-tau-mass requirement
	InvertedVBF_CR2.DiTauSign		= +1;					//1 for LS and -1 for OS, 0 for no requirement
	InvertedVBF_CR2.Btag			= 0;					//number of btags required (exact -> 0 = none)
	InvertedVBF_CR2.JetEtaMax		= 5.;					//maximum eta for jets, set to -1 for no requirement
	InvertedVBF_CR2.LeadJetPtMin		= 75.;					//minimum pt of lead jet, set to -1 for no requirement
	InvertedVBF_CR2.LeadJetPtMax		= -1.;					//maximum pt of lead jet, set to -1 for no requirement
	InvertedVBF_CR2.SubLeadJetPtMin		= 50.;					//minimum pt of sub lead jet, set to -1 for no requirement
	InvertedVBF_CR2.SubLeadJetPtMax		= -1.;					//maximum pt of sub lead jet, set to -1 for no requirement
	InvertedVBF_CR2.DiJetDrMin		= 0.3;					//Dijet minimum delta R, set to -1 for no requirement
	InvertedVBF_CR2.DiJetDrMax		= -1.;					//Dijet maximum delta R, set to -1 for no requirement
	InvertedVBF_CR2.DiJetInvMassMin		= 700.;					//Dijet minimal invariant mass, set to -1 for no requirement
	InvertedVBF_CR2.DiJetInvMassMax		= -1.;					//Dijet maximum invariant mass, set to -1 for no requirement
	InvertedVBF_CR2.DiJetSignEta		= -1;					//Dijet sign eta_1*eta_2
	InvertedVBF_CR2.DiJetDetaMin		= 4.2;					//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
	InvertedVBF_CR2.DiJetDetaMax		= -1.;					//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement	
	InvertedVBF_CR2.weight			= weight;				//event weight
	InvertedVBF_CR2.invertTauRequirements	= false;				//invert number of taus requirement
	InvertedVBF_CR2.invertTauProperties	= false;				//invert ditau properties (dR, sign)
	InvertedVBF_CR2.invertBtagRequirement	= false;				//invert number of b-jets required
	InvertedVBF_CR2.invertJetRequirements	= true;					//invert jet pt requirements
	InvertedVBF_CR2.invertDijetProperties	= true;					//invert dijet system properties (dR, inv mass, sign eta, dEta)
		
	InvertedVBF_CR2.select();							//do selection, fill histograms			

	// ------------------------------------------------------
	// -- CENTRAL + INVERTED VBF CR (with Tau Loose Iso)  --
	// ------------------------------------------------------

	Selection InvertedVBF_CR4("InvertedVBF_CR4"); 						//label and initialisation
	InvertedVBF_CR4.InputCollection 	= &TauLooseIsoObjectSelectionCollection;	//input collection
	InvertedVBF_CR4.OutputCollection 	= &myHistoColl_CR4;				//output collection
	InvertedVBF_CR4.RealData		= eventhelper_isRealData;			//pass information if event is real data
	InvertedVBF_CR4.RunData			= true;						//real data allowed
	InvertedVBF_CR4.NumberTauMin		= 2;						//require at least N tau
	InvertedVBF_CR4.NumberTauMax		= -1;						//require at most N taus
	InvertedVBF_CR4.DiTauDeltaRmin		= 0.3;						//minimum delta R for tau pair
	InvertedVBF_CR4.DiTauInvMassMin		= -1;						//minimum Di-tau-mass requirement
	InvertedVBF_CR4.DiTauInvMassMax		= -1;						//maximum Di-tau-mass requirement	
	InvertedVBF_CR4.DiTauSign		= +1;						//1 for LS and -1 for OS, 0 for no requirement
	InvertedVBF_CR4.Btag			= 0;						//number of btags required (exact -> 0 = none)
	InvertedVBF_CR4.JetEtaMax		= 5.;						//maximum eta for jets, set to -1 for no requirement
	InvertedVBF_CR4.LeadJetPtMin		= 75.;						//minimum pt of lead jet, set to -1 for no requirement
	InvertedVBF_CR4.LeadJetPtMax		= -1.;						//maximum pt of lead jet, set to -1 for no requirement
	InvertedVBF_CR4.SubLeadJetPtMin		= 50.;						//minimum pt of sub lead jet, set to -1 for no requirement
	InvertedVBF_CR4.SubLeadJetPtMax		= -1.;						//maximum pt of sub lead jet, set to -1 for no requirement
	InvertedVBF_CR4.DiJetDrMin		= 0.3;						//Dijet minimum delta R, set to -1 for no requirement
	InvertedVBF_CR4.DiJetDrMax		= -1.;						//Dijet maximum delta R, set to -1 for no requirement
	InvertedVBF_CR4.DiJetInvMassMin		= 700.;						//Dijet minimal invariant mass, set to -1 for no requirement
	InvertedVBF_CR4.DiJetInvMassMax		= -1.;						//Dijet maximum invariant mass, set to -1 for no requirement
	InvertedVBF_CR4.DiJetSignEta		= -1;						//Dijet sign eta_1*eta_2
	InvertedVBF_CR4.DiJetDetaMin		= 4.2;						//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
	InvertedVBF_CR4.DiJetDetaMax		= -1.;						//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement	
	InvertedVBF_CR4.weight			= weight;					//event weight
	InvertedVBF_CR4.invertTauRequirements	= false;					//invert number of taus requirement
	InvertedVBF_CR4.invertTauProperties	= false;					//invert ditau properties (dR, sign)
	InvertedVBF_CR4.invertBtagRequirement	= false;					//invert number of b-jets required
	InvertedVBF_CR4.invertJetRequirements	= true;						//invert jet pt requirements
	InvertedVBF_CR4.invertDijetProperties	= true;						//invert dijet system properties (dR, inv mass, sign eta, dEta)
		
	InvertedVBF_CR4.select();								//do selection, fill histograms			

	// ---------------------
	// -- Z -> TauTau CR  --
	// ---------------------

	Selection Ztautau_CR1("Ztautau_CR1"); 						//label and initialisation
	Ztautau_CR1.InputCollection 		= &mainObjectSelectionCollection;	//input collection
	Ztautau_CR1.OutputCollection 		= &myHistoColl_CR1;			//output collection
	Ztautau_CR1.RealData			= eventhelper_isRealData;		//pass information if event is real data
	Ztautau_CR1.RunData			= true;					//real data allowed
	Ztautau_CR1.NumberTauMin		= 2;					//require at least N tau
	Ztautau_CR1.NumberTauMax		= -1;					//require at most N taus
	Ztautau_CR1.DiTauDeltaRmin		= 0.3;					//minimum delta R for tau pair
	Ztautau_CR1.DiTauInvMassMin		= -1.;					//minimum Di-tau-mass requirement
	Ztautau_CR1.DiTauInvMassMax		= 90.;					//maximum Di-tau-mass requirement	
	Ztautau_CR1.DiTauSign			= -1;					//1 for LS and -1 for OS, 0 for no requirement
	Ztautau_CR1.Btag			= 0;					//number of btags required (exact -> 0 = none)
	Ztautau_CR1.JetEtaMax			= -1.;					//maximum eta for jets, set to -1 for no requirement
	Ztautau_CR1.LeadJetPtMin		= -1.;					//minimum pt of lead jet, set to -1 for no requirement
	Ztautau_CR1.LeadJetPtMax		= -1.;					//maximum pt of lead jet, set to -1 for no requirement
	Ztautau_CR1.SubLeadJetPtMin		= -1.;					//minimum pt of sub lead jet, set to -1 for no requirement
	Ztautau_CR1.SubLeadJetPtMax		= -1.;					//maximum pt of sub lead jet, set to -1 for no requirement
	Ztautau_CR1.DiJetDrMin			= -1.;					//Dijet minimum delta R, set to -1 for no requirement
	Ztautau_CR1.DiJetDrMax			= -1.;					//Dijet maximum delta R, set to -1 for no requirement
	Ztautau_CR1.DiJetInvMassMin		= -1.;					//Dijet minimal invariant mass, set to -1 for no requirement
	Ztautau_CR1.DiJetInvMassMax		= -1.;					//Dijet maximum invariant mass, set to -1 for no requirement
	Ztautau_CR1.DiJetSignEta		= 0;					//Dijet sign eta_1*eta_2
	Ztautau_CR1.DiJetDetaMin		= -1.;					//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
	Ztautau_CR1.DiJetDetaMax		= -1.;					//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement	
	Ztautau_CR1.weight			= weight;				//event weight
	Ztautau_CR1.invertTauRequirements	= false;				//invert number of taus requirement
	Ztautau_CR1.invertTauProperties		= false;				//invert ditau properties (dR, sign)
	Ztautau_CR1.invertBtagRequirement	= false;				//invert number of b-jets required
	Ztautau_CR1.invertJetRequirements	= false;				//invert jet pt requirements
	Ztautau_CR1.invertDijetProperties	= false;				//invert dijet system properties (dR, inv mass, sign eta, dEta)
		
	Ztautau_CR1.select();								//do selection, fill histograms			
	
	// ---------------------
	// -- Central Loose Region   --
	// ---------------------

	Selection Central_TauLooseIso_CR5("Central_TauLooseIso_CR5"); 					//label and initialisation
	Central_TauLooseIso_CR5.InputCollection 	= &TauLooseIsoObjectSelectionCollection;	//input collection
	Central_TauLooseIso_CR5.OutputCollection 	= &myHistoColl_CR5;				//output collection
	Central_TauLooseIso_CR5.RealData		= eventhelper_isRealData;			//pass information if event is real data
	Central_TauLooseIso_CR5.RunData			= true;						//real data allowed
	Central_TauLooseIso_CR5.NumberTauMin		= 2;						//require at least N tau
	Central_TauLooseIso_CR5.NumberTauMax		= -1;						//require at most N taus
	Central_TauLooseIso_CR5.DiTauDeltaRmin		= 0.3;						//minimum delta R for tau pair
	Central_TauLooseIso_CR5.DiTauInvMassMin		= -1;						//minimum Di-tau-mass requirement
	Central_TauLooseIso_CR5.DiTauInvMassMax		= -1;						//maximum Di-tau-mass requirement
	Central_TauLooseIso_CR5.DiTauSign		= +1;						//1 for LS and -1 for OS, 0 for no requirement
	Central_TauLooseIso_CR5.Btag			= 0;						//number of btags required (exact -> 0 = none)
	Central_TauLooseIso_CR5.JetEtaMax		= 5.;						//maximum eta for jets, set to -1 for no requirement
	Central_TauLooseIso_CR5.LeadJetPtMin		= 75.;						//minimum pt of lead jet, set to -1 for no requirement
	Central_TauLooseIso_CR5.LeadJetPtMax		= -1.;						//maximum pt of lead jet, set to -1 for no requirement
	Central_TauLooseIso_CR5.SubLeadJetPtMin		= 50.;						//minimum pt of sub lead jet, set to -1 for no requirement
	Central_TauLooseIso_CR5.SubLeadJetPtMax		= -1.;						//maximum pt of sub lead jet, set to -1 for no requirement
	Central_TauLooseIso_CR5.DiJetDrMin		= 0.3;						//Dijet minimum delta R, set to -1 for no requirement
	Central_TauLooseIso_CR5.DiJetDrMax		= -1;						//Dijet maximum delta R, set to -1 for no requirement
	Central_TauLooseIso_CR5.DiJetInvMassMin		= 700.;						//Dijet minimal invariant mass, set to -1 for no requirement
	Central_TauLooseIso_CR5.DiJetInvMassMax		= -1.;						//Dijet maximum invariant mass, set to -1 for no requirement
	Central_TauLooseIso_CR5.DiJetSignEta		= -1;						//Dijet sign eta_1*eta_2
	Central_TauLooseIso_CR5.DiJetDetaMin		= 4.2;						//Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
	Central_TauLooseIso_CR5.DiJetDetaMax		= -1;						//Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
	Central_TauLooseIso_CR5.weight			= weight;					//event weight
	Central_TauLooseIso_CR5.invertTauRequirements	= false;					//invert number of taus requirement
	Central_TauLooseIso_CR5.invertTauProperties	= false;					//invert ditau properties (dR, sign)
	Central_TauLooseIso_CR5.invertBtagRequirement	= false;					//invert number of b-jets required
	Central_TauLooseIso_CR5.invertJetRequirements	= false;					//invert jet pt requirements
	Central_TauLooseIso_CR5.invertDijetProperties	= false;					//invert dijet system properties (dR, inv mass, sign eta, dEta)
		
	Central_TauLooseIso_CR5.select();	


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

