package com.library.mathlib.moduloarithmetic;

import com.library.customds.Pair;
import com.library.io.Printer;
import com.library.mathlib.LcmGcd;

public class ModuloStatic {

    public static long power(long a,long b,int mod){
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
    public static long add(long a,long b,int mod){
        return (a%mod + b%mod)%mod;
    }
    public static long sub(long a,long b,int mod){
        return (a%mod - b%mod + mod)%mod;
    }
    public static long mul(long a,long b,int mod){
        return ((a%mod)*(b%mod))%mod;
    }
    public static long inverse(long a,int mod){
        Pair<Long,Long> pr= LcmGcd.extendedGcd(a,mod);
        long gcd=a*pr.first + mod*pr.second;
        if(gcd != 1) return -1;
        return (pr.first%mod + mod)%mod;
    }
    public static long div(long a,long b,int mod){
        a=a%mod;
        long inv=inverse(b,mod);
        return mul(a,inv,mod);
    }
}
