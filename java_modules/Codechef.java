
import java.util.*;
import java.lang.*;
import java.io.*;

class Codechef
{

    Boolean isTakeTestCase=true;
    FastScanner scanner;
    Printer out;
    Codechef(){
        scanner=new FastScanner();
    }
    public static void main(String[] args) throws Exception {
        Codechef solution=new Codechef();
        solution.solve();
    }
    void solve() throws Exception {
        out=new Printer();
        int t=1;
        if(isTakeTestCase) t=scanner.nextInt();
        for(int i=0;i<t;i++){
            solve(out,i);
        }
    }

    void solve(Printer out,int t) throws Exception {
        int n=scanner.nextInt();
        int [] arr=scanner.nextIntArray(n);
        int ctr=Integer.MAX_VALUE;
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=arr[i];
        }
        if(sum%2==0){
            ctr=0;
        }
        for(int i=0;i<n;i++){
            int num=arr[i];
            List<Integer> lst=new ArrayList<>();
            while(num>0){
                int bit=(num&1);
                lst.add(bit);
                num>>=1;
            }
            lst.add(0);
            for(int k=1;k<lst.size();k++){
                if(lst.get(k) != lst.get(k-1)){
                    ctr=Math.min(ctr,k);
                    break;
                }
            }
        }
        out.println(ctr);
    }
    static class FastScanner {
        Scanner sc=new Scanner(System.in);
        public String next() {
            return sc.next();
        }
        public int nextInt() {
            return sc.nextInt();
        }
        public long nextLong() {
            return sc.nextLong();
        }
        public String nextLine() throws IOException { return sc.nextLine();}
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
        public static PrintStream out;
        public Printer(){
            this.out=System.out;
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
        public void printList(ArrayList<?> lst){
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
        public void printlnList(ArrayList<?> lst){
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
    }
}
