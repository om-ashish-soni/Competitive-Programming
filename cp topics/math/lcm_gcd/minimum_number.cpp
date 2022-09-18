// problem link : https://practice.geeksforgeeks.org/contest/interview-series-67/problems/#
// solution : below code

class Solution{
public:
    int minimumNumber(int n,vector<int> &arr){
        int hcf=0;
        FEACH(num,arr){
            hcf=GCD(hcf,num);            
        }
        return hcf;
    }
};
