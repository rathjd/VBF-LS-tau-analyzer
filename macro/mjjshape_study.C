#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


struct sampleplots_str {
	string samplename;
	TH1F* h1_SRplot;
	TH1F* h1_CR2plot;
	TH1F* h1_CR3plot;
	TH1F* h1_CR4plot;
	TH1F* h1_CR5plot;
	TH1F* h1_CR6plot;
	TH1F* h1_CR7plot;
	TH1F* h1_CR8plot;
};

void addsamplesplots(sampleplots_str *sample_sampleplots_str1, sampleplots_str *sample_sampleplots_str2) {

	sample_sampleplots_str1->h1_SRplot->Add(sample_sampleplots_str2->h1_SRplot);
	sample_sampleplots_str1->h1_CR2plot->Add(sample_sampleplots_str2->h1_CR2plot);
	sample_sampleplots_str1->h1_CR3plot->Add(sample_sampleplots_str2->h1_CR3plot);
	sample_sampleplots_str1->h1_CR4plot->Add(sample_sampleplots_str2->h1_CR4plot);
	sample_sampleplots_str1->h1_CR5plot->Add(sample_sampleplots_str2->h1_CR5plot);
	sample_sampleplots_str1->h1_CR6plot->Add(sample_sampleplots_str2->h1_CR6plot);
	sample_sampleplots_str1->h1_CR7plot->Add(sample_sampleplots_str2->h1_CR7plot);
	sample_sampleplots_str1->h1_CR8plot->Add(sample_sampleplots_str2->h1_CR8plot);

}

TH1F* normalizeplot(TH1F* plot) {
	double eventsnumber = plot->Integral(0 , -1 );
	if (eventsnumber > 0. ) plot->Scale(1./eventsnumber);
	return plot;	
}

void normalizesampleplots (sampleplots_str *sample_sampleplots_str){

	sample_sampleplots_str->h1_SRplot = normalizeplot(sample_sampleplots_str->h1_SRplot);
        sample_sampleplots_str->h1_CR2plot = normalizeplot(sample_sampleplots_str->h1_CR2plot);
        sample_sampleplots_str->h1_CR3plot = normalizeplot(sample_sampleplots_str->h1_CR3plot);
        sample_sampleplots_str->h1_CR4plot = normalizeplot(sample_sampleplots_str->h1_CR4plot);
        sample_sampleplots_str->h1_CR5plot = normalizeplot(sample_sampleplots_str->h1_CR5plot);
        sample_sampleplots_str->h1_CR6plot = normalizeplot(sample_sampleplots_str->h1_CR6plot);
        sample_sampleplots_str->h1_CR7plot = normalizeplot(sample_sampleplots_str->h1_CR7plot);
        sample_sampleplots_str->h1_CR8plot = normalizeplot(sample_sampleplots_str->h1_CR8plot);
}

void mjjplots_init (TFile* inputfile, sampleplots_str *sample_sampleplots_str, bool isLSchannel, string plotname) {

	if (isLSchannel) {
		sample_sampleplots_str->h1_SRplot = ((TH1F*)(inputfile->Get(("LS_SignalRegion/" + plotname).c_str())));
		sample_sampleplots_str->h1_CR2plot = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_2TightIso_CR2/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR3plot = ((TH1F*)(inputfile->Get(("LS_Central_1TightIso_CR3/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR4plot = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_1TightIso_CR4/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR5plot = ((TH1F*)(inputfile->Get(("LS_Central_AntiTightIso_CR5/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR6plot = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_AntiTightIso_CR6/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR7plot = ((TH1F*)(inputfile->Get(("LS_Central_AntiMediumIso_CR7/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR8plot = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_AntiMediumIso_CR8/"+plotname).c_str())));
	}

	if (!isLSchannel) {
		sample_sampleplots_str->h1_SRplot = ((TH1F*)(inputfile->Get(("OS_SignalRegion/" + plotname).c_str())));
		sample_sampleplots_str->h1_CR2plot = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_2TightIso_CR2/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR3plot = ((TH1F*)(inputfile->Get(("OS_Central_1TightIso_CR3/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR4plot = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_1TightIso_CR4/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR5plot = ((TH1F*)(inputfile->Get(("OS_Central_AntiTightIso_CR5/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR6plot = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_AntiTightIso_CR6/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR7plot = ((TH1F*)(inputfile->Get(("OS_Central_AntiMediumIso_CR7/"+plotname).c_str())));
		sample_sampleplots_str->h1_CR8plot = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_AntiMediumIso_CR8/"+plotname).c_str())));
	}

}

void mjjshapestudy(bool isLSchannel, string plotname) {

	TFile *_allData = TFile::Open("allData.root");
	TFile *_allDY = TFile::Open("allDY.root");
	TFile *_allVV = TFile::Open("allVV.root");
	TFile *_allW = TFile::Open("allW.root");
	TFile *_allT = TFile::Open("allT.root");
	TFile *_allTTbar = TFile::Open("allTTbar.root");
	TFile *_allHiggs = TFile::Open("allHiggs.root");
	TFile *_allQCD = TFile::Open("allQCD.root");

	sampleplots_str Data_sampleplots;
	Data_sampleplots.samplename = "Data";

	sampleplots_str AllMC_sampleplots;
	AllMC_sampleplots.samplename = "AllMC";

	sampleplots_str DY_sampleplots;
	DY_sampleplots.samplename = "Drell-Yan";

	sampleplots_str VV_sampleplots;
	VV_sampleplots.samplename = "VV";

	sampleplots_str W_sampleplots;
	W_sampleplots.samplename = "W+Jets";

	sampleplots_str T_sampleplots;
	T_sampleplots.samplename = "Single t";

	sampleplots_str TTbar_sampleplots;
	TTbar_sampleplots.samplename = "TTbar";

	sampleplots_str Higgs_sampleplots;
	Higgs_sampleplots.samplename = "Higgs";

	sampleplots_str QCD_sampleplots;
	QCD_sampleplots.samplename = "QCD";

	mjjplots_init(_allDY, &AllMC_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allDY, &DY_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allVV, &VV_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allW, &W_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allT, &T_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allTTbar, &TTbar_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allHiggs, &Higgs_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allQCD, &QCD_sampleplots, isLSchannel, plotname);
	mjjplots_init(_allData, &Data_sampleplots, isLSchannel, plotname);
	
	normalizesampleplots (&Data_sampleplots);

	addsamplesplots(&AllMC_sampleplots , &VV_sampleplots);
	addsamplesplots(&AllMC_sampleplots , &W_sampleplots);
	addsamplesplots(&AllMC_sampleplots , &T_sampleplots);
	addsamplesplots(&AllMC_sampleplots , &TTbar_sampleplots);
	addsamplesplots(&AllMC_sampleplots , &Higgs_sampleplots);
	addsamplesplots(&AllMC_sampleplots , &QCD_sampleplots);
	normalizesampleplots (&AllMC_sampleplots);


	TCanvas* c1 = new TCanvas("c1","c1",1);
	c1->cd();

	Data_sampleplots.h1_CR3plot->SetStats(0);
	Data_sampleplots.h1_CR3plot->SetTitle("M_{jj} distribution for different #tau isolation regions");
	Data_sampleplots.h1_CR5plot->SetLineColor(kBlack);	
	Data_sampleplots.h1_CR3plot->Draw();
	Data_sampleplots.h1_CR5plot->SetLineColor(kRed);	
	Data_sampleplots.h1_CR5plot->Draw("same");	
	Data_sampleplots.h1_CR7plot->SetLineColor(kGreen);	
	Data_sampleplots.h1_CR7plot->Draw("same");

	TLegend* legdata = new TLegend(0.6,0.65,0.88,0.85);
	legdata->AddEntry(Data_sampleplots.h1_CR3plot, "Data CR3", "l");
	legdata->AddEntry(Data_sampleplots.h1_CR5plot, "Data CR5", "l");
	legdata->AddEntry(Data_sampleplots.h1_CR7plot, "Data CR7", "l");
	legdata->Draw("same");

	c1->SaveAs("mjjshapestab_vs_tauiso_data.pdf");
	c1->Clear();

	AllMC_sampleplots.h1_CR3plot->SetStats(0);
	AllMC_sampleplots.h1_CR3plot->SetTitle("M_{jj} distribution for different #tau isolation regions");
	AllMC_sampleplots.h1_CR5plot->SetLineColor(kBlack);	
	AllMC_sampleplots.h1_CR3plot->Draw();
	AllMC_sampleplots.h1_CR5plot->SetLineColor(kRed);	
	AllMC_sampleplots.h1_CR5plot->Draw("same");	
	AllMC_sampleplots.h1_CR7plot->SetLineColor(kGreen);	
	AllMC_sampleplots.h1_CR7plot->Draw("same");

	TLegend* legmc = new TLegend(0.6,0.65,0.88,0.85);
	legmc->AddEntry(AllMC_sampleplots.h1_CR3plot, "all MC CR3", "l");
	legmc->AddEntry(AllMC_sampleplots.h1_CR5plot, "all MC CR5", "l");
	legmc->AddEntry(AllMC_sampleplots.h1_CR7plot, "all MC CR7", "l");
	legmc->Draw("same");

	c1->SaveAs("mjjshapestab_vs_tauiso_mc.pdf");
	c1->Clear();

}

