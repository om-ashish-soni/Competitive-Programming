// problem link : https://leetcode.com/problems/maximum-score-from-removing-stones/submissions/
// solution : below code
class Solution {
public:
    int maximumScore(int a, int b, int c) {
        int arr[]={a,b,c};
        sort(arr,arr+3);
        if(arr[1]+arr[0]<=arr[2])  return arr[1]+arr[0];
        int score=0;
        score=arr[2];
        int diff=arr[1]-arr[0];
        int rem=arr[2];
        arr[1]-=min(diff,rem);
        rem-=min(diff,rem);
        
        int half=rem/2;
        rem=rem-half;
        arr[0]-=half;
        arr[1]-=rem;
        rem=0;
        score+=min(arr[0],arr[1]);
        cout<<"rem : "<<rem<<" ; arr[0] : "<<arr[0]<<" , arr[1] : "<<arr[1]<<endl;
        return score;
    }
};
