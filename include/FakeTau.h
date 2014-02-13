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
	
	void generate(std::vector<double> jetTauFakerate, std::vector<double> jet2TauFakerate, bool single){
	  bool verbose=false;
	  if(jetTauFakerate.size() < 2) return; //sanity check whether there are enough jets
		
	  vector<int> wrongs;
	  //loop over all jets
	  double probabilityZero=1.;
	  double probabilityOne=0.;
	  double probabilityTwo=0.;
	  double maxProb1=0.;
	  double maxProb2=0.;
	  if(single){
	    //deprecated >=2 tau version
	    /*for(unsigned int i=0; i<jetTauFakerate.size(); i++){
	        if(jetTauFakerate[i]==0) wrongs.push_back(i);
		//find probability of >0 taus
		probabilityZero *= (1. - jetTauFakerate[i]);
		maxProb1 += jetTauFakerate[i];
		maxProb2 += jet2TauFakerate[i];
		
		//find probability of >1 taus
		double temp = jetTauFakerate[i];
		for(unsigned int j=0; j<jetTauFakerate.size(); j++){
		  if(i==j) continue;
		  temp *= (1 - jet2TauFakerate[j]);
		}
		probabilityOne += temp;	
	    }*/
	   //exactly 2 tau version
	   for(unsigned int i=0; i<jetTauFakerate.size(); i++){
	      if(jetTauFakerate[i]==0) wrongs.push_back(i);
	      maxProb1 += jetTauFakerate[i];
	      maxProb2 += jet2TauFakerate[i];
	      for(unsigned int j=i+1; j<jetTauFakerate.size(); j++){
	        if(i==j) continue;
	        double temp=jetTauFakerate[i]*jetTauFakerate[j];
	        for(unsigned int k=0; k<jetTauFakerate.size(); k++){
		  if(i==k || j==k) continue;
		  //find probability of exactly 2 taus
		  temp *= (1-jetTauFakerate[k]);
		}
		probabilityTwo += temp;
	      }
	    } 
	  }
	  else{
	    for(unsigned int i=0; i<jetTauFakerate.size(); i++){
	      if(jetTauFakerate[i]==0 && jet2TauFakerate[i]==0) wrongs.push_back(i);
	      maxProb1 += jetTauFakerate[i];
	      maxProb2 += jet2TauFakerate[i];
	      for(unsigned int j=0; j<jetTauFakerate.size(); j++){
	        if(i==j) continue;
	        double temp=0;
		if(jetTauFakerate[i]<=1){
		  if(jetTauFakerate[j]<=1) temp=jetTauFakerate[i]*jet2TauFakerate[j];
		  else temp=jetTauFakerate[i];
		}
		else if(jetTauFakerate[j]<=1) temp=jet2TauFakerate[j];
		else temp=1;
	        for(unsigned int k=0; k<jetTauFakerate.size(); k++){
		  if(i==k || j==k) continue;
		  //find probability of exactly 2 taus
		  if(jetTauFakerate[k]+jet2TauFakerate[k]<=1) temp *= (1-jetTauFakerate[k]-jet2TauFakerate[k]);
		  else temp=0;
		}
		probabilityTwo += temp;
	      }
	    }
	  }
	  //set eventweight to == 2 tau
	  weight=probabilityTwo;
	  if(weight>1)std::cout<<"!!!Nonsense warning!!!"<<std::endl;
	  if(verbose)std::cout<<"EventWeight="<<weight<<", p0="<<probabilityZero<<", p1="<<probabilityOne<<std::endl;
	  if(wrongs.size()>jetTauFakerate.size()-2) {weight = 0; if(verbose)std::cout<<"!!!Not enough Jets!!! weight=0"<<std::endl; return;}//catch rounding errors
	  //randomize tau indizes
	  if(weight>=1) return; //sanity check
	  std::uniform_real_distribution<double> distributionOne(0.0, maxProb1);
	  std::random_device rd;
	  std::mt19937 engine(rd()); // Mersenne twister MT19937
	  
	  double TossOne=distributionOne(engine);
	  double temp=0.;
	  for(unsigned int i=0; i<jetTauFakerate.size(); i++){ //choose first tau
	  	temp+=jetTauFakerate[i];
		if(jetTauFakerate[i]==0) continue;
		if(temp>=TossOne){
		  index.first=i;
		  maxProb2 -= jet2TauFakerate[i];
		  break;
		}
	  }
	  
	  std::uniform_real_distribution<double> distributionTwo(0.0, maxProb2);
	  double TossTwo=distributionTwo(engine);
	  temp = 0.;
	  for(unsigned int i=0; i<jet2TauFakerate.size(); i++){ //choose second tau
	  	if(i==abs(index.first)) continue;
		if(jet2TauFakerate[i]==0) continue;
	  	temp+=jet2TauFakerate[i];
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
