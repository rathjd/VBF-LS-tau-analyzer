#include "TROOT.h"
#include "TDirectory.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"
#include <vector>
#include <iostream>
#include "TLine.h"

void ResponseCorrection(double ptMin)
{


TFile _file0("ResponseAllIsos_Jet30Tau45.root","UPDATE");

TH2F *projectN=(TH2F*)_file0.Get("h2_tauResponseN")->Clone("project");
TH2F *projectL=(TH2F*)_file0.Get("h2_tauResponseL")->Clone("project");
TH2F *projectM=(TH2F*)_file0.Get("h2_tauResponseM")->Clone("project");
TH2F *projectT=(TH2F*)_file0.Get("h2_tauResponseT")->Clone("project");

double ptEdges[projectN->GetNbinsX()+1];

for(unsigned int x=0; x<projectN->GetNbinsX(); x++)
  {
    ptEdges[x]=projectN->GetXaxis()->GetBinLowEdge(x+1);
  }
ptEdges[projectN->GetNbinsX()]=2500.;


std::vector<double> EdgesN;
std::vector<double> EdgesL;
std::vector<double> EdgesM;
std::vector<double> EdgesT;
EdgesN.push_back(0);
EdgesL.push_back(0);
EdgesM.push_back(0);
EdgesT.push_back(0);
std::vector<double> RescalesN;
std::vector<double> RescalesL;
std::vector<double> RescalesM;
std::vector<double> RescalesT;
RescalesN.push_back(0);
RescalesL.push_back(0);
RescalesM.push_back(0);
RescalesT.push_back(0);
std::vector<double> scalesN;
std::vector<double> scalesL;
std::vector<double> scalesM;
std::vector<double> scalesT;
scalesN.push_back(0);
scalesL.push_back(0);
scalesM.push_back(0);
scalesT.push_back(0);

for(int p=0; p<projectN->GetNbinsX(); p++)
  {
  TH1F *histN=(TH1F*)projectN->ProjectionY(TString::Format("histN_%d",p+1),p+1,p+1);
  TH1F *histL=(TH1F*)projectL->ProjectionY(TString::Format("histL_%d",p+1),p+1,p+1);
  TH1F *histM=(TH1F*)projectM->ProjectionY(TString::Format("histM_%d",p+1),p+1,p+1);
  TH1F *histT=(TH1F*)projectT->ProjectionY(TString::Format("histT_%d",p+1),p+1,p+1);
  bool finish=false;
  if(ptEdges[p+1]>ptMin/histN->GetBinLowEdge(2))
    {
      histN=(TH1F*)projectN->ProjectionY(TString::Format("histN_%d",p+1),p+1,-1);
      histL=(TH1F*)projectL->ProjectionY(TString::Format("histN_%d",p+1),p+1,-1);
      histM=(TH1F*)projectM->ProjectionY(TString::Format("histN_%d",p+1),p+1,-1);
      histT=(TH1F*)projectT->ProjectionY(TString::Format("histN_%d",p+1),p+1,-1);
      finish=true;
    }
  if(histN->GetEntries()!=0) for(unsigned int x=histN->GetNbinsX(); x>0; x--)
    {
      double pT=ptMin/histN->GetBinLowEdge(x+1);
      if(pT<ptEdges[p]) continue;
      if(pT>=ptEdges[p+1]) break;
      EdgesN.push_back(pT);
      RescalesN.push_back(histN->Integral(x+1,-1)/histN->Integral(0,-1));
      TCanvas *c=new TCanvas("c",TString::Format("NoIso p_{T}=%.0f",pT));
      c->cd();
      histN->GetXaxis()->SetRange(0,histN->GetNbinsX()+1);
      histN->Draw();
      TLine *l=new TLine(histN->GetBinLowEdge(x+1),0,histN->GetBinLowEdge(x+1),histN->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("N_pT%.0f.png",pT));
      histN->GetXaxis()->SetRange(x,histN->GetNbinsX()+1);
      scalesN.push_back(histN->GetMean());
    }
  if(histL->GetEntries()!=0) for(unsigned int x=histL->GetNbinsX(); x>0; x--)
    {
      double pT=ptMin/histL->GetBinLowEdge(x+1);
      if(pT<ptEdges[p]) continue;
      if(pT>=ptEdges[p+1]) break;
      EdgesL.push_back(pT);
      RescalesL.push_back(histL->Integral(x+1,-1)/histL->Integral(0,-1));
      TCanvas *c=new TCanvas("c",TString::Format("LooseIso p_{T}=%.0f",pT));
      c->cd();
      histL->GetXaxis()->SetRange(0,histL->GetNbinsX()+1);
      histL->Draw();
      TLine *l=new TLine(histL->GetBinLowEdge(x+1),0,histL->GetBinLowEdge(x+1),histL->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("L_pT%.0f.png",pT));
      histL->GetXaxis()->SetRange(x,histL->GetNbinsX()+1);
      scalesL.push_back(histL->GetMean());
    }
  if(histM->GetEntries()!=0) for(unsigned int x=histM->GetNbinsX(); x>0; x--)
    {
      double pT=ptMin/histM->GetBinLowEdge(x+1);
      if(pT<ptEdges[p]) continue;
      if(pT>=ptEdges[p+1]) break;
      EdgesM.push_back(pT);
      RescalesM.push_back(histM->Integral(x+1,-1)/histM->Integral(0,-1));
      TCanvas *c=new TCanvas("c",TString::Format("MediumIso p_{T}=%.0f",pT));
      c->cd();
      histM->GetXaxis()->SetRange(0,histM->GetNbinsX()+1);
      histM->Draw();
      TLine *l=new TLine(histM->GetBinLowEdge(x+1),0,histM->GetBinLowEdge(x+1),histM->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("M_pT%.0f.png",pT));
      histM->GetXaxis()->SetRange(x,histM->GetNbinsX()+1);
      scalesM.push_back(histM->GetMean());
    }
  if(histT->GetEntries()!=0) for(unsigned int x=histT->GetNbinsX(); x>0; x--)
    {
      double pT=ptMin/histT->GetBinLowEdge(x+1);
      if(pT<ptEdges[p]) continue;
      if(pT>=ptEdges[p+1]) break;
      EdgesT.push_back(pT);
      RescalesT.push_back(histT->Integral(x+1,-1)/histT->Integral(0,-1));
      TCanvas *c=new TCanvas("c",TString::Format("TightIso p_{T}=%.0f",pT));
      c->cd();
      histT->GetXaxis()->SetRange(0,histT->GetNbinsX()+1);
      histT->Draw();
      TLine *l=new TLine(histT->GetBinLowEdge(x+1),0,histT->GetBinLowEdge(x+1),histT->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("T_pT%.0f.png",pT));
      histT->GetXaxis()->SetRange(x,histT->GetNbinsX()+1);
      scalesT.push_back(histT->GetMean());
    }
    if(finish)break;
  }
EdgesN.push_back(2500.);
EdgesL.push_back(2500.);
EdgesM.push_back(2500.);
EdgesT.push_back(2500.);
/*for(int i=0; i<hist->GetNbinsX()+1; i++)
{std::cout<<Edges[i]<<std::endl;}*/ 
  
double EdgeN[EdgesN.size()];  
for(unsigned int i=0; i<EdgesN.size(); i++)
  {
    EdgeN[i]=EdgesN[i];
    //std::cout<<EdgesN[i]<<std::endl;
    //std::cout<<RescalesN[i]<<" and "<<scalesN[i]<<std::endl;
  } 
double EdgeL[EdgesL.size()];  
for(unsigned int i=0; i<EdgesL.size(); i++)
  {
    EdgeL[i]=EdgesL[i];
    //std::cout<<EdgesL[i]<<std::endl;
    //std::cout<<RescalesL[i]<<" and "<<scalesL[i]<<std::endl;
  }   
double EdgeM[EdgesM.size()];  
for(unsigned int i=0; i<EdgesM.size(); i++)
  {
    EdgeM[i]=EdgesM[i];
    //std::cout<<EdgesM[i]<<std::endl;
    //std::cout<<RescalesM[i]<<" and "<<scalesM[i]<<std::endl;
  }   
double EdgeT[EdgesT.size()];  
for(unsigned int i=0; i<EdgesT.size(); i++)
  {
    EdgeT[i]=EdgesT[i];
    //std::cout<<EdgesT[i]<<std::endl;
    //std::cout<<RescalesT[i]<<" and "<<scalesT[i]<<std::endl;
  }    
  
TH1F *scaleN=new TH1F("scaleN","NoIso scale correction", EdgesN.size()-1, EdgeN);
scaleN->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleN->SetEntries(1);
TH1F *scaleL=new TH1F("scaleL","LooseIso scale correction", EdgesL.size()-1, EdgeL);
scaleL->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleL->SetEntries(1);
TH1F *scaleM=new TH1F("scaleM","MediumIso scale correction", EdgesM.size()-1, EdgeM);
scaleM->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleM->SetEntries(1);
TH1F *scaleT=new TH1F("scaleT","TightIso scale correction", EdgesT.size()-1, EdgeT);
scaleT->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleT->SetEntries(1);

TH1F *RescaleWeightN=new TH1F("RescaleWeightN","NoIso weight correction", EdgesN.size()-1, EdgeN);
RescaleWeightN->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightN->SetEntries(1);
TH1F *RescaleWeightL=new TH1F("RescaleWeightL","LooseIso weight correction", EdgesL.size()-1, EdgeL);
RescaleWeightL->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightL->SetEntries(1);
TH1F *RescaleWeightM=new TH1F("RescaleWeightM","MediumIso weight correction", EdgesM.size()-1, EdgeM);
RescaleWeightM->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightM->SetEntries(1);
TH1F *RescaleWeightT=new TH1F("RescaleWeightT","TightIso weight correction", EdgesT.size()-1, EdgeT);
RescaleWeightT->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightT->SetEntries(1);

for(unsigned int x=0; x<RescalesN.size(); x++)
  {
    RescaleWeightN->SetBinContent(x+1,RescalesN[x]);
    scaleN->SetBinContent(x+1,scalesN[x]);
  }
for(unsigned int x=0; x<RescalesL.size(); x++)
  {
    RescaleWeightL->SetBinContent(x+1,RescalesL[x]);
    scaleL->SetBinContent(x+1,scalesL[x]);
  }
for(unsigned int x=0; x<RescalesM.size(); x++)
  {
    RescaleWeightM->SetBinContent(x+1,RescalesM[x]);
    scaleM->SetBinContent(x+1,scalesM[x]);
  }
for(unsigned int x=0; x<RescalesT.size(); x++)
  {
    RescaleWeightT->SetBinContent(x+1,RescalesT[x]);
    scaleT->SetBinContent(x+1,scalesT[x]);
  }

TFile *f=new TFile("ResponseFactorsAllIsos_Jet30Tau45_15up.root","RECREATE");
RescaleWeightN->Write();
RescaleWeightL->Write();
RescaleWeightM->Write();
RescaleWeightT->Write();
scaleN->Write();
scaleL->Write();
scaleM->Write();
scaleT->Write();

f->Close();
_file0.Close();
}
