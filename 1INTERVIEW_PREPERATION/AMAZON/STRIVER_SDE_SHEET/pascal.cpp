// problem link : https://www.codingninjas.com/codestudio/problems/1089580?topList=striver-sde-sheet-problems&utm_source=striver&utm_medium=website&leftPanelTab=1
// solution : below code

#include <bits/stdc++.h> 
vector<vector<long long int>> printPascal(int n) 
{
  // Write your code here.
    vector<vector<long long>> v;
    vector<long long> row;
    row.push_back(1);
    v.push_back(row);
    for(int k=1;k<n;k++){
        row.clear();
        row.push_back(1);
        vector<long long> & prev=v.back();
        for(int i=1;i<prev.size();i++){
            row.push_back(prev[i]+prev[i-1]);
        }
        row.push_back(1);
        v.push_back(row);
    }
    return v;
}
