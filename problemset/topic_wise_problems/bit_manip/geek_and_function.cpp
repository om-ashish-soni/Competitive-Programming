// Problem link : https://practice.geeksforgeeks.org/problems/geek-and-function-v/0/
// solution : below code
void solve(){
	int n,k;
	cin>>n>>k;
	
    int num=n;
    for(int i=1;;i++){
        num=(num xor (num%10));
        if(i==k){
            cout<<num<<endl;
            break;
        }
        if(num==0){
            cout<<0<<endl;
            break;
        }
        if(num%10 == 0){
            cout<<num<<endl;
            break;
        }
    }

	
}
