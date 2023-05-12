package com.library.io;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class FastScanner {
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
    public int[] readIntArray(int n) {
        int[] a=new int[n];
        for (int i=0; i<n; i++) a[i]=nextInt();
        return a;
    }
    public long[] readLongArray(int n) {
        long[] a=new long[n];
        for (int i=0; i<n; i++) a[i]=nextLong();
        return a;
    }
    public long nextLong() {
        return Long.parseLong(next());
    }
}
