package com.library.heavyds;

import com.library.io.Printer;

import java.util.ArrayList;

public class FenwickTree{
    int n;
    long []BIT;
    public void init(){
        BIT=new long[n];
        for(int i=0;i<n;i++) BIT[i]=0;
    }
    public FenwickTree(int n){
        this.n=n;
        init();
    }
    public FenwickTree(ArrayList<Long> lst){
        this.n=lst.size();
        init();
        BIT[0]=lst.get(0);
        for(int index=1;index<n;index++){
            this.update(index,lst.get(index));
        }
    }
    public FenwickTree(long []lst,int n){
        this.n=n;
        init();
        BIT[0]=lst[0];
        for(int index=1;index<n;index++){
            this.update(index,lst[index]);
        }
    }
    public void update(int index,long delta){
        if(index==0) {
            BIT[index]+=delta;
            return;
        }
        for(;index<n;index+=(index & -index)){
            BIT[index]+=delta;
        }
    }
    public long get(int index){
        long sum=BIT[0];
        for(;index>0;index-=(index & -index)){
            sum+=BIT[index];
        }
        return sum;
    }
    public long[] getBIT(){
        return BIT;
    }
}