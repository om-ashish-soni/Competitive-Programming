// problem link : https://leetcode.com/problems/next-greater-element-ii/
// solution : below code

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int MIN=-(1e9)-1;
        vector<int> v(nums.size(),MIN);
        stack<int> stk;
        for(int i=nums.size()-1;i>=0;i--){
            if(v[i]==MIN){
                while(stk.size()>0){
                    int top=stk.top();
                    if(nums[i]<top){
                        v[i]=top;
                        break;
                    }
                    stk.pop();
                }
            }
            stk.push(nums[i]);
        }
        queue<int> q;
        for(int i=0;i<nums.size();i++){
            q.push(nums[i]);
        }
        for(int i=nums.size()-1;i>=0;i--){
            if(v[i]==MIN){
                while(q.size()>0){
                    int top=q.front();
                    if(nums[i]<top){
                        v[i]=top;
                        break;
                    }
                    q.pop();
                }
            }
        }
        for(auto &num:v) if(num==MIN) num=-1;
        return v;
    }
    
};
