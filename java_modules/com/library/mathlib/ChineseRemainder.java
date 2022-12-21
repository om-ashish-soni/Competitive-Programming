package com.library.mathlib;

import com.library.mathlib.moduloarithmetic.Modulo;
import com.library.mathlib.moduloarithmetic.ModuloStatic;

public class ChineseRemainder {
    int [] arr,rem;
    int ans=-1;
    int mod=(int)(1e9+7);
    public ChineseRemainder(int [] arr,int [] rem){
        this.arr=arr;
        this.rem=rem;
        this.process();
    }
    public ChineseRemainder(int [] arr,int [] rem,int mod){
        this.arr=arr;
        this.rem=rem;
        this.mod=mod;
        this.process();
    }
    public void process(){
        int prod=1;
        int result=0;
        for(int num:arr) prod=(int) ModuloStatic.mul((long)prod,(long)num,mod);
        for(int i=0;i<arr.length;i++){
            int restProduct=(int)ModuloStatic.div(prod,arr[i],mod);
            int inv=(int)(ModuloStatic.inverse(restProduct,arr[i]));
            int addon=(int)ModuloStatic.mul(rem[i],ModuloStatic.mul(restProduct,inv,mod),mod);
            result=(int)ModuloStatic.add(result,addon,mod);
        }
        ans=result%prod;
    }
    public int get(){
        return ans;
    }

}
