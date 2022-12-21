package com.library.algo;

import java.util.*;

public class BinarySearch {
    // lower bound
    public static <T extends Comparable<T>> int lowerBound(List<T> lst,T key,int l,int r){

        int n=lst.size();
        boolean found=false;
        int index=r+1;

        while(l<=r){
            boolean flag=(l==r);
            int mid=(l+r)/2;
            int decision=lst.get(mid).compareTo(key);

            if(decision==-1){
                l=mid+1;
            }else{
                r=mid;
                found=true;
                index=Math.min(index,mid);
            }
            if(flag) break;
        }

        return index;
    }
    public static <T extends Comparable<T>> int lowerBound(List<T> lst,T key){
        int n=lst.size();
        return lowerBound(lst,key,0,n-1);
    }
    public static <T> int lowerBound(List<T> lst,T key,int l,int r,Comparator<T> comparator){

        int n=lst.size();
        boolean found=false;
        int index=n;


        while(l<=r){
            boolean flag=(l==r);
            int mid=(l+r)/2;
            int decision=comparator.compare(lst.get(mid),key);

            if(decision==-1){
                l=mid+1;
            }else{
                r=mid;
                found=true;
                index=Math.min(index,mid);
            }
            if(flag) break;
        }

        return index;
    }
    public static <T> int lowerBound(List<T> lst,T key,Comparator<T> comparator){
        int n=lst.size();
        return lowerBound(lst,key,0,n-1,comparator);
    }
    public static <T extends Comparable<T>> int lowerBound(T[] arr,T key,int l,int r){
        List<T> lst=new ArrayList<>();
        for(T num:arr) lst.add(num);
        return lowerBound(lst,key,l,r);
    }
    public static <T extends Comparable<T>> int lowerBound(T[] arr,T key){
        List<T> lst=new ArrayList<>();
        for(T num:arr) lst.add(num);
        return lowerBound(lst,key);
    }
    public static int lowerBound(int [] arr,int key,int l,int r){
        List<Integer> lst=new ArrayList<>();
        for(int num:arr) lst.add(num);
        return lowerBound(lst,key,l,r);
    }
    public static int lowerBound(int [] arr,int key){
        List<Integer> lst=new ArrayList<>();
        for(int num:arr) lst.add(num);
        return lowerBound(lst,key);
    }
    public static int lowerBound(long [] arr,long key,int l,int r){
        List<Long> lst=new ArrayList<>();
        for(long num:arr) lst.add(num);
        return lowerBound(lst,key,l,r);
    }
    public static int lowerBound(long [] arr,long key){
        List<Long> lst=new ArrayList<>();
        for(long num:arr) lst.add(num);
        return lowerBound(lst,key);
    }
    public static int lowerBound(double [] arr,double key,int l,int r){
        List<Double> lst=new ArrayList<>();
        for(double num:arr) lst.add(num);
        return lowerBound(lst,key,l,r);
    }
    public static int lowerBound(double [] arr,double key){
        List<Double> lst=new ArrayList<>();
        for(double num:arr) lst.add(num);
        return lowerBound(lst,key);
    }
    public static int lowerBound(char [] arr,char key,int l,int r){
        List<Character> lst=new ArrayList<>();
        for(char num:arr) lst.add(num);
        return lowerBound(lst,key,l,r);
    }
    public static int lowerBound(char [] arr,char key){
        List<Character> lst=new ArrayList<>();
        for(char num:arr) lst.add(num);
        return lowerBound(lst,key);
    }

    // upper bound
    public static <T extends Comparable<T>> int upperBound(List<T> lst,T key,int l,int r){
        int n=lst.size();
        boolean found=false;
        int index=n;

        while(l<=r){
            boolean flag=(l==r);
            int mid=(l+r)/2;
            int decision=lst.get(mid).compareTo(key);

            if(decision != 1){
                l=mid+1;
            }else{
                r=mid;
                found=true;
                index=Math.min(index,mid);
            }
            if(flag) break;
        }

        return index;
    }
    public static <T extends Comparable<T>> int upperBound(List<T> lst,T key){
        int n=lst.size();
        return upperBound(lst,key,0,n-1);
    }
    public static <T> int upperBound(List<T> lst,T key,int l,int r,Comparator<T> comparator){

        int n=lst.size();
        boolean found=false;
        int index=n;


        while(l<=r){
            boolean flag=(l==r);
            int mid=(l+r)/2;
            int decision=comparator.compare(lst.get(mid),key);

            if(decision != 1){
                l=mid+1;
            }else{
                r=mid;
                found=true;
                index=Math.min(index,mid);
            }
            if(flag) break;
        }

        return index;
    }
    public static <T> int upperBound(List<T> lst,T key,Comparator<T> comparator){
        int n=lst.size();
        return upperBound(lst,key,0,n-1,comparator);
    }
    public static <T extends Comparable<T>> int upperBound(T[] arr,T key,int l,int r){
        List<T> lst=new ArrayList<>();
        for(T num:arr) lst.add(num);
        return upperBound(lst,key,l,r);
    }
    public static <T extends Comparable<T>> int upperBound(T[] arr,T key){
        List<T> lst=new ArrayList<>();
        for(T num:arr) lst.add(num);
        return upperBound(lst,key);
    }
    public static int upperBound(int [] arr,int key,int l,int r){
        List<Integer> lst=new ArrayList<>();
        for(int num:arr) lst.add(num);
        return upperBound(lst,key,l,r);
    }
    public static int upperBound(int [] arr,int key){
        List<Integer> lst=new ArrayList<>();
        for(int num:arr) lst.add(num);
        return upperBound(lst,key);
    }
    public static int upperBound(long [] arr,long key,int l,int r){
        List<Long> lst=new ArrayList<>();
        for(long num:arr) lst.add(num);
        return upperBound(lst,key,l,r);
    }
    public static int upperBound(long [] arr,long key){
        List<Long> lst=new ArrayList<>();
        for(long num:arr) lst.add(num);
        return upperBound(lst,key);
    }
    public static int upperBound(double [] arr,double key,int l,int r){
        List<Double> lst=new ArrayList<>();
        for(double num:arr) lst.add(num);
        return upperBound(lst,key,l,r);
    }
    public static int upperBound(double [] arr,double key){
        List<Double> lst=new ArrayList<>();
        for(double num:arr) lst.add(num);
        return upperBound(lst,key);
    }
    public static int upperBound(char [] arr,char key,int l,int r){
        List<Character> lst=new ArrayList<>();
        for(char num:arr) lst.add(num);
        return upperBound(lst,key,l,r);
    }
    public static int upperBound(char [] arr,char key){
        List<Character> lst=new ArrayList<>();
        for(char num:arr) lst.add(num);
        return upperBound(lst,key);
    }

    // deprecated
//    public static int lowerBound(int key[],int key){
//        int index= Arrays.binarySearch(key,key);
//        if(index>=0) return index;
//        return Math.abs(index+1);
//    }
//    public static int lowerBound(long key[],long key){
//        int index= Arrays.binarySearch(key,key);
//        if(index>=0) return index;
//        return Math.abs(index+1);
//    }
//    public static <T> int lowerBound(double key[],double key){
//        int index= Arrays.binarySearch(key,key);
//        if(index>=0) return index;
//        return Math.abs(index+1);
//    }
//    public static <T> int lowerBound(float key[],float key){
//        int index= Arrays.binarySearch(key,key);
//        if(index>=0) return index;
//        return Math.abs(index+1);
//    }
//    public static <T> int lowerBound(char key[],char key){
//        int index= Arrays.binarySearch(key,key);
//        if(index>=0) return index;
//        return Math.abs(index+1);
//    }
//    public static <T> int lowerBound(T key[],T key){
//        int index= Arrays.binarySearch(key,key);
//        if(index>=0) return index;
//        return Math.abs(index+1);
//    }
//    public static <T extends Comparable<T>> int lowerBound(List<T> lst, T key){
//        int index= Collections.binarySearch(lst,key);
//        if(index>=0) return index;
//        return Math.abs(index+1);
//    }
}
