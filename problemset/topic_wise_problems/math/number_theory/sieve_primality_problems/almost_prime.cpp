// Problem link : https://codeforces.com/problemset/problem/26/A
// Solution : below code

vector<int> myPref(3010,0);
vector<int> simpleV(3010,0);
vector<int> numberOfPrimeFactors(N+1,0);
void mySeive(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num*2;j<=N;j+=num){
				nonPrimeSet[j]=1;
				numberOfPrimeFactors[j]+=1;
			}
			numberOfPrimeFactors[num]+=1;
		}
		
	}
	for(int i=0;i<3010;i++){
		if(numberOfPrimeFactors[i]==2)simpleV[i]=1;
	}
	for(int i=1;i<3010;i++){
		myPref[i]=myPref[i-1]+simpleV[i];
	}

}
void init(){
	mySeive();
}
bool isTakeTestCaseAsInput=false;
void solve(){
	int n;
	cin>>n;
	cout<<myPref[n]<<endl;
}
