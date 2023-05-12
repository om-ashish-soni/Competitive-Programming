#include <stdio.h>
#include<math.h>
int main1(void) {
    int n,m;
    scanf("%d %d",&n,&m);
    int mn=10000;
    
    if(n>m) mn=m;
    else mn=n;
    if(mn%2==0) printf("Kshitij");
    else printf("Rohan");
    printf("\n");
	return 0;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) main1();
}

