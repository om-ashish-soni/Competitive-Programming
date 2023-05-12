#include<bits/stdc++.h>
#define mat vector<vector<int>>
using namespace std;
namespace ModuloArithmetic{
    vector<int> extendedGcd(int a,int b){
        int r1(a),r2(b),r(0),s1(1),s2(0),s(0),t1(0),t2(1),t(0);
        int q=0;
        while(r2 != 0){
            q=r1/r2;
            r=r1-q*r2;
            r1=r2;
            r2=r;
            
            s=s1-q*s2;
            s1=s2;
            s2=s;
            
            t=t1-q*t2;
            t1=t2;
            t2=t;
        }
        s=s1;
        t=t1;
        r=r1;
        return {s,t,r};
    }
    int modAdd(int a,int b,int mod){
        return (a%mod + b%mod + mod)%mod;
    }
    int modSub(int a,int b,int mod){
        return (a%mod - b%mod + mod)%mod;
    }
    int modMul(int a,int b,int mod){
        return ((a%mod)*(b%mod))%mod;
    }
    int inverse(int a,int mod){
        vector<int> v=extendedGcd(mod,a);
        if(v.back() != 1) return -1;
        return modAdd(v[1],mod,mod);
    }
    int modDiv(int a,int b,int mod){
        int inv=inverse(b,mod);
        return modMul(a,inv,mod);
    }
}

namespace Matrix{
    using namespace ModuloArithmetic;
        
    void transpose(mat & mat1){
        int n=mat1.size();
        int m=mat1.front().size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                swap(mat1[i][j],mat1[j][i]);
            }
        }
        return;
    }
    void print(mat & m){
        for(auto & row:m){
            for(auto & elem:row) cout<<elem<<" ";cout<<endl;
        }
    }
    int det(mat mat1){
        int n=mat1.size();
        int m=mat1.front().size();
        if(n != m){
            cout<<"matrix is not square matrix"<<endl;
            return 0;
        }
        if(n==1){
            return mat1[0][0];
        }
        int value=0;
        int sign=1;
        for(int j=0;j<n;j++){
            int coef=mat1[0][j];
            mat submat1;
            for(int i=1;i<n;i++){
                vector<int> row;
                for(int k=0;k<n;k++){
                    if(j != k) row.push_back(mat1[i][k]);
                }
                submat1.push_back(row);
            }
            
            int subval=det(submat1);
            // cout<<"submat1 : "<<endl;
            // print(submat1);
            // cout<<"value of submat1 : "<<subval<<endl;
            value+=sign*coef*subval;
            sign*=-1;
            
        }
        // cout<<"==================  "<<endl;
        // print(mat1);
        // cout<<"value(mat1): "<<value<<endl;
        return value;
    } 
    mat cofactor(mat mat1){
        int n=mat1.size();
        mat cof=mat1;
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
                // int sign=((i+j)&1)?(-1):(1);
        //         cof[i][j]=sign*mat1[i][j];
        //     }
        // }
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) cof[i][j]=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int sign=((i+j)&1)?(-1):(1);
                int coefficient=mat1[i][j];
                mat submat1;
                for(int i1=0;i1<n;i1++){
                    if(i1==i) continue;
                    vector<int> row;
                    for(int j1=0;j1<n;j1++){
                        if(j1==j) continue;
                        row.push_back(mat1[i1][j1]);
                    }
                    submat1.push_back(row);
                }
                // cout<<"submat1 in cof : "<<coefficient<<endl;
                // print(submat1);
                int subval=det(submat1);
                // cout<<"subval : "<<subval<<endl;
                cof[i][j]=(sign * subval);
            }
        }
        return cof;
    }
    mat inversemat(mat mat1){
        
        const int mod=26;
        int value=det(mat1);
        mat cof=cofactor(mat1);
        transpose(cof);
        // print(cof);
        mat & inv=cof;
        int n=cof.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                inv[i][j]=modDiv(cof[i][j],value,mod);
                inv[i][j]=modAdd(inv[i][j],mod,mod);
            }
        }
        return inv;
    }
    mat multiplymat(mat & mat1,mat & mat2){
        int n1=mat1.size();
        int m1=mat1.front().size();
        int n2=mat2.size();
        int m2=mat2.front().size();
        
        if(m1 != n2){
            cout<<"dimension mismatch : "<<endl;
        }
        mat mat3(n1,vector<int>(m2,0));
        for(int i=0;i<n1;i++){
            for(int k=0;k<m1;k++){
                for(int j=0;j<m2;j++){
                    mat3[i][j]+=mat1[i][k]*mat2[k][j];                    
                }
            }
        }
        return mat3;
    }
    void refinemat(mat & mat1,int mod){
        for(auto & row:mat1){
            for(auto & elem:row){
                elem=modAdd(elem,mod,mod);
            }
        }
        return;
    }
}


namespace HillCipher{
    using namespace Matrix;
    using namespace ModuloArithmetic;
    const int mod=26;
    mat encrypt(mat mat1,mat mat2){
        mat mat3=multiplymat(mat1,mat2);
        refinemat(mat3,mod);
        return mat3;
    }
    mat decrypt(mat mat1,mat mat2){
        mat mat3=multiplymat(mat1,mat2);
        refinemat(mat3,mod);
        return mat3;
    }
};
using namespace Matrix;
using namespace ModuloArithmetic;
using namespace HillCipher;
int main(){
    const int mod=26;
    
   
    // encryption
    mat key1={
        {3,10,20},
        {20,9,17},
        {9,4,17}
    };
    mat mes={
        {0,19,19},
        {0,2,10},
        {8,18,19},
        {14,13,8},
        {6,7,19}
    };
    mat enc=encrypt(mes,key1);
    cout<<"enc : "<<endl;
    print(enc);
    
    //decryption
    mat key2=inversemat(key1);
    mat dec=decrypt(enc,key2);
    cout<<"dec : "<<endl;
    print(dec);
        
    // mat mat1={
    //     {3,10,20},
    //     {20,9,17},
    //     {9,4,17}
    // };
    // mat mat2=inversemat(mat1);
    // print(mat2);

    
    return 0;
}