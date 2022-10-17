// problem link : https://codeforces.com/contest/1736/problem/C1
// solution : below code

class Solution{
	static FastScanner s;	
	Solution(FastScanner s){
		this.s=s;
	}
    public static void solve(){
		int n=s.nextInt();
		long arr[]=new long[(int)n];
		long dp[]=new long[(int)n];
		for(int i=0;i<n;i++){
			arr[i]=s.nextLong();
		}
		for(int i=0;i<n;i++){
			dp[i]=0;
		}
		if(arr[0]>0) dp[0]=1;
		long sm=dp[0];
		for(int i=1;i<n;i++){
			dp[i]=Math.min(arr[i],dp[i-1]+1);
			sm+=dp[i];
		}
		Printer.println(sm);
		
    }
}
