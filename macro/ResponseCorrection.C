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


TFile _file0("ResponseLimitedJetPt_50-80only.root","READ");

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
std::vector<double> EdgesLi;
std::vector<double> EdgesM;
std::vector<double> EdgesMi;
std::vector<double> EdgesT;
EdgesN.push_back(0);
EdgesL.push_back(0);
EdgesLi.push_back(0);
EdgesM.push_back(0);
EdgesMi.push_back(0);
EdgesT.push_back(0);
std::vector<double> RescalesN;
std::vector<double> RescalesL;
std::vector<double> RescalesLi;
std::vector<double> RescalesM;
std::vector<double> RescalesMi;
std::vector<double> RescalesT;
RescalesN.push_back(0);
RescalesL.push_back(0);
RescalesLi.push_back(0);
RescalesM.push_back(0);
RescalesMi.push_back(0);
RescalesT.push_back(0);
std::vector<double> RescaleErrorsN;
std::vector<double> RescaleErrorsL;
std::vector<double> RescaleErrorsLi;
std::vector<double> RescaleErrorsM;
std::vector<double> RescaleErrorsMi;
std::vector<double> RescaleErrorsT;
RescaleErrorsN.push_back(0);
RescaleErrorsL.push_back(0);
RescaleErrorsLi.push_back(0);
RescaleErrorsM.push_back(0);
RescaleErrorsMi.push_back(0);
RescaleErrorsT.push_back(0);
std::vector<double> scalesN;
std::vector<double> scalesL;
std::vector<double> scalesLi;
std::vector<double> scalesM;
std::vector<double> scalesMi;
std::vector<double> scalesT;
scalesN.push_back(0);
scalesL.push_back(0);
scalesLi.push_back(0);
scalesM.push_back(0);
scalesMi.push_back(0);
scalesT.push_back(0);
std::vector<double> scalesErrorN;
std::vector<double> scalesErrorL;
std::vector<double> scalesErrorLi;
std::vector<double> scalesErrorM;
std::vector<double> scalesErrorMi;
std::vector<double> scalesErrorT;
scalesErrorN.push_back(0);
scalesErrorL.push_back(0);
scalesErrorLi.push_back(0);
scalesErrorM.push_back(0);
scalesErrorMi.push_back(0);
scalesErrorT.push_back(0);

for(int p=0; p<projectN->GetNbinsX(); p++)
  {
  TH1F *histN=(TH1F*)projectN->ProjectionY(TString::Format("histN_%d",p+1),p+1,p+1);
  TH1F *histL=(TH1F*)projectL->ProjectionY(TString::Format("histL_%d",p+1),p+1,p+1);
  TH1F *histLi=(TH1F*)histL->Clone("histLi");
  histLi->Add(histN);
  histLi->SetTitle("LooseInclIso #tau response");
  TH1F *histM=(TH1F*)projectM->ProjectionY(TString::Format("histM_%d",p+1),p+1,p+1);
  TH1F *histMi=(TH1F*)histL->Clone("histMi");
  histMi->Add(histLi); 
  histMi->SetTitle("MediumInclIso #tau response");
  TH1F *histT=(TH1F*)projectT->ProjectionY(TString::Format("histT_%d",p+1),p+1,p+1);
  bool finish=false;
  cout<<projectN->GetXaxis()->GetBinLowEdge(p+1)<<endl;
  /*if(ptEdges[p+1]>ptMin/histN->GetBinLowEdge(2))
    {
      histN=(TH1F*)projectN->ProjectionY(TString::Format("histN_%d",p+1),p+1,-1);
      histL=(TH1F*)projectL->ProjectionY(TString::Format("histL_%d",p+1),p+1,-1);
      histLi=(TH1F*)projectL->ProjectionY(TString::Format("histLi_%d",p+1),p+1,-1);
      histLi->SetTitle("LooseInclIso #tau response");
      histLi->Add(histN);
      histM=(TH1F*)projectM->ProjectionY(TString::Format("histM_%d",p+1),p+1,-1);
      histMi=(TH1F*)projectM->ProjectionY(TString::Format("histMi_%d",p+1),p+1,-1);
      histMi->SetTitle("MediumInclIso #tau response");
      histMi->Add(histLi);
      histT=(TH1F*)projectT->ProjectionY(TString::Format("histT_%d",p+1),p+1,-1);
      finish=true;
    }*/
  int x=22-p;
  if(histN->GetEntries()!=0)
    {
      double pT=ptMin/histN->GetBinLowEdge(x);
      cout<<histN->GetBinLowEdge(x)<<" = "<<pT<<endl;
      EdgesN.push_back(pT);
      double E1=0;
      double E2=0;
      RescalesN.push_back(histN->IntegralAndError(x,-1,E1)/histN->IntegralAndError(0,-1,E2));
      RescaleErrorsN.push_back(TMath::Sqrt(TMath::Power(E1/histN->Integral(0,-1),2)+TMath::Power(E2*histN->Integral(x,-1)/TMath::Power(histN->Integral(0,-1),2),2)));
      TCanvas *c=new TCanvas("c",TString::Format("NoIso p_{T}=%.0f",pT));
      c->cd();
      histN->GetXaxis()->SetRange(0,histN->GetNbinsX()+1);
      histN->Draw();
      TLine *l=new TLine(histN->GetBinLowEdge(x),0,histN->GetBinLowEdge(x),histN->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("N_pT%.0f.png",pT));
      histN->GetXaxis()->SetRange(p,histN->GetNbinsX()+1);
      scalesN.push_back(histN->GetMean());
      scalesErrorN.push_back(histN->GetMeanError());
    }
  if(histL->GetEntries()!=0)
    {
      double pT=ptMin/histL->GetBinLowEdge(x);
      EdgesL.push_back(pT);
      double E1=0;
      double E2=0;
      RescalesL.push_back(histL->IntegralAndError(x,-1,E1)/histL->IntegralAndError(0,-1,E2));
      RescaleErrorsL.push_back(TMath::Sqrt(TMath::Power(E1/histL->Integral(0,-1),2)+TMath::Power(E2*histL->Integral(x,-1)/TMath::Power(histL->Integral(0,-1),2),2)));
      TCanvas *c=new TCanvas("c",TString::Format("LooseIso p_{T}=%.0f",pT));
      c->cd();
      histL->GetXaxis()->SetRange(0,histL->GetNbinsX()+1);
      histL->Draw();
      TLine *l=new TLine(histL->GetBinLowEdge(x),0,histL->GetBinLowEdge(x),histL->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("L_pT%.0f.png",pT));
      histL->GetXaxis()->SetRange(p,histL->GetNbinsX()+1);
      scalesL.push_back(histL->GetMean());
      scalesErrorL.push_back(histL->GetMeanError());
    }
  if(histLi->GetEntries()!=0)
    {
      double pT=ptMin/histLi->GetBinLowEdge(x);
      EdgesLi.push_back(pT);
      double E1=0;
      double E2=0;
      RescalesLi.push_back(histLi->IntegralAndError(x,-1,E1)/histLi->IntegralAndError(0,-1,E2));
      RescaleErrorsLi.push_back(TMath::Sqrt(TMath::Power(E1/histLi->Integral(0,-1),2)+TMath::Power(E2*histLi->Integral(x,-1)/TMath::Power(histLi->Integral(0,-1),2),2)));
      TCanvas *c=new TCanvas("c",TString::Format("LooseInclIso p_{T}=%.0f",pT));
      c->cd();
      histLi->GetXaxis()->SetRange(0,histLi->GetNbinsX()+1);
      histLi->Draw();
      TLine *l=new TLine(histLi->GetBinLowEdge(x),0,histLi->GetBinLowEdge(x),histLi->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("Li_pT%.0f.png",pT));
      histLi->GetXaxis()->SetRange(p,histLi->GetNbinsX()+1);
      scalesLi.push_back(histLi->GetMean());
      scalesErrorLi.push_back(histLi->GetMeanError());
    }    
  if(histM->GetEntries()!=0)
    {
      double pT=ptMin/histM->GetBinLowEdge(x);
      EdgesM.push_back(pT);
      double E1=0;
      double E2=0;
      RescalesM.push_back(histM->IntegralAndError(x,-1,E1)/histM->IntegralAndError(0,-1,E2));
      RescaleErrorsM.push_back(TMath::Sqrt(TMath::Power(E1/histM->Integral(0,-1),2)+TMath::Power(E2*histM->Integral(x,-1)/TMath::Power(histM->Integral(0,-1),2),2)));
      TCanvas *c=new TCanvas("c",TString::Format("MediumIso p_{T}=%.0f",pT));
      c->cd();
      histM->GetXaxis()->SetRange(0,histM->GetNbinsX()+1);
      histM->Draw();
      TLine *l=new TLine(histM->GetBinLowEdge(x),0,histM->GetBinLowEdge(x),histM->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("M_pT%.0f.png",pT));
      histM->GetXaxis()->SetRange(p,histM->GetNbinsX()+1);
      scalesM.push_back(histM->GetMean());
      scalesErrorM.push_back(histM->GetMeanError());
    }
  if(histMi->GetEntries()!=0)
    {
      double pT=ptMin/histMi->GetBinLowEdge(x);
      EdgesMi.push_back(pT);
      double E1=0;
      double E2=0;
      RescalesMi.push_back(histMi->IntegralAndError(x,-1,E1)/histMi->IntegralAndError(0,-1,E2));
      RescaleErrorsMi.push_back(TMath::Sqrt(TMath::Power(E1/histMi->Integral(0,-1),2)+TMath::Power(E2*histMi->Integral(x,-1)/TMath::Power(histMi->Integral(0,-1),2),2)));
      TCanvas *c=new TCanvas("c",TString::Format("MediumInclIso p_{T}=%.0f",pT));
      c->cd();
      histMi->GetXaxis()->SetRange(0,histMi->GetNbinsX()+1);
      histMi->Draw();
      TLine *l=new TLine(histMi->GetBinLowEdge(x),0,histMi->GetBinLowEdge(x),histMi->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("Mi_pT%.0f.png",pT));
      histMi->GetXaxis()->SetRange(p,histMi->GetNbinsX()+1);
      scalesMi.push_back(histMi->GetMean());
      scalesErrorMi.push_back(histMi->GetMeanError());
    }    
  if(histT->GetEntries()!=0)
    {
      double pT=ptMin/histT->GetBinLowEdge(x);
      EdgesT.push_back(pT);
      double E1=0;
      double E2=0;
      RescalesT.push_back(histT->IntegralAndError(x,-1,E1)/histT->IntegralAndError(0,-1,E2));
      RescaleErrorsT.push_back(TMath::Sqrt(TMath::Power(E1/histT->Integral(0,-1),2)+TMath::Power(E2*histT->Integral(x,-1)/TMath::Power(histT->Integral(0,-1),2),2)));
      TCanvas *c=new TCanvas("c",TString::Format("TightIso p_{T}=%.0f",pT));
      c->cd();
      histT->GetXaxis()->SetRange(0,histT->GetNbinsX()+1);
      histT->Draw();
      TLine *l=new TLine(histT->GetBinLowEdge(x),0,histT->GetBinLowEdge(x),histT->GetMaximum());
      l->SetLineStyle(2);
      l->SetLineColor(2);
      l->Draw();
      c->SaveAs(TString::Format("T_pT%.0f.png",pT));
      histT->GetXaxis()->SetRange(p,histT->GetNbinsX()+1);
      scalesT.push_back(histT->GetMean());
      scalesErrorT.push_back(histT->GetMeanError());
    }
    if(finish)break;
  }
EdgesN.push_back(2500.);
EdgesL.push_back(2500.);
EdgesLi.push_back(2500.);
EdgesM.push_back(2500.);
EdgesMi.push_back(2500.);
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
double EdgeLi[EdgesLi.size()];  
for(unsigned int i=0; i<EdgesLi.size(); i++)
  {
    EdgeLi[i]=EdgesLi[i];
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
double EdgeMi[EdgesMi.size()];  
for(unsigned int i=0; i<EdgesMi.size(); i++)
  {
    EdgeMi[i]=EdgesMi[i];
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
scaleN->Sumw2();
TH1F *scaleL=new TH1F("scaleL","LooseIso scale correction", EdgesL.size()-1, EdgeL);
scaleL->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleL->SetEntries(1);
scaleL->Sumw2();
TH1F *scaleLi=new TH1F("scaleLi","LooseInclIso scale correction", EdgesLi.size()-1, EdgeLi);
scaleLi->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleLi->SetEntries(1);
scaleLi->Sumw2();
TH1F *scaleM=new TH1F("scaleM","MediumIso scale correction", EdgesM.size()-1, EdgeM);
scaleM->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleM->SetEntries(1);
scaleM->Sumw2();
TH1F *scaleMi=new TH1F("scaleMi","MediumInclIso scale correction", EdgesMi.size()-1, EdgeMi);
scaleMi->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleMi->SetEntries(1);
scaleMi->Sumw2();
TH1F *scaleT=new TH1F("scaleT","TightIso scale correction", EdgesT.size()-1, EdgeT);
scaleT->GetXaxis()->SetTitle("p_{T}^{jet}");
scaleT->SetEntries(1);
scaleT->Sumw2();

TH1F *RescaleWeightN=new TH1F("RescaleWeightN","NoIso weight correction", EdgesN.size()-1, EdgeN);
RescaleWeightN->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightN->SetEntries(1);
RescaleWeightN->Sumw2();
TH1F *RescaleWeightL=new TH1F("RescaleWeightL","LooseIso weight correction", EdgesL.size()-1, EdgeL);
RescaleWeightL->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightL->SetEntries(1);
RescaleWeightL->Sumw2();
TH1F *RescaleWeightLi=new TH1F("RescaleWeightLi","LooseInclIso weight correction", EdgesLi.size()-1, EdgeLi);
RescaleWeightLi->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightLi->SetEntries(1);
RescaleWeightLi->Sumw2();
TH1F *RescaleWeightM=new TH1F("RescaleWeightM","MediumIso weight correction", EdgesM.size()-1, EdgeM);
RescaleWeightM->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightM->SetEntries(1);
RescaleWeightM->Sumw2();
TH1F *RescaleWeightMi=new TH1F("RescaleWeightMi","MediumInclIso weight correction", EdgesMi.size()-1, EdgeMi);
RescaleWeightMi->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightMi->SetEntries(1);
RescaleWeightMi->Sumw2();
TH1F *RescaleWeightT=new TH1F("RescaleWeightT","TightIso weight correction", EdgesT.size()-1, EdgeT);
RescaleWeightT->GetXaxis()->SetTitle("p_{T}^{jet}");
RescaleWeightT->SetEntries(1);
RescaleWeightT->Sumw2();

for(unsigned int x=0; x<RescalesN.size(); x++)
  {
    RescaleWeightN->SetBinContent(x+1,RescalesN[x]);
    RescaleWeightN->SetBinError(x+1,RescaleErrorsN[x]);
    scaleN->SetBinContent(x+1,scalesN[x]);
    scaleN->SetBinError(x+1,scalesErrorN[x]);
  }
for(unsigned int x=0; x<RescalesL.size(); x++)
  {
    RescaleWeightL->SetBinContent(x+1,RescalesL[x]);
    RescaleWeightL->SetBinError(x+1,RescaleErrorsL[x]);
    scaleL->SetBinContent(x+1,scalesL[x]);
    scaleL->SetBinError(x+1,scalesErrorL[x]);    
  }
for(unsigned int x=0; x<RescalesLi.size(); x++)
  {
    RescaleWeightLi->SetBinContent(x+1,RescalesLi[x]);
    RescaleWeightLi->SetBinError(x+1,RescaleErrorsLi[x]);
    scaleLi->SetBinContent(x+1,scalesLi[x]);
    scaleLi->SetBinError(x+1,scalesErrorLi[x]);    
  } 
for(unsigned int x=0; x<RescalesM.size(); x++)
  {
    RescaleWeightM->SetBinContent(x+1,RescalesM[x]);
    RescaleWeightM->SetBinError(x+1,RescaleErrorsM[x]);
    scaleM->SetBinContent(x+1,scalesM[x]);
    scaleM->SetBinError(x+1,scalesErrorM[x]);    
  }
for(unsigned int x=0; x<RescalesMi.size(); x++)
  {
    RescaleWeightMi->SetBinContent(x+1,RescalesMi[x]);
    RescaleWeightMi->SetBinError(x+1,RescaleErrorsMi[x]);
    scaleMi->SetBinContent(x+1,scalesMi[x]);
    scaleMi->SetBinError(x+1,scalesErrorMi[x]);    
  }  
for(unsigned int x=0; x<RescalesT.size(); x++)
  {
    RescaleWeightT->SetBinContent(x+1,RescalesT[x]);
    RescaleWeightT->SetBinError(x+1,RescaleErrorsT[x]);
    scaleT->SetBinContent(x+1,scalesT[x]);
    scaleT->SetBinError(x+1,scalesErrorT[x]);    
  }

TFile *f=new TFile("ResponseFactors_LimitedJetPt_50-80only.root","RECREATE");
RescaleWeightN->Write();
RescaleWeightL->Write();
RescaleWeightLi->Write();
RescaleWeightM->Write();
RescaleWeightMi->Write();
RescaleWeightT->Write();
scaleN->Write();
scaleL->Write();
scaleLi->Write();
scaleM->Write();
scaleMi->Write();
scaleT->Write();

f->Close();
_file0.Close();
}
