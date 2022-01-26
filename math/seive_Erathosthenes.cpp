const int N=1e7;
bitset <N> nonPrimeSet;
// TIME COMPLEXITY : N*LOG(N)
void seive(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num+num;j<=N;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	
}
