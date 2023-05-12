package com.library.mathlib;

import com.library.customds.Pair;

public class LcmGcd{
    public static Pair<Long,Long> extendedGcd(long a, long b){
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