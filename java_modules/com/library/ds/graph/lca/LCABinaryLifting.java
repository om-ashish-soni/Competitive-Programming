package com.library.ds.graph.lca;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class LCABinaryLifting {
    int n;
    int timer=0;
    List<List<Integer>> graph;
    List<Integer> timeIn,timeOut;
    List<List<Integer>> up;
    int height=0;
    int root=0;
    public LCABinaryLifting(List<List<Integer>> graph,int root){
        this.n=graph.size();
        this.timer=0;
        this.graph=graph;
        this.timeIn=new ArrayList<>();
        this.timeOut=new ArrayList<>();
        for(int i=0;i<n;i++){
            this.timeIn.add(0);
            this.timeOut.add(0);
        }
        this.height=(int)Math.ceil((double)Math.log((double)(n+1))/Math.log((double)2));
        this.up=new ArrayList<>();
        for(int i=0;i<n;i++){
            this.up.add(new ArrayList<>());
        }
        this.root=root;
        visit(this.root,this.root);
    }
    public void visit(int u,int parent){
        timer++;
        timeIn.set(u,timer);
        List<Integer> row=up.get(u);
        row.add(parent);
        for(int i=1;i<=height;i++){
            int prevAncestor=row.get(i-1);
            int ancestor=up.get(prevAncestor).get(i-1);
            row.add(ancestor);
        }
        for(int node:graph.get(u)){
            if(node != parent){
                visit(node,u);
            }
        }
        timeOut.set(u,timer);
    }
    public boolean isAncestor(int u,int v){
        return (timeIn.get(u) <= timeIn.get(v) && timeOut.get(u) >= timeOut.get(v));
    }
    public int getLCA(int u,int v){
        if(isAncestor(u,v)) return u;
        if(isAncestor(v,u)) return v;
        for(int i=height;i>=0;i--){
            if(false==isAncestor(up.get(u).get(i),v)){
                u=up.get(u).get(i);
            }
        }
        return up.get(u).get(0);
    }
    public static void howToUse(){
        int n=6;
        int m=4;
        List<List<Integer>> graph=new ArrayList<>();
        for(int i=0;i<n;i++){
            graph.add(new ArrayList<>());
        }
        graph.get(0).add(1);
        graph.get(0).add(2);
        graph.get(1).add(3);
        graph.get(2).add(4);
        graph.get(2).add(5);
        LCABinaryLifting lbt=new LCABinaryLifting(graph,0);
        int anc=lbt.getLCA(5,4);
        System.out.println("anc : "+anc);
    }
}
