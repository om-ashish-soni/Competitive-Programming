import java.util.*;
import java.io.*;

public class Main {

	static Boolean isTakeTestCase=true;
	Main(){
	}
	
    public static void main(String[] args) {
		//Scanner s=new Scanner(System.in);
		FastScanner s=new FastScanner();
		Solution solution=new Solution(s);
        long t=1;
        if(isTakeTestCase){
        	t=s.nextLong();
        }
        while(t>0){
        	t--;
        	solution.solve();
        }

    }
}

class Solution{
	static FastScanner s;	
	Solution(FastScanner s){
		this.s=s;
	}
    public static void solve(){

    	/*
    	
    	+++++++++++++++++++++++++++++++++++++++++++++++++
    					start your code here    	
    	+++++++++++++++++++++++++++++++++++++++++++++++++
    	
    	*/
    	
		Printer.println("Shree Ganeshay Namah");

    	/*
    	
    	+++++++++++++++++++++++++++++++++++++++++++++++++
    					end your code here    	
    	+++++++++++++++++++++++++++++++++++++++++++++++++
    	
    	*/
    }
}
// fast scanner
class FastScanner {
	BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st=new StringTokenizer("");
	String next() {
		while (!st.hasMoreTokens())
			try {
				st=new StringTokenizer(br.readLine());
			} catch (IOException e) {
				e.printStackTrace();
			}
		return st.nextToken();
	}
	
	int nextInt() {
		return Integer.parseInt(next());
	}
	int[] readArray(int n) {
		int[] a=new int[n];
		for (int i=0; i<n; i++) a[i]=nextInt();
		return a;
	}
	long nextLong() {
		return Long.parseLong(next());
	}
}
// heavy ds
class FenwickTree{
	long n;
	ArrayList<Long> BIT;
	public FenwickTree(long n){
		this.n=n;
		BIT=Creator.createList(n,0L);
	}
	public FenwickTree(ArrayList<Long> lst){
		this.n=(long)lst.size();
		BIT=Creator.createList(n,0L);
		Setter.set(BIT,0L,Getter.get(lst,0L));
		for(long index=1;index<n;index++){
			this.update(index,Getter.get(lst,index));
		}
	}
	public void update(long index,long delta){
		if(index==0) {
			Setter.set(BIT,index,Getter.get(BIT,index)+delta);
			return;
		}
		for(;index<n;index+=(index & -index)){
			Setter.set(BIT,index,Getter.get(BIT,index)+delta);
		}
	}
	public long get(long index){
		long sum=Getter.get(BIT,0);
		for(;index>0;index-=(index & -index)){
			sum+=Getter.get(BIT,index);
		}
		return sum;
	}
	public void print(){
		Printer.printlnList(BIT);
	}
}
// custom classes
class BitSet{
	public Long size=65L;
	public Long n;
	ArrayList<Long> bits;
	long setBitsCount=0;
	BitSet(long n){
		this.n=n;
		this.bits=Creator.createList(size,0L);
		long index=0;
		for(;index<size;index++){
			if((n & 1L) == 1L)this.set(index);
			n>>=1;
		}
	}
	public void set(){
		Setter.setAll(bits,1L);
		this.setBitsCount=n;
	}
	public void reset(){
		Setter.setAll(bits,0L);
		this.setBitsCount=0;
	}
	public void clear(){
		this.reset();
	}
	public long get(long index){
		return Getter.get(bits,index);
	}
	public void set(long index){
		long oldValue=this.get(index);
		if(oldValue != 1L){
			this.flip(index);
		}
	}
	public void reset(long index){
		long oldValue=this.get(index);
		if(oldValue != 0){
			this.flip(index);
		}
	}
	public void flip(long index){
		long oldValue=this.get(index);
		if(oldValue == 0) this.setBitsCount+=1;
		else this.setBitsCount-=1;
		Setter.set(bits,index,1L ^ oldValue);
	}
	public void flip(){
		for(long index=0;index<size;index++){
			this.flip(index);
		}
	}
	public long count(){
		return this.setBitsCount;
	}
	public void print(){
		Printer.printList(bits);
	}
	public void println(){
		Printer.printlnList(bits);
	}
	public long toLong(){
		long number=0L;
		long weight=1L;
		for(long index=0L;index<this.size;index++){
			if(this.get(index)==1L) number+=weight;
			weight<<=1L;
		}
		return number;
	}
	@Override
	public String toString(){
		String s="";
		for(long index=0L;index<this.size;index++){
			if(this.get(index)==0) s+="0";
			else s+="1";
		}
		return s;
	}
}
class Pair<T extends Comparable<T>,V extends Comparable<V>> implements Comparable<Pair<T,V>>
{
    // Return a map entry (key-value pair) from the specified values
    public T first;
    public V second;
	public Pair(T first,V second){
		this.first=first;
		this.second=second;
	}
	@Override
	public String toString(){
		return "{ "+this.first+" , "+this.second+" }";
	}
	
	@Override 
	public int compareTo(Pair<T,V> pr){
		int firstComparision=this.first.compareTo(pr.first);
		if(firstComparision==0){
			return this.second.compareTo(pr.second);
		}
		return firstComparision;
	}
}

// utitlity classes
class Printer{
	
	public static void print(Object o1){
		System.out.print(o1+" ");	
	}
	public static void print(Object o1,Object o2){
		System.out.print(o1+" "+o2+" ");	
	}
	public static void print(Object o1,Object o2,Object o3){
		System.out.print(o1+" "+o2+" "+o3+" ");	
	}
	public static void print(Object o1,Object o2,Object o3,Object o4){
		System.out.print(o1+" "+o2+" "+o3+" "+o4+" ");	
	}
	public static void printList(ArrayList<?> lst){
		lst.forEach((elem)->print(elem));
	}
	public static void printReject(){
		print(-1);
	}
	public static void printYESNO(boolean b){
		if(b) print("YES");
		else print("NO");
	}
	public static void printYesNo(boolean b){
		if(b) print("Yes");
		else print("No");
	}
	public static void printyesno(boolean b){
		if(b) print("yes");
		else print("no");
	}
	
	public static void println(){
		System.out.println();
	}
	public static void println(Object o1){
		System.out.println(o1);	
	}
	public static void println(Object o1,Object o2){
		System.out.println(o1+" "+o2);	
	}
	public static void println(Object o1,Object o2,Object o3){
		System.out.println(o1+" "+o2+" "+o3);	
	}
	public static void println(Object o1,Object o2,Object o3,Object o4){
		System.out.println(o1+" "+o2+" "+o3+" "+o4);	
	}
	public static void printlnList(ArrayList<?> lst){
		printList(lst);
		println();
	}
	public static void printlnYESNO(boolean b){
		printYESNO(b);
		println();
	}
	public static void printlnYesNo(boolean b){
		printYesNo(b);
		println();
	}
	public static void printlnyesno(boolean b){
		printyesno(b);
		println();
	}
	public static void printlnReject(){
		printReject();
		println();
	}
}
class Convertor{
	public static Long stringToInt(String s){
		return Long.parseLong(s);
	}
	public static String intToString(Long num){
		return num.toString();
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
class Creator{
	public static <T> ArrayList<T> createList(long n,T value){
		ArrayList<T> lst=new ArrayList<T>((int)n);
		for(long i=0;i<n;i++){
			lst.add(value);
		}
		return lst;
	}
	public static ArrayList<Long> createPermutation(long n){
		ArrayList<Long> perm=new ArrayList<Long>((int)n);
		for(long i=0;i<n;i++){
			perm.add(i+1);
		}
		return perm;
	}
}

class Getter{
	public static <T> T get(ArrayList<T> lst,long index){
		return lst.get((int)index);
	}
}
class Setter{
	public static <T> void set(ArrayList<T> lst,long index,T value){
		lst.set((int)index,value);
	}
	public static <T> void setAll(ArrayList<T> lst,T value){
		for(int i=0;i<lst.size();i++){
			lst.set(i,value);		
		}
	
	}
	// public static <T extends Number> void add(ArrayList<T> lst,long index,T value){
		// lst.set((int)index,lst.get((int)index)+value);
	// }
}
// normal classes

class Factorization{
	Long n;
	Long limit;
	ArrayList<Long> factors;
	Factorization(Long n){
		this.n=n;
		this.factors=new ArrayList<Long>();
		this.limit=Math.round(Math.sqrt(n));
		this.process();
	}
	private void process(){
		for(long i=2;i<=limit;i++){
			if(n%i == 0){
				factors.add(i);
				Long div=n/i;
				if(div != i){
					factors.add(div);
				}
			}
		}
		Collections.sort(factors);
	}
	public ArrayList<Long> getFactors(){
		return factors;
	}
	public long getNumberOfFactors(){
		return factors.size();
	}
	public void printFactors(){
		Printer.printlnList(factors);
	}
}
class Modulo{
	long mod=(long)(1e9+7);
	public Modulo(){
	}
	public Modulo(long mod){
		this.mod=mod;
	}
	public long power(long a,long b){
		long res=1;
		a=a%mod;
		if(a==0) return 0;
		while(b>0){
			if( (b&1) == 1 ){
				res=(res*a)%mod;
			}
			a=(a*a)%mod;
			b>>=1;
		}
		return res;
	}
	public long add(long a,long b){
		return (a%mod + b%mod)%mod;
	}
	public long sub(long a,long b){
		return (a%mod - b%mod + mod)%mod;
	}
	public long mul(long a,long b){
		return ((a%mod)*(b%mod))%mod;
	}
	public long inverse(long a){
		Pair<Long,Long> pr=LcmGcd.extendedGcd(a,mod);	
		long gcd=a*pr.first + mod*pr.second;
		if(gcd != 1) return -1;
		return (pr.first%mod + mod)%mod;
	}
	public long div(long a,long b){
		a=a%mod;
		long inv=inverse(b);
		return mul(a,inv);
	}
	public void printModulo(){
		Printer.println("Modulo : ",mod);
	}
}
class DisjointSet{
    int [] arr;
    int n;
    public DisjointSet(int n){
        this.n=n;
        arr=new int[n];
        for(int i=0;i<n;i++) arr[i]=-1;
    }
    public int findSet(int u){
        int r=u;
        while(arr[r] >= 0){
            r=arr[r];
        }
        while(u != r){
            int next=arr[u];
            arr[u]=r;
            u=next;
        }
        return r;
    }
    public boolean setUnion(int u,int v){
        int uroot=this.findSet(u);
        int vroot=this.findSet(v);
        if(uroot==vroot) return false;
        int totalChilds=arr[uroot]+arr[vroot];
        if(arr[uroot]<arr[vroot]){
            arr[vroot]=uroot;
            arr[uroot]=totalChilds;
        }else{
            arr[uroot]=vroot;
            arr[vroot]=totalChilds;
        }
        return true;
    }
}

