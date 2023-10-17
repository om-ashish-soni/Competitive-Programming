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
		BIT=*new vector<int>(n,0);
		BIT[0]=arr[0];
		for(int i=1;i<n;i++){
			this->update(i,arr[i]);
		}
	}
	fenwickTree(vector<int>&v){
		this->n=v.size();
		BIT=*new vector<int>(n,0);
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





class InversionCounter{
public:
    vector<int> arr;
    int n;
    int ctr=0;

    InversionCounter(vector<int> & v){
        this->arr=v;
        this->n=arr.size();
        this->ctr=0;
        process();
    }
    void process(){
        startCounting();
    }
    void startCounting(){
        int len=n+10;
        fenwickTree *fnt=new fenwickTree(len);
        CordinateCompressor *cc=new CordinateCompressor(arr);
        this->ctr=0;
        for(auto elem:arr){
            int key=cc->compress(elem);
            int diff=(fnt->get(len-1)-fnt->get(key));
            this->ctr+=diff;
            fnt->update(key,1LL);
        }
        delete cc;
        delete fnt;
    }
    int getCount(){
        return ctr;
    }
    static void how_to_use(){
        vector<int> arr={100,10,10,10,10};
        InversionCounter *ic=new InversionCounter(arr);
        int inversion=ic->getCount();
        cout<<"inversion : "<<inversion<<endl;
        delete ic;
    }
};
