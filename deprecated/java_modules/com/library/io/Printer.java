package com.library.io;

import java.io.PrintWriter;
import java.util.ArrayList;

public class Printer{
    public static PrintWriter out;
    public static void print(Object o1){
        out.print(o1+" ");
    }
    public static void print(Object o1,Object o2){
        out.print(o1+" "+o2+" ");
    }
    public static void print(Object o1,Object o2,Object o3){
        out.print(o1+" "+o2+" "+o3+" ");
    }
    public static void print(Object o1,Object o2,Object o3,Object o4){
        out.print(o1+" "+o2+" "+o3+" "+o4+" ");
    }
    public static void printList(ArrayList<?> lst){
        lst.forEach((elem)->print(elem));
    }
    public static <T> void printArray(T []arr){
        for(int i=0;i<arr.length;i++) print(arr[i]);
    }
    public static void printArray(long []arr){
        for(int i=0;i<arr.length;i++) print(arr[i]);
    }
    public static void printArray(int []arr){
        for(int i=0;i<arr.length;i++) print(arr[i]);
    }

    public static void printReject(){
        print(-1);
    }
    public static void printYESNO(boolean b){
        if(b) print("YES");
        else print("NO");
    }
    public static void printYesNo(boolean b){
        if(b) print("Yes");
        else print("No");
    }
    public static void printyesno(boolean b){
        if(b) print("yes");
        else print("no");
    }
    public static void println(){
        out.println();
    }
    public static void println(Object o1){
        out.println(o1);
    }
    public static void println(Object o1,Object o2){
        out.println(o1+" "+o2);
    }
    public static void println(Object o1,Object o2,Object o3){
        out.println(o1+" "+o2+" "+o3);
    }
    public static void println(Object o1,Object o2,Object o3,Object o4){
        out.println(o1+" "+o2+" "+o3+" "+o4);
    }
    public static void printlnList(ArrayList<?> lst){
        printList(lst);
        println();
    }
    public static <T> void printlnArray(T []arr){
        printArray(arr);
        println();
    }
    public static void printlnArray(int []arr){
        printArray(arr);
        println();
    }
    public static void printlnArray(long []arr){
        printArray(arr);
        println();
    }
    public static void printlnYESNO(boolean b){
        printYESNO(b);
        println();
    }
    public static void printlnYesNo(boolean b){
        printYesNo(b);
        println();
    }
    public static void printlnyesno(boolean b){
        printyesno(b);
        println();
    }
    public static void printlnReject(){
        printReject();
        println();
    }
}
