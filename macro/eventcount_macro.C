#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <iostream>
#include <cmath>

using namespace std;

void efficiency_syst(TFile* inputfile, bool isLSchannel){

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

	double onetighteff = (double)CR3counts / (double)(CR3counts + CR4counts);
	double antitighteff = (double)CR5counts / (double)(CR5counts + CR6counts);
	double antimediumeff = (double)CR7counts / (double)(CR7counts + CR8counts);
	double antilooseeff = (double)CR9counts / (double)(CR9counts + CR10counts);

	double onetighteff_err = sqrt( pow(  (((double)CR4counts * CR3counts_err)/(pow(((double)CR3counts + (double)CR4counts),2.))), 2.)  + pow(  (((double)CR3counts * CR4counts_err)/(pow(((double)CR3counts + (double)CR4counts),2.))), 2.)    );
	double antitighteff_err = sqrt( pow(  (((double)CR6counts * CR5counts_err)/(pow(((double)CR5counts + (double)CR6counts),2.))), 2.)  + pow(  (((double)CR5counts * CR6counts_err)/(pow(((double)CR5counts + (double)CR6counts),2.))), 2.)    );
	double antimediumeff_err = sqrt( pow(  (((double)CR8counts * CR7counts_err)/(pow(((double)CR7counts + (double)CR8counts),2.))), 2.)  + pow(  (((double)CR7counts * CR8counts_err)/(pow(((double)CR7counts + (double)CR8counts),2.))), 2.)    );
	double antilooseeff_err = sqrt( pow(  (((double)CR10counts * CR9counts_err)/(pow(((double)CR9counts + (double)CR10counts),2.))), 2.)  + pow(  (((double)CR9counts * CR10counts_err)/(pow(((double)CR9counts + (double)CR10counts),2.))), 2.)    );

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

	double evenCRcount = (double)CR4counts + (double)CR6counts + (double)CR8counts + (double)CR10counts;
	double oddCRcount = (double)CR3counts + (double)CR5counts + (double)CR7counts + (double)CR9counts;
	double evenCRcount_err = sqrt( pow(CR4counts_err, 2.) + pow(CR6counts_err, 2.) + pow(CR8counts_err, 2.) + pow(CR10counts_err, 2.));
	double oddCRcount_err = sqrt( pow(CR3counts_err, 2.) + pow(CR5counts_err, 2.) + pow(CR7counts_err, 2.) + pow(CR9counts_err, 2.));

	double weightedmeaneff = oddCRcount / (oddCRcount + evenCRcount);
	double weightedmeaneff_err = sqrt( pow(  (( evenCRcount * oddCRcount_err)/(pow((oddCRcount + evenCRcount),2.))), 2.)  + pow(  ((oddCRcount * evenCRcount_err)/(pow((oddCRcount + evenCRcount),2.))), 2.)    );


	//upward variation
	double upwardvar = weightedmeaneff;
	for (unsigned int i = 0; i < v_eff.size(); i++) {
		double temp = v_eff[i] + v_eff_err[i];
		if (temp > upwardvar ) upwardvar = temp;
	}

	//downward variation
	double downwardvar = weightedmeaneff;
	for (unsigned int i = 0; i < v_eff.size(); i++) {
		double temp = v_eff[i] - v_eff_err[i];
		if (temp < downwardvar ) downwardvar = temp;
	}
	
	double upsyst = upwardvar - weightedmeaneff;
	double lowsyst = weightedmeaneff - downwardvar;

	cout << "Efficiency" << endl;
	cout << weightedmeaneff << " +- " << weightedmeaneff_err << " + " << upsyst << " - " << lowsyst << endl;
	cout << "----------LATEX-----------" << endl;
	cout << weightedmeaneff << "\\pm" << weightedmeaneff_err << "^{+"<<upsyst<<"}_{-"<<lowsyst<<"}"<< endl;

}

void eventcount(TFile* inputfile, double nonQCDbg, double nonQCDbgerr, bool isLSchannel){

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

	double onetighteff = (double)CR3counts / (double)(CR3counts + CR4counts);
	double antitighteff = (double)CR5counts / (double)(CR5counts + CR6counts);
	double antimediumeff = (double)CR7counts / (double)(CR7counts + CR8counts);
	double antilooseeff = (double)CR9counts / (double)(CR9counts + CR10counts);

	double onetighteff_err = sqrt( pow(  (((double)CR4counts * CR3counts_err)/(pow(((double)CR3counts + (double)CR4counts),2.))), 2.)  + pow(  (((double)CR3counts * CR4counts_err)/(pow(((double)CR3counts + (double)CR4counts),2.))), 2.)    );
	double antitighteff_err = sqrt( pow(  (((double)CR6counts * CR5counts_err)/(pow(((double)CR5counts + (double)CR6counts),2.))), 2.)  + pow(  (((double)CR5counts * CR6counts_err)/(pow(((double)CR5counts + (double)CR6counts),2.))), 2.)    );
	double antimediumeff_err = sqrt( pow(  (((double)CR8counts * CR7counts_err)/(pow(((double)CR7counts + (double)CR8counts),2.))), 2.)  + pow(  (((double)CR7counts * CR8counts_err)/(pow(((double)CR7counts + (double)CR8counts),2.))), 2.)    );
	double antilooseeff_err = sqrt( pow(  (((double)CR10counts * CR9counts_err)/(pow(((double)CR9counts + (double)CR10counts),2.))), 2.)  + pow(  (((double)CR9counts * CR10counts_err)/(pow(((double)CR9counts + (double)CR10counts),2.))), 2.)    );

	double onetightbgpred = ( (double)CR2counts - nonQCDbg) * (onetighteff / (1. - onetighteff) );
	double antitightbgpred = ( (double)CR2counts - nonQCDbg) * (antitighteff / (1. - antitighteff) );
	double antimediumbgpred = ( (double)CR2counts - nonQCDbg) * (antimediumeff / (1. - antimediumeff) );
	double antiloosebgpred = ( (double)CR2counts - nonQCDbg) * (antilooseeff / (1. - antilooseeff) );

	double onetightbgpred_err = sqrt(  pow(   ((onetighteff * ( CR2counts_err + nonQCDbgerr ) )/( 1. - onetighteff))    , 2.)   +   pow(   (((double)CR2counts * onetighteff_err)/(pow( (1 - onetighteff) ,2.)))    , 2.)    );
	double antitightbgpred_err = sqrt(  pow(   ((antitighteff * ( CR2counts_err + nonQCDbgerr ))/( 1. - antitighteff))    , 2.)   +   pow(   (((double)CR2counts * antitighteff_err)/(pow( (1 - antitighteff) ,2.)))    , 2.)    );
	double antimediumbgpred_err = sqrt(  pow(   ((antimediumeff * ( CR2counts_err + nonQCDbgerr ))/( 1. - antimediumeff))    , 2.)   +   pow(   (((double)CR2counts * antimediumeff_err)/(pow( (1 - antimediumeff) ,2.)))    , 2.)    );
	double antiloosebgpred_err = sqrt(  pow(   ((antilooseeff * ( CR2counts_err + nonQCDbgerr ))/( 1. - antilooseeff))    , 2.)   +   pow(   (((double)CR2counts * antilooseeff_err)/(pow( (1 - antilooseeff) ,2.)))    , 2.)    );


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
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout <<"One tight region-- "<< "BG Prediction: " << onetightbgpred<< " +- "<< onetightbgpred_err << endl;
	cout <<"Anti tight region-- "<<	"BG Prediction: " << antitightbgpred<< " +- "<< antitightbgpred_err << endl;
	cout <<"Anti medium region-- "<< "BG Prediction: " << antimediumbgpred<< " +- "<< antimediumbgpred_err << endl;
	cout <<"Anti loose region-- "<<	"BG Prediction: " << antiloosebgpred<< " +- "<< antiloosebgpred_err << endl;
	cout << endl;
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
	cout << endl;
	cout << "BG Prediction#" << endl;
	cout << "$N^{QCD}_{SR}$    &$ " << onetightbgpred << "\\pm" << onetightbgpred_err << 
		" $  &$ " << antitightbgpred << "\\pm" << antitightbgpred_err << 
		" $  &$ " << antimediumbgpred << "\\pm" << antimediumbgpred_err <<
	        " $  &$ " << antiloosebgpred << "\\pm" << antiloosebgpred_err <<	" $ \\\\" << endl;
}
