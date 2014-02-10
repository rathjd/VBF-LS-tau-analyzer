#include "TROOT.h"
#include "TFile.h"
#include "TH2F.h"


void EffmapVariations()
{

TFile _file0 ("EffmapVariations_pTrebalance.root","UPDATE");

TH2F *h2_Nq_Fq_eff=(TH2F*)_file0.Get("h2_Nq_Fq_num")->Clone("h2_Nq_Fq_eff");
h2_Nq_Fq_eff->Divide((TH2F*)_file0.Get("h2_Nq_Fq_den"));
h2_Nq_Fq_eff->GetXaxis()->SetTitle("N^{q}");
h2_Nq_Fq_eff->GetYaxis()->SetTitle("F^{q}");
h2_Nq_Fq_eff->Write();

TH2F *h2_Nq_pT_eff=(TH2F*)_file0.Get("h2_Nq_pT_num")->Clone("h2_Nq_pT_eff");
h2_Nq_pT_eff->Divide((TH2F*)_file0.Get("h2_Nq_pT_den"));
h2_Nq_pT_eff->GetXaxis()->SetTitle("N^{q}");
h2_Nq_pT_eff->GetYaxis()->SetTitle("p_{T}");
h2_Nq_pT_eff->Write();

TH2F *h2_Nq_Abseta_eff=(TH2F*)_file0.Get("h2_Nq_Abseta_num")->Clone("h2_Nq_Abseta_eff");
h2_Nq_Abseta_eff->Divide((TH2F*)_file0.Get("h2_Nq_Abseta_den"));
h2_Nq_Abseta_eff->GetXaxis()->SetTitle("N^{q}");
h2_Nq_Abseta_eff->GetYaxis()->SetTitle("|#eta|");
h2_Nq_Abseta_eff->Write();

TH2F *h2_Fq_pT_eff=(TH2F*)_file0.Get("h2_Fq_pT_num")->Clone("h2_Fq_pT_eff");
h2_Fq_pT_eff->Divide((TH2F*)_file0.Get("h2_Fq_pT_den"));
h2_Fq_pT_eff->GetXaxis()->SetTitle("F^{q}");
h2_Fq_pT_eff->GetYaxis()->SetTitle("p_{T}");
h2_Fq_pT_eff->Write();

TH2F *h2_Fq_Abseta_eff=(TH2F*)_file0.Get("h2_Fq_Abseta_num")->Clone("h2_Fq_Abseta_eff");
h2_Fq_Abseta_eff->Divide((TH2F*)_file0.Get("h2_Fq_Abseta_den"));
h2_Nq_Abseta_eff->GetXaxis()->SetTitle("N^{q}");
h2_Nq_Abseta_eff->GetYaxis()->SetTitle("|#eta|");
h2_Fq_Abseta_eff->Write();

TH2F *h2_pT_Abseta_eff=(TH2F*)_file0.Get("h2_pT_Abseta_num")->Clone("h2_pT_Abseta_eff");
h2_pT_Abseta_eff->Divide((TH2F*)_file0.Get("h2_pT_Abseta_den"));
h2_pT_Abseta_eff->GetXaxis()->SetTitle("p_{T}^{jet}");
h2_pT_Abseta_eff->GetYaxis()->SetTitle("|#eta|");
h2_pT_Abseta_eff->Write();

_file0.Close();
}

