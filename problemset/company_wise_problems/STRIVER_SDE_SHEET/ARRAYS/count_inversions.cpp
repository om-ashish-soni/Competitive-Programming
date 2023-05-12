// problem link : https://www.codingninjas.com/codestudio/problems/count-inversions_615
// solution : below code

#include <bits/stdc++.h> 
void merge(long long *arr,int l,int mid,int r,long long &ctr){
    int left_size=mid-l+1;
    int right_size=r-mid-1 + 1;
    int left[left_size],right[right_size];
    int li=0,ri=0;
    for(int i=l;i<=mid;i++) left[li++]=arr[i];
    for(int i=mid+1;i<=r;i++) right[ri++]=arr[i];
    li=0;
    ri=0;
    int index=l;
    while(li<left_size && ri<right_size){
        if(left[li]>right[ri]){
            arr[index++]=right[ri++];
        }else{
            ctr+=ri;
            arr[index++]=left[li++];
        }
       
    }
    while(li<left_size){
        ctr+=ri;
        arr[index++]=left[li++];
    }
    while(ri<right_size){
        arr[index++]=right[ri++];
    }
//     for(int i=l;i<=r;i++){
//         cout<<arr[i]<<" ";
//     }
//     cout<<endl;
}
void mergesort(long long *arr,int l,int r,long long &ctr){
    if(l>=r) return ;
    int mid=(l+r)/2;
    
    mergesort(arr,l,mid,ctr);
    mergesort(arr,mid+1,r,ctr);
    merge(arr,l,mid,r,ctr);
}
long long getInversions(long long *arr, int n){
    long long ctr=0;
    mergesort(arr,0,n-1,ctr);
    return ctr;
}
