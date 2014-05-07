#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

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
void eventcount(TFile* inputfile, bool isLSchannel){

	TH1F* h1_SRcounts;
	TH1F* h1_CR2counts;
	TH1F* h1_CR3counts;
	TH1F* h1_CR4counts;
	TH1F* h1_CR5counts;
	TH1F* h1_CR6counts;
	TH1F* h1_CR7counts;
	TH1F* h1_CR8counts;
	TH1F* h1_CR9counts;
	TH1F* h1_CR10counts;
	
	if (isLSchannel) {
		h1_SRcounts = ((TH1F*)(inputfile->Get("LS_SignalRegion/h_ditaucharge")));
		h1_CR2counts = ((TH1F*)(inputfile->Get("LS_Central_invertedVBF_2TightIso_CR2/h_ditaucharge")));
		h1_CR3counts = ((TH1F*)(inputfile->Get("LS_Central_1TightIso_CR3/h_ditaucharge")));
		h1_CR4counts = ((TH1F*)(inputfile->Get("LS_Central_invertedVBF_1TightIso_CR4/h_ditaucharge")));
		h1_CR5counts = ((TH1F*)(inputfile->Get("LS_Central_AntiTightIso_CR5/h_ditaucharge")));
		h1_CR6counts = ((TH1F*)(inputfile->Get("LS_Central_invertedVBF_AntiTightIso_CR6/h_ditaucharge")));
		h1_CR7counts = ((TH1F*)(inputfile->Get("LS_Central_AntiMediumIso_CR7/h_ditaucharge")));
		h1_CR8counts = ((TH1F*)(inputfile->Get("LS_Central_invertedVBF_AntiMediumIso_CR8/h_ditaucharge")));
		h1_CR9counts = ((TH1F*)(inputfile->Get("LS_Central_AntiLooseIso_CR9/h_ditaucharge")));
		h1_CR10counts = ((TH1F*)(inputfile->Get("LS_Central_invertedVBF_AntiLooseIso_CR10/h_ditaucharge")));
	}

	if (!isLSchannel) {
		h1_SRcounts = ((TH1F*)(inputfile->Get("OS_SignalRegion/h_ditaucharge")));
		h1_CR2counts = ((TH1F*)(inputfile->Get("OS_Central_invertedVBF_2TightIso_CR2/h_ditaucharge")));
		h1_CR3counts = ((TH1F*)(inputfile->Get("OS_Central_1TightIso_CR3/h_ditaucharge")));
		h1_CR4counts = ((TH1F*)(inputfile->Get("OS_Central_invertedVBF_1TightIso_CR4/h_ditaucharge")));
		h1_CR5counts = ((TH1F*)(inputfile->Get("OS_Central_AntiTightIso_CR5/h_ditaucharge")));
		h1_CR6counts = ((TH1F*)(inputfile->Get("OS_Central_invertedVBF_AntiTightIso_CR6/h_ditaucharge")));
		h1_CR7counts = ((TH1F*)(inputfile->Get("OS_Central_AntiMediumIso_CR7/h_ditaucharge")));
		h1_CR8counts = ((TH1F*)(inputfile->Get("OS_Central_invertedVBF_AntiMediumIso_CR8/h_ditaucharge")));
		h1_CR9counts = ((TH1F*)(inputfile->Get("OS_Central_AntiLooseIso_CR9/h_ditaucharge")));
		h1_CR10counts = ((TH1F*)(inputfile->Get("OS_Central_invertedVBF_AntiLooseIso_CR10/h_ditaucharge")));
	}

	int countbin = 0;
	if (isLSchannel) countbin = 3;
	if (!isLSchannel) countbin = 2;

	double SRcounts = h1_SRcounts->GetBinContent(countbin);
	double CR2counts = h1_CR2counts->GetBinContent(countbin);
	double CR3counts = h1_CR3counts->GetBinContent(countbin);
	double CR4counts = h1_CR4counts->GetBinContent(countbin);
	double CR5counts = h1_CR5counts->GetBinContent(countbin);
	double CR6counts = h1_CR6counts->GetBinContent(countbin);
	double CR7counts = h1_CR7counts->GetBinContent(countbin);
	double CR8counts = h1_CR8counts->GetBinContent(countbin);
	double CR9counts = h1_CR9counts->GetBinContent(countbin);
	double CR10counts = h1_CR10counts->GetBinContent(countbin);

	double SRcounts_err = h1_SRcounts->GetBinError(countbin);
	double CR2counts_err = h1_CR2counts->GetBinError(countbin);
	double CR3counts_err = h1_CR3counts->GetBinError(countbin);
	double CR4counts_err = h1_CR4counts->GetBinError(countbin);
	double CR5counts_err = h1_CR5counts->GetBinError(countbin);
	double CR6counts_err = h1_CR6counts->GetBinError(countbin);
	double CR7counts_err = h1_CR7counts->GetBinError(countbin);
	double CR8counts_err = h1_CR8counts->GetBinError(countbin);
	double CR9counts_err = h1_CR9counts->GetBinError(countbin);
	double CR10counts_err = h1_CR10counts->GetBinError(countbin);

	//loading nonQCD MC Background
	//
	vector<double> v_nonqcdbg;
	vector<double> v_nonqcdbg_err;
	std::string mccountsinputfile("");
	if (isLSchannel) mccountsinputfile = "ls_nonqcdmcbg.txt";
	if (!isLSchannel) mccountsinputfile = "os_nonqcdmcbg.txt";
	ifstream read(mccountsinputfile.c_str());
	double readtemp,readtemp_err;
	while(read>>readtemp>>readtemp_err){
		v_nonqcdbg.push_back(readtemp);
		v_nonqcdbg_err.push_back(readtemp_err);
	}
	double onetighteff = vbfefficiency(CR4counts, CR3counts, v_nonqcdbg[(4 - 1)], v_nonqcdbg[(3 - 1)]);
	double antitighteff = vbfefficiency(CR6counts, CR5counts, v_nonqcdbg[(6 - 1)], v_nonqcdbg[(5 - 1)]);
	double antimediumeff = vbfefficiency(CR8counts, CR7counts, v_nonqcdbg[(8 - 1)], v_nonqcdbg[(7 - 1)]);
	double antilooseeff = vbfefficiency(CR10counts, CR9counts, v_nonqcdbg[(10 - 1)], v_nonqcdbg[(9 - 1)]);

	double onetighteff_err = vbfefficiency_staterr(CR4counts, CR4counts_err, CR3counts, CR3counts_err, v_nonqcdbg[(4 - 1)], v_nonqcdbg_err[(4 - 1)], v_nonqcdbg[(3 - 1)], v_nonqcdbg_err[(3 - 1)]);
	double antitighteff_err = vbfefficiency_staterr(CR6counts, CR6counts_err, CR5counts, CR5counts_err, v_nonqcdbg[(6 - 1)], v_nonqcdbg_err[(6 - 1)], v_nonqcdbg[(5 - 1)], v_nonqcdbg_err[(5 - 1)]);
	double antimediumeff_err = vbfefficiency_staterr(CR8counts, CR8counts_err, CR7counts, CR7counts_err, v_nonqcdbg[(8 - 1)], v_nonqcdbg_err[(8 - 1)], v_nonqcdbg[(7 - 1)], v_nonqcdbg_err[(7 - 1)]);
	double antilooseeff_err = vbfefficiency_staterr(CR10counts, CR10counts_err, CR9counts, CR9counts_err, v_nonqcdbg[(10 - 1)], v_nonqcdbg_err[(10 - 1)], v_nonqcdbg[(9 - 1)], v_nonqcdbg_err[(9 - 1)]);

	//onetighteff = 0.0295485;
	//onetighteff_err = 0.0114218;
	//antitighteff = 0.0832767;
	//antitighteff_err = 0.0281216;
	//antimediumeff = 0.055978;
	//antimediumeff_err = 0.0313339;

	double onetightbgpred = qcdbackgroundprediction(CR2counts, v_nonqcdbg[(2 - 1)], onetighteff);
	double antitightbgpred = qcdbackgroundprediction(CR2counts, v_nonqcdbg[(2 - 1)], antitighteff);
	double antimediumbgpred = qcdbackgroundprediction(CR2counts, v_nonqcdbg[(2 - 1)], antimediumeff);
	double antiloosebgpred = qcdbackgroundprediction(CR2counts, v_nonqcdbg[(2 - 1)], antilooseeff);

	double onetightbgpred_err = qcdbackgroundprediction_staterr(CR2counts, CR2counts_err, v_nonqcdbg[(2 - 1)] , v_nonqcdbg_err[(2 - 1)], onetighteff, onetighteff_err);
	double antitightbgpred_err = qcdbackgroundprediction_staterr(CR2counts, CR2counts_err, v_nonqcdbg[(2 - 1)] , v_nonqcdbg_err[(2 - 1)], antitighteff, antitighteff_err);
	double antimediumbgpred_err = qcdbackgroundprediction_staterr(CR2counts, CR2counts_err, v_nonqcdbg[(2 - 1)] , v_nonqcdbg_err[(2 - 1)], antimediumeff, antimediumeff_err);
	double antiloosebgpred_err = qcdbackgroundprediction_staterr(CR2counts, CR2counts_err, v_nonqcdbg[(2 - 1)] , v_nonqcdbg_err[(2 - 1)], antilooseeff, antilooseeff_err);

	//Efficiency Systematics
	
	double evenCRcount = (double)CR4counts + (double)CR6counts + (double)CR8counts + (double)CR10counts;
	double oddCRcount = (double)CR3counts + (double)CR5counts + (double)CR7counts + (double)CR9counts;
	double evenCRnonQCDbg = v_nonqcdbg[(4 - 1)] + v_nonqcdbg[(6 - 1)] + v_nonqcdbg[(8 - 1)] + v_nonqcdbg[(10 - 1)];
	double oddCRnonQCDbg = v_nonqcdbg[(3 - 1)] + v_nonqcdbg[(5 - 1)] + v_nonqcdbg[(7 - 1)] + v_nonqcdbg[(9 - 1)];
	double evenCRcount_err = sqrt( pow(CR4counts_err, 2.) + pow(CR6counts_err, 2.) + pow(CR8counts_err, 2.) + pow(CR10counts_err, 2.));
	double oddCRcount_err = sqrt( pow(CR3counts_err, 2.) + pow(CR5counts_err, 2.) + pow(CR7counts_err, 2.) + pow(CR9counts_err, 2.));
	double evenCRnonQCDbg_err = sqrt( pow(v_nonqcdbg_err[(4 - 1)], 2.) + pow(v_nonqcdbg_err[(6 - 1)], 2.) + pow(v_nonqcdbg_err[(8 - 1)], 2.) + pow(v_nonqcdbg_err[(10 - 1)], 2.));
	double oddCRnonQCDbg_err = sqrt( pow(v_nonqcdbg_err[(3 - 1)], 2.) + pow(v_nonqcdbg_err[(5 - 1)], 2.) + pow(v_nonqcdbg_err[(7 - 1)], 2.) + pow(v_nonqcdbg_err[(9 - 1)], 2.));

	double weightedmeaneff = vbfefficiency(evenCRcount, oddCRcount, evenCRnonQCDbg, oddCRnonQCDbg);
	double weightedmeaneff_err = vbfefficiency_staterr(evenCRcount, evenCRcount_err, oddCRcount, oddCRcount_err, evenCRnonQCDbg, evenCRnonQCDbg_err, oddCRnonQCDbg, oddCRnonQCDbg_err);

	double weightedmeaneff_nonqcdmc_upwardvar = vbfefficiency(evenCRcount, oddCRcount, (evenCRnonQCDbg * 0.5), (oddCRnonQCDbg * 0.5));
	double weightedmeaneff_nonqcdmc_downwardvar = vbfefficiency(evenCRcount, oddCRcount, (evenCRnonQCDbg * 1.5), (oddCRnonQCDbg * 1.5));

	std::vector<double> v_eff;
	v_eff.push_back(onetighteff);
	v_eff.push_back(antitighteff);
	v_eff.push_back(antimediumeff);
	v_eff.push_back(antilooseeff);

	std::vector<double> v_eff_err;
	v_eff_err.push_back(onetighteff_err);
	v_eff_err.push_back(antitighteff_err);
	v_eff_err.push_back(antimediumeff_err);
	v_eff_err.push_back(antilooseeff_err);

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

	double weightedmeanbgpred = qcdbackgroundprediction(CR2counts, v_nonqcdbg[(2 - 1)], weightedmeaneff);
	double weightedmeanbgpred_err = qcdbackgroundprediction_staterr(CR2counts, CR2counts_err, v_nonqcdbg[(2 - 1)] , v_nonqcdbg_err[(2 - 1)], weightedmeaneff, weightedmeaneff_err);

	double weightedmeanbgpred_nonqcdmc_upwardvar = qcdbackgroundprediction(CR2counts, (v_nonqcdbg[(2 - 1)] * 0.5), weightedmeaneff_nonqcdmc_upwardvar);
	double weightedmeanbgpred_nonqcdmc_downwardvar = qcdbackgroundprediction(CR2counts, (v_nonqcdbg[(2 - 1)] * 1.5), weightedmeaneff_nonqcdmc_downwardvar);

	double weightedmeanbgpred_eff_upwardvar = qcdbackgroundprediction(CR2counts, v_nonqcdbg[(2 - 1)], weightedmeaneff_eff_upwardvar);
	double weightedmeanbgpred_eff_downwardvar = qcdbackgroundprediction(CR2counts, v_nonqcdbg[(2 - 1)], weightedmeaneff_eff_downwardvar);

	double weightedmeanbgpred_nonqcdmc_upsyst = weightedmeanbgpred_nonqcdmc_upwardvar - weightedmeanbgpred;
	double weightedmeanbgpred_nonqcdmc_downsyst = weightedmeanbgpred - weightedmeanbgpred_nonqcdmc_downwardvar;

	double weightedmeanbgpred_eff_upsyst = weightedmeanbgpred_eff_upwardvar - weightedmeanbgpred;
	double weightedmeanbgpred_eff_downsyst = weightedmeanbgpred - weightedmeanbgpred_eff_downwardvar;


	cout << "//-------------------Study Done using Eventcount as input------------------------//" << endl;
	cout << endl;
	cout << "#Event Counting#" << endl;
	cout << "SR: "<< SRcounts  << " +- " << SRcounts_err <<endl;
	cout << "CR2: "<< CR2counts  << " +- " << CR2counts_err <<endl;
	cout << "CR3: "<< CR3counts  << " +- " << CR3counts_err <<endl;
	cout << "CR4: "<< CR4counts  << " +- " << CR4counts_err <<endl;
	cout << "CR5: "<< CR5counts  << " +- " << CR5counts_err <<endl;
	cout << "CR6: "<< CR6counts  << " +- " << CR6counts_err <<endl;
	cout << "CR7: "<< CR7counts  << " +- " << CR7counts_err <<endl;
	cout << "CR8: "<< CR8counts  << " +- " << CR8counts_err <<endl;
	cout << "CR9: "<< CR9counts  << " +- " << CR9counts_err <<endl;
	cout << "CR10: "<< CR10counts  << " +- " << CR10counts_err<<endl;
	cout << endl;
	cout << "#VBF Efficency#" << endl;
	cout <<"One tight region-- "<<"VBF Efficency: "<< onetighteff << " +- "<<onetighteff_err<<endl;
	cout <<"Anti tight region-- "<<"VBF Efficency: "<< antitighteff << " +- "<<antitighteff_err<<endl;
	cout <<"Anti medium region-- "<<"VBF Efficency: "<< antimediumeff << " +- "<<antimediumeff_err<<endl;
	cout <<"Anti loose region-- "<<"VBF Efficency: "<< antilooseeff << " +- "<<antilooseeff_err<<endl;
	cout << "#VBF Efficency Systematics#" << endl;
	cout << "Weighted Mean: " << weightedmeaneff << " +- " << weightedmeaneff_err << " + " << weightedmeaneff_nonqcdmc_upsyst << " + " << weightedmeaneff_eff_upsyst << " - " << weightedmeaneff_nonqcdmc_downsyst << " - " << weightedmeaneff_eff_downsyst << endl;
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout <<"One tight region-- "<< "BG Prediction: " << onetightbgpred<< " +- "<< onetightbgpred_err << endl;
	cout <<"Anti tight region-- "<<	"BG Prediction: " << antitightbgpred<< " +- "<< antitightbgpred_err << endl;
	cout <<"Anti medium region-- "<< "BG Prediction: " << antimediumbgpred<< " +- "<< antimediumbgpred_err << endl;
	cout <<"Anti loose region-- "<<	"BG Prediction: " << antiloosebgpred<< " +- "<< antiloosebgpred_err << endl;
	cout << "Weighted Mean: " << weightedmeanbgpred << " +- " << weightedmeanbgpred_err << " + " << weightedmeanbgpred_nonqcdmc_upsyst << " + " << weightedmeanbgpred_eff_upsyst << " - " << weightedmeanbgpred_nonqcdmc_downsyst << " - " << weightedmeanbgpred_eff_downsyst << endl;
	cout << endl;
	cout << "----------LATEX-----------" << endl;

	cout << "//-------------------Tables Output------------------------//" << endl;
	cout << "#Event Counting#" << endl;
	cout << SRcounts << " " << SRcounts_err << " " << 
		CR2counts  << " " << CR2counts_err << " "<< 
		CR3counts  << " " << CR3counts_err << " " << 
		CR4counts  << " " << CR4counts_err << " " << 
		CR5counts  << " " << CR5counts_err << " " << 
		CR6counts  << " " << CR6counts_err << " " << 
		CR7counts  << " " << CR7counts_err << " " << 
		CR8counts  << " " << CR8counts_err << " " << 
		CR9counts  << " " << CR9counts_err << " " << 
		CR10counts  << " " << CR10counts_err << " " << endl;
	cout << endl;
	cout << "#VBF Efficency#" << endl;
	cout << onetighteff << " " << onetighteff_err << " " << 
		antitighteff << " " << antitighteff_err << " " <<
		antimediumeff << " " << antimediumeff_err << " " <<
		antilooseeff << " " << antilooseeff_err << " " << endl;
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout << onetightbgpred << " " << onetightbgpred_err << " " << 
		antitightbgpred << " " << antitightbgpred_err << " " <<
		antimediumbgpred << " " << antimediumbgpred_err << " " <<
		antiloosebgpred << " " << antiloosebgpred_err << " " << endl;
	cout << endl;
	cout << "//-------------------LATEX OUTPUT------------------------//" << endl;
	cout << "#Event Counting#" << endl;
	cout << "SampleName_errors  &$ " << SRcounts << "\\pm" << SRcounts_err  <<
	       "$    &$ " << CR2counts << "\\pm" << CR2counts_err  <<	
	       "$    &$ " << CR3counts << "\\pm" << CR3counts_err  <<	
	       "$    &$ " << CR4counts << "\\pm" << CR4counts_err  <<	
	       "$    &$ " << CR5counts << "\\pm" << CR5counts_err  <<	
	       "$    &$ " << CR6counts << "\\pm" << CR6counts_err  <<	
	       "$    &$ " << CR7counts << "\\pm" << CR7counts_err  <<	
	       "$    &$ " << CR8counts << "\\pm" << CR8counts_err  <<	
	       "$    &$ " << CR9counts << "\\pm" << CR9counts_err  <<	
	       "$    &$ " << CR10counts << "\\pm" << CR10counts_err  << " $  \\\\" <<endl;
	cout << "SampleName_noerrors  &$ " << SRcounts <<
	       "$    &$ " << CR2counts  <<	
	       "$    &$ " << CR3counts <<	
	       "$    &$ " << CR4counts <<	
	       "$    &$ " << CR5counts <<	
	       "$    &$ " << CR6counts <<	
	       "$    &$ " << CR7counts <<	
	       "$    &$ " << CR8counts <<	
	       "$    &$ " << CR9counts <<	
	       "$    &$ " << CR10counts << " $  \\\\" <<endl;
	cout << endl;
	cout << "#VBF Efficency#" << endl;
	cout << "$\\epsilon^{QCD}_{VBF}$    &$ " << onetighteff << "\\pm" << onetighteff_err << 
		" $  &$ " << antitighteff << "\\pm" << antitighteff_err << 
		" $  &$ " << antimediumeff << "\\pm" << antimediumeff_err << 
		" $  &$ " << antilooseeff << "\\pm" << antilooseeff_err << " $ \\\\" << endl;
	cout << weightedmeaneff << "\\pm" << weightedmeaneff_err << "^{+"<<weightedmeaneff_nonqcdmc_upsyst<<"+"<<weightedmeaneff_eff_upsyst<<"}_{-"<<weightedmeaneff_nonqcdmc_downsyst<<"-"<<weightedmeaneff_eff_downsyst<<"}"<< endl;
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout << "$N^{QCD}_{SR}$    &$ " << onetightbgpred << "\\pm" << onetightbgpred_err << 
		" $  &$ " << antitightbgpred << "\\pm" << antitightbgpred_err << 
		" $  &$ " << antimediumbgpred << "\\pm" << antimediumbgpred_err <<
	        " $  &$ " << antiloosebgpred << "\\pm" << antiloosebgpred_err <<	" $ \\\\" << endl;
	cout << weightedmeanbgpred << "\\pm" << weightedmeanbgpred_err << "^{+"<<weightedmeanbgpred_nonqcdmc_upsyst<<"+"<<weightedmeanbgpred_eff_upsyst<<"}_{-"<<weightedmeanbgpred_nonqcdmc_downsyst<<"-"<<weightedmeanbgpred_eff_downsyst<<"}"<< endl;
}
