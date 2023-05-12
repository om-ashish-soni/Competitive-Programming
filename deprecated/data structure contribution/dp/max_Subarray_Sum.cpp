class Solution {
public:
    void maxSubArray(vector<int>& v,vector<int>& memo,int &mx,int &mn,int i=0){
        if(i==v.size()){ memo[i]=0; return;}
        maxSubArray(v,memo,mx,mn,i+1);
        mn=max(mn,v[i]);
        memo[i]=max(0,memo[i+1]+v[i]);
        mx=max(mx,memo[i]);;
        for(int j=0;j<=v.size();j++){
            if(memo[j] < 0) mx=max(mx,memo[i]-memo[j]);
        }
        return;
    }
    int maxSubArray(vector<int>& nums) {
        vector<int> memo(nums.size()+1);
        int mx=0,mn=INT_MIN;
        maxSubArray(nums,memo,mx,mn);
        if(mx==0 && mn<0) mx=mn;
        // cout<<mx<<" "<<mn<<endl;
        return mx;
    }
};