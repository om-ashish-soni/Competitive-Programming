package com.library.ds.graph.flow;


import java.util.*;

public class Dinic {
    final long flowInfinity=(long)1e18+10;
    List<FlowEdge> edges;
    List<List<Integer>> graph;
    List<Integer> level;
    List<Integer> posPointer;
    Queue<Integer> queue;
    int n=0;
    int m=0;
    int source=0;
    int sink=0;
    public Dinic(int n,int source,int sink){
        this.n=n;
        this.source=source;
        this.sink=sink;
        this.edges=new ArrayList<FlowEdge>();
        this.graph=new ArrayList<List<Integer>>(n);
        this.level=new ArrayList<Integer>(n);
        this.posPointer=new ArrayList<Integer>(n);
        this.queue=new LinkedList<>();
        for(int i=0;i<n;i++){
            graph.add(new ArrayList<Integer>());
            this.level.add(0);
            posPointer.add(0);
        }
    }
    public void addEdge(int u,int v,long capacity){
        FlowEdge forwardEdge=new FlowEdge(u,v,capacity);
        FlowEdge backwardEdge=new FlowEdge(v,u,0L);
        graph.get(u).add(edges.size());
        edges.add(forwardEdge);
        graph.get(v).add(edges.size());
        edges.add(backwardEdge);
        m=edges.size();
    }
    public void print(){
        for(int i=0;i<n;i++){
            for(int edgeIndex:graph.get(i)){
            }
        }

    }
    public boolean bfs(){

        while(queue.isEmpty()==false){
            int u=queue.peek();
            queue.remove();
            for(int edgeIndex:graph.get(u)){
                FlowEdge edge=edges.get(edgeIndex);
                if(edge.getCapacity() - edge.getFlow()<1) continue;
                if(level.get(edge.v) != -1) continue;
                level.set(edge.v,level.get(u)+1);
                queue.add(edge.v);
            }
        }
        return level.get(sink) != -1;
    }
    public long dfs(int u,long incomingFlow){
        if(incomingFlow==0) return 0;
        if(u==sink) return incomingFlow;
        int edgeIndex=posPointer.get(u);
        for(int index:graph.get(u)){
            FlowEdge innerEdge=edges.get(index);
        }
        while(edgeIndex<graph.get(u).size()){
            FlowEdge edge=edges.get(graph.get(u).get(edgeIndex));
            FlowEdge backwardEdge=edges.get(graph.get(u).get(edgeIndex) ^ 1);
            int v=edge.v;
            if(level.get(u)+1 == level.get(v) && edge.getCapacity()-edge.getFlow()>0){
                long addonFlow=dfs(v,Math.min(incomingFlow,edge.getCapacity()-edge.getFlow()));
                if(addonFlow!=0){
                    edge.addFlow(addonFlow);
                    backwardEdge.addFlow(0L-addonFlow);
                    return addonFlow;
                }
            }
            edgeIndex++;
            posPointer.set(u,edgeIndex);
        }
        return 0L;
    }
    public long flow(){

        long maxFlow=0;
        while(true){
            Collections.fill(level,-1);
            level.set(source,0);
            queue.add(source);
            if(bfs()==false) break;
            Collections.fill(posPointer,0);
            while(true){

                long bottleNeck=dfs(source,flowInfinity);
                if(bottleNeck==0) break;
                maxFlow+=bottleNeck;
            }
        }
        return maxFlow;
    }
    static class FlowEdge{
        public int u,v;
        long capacity=0,flow=0;
        FlowEdge(int u,int v,long capacity,long flow){
            this.u=u;
            this.v=v;
            this.capacity=capacity;
            this.flow=flow;
        }
        FlowEdge(int u,int v,long capacity){
            this.u=u;
            this.v=v;
            this.capacity=capacity;
        }
        public long getCapacity(){
            return this.capacity;
        }
        public long getFlow(){
            return this.flow;
        }
        public void addFlow(long addonFlow){
            this.flow+=addonFlow;
        }
    }
    public static void howToUse(){
        int n=6;
        int source=0;
        int sink=n-1;
        Dinic dinic=new Dinic(n,source,sink);
        dinic.addEdge(0, 1, 16);
        dinic.addEdge(0, 2, 13);
        dinic.addEdge(1, 2, 10);
        dinic.addEdge(1, 3, 12);
        dinic.addEdge(2, 1, 4);
        dinic.addEdge(2, 4, 14);
        dinic.addEdge(3, 2, 9);
        dinic.addEdge(3, 5, 20);
        dinic.addEdge(4, 3, 7);
        dinic.addEdge(4, 5, 4);
        long maxFlow=dinic.flow();
        System.out.println("maxFlow : "+maxFlow);
    }
}
