package com.library.customds;

public class MyPair<T extends Comparable<T>,V extends Comparable<V>> implements Comparable<MyPair<T,V>> {
    // Return a map entry (key-value pair) from the specified values
    public T first;
    public V second;
    public MyPair(T first,V second){
        this.first=first;
        this.second=second;
    }
    @Override
    public String toString(){
        return "{ "+this.first+" , "+this.second+" }";
    }

    @Override
    public int compareTo(MyPair<T,V> pr){
        int firstComparision=this.first.compareTo(pr.first);
        if(firstComparision==0){
            return this.second.compareTo(pr.second);
        }
        return firstComparision;
    }
}