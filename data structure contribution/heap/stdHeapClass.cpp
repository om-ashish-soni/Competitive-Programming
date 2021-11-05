class heap{
	private:
		vector<int> arr;
		int len;

	public:
		heap(vector<int> &arr,int len):arr(arr),len(len){
			this->generateHeap();
		}
		void generateHeap(int i=0){
			int left=2*i+1;
			int right = 2*i+2;
			int largest=i;
			if(left<len) generateHeap(left);
			if(right<len) generateHeap(right);
			if(left<len && arr[left]>arr[largest]) largest=left;
			if(right<len && arr[right]>arr[largest])largest=right;
			if(largest!=i){
				swap(arr[largest],arr[i]);
				return generateHeap(largest);
			}
			return;
		}
		void heapify(int i=0){
			int lefet=2*i+1;
			int right=2*i+2;
			int largest=i;
			if(left<len && arr[left]>arr[largest]) largest=left;
			if(right<len && arr[right]>arr[largest]) largest=right;
			if(largest != i){
				swap(arr[largest],arr[i]);
				heapify(largest);
			}
			return;
		}
		void heapifyk(int k=len){
			for(int i=0;i<k;i++){
				len--;
				heapify();
			}

		}
	

};
