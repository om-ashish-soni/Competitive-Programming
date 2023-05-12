class MatrixExp{
	public : 
	int n;
	vector<vector<int>>& mat;
	MatrixExp(int N,vector<vector<int>> &vmat):n(N),mat(vmat){}
	MatrixExp(int N):n(N),mat(*new vector<vector<int>>{{1,1},{1,0}}){}
	void print(){
		for(auto &row:mat){
			for(auto elem:row) cout<<elem<<" ";cout<<endl;
		}
	}
};
