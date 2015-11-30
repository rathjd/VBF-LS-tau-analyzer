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

	TH1F* h_njet;
	TH1F* h_jet1pt;
	TH1F* h_jet1eta;
	TH1F* h_jet2pt;
	TH1F* h_jet2eta;
	TH1F* h_dijetinvariantmass;
	TH1F* h_dijetdeltaeta;

	TH1F* h_electron1pt;
	TH1F* h_electron1eta;
	TH1F* h_electron2pt;
	TH1F* h_electron2eta;
	TH1F* h_dielectroninvariantmass;  

	TH1F* h_muon1pt;
	TH1F* h_muon1eta;
	TH1F* h_muon2pt;
	TH1F* h_muon2eta;
	TH1F* h_dimuoninvariantmass;  

	TH1F* h_tau1pt;
	TH1F* h_tau1eta;
	TH1F* h_tau2pt;
	TH1F* h_tau2eta;
	TH1F* h_ditauinvariantmass;  

	TH1F* h_C1pt;
	TH1F* h_C1eta;

	TH1F* h_N2pt;
	TH1F* h_N2eta;

	TH1F* h_decaychain;
	TH1F* h_vertexz;
	TH1F* h_met;

	//---------------------------------------------------------------------------
	// Histogram Collection Init
	//---------------------------------------------------------------------------

	h_njet = new TH1F("h_njet", "h_njet", 21, -0.5, 20.5);
	h_jet1pt = new TH1F("h_jet1pt", "h_jet1pt", 50, 0., 500.);
	h_jet1eta = new TH1F("h_jet1eta", "h_jet1eta", 50 , -5., 5.);
	h_jet2pt = new TH1F("h_jet2pt", "h_jet2pt", 50, 0., 500.);
	h_jet2eta = new TH1F("h_jet2eta", "h_jet2eta", 50 , -5., 5.);
	h_dijetinvariantmass = new TH1F("h_dijetinvariantmass","h_dijetinvariantmass", 10, 0., 2500.);
	h_dijetdeltaeta = new TH1F ("h_dijetdeltaeta", "h_dijetdeltaeta", 20, 0., 10.);

	h_electron1pt = new TH1F("h_electron1pt", "h_electron1pt", 50, 0., 500.);
	h_electron1eta = new TH1F("h_electron1eta", "h_electron1eta", 30 , -3., 3.);
	h_electron2pt = new TH1F("h_electron2pt", "h_electron2pt", 50, 0., 500.);
	h_electron2eta = new TH1F("h_electron2eta", "h_electron2eta", 30 , -3., 3.);
	h_dielectroninvariantmass = new TH1F("h_dielectroninvariantmass", "h_dielectroninvariantmass", 30, 0., 300.); 

	h_muon1pt = new TH1F("h_muon1pt", "h_muon1pt", 50, 0., 500.);
	h_muon1eta = new TH1F("h_muon1eta", "h_muon1eta", 30 , -3., 3.);
	h_muon2pt = new TH1F("h_muon2pt", "h_muon2pt", 50, 0., 500.);
	h_muon2eta = new TH1F("h_muon2eta", "h_muon2eta", 30 , -3., 3.);
	h_dimuoninvariantmass = new TH1F("h_dimuoninvariantmass", "h_dimuoninvariantmass", 30, 0., 300.); 

	h_tau1pt = new TH1F("h_tau1pt", "h_tau1pt", 50, 0., 500.);
	h_tau1eta = new TH1F("h_tau1eta", "h_tau1eta", 30 , -3., 3.);
	h_tau2pt = new TH1F("h_tau2pt", "h_tau2pt", 50, 0., 500.);
	h_tau2eta = new TH1F("h_tau2eta", "h_tau2eta", 30 , -3., 3.);
	h_ditauinvariantmass = new TH1F("h_ditauinvariantmass", "h_ditauinvariantmass", 30, 0., 300.); 

	h_C1pt = new TH1F("h_C1pt", "h_C1pt", 50, 0., 800.);
	h_C1eta = new TH1F("h_C1eta", "h_C1eta", 30, -3., 3.);
	h_N2pt = new TH1F("h_N2pt", "h_N2pt", 50, 0., 800.);
	h_N2eta = new TH1F("h_N2eta", "h_N2eta", 30, -3., 3.);

	h_decaychain = new TH1F("h_decaychain", "h_decaychain", 1,0,1);
	h_vertexz = new TH1F("h_vertexz", "h_vertexz", 60, -60., 60.);
	h_met = new TH1F("h_met", "h_met", 12, 0., 240.);

	//decay chai plot init
	h_decaychain->Fill("C1->Stau->Tau",0.); 
	h_decaychain->Fill("N2->Stau->Tau",0.); 
	h_decaychain->Fill("noChain",0.); 

	//---------------------------------------------------------------------------
	// Loop over events
	//---------------------------------------------------------------------------

	double weight = 1.;

	int zerocounter = 0;
	int eventcounter = 0;

		for(int entry=0; entry < nevents; ++entry)
		{
			// Read event into memory
			stream.read(entry);

			eventcounter++;

			cout << "--------------Event-----------------" << endl;

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
			ofile.count("NoCuts");

			// ------------------------
			// -- Genlevel Studies   --
			// ------------------------

			std::vector<genparticlehelper_s*> genTau;
			std::vector<genparticlehelper_s*> genMuon;
			std::vector<genparticlehelper_s*> genElectron;
			//std::vector<genparticlehelper_s*> genTau;
			std::vector<genparticlehelper_s*> genParton;
			std::vector<genparticlehelper_s*> genInvis;
			std::vector<genparticlehelper_s*> genC1nos;
			std::vector<genparticlehelper_s*> genN2nos;


			while (true){


				for (unsigned int g = 0; g < genparticlehelper.size(); g++){
					//cout << "#-------------" << endl;
					//cout << "PdgId: " << (int) genparticlehelper[g].pdgId << endl;
					//cout << "Status: " << genparticlehelper[g].status << endl;
					//if (fabs(genparticlehelper[g].pdgId) < 9 ) cout << "PARTONE!!! " <<endl;
					//if (  !(fabs(genparticlehelper[g].status)==1 || fabs(genparticlehelper[g].status)==2)  ) continue;
					//if (  !(fabs(genparticlehelper[g].status) > 20 )  ) continue;
					//cout << "PdgId: " << genparticlehelper[g].pdgId << endl;
					//cout << "Status: " << genparticlehelper[g].status << endl;
					if (fabs(genparticlehelper[g].pdgId) == 15) {
						genTau.push_back(&genparticlehelper[g]);
						//cout << "Found Tau" << endl;
					}
					if (fabs(genparticlehelper[g].pdgId) == 1000022 || fabs(genparticlehelper[g].pdgId) == 12 || fabs(genparticlehelper[g].pdgId) == 14 || fabs(genparticlehelper[g].pdgId) == 16 ) {
						genInvis.push_back(&genparticlehelper[g]);
						//cout << "Found Invis" << endl;
					}
					if (fabs(genparticlehelper[g].pdgId) == 1000024) { 
						genC1nos.push_back(&genparticlehelper[g]);
						//cout << "Found C1" << endl;
					}
					if (fabs(genparticlehelper[g].pdgId) == 1000023) {
						genN2nos.push_back(&genparticlehelper[g]);
						//cout << "Found N2" << endl;
					}
					if (fabs(genparticlehelper[g].pdgId) == 11) {
						genElectron.push_back(&genparticlehelper[g]);
						//cout << "Found Electron" << endl;
					}

					if (fabs(genparticlehelper[g].pdgId) == 13) {
						genMuon.push_back(&genparticlehelper[g]);
						//cout << "Found Muon" << endl;
					}
					//if (fabs(genparticlehelper[g].pdgId) < 7) {
					//	genParton.push_back(&genparticlehelper[g]);
					//	cout << "Found Parton" << endl;
					//}
					
					 cout << "ParticleID: " << (int) genparticlehelper[g].pdgId << " ParticleStatus: " << (int) genparticlehelper[g].status << " Pt: " << genparticlehelper[g].pt << endl;
				}

				//cout << "#-------------" << endl;
				//cout << "genElectron.size() " << genElectron.size() << endl;
				//cout << "genMuon.size() " << genMuon.size() << endl;
				//cout << "genTau.size() " << genTau.size() << endl;
				//if ((genElectron.size() == 0 ) && ( genMuon.size() == 0 )) {
				//	cout << "ATTENZIONE: genTau.size() " << genTau.size() << endl;
				//	if (genTau.size() == 0 ) {zerocounter++;}
				//}

				//cout << "Status: " << genparticlehelper[g].status << endl;



				unsigned int firstMother = 99999;
				unsigned int lastMother = 99999;


				for (unsigned int g = 0; g < genparticlehelper.size(); g++){

					if (  !((fabs(genparticlehelper[g].status) > 20 ) && (fabs(genparticlehelper[g].status) < 30) )  ) continue;
					//if ( (fabs(genparticlehelper[g].pdgId) == 1000023) || (fabs(genparticlehelper[g].pdgId) == 1000024) ){ 
					if ( fabs(genparticlehelper[g].pdgId) > 1000000) { 
					
						cout<<"found!!!"<<endl; 
						cout << "From the selected susy particle. PDGID: " << (int)genparticlehelper[g].pdgId << " Status: " << genparticlehelper[g].status << " Pt: " << genparticlehelper[g].pt << endl;
						firstMother = genparticlehelper[g].firstMother;
						lastMother = genparticlehelper[g].lastMother;
						break;
					
					}
				}


				cout << "firstMotherindex: " << firstMother << endl;

				unsigned int firstDaughter = 99999;
				unsigned int lastDaughter = 99999;

				if (firstMother < 99999) {
					if (genparticlehelper[firstMother].firstDaughter != -1) firstDaughter = genparticlehelper[firstMother].firstDaughter;
					if (genparticlehelper[firstMother].lastDaughter != -1) lastDaughter= genparticlehelper[firstMother].lastDaughter;

					for ( unsigned int g = firstDaughter; g < lastDaughter + 1; g++) {
						//if (  !(fabs(genparticlehelper[g].status) == 3)  ) continue;
						if (fabs(genparticlehelper[g].pdgId) < 7) {genParton.push_back(&genparticlehelper[g]);}
					}

				}

				if ( (firstMother < 99999) && (lastMother < 99999) && (firstDaughter < 99999) && (lastDaughter < 99999) ) {

					cout << "Looping over the selected susy particle mother and daughters pdg ids" << endl;
					for ( unsigned int g = firstMother; g < lastMother + 1; g++) { 
						cout << "MotherID: " << (int) genparticlehelper[g].pdgId << " MotherStatus: " << (int) genparticlehelper[g].status << " Pt: " << genparticlehelper[g].pt << endl;
					}
					for ( unsigned int g = firstDaughter; g < lastDaughter + 1; g++) { 
						cout << "DaughterID: " << (int) genparticlehelper[g].pdgId << " DaughterStatus: " << (int) genparticlehelper[g].status << " Pt: " << genparticlehelper[g].pt << endl;
					}
			
				}
				//Check for correct stau decay chain

				bool hasC1Mother = false;
				bool hasN2Mother = false;
				bool hasTauDaughter = false;

				unsigned int staufirstDaughter = 0;
				unsigned int staulastDaughter = 0;
				unsigned int staufirstMother = 0;
				unsigned int staulastMother = 0;

				for (unsigned int g = 0; g < genparticlehelper.size(); g++){

					hasC1Mother = false;
					hasN2Mother = false;
					hasTauDaughter = false;

					staufirstDaughter = 0;
					staulastDaughter = 0;
					staufirstMother = 0;
					staulastMother = 0;

					//if (  !(fabs(genparticlehelper[g].status) == 3)  ) continue;
					if (!(fabs(genparticlehelper[g].pdgId) == 1000015)) continue;

					staufirstDaughter = genparticlehelper[g].firstDaughter;
					staulastDaughter = genparticlehelper[g].lastDaughter;
					staufirstMother = genparticlehelper[g].firstMother;
					staulastMother = genparticlehelper[g].lastMother;

					for (unsigned int gg = staufirstDaughter; gg < staulastDaughter + 1; gg++) {
						if (fabs(genparticlehelper[gg].pdgId) == 15) hasTauDaughter = true; 
					}

					for (unsigned int gg = staufirstMother; gg < staulastMother + 1; gg++) {
						if (fabs(genparticlehelper[gg].pdgId) == 1000024)  hasC1Mother = true;
						if (fabs(genparticlehelper[gg].pdgId) == 1000023)  hasN2Mother = true;
						//cout<<"Mother PDGID: "<< genparticlehelper[gg].pdgId << endl;
					}

					//cout << "------------------------------------"<< endl;
					//cout << "hasTauDaughter: " << hasTauDaughter << " hasC1Mother: " << hasC1Mother << " hasN2Mother: " << hasN2Mother << endl;
					if ( hasTauDaughter && hasC1Mother) {h_decaychain->Fill("C1->Stau->Tau", weight);
						//cout<<"C1->Stau->Tau"<<endl;
					} 
					else if (hasTauDaughter && hasN2Mother) {h_decaychain->Fill("N2->Stau->Tau", weight);
						//cout<<"N2->Stau->Tau"<<endl;
					} 
					else {h_decaychain->Fill("noChain", weight);
						//cout<<"noChain"<<endl;
					}


				}

				//Selection of Gen Tau 1,2

				double tau1pt = 0.;
				double tau2pt = 0.;
				unsigned int tau1index = 99999;
				unsigned int tau2index = 99999;

				for (unsigned int i = 0; i < genTau.size(); i++) {
					if (genTau[i]->pt > tau1pt) {tau1pt = genTau[i]->pt; tau1index = i;}
				}

				for (unsigned int i = 0; i < genTau.size(); i++) {
					if ((genTau[i]->pt > tau2pt) && (genTau[i]->pt < tau1pt)) {tau2pt = genTau[i]->pt; tau2index = i;}
				}

				//Selection of Gen Electron 1,2

				double electron1pt = 0.;
				double electron2pt = 0.;
				unsigned int electron1index = 99999;
				unsigned int electron2index = 99999;

				for (unsigned int i = 0; i < genElectron.size(); i++) {
					if (genElectron[i]->pt > electron1pt) {electron1pt = genElectron[i]->pt; electron1index = i;}
				}

				for (unsigned int i = 0; i < genElectron.size(); i++) {
					if ((genElectron[i]->pt > electron2pt) && (genElectron[i]->pt < electron1pt)) {electron2pt = genElectron[i]->pt; electron2index = i;}
				}

				//Selection of Gen Muon 1,2

				double muon1pt = 0.;
				double muon2pt = 0.;
				unsigned int muon1index = 99999;
				unsigned int muon2index = 99999;

				for (unsigned int i = 0; i < genMuon.size(); i++) {
					if (genMuon[i]->pt > muon1pt) {muon1pt = genMuon[i]->pt; muon1index = i;}
				}

				for (unsigned int i = 0; i < genMuon.size(); i++) {
					if ((genMuon[i]->pt > muon2pt) && (genMuon[i]->pt < muon1pt)) {muon2pt = genMuon[i]->pt; muon2index = i;}
				}

				//Selection of Gen Parton 1,2

				double parton1pt = 0.;
				double parton2pt = 0.;
				unsigned int parton1index = 99999;
				unsigned int parton2index = 99999;

				for (unsigned int i = 0; i < genParton.size(); i++) {
					if (genParton[i]->pt > parton1pt) {parton1pt = genParton[i]->pt; parton1index = i;}
				}

				for (unsigned int i = 0; i < genParton.size(); i++) {
					if ((genParton[i]->pt > parton2pt) && (genParton[i]->pt < parton1pt)) {parton2pt = genParton[i]->pt; parton2index = i;}
				}

				cout << "Parton 1 Pt: " << parton1pt << endl;
				cout << "Parton 2 Pt: " << parton2pt << endl;

				//Fill Vertex Z Plot

				h_vertexz->Fill(vertex[0].z);

				//Fill C1 Plots

				for (unsigned int g = 0; g < genC1nos.size(); g++) {
					h_C1pt->Fill(genC1nos[g]->pt,weight);
					h_C1eta->Fill(genC1nos[g]->eta,weight);
				}

				//Fill N2 Plots

				for (unsigned int g = 0; g < genN2nos.size(); g++) {
					h_N2pt->Fill(genN2nos[g]->pt,weight);
					h_N2eta->Fill(genN2nos[g]->eta,weight);
				}

				//Fill Electron Plots			

				if (electron1index < 99999) {
					h_electron1pt->Fill(genElectron[electron1index]->pt,weight);
					h_electron1eta->Fill(genElectron[electron1index]->eta,weight);
				}

				if (electron2index < 99999) {
					h_electron2pt->Fill(genElectron[electron2index]->pt,weight);
					h_electron2eta->Fill(genElectron[electron2index]->eta,weight);
				}

				if ((electron1index < 99999) && (electron2index < 99999)){

					TLorentzVector electron1_4v;
					TLorentzVector electron2_4v;		  

					electron1_4v.SetPtEtaPhiM(genElectron[electron1index]->pt, genElectron[electron1index]->eta, genElectron[electron1index]->phi, genElectron[electron1index]->mass);
					electron2_4v.SetPtEtaPhiM(genElectron[electron2index]->pt, genElectron[electron2index]->eta, genElectron[electron2index]->phi, genElectron[electron2index]->mass);

					TLorentzVector dielectron_4v = electron1_4v + electron2_4v;
					h_dielectroninvariantmass->Fill(dielectron_4v.M(),weight);
				}

				//Fill Muon Plots			

				if (muon1index < 99999) {
					h_muon1pt->Fill(genMuon[muon1index]->pt,weight);
					h_muon1eta->Fill(genMuon[muon1index]->eta,weight);
				}

				if (muon2index < 99999) {
					h_muon2pt->Fill(genMuon[muon2index]->pt,weight);
					h_muon2eta->Fill(genMuon[muon2index]->eta,weight);
				}

				if ((muon1index < 99999) && (muon2index < 99999)){

					TLorentzVector muon1_4v;
					TLorentzVector muon2_4v;		  

					muon1_4v.SetPtEtaPhiM(genMuon[muon1index]->pt, genMuon[muon1index]->eta, genMuon[muon1index]->phi, genMuon[muon1index]->mass);
					muon2_4v.SetPtEtaPhiM(genMuon[muon2index]->pt, genMuon[muon2index]->eta, genMuon[muon2index]->phi, genMuon[muon2index]->mass);

					TLorentzVector dimuon_4v = muon1_4v + muon2_4v;
					h_dimuoninvariantmass->Fill(dimuon_4v.M(),weight);
				}

				//Fill Tau Plots			

				if (tau1index < 99999) {
					h_tau1pt->Fill(genTau[tau1index]->pt,weight);
					h_tau1eta->Fill(genTau[tau1index]->eta,weight);
				}

				if (tau2index < 99999) {
					h_tau2pt->Fill(genTau[tau2index]->pt,weight);
					h_tau2eta->Fill(genTau[tau2index]->eta,weight);
				}

				if ((tau1index < 99999) && (tau2index < 99999)){

					TLorentzVector tau1_4v;
					TLorentzVector tau2_4v;		  

					tau1_4v.SetPtEtaPhiM(genTau[tau1index]->pt, genTau[tau1index]->eta, genTau[tau1index]->phi, genTau[tau1index]->mass);
					tau2_4v.SetPtEtaPhiM(genTau[tau2index]->pt, genTau[tau2index]->eta, genTau[tau2index]->phi, genTau[tau2index]->mass);

					TLorentzVector ditau_4v = tau1_4v + tau2_4v;
					h_ditauinvariantmass->Fill(ditau_4v.M(),weight);
				}

				//Fill Parton Plots			

				h_njet->Fill(genParton.size(),weight);

				if (parton1index < 99999) {
					h_jet1pt->Fill(genParton[parton1index]->pt,weight);
					h_jet1eta->Fill(genParton[parton1index]->eta,weight);
				}

				if (parton2index < 99999) {
					h_jet2pt->Fill(genParton[parton2index]->pt,weight);
					h_jet2eta->Fill(genParton[parton2index]->eta,weight);
				}

				if ((parton1index < 99999) && (parton2index < 99999)){

					TLorentzVector jet1_4v;
					TLorentzVector jet2_4v;		  

					jet1_4v.SetPtEtaPhiM(genParton[parton1index]->pt, genParton[parton1index]->eta, genParton[parton1index]->phi, genParton[parton1index]->mass);
					jet2_4v.SetPtEtaPhiM(genParton[parton2index]->pt, genParton[parton2index]->eta, genParton[parton2index]->phi, genParton[parton2index]->mass);

					TLorentzVector dijet_4v = jet1_4v + jet2_4v;
					h_dijetinvariantmass->Fill(dijet_4v.M(),weight);
					double dijetdeltaeta = fabs(genParton[parton1index]->eta - genParton[parton2index]->eta);
					h_dijetdeltaeta -> Fill(dijetdeltaeta ,weight);
				}

				// Fill MET Plot

				TLorentzVector met_4v;
				TLorentzVector temp_4v;

				for (unsigned int i = 0; i < genInvis.size(); i++) {

					temp_4v.SetPtEtaPhiM(genInvis[i]->pt, genInvis[i]->eta, genInvis[i]->phi, genInvis[i]->mass);
					met_4v+= temp_4v;

				}

				h_met->Fill(met_4v.Pt(),weight);

				break;		

			}


		}

	cout << "eventcounter: " << eventcounter << endl;
	cout << "zerocounter: " << zerocounter << endl;

	stream.close();
	ofile.close();
	return 0;
}

