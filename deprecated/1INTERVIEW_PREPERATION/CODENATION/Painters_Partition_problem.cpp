// problem link : https://www.codingninjas.com/codestudio/problems/painter-s-partition-problem_1089557?leftPanelTab=1
// solution : below code
// approach : binary search 

int findLargestMinDistance(vector<int> &boards, int k)
{
    long long r=accumulate(boards.begin(),boards.end(),0LL);
    long long l=*max_element(boards.begin(),boards.end());
    int ans=r;
    while(l<=r){
        bool flag=false;
        if(l==r) flag=true;
        int mid=(l+r)/2;
        int ctr=1;
        int curr=0;
        
        for(auto board:boards){
            if(curr+board>mid){
                ctr++;
                curr=board;
            }else{
                curr+=board;
            }
        }
        if(ctr>k){
            l=mid+1;
        }else{
            r=mid;
            ans=min(ans,mid);
        }
        if(flag) break;
    }
    return ans;
}
