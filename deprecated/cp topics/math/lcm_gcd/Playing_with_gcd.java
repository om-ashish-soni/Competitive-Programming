// problem link : https://codeforces.com/contest/1736/problem/B
// solution : below code


class Solution{
	static FastScanner s;	
	Solution(FastScanner s){
		this.s=s;
	}
    public static void solve(){
		int n=s.nextInt();
		long arr[]=new long[(int)n];
		for(int i=0;i<n;i++){
			arr[i]=s.nextLong();
		}
		boolean flag=true;
		for(int i=1;i<n-1;i++){
			long gcd=LcmGcd.gcd(arr[i-1],arr[i+1]);
			if(arr[i]%gcd > 0){
				flag=false;
				break;
			}
		}
		
		
		Printer.printlnYESNO(flag);
		return;
    }
}

class LcmGcd{
	public static Pair<Long,Long> extendedGcd(long a,long b){
		if(b==0) return new Pair<Long,Long>(1L,1L);
		Pair<Long,Long> pr=extendedGcd(b,a%b);
		return new Pair<Long,Long>(pr.second,pr.first - (a/b)*pr.second);
	}
	public static long gcd(long a,long b){
		while(b != 0){
			long middle=b;
			b=a%b;
			a=middle;
		}
		return a;
	}
	public static long lcm(long a,long b){
		return a*b/(gcd(a,b));
	}
}
