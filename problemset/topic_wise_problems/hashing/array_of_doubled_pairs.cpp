// problem link : https://leetcode.com/problems/array-of-doubled-pairs/description/
// solution : below code

class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        map<int,int> mp;
        // for(auto & num:arr){
        //     num=abs(num);
        // }
        sort(arr.begin(),arr.end());
        for(auto & num:arr) mp[num]++;
        for(int i=arr.size()-1;i>=0;i--){
            if(mp.count(arr[i]) && mp[arr[i]]>0){
                cout<<"i : "<<i<<" , arr[i] : "<<arr[i]<<endl;
                if(arr[i]%2) continue;
                int half=arr[i]/2;
                if(mp.count(half) && mp[half]>0){
                    mp[half]--;
                    mp[arr[i]]--;
                }
            }
        }
        for(auto & pr:mp){
            cout<<pr.first<<" , "<<pr.second<<endl;
            if(pr.second>0) return false;
        }
        return true;
    }
};