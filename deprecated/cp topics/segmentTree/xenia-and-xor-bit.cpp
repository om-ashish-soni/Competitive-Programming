problem link : https://codeforces.com/contest/339/problem/D
Solution : below code
void segBuild(vector<int>&seg,vector<int>&des,int n){
	int domain,start,bit;
	domain=n;start=domain-1;bit=1;
    while(domain>0){
	    
    	for(int index=start;index<start+domain;index++){
    		if(bit==1){
    			seg[index]=(seg[(2*index) + 1] | seg[(2*index) + 2]);
    		}else{
    			seg[index]=(seg[(2*index) + 1] xor seg[(2*index) + 2]);
    		}
    		des[index]=bit;
    	}

        bit=(bit^1);
    	domain=domain/2;start=domain-1;
    }
}
void segUpdate(vector<int>&seg,vector<int>&des,int pos,int val){
	int domain=pow(2,(1+floor(log2(pos))));pos-=1;
    int mypos=pos+ seg.size()/2;
    seg[mypos]=val;
    while( mypos>0){
    	mypos=(mypos-1)/2;
        if(des[mypos]==1) 
            seg[mypos]=(seg[(2*mypos) + 1] | seg[(2*mypos) + 2]);
        else
            seg[mypos]=(seg[(2*mypos) + 1] xor seg[(2*mypos) + 2]);

    }
        
}
void solve(){
	int n,q,x;
	cin>>n>>q;
	int sz=pow(2,n);
	int lst[sz];
    scan(lst,sz);
    x=sz;
    vector<int> seg(2*x-1,0),des(2*x-1,0);
    for(int i=x-1,index=0;i<x-1+sz;i++,index++){
    	seg[i]=lst[index];
    }
    segBuild(seg,des,x/2);
    // print(seg);
    for(int i=0;i<q;i++){
    	int pos,val;cin>>pos>>val;
        segUpdate(seg,des,pos,val);
        cout<<seg[0]<<endl;
    }
       	

}
