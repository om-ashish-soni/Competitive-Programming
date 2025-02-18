struct hasher{
    int n, _k, _p;
    vector<int> powk,base;

    void init(string s,int k,int p){
        _k = k, _p = p;
        n = s.length();
        powk.resize(n+1);
        base.resize(n+1);
        // precompute
        base[0] = 0;
        powk[0] = 1;
        for(int i=0;i<n;i++){
            int num = (s[i]-'a'+1 )%p;
            base[i+1] = (1LL *base[i] * k + num)%p;
            powk[i+1] = (1LL* k * powk[i]) %p;
        }
    }  

    int gethash(int l,int r){ // 0 index
        int ans = (base[r+1] - 1LL *base[l]*powk[(r-l+1)])%_p;
        return (ans+_p)%_p;
    }

    //This Function is just for demo
    static void How_To_Use_For_Double_Hash(){
        string s;
        hasher hasha,hashb;
        hasha.init(s,37,1000000021);
        hashb.init(s,39,1000000009);

        //Demo for Number of unique substring 
        int n=s.size();

        set<pair<int,int>>st;
        
        for(int i=0;i<n;i++){

            for(int j=0;j<n;j++){
                
                int val_a=hasha.gethash(i,j);
                int val_b=hashb.gethash(i,j);

                //here combinaction of val_a,val_b should be unique 
                st.insert(make_pair(val_a,val_b));
            }
        }

        int total_unique_substrings=st.size();

        /*
        Probability of collision 
        for double hash = Number of time string access (Gethash used)/p1*p2;

        Probability of collision 
        for single hash = Number of time string access (Gethash used)/p1;
        */
    }
};
