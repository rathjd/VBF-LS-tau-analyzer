{
#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>


cout<<"begin"<<endl;

//TFile _file0 ("effmap.root","UPDATE");
TFile _file0 ("UltimateMaps.root","UPDATE");

((TH2F*)(_file0->Get("ChargeMapN_num")))->Clone("ChargeMapN_eff");

((TH2F*)(_file0->Get("ChargeMapN_eff")))->Divide((TH2F*)(_file0->Get("ChargeMapN_den")));

((TH2F*)(_file0->Get("ChargeMapN_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMapL_num")))->Clone("ChargeMapL_eff");

((TH2F*)(_file0->Get("ChargeMapL_eff")))->Divide((TH2F*)(_file0->Get("ChargeMapL_den")));

((TH2F*)(_file0->Get("ChargeMapL_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMapLi_num")))->Clone("ChargeMapLi_eff");

((TH2F*)(_file0->Get("ChargeMapLi_eff")))->Divide((TH2F*)(_file0->Get("ChargeMapLi_den")));

((TH2F*)(_file0->Get("ChargeMapLi_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMapM_num")))->Clone("ChargeMapM_eff");

((TH2F*)(_file0->Get("ChargeMapM_eff")))->Divide((TH2F*)(_file0->Get("ChargeMapM_den")));

((TH2F*)(_file0->Get("ChargeMapM_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMapMi_num")))->Clone("ChargeMapMi_eff");

((TH2F*)(_file0->Get("ChargeMapMi_eff")))->Divide((TH2F*)(_file0->Get("ChargeMapMi_den")));

((TH2F*)(_file0->Get("ChargeMapMi_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMapT_num")))->Clone("ChargeMapT_eff");

((TH2F*)(_file0->Get("ChargeMapT_eff")))->Divide((TH2F*)(_file0->Get("ChargeMapT_den")));

((TH2F*)(_file0->Get("ChargeMapT_eff")))->Write();

((TH2F*)(_file0->Get("ChargeMapT_num_Uds")))->Clone("ChargeMapT_eff_Uds");

((TH2F*)(_file0->Get("ChargeMapT_eff_Uds")))->Divide((TH2F*)(_file0->Get("ChargeMapT_den_Uds")));

((TH2F*)(_file0->Get("ChargeMapT_eff_Uds")))->Write();

((TH2F*)(_file0->Get("ChargeMapT_num_C")))->Clone("ChargeMapT_eff_C");

((TH2F*)(_file0->Get("ChargeMapT_eff_C")))->Divide((TH2F*)(_file0->Get("ChargeMapT_den_C")));

((TH2F*)(_file0->Get("ChargeMapT_eff_C")))->Write();

((TH2F*)(_file0->Get("ChargeMapT_num_B")))->Clone("ChargeMapT_eff_B");

((TH2F*)(_file0->Get("ChargeMapT_eff_B")))->Divide((TH2F*)(_file0->Get("ChargeMapT_den_B")));

((TH2F*)(_file0->Get("ChargeMapT_eff_B")))->Write();

((TH2F*)(_file0->Get("ChargeMapT_num_G")))->Clone("ChargeMapT_eff_G");

((TH2F*)(_file0->Get("ChargeMapT_eff_G")))->Divide((TH2F*)(_file0->Get("ChargeMapT_den_G")));

((TH2F*)(_file0->Get("ChargeMapT_eff_G")))->Write();

((TH2F*)(_file0->Get("ChargeMapM_num_Uds")))->Clone("ChargeMapM_eff_Uds");

((TH2F*)(_file0->Get("ChargeMapM_eff_Uds")))->Divide((TH2F*)(_file0->Get("ChargeMapM_den_Uds")));

((TH2F*)(_file0->Get("ChargeMapM_eff_Uds")))->Write();

((TH2F*)(_file0->Get("ChargeMapM_num_C")))->Clone("ChargeMapM_eff_C");

((TH2F*)(_file0->Get("ChargeMapM_eff_C")))->Divide((TH2F*)(_file0->Get("ChargeMapM_den_C")));

((TH2F*)(_file0->Get("ChargeMapM_eff_C")))->Write();

((TH2F*)(_file0->Get("ChargeMapM_num_B")))->Clone("ChargeMapM_eff_B");

((TH2F*)(_file0->Get("ChargeMapM_eff_B")))->Divide((TH2F*)(_file0->Get("ChargeMapM_den_B")));

((TH2F*)(_file0->Get("ChargeMapM_eff_B")))->Write();

((TH2F*)(_file0->Get("ChargeMapM_num_G")))->Clone("ChargeMapM_eff_G");

((TH2F*)(_file0->Get("ChargeMapM_eff_G")))->Divide((TH2F*)(_file0->Get("ChargeMapM_den_G")));

((TH2F*)(_file0->Get("ChargeMapM_eff_G")))->Write();

((TH2F*)(_file0->Get("ChargeMapL_num_Uds")))->Clone("ChargeMapL_eff_Uds");

((TH2F*)(_file0->Get("ChargeMapL_eff_Uds")))->Divide((TH2F*)(_file0->Get("ChargeMapL_den_Uds")));

((TH2F*)(_file0->Get("ChargeMapL_eff_Uds")))->Write();

((TH2F*)(_file0->Get("ChargeMapL_num_C")))->Clone("ChargeMapL_eff_C");

((TH2F*)(_file0->Get("ChargeMapL_eff_C")))->Divide((TH2F*)(_file0->Get("ChargeMapL_den_C")));

((TH2F*)(_file0->Get("ChargeMapL_eff_C")))->Write();

((TH2F*)(_file0->Get("ChargeMapL_num_B")))->Clone("ChargeMapL_eff_B");

((TH2F*)(_file0->Get("ChargeMapL_eff_B")))->Divide((TH2F*)(_file0->Get("ChargeMapL_den_B")));

((TH2F*)(_file0->Get("ChargeMapL_eff_B")))->Write();

((TH2F*)(_file0->Get("ChargeMapL_num_G")))->Clone("ChargeMapL_eff_G");

((TH2F*)(_file0->Get("ChargeMapL_eff_G")))->Divide((TH2F*)(_file0->Get("ChargeMapL_den_G")));

((TH2F*)(_file0->Get("ChargeMapL_eff_G")))->Write();

((TH2F*)(_file0->Get("ChargeMapN_num_Uds")))->Clone("ChargeMapN_eff_Uds");

((TH2F*)(_file0->Get("ChargeMapN_eff_Uds")))->Divide((TH2F*)(_file0->Get("ChargeMapN_den_Uds")));

((TH2F*)(_file0->Get("ChargeMapN_eff_Uds")))->Write();

((TH2F*)(_file0->Get("ChargeMapN_num_C")))->Clone("ChargeMapN_eff_C");

((TH2F*)(_file0->Get("ChargeMapN_eff_C")))->Divide((TH2F*)(_file0->Get("ChargeMapN_den_C")));

((TH2F*)(_file0->Get("ChargeMapN_eff_C")))->Write();

((TH2F*)(_file0->Get("ChargeMapN_num_B")))->Clone("ChargeMapN_eff_B");

((TH2F*)(_file0->Get("ChargeMapN_eff_B")))->Divide((TH2F*)(_file0->Get("ChargeMapN_den_B")));

((TH2F*)(_file0->Get("ChargeMapN_eff_B")))->Write();

((TH2F*)(_file0->Get("ChargeMapN_num_G")))->Clone("ChargeMapN_eff_G");

((TH2F*)(_file0->Get("ChargeMapN_eff_G")))->Divide((TH2F*)(_file0->Get("ChargeMapN_den_G")));

((TH2F*)(_file0->Get("ChargeMapN_eff_G")))->Write();




cout<<"end"<<endl;

}

