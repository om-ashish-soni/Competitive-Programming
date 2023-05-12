// Problem Link : https://www.codechef.com/problems/BINTREE
// Problem Type: Data structure(binary tree) 
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int32_t main()
{

    int numberoftestcases = 1;
    // cin >> numberoftestcases;
    int t = 1;
    while (numberoftestcases--)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int first, second;
            cin >> first >> second;
            stack<int> vF, vS;
            unordered_map<int, bool> hashF, hashS;
            while (first > 0)
            {
                vF.push(first);
                hashF[first] = vF.size();
                first /= 2;
            }
            while (second > 0)
            {
                vS.push(second);
                hashS[second] = vS.size();
                second /= 2;
            }
            long long total = 0;
            int match=0;

            while(!vF.empty() and !vS.empty()){
                auto fTop=vF.top();
                auto sTop=vS.top();
                if(fTop!=sTop){
                    break;
                }
                vS.pop();
                vF.pop();
                match++;
            }
            total=vF.size()+vS.size();
            cout<<total<<endl;
        }
    }
    return 0;
}
