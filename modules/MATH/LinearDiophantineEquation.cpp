pair<int,int> extended_gcd(int a,int b){
	if(b==0) return{1,1};
	pair<int,int> pr=extended_gcd(b,a%b);
	return {pr.second,pr.first-(a/b)*pr.second};
}
bool find_any_solution(int a,int b,int c,int &x0,int &y0,int &g){
	pair<int,int> pr=extended_gcd(abs(a),abs(b));
	x0=pr.first;
	y0=pr.second;
	g=x0*abs(a)+y0*abs(b);
	if(c%g) return false;
	x0*=c/g;
	y0*=c/g;
	if(a<0) x0=-x0;
	if(b<0) y0=-y0;
	return true;
}
void lde_solution(int a,int b,int c,int &x,int &y){
	int x,y,g;
	if(find_any_solution(a,b,c,x,y,g)==false){
		cerr<<"no solution exists for lde eq"<<endl;
		exit(0);
	}
	return;
}