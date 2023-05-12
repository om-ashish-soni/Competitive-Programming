package com.library.bitmanip;

public class KerninghanAlgo {
    public static int setBits(int n){
        int ctr=0;
        while(n != 0){
            ctr++;
            n=(n & (n-1));
        }
        return ctr;
    }
}
