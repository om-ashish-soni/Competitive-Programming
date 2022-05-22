// problem link : https://leetcode.com/contest/weekly-contest-294/problems/maximum-bags-with-full-capacity-of-rocks/
// solution : below code

#define pii pair<int,int>
#define vpii vector<pii>
class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        priority_queue<pii,vpii,greater<pii>> pq;
        int k=additionalRocks;
        int n=capacity.size();
        for(int i=0;i<n;i++){
            capacity[i]-=rocks[i];
            pq.push({capacity[i],i});
        }
        while(k>0 && pq.size()>0){
            pii top=pq.top();pq.pop();
            int i=top.second;
            int mn=min(capacity[i],k);
            k-=mn;
            capacity[i]-=mn;
        }
        int ctr=0;
        for(int i=0;i<n;i++) if(capacity[i]==0) ctr++;
        return ctr;
    }
};
