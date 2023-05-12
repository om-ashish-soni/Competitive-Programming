package com.library.algo;

import java.util.*;

public class LIS {
    public static <T extends Comparable<T>> List<T> get(List<T> lst){
        List<T> lis=new ArrayList<>();
        for(T elem:lst){
            int index=BinarySearch.upperBound(lis,elem);
            if(index<lis.size()){
                lis.set(index,elem);
            }else{
                lis.add(elem);
            }
        }
        return lis;
    }
    public static <T> List<T> get(List<T> lst, Comparator<T> comparator){
        List<T> lis=new ArrayList<>();
        for(T elem:lst){
            int index=BinarySearch.upperBound(lis,elem,comparator);
            if(index<lis.size()){
                lis.set(index,elem);
            }else{
                lis.add(elem);
            }
        }
        return lis;
    }
    public static <T extends Comparable<T>> List<T> get(T arr[]){
        List<T> lst=new ArrayList<>(arr.length);
        for(T num:arr) lst.add(num);
        return get(lst);
    }
    public static List<Integer> get(int arr[]){
        List<Integer> lst=new ArrayList<>(arr.length);
        for(int num:arr) lst.add(num);
        return get(lst);
    }
    public static List<Long> get(long arr[]){
        List<Long> lst=new ArrayList<>(arr.length);
        for(long num:arr) lst.add(num);
        return get(lst);
    }
    public static List<Double> get(double arr[]){
        List<Double> lst=new ArrayList<>(arr.length);
        for(double num:arr) lst.add(num);
        return get(lst);
    }
    public static List<Character> get(char arr[]){
        List<Character> lst=new ArrayList<>(arr.length);
        for(char num:arr) lst.add(num);
        return get(lst);
    }


}
