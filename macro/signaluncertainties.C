#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double ratioerror(double num, double num_err, double den, double den_err) {

	return sqrt( pow(    (num_err/den)     ,2) + pow(   ((num*den_err)/(den*den))    ,2)   );
}

void signalefficiency(bool isLSchannel) {

	string channelstring;
	if (isLSchannel) channelstring = "LS_SignalRegion/"; 
	if (!isLSchannel) channelstring = "OS_SignalRegion/"; 

	//load files
	TFile *_Stau095_Chargino100 = TFile::Open("VBFC1pmN2_C1ToTau_N2ToTauTau_LSP000_Stau095_Chargino100_FastSim.root");
	TFile *_Stau145_Chargino150 = TFile::Open("VBFC1pmN2_C1ToTau_N2ToTauTau_LSP000_Stau145_Chargino150_FastSim.root");
	TFile *_Stau195_Chargino200 = TFile::Open("VBFC1pmN2_C1ToTau_N2ToTauTau_LSP000_Stau195_Chargino200_FastSim.root");
	TFile *_Stau245_Chargino250 = TFile::Open("VBFC1pmN2_C1ToTau_N2ToTauTau_LSP000_Stau245_Chargino250_FastSim.root");
	TFile *_Stau295_Chargino300= TFile::Open("VBFC1pmN2_C1ToTau_N2ToTauTau_LSP000_Stau295_Chargino300_FastSim.root");

	//load errorsi
	double Stau095_Chargino100_num = ((TH1F*)(_Stau095_Chargino100->Get((channelstring+"counts").c_str())))->GetBinContent(14);
	double Stau095_Chargino100_den = ((TH1F*)(_Stau095_Chargino100->Get((channelstring+"counts").c_str())))->GetBinContent(1);
	double Stau095_Chargino100_num_err = ((TH1F*)(_Stau095_Chargino100->Get((channelstring+"counts").c_str())))->GetBinError(14);
	double Stau095_Chargino100_den_err = ((TH1F*)(_Stau095_Chargino100->Get((channelstring+"counts").c_str())))->GetBinError(1);

	double Stau145_Chargino150_num = ((TH1F*)(_Stau145_Chargino150->Get((channelstring+"counts").c_str())))->GetBinContent(14);
	double Stau145_Chargino150_den = ((TH1F*)(_Stau145_Chargino150->Get((channelstring+"counts").c_str())))->GetBinContent(1);
	double Stau145_Chargino150_num_err = ((TH1F*)(_Stau145_Chargino150->Get((channelstring+"counts").c_str())))->GetBinError(14);
	double Stau145_Chargino150_den_err = ((TH1F*)(_Stau145_Chargino150->Get((channelstring+"counts").c_str())))->GetBinError(1);

	double Stau195_Chargino200_num = ((TH1F*)(_Stau195_Chargino200->Get((channelstring+"counts").c_str())))->GetBinContent(14);
	double Stau195_Chargino200_den = ((TH1F*)(_Stau195_Chargino200->Get((channelstring+"counts").c_str())))->GetBinContent(1);
	double Stau195_Chargino200_num_err = ((TH1F*)(_Stau195_Chargino200->Get((channelstring+"counts").c_str())))->GetBinError(14);
	double Stau195_Chargino200_den_err = ((TH1F*)(_Stau195_Chargino200->Get((channelstring+"counts").c_str())))->GetBinError(1);

	double Stau245_Chargino250_num = ((TH1F*)(_Stau245_Chargino250->Get((channelstring+"counts").c_str())))->GetBinContent(14);
	double Stau245_Chargino250_den = ((TH1F*)(_Stau245_Chargino250->Get((channelstring+"counts").c_str())))->GetBinContent(1);
	double Stau245_Chargino250_num_err = ((TH1F*)(_Stau245_Chargino250->Get((channelstring+"counts").c_str())))->GetBinError(14);
	double Stau245_Chargino250_den_err = ((TH1F*)(_Stau245_Chargino250->Get((channelstring+"counts").c_str())))->GetBinError(1);

	double Stau295_Chargino300_num = ((TH1F*)(_Stau295_Chargino300->Get((channelstring+"counts").c_str())))->GetBinContent(14);
	double Stau295_Chargino300_den = ((TH1F*)(_Stau295_Chargino300->Get((channelstring+"counts").c_str())))->GetBinContent(1);
	double Stau295_Chargino300_num_err = ((TH1F*)(_Stau295_Chargino300->Get((channelstring+"counts").c_str())))->GetBinError(14);
	double Stau295_Chargino300_den_err = ((TH1F*)(_Stau295_Chargino300->Get((channelstring+"counts").c_str())))->GetBinError(1);

	double Stau095_Chargino100_eff = Stau095_Chargino100_num / Stau095_Chargino100_den;
	double Stau145_Chargino150_eff = Stau145_Chargino150_num / Stau145_Chargino150_den;
	double Stau195_Chargino200_eff = Stau195_Chargino200_num / Stau195_Chargino200_den;
	double Stau245_Chargino250_eff = Stau245_Chargino250_num / Stau245_Chargino250_den;
	double Stau295_Chargino300_eff = Stau295_Chargino300_num / Stau295_Chargino300_den;
	double Stau095_Chargino100_err = ratioerror(Stau095_Chargino100_num, Stau095_Chargino100_num_err, Stau095_Chargino100_den, Stau095_Chargino100_den_err);
	double Stau145_Chargino150_err = ratioerror(Stau145_Chargino150_num, Stau145_Chargino150_num_err, Stau145_Chargino150_den, Stau145_Chargino150_den_err);
	double Stau195_Chargino200_err = ratioerror(Stau195_Chargino200_num, Stau195_Chargino200_num_err, Stau195_Chargino200_den, Stau195_Chargino200_den_err);
	double Stau245_Chargino250_err = ratioerror(Stau245_Chargino250_num, Stau245_Chargino250_num_err, Stau245_Chargino250_den, Stau245_Chargino250_den_err);
	double Stau295_Chargino300_err = ratioerror(Stau295_Chargino300_num, Stau295_Chargino300_num_err, Stau295_Chargino300_den, Stau295_Chargino300_den_err);
	
	cout << "Stau095_Chargino100: " << Stau095_Chargino100_eff << " +- " << Stau095_Chargino100_err << endl;
	cout << "Stau145_Chargino150: " << Stau145_Chargino150_eff << " +- " << Stau145_Chargino150_err << endl;
	cout << "Stau195_Chargino200: " << Stau195_Chargino200_eff << " +- " << Stau195_Chargino200_err << endl;
	cout << "Stau245_Chargino250: " << Stau245_Chargino250_eff << " +- " << Stau245_Chargino250_err << endl;
	cout << "Stau295_Chargino300: " << Stau295_Chargino300_eff << " +- " << Stau295_Chargino300_err << endl;

	TH1F* h_efficiencies = new TH1F("counts", "", 1,0,1);
	h_efficiencies->SetBit(TH1::kCanRebin);
	h_efficiencies->SetStats(0);

	if (isLSchannel) h_efficiencies->SetTitle("Signal efficiency for LS channel");
	if (!isLSchannel) h_efficiencies->SetTitle("Signal efficiency for OS channel");
	h_efficiencies->GetXaxis()->SetTitle("M(#chi^{1}) [GeV] [ M(#chi^{1}) - M(#tilde{#tau}) ]");
	h_efficiencies->GetYaxis()->SetTitle("%");
	h_efficiencies->Fill("100",Stau095_Chargino100_eff*100.);
	h_efficiencies->SetBinError(1,Stau095_Chargino100_err*100.);
	h_efficiencies->Fill("150",Stau145_Chargino150_eff*100.);
	h_efficiencies->SetBinError(2,Stau145_Chargino150_err*100.);
	h_efficiencies->Fill("200",Stau195_Chargino200_eff*100.);
	h_efficiencies->SetBinError(3,Stau195_Chargino200_err*100.);
	h_efficiencies->Fill("250",Stau245_Chargino250_eff*100.);
	h_efficiencies->SetBinError(4,Stau245_Chargino250_err*100.);
	h_efficiencies->Fill("300",Stau295_Chargino300_eff*100.);
	h_efficiencies->SetBinError(5,Stau295_Chargino300_err*100.);

	TCanvas* c1 = new TCanvas("c1","c1",1);
	c1->cd();

	h_efficiencies->Draw();

	if (isLSchannel) c1->SaveAs("LS_signalefficiency.pdf");
	if (!isLSchannel) c1->SaveAs("OS_signalefficiency.pdf");
	c1->Clear();


}

