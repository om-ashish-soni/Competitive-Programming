// Problem link  : https://practice.geeksforgeeks.org/problems/geek-and-subset-sum/0/
// Solution : below code
void solve(){
	int n,k;
	cin>>n>>k;
	int arr[n];
	scan(arr,n);
	string s;
	for(int i=0;i<n;i++) s+='0';
	for(int i=0;i<k;i++) s[i]='1';
	reverse(s.begin(),s.end());
	int sum=0;
	do{
	    for(int i=0;i<n;i++){
	        if(s[i]=='1') sum+=arr[i];
	    }
	}while(next_permutation(s.begin(),s.end()));
	cout<<sum<<endl;
	
	
}
