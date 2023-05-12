// problem link : https://codeforces.com/problemset/problem/1526/C2
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    int a[n];
    read(a,n);
    priority_queue<int> pq;
    int ctr=0;
    int score=0;
    F(i,0,n){
    	if(a[i]>=0){
    		score+=a[i];
    		ctr++;
    		// cout<<"adding : "<<a[i]<<endl;
    	}else{
    		if(score+a[i]<0){
    			if(pq.size()==0) continue;
    			int top=pq.top();
    			if(top>abs(a[i])){
    				// cout<<"removing : "<<-top<<endl;
    				pq.pop();
    				score+=top;
    				score-=abs(a[i]);
    				pq.push(abs(a[i]));
    				// cout<<"adding : "<<a[i]<<endl;
    			}
    		}else{
    			score+=a[i];
    			pq.push(-a[i]);
    			ctr++;
    			// cout<<"adding : "<<a[i]<<endl;
    		}
    	}
    }
    println(ctr);
}   
