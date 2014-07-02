#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


struct eventcount_str {
	string samplename;
	double SRcounts;
	double SRcounts_err;
	double CR2counts;
	double CR2counts_err;
	double CR3counts;
	double CR3counts_err;
	double CR4counts;
	double CR4counts_err;
	double CR5counts;
	double CR5counts_err;
	double CR6counts;
	double CR6counts_err;
	double CR7counts;
	double CR7counts_err;
	double CR8counts;
	double CR8counts_err;
};

double vbfefficiency(double evenCRcounts, double oddCRcounts, double evenCRnonQCDbg, double oddCRnonQCDbg){

	return ( (oddCRcounts - oddCRnonQCDbg) / ( (oddCRcounts - oddCRnonQCDbg) + (evenCRcounts - evenCRnonQCDbg) ));
}

double vbfefficiency_staterr(double evenCRcounts, double evenCRcounts_err,double oddCRcounts, double oddCRcounts_err, double evenCRnonQCDbg, double evenCRnonQCDbg_err, double oddCRnonQCDbg, double oddCRnonQCDbg_err) {
	double temp_evenCRcounts = evenCRcounts - evenCRnonQCDbg;
	double temp_evenCRcounts_err = sqrt( pow(evenCRcounts_err,2.) + pow(evenCRnonQCDbg_err,2.)  );
	double temp_oddCRcounts = oddCRcounts - oddCRnonQCDbg;
	double temp_oddCRcounts_err = sqrt( pow(oddCRcounts_err,2.) + pow(oddCRnonQCDbg_err,2.)  );
	return sqrt( pow(  (( temp_evenCRcounts * temp_oddCRcounts_err)/(pow((temp_oddCRcounts + temp_evenCRcounts),2.))), 2.)  + pow(  ((temp_oddCRcounts * temp_evenCRcounts_err)/(pow((temp_oddCRcounts + evenCRcounts),2.))), 2.)    );
}

double qcdbackgroundprediction(double CR2counts, double CR2nonqcdbg, double vbfefficiency) {
	return ( CR2counts - CR2nonqcdbg) * (vbfefficiency / (1. - vbfefficiency) );
}


double qcdbackgroundprediction_staterr(double CR2counts, double CR2counts_err, double CR2nonqcdbg, double CR2nonqcdbg_err, double vbfefficiency, double vbfefficiency_err) {
	double temp_CR2counts = CR2counts - CR2nonqcdbg;
	double temp_CR2counts_err = sqrt( pow(CR2counts_err,2.) + pow(CR2nonqcdbg_err,2.)  );
	return sqrt(  pow(   ((vbfefficiency * ( temp_CR2counts_err ) )/( 1. - vbfefficiency))    , 2.)   +   pow(   (( temp_CR2counts * vbfefficiency_err)/(pow( (1 - vbfefficiency) ,2.)))    , 2.)    );
}

double binerrors(TH1F* h1, int minMETbin, int maxMETbin){
	double temperror = 0;
	for (int i = minMETbin; i < maxMETbin + 1; i++){
	temperror = temperror + pow(h1->GetBinError(i),2.);
	}
	return sqrt(temperror);
}

void eventcount(TFile* inputfile, eventcount_str *sample_evtcount, bool isLSchannel, string plotname, double minMET, double maxMET){

	TH1F* h1_SRcounts;
	TH1F* h1_CR2counts;
	TH1F* h1_CR3counts;
	TH1F* h1_CR4counts;
	TH1F* h1_CR5counts;
	TH1F* h1_CR6counts;
	TH1F* h1_CR7counts;
	TH1F* h1_CR8counts;

	if (isLSchannel) {
		h1_SRcounts = ((TH1F*)(inputfile->Get(("LS_SignalRegion/" + plotname).c_str())));
		h1_CR2counts = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_2TightIso_CR2/"+plotname).c_str())));
		h1_CR3counts = ((TH1F*)(inputfile->Get(("LS_Central_1TightIso_CR3/"+plotname).c_str())));
		h1_CR4counts = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_1TightIso_CR4/"+plotname).c_str())));
		h1_CR5counts = ((TH1F*)(inputfile->Get(("LS_Central_AntiTightIso_CR5/"+plotname).c_str())));
		h1_CR6counts = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_AntiTightIso_CR6/"+plotname).c_str())));
		h1_CR7counts = ((TH1F*)(inputfile->Get(("LS_Central_AntiMediumIso_CR7/"+plotname).c_str())));
		h1_CR8counts = ((TH1F*)(inputfile->Get(("LS_Central_invertedVBF_AntiMediumIso_CR8/"+plotname).c_str())));
	}

	if (!isLSchannel) {
		h1_SRcounts = ((TH1F*)(inputfile->Get(("OS_SignalRegion/"+plotname).c_str())));
		h1_CR2counts = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_2TightIso_CR2/"+plotname).c_str())));
		h1_CR3counts = ((TH1F*)(inputfile->Get(("OS_Central_1TightIso_CR3/"+plotname).c_str())));
		h1_CR4counts = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_1TightIso_CR4/"+plotname).c_str())));
		h1_CR5counts = ((TH1F*)(inputfile->Get(("OS_Central_AntiTightIso_CR5/"+plotname).c_str())));
		h1_CR6counts = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_AntiTightIso_CR6/"+plotname).c_str())));
		h1_CR7counts = ((TH1F*)(inputfile->Get(("OS_Central_AntiMediumIso_CR7/"+plotname).c_str())));
		h1_CR8counts = ((TH1F*)(inputfile->Get(("OS_Central_invertedVBF_AntiMediumIso_CR8/"+plotname).c_str())));
	}

	int minMETbin = h1_SRcounts->FindBin(minMET);
	int maxMETbin = h1_SRcounts->FindBin(maxMET);

	sample_evtcount->SRcounts = h1_SRcounts->Integral(minMETbin,maxMETbin);
	sample_evtcount->CR2counts = h1_CR2counts->Integral(minMETbin,maxMETbin);
	sample_evtcount->CR3counts = h1_CR3counts->Integral(minMETbin,maxMETbin);
	sample_evtcount->CR4counts = h1_CR4counts->Integral(minMETbin,maxMETbin);
	sample_evtcount->CR5counts = h1_CR5counts->Integral(minMETbin,maxMETbin);
	sample_evtcount->CR6counts = h1_CR6counts->Integral(minMETbin,maxMETbin);
	sample_evtcount->CR7counts = h1_CR7counts->Integral(minMETbin,maxMETbin);
	sample_evtcount->CR8counts = h1_CR8counts->Integral(minMETbin,maxMETbin);

	sample_evtcount->SRcounts_err = binerrors(h1_SRcounts, minMETbin, maxMETbin);
	sample_evtcount->CR2counts_err = binerrors(h1_CR2counts, minMETbin, maxMETbin);
	sample_evtcount->CR3counts_err = binerrors(h1_CR3counts, minMETbin, maxMETbin); 
	sample_evtcount->CR4counts_err = binerrors(h1_CR4counts, minMETbin, maxMETbin);
	sample_evtcount->CR5counts_err = binerrors(h1_CR5counts, minMETbin, maxMETbin);
	sample_evtcount->CR6counts_err = binerrors(h1_CR6counts, minMETbin, maxMETbin);
	sample_evtcount->CR7counts_err = binerrors(h1_CR7counts, minMETbin, maxMETbin);
	sample_evtcount->CR8counts_err = binerrors(h1_CR8counts, minMETbin, maxMETbin);

}

void printtableentry(eventcount_str *sample_evtcount) {

	cout << sample_evtcount->samplename << " &$ " << sample_evtcount->SRcounts << "\\pm" << sample_evtcount->SRcounts_err  <<
	       "$    &$ " << sample_evtcount->CR2counts << "\\pm" << sample_evtcount->CR2counts_err  <<	
	       "$    &$ " << sample_evtcount->CR3counts << "\\pm" << sample_evtcount->CR3counts_err  <<	
	       "$    &$ " << sample_evtcount->CR4counts << "\\pm" << sample_evtcount->CR4counts_err  <<	
	       "$    &$ " << sample_evtcount->CR5counts << "\\pm" << sample_evtcount->CR5counts_err  <<	
	       "$    &$ " << sample_evtcount->CR6counts << "\\pm" << sample_evtcount->CR6counts_err  <<	
	       "$    &$ " << sample_evtcount->CR7counts << "\\pm" << sample_evtcount->CR7counts_err  <<	
	       "$    &$ " << sample_evtcount->CR8counts << "\\pm" << sample_evtcount->CR8counts_err  << " $  \\\\" <<endl;
}

void qcdbgprediction(bool isLSchannel, string plotname, double minMET, double maxMET) {

	TFile *_alldata = TFile::Open("alldata.root");
	TFile *_allDY = TFile::Open("allDY.root");
	TFile *_allVV = TFile::Open("allVV.root");
	TFile *_allW = TFile::Open("allW.root");
	TFile *_allT = TFile::Open("allT.root");
	TFile *_allTTbar = TFile::Open("allTTbar.root");
	TFile *_allHiggs = TFile::Open("allHiggs.root");

	eventcount_str data_evtcount;
	data_evtcount.samplename = "Data";

	eventcount_str DY_evtcount;
	DY_evtcount.samplename = "Drell-Yan";

	eventcount_str VV_evtcount;
	VV_evtcount.samplename = "VV";

	eventcount_str W_evtcount;
	W_evtcount.samplename = "W+Jets";

	eventcount_str T_evtcount;
	T_evtcount.samplename = "Single t";

	eventcount_str TTbar_evtcount;
	TTbar_evtcount.samplename = "TTbar";

	eventcount_str Higgs_evtcount;
	Higgs_evtcount.samplename = "Higgs";


	eventcount(_allDY, &DY_evtcount, isLSchannel, plotname, minMET, maxMET);
	eventcount(_allVV, &VV_evtcount, isLSchannel, plotname, minMET, maxMET);
	eventcount(_allW, &W_evtcount, isLSchannel, plotname, minMET, maxMET);
	eventcount(_allT, &T_evtcount, isLSchannel, plotname, minMET, maxMET);
	eventcount(_allTTbar, &TTbar_evtcount, isLSchannel, plotname, minMET, maxMET);
	eventcount(_allHiggs, &Higgs_evtcount, isLSchannel, plotname, minMET, maxMET);
	eventcount(_alldata, &data_evtcount, isLSchannel, plotname, minMET, maxMET);
	//printtableentry(&DY_evtcount);

	
	//loading nonQCD MC Background
	eventcount_str nonQCDmc_evtcount;
	nonQCDmc_evtcount.samplename = "Total nonQCD MC";
	nonQCDmc_evtcount.SRcounts = DY_evtcount.SRcounts + VV_evtcount.SRcounts + W_evtcount.SRcounts + T_evtcount.SRcounts + TTbar_evtcount.SRcounts + Higgs_evtcount.SRcounts;
	nonQCDmc_evtcount.CR2counts = DY_evtcount.CR2counts + VV_evtcount.CR2counts + W_evtcount.CR2counts + T_evtcount.CR2counts + TTbar_evtcount.CR2counts + Higgs_evtcount.CR2counts;
	nonQCDmc_evtcount.CR3counts = DY_evtcount.CR3counts + VV_evtcount.CR3counts + W_evtcount.CR3counts + T_evtcount.CR3counts + TTbar_evtcount.CR3counts + Higgs_evtcount.CR3counts;
	nonQCDmc_evtcount.CR4counts = DY_evtcount.CR4counts + VV_evtcount.CR4counts + W_evtcount.CR4counts + T_evtcount.CR4counts + TTbar_evtcount.CR4counts + Higgs_evtcount.CR4counts;
	nonQCDmc_evtcount.CR5counts = DY_evtcount.CR5counts + VV_evtcount.CR5counts + W_evtcount.CR5counts + T_evtcount.CR5counts + TTbar_evtcount.CR5counts + Higgs_evtcount.CR5counts;
	nonQCDmc_evtcount.CR6counts = DY_evtcount.CR6counts + VV_evtcount.CR6counts + W_evtcount.CR6counts + T_evtcount.CR6counts + TTbar_evtcount.CR6counts + Higgs_evtcount.CR6counts;
	nonQCDmc_evtcount.CR7counts = DY_evtcount.CR7counts + VV_evtcount.CR7counts + W_evtcount.CR7counts + T_evtcount.CR7counts + TTbar_evtcount.CR7counts + Higgs_evtcount.CR7counts;
	nonQCDmc_evtcount.CR8counts = DY_evtcount.CR8counts + VV_evtcount.CR8counts + W_evtcount.CR8counts + T_evtcount.CR8counts + TTbar_evtcount.CR8counts + Higgs_evtcount.CR8counts;
	nonQCDmc_evtcount.SRcounts_err = sqrt(pow(DY_evtcount.SRcounts_err,2.) + pow(VV_evtcount.SRcounts_err,2.) + pow(W_evtcount.SRcounts_err,2.) + pow(T_evtcount.SRcounts_err,2.) + pow(TTbar_evtcount.SRcounts_err,2.) + pow(Higgs_evtcount.SRcounts_err,2.));
	nonQCDmc_evtcount.CR2counts_err = sqrt(pow(DY_evtcount.CR2counts_err,2.) + pow(VV_evtcount.CR2counts_err,2.) + pow(W_evtcount.CR2counts_err,2.) + pow(T_evtcount.CR2counts_err,2.) + pow(TTbar_evtcount.CR2counts_err,2.) + pow(Higgs_evtcount.CR2counts_err,2.));
	nonQCDmc_evtcount.CR3counts_err = sqrt(pow(DY_evtcount.CR3counts_err,2.) + pow(VV_evtcount.CR3counts_err,2.) + pow(W_evtcount.CR3counts_err,2.) + pow(T_evtcount.CR3counts_err,2.) + pow(TTbar_evtcount.CR3counts_err,2.) + pow(Higgs_evtcount.CR3counts_err,2.));
	nonQCDmc_evtcount.CR4counts_err = sqrt(pow(DY_evtcount.CR4counts_err,2.) + pow(VV_evtcount.CR4counts_err,2.) + pow(W_evtcount.CR4counts_err,2.) + pow(T_evtcount.CR4counts_err,2.) + pow(TTbar_evtcount.CR4counts_err,2.) + pow(Higgs_evtcount.CR4counts_err,2.));
	nonQCDmc_evtcount.CR5counts_err = sqrt(pow(DY_evtcount.CR5counts_err,2.) + pow(VV_evtcount.CR5counts_err,2.) + pow(W_evtcount.CR5counts_err,2.) + pow(T_evtcount.CR5counts_err,2.) + pow(TTbar_evtcount.CR5counts_err,2.) + pow(Higgs_evtcount.CR5counts_err,2.));
	nonQCDmc_evtcount.CR6counts_err = sqrt(pow(DY_evtcount.CR6counts_err,2.) + pow(VV_evtcount.CR6counts_err,2.) + pow(W_evtcount.CR6counts_err,2.) + pow(T_evtcount.CR6counts_err,2.) + pow(TTbar_evtcount.CR6counts_err,2.) + pow(Higgs_evtcount.CR6counts_err,2.));
	nonQCDmc_evtcount.CR7counts_err = sqrt(pow(DY_evtcount.CR7counts_err,2.) + pow(VV_evtcount.CR7counts_err,2.) + pow(W_evtcount.CR7counts_err,2.) + pow(T_evtcount.CR7counts_err,2.) + pow(TTbar_evtcount.CR7counts_err,2.) + pow(Higgs_evtcount.CR7counts_err,2.));
	nonQCDmc_evtcount.CR8counts_err = sqrt(pow(DY_evtcount.CR8counts_err,2.) + pow(VV_evtcount.CR8counts_err,2.) + pow(W_evtcount.CR8counts_err,2.) + pow(T_evtcount.CR8counts_err,2.) + pow(TTbar_evtcount.CR8counts_err,2.) + pow(Higgs_evtcount.CR8counts_err,2.));

	double onetighteff = vbfefficiency(data_evtcount.CR4counts, data_evtcount.CR3counts, nonQCDmc_evtcount.CR4counts, nonQCDmc_evtcount.CR3counts);
	double antitighteff = vbfefficiency(data_evtcount.CR6counts, data_evtcount.CR5counts, nonQCDmc_evtcount.CR8counts, nonQCDmc_evtcount.CR5counts);
	double antimediumeff = vbfefficiency(data_evtcount.CR8counts, data_evtcount.CR7counts, nonQCDmc_evtcount.CR8counts, nonQCDmc_evtcount.CR7counts);

	double onetighteff_err = vbfefficiency_staterr(data_evtcount.CR4counts, data_evtcount.CR4counts_err, data_evtcount.CR3counts, data_evtcount.CR3counts_err, nonQCDmc_evtcount.CR4counts, nonQCDmc_evtcount.CR4counts_err, nonQCDmc_evtcount.CR3counts, nonQCDmc_evtcount.CR3counts_err);
	double antitighteff_err = vbfefficiency_staterr(data_evtcount.CR6counts, data_evtcount.CR6counts_err, data_evtcount.CR5counts, data_evtcount.CR5counts_err, nonQCDmc_evtcount.CR6counts, nonQCDmc_evtcount.CR6counts_err, nonQCDmc_evtcount.CR5counts, nonQCDmc_evtcount.CR5counts_err);
	double antimediumeff_err = vbfefficiency_staterr(data_evtcount.CR8counts, data_evtcount.CR8counts_err, data_evtcount.CR7counts, data_evtcount.CR7counts_err, nonQCDmc_evtcount.CR8counts, nonQCDmc_evtcount.CR8counts_err, nonQCDmc_evtcount.CR7counts, nonQCDmc_evtcount.CR7counts_err);

	double onetightbgpred = qcdbackgroundprediction(data_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts, onetighteff);
	double antitightbgpred = qcdbackgroundprediction(data_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts, antitighteff);
	double antimediumbgpred = qcdbackgroundprediction(data_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts, antimediumeff);

	double onetightbgpred_err = qcdbackgroundprediction_staterr(data_evtcount.CR2counts, data_evtcount.CR2counts_err, nonQCDmc_evtcount.CR2counts , nonQCDmc_evtcount.CR2counts_err, onetighteff, onetighteff_err);
	double antitightbgpred_err = qcdbackgroundprediction_staterr(data_evtcount.CR2counts, data_evtcount.CR2counts_err, nonQCDmc_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts_err, antitighteff, antitighteff_err);
	double antimediumbgpred_err = qcdbackgroundprediction_staterr(data_evtcount.CR2counts, data_evtcount.CR2counts_err, nonQCDmc_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts_err, antimediumeff, antimediumeff_err);

	//Efficiency Systematics
	
	double evenCRcount = (double)data_evtcount.CR4counts + (double)data_evtcount.CR6counts + (double)data_evtcount.CR8counts;
	double oddCRcount = (double)data_evtcount.CR3counts + (double)data_evtcount.CR5counts + (double)data_evtcount.CR7counts;
	double evenCRnonQCDbg = nonQCDmc_evtcount.CR4counts + nonQCDmc_evtcount.CR6counts + nonQCDmc_evtcount.CR8counts;
	double oddCRnonQCDbg = nonQCDmc_evtcount.CR3counts + nonQCDmc_evtcount.CR5counts + nonQCDmc_evtcount.CR7counts;
	double evenCRcount_err = sqrt( pow(data_evtcount.CR4counts_err, 2.) + pow(data_evtcount.CR6counts_err, 2.) + pow(data_evtcount.CR8counts_err, 2.));
	double oddCRcount_err = sqrt( pow(data_evtcount.CR3counts_err, 2.) + pow(data_evtcount.CR5counts_err, 2.) + pow(data_evtcount.CR7counts_err, 2.));
	double evenCRnonQCDbg_err = sqrt( pow(nonQCDmc_evtcount.CR4counts_err, 2.) + pow(nonQCDmc_evtcount.CR6counts_err, 2.) + pow(nonQCDmc_evtcount.CR8counts_err, 2.));
	double oddCRnonQCDbg_err = sqrt( pow(nonQCDmc_evtcount.CR3counts_err, 2.) + pow(nonQCDmc_evtcount.CR5counts_err, 2.) + pow(nonQCDmc_evtcount.CR7counts_err, 2.));

	double weightedmeaneff = vbfefficiency(evenCRcount, oddCRcount, evenCRnonQCDbg, oddCRnonQCDbg);
	double weightedmeaneff_err = vbfefficiency_staterr(evenCRcount, evenCRcount_err, oddCRcount, oddCRcount_err, evenCRnonQCDbg, evenCRnonQCDbg_err, oddCRnonQCDbg, oddCRnonQCDbg_err);

	double weightedmeaneff_nonqcdmc_upwardvar = vbfefficiency(evenCRcount, oddCRcount, (evenCRnonQCDbg * 0.5), (oddCRnonQCDbg * 0.5));
	double weightedmeaneff_nonqcdmc_downwardvar = vbfefficiency(evenCRcount, oddCRcount, (evenCRnonQCDbg * 1.5), (oddCRnonQCDbg * 1.5));

	std::vector<double> v_eff;
	v_eff.push_back(onetighteff);
	v_eff.push_back(antitighteff);
	v_eff.push_back(antimediumeff);

	std::vector<double> v_eff_err;
	v_eff_err.push_back(onetighteff_err);
	v_eff_err.push_back(antitighteff_err);
	v_eff_err.push_back(antimediumeff_err);

	//upward variation
	double weightedmeaneff_eff_upwardvar = weightedmeaneff;
	for (unsigned int i = 0; i < v_eff.size(); i++) {
		double temp = v_eff[i] + v_eff_err[i];
		if (temp > weightedmeaneff_eff_upwardvar ) weightedmeaneff_eff_upwardvar = temp;
	}

	//downward variation
	double weightedmeaneff_eff_downwardvar = weightedmeaneff;
	for (unsigned int i = 0; i < v_eff.size(); i++) {
		double temp = v_eff[i] - v_eff_err[i];
		if (temp < weightedmeaneff_eff_downwardvar ) weightedmeaneff_eff_downwardvar = temp;
	}
	

	double weightedmeaneff_nonqcdmc_upsyst = weightedmeaneff_nonqcdmc_upwardvar - weightedmeaneff;
	double weightedmeaneff_nonqcdmc_downsyst = weightedmeaneff - weightedmeaneff_nonqcdmc_downwardvar;

	double weightedmeaneff_eff_upsyst = weightedmeaneff_eff_upwardvar - weightedmeaneff;
	double weightedmeaneff_eff_downsyst = weightedmeaneff - weightedmeaneff_eff_downwardvar;

	//MC Syst Uncertainty

	double weightedmeanbgpred = qcdbackgroundprediction(data_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts, weightedmeaneff);
	double weightedmeanbgpred_err = qcdbackgroundprediction_staterr(data_evtcount.CR2counts, data_evtcount.CR2counts_err, nonQCDmc_evtcount.CR2counts , nonQCDmc_evtcount.CR2counts_err, weightedmeaneff, weightedmeaneff_err);

	double weightedmeanbgpred_nonqcdmc_upwardvar = qcdbackgroundprediction(data_evtcount.CR2counts, (nonQCDmc_evtcount.CR2counts * 0.5), weightedmeaneff_nonqcdmc_upwardvar);
	double weightedmeanbgpred_nonqcdmc_downwardvar = qcdbackgroundprediction(data_evtcount.CR2counts, (nonQCDmc_evtcount.CR2counts * 1.5), weightedmeaneff_nonqcdmc_downwardvar);

	double weightedmeanbgpred_eff_upwardvar = qcdbackgroundprediction(data_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts, weightedmeaneff_eff_upwardvar);
	double weightedmeanbgpred_eff_downwardvar = qcdbackgroundprediction(data_evtcount.CR2counts, nonQCDmc_evtcount.CR2counts, weightedmeaneff_eff_downwardvar);

	double weightedmeanbgpred_nonqcdmc_upsyst = weightedmeanbgpred_nonqcdmc_upwardvar - weightedmeanbgpred;
	double weightedmeanbgpred_nonqcdmc_downsyst = weightedmeanbgpred - weightedmeanbgpred_nonqcdmc_downwardvar;

	double weightedmeanbgpred_eff_upsyst = weightedmeanbgpred_eff_upwardvar - weightedmeanbgpred;
	double weightedmeanbgpred_eff_downsyst = weightedmeanbgpred - weightedmeanbgpred_eff_downwardvar;


	cout << "//-------------------Study Done using Eventcount as input------------------------//" << endl;
	cout << endl;
	cout << endl;
	cout << "#VBF Efficency#" << endl;
	cout <<"One tight region-- "<<"VBF Efficency: "<< onetighteff << " +- "<<onetighteff_err<<endl;
	cout <<"Anti tight region-- "<<"VBF Efficency: "<< antitighteff << " +- "<<antitighteff_err<<endl;
	cout <<"Anti medium region-- "<<"VBF Efficency: "<< antimediumeff << " +- "<<antimediumeff_err<<endl;
	cout << "#VBF Efficency Systematics#" << endl;
	cout << "Weighted Mean: " << weightedmeaneff << " +- " << weightedmeaneff_err << " + " << weightedmeaneff_nonqcdmc_upsyst << " + " << weightedmeaneff_eff_upsyst << " - " << weightedmeaneff_nonqcdmc_downsyst << " - " << weightedmeaneff_eff_downsyst << endl;
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout <<"One tight region-- "<< "BG Prediction: " << onetightbgpred<< " +- "<< onetightbgpred_err << endl;
	cout <<"Anti tight region-- "<<	"BG Prediction: " << antitightbgpred<< " +- "<< antitightbgpred_err << endl;
	cout <<"Anti medium region-- "<< "BG Prediction: " << antimediumbgpred<< " +- "<< antimediumbgpred_err << endl;
	cout << "Weighted Mean: " << weightedmeanbgpred << " +- " << weightedmeanbgpred_err << " + " << weightedmeanbgpred_nonqcdmc_upsyst << " + " << weightedmeanbgpred_eff_upsyst << " - " << weightedmeanbgpred_nonqcdmc_downsyst << " - " << weightedmeanbgpred_eff_downsyst << endl;
	cout << endl;
	cout << "----------LATEX-----------" << endl;

	cout << "//-------------------Tables Output------------------------//" << endl;
	cout << endl;
	cout << "#VBF Efficency#" << endl;
	cout << onetighteff << " " << onetighteff_err << " " << 
		antitighteff << " " << antitighteff_err << " " <<
		antimediumeff << " " << antimediumeff_err << " " << endl;
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout << onetightbgpred << " " << onetightbgpred_err << " " << 
		antitightbgpred << " " << antitightbgpred_err << " " <<
		antimediumbgpred << " " << antimediumbgpred_err << " " << endl;
	cout << endl;
	cout << "//-------------------LATEX OUTPUT------------------------//" << endl;
	cout << "#Event Counting#" << endl;
	printtableentry(&data_evtcount);
	printtableentry(&DY_evtcount);
	printtableentry(&VV_evtcount);
	printtableentry(&W_evtcount);
	printtableentry(&T_evtcount);
	printtableentry(&TTbar_evtcount);
	printtableentry(&Higgs_evtcount);
	cout << "\\hline" <<endl;
	printtableentry(&nonQCDmc_evtcount);
	cout << endl;
	cout << "#VBF Efficency#" << endl;
	cout << "$\\epsilon^{QCD}_{VBF}$    &$ " << onetighteff << "\\pm" << onetighteff_err << 
		" $  &$ " << antitighteff << "\\pm" << antitighteff_err << 
		" $  &$ " << antimediumeff << "\\pm" << antimediumeff_err << " $ \\\\" << endl;
	cout << weightedmeaneff << "\\pm" << weightedmeaneff_err << "^{+"<<weightedmeaneff_nonqcdmc_upsyst<<"+"<<weightedmeaneff_eff_upsyst<<"}_{-"<<weightedmeaneff_nonqcdmc_downsyst<<"-"<<weightedmeaneff_eff_downsyst<<"}"<< endl;
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout << "$N^{QCD}_{SR}$    &$ " << onetightbgpred << "\\pm" << onetightbgpred_err << 
		" $  &$ " << antitightbgpred << "\\pm" << antitightbgpred_err << 
		" $  &$ " << antimediumbgpred << "\\pm" << antimediumbgpred_err << " $ \\\\" << endl;
	cout << weightedmeanbgpred << "\\pm" << weightedmeanbgpred_err << "^{+"<<weightedmeanbgpred_nonqcdmc_upsyst<<"+"<<weightedmeanbgpred_eff_upsyst<<"}_{-"<<weightedmeanbgpred_nonqcdmc_downsyst<<"-"<<weightedmeanbgpred_eff_downsyst<<"}"<< endl;

} 
