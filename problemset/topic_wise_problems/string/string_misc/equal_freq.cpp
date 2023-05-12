// problem link : https://codeforces.com/problemset/problem/1781/C
// solution : below code

#define map unordered_map
void solve(int t){
    int n;
    read(n);
    string s;
    read(s);
    vector<int> v(27,0);
    map<char,vi> mp;
    mp.reserve(27);
    for(char c='a';c<='z';c++){
        mp[c]={};
    }
    F(i,0,n){
        char c=s[i];
        int pos=(int)(c-'a');
        v[pos]++;
        mp[c].pb(i);
    }
    SORT(v);
    vi pref=v,suff=v;
    F(i,1,27){
        pref[i]+=pref[i-1];
    }
    FND(i,27-2,0){
        suff[i]+=suff[i+1];
    }
    suff.push_back(0);
    // printv(v);
    // printv(pref);
    // printv(suff);
    vi facts;
    findAllFactors(n,facts);
    int mn_d=1;
    int mn_cost=1e9+10;
    FEACH(d,facts){
        if(d*26<n) continue;
        int index=lower_bound(ALL(v),d)-v.begin();
        // cout<<"d : "<<d<<" , index : "<<index<<endl;
        int right=27-index;
        // cout<<"right : "<<right<<endl;
        int limit=n-(right*d);
        int can_take=(limit/d);
        // cout<<"can_take : "<<can_take<<endl;
        int l_index=max(0LL,index-can_take);
        int r_index=index;
        // cout<<l_index<<" , "<<r_index<<endl;
        int cost=limit-(suff[l_index]-suff[r_index]);
        // cout<<"cost : "<<cost<<endl;
        if(mn_cost>=cost){
            mn_cost=cost;
            mn_d=d;
        }
    }
    cout<<mn_cost<<endl;
    string output="";
    char esc='0';
    F(i,0,n) output.pb(esc);
    string dumping="";
    string use_less="";
    FEACH(pr,mp){
        vi & positions=pr.second;
        int ctr=0;
        if(positions.size()>=mn_d){
            // cout<<"used : "<<pr.first<<endl;
            while(positions.size()>0){
                if(ctr>=mn_d) break;
                int index=positions.back();
                positions.pop_back();
                output[index]=pr.first;
                ctr++;
            }
        }else{
            use_less.pb(pr.first);
        }
        
    }
    
    // cout<<dumping<<endl;
    sort(ALL(use_less),[&](char a,char b){
        if(mp[a].size()==mp[b].size()) return a<b;
        return mp[a].size()>mp[b].size();
    });
    // cout<<use_less<<endl;
    int empos=0;
    F(i,0,n){
        if(output[i]==esc) empos++;
    }
    // cout<<empos%mn_d<<" see"<<endl;
    FEACH(c,use_less){
        vi & positions=mp[c];
        int limit=mn_d;
        // cout<<"c : "<<c<<" , empos : "<<empos<<endl;
        if(empos<=0)  break;
        empos-=mn_d;
        while(positions.size()>0 && limit>0){
            int index=positions.back();
            // cout<<"putting "<<c<<" at "<<index<<endl;
            output[index]=c;
            limit--;
            positions.pop_back();
        }
        while(limit>0){
            dumping.pb(c);
            limit--;
        }
    }
    
    F(i,0,n){
        if(dumping.size()>0 && output[i]==esc){
            char c=dumping.back();
            output[i]=c;
            dumping.pop_back();
        }
    }
    cout<<output<<endl;
}

signed main(){
    FASTIO;
    BOOLALPHA;
    int t=1;
    read(t);//isTakeTestCase
    F(i,1,t+1){
        solve(i);
    }
    printTime();
    return 0;
}   
