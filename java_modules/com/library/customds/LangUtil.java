package com.library.customds;

public class LangUtil {
    public static String vowels="aeiou";
    public static char toLowerCase(Character c){
        return c.toString().toLowerCase().toCharArray()[0];
    }
    public static char toUpperCase(Character c){
        return c.toString().toUpperCase().toCharArray()[0];
    }
    public static boolean isVowel(char c){
        c=toLowerCase(c);
        return vowels.indexOf(c) != -1;
    }
    public static boolean isConsonant(char c){
        return false==isVowel(c);
    }
}
