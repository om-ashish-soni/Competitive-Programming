// problem link : https://codeforces.com/problemset/problem/1553/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    string s,p;
    read(s,p);
    int sz=s.size();
    int pz=p.size();

    vs v(sz);
    string carry="";
    F(i,0,sz){
        v[i]=carry;
        REVERSE(v[i]);
        carry+=s[i];
        // cout<<i<<" : "<<v[i]<<endl;
    }
    int found1=s.find(p);
    if(found1>=0 && found1<sz){
        YESNO1(true);
        return;
    }
    string rev=s;
    REVERSE(rev);
    int found2=rev.find(p);
    if(found2>=0 && found2<sz){
        YESNO1(true);
        return;
    }

    string key="";
    while(key.size()<pz){
        int index=key.size();
        // cout<<"key : "<<key<<endl;
        int found=s.find(key);
        while(found>=0 && found<sz){
            int pos=found+key.size()-1;
            if(pos>=0 && pos<sz){
                // cout<<"pos : "<<pos<<endl;
                string text=v[pos];
                // cout<<"text : "<<text<<" , residue : "<<p.substr(index)<<endl;
                if(text.find(p.substr(index)) == 0){
                    YESNO1(true);
                    return;
                }
            }
            found=s.find(key,found+1);
        }
        
        key+=p[index];
    }
    YESNO1(false);
    return;
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
