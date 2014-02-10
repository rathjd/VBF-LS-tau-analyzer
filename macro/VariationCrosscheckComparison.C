#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TCanvas.h"

void VariationCrosscheckComparison()
{

TFile Dice ("MonoTauDice_FqFix.root","UPDATE");
TFile MC ("MonoTauRead_NoPt15-30.root","UPDATE");


TH1F *tau1pt_SR=(TH1F*)MC.Get("VBF/h_tau1pt")->Clone("tau1pt_SR");
tau1pt_SR->SetLineColor(1);
TH1F *tau1pt_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_tau1pt")->Clone("tau1pt_SR_Nq_Fq");
tau1pt_SR_Nq_Fq->SetLineColor(2);
TH1F *tau1pt_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_tau1pt")->Clone("tau1pt_SR_Nq_pT");
tau1pt_SR_Nq_pT->SetLineColor(3);
TH1F *tau1pt_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_tau1pt")->Clone("tau1pt_SR_Nq_Abseta");
tau1pt_SR_Nq_Abseta->SetLineColor(4);
TH1F *tau1pt_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_tau1pt")->Clone("tau1pt_SR_Fq_pT");
tau1pt_SR_Fq_pT->SetLineColor(5);
TH1F *tau1pt_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_tau1pt")->Clone("tau1pt_SR_Fq_Abseta");
tau1pt_SR_Fq_Abseta->SetLineColor(6);
TH1F *tau1pt_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_tau1pt")->Clone("tau1pt_SR_pT_Abseta");
tau1pt_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_tau1pt = new TCanvas("VBF: c_SR_tau1pt", "p_{T}^{#tau_{1}}");
TLegend *leg = new TLegend(0.7,0.7,1.,1.,"samples");
leg->AddEntry(tau1pt_SR, "baseline", "l");
leg->AddEntry(tau1pt_SR_Nq_Fq, "N^{q} vs F^{q}", "l");
leg->AddEntry(tau1pt_SR_Nq_pT, "N^{q} vs p_{T}", "l");
leg->AddEntry(tau1pt_SR_Nq_Abseta, "N^{q} vs |#eta|", "l");
leg->AddEntry(tau1pt_SR_Fq_pT, "F^{q} vs p_{T}", "l");
leg->AddEntry(tau1pt_SR_Fq_Abseta, "F^{q} vs |#eta|", "l");
leg->AddEntry(tau1pt_SR_pT_Abseta, "p_{T} vs |#eta|", "l");
leg->SetFillColor(0);
tau1pt_SR->GetYaxis()->SetRangeUser(1, 1000000);
tau1pt_SR->DrawCopy();
tau1pt_SR_Nq_Fq->DrawCopy("same");
tau1pt_SR_Nq_pT->DrawCopy("same");
tau1pt_SR_Nq_Abseta->DrawCopy("same");
tau1pt_SR_Fq_pT->DrawCopy("same");
tau1pt_SR_Fq_Abseta->DrawCopy("same");
tau1pt_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_tau1pt->SetLogy(1);
c_SR_tau1pt->Update();

c_SR_tau1pt->SaveAs("SR_tau1pt.eps");

TH1F *tau1pt_CR=(TH1F*)MC.Get("invertedVBF/h_tau1pt")->Clone("tau1pt_CR");
tau1pt_CR->SetLineColor(1);
TH1F *tau1pt_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_tau1pt")->Clone("tau1pt_CR_Nq_Fq");
tau1pt_CR_Nq_Fq->SetLineColor(2);
TH1F *tau1pt_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_tau1pt")->Clone("tau1pt_CR_Nq_pT");
tau1pt_CR_Nq_pT->SetLineColor(3);
TH1F *tau1pt_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_tau1pt")->Clone("tau1pt_CR_Nq_Abseta");
tau1pt_CR_Nq_Abseta->SetLineColor(4);
TH1F *tau1pt_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_tau1pt")->Clone("tau1pt_CR_Fq_pT");
tau1pt_CR_Fq_pT->SetLineColor(5);
TH1F *tau1pt_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_tau1pt")->Clone("tau1pt_CR_Fq_Abseta");
tau1pt_CR_Fq_Abseta->SetLineColor(6);
TH1F *tau1pt_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_tau1pt")->Clone("tau1pt_CR_pT_Abseta");
tau1pt_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_tau1pt = new TCanvas("c_CR_tau1pt", "#bar{VBF}: p_{T}^{#tau_{1}}");
tau1pt_CR->GetYaxis()->SetRangeUser(1, 100000000);
tau1pt_CR->DrawCopy();
tau1pt_CR_Nq_Fq->DrawCopy("same");
tau1pt_CR_Nq_pT->DrawCopy("same");
tau1pt_CR_Nq_Abseta->DrawCopy("same");
tau1pt_CR_Fq_pT->DrawCopy("same");
tau1pt_CR_Fq_Abseta->DrawCopy("same");
tau1pt_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_tau1pt->SetLogy(1);
c_CR_tau1pt->Update();

c_CR_tau1pt->SaveAs("CR_tau1pt.eps");

//tau2pt

TH1F *tau2pt_SR=(TH1F*)MC.Get("VBF/h_tau2pt")->Clone("tau2pt_SR");
tau2pt_SR->SetLineColor(1);
TH1F *tau2pt_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_tau2pt")->Clone("tau2pt_SR_Nq_Fq");
tau2pt_SR_Nq_Fq->SetLineColor(2);
TH1F *tau2pt_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_tau2pt")->Clone("tau2pt_SR_Nq_pT");
tau2pt_SR_Nq_pT->SetLineColor(3);
TH1F *tau2pt_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_tau2pt")->Clone("tau2pt_SR_Nq_Abseta");
tau2pt_SR_Nq_Abseta->SetLineColor(4);
TH1F *tau2pt_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_tau2pt")->Clone("tau2pt_SR_Fq_pT");
tau2pt_SR_Fq_pT->SetLineColor(5);
TH1F *tau2pt_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_tau2pt")->Clone("tau2pt_SR_Fq_Abseta");
tau2pt_SR_Fq_Abseta->SetLineColor(6);
TH1F *tau2pt_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_tau2pt")->Clone("tau2pt_SR_pT_Abseta");
tau2pt_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_tau2pt = new TCanvas("VBF: c_SR_tau2pt", "p_{T}^{#tau_{2}}");
tau2pt_SR->GetYaxis()->SetRangeUser(1, 10000000);
tau2pt_SR->DrawCopy();
tau2pt_SR_Nq_Fq->DrawCopy("same");
tau2pt_SR_Nq_pT->DrawCopy("same");
tau2pt_SR_Nq_Abseta->DrawCopy("same");
tau2pt_SR_Fq_pT->DrawCopy("same");
tau2pt_SR_Fq_Abseta->DrawCopy("same");
tau2pt_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_tau2pt->SetLogy(1);
c_SR_tau2pt->Update();

c_SR_tau2pt->SaveAs("SR_tau2pt.eps");

TH1F *tau2pt_CR=(TH1F*)MC.Get("invertedVBF/h_tau2pt")->Clone("tau2pt_CR");
tau2pt_CR->SetLineColor(1);
TH1F *tau2pt_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_tau2pt")->Clone("tau2pt_CR_Nq_Fq");
tau2pt_CR_Nq_Fq->SetLineColor(2);
TH1F *tau2pt_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_tau2pt")->Clone("tau2pt_CR_Nq_pT");
tau2pt_CR_Nq_pT->SetLineColor(3);
TH1F *tau2pt_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_tau2pt")->Clone("tau2pt_CR_Nq_Abseta");
tau2pt_CR_Nq_Abseta->SetLineColor(4);
TH1F *tau2pt_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_tau2pt")->Clone("tau2pt_CR_Fq_pT");
tau2pt_CR_Fq_pT->SetLineColor(5);
TH1F *tau2pt_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_tau2pt")->Clone("tau2pt_CR_Fq_Abseta");
tau2pt_CR_Fq_Abseta->SetLineColor(6);
TH1F *tau2pt_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_tau2pt")->Clone("tau2pt_CR_pT_Abseta");
tau2pt_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_tau2pt = new TCanvas("c_CR_tau2pt", "#bar{VBF}: p_{T}^{#tau_{2}}");
tau2pt_CR->GetYaxis()->SetRangeUser(1, 100000000);
tau2pt_CR->DrawCopy();
tau2pt_CR_Nq_Fq->DrawCopy("same");
tau2pt_CR_Nq_pT->DrawCopy("same");
tau2pt_CR_Nq_Abseta->DrawCopy("same");
tau2pt_CR_Fq_pT->DrawCopy("same");
tau2pt_CR_Fq_Abseta->DrawCopy("same");
tau2pt_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_tau2pt->SetLogy(1);
c_CR_tau2pt->Update();

c_CR_tau2pt->SaveAs("CR_tau2pt.eps");

//tau1eta

TH1F *tau1eta_SR=(TH1F*)MC.Get("VBF/h_tau1eta")->Clone("tau1eta_SR");
tau1eta_SR->SetLineColor(1);
TH1F *tau1eta_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_tau1eta")->Clone("tau1eta_SR_Nq_Fq");
tau1eta_SR_Nq_Fq->SetLineColor(2);
TH1F *tau1eta_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_tau1eta")->Clone("tau1eta_SR_Nq_pT");
tau1eta_SR_Nq_pT->SetLineColor(3);
TH1F *tau1eta_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_tau1eta")->Clone("tau1eta_SR_Nq_Abseta");
tau1eta_SR_Nq_Abseta->SetLineColor(4);
TH1F *tau1eta_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_tau1eta")->Clone("tau1eta_SR_Fq_pT");
tau1eta_SR_Fq_pT->SetLineColor(5);
TH1F *tau1eta_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_tau1eta")->Clone("tau1eta_SR_Fq_Abseta");
tau1eta_SR_Fq_Abseta->SetLineColor(6);
TH1F *tau1eta_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_tau1eta")->Clone("tau1eta_SR_pT_Abseta");
tau1eta_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_tau1eta = new TCanvas("VBF: c_SR_tau1eta", "#eta^{#tau_{1}}");
tau1eta_SR->GetYaxis()->SetRangeUser(100, 1000000);
tau1eta_SR->DrawCopy();
tau1eta_SR_Nq_Fq->DrawCopy("same");
tau1eta_SR_Nq_pT->DrawCopy("same");
tau1eta_SR_Nq_Abseta->DrawCopy("same");
tau1eta_SR_Fq_pT->DrawCopy("same");
tau1eta_SR_Fq_Abseta->DrawCopy("same");
tau1eta_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_tau1eta->SetLogy(1);
c_SR_tau1eta->Update();

c_SR_tau1eta->SaveAs("SR_tau1eta.eps");

TH1F *tau1eta_CR=(TH1F*)MC.Get("invertedVBF/h_tau1eta")->Clone("tau1eta_CR");
tau1eta_CR->SetLineColor(1);
TH1F *tau1eta_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_tau1eta")->Clone("tau1eta_CR_Nq_Fq");
tau1eta_CR_Nq_Fq->SetLineColor(2);
TH1F *tau1eta_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_tau1eta")->Clone("tau1eta_CR_Nq_pT");
tau1eta_CR_Nq_pT->SetLineColor(3);
TH1F *tau1eta_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_tau1eta")->Clone("tau1eta_CR_Nq_Abseta");
tau1eta_CR_Nq_Abseta->SetLineColor(4);
TH1F *tau1eta_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_tau1eta")->Clone("tau1eta_CR_Fq_pT");
tau1eta_CR_Fq_pT->SetLineColor(5);
TH1F *tau1eta_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_tau1eta")->Clone("tau1eta_CR_Fq_Abseta");
tau1eta_CR_Fq_Abseta->SetLineColor(6);
TH1F *tau1eta_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_tau1eta")->Clone("tau1eta_CR_pT_Abseta");
tau1eta_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_tau1eta = new TCanvas("c_CR_tau1eta", "#bar{VBF}: #eta^{#tau_{1}}");
tau1eta_CR->GetYaxis()->SetRangeUser(100000, 10000000);
tau1eta_CR->DrawCopy();
tau1eta_CR_Nq_Fq->DrawCopy("same");
tau1eta_CR_Nq_pT->DrawCopy("same");
tau1eta_CR_Nq_Abseta->DrawCopy("same");
tau1eta_CR_Fq_pT->DrawCopy("same");
tau1eta_CR_Fq_Abseta->DrawCopy("same");
tau1eta_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_tau1eta->SetLogy(1);
c_CR_tau1eta->Update();

c_CR_tau1eta->SaveAs("CR_tau1eta.eps");

//tau2eta
TH1F *tau2eta_SR=(TH1F*)MC.Get("VBF/h_tau2eta")->Clone("tau2eta_SR");
tau2eta_SR->SetLineColor(1);
TH1F *tau2eta_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_tau2eta")->Clone("tau2eta_SR_Nq_Fq");
tau2eta_SR_Nq_Fq->SetLineColor(2);
TH1F *tau2eta_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_tau2eta")->Clone("tau2eta_SR_Nq_pT");
tau2eta_SR_Nq_pT->SetLineColor(3);
TH1F *tau2eta_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_tau2eta")->Clone("tau2eta_SR_Nq_Abseta");
tau2eta_SR_Nq_Abseta->SetLineColor(4);
TH1F *tau2eta_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_tau2eta")->Clone("tau2eta_SR_Fq_pT");
tau2eta_SR_Fq_pT->SetLineColor(5);
TH1F *tau2eta_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_tau2eta")->Clone("tau2eta_SR_Fq_Abseta");
tau2eta_SR_Fq_Abseta->SetLineColor(6);
TH1F *tau2eta_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_tau2eta")->Clone("tau2eta_SR_pT_Abseta");
tau2eta_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_tau2eta = new TCanvas("VBF: c_SR_tau2eta", "#eta^{#tau_{2}}");
tau2eta_SR->GetYaxis()->SetRangeUser(100, 1000000);
tau2eta_SR->DrawCopy();
tau2eta_SR_Nq_Fq->DrawCopy("same");
tau2eta_SR_Nq_pT->DrawCopy("same");
tau2eta_SR_Nq_Abseta->DrawCopy("same");
tau2eta_SR_Fq_pT->DrawCopy("same");
tau2eta_SR_Fq_Abseta->DrawCopy("same");
tau2eta_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_tau2eta->SetLogy(1);
c_SR_tau2eta->Update();

c_SR_tau2eta->SaveAs("SR_tau2eta.eps");

TH1F *tau2eta_CR=(TH1F*)MC.Get("invertedVBF/h_tau2eta")->Clone("tau2eta_CR");
tau2eta_CR->SetLineColor(1);
TH1F *tau2eta_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_tau2eta")->Clone("tau2eta_CR_Nq_Fq");
tau2eta_CR_Nq_Fq->SetLineColor(2);
TH1F *tau2eta_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_tau2eta")->Clone("tau2eta_CR_Nq_pT");
tau2eta_CR_Nq_pT->SetLineColor(3);
TH1F *tau2eta_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_tau2eta")->Clone("tau2eta_CR_Nq_Abseta");
tau2eta_CR_Nq_Abseta->SetLineColor(4);
TH1F *tau2eta_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_tau2eta")->Clone("tau2eta_CR_Fq_pT");
tau2eta_CR_Fq_pT->SetLineColor(5);
TH1F *tau2eta_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_tau2eta")->Clone("tau2eta_CR_Fq_Abseta");
tau2eta_CR_Fq_Abseta->SetLineColor(6);
TH1F *tau2eta_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_tau2eta")->Clone("tau2eta_CR_pT_Abseta");
tau2eta_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_tau2eta = new TCanvas("c_CR_tau2eta", "#bar{VBF}: #eta^{#tau_{2}}");
tau2eta_CR->GetYaxis()->SetRangeUser(10000, 10000000);
tau2eta_CR->DrawCopy();
tau2eta_CR_Nq_Fq->DrawCopy("same");
tau2eta_CR_Nq_pT->DrawCopy("same");
tau2eta_CR_Nq_Abseta->DrawCopy("same");
tau2eta_CR_Fq_pT->DrawCopy("same");
tau2eta_CR_Fq_Abseta->DrawCopy("same");
tau2eta_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_tau2eta->SetLogy(1);
c_CR_tau2eta->Update();

c_CR_tau2eta->SaveAs("CR_tau2eta.eps");

//ditaucharge
TH1F *ditaucharge_SR=(TH1F*)MC.Get("VBF/h_ditaucharge")->Clone("ditaucharge_SR");
ditaucharge_SR->SetLineColor(1);
TH1F *ditaucharge_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_ditaucharge")->Clone("ditaucharge_SR_Nq_Fq");
ditaucharge_SR_Nq_Fq->SetLineColor(2);
TH1F *ditaucharge_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_ditaucharge")->Clone("ditaucharge_SR_Nq_pT");
ditaucharge_SR_Nq_pT->SetLineColor(3);
TH1F *ditaucharge_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_ditaucharge")->Clone("ditaucharge_SR_Nq_Abseta");
ditaucharge_SR_Nq_Abseta->SetLineColor(4);
TH1F *ditaucharge_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_ditaucharge")->Clone("ditaucharge_SR_Fq_pT");
ditaucharge_SR_Fq_pT->SetLineColor(5);
TH1F *ditaucharge_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_ditaucharge")->Clone("ditaucharge_SR_Fq_Abseta");
ditaucharge_SR_Fq_Abseta->SetLineColor(6);
TH1F *ditaucharge_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_ditaucharge")->Clone("ditaucharge_SR_pT_Abseta");
ditaucharge_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_ditaucharge = new TCanvas("VBF: c_SR_ditaucharge", "q^{di-#tau}");
ditaucharge_SR->GetYaxis()->SetRangeUser(10000, 10000000);
ditaucharge_SR->DrawCopy();
ditaucharge_SR_Nq_Fq->DrawCopy("same");
ditaucharge_SR_Nq_pT->DrawCopy("same");
ditaucharge_SR_Nq_Abseta->DrawCopy("same");
ditaucharge_SR_Fq_pT->DrawCopy("same");
ditaucharge_SR_Fq_Abseta->DrawCopy("same");
ditaucharge_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_ditaucharge->SetLogy(1);
c_SR_ditaucharge->Update();

c_SR_ditaucharge->SaveAs("SR_ditaucharge.eps");

TH1F *ditaucharge_CR=(TH1F*)MC.Get("invertedVBF/h_ditaucharge")->Clone("ditaucharge_CR");
ditaucharge_CR->SetLineColor(1);
TH1F *ditaucharge_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_ditaucharge")->Clone("ditaucharge_CR_Nq_Fq");
ditaucharge_CR_Nq_Fq->SetLineColor(2);
TH1F *ditaucharge_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_ditaucharge")->Clone("ditaucharge_CR_Nq_pT");
ditaucharge_CR_Nq_pT->SetLineColor(3);
TH1F *ditaucharge_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_ditaucharge")->Clone("ditaucharge_CR_Nq_Abseta");
ditaucharge_CR_Nq_Abseta->SetLineColor(4);
TH1F *ditaucharge_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_ditaucharge")->Clone("ditaucharge_CR_Fq_pT");
ditaucharge_CR_Fq_pT->SetLineColor(5);
TH1F *ditaucharge_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_ditaucharge")->Clone("ditaucharge_CR_Fq_Abseta");
ditaucharge_CR_Fq_Abseta->SetLineColor(6);
TH1F *ditaucharge_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_ditaucharge")->Clone("ditaucharge_CR_pT_Abseta");
ditaucharge_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_ditaucharge = new TCanvas("c_CR_ditaucharge", "#bar{VBF}: q^{di-#tau}");
ditaucharge_CR->GetYaxis()->SetRangeUser(1000000, 1000000000000);
ditaucharge_CR->DrawCopy();
ditaucharge_CR_Nq_Fq->DrawCopy("same");
ditaucharge_CR_Nq_pT->DrawCopy("same");
ditaucharge_CR_Nq_Abseta->DrawCopy("same");
ditaucharge_CR_Fq_pT->DrawCopy("same");
ditaucharge_CR_Fq_Abseta->DrawCopy("same");
ditaucharge_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_ditaucharge->SetLogy(1);
c_CR_ditaucharge->Update();

c_CR_ditaucharge->SaveAs("CR_ditaucharge.eps");

//ditauinvariantmass
TH1F *ditauinvariantmass_SR=(TH1F*)MC.Get("VBF/h_ditauinvariantmass")->Clone("ditauinvariantmass_SR");
ditauinvariantmass_SR->SetLineColor(1);
TH1F *ditauinvariantmass_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_ditauinvariantmass")->Clone("ditauinvariantmass_SR_Nq_Fq");
ditauinvariantmass_SR_Nq_Fq->SetLineColor(2);
TH1F *ditauinvariantmass_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_ditauinvariantmass")->Clone("ditauinvariantmass_SR_Nq_pT");
ditauinvariantmass_SR_Nq_pT->SetLineColor(3);
TH1F *ditauinvariantmass_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_ditauinvariantmass")->Clone("ditauinvariantmass_SR_Nq_Abseta");
ditauinvariantmass_SR_Nq_Abseta->SetLineColor(4);
TH1F *ditauinvariantmass_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_ditauinvariantmass")->Clone("ditauinvariantmass_SR_Fq_pT");
ditauinvariantmass_SR_Fq_pT->SetLineColor(5);
TH1F *ditauinvariantmass_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_ditauinvariantmass")->Clone("ditauinvariantmass_SR_Fq_Abseta");
ditauinvariantmass_SR_Fq_Abseta->SetLineColor(6);
TH1F *ditauinvariantmass_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_ditauinvariantmass")->Clone("ditauinvariantmass_SR_pT_Abseta");
ditauinvariantmass_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_ditauinvariantmass = new TCanvas("VBF: c_SR_ditauinvariantmass", "M^{di-#tau}");
ditauinvariantmass_SR->GetYaxis()->SetRangeUser(1, 1000000);
ditauinvariantmass_SR->DrawCopy();
ditauinvariantmass_SR_Nq_Fq->DrawCopy("same");
ditauinvariantmass_SR_Nq_pT->DrawCopy("same");
ditauinvariantmass_SR_Nq_Abseta->DrawCopy("same");
ditauinvariantmass_SR_Fq_pT->DrawCopy("same");
ditauinvariantmass_SR_Fq_Abseta->DrawCopy("same");
ditauinvariantmass_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_ditauinvariantmass->SetLogy(1);
c_SR_ditauinvariantmass->Update();

c_SR_ditauinvariantmass->SaveAs("SR_ditauinvariantmass.eps");

TH1F *ditauinvariantmass_CR=(TH1F*)MC.Get("invertedVBF/h_ditauinvariantmass")->Clone("ditauinvariantmass_CR");
ditauinvariantmass_CR->SetLineColor(1);
TH1F *ditauinvariantmass_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_ditauinvariantmass")->Clone("ditauinvariantmass_CR_Nq_Fq");
ditauinvariantmass_CR_Nq_Fq->SetLineColor(2);
TH1F *ditauinvariantmass_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_ditauinvariantmass")->Clone("ditauinvariantmass_CR_Nq_pT");
ditauinvariantmass_CR_Nq_pT->SetLineColor(3);
TH1F *ditauinvariantmass_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_ditauinvariantmass")->Clone("ditauinvariantmass_CR_Nq_Abseta");
ditauinvariantmass_CR_Nq_Abseta->SetLineColor(4);
TH1F *ditauinvariantmass_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_ditauinvariantmass")->Clone("ditauinvariantmass_CR_Fq_pT");
ditauinvariantmass_CR_Fq_pT->SetLineColor(5);
TH1F *ditauinvariantmass_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_ditauinvariantmass")->Clone("ditauinvariantmass_CR_Fq_Abseta");
ditauinvariantmass_CR_Fq_Abseta->SetLineColor(6);
TH1F *ditauinvariantmass_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_ditauinvariantmass")->Clone("ditauinvariantmass_CR_pT_Abseta");
ditauinvariantmass_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_ditauinvariantmass = new TCanvas("c_CR_ditauinvariantmass", "#bar{VBF}: M^{di-#tau}");
ditauinvariantmass_CR->GetYaxis()->SetRangeUser(1, 10000000);
ditauinvariantmass_CR->DrawCopy();
ditauinvariantmass_CR_Nq_Fq->DrawCopy("same");
ditauinvariantmass_CR_Nq_pT->DrawCopy("same");
ditauinvariantmass_CR_Nq_Abseta->DrawCopy("same");
ditauinvariantmass_CR_Fq_pT->DrawCopy("same");
ditauinvariantmass_CR_Fq_Abseta->DrawCopy("same");
ditauinvariantmass_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_ditauinvariantmass->SetLogy(1);
c_CR_ditauinvariantmass->Update();

c_CR_ditauinvariantmass->SaveAs("CR_ditauinvariantmass.eps");

//h_ht
TH1F *ht_SR=(TH1F*)MC.Get("VBF/h_ht")->Clone("ht_SR");
ht_SR->SetLineColor(1);
TH1F *ht_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_ht")->Clone("ht_SR_Nq_Fq");
ht_SR_Nq_Fq->SetLineColor(2);
TH1F *ht_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_ht")->Clone("ht_SR_Nq_pT");
ht_SR_Nq_pT->SetLineColor(3);
TH1F *ht_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_ht")->Clone("ht_SR_Nq_Abseta");
ht_SR_Nq_Abseta->SetLineColor(4);
TH1F *ht_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_ht")->Clone("ht_SR_Fq_pT");
ht_SR_Fq_pT->SetLineColor(5);
TH1F *ht_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_ht")->Clone("ht_SR_Fq_Abseta");
ht_SR_Fq_Abseta->SetLineColor(6);
TH1F *ht_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_ht")->Clone("ht_SR_pT_Abseta");
ht_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_ht = new TCanvas("VBF: c_SR_ht", "H_{T}");
ht_SR->GetYaxis()->SetRangeUser(1, 1000000);
ht_SR->DrawCopy();
ht_SR_Nq_Fq->DrawCopy("same");
ht_SR_Nq_pT->DrawCopy("same");
ht_SR_Nq_Abseta->DrawCopy("same");
ht_SR_Fq_pT->DrawCopy("same");
ht_SR_Fq_Abseta->DrawCopy("same");
ht_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_ht->SetLogy(1);
c_SR_ht->Update();

c_SR_ht->SaveAs("SR_ht.eps");

TH1F *ht_CR=(TH1F*)MC.Get("invertedVBF/h_ht")->Clone("ht_CR");
ht_CR->SetLineColor(1);
TH1F *ht_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_ht")->Clone("ht_CR_Nq_Fq");
ht_CR_Nq_Fq->SetLineColor(2);
TH1F *ht_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_ht")->Clone("ht_CR_Nq_pT");
ht_CR_Nq_pT->SetLineColor(3);
TH1F *ht_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_ht")->Clone("ht_CR_Nq_Abseta");
ht_CR_Nq_Abseta->SetLineColor(4);
TH1F *ht_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_ht")->Clone("ht_CR_Fq_pT");
ht_CR_Fq_pT->SetLineColor(5);
TH1F *ht_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_ht")->Clone("ht_CR_Fq_Abseta");
ht_CR_Fq_Abseta->SetLineColor(6);
TH1F *ht_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_ht")->Clone("ht_CR_pT_Abseta");
ht_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_ht = new TCanvas("c_CR_ht", "#bar{VBF}: H_{T}");
ht_CR->GetYaxis()->SetRangeUser(1, 100000000);
ht_CR->DrawCopy();
ht_CR_Nq_Fq->DrawCopy("same");
ht_CR_Nq_pT->DrawCopy("same");
ht_CR_Nq_Abseta->DrawCopy("same");
ht_CR_Fq_pT->DrawCopy("same");
ht_CR_Fq_Abseta->DrawCopy("same");
ht_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_ht->SetLogy(1);
c_CR_ht->Update();

c_CR_ht->SaveAs("CR_ht.eps");

//h_ht_withtau
TH1F *ht_withtau_SR=(TH1F*)MC.Get("VBF/h_ht_withtau")->Clone("ht_withtau_SR");
ht_withtau_SR->SetLineColor(1);
TH1F *ht_withtau_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_ht_withtau")->Clone("ht_withtau_SR_Nq_Fq");
ht_withtau_SR_Nq_Fq->SetLineColor(2);
TH1F *ht_withtau_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_ht_withtau")->Clone("ht_withtau_SR_Nq_pT");
ht_withtau_SR_Nq_pT->SetLineColor(3);
TH1F *ht_withtau_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_ht_withtau")->Clone("ht_withtau_SR_Nq_Abseta");
ht_withtau_SR_Nq_Abseta->SetLineColor(4);
TH1F *ht_withtau_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_ht_withtau")->Clone("ht_withtau_SR_Fq_pT");
ht_withtau_SR_Fq_pT->SetLineColor(5);
TH1F *ht_withtau_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_ht_withtau")->Clone("ht_withtau_SR_Fq_Abseta");
ht_withtau_SR_Fq_Abseta->SetLineColor(6);
TH1F *ht_withtau_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_ht_withtau")->Clone("ht_withtau_SR_pT_Abseta");
ht_withtau_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_ht_withtau = new TCanvas("VBF: c_SR_ht_withtau", "H_{T}+#tau");
ht_withtau_SR->GetYaxis()->SetRangeUser(1, 1000000);
ht_withtau_SR->DrawCopy();
ht_withtau_SR_Nq_Fq->DrawCopy("same");
ht_withtau_SR_Nq_pT->DrawCopy("same");
ht_withtau_SR_Nq_Abseta->DrawCopy("same");
ht_withtau_SR_Fq_pT->DrawCopy("same");
ht_withtau_SR_Fq_Abseta->DrawCopy("same");
ht_withtau_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_ht_withtau->SetLogy(1);
c_SR_ht_withtau->Update();

c_SR_ht_withtau->SaveAs("SR_ht_withtau.eps");

TH1F *ht_withtau_CR=(TH1F*)MC.Get("invertedVBF/h_ht_withtau")->Clone("ht_withtau_CR");
ht_withtau_CR->SetLineColor(1);
TH1F *ht_withtau_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_ht_withtau")->Clone("ht_withtau_CR_Nq_Fq");
ht_withtau_CR_Nq_Fq->SetLineColor(2);
TH1F *ht_withtau_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_ht_withtau")->Clone("ht_withtau_CR_Nq_pT");
ht_withtau_CR_Nq_pT->SetLineColor(3);
TH1F *ht_withtau_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_ht_withtau")->Clone("ht_withtau_CR_Nq_Abseta");
ht_withtau_CR_Nq_Abseta->SetLineColor(4);
TH1F *ht_withtau_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_ht_withtau")->Clone("ht_withtau_CR_Fq_pT");
ht_withtau_CR_Fq_pT->SetLineColor(5);
TH1F *ht_withtau_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_ht_withtau")->Clone("ht_withtau_CR_Fq_Abseta");
ht_withtau_CR_Fq_Abseta->SetLineColor(6);
TH1F *ht_withtau_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_ht_withtau")->Clone("ht_withtau_CR_pT_Abseta");
ht_withtau_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_ht_withtau = new TCanvas("c_CR_ht_withtau", "#bar{VBF}: H_{T}+#tau");
ht_withtau_CR->GetYaxis()->SetRangeUser(1, 100000000);
ht_withtau_CR->DrawCopy();
ht_withtau_CR_Nq_Fq->DrawCopy("same");
ht_withtau_CR_Nq_pT->DrawCopy("same");
ht_withtau_CR_Nq_Abseta->DrawCopy("same");
ht_withtau_CR_Fq_pT->DrawCopy("same");
ht_withtau_CR_Fq_Abseta->DrawCopy("same");
ht_withtau_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_ht_withtau->SetLogy(1);
c_CR_ht_withtau->Update();

c_CR_ht_withtau->SaveAs("CR_ht_withtau.eps");

//h_met
TH1F *met_SR=(TH1F*)MC.Get("VBF/h_met")->Clone("met_SR");
met_SR->SetLineColor(1);
TH1F *met_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_met")->Clone("met_SR_Nq_Fq");
met_SR_Nq_Fq->SetLineColor(2);
TH1F *met_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_met")->Clone("met_SR_Nq_pT");
met_SR_Nq_pT->SetLineColor(3);
TH1F *met_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_met")->Clone("met_SR_Nq_Abseta");
met_SR_Nq_Abseta->SetLineColor(4);
TH1F *met_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_met")->Clone("met_SR_Fq_pT");
met_SR_Fq_pT->SetLineColor(5);
TH1F *met_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_met")->Clone("met_SR_Fq_Abseta");
met_SR_Fq_Abseta->SetLineColor(6);
TH1F *met_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_met")->Clone("met_SR_pT_Abseta");
met_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_met = new TCanvas("VBF: c_SR_met", "E_{T}^{miss}");
met_SR->GetYaxis()->SetRangeUser(1, 1000000);
met_SR->DrawCopy();
met_SR_Nq_Fq->DrawCopy("same");
met_SR_Nq_pT->DrawCopy("same");
met_SR_Nq_Abseta->DrawCopy("same");
met_SR_Fq_pT->DrawCopy("same");
met_SR_Fq_Abseta->DrawCopy("same");
met_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_met->SetLogy(1);
c_SR_met->Update();

c_SR_met->SaveAs("SR_met.eps");

TH1F *met_CR=(TH1F*)MC.Get("invertedVBF/h_met")->Clone("met_CR");
met_CR->SetLineColor(1);
TH1F *met_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_met")->Clone("met_CR_Nq_Fq");
met_CR_Nq_Fq->SetLineColor(2);
TH1F *met_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_met")->Clone("met_CR_Nq_pT");
met_CR_Nq_pT->SetLineColor(3);
TH1F *met_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_met")->Clone("met_CR_Nq_Abseta");
met_CR_Nq_Abseta->SetLineColor(4);
TH1F *met_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_met")->Clone("met_CR_Fq_pT");
met_CR_Fq_pT->SetLineColor(5);
TH1F *met_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_met")->Clone("met_CR_Fq_Abseta");
met_CR_Fq_Abseta->SetLineColor(6);
TH1F *met_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_met")->Clone("met_CR_pT_Abseta");
met_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_met = new TCanvas("c_CR_met", "#bar{VBF}: E_{T}^{miss}}");
met_CR->GetYaxis()->SetRangeUser(1, 100000000);
met_CR->DrawCopy();
met_CR_Nq_Fq->DrawCopy("same");
met_CR_Nq_pT->DrawCopy("same");
met_CR_Nq_Abseta->DrawCopy("same");
met_CR_Fq_pT->DrawCopy("same");
met_CR_Fq_Abseta->DrawCopy("same");
met_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_met->SetLogy(1);
c_CR_met->Update();

c_CR_met->SaveAs("CR_met.eps");

//h_njet
TH1F *njet_SR=(TH1F*)MC.Get("VBF/h_njet")->Clone("njet_SR");
njet_SR->SetLineColor(1);
TH1F *njet_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_njet")->Clone("njet_SR_Nq_Fq");
njet_SR_Nq_Fq->SetLineColor(2);
TH1F *njet_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_njet")->Clone("njet_SR_Nq_pT");
njet_SR_Nq_pT->SetLineColor(3);
TH1F *njet_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_njet")->Clone("njet_SR_Nq_Abseta");
njet_SR_Nq_Abseta->SetLineColor(4);
TH1F *njet_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_njet")->Clone("njet_SR_Fq_pT");
njet_SR_Fq_pT->SetLineColor(5);
TH1F *njet_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_njet")->Clone("njet_SR_Fq_Abseta");
njet_SR_Fq_Abseta->SetLineColor(6);
TH1F *njet_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_njet")->Clone("njet_SR_pT_Abseta");
njet_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_njet = new TCanvas("VBF: c_SR_njet", "N^{jet}");
njet_SR->GetYaxis()->SetRangeUser(1, 1000000);
njet_SR->DrawCopy();
njet_SR_Nq_Fq->DrawCopy("same");
njet_SR_Nq_pT->DrawCopy("same");
njet_SR_Nq_Abseta->DrawCopy("same");
njet_SR_Fq_pT->DrawCopy("same");
njet_SR_Fq_Abseta->DrawCopy("same");
njet_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_njet->SetLogy(1);
c_SR_njet->Update();

c_SR_njet->SaveAs("SR_njet.eps");

TH1F *njet_CR=(TH1F*)MC.Get("invertedVBF/h_njet")->Clone("njet_CR");
njet_CR->SetLineColor(1);
TH1F *njet_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_njet")->Clone("njet_CR_Nq_Fq");
njet_CR_Nq_Fq->SetLineColor(2);
TH1F *njet_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_njet")->Clone("njet_CR_Nq_pT");
njet_CR_Nq_pT->SetLineColor(3);
TH1F *njet_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_njet")->Clone("njet_CR_Nq_Abseta");
njet_CR_Nq_Abseta->SetLineColor(4);
TH1F *njet_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_njet")->Clone("njet_CR_Fq_pT");
njet_CR_Fq_pT->SetLineColor(5);
TH1F *njet_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_njet")->Clone("njet_CR_Fq_Abseta");
njet_CR_Fq_Abseta->SetLineColor(6);
TH1F *njet_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_njet")->Clone("njet_CR_pT_Abseta");
njet_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_njet = new TCanvas("c_CR_njet", "#bar{VBF}: N^{jet}");
njet_CR->GetYaxis()->SetRangeUser(1, 100000000);
njet_CR->DrawCopy();
njet_CR_Nq_Fq->DrawCopy("same");
njet_CR_Nq_pT->DrawCopy("same");
njet_CR_Nq_Abseta->DrawCopy("same");
njet_CR_Fq_pT->DrawCopy("same");
njet_CR_Fq_Abseta->DrawCopy("same");
njet_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_njet->SetLogy(1);
c_CR_njet->Update();

c_CR_njet->SaveAs("CR_njet.eps");

//counts
TH1F *counts_SR=(TH1F*)MC.Get("VBF/counts")->Clone("counts_SR");
counts_SR->SetLineColor(1);
TH1F *counts_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/counts")->Clone("counts_SR_Nq_Fq");
counts_SR_Nq_Fq->SetLineColor(2);
TH1F *counts_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/counts")->Clone("counts_SR_Nq_pT");
counts_SR_Nq_pT->SetLineColor(3);
TH1F *counts_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/counts")->Clone("counts_SR_Nq_Abseta");
counts_SR_Nq_Abseta->SetLineColor(4);
TH1F *counts_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/counts")->Clone("counts_SR_Fq_pT");
counts_SR_Fq_pT->SetLineColor(5);
TH1F *counts_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/counts")->Clone("counts_SR_Fq_Abseta");
counts_SR_Fq_Abseta->SetLineColor(6);
TH1F *counts_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/counts")->Clone("counts_SR_pT_Abseta");
counts_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_counts = new TCanvas("VBF: c_SR_counts", "counts");
counts_SR->GetYaxis()->SetRangeUser(10000, 100000000000000);
counts_SR->DrawCopy();
counts_SR_Nq_Fq->DrawCopy("same");
counts_SR_Nq_pT->DrawCopy("same");
counts_SR_Nq_Abseta->DrawCopy("same");
counts_SR_Fq_pT->DrawCopy("same");
counts_SR_Fq_Abseta->DrawCopy("same");
counts_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_counts->SetLogy(1);
c_SR_counts->Update();

c_SR_counts->SaveAs("SR_counts.eps");

TH1F *counts_CR=(TH1F*)MC.Get("invertedVBF/counts")->Clone("counts_CR");
counts_CR->SetLineColor(1);
TH1F *counts_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/counts")->Clone("counts_CR_Nq_Fq");
counts_CR_Nq_Fq->SetLineColor(2);
TH1F *counts_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/counts")->Clone("counts_CR_Nq_pT");
counts_CR_Nq_pT->SetLineColor(3);
TH1F *counts_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/counts")->Clone("counts_CR_Nq_Abseta");
counts_CR_Nq_Abseta->SetLineColor(4);
TH1F *counts_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/counts")->Clone("counts_CR_Fq_pT");
counts_CR_Fq_pT->SetLineColor(5);
TH1F *counts_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/counts")->Clone("counts_CR_Fq_Abseta");
counts_CR_Fq_Abseta->SetLineColor(6);
TH1F *counts_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/counts")->Clone("counts_CR_pT_Abseta");
counts_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_counts = new TCanvas("c_CR_counts", "#bar{VBF}: counts");
counts_CR->GetYaxis()->SetRangeUser(1000, 100000000000000);
counts_CR->DrawCopy();
counts_CR_Nq_Fq->DrawCopy("same");
counts_CR_Nq_pT->DrawCopy("same");
counts_CR_Nq_Abseta->DrawCopy("same");
counts_CR_Fq_pT->DrawCopy("same");
counts_CR_Fq_Abseta->DrawCopy("same");
counts_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_counts->SetLogy(1);
c_CR_counts->Update();

c_CR_counts->SaveAs("CR_counts.eps");

//h_jet1pt
TH1F *jet1pt_SR=(TH1F*)MC.Get("VBF/h_jet1pt")->Clone("jet1pt_SR");
jet1pt_SR->SetLineColor(1);
TH1F *jet1pt_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_jet1pt")->Clone("jet1pt_SR_Nq_Fq");
jet1pt_SR_Nq_Fq->SetLineColor(2);
TH1F *jet1pt_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_jet1pt")->Clone("jet1pt_SR_Nq_pT");
jet1pt_SR_Nq_pT->SetLineColor(3);
TH1F *jet1pt_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_jet1pt")->Clone("jet1pt_SR_Nq_Abseta");
jet1pt_SR_Nq_Abseta->SetLineColor(4);
TH1F *jet1pt_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_jet1pt")->Clone("jet1pt_SR_Fq_pT");
jet1pt_SR_Fq_pT->SetLineColor(5);
TH1F *jet1pt_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_jet1pt")->Clone("jet1pt_SR_Fq_Abseta");
jet1pt_SR_Fq_Abseta->SetLineColor(6);
TH1F *jet1pt_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_jet1pt")->Clone("jet1pt_SR_pT_Abseta");
jet1pt_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_jet1pt = new TCanvas("VBF: c_SR_jet1pt", "p_{T}^{jet_{1}}");
jet1pt_SR->GetYaxis()->SetRangeUser(1, 1000000);
jet1pt_SR->DrawCopy();
jet1pt_SR_Nq_Fq->DrawCopy("same");
jet1pt_SR_Nq_pT->DrawCopy("same");
jet1pt_SR_Nq_Abseta->DrawCopy("same");
jet1pt_SR_Fq_pT->DrawCopy("same");
jet1pt_SR_Fq_Abseta->DrawCopy("same");
jet1pt_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_jet1pt->SetLogy(1);
c_SR_jet1pt->Update();

c_SR_jet1pt->SaveAs("SR_jet1pt.eps");

TH1F *jet1pt_CR=(TH1F*)MC.Get("invertedVBF/h_jet1pt")->Clone("jet1pt_CR");
jet1pt_CR->SetLineColor(1);
TH1F *jet1pt_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_jet1pt")->Clone("jet1pt_CR_Nq_Fq");
jet1pt_CR_Nq_Fq->SetLineColor(2);
TH1F *jet1pt_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_jet1pt")->Clone("jet1pt_CR_Nq_pT");
jet1pt_CR_Nq_pT->SetLineColor(3);
TH1F *jet1pt_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_jet1pt")->Clone("jet1pt_CR_Nq_Abseta");
jet1pt_CR_Nq_Abseta->SetLineColor(4);
TH1F *jet1pt_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_jet1pt")->Clone("jet1pt_CR_Fq_pT");
jet1pt_CR_Fq_pT->SetLineColor(5);
TH1F *jet1pt_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_jet1pt")->Clone("jet1pt_CR_Fq_Abseta");
jet1pt_CR_Fq_Abseta->SetLineColor(6);
TH1F *jet1pt_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_jet1pt")->Clone("jet1pt_CR_pT_Abseta");
jet1pt_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_jet1pt = new TCanvas("c_CR_jet1pt", "#bar{VBF}: p_{T}^{jet_{1}}");
jet1pt_CR->GetYaxis()->SetRangeUser(1, 10000000);
jet1pt_CR->DrawCopy();
jet1pt_CR_Nq_Fq->DrawCopy("same");
jet1pt_CR_Nq_pT->DrawCopy("same");
jet1pt_CR_Nq_Abseta->DrawCopy("same");
jet1pt_CR_Fq_pT->DrawCopy("same");
jet1pt_CR_Fq_Abseta->DrawCopy("same");
jet1pt_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_jet1pt->SetLogy(1);
c_CR_jet1pt->Update();

c_CR_jet1pt->SaveAs("CR_jet1pt.eps");

//h_jet2pt
TH1F *jet2pt_SR=(TH1F*)MC.Get("VBF/h_jet2pt")->Clone("jet2pt_SR");
jet2pt_SR->SetLineColor(1);
TH1F *jet2pt_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_jet2pt")->Clone("jet2pt_SR_Nq_Fq");
jet2pt_SR_Nq_Fq->SetLineColor(2);
TH1F *jet2pt_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_jet2pt")->Clone("jet2pt_SR_Nq_pT");
jet2pt_SR_Nq_pT->SetLineColor(3);
TH1F *jet2pt_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_jet2pt")->Clone("jet2pt_SR_Nq_Abseta");
jet2pt_SR_Nq_Abseta->SetLineColor(4);
TH1F *jet2pt_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_jet2pt")->Clone("jet2pt_SR_Fq_pT");
jet2pt_SR_Fq_pT->SetLineColor(5);
TH1F *jet2pt_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_jet2pt")->Clone("jet2pt_SR_Fq_Abseta");
jet2pt_SR_Fq_Abseta->SetLineColor(6);
TH1F *jet2pt_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_jet2pt")->Clone("jet2pt_SR_pT_Abseta");
jet2pt_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_jet2pt = new TCanvas("VBF: c_SR_jet2pt", "p_{T}^{jet_{2}}");
jet2pt_SR->GetYaxis()->SetRangeUser(1, 1000000);
jet2pt_SR->DrawCopy();
jet2pt_SR_Nq_Fq->DrawCopy("same");
jet2pt_SR_Nq_pT->DrawCopy("same");
jet2pt_SR_Nq_Abseta->DrawCopy("same");
jet2pt_SR_Fq_pT->DrawCopy("same");
jet2pt_SR_Fq_Abseta->DrawCopy("same");
jet2pt_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_jet2pt->SetLogy(1);
c_SR_jet2pt->Update();

c_SR_jet2pt->SaveAs("SR_jet2pt.eps");

TH1F *jet2pt_CR=(TH1F*)MC.Get("invertedVBF/h_jet2pt")->Clone("jet2pt_CR");
jet2pt_CR->SetLineColor(1);
TH1F *jet2pt_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_jet2pt")->Clone("jet2pt_CR_Nq_Fq");
jet2pt_CR_Nq_Fq->SetLineColor(2);
TH1F *jet2pt_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_jet2pt")->Clone("jet2pt_CR_Nq_pT");
jet2pt_CR_Nq_pT->SetLineColor(3);
TH1F *jet2pt_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_jet2pt")->Clone("jet2pt_CR_Nq_Abseta");
jet2pt_CR_Nq_Abseta->SetLineColor(4);
TH1F *jet2pt_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_jet2pt")->Clone("jet2pt_CR_Fq_pT");
jet2pt_CR_Fq_pT->SetLineColor(5);
TH1F *jet2pt_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_jet2pt")->Clone("jet2pt_CR_Fq_Abseta");
jet2pt_CR_Fq_Abseta->SetLineColor(6);
TH1F *jet2pt_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_jet2pt")->Clone("jet2pt_CR_pT_Abseta");
jet2pt_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_jet2pt = new TCanvas("c_CR_jet2pt", "#bar{VBF}: p_{T}^{jet_{2}}");
jet2pt_CR->GetYaxis()->SetRangeUser(1, 10000000);
jet2pt_CR->DrawCopy();
jet2pt_CR_Nq_Fq->DrawCopy("same");
jet2pt_CR_Nq_pT->DrawCopy("same");
jet2pt_CR_Nq_Abseta->DrawCopy("same");
jet2pt_CR_Fq_pT->DrawCopy("same");
jet2pt_CR_Fq_Abseta->DrawCopy("same");
jet2pt_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_jet2pt->SetLogy(1);
c_CR_jet2pt->Update();

c_CR_jet2pt->SaveAs("CR_jet2pt.eps");

//h_jet1eta
TH1F *jet1eta_SR=(TH1F*)MC.Get("VBF/h_jet1eta")->Clone("jet1eta_SR");
jet1eta_SR->SetLineColor(1);
TH1F *jet1eta_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_jet1eta")->Clone("jet1eta_SR_Nq_Fq");
jet1eta_SR_Nq_Fq->SetLineColor(2);
TH1F *jet1eta_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_jet1eta")->Clone("jet1eta_SR_Nq_pT");
jet1eta_SR_Nq_pT->SetLineColor(3);
TH1F *jet1eta_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_jet1eta")->Clone("jet1eta_SR_Nq_Abseta");
jet1eta_SR_Nq_Abseta->SetLineColor(4);
TH1F *jet1eta_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_jet1eta")->Clone("jet1eta_SR_Fq_pT");
jet1eta_SR_Fq_pT->SetLineColor(5);
TH1F *jet1eta_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_jet1eta")->Clone("jet1eta_SR_Fq_Abseta");
jet1eta_SR_Fq_Abseta->SetLineColor(6);
TH1F *jet1eta_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_jet1eta")->Clone("jet1eta_SR_pT_Abseta");
jet1eta_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_jet1eta = new TCanvas("VBF: c_SR_jet1eta", "#eta^{jet_{1}}");
jet1eta_SR->GetYaxis()->SetRangeUser(1, 1000000);
jet1eta_SR->DrawCopy();
jet1eta_SR_Nq_Fq->DrawCopy("same");
jet1eta_SR_Nq_pT->DrawCopy("same");
jet1eta_SR_Nq_Abseta->DrawCopy("same");
jet1eta_SR_Fq_pT->DrawCopy("same");
jet1eta_SR_Fq_Abseta->DrawCopy("same");
jet1eta_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_jet1eta->SetLogy(1);
c_SR_jet1eta->Update();

c_SR_jet1eta->SaveAs("SR_jet1eta.eps");

TH1F *jet1eta_CR=(TH1F*)MC.Get("invertedVBF/h_jet1eta")->Clone("jet1eta_CR");
jet1eta_CR->SetLineColor(1);
TH1F *jet1eta_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_jet1eta")->Clone("jet1eta_CR_Nq_Fq");
jet1eta_CR_Nq_Fq->SetLineColor(2);
TH1F *jet1eta_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_jet1eta")->Clone("jet1eta_CR_Nq_pT");
jet1eta_CR_Nq_pT->SetLineColor(3);
TH1F *jet1eta_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_jet1eta")->Clone("jet1eta_CR_Nq_Abseta");
jet1eta_CR_Nq_Abseta->SetLineColor(4);
TH1F *jet1eta_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_jet1eta")->Clone("jet1eta_CR_Fq_pT");
jet1eta_CR_Fq_pT->SetLineColor(5);
TH1F *jet1eta_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_jet1eta")->Clone("jet1eta_CR_Fq_Abseta");
jet1eta_CR_Fq_Abseta->SetLineColor(6);
TH1F *jet1eta_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_jet1eta")->Clone("jet1eta_CR_pT_Abseta");
jet1eta_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_jet1eta = new TCanvas("c_CR_jet1eta", "#bar{VBF}: #eta^{jet_{1}}");
jet1eta_CR->GetYaxis()->SetRangeUser(1, 10000000);
jet1eta_CR->DrawCopy();
jet1eta_CR_Nq_Fq->DrawCopy("same");
jet1eta_CR_Nq_pT->DrawCopy("same");
jet1eta_CR_Nq_Abseta->DrawCopy("same");
jet1eta_CR_Fq_pT->DrawCopy("same");
jet1eta_CR_Fq_Abseta->DrawCopy("same");
jet1eta_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_jet1eta->SetLogy(1);
c_CR_jet1eta->Update();

c_CR_jet1eta->SaveAs("CR_jet1eta.eps");

//h_jet2eta
TH1F *jet2eta_SR=(TH1F*)MC.Get("VBF/h_jet2eta")->Clone("jet2eta_SR");
jet2eta_SR->SetLineColor(1);
TH1F *jet2eta_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_jet2eta")->Clone("jet2eta_SR_Nq_Fq");
jet2eta_SR_Nq_Fq->SetLineColor(2);
TH1F *jet2eta_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_jet2eta")->Clone("jet2eta_SR_Nq_pT");
jet2eta_SR_Nq_pT->SetLineColor(3);
TH1F *jet2eta_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_jet2eta")->Clone("jet2eta_SR_Nq_Abseta");
jet2eta_SR_Nq_Abseta->SetLineColor(4);
TH1F *jet2eta_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_jet2eta")->Clone("jet2eta_SR_Fq_pT");
jet2eta_SR_Fq_pT->SetLineColor(5);
TH1F *jet2eta_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_jet2eta")->Clone("jet2eta_SR_Fq_Abseta");
jet2eta_SR_Fq_Abseta->SetLineColor(6);
TH1F *jet2eta_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_jet2eta")->Clone("jet2eta_SR_pT_Abseta");
jet2eta_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_jet2eta = new TCanvas("VBF: c_SR_jet2eta", "#eta^{jet_{2}}");
jet2eta_SR->GetYaxis()->SetRangeUser(1, 1000000);
jet2eta_SR->DrawCopy();
jet2eta_SR_Nq_Fq->DrawCopy("same");
jet2eta_SR_Nq_pT->DrawCopy("same");
jet2eta_SR_Nq_Abseta->DrawCopy("same");
jet2eta_SR_Fq_pT->DrawCopy("same");
jet2eta_SR_Fq_Abseta->DrawCopy("same");
jet2eta_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_jet2eta->SetLogy(1);
c_SR_jet2eta->Update();

c_SR_jet2eta->SaveAs("SR_jet2eta.eps");

TH1F *jet2eta_CR=(TH1F*)MC.Get("invertedVBF/h_jet2eta")->Clone("jet2eta_CR");
jet2eta_CR->SetLineColor(1);
TH1F *jet2eta_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_jet2eta")->Clone("jet2eta_CR_Nq_Fq");
jet2eta_CR_Nq_Fq->SetLineColor(2);
TH1F *jet2eta_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_jet2eta")->Clone("jet2eta_CR_Nq_pT");
jet2eta_CR_Nq_pT->SetLineColor(3);
TH1F *jet2eta_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_jet2eta")->Clone("jet2eta_CR_Nq_Abseta");
jet2eta_CR_Nq_Abseta->SetLineColor(4);
TH1F *jet2eta_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_jet2eta")->Clone("jet2eta_CR_Fq_pT");
jet2eta_CR_Fq_pT->SetLineColor(5);
TH1F *jet2eta_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_jet2eta")->Clone("jet2eta_CR_Fq_Abseta");
jet2eta_CR_Fq_Abseta->SetLineColor(6);
TH1F *jet2eta_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_jet2eta")->Clone("jet2eta_CR_pT_Abseta");
jet2eta_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_jet2eta = new TCanvas("c_CR_jet2eta", "#bar{VBF}: #eta^{jet_{2}}");
jet2eta_CR->GetYaxis()->SetRangeUser(1, 10000000);
jet2eta_CR->DrawCopy();
jet2eta_CR_Nq_Fq->DrawCopy("same");
jet2eta_CR_Nq_pT->DrawCopy("same");
jet2eta_CR_Nq_Abseta->DrawCopy("same");
jet2eta_CR_Fq_pT->DrawCopy("same");
jet2eta_CR_Fq_Abseta->DrawCopy("same");
jet2eta_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_jet2eta->SetLogy(1);
c_CR_jet2eta->Update();

c_CR_jet2eta->SaveAs("CR_jet2eta.eps");

//h_dijetinvariantmass
TH1F *dijetinvariantmass_SR=(TH1F*)MC.Get("VBF/h_dijetinvariantmass")->Clone("dijetinvariantmass_SR");
dijetinvariantmass_SR->SetLineColor(1);
TH1F *dijetinvariantmass_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_dijetinvariantmass")->Clone("dijetinvariantmass_SR_Nq_Fq");
dijetinvariantmass_SR_Nq_Fq->SetLineColor(2);
TH1F *dijetinvariantmass_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_dijetinvariantmass")->Clone("dijetinvariantmass_SR_Nq_pT");
dijetinvariantmass_SR_Nq_pT->SetLineColor(3);
TH1F *dijetinvariantmass_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_dijetinvariantmass")->Clone("dijetinvariantmass_SR_Nq_Abseta");
dijetinvariantmass_SR_Nq_Abseta->SetLineColor(4);
TH1F *dijetinvariantmass_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_dijetinvariantmass")->Clone("dijetinvariantmass_SR_Fq_pT");
dijetinvariantmass_SR_Fq_pT->SetLineColor(5);
TH1F *dijetinvariantmass_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_dijetinvariantmass")->Clone("dijetinvariantmass_SR_Fq_Abseta");
dijetinvariantmass_SR_Fq_Abseta->SetLineColor(6);
TH1F *dijetinvariantmass_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_dijetinvariantmass")->Clone("dijetinvariantmass_SR_pT_Abseta");
dijetinvariantmass_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_dijetinvariantmass = new TCanvas("VBF: c_SR_dijetinvariantmass", "M^{dijet}");
dijetinvariantmass_SR->GetYaxis()->SetRangeUser(1, 1000000);
dijetinvariantmass_SR->DrawCopy();
dijetinvariantmass_SR_Nq_Fq->DrawCopy("same");
dijetinvariantmass_SR_Nq_pT->DrawCopy("same");
dijetinvariantmass_SR_Nq_Abseta->DrawCopy("same");
dijetinvariantmass_SR_Fq_pT->DrawCopy("same");
dijetinvariantmass_SR_Fq_Abseta->DrawCopy("same");
dijetinvariantmass_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_dijetinvariantmass->SetLogy(1);
c_SR_dijetinvariantmass->Update();

c_SR_dijetinvariantmass->SaveAs("SR_dijetinvariantmass.eps");

TH1F *dijetinvariantmass_CR=(TH1F*)MC.Get("invertedVBF/h_dijetinvariantmass")->Clone("dijetinvariantmass_CR");
dijetinvariantmass_CR->SetLineColor(1);
TH1F *dijetinvariantmass_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_dijetinvariantmass")->Clone("dijetinvariantmass_CR_Nq_Fq");
dijetinvariantmass_CR_Nq_Fq->SetLineColor(2);
TH1F *dijetinvariantmass_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_dijetinvariantmass")->Clone("dijetinvariantmass_CR_Nq_pT");
dijetinvariantmass_CR_Nq_pT->SetLineColor(3);
TH1F *dijetinvariantmass_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_dijetinvariantmass")->Clone("dijetinvariantmass_CR_Nq_Abseta");
dijetinvariantmass_CR_Nq_Abseta->SetLineColor(4);
TH1F *dijetinvariantmass_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_dijetinvariantmass")->Clone("dijetinvariantmass_CR_Fq_pT");
dijetinvariantmass_CR_Fq_pT->SetLineColor(5);
TH1F *dijetinvariantmass_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_dijetinvariantmass")->Clone("dijetinvariantmass_CR_Fq_Abseta");
dijetinvariantmass_CR_Fq_Abseta->SetLineColor(6);
TH1F *dijetinvariantmass_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_dijetinvariantmass")->Clone("dijetinvariantmass_CR_pT_Abseta");
dijetinvariantmass_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_dijetinvariantmass = new TCanvas("c_CR_dijetinvariantmass", "#bar{VBF}: M^{dijet}");
dijetinvariantmass_CR->GetYaxis()->SetRangeUser(1, 10000000);
dijetinvariantmass_CR->DrawCopy();
dijetinvariantmass_CR_Nq_Fq->DrawCopy("same");
dijetinvariantmass_CR_Nq_pT->DrawCopy("same");
dijetinvariantmass_CR_Nq_Abseta->DrawCopy("same");
dijetinvariantmass_CR_Fq_pT->DrawCopy("same");
dijetinvariantmass_CR_Fq_Abseta->DrawCopy("same");
dijetinvariantmass_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_dijetinvariantmass->SetLogy(1);
c_CR_dijetinvariantmass->Update();

c_CR_dijetinvariantmass->SaveAs("CR_dijetinvariantmass.eps");

//h_dijetdeltaeta
TH1F *dijetdeltaeta_SR=(TH1F*)MC.Get("VBF/h_dijetdeltaeta")->Clone("dijetdeltaeta_SR");
dijetdeltaeta_SR->SetLineColor(1);
TH1F *dijetdeltaeta_SR_Nq_Fq=(TH1F*)Dice.Get("SR_Nq_Fq/h_dijetdeltaeta")->Clone("dijetdeltaeta_SR_Nq_Fq");
dijetdeltaeta_SR_Nq_Fq->SetLineColor(2);
TH1F *dijetdeltaeta_SR_Nq_pT=(TH1F*)Dice.Get("SR_Nq_pT/h_dijetdeltaeta")->Clone("dijetdeltaeta_SR_Nq_pT");
dijetdeltaeta_SR_Nq_pT->SetLineColor(3);
TH1F *dijetdeltaeta_SR_Nq_Abseta=(TH1F*)Dice.Get("SR_Nq_Abseta/h_dijetdeltaeta")->Clone("dijetdeltaeta_SR_Nq_Abseta");
dijetdeltaeta_SR_Nq_Abseta->SetLineColor(4);
TH1F *dijetdeltaeta_SR_Fq_pT=(TH1F*)Dice.Get("SR_Fq_pT/h_dijetdeltaeta")->Clone("dijetdeltaeta_SR_Fq_pT");
dijetdeltaeta_SR_Fq_pT->SetLineColor(5);
TH1F *dijetdeltaeta_SR_Fq_Abseta=(TH1F*)Dice.Get("SR_Fq_Abseta/h_dijetdeltaeta")->Clone("dijetdeltaeta_SR_Fq_Abseta");
dijetdeltaeta_SR_Fq_Abseta->SetLineColor(6);
TH1F *dijetdeltaeta_SR_pT_Abseta=(TH1F*)Dice.Get("SR_pT_Abseta/h_dijetdeltaeta")->Clone("dijetdeltaeta_SR_pT_Abseta");
dijetdeltaeta_SR_pT_Abseta->SetLineColor(7);

TCanvas *c_SR_dijetdeltaeta = new TCanvas("VBF: c_SR_dijetdeltaeta", "#Delta#eta^{dijet}");
dijetdeltaeta_SR->GetYaxis()->SetRangeUser(1, 1000000);
dijetdeltaeta_SR->DrawCopy();
dijetdeltaeta_SR_Nq_Fq->DrawCopy("same");
dijetdeltaeta_SR_Nq_pT->DrawCopy("same");
dijetdeltaeta_SR_Nq_Abseta->DrawCopy("same");
dijetdeltaeta_SR_Fq_pT->DrawCopy("same");
dijetdeltaeta_SR_Fq_Abseta->DrawCopy("same");
dijetdeltaeta_SR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_SR_dijetdeltaeta->SetLogy(1);
c_SR_dijetdeltaeta->Update();

c_SR_dijetdeltaeta->SaveAs("SR_dijetdeltaeta.eps");

TH1F *dijetdeltaeta_CR=(TH1F*)MC.Get("invertedVBF/h_dijetdeltaeta")->Clone("dijetdeltaeta_CR");
dijetdeltaeta_CR->SetLineColor(1);
TH1F *dijetdeltaeta_CR_Nq_Fq=(TH1F*)Dice.Get("CR_Nq_Fq/h_dijetdeltaeta")->Clone("dijetdeltaeta_CR_Nq_Fq");
dijetdeltaeta_CR_Nq_Fq->SetLineColor(2);
TH1F *dijetdeltaeta_CR_Nq_pT=(TH1F*)Dice.Get("CR_Nq_pT/h_dijetdeltaeta")->Clone("dijetdeltaeta_CR_Nq_pT");
dijetdeltaeta_CR_Nq_pT->SetLineColor(3);
TH1F *dijetdeltaeta_CR_Nq_Abseta=(TH1F*)Dice.Get("CR_Nq_Abseta/h_dijetdeltaeta")->Clone("dijetdeltaeta_CR_Nq_Abseta");
dijetdeltaeta_CR_Nq_Abseta->SetLineColor(4);
TH1F *dijetdeltaeta_CR_Fq_pT=(TH1F*)Dice.Get("CR_Fq_pT/h_dijetdeltaeta")->Clone("dijetdeltaeta_CR_Fq_pT");
dijetdeltaeta_CR_Fq_pT->SetLineColor(5);
TH1F *dijetdeltaeta_CR_Fq_Abseta=(TH1F*)Dice.Get("CR_Fq_Abseta/h_dijetdeltaeta")->Clone("dijetdeltaeta_CR_Fq_Abseta");
dijetdeltaeta_CR_Fq_Abseta->SetLineColor(6);
TH1F *dijetdeltaeta_CR_pT_Abseta=(TH1F*)Dice.Get("CR_pT_Abseta/h_dijetdeltaeta")->Clone("dijetdeltaeta_CR_pT_Abseta");
dijetdeltaeta_CR_pT_Abseta->SetLineColor(7);

TCanvas *c_CR_dijetdeltaeta = new TCanvas("c_CR_dijetdeltaeta", "#bar{VBF}: #Delta#eta^{dijet}");
dijetdeltaeta_CR->GetYaxis()->SetRangeUser(1, 10000000);
dijetdeltaeta_CR->DrawCopy();
dijetdeltaeta_CR_Nq_Fq->DrawCopy("same");
dijetdeltaeta_CR_Nq_pT->DrawCopy("same");
dijetdeltaeta_CR_Nq_Abseta->DrawCopy("same");
dijetdeltaeta_CR_Fq_pT->DrawCopy("same");
dijetdeltaeta_CR_Fq_Abseta->DrawCopy("same");
dijetdeltaeta_CR_pT_Abseta->DrawCopy("same");
leg->Draw("same");
c_CR_dijetdeltaeta->SetLogy(1);
c_CR_dijetdeltaeta->Update();

c_CR_dijetdeltaeta->SaveAs("CR_dijetdeltaeta.eps");


}
