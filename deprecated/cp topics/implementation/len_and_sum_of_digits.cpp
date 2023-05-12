// problem link : https://codeforces.com/problemset/problem/489/C
// solution : below code
#include <iostream>
using namespace std;
void reject(){
    cout<<-1<<" "<<-1<<endl;
}
int main() {
    int m,s;cin>>m>>s;
    if(s>9*m){ reject();return 0;}
    if(m==1){
        cout<<s<<" "<<s<<endl;
        return 0;
    }
    if(s<1){ reject();return 0;}
    int front[m];
    int rest[m];
    for(int i=0;i<m;i++){
        int num=min(s,9);
        s-=num;
        front[m-i-1]=num;
        rest[i]=num;
    }
    for(int i=0;i<m;i++){
        if(front[i]>0){
            front[i]--;
            front[0]++;
            break;
        }
    }
    for(int i=0;i<m;i++) cout<<front[i];cout<<" ";
    for(int i=0;i<m;i++) cout<<rest[i];cout<<endl;
    return 0;
}
