// Problem link : https://practice.geeksforgeeks.org/problems/euler-totient2036/1
// Solution : below code

// { Driver Code Starts

#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends

bool flag=false;
const int NUM=1e5;
vector<int> primes;
bitset <NUM> nonPrimeSet;
void seiveWithAllPrimes(){
    
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num*num<=NUM;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num*num;j<=NUM;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	for(int num=2;num<=NUM;num++){
		if(0==nonPrimeSet[num]) primes.push_back(num);
	}
}
class Solution {
  public:
    long long maximizeEulerRatio(long long N) {
        if(!flag) {
            seiveWithAllPrimes();
            flag=true;
        }
        long long int res=1;
        for(auto num:primes)
        {
            if(res*num <= N) res*=num;
            else break;
        }
        return res;
    }
};

// { Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        long long N;
        
        cin>>N;

        Solution ob;
        cout << ob.maximizeEulerRatio(N) << endl;
    }
    return 0;
}  // } Driver Code Ends
