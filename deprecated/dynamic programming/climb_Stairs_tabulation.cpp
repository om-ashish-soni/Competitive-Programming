class Solution {
public:
    int climbStairs(int n) {
        vector<int> table(n+2,0);
        table[0]=1;
        for(int i=0;i<n;i++){
            table[i+1]+=table[i];
            table[i+2]+=table[i];
        }
        return table[n];
    }
};
//alternate way using array

class Solution1 {
public:
    int climbStairs(int n) {
        int *table=(int *)calloc(n+2,sizeof(int));
        table[0]=1;
        for(int i=0;i<n;i++){
            table[i+1]+=table[i];
            table[i+2]+=table[i];
        }
        return table[n];
    }
};
