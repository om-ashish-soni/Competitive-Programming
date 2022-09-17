// problem link : https://codeforces.com/problemset/problem/1648/A
// solution : below code

void solve(int t){
    //shree ganeshay namah  
        

    int n;
    read(n);
    int m;
    read(m);
    vvi mat(n,vi(m));
    readm(mat);
    unordered_map<int,int> mpr,mpc,rem_r,rem_c;
    unordered_map<int,pii> lastr,lastc;
    int tm=0;
    int sm=0;
    F(i,0,n){
        F(j,0,m){
            rem_r[mat[i][j]]++;
        }
    }
    rem_c=rem_r;
    F(i,0,n){
        map<int,int> mp_future;
        F(j,0,m){
            int num=mat[i][j];
            if(lastr.count(num)){
                pii pr=lastr[num];
                int freq=pr.first;
                int index=pr.second;
                // cout<<"deducting occurance of "<<num<<" : "<<freq<<" times "<<" at "<<index<<endl;
                sm-=freq*rem_r[num]*index;
                lastr.erase(num);
            }
            if(mpr.count(num)){
                sm+=tm*mpr[num];
                // cout<<"adding occurance of : "<<num<<" for "<<tm<<" * "<<mpr[num]<<" times "<<endl;
            }
            mp_future[num]++;
            rem_r[num]--;
        }
        FEACH(pr,mp_future){
            int key=pr.first;
            mpr[key]+=pr.second;
            lastr[key]={pr.second,i};
        }
        mp_future.clear();
        tm++;
    }
    tm=0;
    F(j,0,m){
        map<int,int> mp_future;
        F(i,0,n){
            int num=mat[i][j];
            if(lastc.count(num)){
                pii pr=lastc[num];
                int freq=pr.first;
                int index=pr.second;
                sm-=freq*rem_c[num]*index;
                lastc.erase(num);
            }
            if(mpc.count(num)){
                sm+=tm*mpc[num];
            }
            mp_future[num]++;
            rem_c[num]--;
        }
        FEACH(pr,mp_future){
            int key=pr.first;
            mpc[key]+=pr.second;
            lastc[key]={pr.second,j};
        }
        mp_future.clear();
        tm++;
    }

    println(sm);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
