package com.library.customds;

public class Pair<T extends Comparable<T>,V extends Comparable<V>> implements Comparable<Pair<T,V>>
{
    // Return a map entry (key-value pair) from the specified values
    public T first;
    public V second;
    public Pair(T first,V second){
        this.first=first;
        this.second=second;
    }
    @Override
    public String toString(){
        return "{ "+this.first+" , "+this.second+" }";
    }

    @Override
    public int compareTo(Pair<T,V> pr){
        int firstComparision=this.first.compareTo(pr.first);
        if(firstComparision==0){
            return this.second.compareTo(pr.second);
        }
        return firstComparision;
    }
}