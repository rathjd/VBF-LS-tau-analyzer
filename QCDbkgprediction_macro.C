{
#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>


cout<<"begin"<<endl;

TFile _file0 ("alldata.root","UPDATE");

((TH1F*)(_file0->Get("SignalRegion/h_dijetinvariantmass")))->Clone("h1_dijetinvariantmass_onetight");
((TH1F*)(_file0->Get("SignalRegion/h_dijetinvariantmass")))->Clone("h1_dijetinvariantmass_antitight");
((TH1F*)(_file0->Get("SignalRegion/h_dijetinvariantmass")))->Clone("h1_dijetinvariantmass_antimedium");
((TH1F*)(_file0->Get("SignalRegion/h_dijetinvariantmass")))->Clone("h1_dijetinvariantmass_antiloose");

Int_t nbins = ((TH1F*)(_file0->Get("SignalRegion/h_dijetinvariantmass")))->GetXaxis()->GetNbins();

for (Int_t i = 0; i < nbins ; i ++) {

	Double_t eff_onetight = ((TH1F*)(_file0->Get("Central_1TightIso_CR3/h_dijetinvariantmass")))->GetBinContent(i) / (((TH1F*)(_file0->Get("Central_1TightIso_CR3/h_dijetinvariantmass")))->GetBinContent(i) + ((TH1F*)(_file0->Get("Central_invertedVBF_1TightIso_CR4/h_dijetinvariantmass")))->GetBinContent(i));
	Double_t eff_antitight = ((TH1F*)(_file0->Get("Central_AntiTightIso_CR5/h_dijetinvariantmass")))->GetBinContent(i) / (((TH1F*)(_file0->Get("Central_AntiTightIso_CR5/h_dijetinvariantmass")))->GetBinContent(i) + ((TH1F*)(_file0->Get("Central_invertedVBF_AntiTightIso_CR6/h_dijetinvariantmass")))->GetBinContent(i));
	Double_t eff_antimedium = ((TH1F*)(_file0->Get("Central_AntiMediumIso_CR7/h_dijetinvariantmass")))->GetBinContent(i) / (((TH1F*)(_file0->Get("Central_AntiMediumIso_CR7/h_dijetinvariantmass")))->GetBinContent(i) + ((TH1F*)(_file0->Get("Central_invertedVBF_AntiMediumIso_CR8/h_dijetinvariantmass")))->GetBinContent(i));
	Double_t eff_antiloose = ((TH1F*)(_file0->Get("Central_AntiLooseIso_CR9/h_dijetinvariantmass")))->GetBinContent(i) / (((TH1F*)(_file0->Get("Central_AntiLooseIso_CR9/h_dijetinvariantmass")))->GetBinContent(i) + ((TH1F*)(_file0->Get("Central_AntiLooseIso_CR10/h_dijetinvariantmass")))->GetBinContent(i));

	Double_t nbkg_onetight = ((TH1F*)(_file0->Get("Central_invertedVBF_2TightIso_CR2/h_dijetinvariantmass")))->GetBinContent(i) * eff_onetight;
	Double_t nbkg_antitight = ((TH1F*)(_file0->Get("Central_invertedVBF_2TightIso_CR2/h_dijetinvariantmass")))->GetBinContent(i) * eff_antitight;
	Double_t nbkg_antimedium = ((TH1F*)(_file0->Get("Central_invertedVBF_2TightIso_CR2/h_dijetinvariantmass")))->GetBinContent(i) * eff_antimedium;
	Double_t nbkg_antiloose = ((TH1F*)(_file0->Get("Central_invertedVBF_2TightIso_CR2/h_dijetinvariantmass")))->GetBinContent(i) * eff_antiloose;
	

if (nbkg_onetight >= 0.) ((TH1F*)(_file0->Get("h1_dijetinvariantmass_onetight")))->SetBinContent(i,nbkg_onetight);
if (nbkg_antitight >= 0.) ((TH1F*)(_file0->Get("h1_dijetinvariantmass_antitight")))->SetBinContent(i,nbkg_antitight);
if (nbkg_antimedium >= 0.) ((TH1F*)(_file0->Get("h1_dijetinvariantmass_antimedium")))->SetBinContent(i,nbkg_antimedium);
if (nbkg_antiloose >= 0.) ((TH1F*)(_file0->Get("h1_dijetinvariantmass_antiloose")))->SetBinContent(i,nbkg_antiloose);

}

Double_t nqcdevt_CR2 = ((TH1F*)(_file0->Get("Central_invertedVBF_2TightIso_CR2/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR3 = ((TH1F*)(_file0->Get("Central_1TightIso_CR3/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR4 = ((TH1F*)(_file0->Get("Central_invertedVBF_1TightIso_CR4/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR5 = ((TH1F*)(_file0->Get("Central_AntiTightIso_CR5/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR6 = ((TH1F*)(_file0->Get("Central_invertedVBF_AntiTightIso_CR6/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR7 = ((TH1F*)(_file0->Get("Central_AntiMediumIso_CR7/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR8 = ((TH1F*)(_file0->Get("Central_invertedVBF_AntiMediumIso_CR8/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR9 = ((TH1F*)(_file0->Get("Central_AntiLooseIso_CR9/h_dijetinvariantmass")))->GetEntries(); 
Double_t nqcdevt_CR10 = ((TH1F*)(_file0->Get("Central_AntiLooseIso_CR10/h_dijetinvariantmass")))->GetEntries(); 

cout<< "# of events in CR_2: " << nqcdevt_CR2 << endl; 
cout<< "# of events in CR_3: " << nqcdevt_CR3 << endl; 
cout<< "# of events in CR_4: " << nqcdevt_CR4 << endl; 
cout<< "# of events in CR_5: " << nqcdevt_CR5 << endl; 
cout<< "# of events in CR_6: " << nqcdevt_CR6 << endl; 
cout<< "# of events in CR_7: " << nqcdevt_CR7 << endl; 
cout<< "# of events in CR_8: " << nqcdevt_CR8 << endl; 
cout<< "# of events in CR_9: " << nqcdevt_CR9 << endl; 
cout<< "# of events in CR_10: " << nqcdevt_CR10 << endl; 

((TH1F*)(_file0->Get("h1_dijetinvariantmass_onetight")))->Write();
((TH1F*)(_file0->Get("h1_dijetinvariantmass_antitight")))->Write();
((TH1F*)(_file0->Get("h1_dijetinvariantmass_antimedium")))->Write();
((TH1F*)(_file0->Get("h1_dijetinvariantmass_antiloose")))->Write();

}
