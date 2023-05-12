// problem link : https://codeforces.com/contest/1463/problem/C
// solution : below code

bool isInRange(int l,int r,int val){
	return l<=val and val<=r;
}
void solve(){
	int n;cin>>n;
	pair<int,int> goal={0,0};
	vector<int> tm(n);
	vector<int> pos(n);
	vector<int> act(n+1);
	int sign=1;
	for(int i=0;i<n;i++){
		cin>>tm[i]>>pos[i];
		int time=tm[i];
		if(time>=goal.first){
			// don't ignore command
			// cout<<"followed on time: "<<time<<endl;
			act[i]=goal.second;
			int diff=0;
			int currPos=goal.second;
			int nextPos=pos[i];
			if(nextPos>=currPos){
				diff=nextPos-currPos;
				sign=1;
				goal.first=time+diff;
				goal.second=nextPos;
			}else{
				diff=currPos-nextPos;
				sign=-1;
				goal.first=time+diff;
				goal.second=nextPos;
			}
			
			// cout<<"set : "<<goal.first<<","<<goal.second<<"]"<<endl;
		}
		else{
			//ignore command
			int deltaTime=goal.first-time;
			act[i]=goal.second-(deltaTime*sign);
		}
	}
	act[n]=goal.second;
	int ctr=0;
	for(int i=0;i<n;i++){
		// cout<<" at "<<tm[i]<<" should be on "<<pos[i]<<" but acutally on "<<act[i]<<endl;
		if(isInRange(min(act[i],act[i+1]),max(act[i],act[i+1]),pos[i])) ctr++;
	}
	// cout<<" at "<<"inf"<<" but acutally on "<<act[n]<<endl;
	cout<<ctr<<endl;
}
