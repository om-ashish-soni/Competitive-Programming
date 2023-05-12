import java.util.*;
import java.io.*;
import java.util.AbstractMap.SimpleEntry;

public class Main {
    static boolean isTakeTestCase=false;
    FastScanner scanner;
    Printer out;

    Main(){
        scanner=new FastScanner();
    }
    public static void main(String[] args) throws Exception{
        Main solution=new Main();
        solution.solve();
    }
    public static int log2(long n){
        int l2=0;
        while(n>1){
            l2++;
            n>>=1;
        }
        return l2;
    }
    private void solve(Printer out,int testcase) throws Exception{
    
        int n=scanner.nextInt();
        String s=scanner.next();
        for(int i=1;i<n;i++){
            if(s.charAt(i) == s.charAt(i-1)){
                out.printlnYesNo(false);
                return;
            }
        }
        out.printlnYesNo(true);
    }
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
        public void readIntArray(int arr[]) {
            for (int i=0; i<arr.length; i++) arr[i]=nextInt();
        }
        public void readLongArray(long arr[]) {
            for (int i=0; i<arr.length; i++) arr[i]=nextLong();
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
            print("Case #",t,": ");
        }
        public void printTime() {
            double tm = (double) System.currentTimeMillis() / 1000.0;
            System.err.println("time taken : " + tm);
        }

    }
    static class ModuloArithmetic {
        public static Map.Entry<Long, Long> extendedGcd(long a, long b) {
            if (b == 0) {
                return Map.entry(1L, 0L);
            } else {
                Map.Entry<Long, Long> prev = extendedGcd(b, a % b);
                long x = prev.getValue();
                long y = prev.getKey() - (a / b) * prev.getValue();
                return Map.entry(x, y);
            }
        }

        public static long hcf(long a, long b) {
            if (a == 0 || b == 0) {
                return Math.max(a, b);
            } else {
                Map.Entry<Long, Long> prev = extendedGcd(a, b);
                return a * prev.getKey() + b * prev.getValue();
            }
        }

        public static long lcm(long a, long b) {
            return a * (b / hcf(a, b));
        }

        public static long gcd(long a, long b) {
            return hcf(a, b);
        }

        public static long modSub(long a, long b, long mod) {
            return ((a % mod - b % mod + mod) % mod);
        }

        public static long modMul(long a, long b, long mod) {
            return ((a % mod) * (b % mod)) % mod;
        }

        public static long modAdd(long a, long b, long mod) {
            return ((a % mod) + (b % mod)) % mod;
        }

        public static long modInv(long a, long mod) {
            Map.Entry<Long, Long> prev = extendedGcd(a, mod);
            long x = prev.getKey();
            long y = prev.getValue();
            long g = a * x + mod * y;
            if (g != 1) {
                System.err.println("modular inverse does not exist , gcd != 1");
                // System.exit(0);
            }
            // adding mod to avoid negative value of x
            long res = (x % mod + mod) % mod;
            return res;
        }

        public static long modDiv(long a, long b, long mod) {
            a = a % mod;
            long inv = modInv(b, mod);
            long res = (inv * a) % mod;
            return res;
        }

        public static long power(long x, long y, long p) {
            long res = 1;
            x = x % p; // Update x if it is more than or equal to p
            if (x == 0) {
                return 0; // In case x is divisible by p
            }
            while (y > 0) {
                if ((y & 1) == 1) {
                    res = (res * x) % p;
                }
                y = y >> 1; // y = y/2
                x = (x * x) % p;
            }
            return res;
        }
    }
    static class DisjointSet {
        private List<Integer> ump;
        
        public DisjointSet(int n) {
            ump = new ArrayList<>(n + 1);
            for (int i = 0; i <= n; i++) {
                ump.add(-1);
            }
        }
        
        public List<Integer> getUmp() {
            return ump;
        }
        
        public int findSet(int u) {
            int r = u;
            while (ump.get(r) >= 0) {
                r = ump.get(r);
            }
            while (u != r) {
                int par = ump.get(u);
                ump.set(u, r);
                u = par;
            }
            return r;
        }
        
        public boolean setUnion(int u, int v) {
            int uroot = findSet(u);
            int vroot = findSet(v);
            if (uroot == vroot) {
                return false;
            }
            int uchild = ump.get(uroot);
            int vchild = ump.get(vroot);
            int totalChild = uchild + vchild;
            if (uchild > vchild) {
                ump.set(uroot, vroot);
                ump.set(vroot, totalChild);
            } else {
                ump.set(vroot, uroot);
                ump.set(uroot, totalChild);
            }
            return true;
        }
        
        public boolean preferredUnion(int u, int v) {
            int uroot = findSet(u);
            int vroot = findSet(v);
            if (uroot == vroot) {
                return false;
            }
            int uchild = ump.get(uroot);
            int vchild = ump.get(vroot);
            int totalChild = uchild + vchild;
            ump.set(uroot, vroot);
            ump.set(vroot, totalChild);
            return true;
        }
        
        public boolean checkOdd(int l, int r) {
            for (int i = l; i <= r; i++) {
                if (ump.get(i) < 0) {
                    if (Math.abs(ump.get(i)) % 2 == 1) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        public int getChilds(int u) {
            int root = findSet(u);
            return Math.abs(ump.get(root));
        }
    }
}
    