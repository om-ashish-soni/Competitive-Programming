package com.library.heavyds;

public class DisjointSet{
    public int [] arr;
    public int n;
    public DisjointSet(int n){
        this.n=n;
        arr=new int[n];
        for(int i=0;i<n;i++) arr[i]=-1;
    }
    public int findSet(int u){
        int r=u;
        while(arr[r] >= 0){
            r=arr[r];
        }
        while(u != r){
            int next=arr[u];
            arr[u]=r;
            u=next;
        }
        return r;
    }
    public boolean setUnion(int u,int v){
        int uroot=this.findSet(u);
        int vroot=this.findSet(v);
        if(uroot==vroot) return false;
        int totalChilds=arr[uroot]+arr[vroot];
        if(arr[uroot]<arr[vroot]){
            arr[vroot]=uroot;
            arr[uroot]=totalChilds;
        }else{
            arr[uroot]=vroot;
            arr[vroot]=totalChilds;
        }
        return true;
    }
    public boolean preferedUnion(int u,int v){
        int uroot=this.findSet(u);
        int vroot=this.findSet(v);
        if(uroot==vroot) return false;
        int totalChilds=arr[uroot]+arr[vroot];
        arr[uroot]=vroot;
        arr[vroot]=totalChilds;
        return true;
    }
}

