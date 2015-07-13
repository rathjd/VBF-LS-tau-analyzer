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
#include <random>

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
  TH1::SetDefaultSumw2();
  
  TFile file_Resp("/nfs/dust/cms/user/rathjd/VBF-LS-tau/Response/ResponseFactors_InclAndExclIsos_Jet30Lukas_MC_Tau45.root", "read");

	double weight = 1.;

	MyHistoCollection myHistoColl_Skim (ofile.file_, "Skim");
	
	MyHistoCollection myHistoColl_SR(ofile.file_, "VBF");        
	MyHistoCollection myHistoColl_CR (ofile.file_, "invertedVBF");

	MyEventCollection baselineObjectSelectionCollection ("baselineObjectSelection");
	MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
	MyEventCollection MonoTauIsoObjectSelectionCollection ("MonoTauIsoObjectSelection");

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

if(!( vertex.size() > 0 )) goodVertex = false;
if( goodVertex ) {
	baselineObjectSelectionCollection.goodVertex = true;
	TauTightIsoObjectSelectionCollection.goodVertex = true;
	MonoTauIsoObjectSelectionCollection.goodVertex = true;
}

	std::vector<int> tights;
	
          //smart tau selection
	  for(unsigned int t =0;t<tau.size();++t){
            if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
            if(!(       tau[t].pt >= 45.                                            				)) continue;
            if(!(       tau[t].leadPFChargedHadrCand_pt >= 5.0                      				)) continue;
            if(!(       tau[t].tauID_againstElectronTightMVA5 > 0.5                				)) continue;
            if(!(       tau[t].tauID_againstMuonTight2 > 0.5                        				)) continue;
            if(!(       (tau[t].tauID_decayModeFinding > 0.5) && (tau[t].signalPFChargedHadrCands_size == 1)	)) continue;
            baselineObjectSelectionCollection.tau.push_back(&tau[t]);
	    if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) TauTightIsoObjectSelectionCollection.tau.push_back(&tau[t]);
          }
	  
	  //Choose 1 tau only
	  if(TauTightIsoObjectSelectionCollection.tau.size()==1) MonoTauIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[0]);
	  else if(TauTightIsoObjectSelectionCollection.tau.size()>1){
	    std::uniform_int_distribution<int> distribution(0, TauTightIsoObjectSelectionCollection.tau.size()-1);
	    std::mt19937 engine;
	    int Toss=distribution(engine);
	    MonoTauIsoObjectSelectionCollection.tau.push_back(TauTightIsoObjectSelectionCollection.tau[Toss]);
	  }
	  
	  TH1F* h1_taufakescaleT_fac = (TH1F*)(file_Resp.Get("scaleT"));
          // jet && bjet selection before choosing jet->tau #2
	  // ? id ?
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                	)) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 5.0                                          )) continue;
	    double baseDistance = TauJetMinDistance(baselineObjectSelectionCollection, jet[j].eta, jet[j].phi);
	    double mainDistance = TauJetMinDistance(TauTightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
            bool jetid=true;
	    if(!(      (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99      )) jetid=false;
	    if(!(      jet[j].neutralEmEnergyFraction < 0.99                                            )) jetid=false;
	    if(!(      jet[j].numberOfDaughters > 1                                                     )) jetid=false;
	    if(fabs(jet[j].eta) < 2.4) {
              if(!(      jet[j].chargedHadronEnergyFraction > 0                        			)) jetid=false;
              if(!(      jet[j].chargedEmEnergyFraction < 0.99                            		)) jetid=false;
              if(!(      jet[j].chargedHadronMultiplicity > 0                             		)) jetid=false;
            }
	    double scale = h1_taufakescaleT_fac->GetBinContent(h1_taufakescaleT_fac->FindBin(jet[j].pt));
            //if(       jetid  		){
              if(	baseDistance >= 0.3	) baselineObjectSelectionCollection.jet.push_back(&jet[j]);	
	      if(	scale*jet[j].pt >= 45.  && mainDistance >= 0.3 && fabs(jet[j].eta)<2.2	) TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
            //}
            if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244    ){
              if(	baseDistance >= 0.3	) baselineObjectSelectionCollection.bjet.push_back(&jet[j]);	
              if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
            }
	  }
	  
	  //dice 1 jet to be a tau that passes selections
	  if(TauTightIsoObjectSelectionCollection.jet.size()>0){
	    std::uniform_int_distribution<> distribution(0, TauTightIsoObjectSelectionCollection.jet.size()-1);
	    std::random_device rd;
	    std::mt19937 engine(rd());
	    int Toss=distribution(engine);
	    tau_s faketau;
	    double scale = h1_taufakescaleT_fac->GetBinContent(h1_taufakescaleT_fac->FindBin(TauTightIsoObjectSelectionCollection.jet[Toss]->pt));
	    if(TauTightIsoObjectSelectionCollection.jet[Toss]->charge >= 0 )
	    faketau.charge = +1;
	    else if(TauTightIsoObjectSelectionCollection.jet[Toss]->charge < 0 )
	    faketau.charge = -1;
	    faketau.p = TauTightIsoObjectSelectionCollection.jet[Toss]->p;
	    faketau.energy = TauTightIsoObjectSelectionCollection.jet[Toss]->energy;
	    faketau.et = TauTightIsoObjectSelectionCollection.jet[Toss]->et;
	    faketau.px = TauTightIsoObjectSelectionCollection.jet[Toss]->px;
	    faketau.py = TauTightIsoObjectSelectionCollection.jet[Toss]->py;
	    faketau.pz = TauTightIsoObjectSelectionCollection.jet[Toss]->pz;
	    faketau.pt = TauTightIsoObjectSelectionCollection.jet[Toss]->pt * scale;
	    faketau.phi = TauTightIsoObjectSelectionCollection.jet[Toss]->phi;
	    if(TauTightIsoObjectSelectionCollection.jet[Toss]->eta<=2.1) faketau.eta = TauTightIsoObjectSelectionCollection.jet[Toss]->eta;
	    else faketau.eta = TauTightIsoObjectSelectionCollection.jet[Toss]->eta/fabs(TauTightIsoObjectSelectionCollection.jet[Toss]->eta)*2.1;
	    MonoTauIsoObjectSelectionCollection.tau.push_back(&faketau);
	  }
	  int exitus=0;
	  //find all non-tau-jets left
	  for(unsigned int j = 0;j<jet.size();++j){
	    if(!(      jet[j].pt >= 30.                                                	)) continue;  // Original value 20
	    if(!(      fabs(jet[j].eta) <= 5.0                                          )) continue;
	    double MonoDistance = TauJetMinDistance(MonoTauIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
            bool jetid=true;
	    if(!(      (jet[j].neutralHadronEnergy + jet[j].HFHadronEnergy) / jet[j].energy < 0.99      )) jetid=false;
	    if(!(      jet[j].neutralEmEnergyFraction < 0.99                                            )) jetid=false;
	    if(!(      jet[j].numberOfDaughters > 1                                                     )) jetid=false;
	    if(fabs(jet[j].eta) < 2.4) {
              if(!(      jet[j].chargedHadronEnergyFraction > 0                        			)) jetid=false;
              if(!(      jet[j].chargedEmEnergyFraction < 0.99                            		)) jetid=false;
              if(!(      jet[j].chargedHadronMultiplicity > 0                             		)) jetid=false;
            }
            if(      jetid			){
              if(	MonoDistance >= 0.3	) MonoTauIsoObjectSelectionCollection.jet.push_back(&jet[j]);
	      else if(MonoTauIsoObjectSelectionCollection.tau.size()==2) exitus++;
            }
            if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244    ){
              if(	MonoDistance >= 0.3	) MonoTauIsoObjectSelectionCollection.bjet.push_back(&jet[j]);	
            }
	  }
	//std::cout<<"base="<<baselineObjectSelectionCollection.jet.size()<<", 1tau>45="<<TauTightIsoObjectSelectionCollection.jet.size()<<", end="<<MonoTauIsoObjectSelectionCollection.jet.size()<<", exitus="<<exitus<<std::endl;
	  //MET selection
	  baselineObjectSelectionCollection.met.push_back(&met[0]);
	  TauTightIsoObjectSelectionCollection.met.push_back(&met[0]);
	  MonoTauIsoObjectSelectionCollection.met.push_back(&met[0]);

	  //Event Count
	  ofile.count("NoCuts");

	  // ------------------------
	  // -- Skimming Studies   --
	  // ------------------------

	  myHistoColl_Skim.h_count->Fill("NoCuts",0);
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",0);

	  while (true){

		//NoCuts
		myHistoColl_Skim.h_count->Fill("NoCuts",1);

		//AtLeast2Loostau
		//if(!(             ( (int)baselineObjectSelectionCollection.tau.size() >= 2 )                 )) break;
		//myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",1);

		fillHistoCollection (myHistoColl_Skim, baselineObjectSelectionCollection,weight);

		break;		

	}

/*if(MonoTauIsoObjectSelectionCollection.tau.size()==2){
std::cout<<"There is one!"<<std::endl;
if(MonoTauIsoObjectSelectionCollection.tau[0]->charge*MonoTauIsoObjectSelectionCollection.tau[1]->charge==1)std::cout<<"It's even got good charge"<<std::endl;
}*/
//if(MonoTauIsoObjectSelectionCollection.tau.size()==2 && (MonoTauIsoObjectSelectionCollection.tau[0]->pt < 50 || MonoTauIsoObjectSelectionCollection.tau[1]->pt < 50))MonoTauIsoObjectSelectionCollection.tau.clear();
// ---------------------
// -- Signal Region --
// ---------------------

Selection SR("SR"); //label and initialisation
SR.InputCollection 	= &MonoTauIsoObjectSelectionCollection;        //input collection
SR.OutputCollection 	= &myHistoColl_SR;        //output collection
SR.RealData        	= eventhelper_isRealData;        //pass information if event is real data
SR.RunData        	= false;        //real data allowed
SR.NumberTauMin        	= 2;        //require at least N tau
SR.NumberTauMax        	= 3;        //require at less than N taus
SR.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
SR.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
SR.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
SR.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
SR.Btag        		= 0;        //number of btags required (exact -> 0 = none)
SR.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
SR.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
SR.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
SR.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
SR.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
SR.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
SR.DiJetDrMax        	= -1;        //Dijet maximum delta R, set to -1 for no requirement
SR.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
SR.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
SR.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
SR.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
SR.DiJetDetaMax        	= -1;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
SR.weight        	= 1.;        //event weight
SR.invertTauRequirements    = false;        //invert number of taus requirement
SR.invertTauProperties      = false;        //invert ditau properties (dR, sign)
SR.invertBtagRequirement    = false;        //invert number of b-jets required
SR.invertJetRequirements    = false;        //invert jet pt requirements
SR.invertDijetProperties    = false;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

SR.select();        //do selection, fill histograms

// -------------------------------------------
// -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
// -------------------------------------------

Selection CR("CR"); //label and initialisation
CR.InputCollection 	= &MonoTauIsoObjectSelectionCollection;        //input collection
CR.OutputCollection 	= &myHistoColl_CR;        //output collection
CR.RealData        	= eventhelper_isRealData;        //pass information if event is real data
CR.RunData        	= true;        //real data allowed
CR.NumberTauMin        	= 2;        //require at least N tau
CR.NumberTauMax        	= 3;        //require at less than N taus
CR.DiTauDeltaRmin       = 0.3;        //minimum delta R for tau pair
CR.DiTauInvMassMin      = -1;        //minimum Di-tau-mass requirement
CR.DiTauInvMassMax      = -1;        //maximum Di-tau-mass requirement
CR.DiTauSign        	= +1;        //1 for LS and -1 for OS, 0 for no requirement
CR.Btag        		= 0;        //number of btags required (exact -> 0 = none)
CR.JetEtaMax        	= 5.;        //maximum eta for jets, set to -1 for no requirement
CR.LeadJetPtMin        	= 30.;        //minimum pt of lead jet, set to -1 for no requirement
CR.LeadJetPtMax        	= -1.;        //maximum pt of lead jet, set to -1 for no requirement
CR.SubLeadJetPtMin      = 30.;        //minimum pt of sub lead jet, set to -1 for no requirement
CR.SubLeadJetPtMax      = -1.;        //maximum pt of sub lead jet, set to -1 for no requirement
CR.DiJetDrMin        	= 0.3;        //Dijet minimum delta R, set to -1 for no requirement
CR.DiJetDrMax        	= -1.;        //Dijet maximum delta R, set to -1 for no requirement
CR.DiJetInvMassMin      = 250.;        //Dijet minimal invariant mass, set to -1 for no requirement
CR.DiJetInvMassMax      = -1.;        //Dijet maximum invariant mass, set to -1 for no requirement
CR.DiJetSignEta        	= -1;        //Dijet sign eta_1*eta_2
CR.DiJetDetaMin        	= 3.9;        //Dijet |eta_1-eta_2| minimum, set to -1 for no requirement
CR.DiJetDetaMax        	= -1.;        //Dijet |eta_1-eta_2| maximum, set to -1 for no requirement
CR.weight        	= 1.;        //event weight
CR.invertTauRequirements   = false;        //invert number of taus requirement
CR.invertTauProperties     = false;        //invert ditau properties (dR, sign)
CR.invertBtagRequirement   = false;        //invert number of b-jets required
CR.invertJetRequirements   = true;        //invert jet pt requirements
CR.invertDijetProperties   = true;        //invert dijet system properties (dR, inv mass, sign eta, dEta)

CR.select();        //do selection, fill histograms

//Clearing Object Collections
TauTightIsoObjectSelectionCollection.clear();
MonoTauIsoObjectSelectionCollection.clear();
baselineObjectSelectionCollection.clear();
}
  stream.close();
  ofile.close();
  return 0;
}

