//-----------------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for ntuples created by TheNtupleMaker
// Created:     Wed Jul 15 14:54:46 2015 by mkanalyzer.py
// Author:      Daniele Marconi
//-----------------------------------------------------------------------------

#include "CommonHistoCollection.h"
#include "CutConfiguration.h"
#include "analyzer.h"

using namespace std;
using namespace evt;

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

  int nevents = stream.size();
  cout << "Number of events: " << nevents << endl;

  // Select variables to be read

  selectVariables(stream);


  // The root application is needed to make canvases visible during
  // program execution. If this is not needed, just comment out the
  // following line

  TApplication app("analyzer", &argc, argv);

  /**
	 Notes 1
	 -------
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

     Notes 2
	 -------
	 By default all variables are saved. Before the event loop, you can use
  
       select(objectname)
	  
     e.g.,
	
       select("GenParticle")
  
     to declare that you intend to select objects of this type. The
	 selection is done using

       select(objectname, index)
	  
     e.g.,
	  
       select("GenParticle", 3),
  
     which is called within the event loop. Call saveSelectedObjects()
	 before a call to addEvent if you wish to save the selected objects.
	 All other objects are saved by default.
	 
	 NB: If you declare your intention to select objects of a given type
	     by calling select(objectname), but subsequently fail to select
	     them using select(objectname, index) then none will be saved!
  */

  outputFile ofile(cmdline.outputfilename);

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------


  //---------------------------------------------------------------------------
  // Histogram Collection Init
  //---------------------------------------------------------------------------
	
	double weight = 1.;

	MyHistoCollection myHistoColl_Skim 		(ofile.file_, "Skim");
	
	MyHistoCollection myHistoColl_OS_SignalRegion	(ofile.file_, "OS_SignalRegion");        
	MyHistoCollection myHistoColl_OS_CR2 		(ofile.file_, "OS_Central_invertedVBF_2TightIso_CR2");
	
	MyProfileCollection myProfileColl_OS_SignalRegion	(ofile.file_, "p_OS_SignalRegion");        
	MyProfileCollection myProfileColl_OS_CR2 		(ofile.file_, "p_OS_Central_invertedVBF_2TightIso_CR2");
	
	MyHistoCollection myHistoColl_LS_SignalRegion	(ofile.file_, "LS_SignalRegion");        
	MyHistoCollection myHistoColl_LS_CR2 		(ofile.file_, "LS_Central_invertedVBF_2TightIso_CR2");
	
	MyProfileCollection myProfileColl_LS_SignalRegion	(ofile.file_, "p_LS_SignalRegion");        
	MyProfileCollection myProfileColl_LS_CR2 		(ofile.file_, "p_LS_Central_invertedVBF_2TightIso_CR2");
	
	MyEventCollection baselineObjectSelectionCollection ("baselineObjectSelection");
	MyEventCollection TauTightIsoObjectSelectionCollection ("TauTightIsoObjectSelection");
	MyEventCollection Tau1TightIsoObjectSelectionCollection ("Tau1TightIsoObjectSelection");
	MyEventCollection TauMediumIsoObjectSelectionCollection ("TauMediumIsoObjectSelection");
	MyEventCollection TauLooseIsoObjectSelectionCollection ("TauLooseIsoObjectSelection");
	MyEventCollection TauNoIsoObjectSelectionCollection ("TauNoIsoObjectSelection");

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------


  for(int entry=0; entry < nevents; ++entry)
	{
	  // Read event into memory
	  stream.read(entry);

	  // NB: call to clear object selection map (indexmap)
	  initialize();
	  
	  // Uncomment the following line if you wish to copy variables into
	  // structs. See the header file analyzer.h to find out what structs
	  // are available. Alternatively, you can call individual fill functions.
	  fillObjects();

	  // ----------------------
	  // -- object selection --
	  // ----------------------

	  baselineObjectSelectionCollection.NVtx        = nvertex;
	  TauTightIsoObjectSelectionCollection.NVtx 	= nvertex;
	  Tau1TightIsoObjectSelectionCollection.NVtx 	= nvertex;
	  TauMediumIsoObjectSelectionCollection.NVtx 	= nvertex;
	  TauLooseIsoObjectSelectionCollection.NVtx 	= nvertex;
	  TauNoIsoObjectSelectionCollection.NVtx        = nvertex;

	  // vertex selection
	  bool goodVertex = true;

	  if(!( vertex.size() > 0 )) goodVertex = false;
	  if( goodVertex ) {
		  baselineObjectSelectionCollection.goodVertex = true;
		  TauTightIsoObjectSelectionCollection.goodVertex = true;
		  Tau1TightIsoObjectSelectionCollection.goodVertex = true;
		  TauMediumIsoObjectSelectionCollection.goodVertex = true;
		  TauLooseIsoObjectSelectionCollection.goodVertex = true;
		  TauNoIsoObjectSelectionCollection.goodVertex = true;
	  }

	  //trigger selection

	  baselineObjectSelectionCollection.passedTrigger = true;	
	  TauTightIsoObjectSelectionCollection.passedTrigger = true;
	  Tau1TightIsoObjectSelectionCollection.passedTrigger = true;
	  TauMediumIsoObjectSelectionCollection.passedTrigger = true;
	  TauLooseIsoObjectSelectionCollection.passedTrigger = true;
	  TauNoIsoObjectSelectionCollection.passedTrigger = true;
	

	  // electron selection
	  for(unsigned int e = 0;e<electron.size();++e){
		  baselineObjectSelectionCollection.electron.push_back(&electron[e]);
		  TauTightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
		  Tau1TightIsoObjectSelectionCollection.electron.push_back(&electron[e]);
		  TauMediumIsoObjectSelectionCollection.electron.push_back(&electron[e]);
		  TauLooseIsoObjectSelectionCollection.electron.push_back(&electron[e]);
		  TauNoIsoObjectSelectionCollection.electron.push_back(&electron[e]);
	  }

	  // muon selection
	  for(unsigned int m =0;m<muon.size();++m){
		  if(!( fabs(muon[m].eta) < 2.4 )) 					continue;
		  if(!( muon[m].pt > 20 )) 						continue;
		  if(!( muon[m].isGlobalMuon )) 						continue;
		  if(!( muon[m].isTrackerMuon )) 						continue;
		  if(!( muon[m].isPFMuon )) 						continue;
		  if(!( muon[m].numberOfMatchedStations > 1 )) 				continue;
		  if(!(( fabs(muon[m].muonBestTrack_dxy) < 0.2 )) &&
				  ( fabs(muon[m]. muonBestTrack_dz) < 0.5 )) 			continue;
		  if(!( muon[m].globalTrack_normalizedChi2 < 10. )) 			continue;
		  if(!( muon[m].globalTrack_hitPattern_numberOfValidMuonHits > 0 )) 	continue;
		  if(!( muon[m].innerTrack_hitPattern_numberOfValidPixelHits > 0 )) 	continue;
		  if(!( muon[m].innerTrack_hitPattern_pixelLayersWithMeasurement > 5 )) 	continue;
		  if(!( muon[m].innerTrack_normalizedChi2 < 1.8 )) 			continue;
		  if(!( fabs(muon[m].innerTrack_dxy) < 3. )) 				continue;
		  if(!( fabs(muon[m].innerTrack_dz) < 30. )) 				continue;
		  baselineObjectSelectionCollection.muon.push_back(&muon[m]);
		  TauTightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
		  Tau1TightIsoObjectSelectionCollection.muon.push_back(&muon[m]);
		  TauMediumIsoObjectSelectionCollection.muon.push_back(&muon[m]);
		  TauLooseIsoObjectSelectionCollection.muon.push_back(&muon[m]);
		  TauNoIsoObjectSelectionCollection.muon.push_back(&muon[m]);
	  }     

	  std::vector<int> tights;
	  std::vector<int> mediums;
	  std::vector<int> looses;
	  std::vector<int> nones;

	  //smart tau selection
	  //cout << "DEBUG: Tau vector size: " << tau.size() << endl;
	  for(unsigned int t =0;t<tau.size();++t){
		  //cout << "DEBUG: Tau counter: " << t << endl;
		  if(!(	fabs(tau[t].eta) <= 2.1                              					)) continue;
		  //cout << "DEBUG: Eta cut passed for tau : " << t << endl;
		  //cout << "DEBUG: Tau pt : " << tau[t].pt << endl;
		  //cout << "DEBUG: Tau eta : " << tau[t].eta << endl;
		  //cout << "DEBUG: Tau phi : " << tau[t].phi << endl;
		  //OLDID    //if(!(       tau[t].pt >= 45.                                            				)) continue;
		  if(!(       tau[t].pt >= 20.                                            				)) continue;
		  //cout << "DEBUG: Pt cut passed for tau : " << t << endl;
		  //OLDID  //if(!(       tau[t].tauID_againstElectronMediumMVA5 > 0.5                				)) continue;
		  if(!(       tau[t].tauID_againstElectronVLooseMVA5 > 0.5                				)) continue;
		  //cout << "DEBUG: Electron veto cut passed for tau : " << t << endl;
		  if(!(       tau[t].tauID_againstMuonLoose3 > 0.5                        				)) continue;
		  //cout << "DEBUG: Muon veto cut passed for tau : " << t << endl;
		  if(!(       tau[t].leadChargedHadrCand_pt >= 5.0                      				)) continue;
		  //cout << "DEBUG: leadChargedHadrCand_pt cut passed for tau : " << t << endl;
		  if(!(       (tau[t].tauID_decayModeFindingNewDMs > 0.5) 
//TODO(Lele): check if the variable is the miniaods					  //&& (tau[t].signalPFChargedHadrCands_size == 1)	
					  )) continue;
		  //cout << "DEBUG: decayModeFindingNewDMs cut passed for tau : " << t << endl;

		  baselineObjectSelectionCollection.tau.push_back(&tau[t]);
		  /*pTchargedHad->Fill(tau[t].leadPFChargedHadrCand_pt);
		    eVeto->Fill(tau[t].tauID_againstElectronMediumMVA5);
		    MuVeto->Fill(tau[t].tauID_againstMuonLoose3);
		    DMFandProng->Fill(tau[t].tauID_decayModeFindingNewDMs,tau[t].signalPFChargedHadrCands_size);
		    TightIso->Fill(tau[t].tauID_byTightIsolationMVA3newDMwLT);*/

		  //OLDID   if(!(tau[t].tauID_byTightIsolationMVA3newDMwLT  <= 0.5)) tights.push_back(t);
		  //OLDID   else if(!(tau[t].tauID_byMediumIsolationMVA3newDMwLT  <= 0.5)) mediums.push_back(t);
		  //OLDID   else if(!(tau[t].tauID_byLooseIsolationMVA3newDMwLT  <= 0.5)) looses.push_back(t);
		  
		  if(!(tau[t].tauID_byLooseCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) tights.push_back(t);
		  else if(!(tau[t].tauID_byMediumCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) mediums.push_back(t);
		  else if(!(tau[t].tauID_byTightCombinedIsolationDeltaBetaCorr3Hits  <= 0.5)) looses.push_back(t);
		  //else nones.push_back(t);
	  }

	  if(tights.size()==2) for(unsigned int t =0;t<tights.size();++t) {int i=tights[t]; TauTightIsoObjectSelectionCollection.tau.push_back(&tau[i]);}
	  else if(tights.size()==1 && (mediums.size()+looses.size()+nones.size())==1) {tights.insert(tights.end(),mediums.begin(), mediums.end()); tights.insert(tights.end(),looses.begin(), looses.end()); tights.insert(tights.end(),nones.begin(), nones.end()); for(unsigned int t =0;t<tights.size();++t) {int i=tights[t]; Tau1TightIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(mediums.size()>=1 && (mediums.size()+looses.size()+nones.size())==2) {mediums.insert(mediums.end(), looses.begin(), looses.end()); mediums.insert(mediums.end(), nones.begin(), nones.end()); for(unsigned int t =0;t<mediums.size();++t) {int i=mediums[t]; TauMediumIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(looses.size()>=1 && (looses.size()+nones.size())==2) {looses.insert(looses.end(), nones.begin(), nones.end()); for(unsigned int t =0;t<looses.size();++t) {int i=looses[t]; TauLooseIsoObjectSelectionCollection.tau.push_back(&tau[i]);}}
	  else if(nones.size()==2) for(unsigned int t =0;t<nones.size();++t) {int i=nones[t]; TauNoIsoObjectSelectionCollection.tau.push_back(&tau[i]);}

	  realTauMass(TauTightIsoObjectSelectionCollection);
	  realTauMass(Tau1TightIsoObjectSelectionCollection);
	  realTauMass(TauMediumIsoObjectSelectionCollection);
	  realTauMass(TauLooseIsoObjectSelectionCollection);
	  realTauMass(TauNoIsoObjectSelectionCollection);


	  // jet && bjet selection
	  // ? id ?
	  //cout << "jet.size(): " << jet.size() << endl;
	  for(unsigned int j = 0;j<jet.size();++j){
		  //cout << "CIao inizio!!!" << endl;
		  //cout << "jet[j].pt" << jet[j].pt << endl;
		  if(!(      jet[j].pt >= 30.                                                	)) continue;  // Original value 20
		  //cout << "Cut 1!!!" << endl;
		  if(!(      fabs(jet[j].eta) <= 5.0                                          )) continue;
		  //cout << "Cut 2!!!" << endl;
		  double baseDistance = TauJetMinDistance(baselineObjectSelectionCollection, jet[j].eta, jet[j].phi);
		  double mainDistance = TauJetMinDistance(TauTightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
		  double T1Distance = TauJetMinDistance(Tau1TightIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
		  double mediumDistance = TauJetMinDistance(TauMediumIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
		  double looseDistance = TauJetMinDistance(TauLooseIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
		  double NoDistance = TauJetMinDistance(TauNoIsoObjectSelectionCollection, jet[j].eta, jet[j].phi);
		  bool jetid=true;
		  if(!(      jet[j].neutralHadronEnergyFraction < 0.99                                        )) jetid=false;
		  if(!(      jet[j].neutralEmEnergyFraction < 0.99                                            )) jetid=false;
		  if(!(      jet[j].numberOfDaughters > 1                                                     )) jetid=false;
		  if(fabs(jet[j].eta) < 2.4) {
			  if(!(      jet[j].chargedHadronEnergyFraction > 0                        			)) jetid=false;
			  if(!(      jet[j].chargedEmEnergyFraction < 0.99                            		)) jetid=false;
			  if(!(      jet[j].chargedHadronMultiplicity > 0					)) jetid=false;
		  }
		  //cout << "CIao fine!!!" << endl;
		  //cout << "jetid: " << jetid << endl;
		  if(      /*jet[j].pt >= 50.  &&*/ jetid		){
			  if(	baseDistance >= 0.3	) baselineObjectSelectionCollection.jet.push_back(&jet[j]);	
			  if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
			  if(	T1Distance >= 0.3	) Tau1TightIsoObjectSelectionCollection.jet.push_back(&jet[j]);
			  if(	mediumDistance >= 0.3	) TauMediumIsoObjectSelectionCollection.jet.push_back(&jet[j]);
			  if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.jet.push_back(&jet[j]);
			  if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.jet.push_back(&jet[j]);
		  }
//TODO(Lele): Include Bjetveto in ntuples
//		  if(fabs(jet[j].eta) <= 2.4 && jet[j].bDiscriminator_combinedSecondaryVertexBJetTags > 0.244    ){
//			  if(	baseDistance >= 0.3	) baselineObjectSelectionCollection.bjet.push_back(&jet[j]);	
//			  if(	mainDistance >= 0.3	) TauTightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
//			  if(	T1Distance >= 0.3	) Tau1TightIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
//			  if(	mediumDistance >= 0.3	) TauMediumIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
//			  if(	looseDistance >= 0.3	) TauLooseIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
//			  if(	NoDistance  >= 0.3	) TauNoIsoObjectSelectionCollection.bjet.push_back(&jet[j]);
//		  }
	  }

	  //MET selection
	  baselineObjectSelectionCollection.met.push_back(&met2[0]);
	  TauTightIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  Tau1TightIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  TauMediumIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  TauLooseIsoObjectSelectionCollection.met.push_back(&met2[0]);
	  TauNoIsoObjectSelectionCollection.met.push_back(&met2[0]);

	  //Event Count
	  ofile.count("NoCuts");

	  // ------------------------
	  // -- Skimming Studies   --
	  // ------------------------

	  myHistoColl_Skim.h_count->Fill("NoCuts",0);
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",0);

	  //NoCuts
	  myHistoColl_Skim.h_count->Fill("NoCuts",1);

	  //AtLeast2Loostau
	  //if(!(             ( (int)baselineObjectSelectionCollection.tau.size() >= 2 )                 )) break;
	  //myHistoColl_Skim.h_count->Fill("AtLeast2Loosetau",1);

	  fillHistoCollection (myHistoColl_Skim, baselineObjectSelectionCollection,weight);

	  //set sign	
	  bool LS=true; 	


	  // ---------------------
	  // -- Signal Region --
	  // ---------------------
	  //if(TauTightIsoObjectSelectionCollection.jet.size()>=2){
	  Selection LS_Signal("LS_Signal"); 					//label and initialisation
	  LS_Signal.InputCollection 	= &TauTightIsoObjectSelectionCollection;//input collection
	  LS_Signal.OutputCollection 	= &myHistoColl_LS_SignalRegion;        	//output collection
	  LS_Signal.ProfileCollection 	= &myProfileColl_LS_SignalRegion;      	//profile collection
	  LS_Signal.RealData        	= false;        	//pass information if event is real data
	  LS_Signal.RunData        	= true;        				//real data allowed
	  LS_Signal.RequireTriggers       = false;       				//require at least one of the triggers fired
	  LS_Signal.weight        	= weight;      				//event weight
	  CutConfiguration(&LS_Signal, true, LS); 				//selection, VBF, LS
	  LS_Signal.METMin = 30.;

	  LS_Signal.select(false);        						//do selection, fill histograms

	  // -------------------------------------------
	  // -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
	  // -------------------------------------------

	  Selection InvertedVBF_LS_CR2("InvertedVBF_LS_CR2"); 				//label and initialisation
	  InvertedVBF_LS_CR2.InputCollection 	= &TauTightIsoObjectSelectionCollection;//input collection
	  InvertedVBF_LS_CR2.OutputCollection 	= &myHistoColl_LS_CR2;        		//output collection
	  InvertedVBF_LS_CR2.ProfileCollection 	= &myProfileColl_LS_CR2;      		//profile collection
	  InvertedVBF_LS_CR2.RealData        	= false;        	//pass information if event is real data
	  InvertedVBF_LS_CR2.RunData        	= true;        				//real data allowed
	  InvertedVBF_LS_CR2.RequireTriggers      = false;       				//require at least one of the triggers fired
	  InvertedVBF_LS_CR2.weight        	= weight;      				//event weight
	  CutConfiguration(&InvertedVBF_LS_CR2, false, LS); 				//selection, VBF, LS
	  InvertedVBF_LS_CR2.METMin = 30.;

	  InvertedVBF_LS_CR2.select(false);        						//do selection, fill histograms

	  //}

	  //_____________________________________________
	  //-------------------OS SECTION----------------
	  //_____________________________________________

	  LS=false;

	  // ---------------------
	  // -- Signal Region --
	  // ---------------------
	  //if(TauTightIsoObjectSelectionCollection.jet.size()>=2){
	  Selection OS_Signal("OS_Signal"); //label and initialisation
	  OS_Signal.InputCollection 		= &TauTightIsoObjectSelectionCollection;//input collection
	  OS_Signal.OutputCollection 		= &myHistoColl_OS_SignalRegion;        	//output collection
	  OS_Signal.ProfileCollection 		= &myProfileColl_OS_SignalRegion;       //profile collection
	  OS_Signal.RealData        		= false;        	//pass information if event is real data
	  OS_Signal.RunData        		= false;        			//real data allowed
	  OS_Signal.RequireTriggers          	= false;       				//require at least one of the triggers fired
	  OS_Signal.weight        		= weight;      				//event weight
	  CutConfiguration(&OS_Signal, true, LS); 					//selection, VBF, LS
	  OS_Signal.METMin = 30.;

	  OS_Signal.select(false);        							//do selection, fill histograms

	  // -------------------------------------------
	  // -- CENTRAL + INVERTED VBF + 2 Iso Tau CR --
	  // -------------------------------------------

	  Selection InvertedVBF_OS_CR2("InvertedVBF_OS_CR2"); 				//label and initialisation
	  InvertedVBF_OS_CR2.InputCollection 	= &TauTightIsoObjectSelectionCollection;//input collection
	  InvertedVBF_OS_CR2.OutputCollection 	= &myHistoColl_OS_CR2;        		//output collection
	  InvertedVBF_OS_CR2.ProfileCollection 	= &myProfileColl_OS_CR2;	        //profile collection
	  InvertedVBF_OS_CR2.RealData        	= false;        	//pass information if event is real data
	  InvertedVBF_OS_CR2.RunData        	= true;        				//real data allowed
	  InvertedVBF_OS_CR2.RequireTriggers      = false;       				//require at least one of the triggers fired
	  InvertedVBF_OS_CR2.weight        	= weight;      				//event weight
	  CutConfiguration(&InvertedVBF_OS_CR2, false, LS); 				//selection, VBF, LS
	  InvertedVBF_OS_CR2.METMin = 30.;

	  InvertedVBF_OS_CR2.select(false);        						//do selection, fill histograms

	  //}

	  // ---------------------
	  // -- event selection --
	  // ---------------------



	  // ---------------------
	  // -- fill histograms --
	  // ---------------------	  

	  //Clearing Object Collections
	  TauTightIsoObjectSelectionCollection.clear();
	  Tau1TightIsoObjectSelectionCollection.clear();
	  TauMediumIsoObjectSelectionCollection.clear();
	  TauLooseIsoObjectSelectionCollection.clear();
	  TauNoIsoObjectSelectionCollection.clear();
	  baselineObjectSelectionCollection.clear();
	}

  //TODO(lele): remember to write properly to file


  stream.close();
  ofile.close();
  return 0;
}
