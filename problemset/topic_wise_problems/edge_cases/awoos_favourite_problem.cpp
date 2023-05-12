// problem link : https://codeforces.com/problemset/problem/1697/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
        

    int n;
    read(n);
    string a,b;
    read(a,b);
    map<int,int> mp1,mp2;
    int last=-1;
    int a_i=-1,b_i=-1,c_i=-1,ab=-1,bc=-1;
    vi pend_a,pend_b;
    F(i,0,n){
        // cout<<pend_a.size()<<" , "<<pend_b.size()<<endl;
        if(a[i]=='a' && b[i]=='c'){
            YESNO1(false);
            return;
        }
        if(a[i]=='c' && b[i]=='a'){
            YESNO1(false);
            return;
        }

        if(a[i]=='a' && b[i]=='b'){
            pend_a.pb(i);
        }
        if(a[i]=='b' && b[i]=='c'){
            pend_b.pb(i);
        }
        if(a[i]=='b'){
            
            pend_a.clear();
        }
        if(a[i]=='c'){
            
            if(pend_a.size()>0){
                YESNO1(false);
                return;
            }
            pend_b.clear();
        }
        if(a[i]=='a'){
            
            if(pend_b.size()>0){
                YESNO1(false);
                return;
            }
        }
    }
    // cout<<pend_a.size()<<" , "<<pend_b.size()<<endl;
    if(pend_a.size()>0 || pend_b.size()>0){
        YESNO1(false);
        return;
    }
    F(i,0,n){
        mp1[a[i]]++;
        mp2[b[i]]++;

        if(a[i]=='b' && b[i]=='a'){
            if(c_i>=ab){
                YESNO1(false);
                return;
            }
        }
        if(a[i]=='c' && b[i]=='b'){
            if(a_i>=bc){
                YESNO1(false);
                return;
            }
        }
        if(a[i]==b[i]){
            if(mp1.size()==1 && mp2.size()==1){
                mp1.clear();
                mp2.clear();
                a_i=-1;
                b_i=-1;
                c_i=-1;
                ab=-1;
                bc=-1;
            }
        }
        
        if(mp1.size()==2 && mp2.size()==2){
            if(mp1.count('a') && mp1.count('b')){
                if(mp2.count('a') && mp2.count('b')){
                    if(mp1['a']==mp2['a'] && mp1['b']==mp2['b']){
                        mp1.clear();
                        mp2.clear();
                        a_i=-1;
                        b_i=-1;
                        c_i=-1;
                        ab=-1;
                        bc=-1;
                    }
                }else if(mp2.count('c')){
                    YESNO1(false);
                    return;
                }
            }
            if(mp1.count('c') && mp1.count('b')){
                if(mp2.count('c') && mp2.count('b')){
                    if(mp1['c']==mp2['c'] && mp1['b']==mp2['b']){
                        mp1.clear();
                        mp2.clear();
                        a_i=-1;
                        b_i=-1;
                        c_i=-1;
                        ab=-1;
                        bc=-1;
                    }
                }else if(mp2.count('a')){
                    YESNO1(false);
                    return;
                }   
            }
        }
        if(mp1.size()==3 || mp2.size()==3){
            YESNO1(false);
            return;
        }
        if(a[i]=='a' ) a_i=i;
        else if(a[i]=='b' ) b_i=i;
        else if(a[i]=='c') c_i=i;
        if(a[i]=='a' && b[i]=='b') ab=i;
        if(a[i]=='b' && b[i]=='c') bc=i;
    }
    // printmap(mp1);
    // printmap(mp2);
    if(mp1.size()==0 && mp2.size()==0){
        YESNO1(true);
    }else{
        YESNO1(false);
    }
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
