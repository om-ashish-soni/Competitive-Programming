package com.library.conversion;

import java.util.ArrayList;

public class Convertor {
    public static  <T extends Number> long[] toLongArray(ArrayList<T> lst){
        return lst.stream().mapToLong((num)->{
            return num.longValue();
        }).toArray();
    }
    public static <T extends Number> int[] toIntArray(ArrayList<T> lst){
        return lst.stream().mapToInt((num)->{
            return num.intValue();
        }).toArray();
    }
    public static char toLowerCase(Character c){
        return c.toString().toLowerCase().toCharArray()[0];
    }
    public static char toUpperCase(Character c){
        return c.toString().toUpperCase().toCharArray()[0];
    }
}
