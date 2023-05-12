//factors 
void findAllFactors(int n,std::vector<int>& factors){
	double sqroot=sqrt(n);
	factors.push_back(1);
	for(int i=2;i<=sqroot;i++){
		if(n%i == 0){
			factors.push_back(i);
			if(n/i != i){
				factors.push_back(n/i);
			}
		}
	}
	factors.push_back(n);
	sort(factors.begin(),factors.end());
}
