{
#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>


cout<<"begin"<<endl;

//TFile _file0 ("effmap.root","UPDATE");
TFile _file0 ("analyzer_effmap_histograms.root","UPDATE");

((TH2F*)(_file0->Get("h2_taufakerate_num")))->Clone("h2_taufakerate_eff");

((TH2F*)(_file0->Get("h2_taufakerate_eff")))->Divide((TH2F*)(_file0->Get("h2_taufakerate_den")));

((TH2F*)(_file0->Get("h2_taufakerate_eff")))->Write();

((TH1F*)(_file0->Get("h1_taufakerate_pt_num")))->Clone("h1_taufakerate_pt_eff");

((TH1F*)(_file0->Get("h1_taufakerate_pt_eff")))->Divide((TH2F*)(_file0->Get("h1_taufakerate_pt_den")));

((TH1F*)(_file0->Get("h1_taufakerate_pt_eff")))->Write();

((TH1F*)(_file0->Get("h1_taufakerate_ptjet1_num")))->Clone("h1_taufakerate_ptjet1_eff");

((TH1F*)(_file0->Get("h1_taufakerate_ptjet1_eff")))->Divide((TH2F*)(_file0->Get("h1_taufakerate_ptjet1_den")));

((TH1F*)(_file0->Get("h1_taufakerate_ptjet1_eff")))->Write();

((TH1F*)(_file0->Get("h1_taufakerate_ptjet2_num")))->Clone("h1_taufakerate_ptjet2_eff");

((TH1F*)(_file0->Get("h1_taufakerate_ptjet2_eff")))->Divide((TH2F*)(_file0->Get("h1_taufakerate_ptjet2_den")));

((TH1F*)(_file0->Get("h1_taufakerate_ptjet2_eff")))->Write();

((TH1F*)(_file0->Get("h1_taufakerate_ptjet3_num")))->Clone("h1_taufakerate_ptjet3_eff");

((TH1F*)(_file0->Get("h1_taufakerate_ptjet3_eff")))->Divide((TH2F*)(_file0->Get("h1_taufakerate_ptjet3_den")));

((TH1F*)(_file0->Get("h1_taufakerate_ptjet3_eff")))->Write();

((TH1F*)(_file0->Get("h1_taufakerate_ptjet4_num")))->Clone("h1_taufakerate_ptjet4_eff");

((TH1F*)(_file0->Get("h1_taufakerate_ptjet4_eff")))->Divide((TH2F*)(_file0->Get("h1_taufakerate_ptjet4_den")));

((TH1F*)(_file0->Get("h1_taufakerate_ptjet4_eff")))->Write();

((TH1F*)(_file0->Get("h1_taufakerate_jetrank_num")))->Clone("h1_taufakerate_jetrank_eff");

((TH1F*)(_file0->Get("h1_taufakerate_jetrank_eff")))->Divide((TH2F*)(_file0->Get("h1_taufakerate_jetrank_den")));

((TH1F*)(_file0->Get("h1_taufakerate_jetrank_eff")))->Write();

((TH2F*)(_file0->Get("h2_taufakerate_loose_num")))->Clone("h2_taufakerate_loose_eff");

((TH2F*)(_file0->Get("h2_taufakerate_loose_eff")))->Divide((TH2F*)(_file0->Get("h2_taufakerate_den")));

((TH2F*)(_file0->Get("h2_taufakerate_loose_eff")))->Write();

((TH2F*)(_file0->Get("h2_taufakerate_dR_num")))->Clone("h2_taufakerate_dR_eff");

((TH2F*)(_file0->Get("h2_taufakerate_dR_eff")))->Divide((TH2F*)(_file0->Get("h2_taufakerate_dR_den")));

((TH2F*)(_file0->Get("h2_taufakerate_dR_eff")))->Write();

((TH2F*)(_file0->Get("h2_taufakerate_dRl_num")))->Clone("h2_taufakerate_dRl_eff");

((TH2F*)(_file0->Get("h2_taufakerate_dRl_eff")))->Divide((TH2F*)(_file0->Get("h2_taufakerate_dR_den")));

((TH2F*)(_file0->Get("h2_taufakerate_dRl_eff")))->Write();

((TH2F*)(_file0->Get("h2_taufakerate_dRjet_num")))->Clone("h2_taufakerate_dRjet_eff");

((TH2F*)(_file0->Get("h2_taufakerate_dRjet_eff")))->Divide((TH2F*)(_file0->Get("h2_taufakerate_dRjet_den")));

((TH2F*)(_file0->Get("h2_taufakerate_dRjet_eff")))->Write();

((TH2F*)(_file0->Get("h2_taufakerate_dRjetl_num")))->Clone("h2_taufakerate_dRjetl_eff");

((TH2F*)(_file0->Get("h2_taufakerate_dRjetl_eff")))->Divide((TH2F*)(_file0->Get("h2_taufakerate_dRjet_den")));

((TH2F*)(_file0->Get("h2_taufakerate_dRjetl_eff")))->Write();

((TH1F*)(_file0->Get("h1_taufakescale_num")))->Clone("h1_taufakescale_fac");

((TH1F*)(_file0->Get("h1_taufakescale_fac")))->Divide((TH1F*)(_file0->Get("h1_taufakescale_den")));

((TH1F*)(_file0->Get("h1_taufakescale_fac")))->Write();

((TH1F*)(_file0->Get("h1_taufakescale_pt_num")))->Clone("h1_taufakescale_pt_fac");

((TH1F*)(_file0->Get("h1_taufakescale_pt_fac")))->Divide((TH1F*)(_file0->Get("h1_taufakescale_pt_den")));

((TH1F*)(_file0->Get("h1_taufakescale_pt_fac")))->Write();

((TH1F*)(_file0->Get("h1_taufakescale_loose_pt_num")))->Clone("h1_taufakescale_loose_pt_fac");

((TH1F*)(_file0->Get("h1_taufakescale_loose_pt_fac")))->Divide((TH1F*)(_file0->Get("h1_taufakescale_loose_pt_den")));

((TH1F*)(_file0->Get("h1_taufakescale_loose_pt_fac")))->Write();

((TH1F*)(_file0->Get("h1_taufakescale_loose_num")))->Clone("h1_taufakescale_loose_fac");

((TH1F*)(_file0->Get("h1_taufakescale_loose_fac")))->Divide((TH1F*)(_file0->Get("h1_taufakescale_loose_den")));

((TH1F*)(_file0->Get("h1_taufakescale_loose_fac")))->Write();

((TH1F*)(_file0->Get("Nod_num")))->Clone("Nod_eff");

((TH1F*)(_file0->Get("Nod_eff")))->Divide((TH1F*)(_file0->Get("Nod_den")));

((TH1F*)(_file0->Get("Nod_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMap_num")))->Clone("ChargeMap_eff");

((TH2F*)(_file0->Get("ChargeMap_eff")))->Divide((TH2F*)(_file0->Get("ChargeMap_den")));

((TH2F*)(_file0->Get("ChargeMap_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMap_loose_num")))->Clone("ChargeMap_loose_eff");

((TH2F*)(_file0->Get("ChargeMap_loose_eff")))->Divide((TH2F*)(_file0->Get("ChargeMap_den")));

((TH2F*)(_file0->Get("ChargeMap_loose_eff")))->Write();


cout<<"end"<<endl;

}

