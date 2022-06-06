// problem link : https://codeforces.com/problemset/problem/1676/H1(easy version)
// problem link : https://codeforces.com/problemset/problem/1676/H2(hard version)
// solution : single solution works for both versions of the problem , below code


void merge(int *a,int l,int mid,int r,int & ctr){
	int lz=mid-l+1,rz=r-mid;
	int left[lz];F(i,0,lz) left[i]=a[l+i];
	int right[rz];F(i,0,rz) right[i]=a[mid+i+1];
	int li=0,ri=0;
	int index=l;
	// cout<<"left : "<<endl;
	// cout<<"l : "<<l<<" to "<<"mid : "<<mid<<endl;
	// println(left,lz);

	// cout<<"right : "<<endl;
	// cout<<"mid+1 : "<<mid+1<<" to "<<"r : "<<r<<endl;
	// println(right,rz);

	while(li<lz && ri<rz){
		if(left[li]<right[ri]){
			a[index]=left[li];
			li++;
		}else{
			ctr+=lz-li;
			// cout<<"for : "<<left[li]<<" vs "<<right[ri]<<" "<<" inc "<<lz-li<<endl;
			a[index]=right[ri];
			ri++;
		}
		index++;
	}
	while(li<lz){
		a[index]=left[li];
		li++;
		index++;
	}

	while(ri<rz){
		a[index]=right[ri];
		ri++;
		index++;
	}
	// cout<<"ultimate : a "<<endl;
	// F(i,l,r+1) cout<<a[i]<<" ";
	// cout<<endl;
}
int stop=0;
void mergeSort(int *a,int l,int r,int & ctr){
	if(l>=r) return;
	// cout<<l<<" "<<r<<endl;
	int mid=(l+r)/2;
	mergeSort(a,l,mid,ctr);
	mergeSort(a,mid+1,r,ctr);
	merge(a,l,mid,r,ctr);
}
void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int a[n];
	read(a,n);
	int ctr=0;
	// println(a,n);
	mergeSort(a,0,n-1,ctr);
	println(ctr);	
}
