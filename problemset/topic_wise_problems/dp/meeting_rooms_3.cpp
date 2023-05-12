// problem link : https://leetcode.com/problems/meeting-rooms-iii/description/
// solution : below code

class Solution {
public:
    #define ll long long
    int mostBooked(int n, vector<vector<int>>& meetings) {
        priority_queue<pair<ll,ll>> pq;
        // for(int i=0;i<n;i++){
        //     pq.push({-0,-i});
        // }
        sort(meetings.begin(),meetings.end());
        vector<ll> v(n,0);
        vector<ll> start(n,0);
        for(auto & meet:meetings){
            ll l=meet[0];
            ll r=meet[1];
            ll delta=r-l;
            int min_index=0;
            bool done=false;
            for(int i=0;i<n;i++){
                int st=start[i];
                if(start[i]<=l){
                    min_index=i;
                    done=true;
                    break;
                }else{
                    if(start[i]<start[min_index]){
                        min_index=i;
                    }
                }
            }
            start[min_index]=max(start[min_index],l)+delta;
            v[min_index]++;
        }
        int mx_index=0;
        for(int i=0;i<n;i++){
            // cout<<v[i]<<" ";
            if(v[mx_index]<v[i]){
                mx_index=i;
            }
        }
        return mx_index;
    }
};