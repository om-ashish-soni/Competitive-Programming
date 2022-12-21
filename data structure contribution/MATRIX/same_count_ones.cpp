// problem link : https://codeforces.com/problemset/problem/1774/D
// solution : below code

    void solve(int t){
        //shree ganeshay namah
        // println("shree ganeshay namah");
        // println("shreepad rajam sharanam prapadhye");
        int n,m;
        read(n,m);
        vvi v(n,vi(m));
        readm(v);

        vvi zeros(m);
        int sm=0;
        vi rone(n,0);
        F(i,0,n){
            F(j,0,m){
                if(v[i][j]==1) rone[i]++;
            }
            sm+=rone[i];
        }

        
        if(sm%n != 0) return reject();
        int mean=sm/n;
        vvi op;
        F(j,0,m){
            vpii ones;
            vpii zeros;
            F(i,0,n){
                if(v[i][j]==1){
                    if(rone[i]>mean) ones.pb({rone[i],i});
                }
                else{
                    if(rone[i]<mean) zeros.pb({rone[i],i});
                }
            }
            SORT(ones);
            REVERSE(ones);
            SORT(zeros);
            int oz=ones.size();
            int zz=zeros.size();
            int sz=min(oz,zz);
            F(i,0,sz){
                pii pone=ones[i];
                pii pzero=zeros[i];
                if(pone.first<=pzero.first) break;
                rone[pone.second]--;
                rone[pzero.second]++;
                op.pb({pone.second+1,pzero.second+1,j+1});
            }
        }
        F(i,0,n){
            if(rone[i] != mean) return reject();
        }
        int oz=op.size();
        println(oz);
        FEACH(row,op){
            printv(row);
        }


        // println("shree ganeshay namah");
        // println("shreepad rajam sharanam prapadhye");

    }   
