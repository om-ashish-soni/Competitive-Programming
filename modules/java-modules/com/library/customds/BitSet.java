package com.library.customds;

import com.library.io.Printer;

import java.util.ArrayList;

public class BitSet{
    public int size=65;
    public int n;
    public ArrayList<Byte> bits;
    public int setBitsCount=0;
    public BitSet(int n){
        this.n=n;
        //this.bits=Creator.createList(size,0L);
        this.bits=new ArrayList<Byte>(size);
        int index=0;
        for(;index<size;index++){
            if((n & 1L) == 1L)this.set(index);
            n>>=1;
        }
    }
    public BitSet(long n){

        //this.bits=Creator.createList(size,0L);
        this.bits=new ArrayList<Byte>(size);
        int index=0;
        for(;index<size;index++){
            if((n & 1L) == 1L)this.set(index);
            n>>=1;
        }
    }
    public void setAll(byte val){
        for(int i=0;i<size;i++){
            this.bits.set(i,val);
        }
    }
    public void set(){
        //Setter.setAll(bits,1L);
        this.setAll((byte)1);
        this.setBitsCount=n;
    }
    public void reset(){
        //Setter.setAll(bits,0L);
        this.setAll((byte)0);
        this.setBitsCount=0;
    }
    public void clear(){
        this.reset();
    }
    public byte get(int index){
        return bits.get(index);
    }
    public void set(int index){
        byte oldValue=this.get(index);
        if(oldValue != 1L){
            this.flip(index);
        }
    }
    public void reset(int index){
        byte oldValue=this.get(index);
        if(oldValue != 0){
            this.flip(index);
        }
    }
    public void flip(int index){
        byte oldValue=this.get(index);
        if(oldValue == 0) this.setBitsCount+=1;
        else this.setBitsCount-=1;
        bits.set(index,(byte)(1 ^ oldValue));
    }
    public void flip(){
        for(int index=0;index<size;index++){
            this.flip(index);
        }
    }
    public long count(){
        return this.setBitsCount;
    }
    public void print(){
        Printer.printList(bits);
    }
    public void println(){
        Printer.printlnList(bits);
    }
    public long toLong(){
        long number=0L;
        long weight=1L;
        for(int index=0;index<this.size;index++){
            if(this.get(index)==1L) number+=weight;
            weight<<=1L;
        }
        return number;
    }
    @Override
    public String toString(){
        String s="";
        for(int index=0;index<this.size;index++){
            if(this.get(index)==0) s+="0";
            else s+="1";
        }
        return s;
    }
}