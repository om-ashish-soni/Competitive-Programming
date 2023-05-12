// problem link : https://codeforces.com/problemset/problem/1792/D
// solution : below code

#define map unordered_map
void solve(int t){
    int n,m;
    read(n,m);
    vvi v(n,vi(m));
    readm(v);
    map<string,bool> mp;
    FEACH(row,v){
        FEACH(num,row) num--;
    }
    FEACH(row,v){

        vector<int> hashmap(m,-1);
        string s;
        F(i,0,m){
            s.pb('*');
            hashmap[row[i]]=i;
        }
        F(i,0,m){
            int index=hashmap[i];
            s[index]=(char)('0'+i);
            mp[s]=true;
        }
    }
    FEACH(row,v){
        int l=0;
        int r=m-1;
        int mx=0;
        while(l<=r){
            bool flag=(l==r);
            int mid=(l+r)/2;
            string s=encode(row,mid);
            // cout<<"s : "<<s<<" , mid : "<<mid<<endl;
            if(mp.count(s)){
                mx=max(mx,mid+1);
                l=mid+1;
            }else{
                r=mid;
            }
            if(flag) break;
        }
        print(mx);
    }
    println();



}