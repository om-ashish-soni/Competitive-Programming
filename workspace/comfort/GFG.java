//{ Driver Code Starts
//Initial Template for Java

import java.io.*;
import java.util.*;

public class GFG{
    public static void main(String args[])throws IOException
    {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        while(t-- > 0){
            int N = Integer.parseInt(in.readLine());
            String S = in.readLine();
            
            Solution ob = new Solution();
            System.out.println(ob.countWays(N, S));
        }
    }
}
// } Driver Code Ends


//User function Template for Java

class Solution{
    // private static Map<int[],Integer> mp=new TreeMap<>(
    //     (o1,o2)->{
    //         for(int i=0;i<o1.length;i++){
    //             int comp=Integer.compare(o1[i],o2[i]);
    //             if(comp != 0) return comp;
    //         }
    //         return 0;
    //     }
    // );
    private static int ways(char [] arr,int [][][] dp,int l,int r,int bit){
        if(r==l){
            int myBit=arr[l]-'0';
            if(myBit==bit) return 1;
            return 0;
        }
        if(dp[l][r][bit] != -1) return dp[l][r][bit];
        int sum=0;
        for(int i=l;i<r;i++){
            if(arr[i] != '1' && arr[i] != '0'){
                int [] left=new int[]{0,0};
                int [] right=new int[]{0,0};
                for(int k=0;k<=1;k++){
                    left[k]=ways(arr,dp,l,i-1,k);
                    right[k]=ways(arr,dp,i+1,r,k);
                }
                char sign=arr[i];
                if(sign=='&'){
                    if(bit==1){
                        sum+=left[1]*right[1];
                    }else{
                        sum+=left[0]*right[0];
                        sum+=left[0]*right[1];
                        sum+=left[1]*right[0];
                    }
                }
                else if(sign=='|'){
                    if(bit==1){
                        sum+=left[0]*right[1];
                        sum+=left[1]*right[0];
                        sum+=left[1]*right[1];
                    }else{
                        sum+=left[0]*right[0];
                    }
                }
                else if(sign=='^'){
                    if(bit==1){
                        sum+=left[0]*right[1];
                        sum+=left[1]*right[0];
                    }else{
                        sum+=left[0]*right[0];
                        sum+=left[1]*right[1];
                    }
                }
            }
        }
        dp[l][r][bit]=sum;
        // System.out.println("["+l+","+r+"] : "+" bit : "+bit+ " :: "+sum);
        return sum;
    }
    static int countWays(int N, String S){
        char [] arr=S.toCharArray();
        int n=arr.length;
        for(int i=0;i<n;i++){
            if(arr[i]=='T') arr[i]='1';
            else if(arr[i]=='F') arr[i]='0';
        }
        int [][][] dp=new int[n][][];
        for(int i=0;i<n;i++){
            dp[i]=new int[n][];
            for(int j=0;j<n;j++){
                dp[i][j]=new int[]{-1,-1};
            }
        }
        int ctr=ways(arr,dp,0,n-1,1);
        return ctr;
    }
}