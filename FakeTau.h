#ifndef FAKETAU_H
#define FAKETAU_H

#include <random>

struct Fake {
	std::string label;
	pair<int,int> index;
	double weight;
	
	Fake (const std::string & inputlabel){
	  label = inputlabel;
	  index.first = -1;
	  index.second = -1;
	  weight = 0.;
	}
	
	void generate(std::vector<double> jetTauFakerate){
	  bool verbose=false;
	  if(jetTauFakerate.size() < 2) return; //sanity check whether there are enough jets
		
	  vector<int> wrongs;
	  //loop over all jets
	  double probabilityZero=1.;
	  double probabilityOne=0.;
	  double maxProb=0.;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){
	        if(jetTauFakerate[i]==0) wrongs.push_back(i);
		//find probability of >0 taus
		probabilityZero *= (1. - jetTauFakerate[i]);
		maxProb += jetTauFakerate[i];
		
		//find probability of >1 taus
		double temp = jetTauFakerate[i];
		for(unsigned int j=0; j<jetTauFakerate.size(); j++){
		  if(i==j) continue;
		  temp *= (1 - jetTauFakerate[j]);
		}
		
		probabilityOne += temp;	
	  }
	  
	  //set eventweight to >= 2 tau
	  weight = 1 - probabilityZero - probabilityOne;
	  if(verbose)std::cout<<"EventWeight="<<weight<<", p0="<<probabilityZero<<", p1="<<probabilityOne<<std::endl;
	  if(wrongs.size()>jetTauFakerate.size()-2) {weight = 0; if(verbose)std::cout<<"!!!Not enough Jets!!! weight=0"<<std::endl; return;}//catch rounding errors
	  //randomize tau indizes
	  if(weight>=1) return; //sanity check
	  std::uniform_real_distribution<double> distributionOne(0.0, maxProb);
	  std::mt19937 engine; // Mersenne twister MT19937
	  
	  double TossOne=distributionOne(engine);
	  double temp=0.;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){ //choose first tau
	  	temp+=jetTauFakerate[i];
		if(jetTauFakerate[i]==0) continue;
		if(temp>=TossOne){
		  index.first=i;
		  maxProb -= jetTauFakerate[i];
		  break;
		}
	  }
	  
	  std::uniform_real_distribution<double> distributionTwo(0.0, maxProb);
	  double TossTwo=distributionTwo(engine);
	  temp = 0.;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){ //choose second tau
	  	if(i==abs(index.first)) continue;
		if(jetTauFakerate[i]==0) continue;
	  	temp+=jetTauFakerate[i];
		if(temp>=TossTwo){
		  index.second = i;
		  break;
		}
	  }
	  /*if(weight>0){
	  double p2=1;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){ //try p2 vs pg2
	  	if(i==abs(index.first) || i==abs(index.second)) p2*=jetTauFakerate[i];
		else if(jetTauFakerate[i]>0) p2*=(1-jetTauFakerate[i]);
	  }
	  if(weight-p2>p2)std::cout<<"N="<<jetTauFakerate.size()-wrongs.size()<<" and p_Diff="<<weight-p2<<std::endl;}
	  */
	  return;
	}
};

#endif
