#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH2F.h>

void effmap_macro()
{
  TFile *f=TFile::Open("AmandeepID_FlavouredMaps_PUw.root","UPDATE");

  TH2F *ChargeMapN_eff=(TH2F*)ChargeMapN_num->Clone("ChargeMapN_eff");
  ChargeMapN_eff->Divide(ChargeMapN_den);
  ChargeMapN_eff->Write();
  TH2F *ChargeMapN_eff_Uds=(TH2F*)ChargeMapN_num_Uds->Clone("ChargeMapN_eff_Uds");
  ChargeMapN_eff_Uds->Divide(ChargeMapN_den_Uds);
  ChargeMapN_eff_Uds->Write();
  TH2F *ChargeMapN_eff_C=(TH2F*)ChargeMapN_num_C->Clone("ChargeMapN_eff_C");
  ChargeMapN_eff_C->Divide(ChargeMapN_den_C);
  ChargeMapN_eff_C->Write();
  TH2F *ChargeMapN_eff_B=(TH2F*)ChargeMapN_num_B->Clone("ChargeMapN_eff_B");
  ChargeMapN_eff_B->Divide(ChargeMapN_den_B);
  ChargeMapN_eff_B->Write();
  TH2F *ChargeMapN_eff_G=(TH2F*)ChargeMapN_num_G->Clone("ChargeMapN_eff_G");
  ChargeMapN_eff_G->Divide(ChargeMapN_den_G);
  ChargeMapN_eff_G->Write();
  TH2F *ChargeMapN_eff_Un=(TH2F*)ChargeMapN_num_Un->Clone("ChargeMapN_eff_Un");
  ChargeMapN_eff_Un->Divide(ChargeMapN_den_Un);
  ChargeMapN_eff_Un->Write();

  TH2F *ChargeMapL_eff=(TH2F*)ChargeMapL_num->Clone("ChargeMapL_eff");
  ChargeMapL_eff->Divide(ChargeMapL_den);
  ChargeMapL_eff->Write();
  TH2F *ChargeMapL_eff_Uds=(TH2F*)ChargeMapL_num_Uds->Clone("ChargeMapL_eff_Uds");
  ChargeMapL_eff_Uds->Divide(ChargeMapL_den_Uds);
  ChargeMapL_eff_Uds->Write();
  TH2F *ChargeMapL_eff_C=(TH2F*)ChargeMapL_num_C->Clone("ChargeMapL_eff_C");
  ChargeMapL_eff_C->Divide(ChargeMapL_den_C);
  ChargeMapL_eff_C->Write();
  TH2F *ChargeMapL_eff_B=(TH2F*)ChargeMapL_num_B->Clone("ChargeMapL_eff_B");
  ChargeMapL_eff_B->Divide(ChargeMapL_den_B);
  ChargeMapL_eff_B->Write();
  TH2F *ChargeMapL_eff_G=(TH2F*)ChargeMapL_num_G->Clone("ChargeMapL_eff_G");
  ChargeMapL_eff_G->Divide(ChargeMapL_den_G);
  ChargeMapL_eff_G->Write();
  TH2F *ChargeMapL_eff_Un=(TH2F*)ChargeMapL_num_Un->Clone("ChargeMapL_eff_Un");
  ChargeMapL_eff_Un->Divide(ChargeMapL_den_Un);
  ChargeMapL_eff_Un->Write();

  TH2F *ChargeMapM_eff=(TH2F*)ChargeMapM_num->Clone("ChargeMapM_eff");
  ChargeMapM_eff->Divide(ChargeMapM_den);
  ChargeMapM_eff->Write();
  TH2F *ChargeMapM_eff_Uds=(TH2F*)ChargeMapM_num_Uds->Clone("ChargeMapM_eff_Uds");
  ChargeMapM_eff_Uds->Divide(ChargeMapM_den_Uds);
  ChargeMapM_eff_Uds->Write();
  TH2F *ChargeMapM_eff_C=(TH2F*)ChargeMapM_num_C->Clone("ChargeMapM_eff_C");
  ChargeMapM_eff_C->Divide(ChargeMapM_den_C);
  ChargeMapM_eff_C->Write();
  TH2F *ChargeMapM_eff_B=(TH2F*)ChargeMapM_num_B->Clone("ChargeMapM_eff_B");
  ChargeMapM_eff_B->Divide(ChargeMapM_den_B);
  ChargeMapM_eff_B->Write();
  TH2F *ChargeMapM_eff_G=(TH2F*)ChargeMapM_num_G->Clone("ChargeMapM_eff_G");
  ChargeMapM_eff_G->Divide(ChargeMapM_den_G);
  ChargeMapM_eff_G->Write();
  TH2F *ChargeMapM_eff_Un=(TH2F*)ChargeMapM_num_Un->Clone("ChargeMapM_eff_Un");
  ChargeMapM_eff_Un->Divide(ChargeMapM_den_Un);
  ChargeMapM_eff_Un->Write();

  TH2F *ChargeMapT_eff=(TH2F*)ChargeMapT_num->Clone("ChargeMapT_eff");
  ChargeMapT_eff->Divide(ChargeMapT_den);
  ChargeMapT_eff->Write();
  TH2F *ChargeMapT_eff_Uds=(TH2F*)ChargeMapT_num_Uds->Clone("ChargeMapT_eff_Uds");
  ChargeMapT_eff_Uds->Divide(ChargeMapT_den_Uds);
  ChargeMapT_eff_Uds->Write();
  TH2F *ChargeMapT_eff_C=(TH2F*)ChargeMapT_num_C->Clone("ChargeMapT_eff_C");
  ChargeMapT_eff_C->Divide(ChargeMapT_den_C);
  ChargeMapT_eff_C->Write();
  TH2F *ChargeMapT_eff_B=(TH2F*)ChargeMapT_num_B->Clone("ChargeMapT_eff_B");
  ChargeMapT_eff_B->Divide(ChargeMapT_den_B);
  ChargeMapT_eff_B->Write();
  TH2F *ChargeMapT_eff_G=(TH2F*)ChargeMapT_num_G->Clone("ChargeMapT_eff_G");
  ChargeMapT_eff_G->Divide(ChargeMapT_den_G);
  ChargeMapT_eff_G->Write();
  TH2F *ChargeMapT_eff_Un=(TH2F*)ChargeMapT_num_Un->Clone("ChargeMapT_eff_Un");
  ChargeMapT_eff_Un->Divide(ChargeMapT_den_Un);
  ChargeMapT_eff_Un->Write();

  TH2F *ChargeMapLi_eff=(TH2F*)ChargeMapLi_num->Clone("ChargeMapLi_eff");
  ChargeMapLi_eff->Divide(ChargeMapLi_den);
  ChargeMapLi_eff->Write();

  TH2F *ChargeMapMi_eff=(TH2F*)ChargeMapMi_num->Clone("ChargeMapMi_eff");
  ChargeMapMi_eff->Divide(ChargeMapMi_den);
  ChargeMapMi_eff->Write();

  f->Close();
}

