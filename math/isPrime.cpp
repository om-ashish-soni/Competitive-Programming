// sieve of erathosthens for prime
const int N=1e6;
bitset <N> nonPrimeSet;
// isPrime
bool isPrimeBig(int n){
	if(n==1) return false;
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				return false;
				n/=p;
			}else p++;
		}else{
			return true;
			break;
		}
	}
	return false;
}
// TIME COMPLEXITY : NLOGN
void seive(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num+num;j<=N;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	
}
bool isPrime(int n){
	if(n>1e6) return isPrimeBig(n);
	return 0==nonPrimeSet[n];
}
