// problem link : https://leetcode.com/problems/binary-trees-with-factors/
// solution : below code

class Solution {
    int mod=(int)(1e9+7);
    public int numFactoredBinaryTrees(int[] arr) {
        Arrays.sort(arr);
        int n=arr.length;
        ArrayList<Long> dp=new ArrayList<Long>(n);
        Map<Integer, Integer> hm
            = new HashMap<Integer, Integer>();
        for(int i=0;i<n;i++){
            long curr=1;
            for(int j=0;j<i;j++){
                if(arr[i]%arr[j]==0){
                    int first=arr[j];
                    int second=arr[i]/arr[j];
                    if(hm.containsKey(first) && hm.containsKey(second)){
                        int firstKey=hm.get(first);
                        int secondKey=hm.get(second);
                        curr+=((dp.get(firstKey)%mod)*(dp.get(secondKey)%mod))%mod;
                    }
                }
            }
            dp.add(curr);
            hm.put(arr[i],i);
        }
        long ans=0;
        for(int i=0;i<n;i++){
            ans=(ans%mod + dp.get(i)%mod)%mod;
        }
        return (int)ans;
    }
}
