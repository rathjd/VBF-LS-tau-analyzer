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
	  if(jetTauFakerate.size() < 2) return; //sanity check whether there are enough jets
		
	  //loop over all jets
	  double probabilityZero=1.;
	  double probabilityOne=0.;
	  double maxProb=0.;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){
	  
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
	  
	  //randomize tau indizes
	  if(weight>=1) return; //sanity check
	  std::uniform_real_distribution<double> distributionOne(0.0, maxProb);
	  std::mt19937 engine; // Mersenne twister MT19937
	  
	  double TossOne=distributionOne(engine);
	  double temp=0.;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){ //choose first tau
	  	temp+=jetTauFakerate[i];
		if(temp>=TossOne){
		  index.first=i;
		  maxProb -= jetTauFakerate[i];
		  break;
		}
	  }
	  
	  std::uniform_real_distribution<double> distributionTwo(0.0, maxProb);
	  double TossTwo=distributionOne(engine);
	  temp = 0;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){ //choose second tau
	  	if(i==fabs(index.first)) continue;
	  	temp+=jetTauFakerate[i];
		if(temp>=TossTwo){
		  index.second = i;
		  break;
		}
	  }
	  return;
	}
};

#endif
