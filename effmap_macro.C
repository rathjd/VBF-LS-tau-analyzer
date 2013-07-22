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

cout<<"end"<<endl;

}

