// problem link : https://leetcode.com/problems/next-greater-element-i/
// solution : below code

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> hash;
        for(int i=0;i<nums1.size();i++) hash[nums1[i]]=i;
        vector<int> v(nums1.size(),-1);
        stack<int> stk;
        for(int i=nums2.size()-1;i>=0;i--){
            while(stk.size()>0){
                int top=stk.top();
                if(nums2[i]<top){
                    if(hash.count(nums2[i])){
                        int index=hash[nums2[i]];
                        v[index]=top;
                        break;
                    }
                }
                stk.pop();
            }
            stk.push(nums2[i]);
        }
        return v;
    }
};
