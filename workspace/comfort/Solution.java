// Solution.java

import java.util.*;
import java.io.*;
import java.util.AbstractMap.SimpleEntry;
import java.math.*;
import java.util.stream.Collectors;

public class Solution {
    // some state attributes
    static boolean isTakeTestCase=true;

    // some static variables for precomputation
    

    // actual solve method containing logic
    private void solve(Printer out,int testcase) throws Exception{
        int n=scanner.nextInt();
        int[] arr=scanner.nextIntArray(n);
        Map<Integer,Integer> mp=new HashMap<>();
        long ctr=0L;
        for(int i=n-1;i>=0;i--){
            long total=n-i;
            int num=arr[i];
            if(mp.containsKey(num)){
                mp.put(num,mp.get(num)+1);
            }else{
                mp.put(num,1);
            }
            long addon=total-mp.get(num);
            ctr+=addon;
        }
        out.println(ctr);


    }   

    // imported extra custom  modules
    static class Sieve {
        List<Integer> primes;
        List<Integer> lp;
        int n = 100001;

        Sieve() {
            init();
        }

        Sieve(int n) {
            this.n = n;
            init();
        }

        void init() {
            boolean[] isprm = new boolean[n];
            primes = new ArrayList<Integer>();
            lp = new ArrayList<Integer>();

            for (int i = 0; i < n; i++) {
                isprm[i] = true;
                lp.add(-1);
            }

            isprm[0] = isprm[1] = false;

            for (int i = 2; i < n; i++) {
                if (!isprm[i])
                    continue;

                lp.set(i, i);
                primes.add(i);

                for (int j = i + i; j < n; j += i) {
                    isprm[j] = false;
                    if (lp.get(j) == -1) {
                        lp.set(j, i);
                    }
                }
            }
        }

        List<Integer> get() {
            return primes;
        }
        boolean isPrime(int num){
            return num==getLP(num);
        }
        int getLP(int num) {
            return lp.get(num);
        }

        List<Integer> getPrimeFactors(int num) {
            List<Integer> factors = new ArrayList<Integer>();

            while (num > 1) {
                factors.add(lp.get(num));
                num /= lp.get(num);
            }

            return factors;
        }

        void print() {
            for (int prm : primes) {
                System.out.print(prm + " ");
            }
            System.out.println();
        }
    }

    
    // here is helper solve method
    public void solve() throws Exception {
        out=new Printer();
        int t=1;
        if(isTakeTestCase) t=scanner.nextInt();
        for(int i=0;i<t;i++){
            solve(out,i);    
        }
        // out.printTime();
        out.out.close();
    }

    // here is main method
    public static void main(String[] args) throws Exception{
        Solution solution=new Solution();
        solution.solve();
    }

    // constructor
    Solution(){
        scanner=new FastScanner();
    }

    // other supporting classes
    static class CommonUtil{
        public static int log2(long n){
            int l2=0;
            while(n>1){
                l2++;
                n>>=1;
            }
            return l2;
        }
        public static long gcd(long a,long b){
            while(b != 0){
                long temp=b;
                b=a%b;
                a=temp;
            }
            return a;
        }    
    };

    // io modules
    FastScanner scanner;
    Printer out;
    static class FastScanner {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st=new StringTokenizer("");
        public String next() {
            while (!st.hasMoreTokens())
                try {
                    st=new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            return st.nextToken();
        }
        public int nextInt() {
            return Integer.parseInt(next());
        }
        public long nextLong() {
            return Long.parseLong(next());
        }
        public String nextLine() throws IOException { return br.readLine();}
        public int [] nextIntArray(int n){
            int [] arr=new int[n];
            readIntArray(arr);
            return arr;
        }
        public long [] nextLongArray(int n){
            long [] arr=new long[n];
            readLongArray(arr);
            return arr;
        }
        public String [] nextStringArray(int n){
            String [] arr=new String[n];
            readStringArray(arr);
            return arr;
        }
        public void readIntArray(int arr[]) {
            for (int i=0; i<arr.length; i++) arr[i]=nextInt();
        }
        public void readLongArray(long arr[]) {
            for (int i=0; i<arr.length; i++) arr[i]=nextLong();
        }
        public void readStringArray(String arr[]) {
            for (int i=0; i<arr.length; i++) arr[i]=next();
        }

    }
    static class Printer{
        public PrintWriter out;
        public Printer(){
            this.out=new PrintWriter(System.out);
        }
        public void print(Object o1){
            out.print(o1+" ");
        }
        public void print(Object o1,Object o2){
            out.print(o1+" "+o2+" ");
        }
        public void print(Object o1,Object o2,Object o3){
            out.print(o1+" "+o2+" "+o3+" ");
        }
        public void print(Object o1,Object o2,Object o3,Object o4){
            out.print(o1+" "+o2+" "+o3+" "+o4+" ");
        }
        public void printList(List<?> lst){
            lst.forEach((elem)->print(elem));
        }
        public <T> void printArray(T []arr){
            for(int i=0;i<arr.length;i++) print(arr[i]);
        }
        public void printArray(long []arr){
            for(int i=0;i<arr.length;i++) print(arr[i]);
        }
        public void printArray(int []arr){
            for(int i=0;i<arr.length;i++) print(arr[i]);
        }

        public void printReject(){
            print(-1);
        }
        public void printYESNO(boolean b){
            if(b) print("YES");
            else print("NO");
        }
        public void printYesNo(boolean b){
            if(b) print("Yes");
            else print("No");
        }
        public void printyesno(boolean b){
            if(b) print("yes");
            else print("no");
        }
        public void println(){
            out.println();
        }
        public void println(Object o1){
            out.println(o1);
        }
        public void println(Object o1,Object o2){
            out.println(o1+" "+o2);
        }
        public void println(Object o1,Object o2,Object o3){
            out.println(o1+" "+o2+" "+o3);
        }
        public void println(Object o1,Object o2,Object o3,Object o4){
            out.println(o1+" "+o2+" "+o3+" "+o4);
        }
        public void printlnList(List<?> lst){
            printList(lst);
            println();
        }
        public <T> void printlnArray(T []arr){
            printArray(arr);
            println();
        }
        public void printlnArray(int []arr){
            printArray(arr);
            println();
        }
        public void printlnArray(long []arr){
            printArray(arr);
            println();
        }
        public void printlnYESNO(boolean b){
            printYESNO(b);
            println();
        }
        public void printlnYesNo(boolean b){
            printYesNo(b);
            println();
        }
        public void printlnyesno(boolean b){
            printyesno(b);
            println();
        }
        public void printlnReject(){
            printReject();
            println();
        }
        public void printKickStartCase(int t){
            print("Case #"+(t+1)+":");
        }
        public void printTime() {
            double tm = (double) System.currentTimeMillis() / 1000.0;
            System.err.println("time taken : " + tm);
        }

    }


}
    