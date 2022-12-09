package com.library.ds.graph.flow;

import java.util.*;

public class MPM {
    final long flowInfinity=(long)(1e18+10);
    List<FlowEdge> edges;
    List<Boolean> alive;
    List<Long> incomingFlow,outgoingFlow;
    List<Set<Integer>> inEdges,outEdges;
    List<List<Integer>> graph;
    List<Long> ex;
    List<Integer> level;
    Queue<Integer> queue;
    int n=0,m=0;
    int source=0,sink=0;
    public MPM(int n,int source,int sink){
        this.n=n;
        this.source=source;
        this.sink=sink;
        initialize();
    }
    public void initialize(){
        edges=new ArrayList<>();
        alive=new ArrayList<>(n);
        incomingFlow=new ArrayList<>(n);
        outgoingFlow=new ArrayList<>(n);
        inEdges=new ArrayList<>(n);
        outEdges=new ArrayList<>(n);
        graph=new ArrayList<>(n);
        ex=new ArrayList<>(n);
        level=new ArrayList<>(n);
        queue=new LinkedList<Integer>();
        for(int i=0;i<n;i++){
            incomingFlow.add(0L);
            outgoingFlow.add(0L);
            ex.add(0L);
            level.add(-1);
            alive.add(true);
            inEdges.add(new HashSet<Integer>());
            outEdges.add(new HashSet<Integer>());
            graph.add(new ArrayList<>());
        }
    }
    public void addEdge(int u,int v,long capacity){
        FlowEdge forwardEdge=new FlowEdge(u,v,capacity);
        FlowEdge backwardEdge=new FlowEdge(v,u,0L);
        graph.get(u).add(edges.size());
        edges.add(forwardEdge);
        graph.get(v).add(edges.size());
        edges.add(backwardEdge);
        m+=2;
    }
    boolean bfs(){
        while(queue.isEmpty()==false){
            int node=queue.peek();
            queue.remove();
            for(int edgeIndex:graph.get(node)){
                FlowEdge edge=edges.get(edgeIndex);
                if(edge.getCapacity()-edge.getFlow()<1) continue;
                if(level.get(edge.v) != -1) continue;
                level.set(edge.v,level.get(node)+1);
                queue.add(edge.v);
            }
        }
        return level.get(sink) != -1;
    }
    public long getPassingCapacity(int node){
        return Math.min(incomingFlow.get(node),outgoingFlow.get(node));
    }
    public void removeNode(int node){

        for(int edgeIndex:inEdges.get(node)){
            FlowEdge edge=edges.get(edgeIndex);
            int u=edge.u;
            outEdges.get(u).remove(edgeIndex);
            outgoingFlow.set(u,outgoingFlow.get(u)-(edge.getCapacity()-edge.getFlow()));

        }
        for(int edgeIndex:outEdges.get(node)){
            FlowEdge edge=edges.get(edgeIndex);
            int v=edge.v;
            inEdges.get(v).remove(edgeIndex);
            incomingFlow.set(v,incomingFlow.get(v)-(edge.getCapacity()-edge.getFlow()));

        }
    }
    public void pushFlow(int from,int to,long flow,boolean isForward){

        Collections.fill(ex,0L);
        ex.set(from,flow);
        queue.add(from);
        while(queue.isEmpty()==false){
            int top=queue.peek();
            queue.remove();
            if(top==to) break;
            long incoming=ex.get(top);
            Set<Integer> connectedEdgesSet=(isForward)?(outEdges.get(top)):(inEdges.get(top));
            List<Integer> connectedEdges=new ArrayList<>();
            connectedEdges.addAll(connectedEdgesSet);
            for(int edgeIndex:connectedEdges){
                FlowEdge edge=edges.get(edgeIndex);
                int currentNode=top;
                int otherNode=(isForward)?(edge.v):(edge.u);
                long pushed=Math.min(incoming,edge.getCapacity()- edge.getFlow());
                if(pushed==0) break;
                if(isForward){

                    outgoingFlow.set(currentNode,outgoingFlow.get(currentNode)-pushed);
                    incomingFlow.set(otherNode,incomingFlow.get(otherNode)-pushed);

                }else{

                    incomingFlow.set(currentNode,incomingFlow.get(currentNode)-pushed);
                    outgoingFlow.set(otherNode,outgoingFlow.get(otherNode)-pushed);

                }
                if(ex.get(otherNode)==0){
                    queue.add(otherNode);
                }
                ex.set(otherNode,ex.get(otherNode)+pushed);
                edge.addFlow(pushed);



                FlowEdge backwardEdge=edges.get(edgeIndex ^ 1);
                backwardEdge.addFlow(0L-pushed);
                incoming-=pushed;
                if(edge.getCapacity()-edge.getFlow()==0){
                    if(isForward){
                        outEdges.get(currentNode).remove(edgeIndex);
                        inEdges.get(otherNode).remove(edgeIndex);
                    }else{
                        outEdges.get(otherNode).remove(edgeIndex);
                        inEdges.get(currentNode).remove(edgeIndex);
                    }
                }else break;
                if(incoming==0) break;
            }
        }
    }
    int stopper=0;
    public long flow(){

        long maxFlow=0;
        while(true){

            Collections.fill(incomingFlow,0L);
            Collections.fill(outgoingFlow,0L);
            Collections.fill(level,-1);
            Collections.fill(alive,true);
            level.set(source,0);
            queue.add(source);
            if(bfs()==false) break;
            for(int i=0;i<n;i++){
                outEdges.get(i).clear();
                inEdges.get(i).clear();
            }
            for(int i=0;i<edges.size();i++){
                int edgeIndex=i;
                FlowEdge edge=edges.get(edgeIndex);
                if(edge.getCapacity()-edge.getFlow()==0) continue;
                int u=edge.u;
                int v=edge.v;
                if(level.get(u)+1==level.get(v) && (level.get(v) < level.get(sink) || v==sink) ){

                    outEdges.get(u).add(edgeIndex);
                    inEdges.get(v).add(edgeIndex);
                    incomingFlow.set(v,incomingFlow.get(v)+(edge.getCapacity()-edge.getFlow()));
                    outgoingFlow.set(u,outgoingFlow.get(u)+(edge.getCapacity()-edge.getFlow()));
                }
            }
            incomingFlow.set(source,flowInfinity);
            outgoingFlow.set(sink,flowInfinity);

            for(int i=0;i<n;i++){

            }

//            for(FlowEdge edge:edges){

//            }

            while(true){

                int criticalNode=-1;
                for(int i=0;i<n;i++){
                    if(alive.get(i)==false) continue;
                    if(criticalNode==-1 || getPassingCapacity(i)<getPassingCapacity(criticalNode)){
                        criticalNode=i;
                    }
                }


                if(criticalNode==-1){
                    break;
                }


                if(stopper++>20) return -1L;//removeThis

                if(getPassingCapacity(criticalNode)==0){
                    alive.set(criticalNode,false);
                    removeNode(criticalNode);
                    continue;
                }
                long passedFlow=getPassingCapacity(criticalNode);
                maxFlow+=passedFlow;
                pushFlow(criticalNode,source,passedFlow,false);
                pushFlow(criticalNode,sink,passedFlow,true);
                alive.set(criticalNode,false);
                removeNode(criticalNode);
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
        MPM mpm=new MPM(n,source,sink);
        mpm.addEdge(0, 1, 16);
        mpm.addEdge(0, 2, 13);
        mpm.addEdge(1, 2, 10);
        mpm.addEdge(1, 3, 12);
        mpm.addEdge(2, 1, 4);
        mpm.addEdge(2, 4, 14);
        mpm.addEdge(3, 2, 9);
        mpm.addEdge(3, 5, 20);
        mpm.addEdge(4, 3, 7);
        mpm.addEdge(4, 5, 4);
        long maxFlow=mpm.flow();
        System.out.println("maxFlow : "+maxFlow);
    }
}
