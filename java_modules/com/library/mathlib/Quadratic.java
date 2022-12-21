package com.library.mathlib;

public class Quadratic{
    public static double[] solve(int a,int b,int c){
        double dr=Math.sqrt(b*b-4*a*c);
        double[] roots={
                (-b + dr )/ 2 * a,
                (-b - dr )/ 2 * a
        };
        return roots;
    }
}