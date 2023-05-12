// problem link : https://leetcode.com/problems/find-median-from-data-stream/description/
// solution : below code


// fenwick tree
class fenwickTree{
    vector<int> BIT;
    int n;
    public : 
    fenwickTree(int n){
        this->n=n;
        // BIT=*new vector<int>(n,0);
        BIT.assign(n,0);
    }
    fenwickTree(int *arr,int n){
        
        this->n=n;
        BIT.assign(n,0);
        BIT[0]=arr[0];
        for(int i=1;i<n;i++){
            this->update(i,arr[i]);
        }
    }
    fenwickTree(vector<int>&v){
        this->n=v.size();
        BIT.assign(n,0);
        BIT[0]=v[0];
        for(int i=1;i<n;i++){
            this->update(i,v[i]);
        }
    }
    void update(int index, int delta)
    {
          if(index==0) {BIT[index]+=delta;return;}
          for(; index < n; index += index&-index)

            BIT[index] += delta;
    }
    int get(int index)
    {
         int sum = BIT[0];
         for(; index > 0; index -= index&-index)
            sum += BIT[index];
         return sum;
    }
    void print(){
        for(int i=0;i<n;i++){
            cout<<BIT[i]<<" ";
        }
        cout<<endl;
    }
    
};

class MedianFinder {
public:
    fenwickTree *fnt=NULL;
    int threshold=1e5;
    int sz=2e6+10;
    int ctr=0;
    set<int> s;
    map<int,int> mp;
    MedianFinder() {
        fnt=new fenwickTree(sz+100);
    }
    
    void addNum(int num) {
        num+=threshold;
        ctr++;
        mp[num]=num-threshold;
        s.insert(num);
        fnt->update(num,1);
    }
    
    double findMedian() {
        int l=1;
        int r=sz-1;
        double median=0;
        int half=ctr/2;
        while(l<=r){
            bool flag=(l==r);
            int mid=(l+r)/2;
            int left=(fnt->get(mid-1));
            int right=fnt->get(sz-1)-fnt->get(mid);
            int myfreq=fnt->get(mid)-fnt->get(mid-1);
            int total=left+right+myfreq;
            if(left+myfreq==right){
                auto it1=s.upper_bound(mid);
                int second=*it1;
                it1--;
                int first=*it1;
                first=mp[first];
                second=mp[second];
                median=(first+second)/2.0;
                break;
            }else if((2*left)<total && (2*(left+myfreq))>total){
                int num=mp[mid];
                median=num;
                break;
            }
            else if(left<right){
                l=mid+1;
            }else{
                r=mid;
            }
            if(flag) break;
        }
        return median;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */