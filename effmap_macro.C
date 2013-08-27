{
#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>


cout<<"begin"<<endl;

TFile _file0 ("effmap.root","UPDATE");

((TH2F*)(_file0->Get("h2_taufakerate_num")))->Clone("h2_taufakerate_eff");

((TH2F*)(_file0->Get("h2_taufakerate_eff")))->Divide((TH2F*)(_file0->Get("h2_taufakerate_den")));

((TH2F*)(_file0->Get("h2_taufakerate_eff")))->Write();

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

cout<<"end"<<endl;

}

