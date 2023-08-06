import java.util.*;
import java.io.*;
import java.util.stream.Collectors;
public class ShreepadAllInOne {
    public static void main(String[] args) throws Exception {
        Solution solution = new Solution();
        solution.solve();
    }
}

class Solution {
    static boolean isTakeTestCase = false;
    FastScanner scanner;
    Printer out;
    Solution() {
        scanner = new FastScanner();
    }
    public void solve() throws Exception {
        out = new Printer();
        int t = 1;
        if (isTakeTestCase) t = scanner.nextInt();
        for (int i = 0; i < t; i++) {
            solve(out, i);
        }
        out.out.close();
    }

    void solve(Printer out, int testcase) throws Exception {
        out.println("hello world");
    }
    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        public String next() {
            while (!st.hasMoreTokens())
                try {
                    st = new StringTokenizer(br.readLine());
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
        public int [] nextIntArray(int n) {
            int [] arr = new int[n];
            readIntArray(arr);
            return arr;
        }
        public long [] nextLongArray(int n) {
            long [] arr = new long[n];
            readLongArray(arr);
            return arr;
        }
        public void readIntArray(int arr[]) {
            for (int i = 0; i < arr.length; i++) arr[i] = nextInt();
        }
        public void readLongArray(long arr[]) {
            for (int i = 0; i < arr.length; i++) arr[i] = nextLong();
        }

    }
    static class Printer {
        public PrintWriter out;
        public Printer() {
            this.out = new PrintWriter(System.out);
        }
        public void print(Object o1) {
            out.print(o1 + " ");
        }
        public void print(Object o1, Object o2) {
            out.print(o1 + " " + o2 + " ");
        }
        public void print(Object o1, Object o2, Object o3) {
            out.print(o1 + " " + o2 + " " + o3 + " ");
        }
        public void print(Object o1, Object o2, Object o3, Object o4) {
            out.print(o1 + " " + o2 + " " + o3 + " " + o4 + " ");
        }
        public void printList(List<?> lst) {
            lst.forEach((elem)->print(elem));
        }
        public <T> void printArray(T []arr) {
            for (int i = 0; i < arr.length; i++) print(arr[i]);
        }
        public void printArray(long []arr) {
            for (int i = 0; i < arr.length; i++) print(arr[i]);
        }
        public void printArray(int []arr) {
            for (int i = 0; i < arr.length; i++) print(arr[i]);
        }

        public void printReject() {
            print(-1);
        }
        public void printYESNO(boolean b) {
            if (b) print("YES");
            else print("NO");
        }
        public void printYesNo(boolean b) {
            if (b) print("Yes");
            else print("No");
        }
        public void printyesno(boolean b) {
            if (b) print("yes");
            else print("no");
        }
        public void println() {
            out.println();
        }
        public void println(Object o1) {
            out.println(o1);
        }
        public void println(Object o1, Object o2) {
            out.println(o1 + " " + o2);
        }
        public void println(Object o1, Object o2, Object o3) {
            out.println(o1 + " " + o2 + " " + o3);
        }
        public void println(Object o1, Object o2, Object o3, Object o4) {
            out.println(o1 + " " + o2 + " " + o3 + " " + o4);
        }
        public void printlnList(List<?> lst) {
            printList(lst);
            println();
        }
        public <T> void printlnArray(T []arr) {
            printArray(arr);
            println();
        }
        public void printlnArray(int []arr) {
            printArray(arr);
            println();
        }
        public void printlnArray(long []arr) {
            printArray(arr);
            println();
        }
        public void printlnYESNO(boolean b) {
            printYESNO(b);
            println();
        }
        public void printlnYesNo(boolean b) {
            printYesNo(b);
            println();
        }
        public void printlnyesno(boolean b) {
            printyesno(b);
            println();
        }
        public void printlnReject() {
            printReject();
            println();
        }
        public void printKickStartCase(int t) {
            print("Case #", t, ": ");
        }
        public void printTime() {
            double tm = (double) System.currentTimeMillis() / 1000.0;
            System.err.println("time taken : " + tm);
        }

    }
}
class CordinateCompressor<T extends Number & Comparable<T>> {
    Map<T, Integer> cord;
    List<T> reverseCord;
    T[] arr;
    int n;

    public CordinateCompressor(T[] arr) {
        this.arr = arr;
        this.n = this.arr.length;
        this.reverseCord = new ArrayList<>(Collections.nCopies(n + 10, null));
        this.cord = new HashMap<>();
        startCompressor();
    }

    public CordinateCompressor(List<T> list) {
        this.arr = (T[]) list.toArray();
        this.n = this.arr.length;
        this.reverseCord = new ArrayList<>(Collections.nCopies(n + 10, null));
        this.cord = new HashMap<>();
        startCompressor();
    }

    void startCompressor() {
        Arrays.sort(arr);
        int key = 1;
        for (T val : arr) {
            if (!cord.containsKey(val)) {
                cord.put(val, key);
                reverseCord.set(key, val);
                key++;
            }
        }
    }

    public int compress(T num) {
        if (!cord.containsKey(num)) {
            return -1;
        }
        return cord.get(num);
    }

    public T decompress(int num) {
        return reverseCord.get(num);
    }

    public static void howToUse() {
        Integer[] arr = {100, 10, 52, 83, 10};
        List<Integer> list = Arrays.asList(100, 10, 52, 83, 10);
        int len = arr.length;
        CordinateCompressor<Integer> cc1 = new CordinateCompressor<>(arr);
        CordinateCompressor<Integer> cc2 = new CordinateCompressor<>(list);
        Integer[] compressed = new Integer[len];
        Integer[] decompressed = new Integer[len];
        for (int i = 0; i < len; i++) {
            compressed[i] = cc1.compress(arr[i]);
            decompressed[i] = cc1.decompress(compressed[i]);
            System.out.printf("element : %d : %d , %d%n", arr[i], compressed[i], decompressed[i]);
        }
        for (int i = 0; i < len; i++) {
            compressed[i] = cc2.compress(list.get(i));
            decompressed[i] = cc2.decompress(compressed[i]);
            System.out.printf("element : %d : %d , %d%n", list.get(i), compressed[i], decompressed[i]);
        }
    }
}
class FenwickTree {
    List<Long> BIT;
    int n;
    long mod;

    public FenwickTree(int n) {
        this(n, 0);
    }

    public FenwickTree(int n, long mod) {
        this.n = n;
        this.mod = mod;
        BIT = new ArrayList<>(Collections.nCopies(n, 0L));
    }

    public FenwickTree(long[] arr) {
        this(arr.length, 0);
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }

    public FenwickTree(long[] arr, long mod) {
        this(arr.length, mod);
        for (int i = 0; i < n; i++) {
            update(i, arr[i]);
        }
    }

    public FenwickTree(List<Long> v) {
        this(v.size(), 0);
        for (int i = 0; i < n; i++) {
            update(i, v.get(i));
        }
    }

    public FenwickTree(List<Long> v, long mod) {
        this(v.size(), mod);
        for (int i = 0; i < n; i++) {
            update(i, v.get(i));
        }
    }

    public void update(int index, long delta) {
        if (mod == 0) {
            if (index == 0) {
                BIT.set(index, BIT.get(index) + delta);
                return;
            }
            for (; index < n; index += index & -index) {
                BIT.set(index, BIT.get(index) + delta);
            }
        } else {
            delta %= mod;
            if (delta < 0) {
                delta += mod;
            }
            if (index == 0) {
                BIT.set(index, (BIT.get(index) + delta) % mod);
                return;
            }
            for (; index < n; index += index & -index) {
                BIT.set(index, (BIT.get(index) + delta) % mod);
            }
        }
    }

    public long get(int index) {
        long sum = BIT.get(0);
        if (mod == 0) {
            for (; index > 0; index -= index & -index) {
                sum += BIT.get(index);
            }
        } else {
            for (; index > 0; index -= index & -index) {
                sum = (sum + BIT.get(index)) % mod;
            }
        }
        return sum;
    }

    public void print() {
        for (int i = 0; i < n; i++) {
            System.out.print(BIT.get(i) + " ");
        }
        System.out.println();
    }
}
class ModuloArithmetic {
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

class CollectionUtil {

    public static <T extends Comparable<? super T>> void removeDuplicatesAndSortList(List<T> list) {
        Set<T> set = new TreeSet<>(list);
        list.clear();
        list.addAll(set);
    }
}
class DisjointSet {
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
class BinarySearch {
    public static <T extends Comparable<T>> int upperBound(List<T> list, T target) {
        int lo = 0, hi = list.size() - 1;
        int index = list.size();
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (list.get(mid).compareTo(target) <= 0) {
                lo = mid + 1;
            } else {
                index = mid;
                hi = mid - 1;
            }
        }
        return index;
    }

    public static <T extends Comparable<T>> int lowerBound(List<T> list, T target) {
        int lo = 0, hi = list.size() - 1;
        int index = list.size();
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (list.get(mid).compareTo(target) < 0) {
                lo = mid + 1;
            } else {
                index = mid;
                hi = mid - 1;
            }
        }
        return index;
    }
}
class LIS {
    public static int lis(int[] nums) {
        return lis(nums, false);
    }
    public static int lis(int[] nums, boolean strict) {
        List<Integer> seq = new ArrayList<>();
        for (int num : nums) {
            int pos = (strict ? BinarySearch.lowerBound(seq, num) : BinarySearch.upperBound(seq, num));
            if (pos == seq.size()) {
                seq.add(num);
            } else {
                seq.set(pos, num);
            }
        }
        return seq.size();
    }

    public static int lis(long[] nums) {
        return lis(nums, false);
    }
    public static int lis(long[] nums, boolean strict) {
        List<Long> seq = new ArrayList<>();
        for (long num : nums) {
            int pos = (strict ? BinarySearch.lowerBound(seq, num) : BinarySearch.upperBound(seq, num));
            if (pos == seq.size()) {
                seq.add(num);
            } else {
                seq.set(pos, num);
            }
        }
        return seq.size();
    }

    public static <T extends Comparable> int lis(List<T> nums) {
        return lis(nums, false);
    }
    public static <T extends Comparable> int lis(List<T> nums, boolean strict) {
        List<T> seq = new ArrayList<>();
        for (T num : nums) {
            int pos = (strict ? BinarySearch.lowerBound(seq, num) : BinarySearch.upperBound(seq, num));
            if (pos == seq.size()) {
                seq.add(num);
            } else {
                seq.set(pos, num);
            }
        }
        return seq.size();
    }



}
class MathUtil {
    static long rangeAnd(long a, long b) {
        int shiftcount = 0;
        while (a != b && a > 0) {
            shiftcount++;
            a = a >> 1;
            b = b >> 1;
        }
        return (long)(a << shiftcount);
    }
    public static int log2(long n) {
        int l2 = 0;
        while (n > 1) {
            l2++;
            n >>= 1;
        }
        return l2;
    }
    public static boolean isPrime(long n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        long limit = (long)Math.sqrt(n) + 1;
        for (int i = 3; i <= limit; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    public static boolean isPrime(int n) {
        return isPrime((long)n);
    }
    public static int sumOfDigits(long n) {
        List<Integer> v = new ArrayList<Integer>();
        while (n > 0) {
            v.add((int)(n % 10));
            n /= 10;
        }
        int total = 0;
        for (int i = 0; i < v.size(); i++) {
            total += v.get(i);
        }
        return total;
    }
    public static int sumOfDigits(int n) {
        return sumOfDigits((long)n);
    }
    public static int sumOfDigits(String str) {
        int sum = 0;
        for (int i = 0; i < str.length(); i++) {
            if (Character.isDigit(str.charAt(i))) {
                sum += Character.getNumericValue(str.charAt(i));
            }
        }
        return sum;
    }
    public static void findAllFactors(int n, List<Integer> factors) {
        double sqroot = Math.sqrt(n);
        factors.add(1);
        if (n == 1) {
            return;
        }
        for (int i = 2; i <= sqroot; i++) {
            if (n % i == 0) {
                factors.add(i);
                if (n / i != i) {
                    factors.add(n / i);
                }
            }
        }
        factors.add(n);
        Collections.sort(factors);
    }
    public static void findAllFactors(long n, List<Long> factors) {
        double sqroot = Math.sqrt(n);
        factors.add((long)1);
        if (n == 1) {
            return;
        }
        for (int i = 2; i <= sqroot; i++) {
            if (n % i == 0) {
                factors.add((long)i);
                if (n / i != i) {
                    factors.add(n / i);
                }
            }
        }
        factors.add(n);
        Collections.sort(factors);
    }
}

class TrieNode {
    TrieNode[] children;
    boolean isEndOfWord;
    int freq;
    TrieNode() {
        children = new TrieNode[128];
        isEndOfWord = false;
        freq = 0;
    }
}

class Trie {
    TrieNode root;

    Trie() {
        root = new TrieNode();
    }

    void insert(String word) {
        TrieNode current = root;

        for (char c : word.toCharArray()) {
            if (current.children[c] == null) {
                current.children[c] = new TrieNode();
            }
            current = current.children[c];
        }

        current.isEndOfWord = true;
    }

    boolean search(String word) {
        TrieNode current = root;

        for (char c : word.toCharArray()) {
            if (current.children[c] == null) {
                return false;
            }
            current = current.children[c];
        }

        return current.isEndOfWord;
    }

    boolean startsWith(String prefix) {
        TrieNode current = root;

        for (char c : prefix.toCharArray()) {
            if (current.children[c] == null) {
                return false;
            }
            current = current.children[c];
        }

        return true;
    }
    String getUniquePrefix(String key) {
        TrieNode current = root;
        int index = 0;
        for (char c : key.toCharArray()) {
            if (current.children[c] == null) {
                break;
            }
            current = current.children[c];
            if (current.freq <= 1) break;
            index++;
        }
        return key.substring(0, index + 1);
    }
    List<String> getAllStartingWithPrefix(String prefix) {

        char [] arr = prefix.toCharArray();
        List<StringBuilder> lstSB = getAllStartingWithPrefixUtil(root, arr, 0);
        for (StringBuilder elem : lstSB) {
            elem.reverse();
        }
        List<String> lst = lstSB.stream()
                           .map(StringBuilder::toString)
                           .collect(java.util.stream.Collectors.toList());
        return lst;
    }
    private List<StringBuilder> getAllStartingWithPrefixUtil(TrieNode curr, char [] arr, int index) {
        int n = arr.length;
        List<StringBuilder> myList = new ArrayList<>();
        TrieNode[] children = curr.children;
        if (index < n) {
            char ch = arr[index];
            if (curr.children[ch] != null) {
                List<StringBuilder> nextList = getAllStartingWithPrefixUtil(curr.children[ch], arr, index + 1);
                if (nextList.size() >= 0) {
                    for (StringBuilder key : nextList) {
                        key.append(ch);
                        myList.add(key);
                    }
                }
                if (index == n - 1 && curr.children[ch].isEndOfWord) {
                    myList.add(new StringBuilder("" + ch));
                }
                nextList.clear();
            } else {
                return myList;
            }
        } else {
            for (char ch = 0; ch < children.length; ch++) {
                if (curr.children[ch] != null) {
                    List<StringBuilder> nextList = getAllStartingWithPrefixUtil(curr.children[ch], arr, index + 1);
                    if (nextList.size() >= 0) {
                        for (StringBuilder key : nextList) {
                            key.append(ch);
                            myList.add(key);
                        }
                    }
                    if (curr.children[ch].isEndOfWord) {
                        myList.add(new StringBuilder("" + ch));
                    }
                    nextList.clear();
                }
            }
        }
        return myList;
    }
}



class LCABinaryLifting {
    public int n;
    public int timer = 0;
    public List<List<Integer>> graph;
    public List<Integer> tin, tout;
    public List<List<Integer>> up;
    public int height = 0;
    public int root = 0;

    public LCABinaryLifting(List<List<Integer>> graph, int root) {
        this.n = graph.size();
        this.timer = 0;
        this.graph = graph;
        this.tin = new ArrayList<Integer>(Collections.nCopies(n + 1, 0));
        this.tout = new ArrayList<Integer>(Collections.nCopies(n + 1, 0));
        this.height = (int)Math.ceil(Math.log(n + 1) / Math.log(2));
        this.root = root;
        this.up = new ArrayList<List<Integer>>();
        for (int i = 0; i <= n; i++) {
            List<Integer> row = new ArrayList<Integer>(Collections.nCopies(height + 1, 0));
            this.up.add(row);
        }
        visit(root, root);
    }

    public void visit(int u, int parent) {
        timer++;
        tin.set(u, timer);
        up.get(u).set(0, parent);
        for (int i = 1; i <= height; i++) {
            up.get(u).set(i, up.get(up.get(u).get(i - 1)).get(i - 1));
        }
        for (int node : graph.get(u)) {
            if (node != parent) {
                visit(node, u);
            }
        }
        tout.set(u, timer);
    }

    public boolean isAncestor(int u, int v) {
        return (tin.get(u) <= tin.get(v) && tout.get(u) >= tout.get(v));
    }

    public int getLCA(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = height; i >= 0; i--) {
            if (!isAncestor(up.get(u).get(i), v)) {
                u = up.get(u).get(i);
            }
        }
        return up.get(u).get(0);
    }
    public int query(int u, int v) {
        return getLCA(u, v);
    }
    public static void how_to_use() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        int root = sc.nextInt();
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<Integer>());
        }
        for (int i = 0; i < m; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        LCABinaryLifting lbt = new LCABinaryLifting(graph, root);

        int q = sc.nextInt();
        for (int i = 0; i < q; i++) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int anc = lbt.getLCA(u, v);
            System.out.println("u: " + u + ", v: " + v + ", anc = " + anc);
        }
        sc.close();
    }
}

class NCRefficientMod {
    int n;
    long mod;
    int r;
    List<Long> fact, invFact, invNum;

    void calculateFactorial() {
        fact.set(0, 1L);
        fact.set(1, 1L);
        for (int i = 2; i <= n; i++) {
            fact.set(i, (fact.get(i - 1) * i) % mod);
        }
    }

    void calculateInverseNum() {
        invNum.set(0, 1L);
        invNum.set(1, 1L);
        for (int i = 2; i <= n; i++) {
            invNum.set(i, (invNum.get((int) (mod % i)) * (mod - mod / i)) % mod);
        }
    }

    void calculateInverseFactorial() {
        invFact.set(0, 1L);
        invFact.set(1, 1L);
        for (int i = 2; i <= n; i++) {
            invFact.set(i, (invNum.get(i) * invFact.get(i - 1)) % mod);
        }
    }

    NCRefficientMod(int n, long mod) {
        this.n = n;
        this.mod = mod;
        fact = new ArrayList<>(Collections.nCopies(n + 1, 0L));
        invFact = new ArrayList<>(Collections.nCopies(n + 1, 0L));
        invNum = new ArrayList<>(Collections.nCopies(n + 1, 0L));
        calculateFactorial();
        calculateInverseNum();
        calculateInverseFactorial();
    }
    NCRefficientMod(int n, int mod) {
        this(n, (long)mod);
    }

    long get(int N, int r) {
        if (N > n) return 0;
        if (r < 0 || r > N) return 0;
        long ans = (fact.get(N) * invFact.get(r)) % mod * (invFact.get(N - r)) % mod;
        return ans;
    }
    public long query(int N, int r) {
        return get(N, r);
    }
}
class EulerTotient {
    private int n;
    private ArrayList<Integer> totient;

    public EulerTotient(int N) {
        this.n = N + 1;
        this.totient = new ArrayList<Integer>(n);

        for (int i = 0; i < n; i++) {
            totient.add(i, i);
        }

        for (int i = 2; i < n; i++) {
            if (totient.get(i) == i) { // i is prime
                for (int j = 2 * i; j < n; j += i) {
                    totient.set(j, totient.get(j) * (i - 1) / i); // multiply by phi(i) = i-1 and divide by factor
                }
                totient.set(i, i - 1); // updating phi(i) = i-1; as i is prime
            }
        }
    }

    public void print() {
        for (int num : totient) {
            System.out.print(num + " ");
        }
        System.out.println();
    }

    public int get(int index) {
        return totient.get(index);
    }
}

class MatrixExp {
    private long n;
    int row, col;
    private long[][] mat;
    private long[][] resultMat;

    // function to multiply matrices
    private long[][] matrixMultiply(long[][] mat1, long[][] mat2, long mod) {
        if (mat1[0].length != mat2.length) {
            System.out.println("invalid matrix matrixMultiply");
            System.exit(0);
        }
        int myrow = mat1.length, mycol = mat2[0].length, comm = mat1[0].length;
        long[][] mulMat = new long[myrow][mycol];
        for (int i = 0; i < myrow; i++) {
            for (int j = 0; j < mycol; j++) {
                mulMat[i][j] = 0;
                for (int k = 0; k < comm; k++) {
                    mulMat[i][j] = (mulMat[i][j] + ((mat1[i][k] % mod) * (mat2[k][j] % mod)) % mod) % mod;
                }
            }
        }
        return mulMat;
    }

    // function to make identity matrix
    private void makeIdentityMatrix(long[][] identityMat) {
        for (int i = 0; i < row; i++) {
            identityMat[i] = new long[row];
            for (int j = 0; j < row; j++) {
                identityMat[i][j] = (i == j) ? 1 : 0;
            }
        }
        return;
    }

    // function to exponentiate matrix
    private long[][] exponentiate(long power, long mod) {
        if (power == 1) {
            return mat;
        }
        long[][] mymat;
        if (power == 0) {
            mymat = new long[row][row];
            makeIdentityMatrix(mymat);
            return mymat;
        }
        mymat = exponentiate(power / 2, mod);
        long[][] ansmat = matrixMultiply(mymat, mymat, mod);
        if (power % 2 == 1) {
            ansmat = matrixMultiply(ansmat, mat, mod);
        }
        return ansmat;
    }

    // constructor

    public MatrixExp(int N, long[][] vmat, long mod) {
        this((long)(N), vmat, mod);
    }
    public MatrixExp(int N, long mod) {
        this((long)(N), mod);
    }
    public MatrixExp(long N, long[][] vmat, long mod) {
        n = N;
        mat = vmat;
        row = mat.length;
        col = mat[0].length;
        resultMat = exponentiate(n, mod);
    }

    // overloaded constructor
    public MatrixExp(long N, long mod) {
        n = N;
        mat = new long[][] {{1, 1}, {1, 0}};
        row = mat.length;
        col = mat[0].length;
        resultMat = exponentiate(n, mod);
    }

    // getter for resultmatrix
    public long[][] getResultMatrix() {
        return this.resultMat;
    }
    public long[][] get() {
        return getResultMatrix();
    }
    // method to print result mat
    public void printMatrix(long[][] vmatrix) {
        for (long[] rowv : vmatrix) {
            for (long elem : rowv) System.out.print(elem + " ");
            System.out.println();
        }
    }

    public void print() {
        for (long[] rowv : resultMat) {
            for (long elem : rowv) System.out.print(elem + " ");
            System.out.println();
        }
    }
}

class Fibonacci {
    static long query(int n) {
        return query((long)n);
    }
    static long query(long n) {
        long mod = (long)(Long.MAX_VALUE);
        return query(n, mod);
    }
    static long query(int n, long mod) {
        return query((long)(n), mod);
    }
    static long query(long n, long mod) {
        if (n == 0) {
            return 0L;
        }

        long[][] mymat = {{1, 1}, {1, 0}};
        MatrixExp me = new MatrixExp(n, mymat, mod);
        long[][] fibMatrix = me.getResultMatrix();
        return fibMatrix[0][0];
    }
}

class Sieve {
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
    boolean isPrime(int num) {
        return num == getLP(num);
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
class Transformer {
    public static int ctoa(char c) {
        return c - 'a';
    }

    public static char atoc(int a) {
        return (char) (a + 'a');
    }

    public static int ctoi(char c) {
        return c - '0';
    }

    public static char itoc(int i) {
        return (char) (i - 0 + '0');
    }

    public static char tolower(char c) {
        int ascii = (int) (c - 'A');
        char c1 = (char) (ascii + 'a');
        return c1;
    }

    public static char toupper(char c) {
        int ascii = (int) (c - 'a');
        char c1 = (char) (ascii + 'A');
        return c1;
    }
}
class ChineseRemainder {
    public static long chiRem(long [] rem, long [] arr) {
        long mod = 1L;
        for (long num : arr) {
            mod *= num;
        }
        long [] mrr = arr.clone();
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            long mi = (mod / arr[i]);
            // mrr[i]=ModuloArithmetic.modInv(mi,rem[i]);
            mrr[i] = mi;
        }
        // System.out.println(Arrays.toString(mrr));
        long x = 0L;
        for (int i = 0; i < n; i++) {
            long inv = ModuloArithmetic.modInv(mrr[i], arr[i]);
            // System.out.println("inv : "+(rem[i])+" , "+(mrr[i])+" "+inv);
            long first = ModuloArithmetic.modMul(rem[i], inv, mod);
            long second = ModuloArithmetic.modMul(first, mrr[i], mod);
            // out.println("<= "+second);
            x = ModuloArithmetic.modAdd(x, second, mod);
        }
        return x;
    }
    public static void howToUse() {
        long num = ChineseRemainder.chiRem(new long[] {1, 2, 3}, new long[] {7, 5, 11});
        System.out.println(num);
    }
};

class KMP {
    int [] lps;
    String pattern = "";
    public KMP(String pattern) {
        this.pattern = pattern;
        this.lps = this.getLPS(pattern);
    }
    public static int [] getLPS(String pattern) {
        char [] arr = pattern.toCharArray();
        int n = arr.length;
        int [] lpsTable = new int[n];
        int index = 0;
        for (int i = 1; i < n;) {
            if (arr[i] == arr[index]) {
                lpsTable[i] = index + 1;
                i++;
                index++;
            } else {
                if (index != 0) {
                    index = lpsTable[index - 1];
                } else {
                    lpsTable[i] = 0;
                    i++;
                }
            }
        }
        return lpsTable;
    }
    public int [] getLPS() {
        return this.lps;
    }
    public int indexOf(String text, int start) {
        char [] textArray = text.toCharArray();
        char [] patternArray = pattern.toCharArray();
        int n = textArray.length;
        int m = patternArray.length;
        int index = 0;
        for (int i = start; i < n;) {

            // System.out.println(textArray[i]+" , "+patternArray[index]);
            // System.out.println(i+" , "+index);
            if (textArray[i] == patternArray[index]) {
                i++;
                index++;
                if (index >= m) return i - m;
            } else {
                if (index != 0) {
                    index = lps[index - 1];
                } else {
                    i++;
                }
            }
        }
        return -1;
    }
    public int indexOf(String text) {
        return this.indexOf(text, 0);
    }
}
class HybridKMPZ {

    public static int indexOf(String text, String pattern, int start) {
        String mix = pattern + "#" + text;

        char [] arr = mix.toCharArray();
        int n = arr.length;
        int [] lpsTable = new int[n];
        int index = 0;
        for (int i = 1; i < n;) {
            int currPos = i;
            int currLPS = 0;
            if (arr[i] == arr[index]) {
                lpsTable[i] = index + 1;
                currLPS = lpsTable[i];
                i++;
                index++;
            } else {
                if (index != 0) {
                    index = lpsTable[index - 1];
                } else {
                    lpsTable[i] = 0;
                    currLPS = lpsTable[i];
                    i++;
                }
            }
            if (currLPS >= pattern.length()) return currPos - pattern.length() - start + 1;
        }
        return -1;
    }
    public static int indexOf(String text, String pattern) {
        return indexOf(text, pattern, pattern.length() + 1);
    }
}

class ZAlgorithm {
    public static int[] getZ(String text, String pattern) {
        char [] arr = (pattern + "#" + text).toCharArray();
        int n = arr.length;
        int [] z = new int[n];
        int left, right;
        left = 0;
        right = 0;
        for (int i = 1; i < n; i++) {
            // System.out.println(i+" vs "+right);
            if (i > right) {
                left = right = i;
                while (right < n && arr[right] == arr[right - left]) {
                    right++;
                }
                z[i] = right - left;
                right--;
            } else {
                // System.out.println("in else");
                int k = i - left;
                if (z[k] < right - i + 1) {
                    z[i] = z[k];
                } else {
                    left = i;
                    while (right < n && arr[right] == arr[right - left]) {
                        right++;
                    }
                    z[i] = right - left;
                    right--;
                }
            }
            // System.out.println(i+" , "+z[i]);
        }
        return z;
    }
    public static int indexOf(String text, String pattern, int start) {
        start += pattern.length() + 1;
        char [] arr = (pattern + "#" + text).toCharArray();
        int n = arr.length;
        int [] z = new int[n];
        int left, right;
        left = 0;
        right = 0;
        for (int i = 1; i < n; i++) {
            // System.out.println(i+" vs "+right);
            if (i > right) {
                left = right = i;
                while (right < n && arr[right] == arr[right - left]) {
                    right++;
                }
                z[i] = right - left;
                right--;
            } else {
                // System.out.println("in else");
                int k = i - left;
                if (z[k] < right - i + 1) {
                    z[i] = z[k];
                } else {
                    left = i;
                    while (right < n && arr[right] == arr[right - left]) {
                        right++;
                    }
                    z[i] = right - left;
                    right--;
                }
            }
            if (z[i] >= pattern.length()) {
                // System.out.println("match at : "+i);
                return i - start;
            }
            // System.out.println(i+" , "+z[i]);
        }

        return -1;
    }
    public static int indexOf(String text, String pattern) {
        return indexOf(text, pattern, 0);
    }
}

// remaining topics :

/*
segment trees
Merge sort tree
hld
centroid decomp
manacher,rabin
sparse table
fft , ntt
*/

// shreepad sharanam