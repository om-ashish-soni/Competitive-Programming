// problem link : https://codeforces.com/problemset/problem/1773/E
// solution : below code

    void solve(int t){
        //shree ganeshay namah
        // println("shree ganeshay namah");
        // println("shreepad rajam sharanam prapadhye");
        int n;
        read(n);
        vvi v(n);
        vi keys;
        map<int,pii> mp;
        F(i,0,n){
            int k;
            read(k); 
            vi & row=v[i];
            row.resize(k);
            readv(row);
            REVERSE(row);
        }
        FEACH(row,v){
            int sz=row.size();
            F(i,0,sz){
                int left=-1;
                int right=-1;
                if(i-1>=0) left=row[i-1];
                if(i+1<sz) right=row[i+1];
                mp[row[i]]={left,right};
                keys.pb(row[i]);
            }
        }
        SORT(keys);
        REVERSE(keys);
        int split=0;
        int merge=0;

        int last=-1;
        FEACH(key,keys){
            // cout<<"key : "<<key<<endl;
            pii pr=mp[key];
            int left=pr.first;
            int right=pr.second;
            // cout<<"left : "<<left<<" , right : "<<right<<endl;
            // cout<<"last : "<<last<<endl;
            if(left != last){
                if(left != -1){
                    // cout<<"splitting : "<<left<<" => "<<key<<endl;
                    split++;
                    mp[left].second=-1;
                    mp[key].first=-1;
                }
                if(last != -1){
                    
                    merge++;
                    int new_tower=mp[last].second;
                    if(new_tower != -1){
                        // cout<<"splitting : "<<last<<" => "<<new_tower<<endl;
                        split++;
                        mp[new_tower].first=-1;
                    }
                    mp[last].second=key;
                    mp[key].first=last;
                    // cout<<"merging : "<<last<<" => "<<key<<endl;
                }
            }
                
            last=key;
        }
        println(split,merge);

        // println("shree ganeshay namah");
        // println("shreepad rajam sharanam prapadhye");

    }   
