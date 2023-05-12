#include<bits/stdc++.h>
using namespace std;

class P{
public:
	void abc(){
		cout<<"abc in P"<<endl;
	}
};
class C : public P{
public:
	void abc(int a){
		cout<<"abc in C"<<endl;
	}
};

signed main(){
	P obj=new C();
	obj.abc();
	return 0;
}