class Solution {
public:
    void maxSubArray(vector<int>& v,int memo[],int &mx,int i=0){
        if(i==v.size()){ memo[i]=0; return;}
        maxSubArray(v,memo,mx,i+1);
        memo[i]=max(0,memo[i+1]+v[i]);
        mx=max(mx,memo[i]);
    }
    int maxSubArray(vector<int>& nums) {
        int *memo=(int *) calloc(nums.size()+1,sizeof(int));
        int mx=0,mn=INT_MIN;
        mn=*max_element(nums.begin(),nums.end());
        if(mn<1) return mn;
        maxSubArray(nums,memo,mx);
        if(mx==0 && mn<0) mx=mn;
        return mx;
    }
};