{
#include <TROOT.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>

TFile _file0 ("effmap.root","UPDATE");

TH2F *hist=((TH2F*)(_file0->Get("h2_taufakerate_eff")))->Clone("h2_taufakerate_eff_smoothed");

for(unsigned int x=0; x<hist->GetNbinsX(); x++)
  {
  	unsigned int count=0;
	double value = -1;
	double error = -1;
	int end=-1;
  	for(unsigned int y=0; y<hist->GetNbinsY(); y++)\
	  {
	  	double binC=hist->GetBinContent(x+1,y+1);
		if(y==end)break;
		if((binC>0 && y>0) || y>0) count++;
		if(count==1)
		  {
		    double lowEdge=hist->GetYaxis()->GetBinLowEdge(y+1);
		    double highEdge=hist->GetYaxis()->GetBinLowEdge(hist->GetNbinsY()-y+1);
		    TF1 *const=new TF1("const","[0]");
		    TH1F *projection=(TH1F*)hist->ProjectionY("py",x+1,x+1);
		    projection->Fit(const,"RF","",lowEdge,highEdge);
		    value = const->GetParameter(0);
		    error = const->GetParError(0);
		    std::cout<<lowEdge<<" to "<<highEdge<<" yielding "<<value<<" +/- "<<error<<std::endl;
		    end=hist->GetNbinsY()-y;
		  }
		if(value>0)
		  {
		    hist->SetBinContent(x+1,y+1,value);
		    hist->SetBinError(x+1,y+1,error);
		  }
	  }
  }
hist->Write();
}
