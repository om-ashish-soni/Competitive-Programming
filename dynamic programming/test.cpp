class Solution {
public:
    int fib(int n,int *memo=NULL) {
        if(n==0 || n==1) return n;
        int *tab=(int *)calloc(n+2,sizeof(int));
        tab[0]=0;
        tab[1]=1;
        for(int i=0;i<n;i++){
            tab[i+1]+=tab[i];
            tab[i+2]+=tab[i];
        }
        return tab[n];
    }
};