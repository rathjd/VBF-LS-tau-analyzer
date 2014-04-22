#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include "TMath.h"
#include "TF1.h"
#include "TString.h"

void PoissonianMagic()
{
  TFile file_PUnum("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/DataPUFile_22Jan2013ReReco_Run2012.root", "read");
  TFile file_PUden("/nfs/dust/cms/user/rathjd/VBF-LS-tau/PU/S10MC_PUFile.root", "read");
  
  TH1F *data = (TH1F*)file_PUnum.Get("analyzeHiMassTau/NVertices_0");
  data->Scale(1/data->Integral(0,-1));
  TH1F *MC   = (TH1F*)file_PUden.Get("analyzeHiMassTau/NVertices_0");
  MC->Scale(1/MC->Integral(0,-1));
  
  //define empty histograms for the smeared versions
  TH1F *num = (TH1F*)data->Clone("ratio");
  for(int i=0; i<num->GetNbinsX(); i++) num->SetBinContent(i+1,0);
  TH1F *den = (TH1F*)data->Clone("MC");
  for(int i=0; i<den->GetNbinsX(); i++) den->SetBinContent(i+1,0);
  
  //generate the poissonian distributions
  for(unsigned int i=0; i<data->GetNbinsX(); i++){
    TF1 *Pd = new TF1("Pd", "TMath::PoissonI(x,[0])",0,100);
    Pd->SetParameter(0,data->GetBinLowEdge(i+1));
    std::cout<<data->GetBinLowEdge(i+1)<<std::endl;
    TF1 *Pm = new TF1("Pm", "TMath::PoissonI(x,[0])",0,100);
    Pm->SetParameter(0,MC->GetBinLowEdge(i+1));
    //add up the poissonians
    for(unsigned int j=0; j<data->GetNbinsX(); j++){
      num->SetBinContent(j+1,num->GetBinContent(j+1)+Pd->Eval(j)/Pd->Integral(0,100)*data->GetBinContent(i+1));
      den->SetBinContent(j+1,den->GetBinContent(j+1)+Pm->Eval(j)/Pm->Integral(0,100)*MC->GetBinContent(i+1));
    }
  }
  
  //make the ratio and save the result
  num->Divide(den);
  
  TFile *f=new TFile("PUreweightHistogram.root","RECREATE");
  num->Write();
  den->Write();
  
  f->Close();
  file_PUnum.Close();
  file_PUden.Close();
}
