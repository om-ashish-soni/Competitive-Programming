package com.library.mathlib.moduloarithmetic;

import com.library.customds.Pair;
import com.library.io.Printer;
import com.library.mathlib.LcmGcd;

public class Modulo{
    public long mod=(long)(1e9+7);
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
        Pair<Long,Long> pr= LcmGcd.extendedGcd(a,mod);
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
