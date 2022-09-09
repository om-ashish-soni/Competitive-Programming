// problem link : https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
// solution : below code

class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        vector<pair<int,int>> v;
        for(auto & row:properties){
            v.push_back({row[0],row[1]});
        }
        sort(v.begin(),v.end());
        int sz=v.size();
        vector<int> suff(sz,0);
        suff[sz-1]=v[sz-1].second;
        for(int i=sz-2;i>=0;i--){
            suff[i]=max(suff[i+1],v[i].second);
        }
        int ctr=0;
        for(int i=0;i<sz;i++){
            pair<int,int> pr={v[i].first+1,v[i].second+1};
            int index=lower_bound(v.begin(),v.end(),pr)-v.begin();
            if(index<sz){
                if(suff[index]>v[i].second){
                    ctr++;
                    // cout<<i<<" : "<<"{"<<v[i].first<<","<<v[i].second<<"} "<<suff[index]<<endl;
                }
            }
        }
        return ctr;
    }
};
