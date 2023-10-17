class CordinateCompressor{
public:
    map<int,int> cord;
    vector<int> reverseCord;
    vector<int> arr;
    int n;
    CordinateCompressor(vector<int> & arr){
        this->arr=arr;
        this->n=this->arr.size();
        this->reverseCord.assign(n+10,-1);
        startCompressor();
    }
    void startCompressor(){
        SORT(arr);
        int key=1;
        for(auto& val:arr){
            if(cord.count(val)==0){
                cord[val]=key;
                reverseCord[key]=val;
                key++;    
            }
        }
    }
    int compress(int num){
        if(cord.count(num)==0) return -1;
        return cord[num];
    }
    int decompress(int num){
        return reverseCord[num];
    }
    static void how_to_use(){
        // println("shree ganeshay namah");
        vector<int> arr={100,10,52,83,10};
        int len=arr.size();
        CordinateCompressor * cc=new CordinateCompressor(arr);
        vector<int> compressed(len),decompressed(len);
        for(int i=0;i<len;i++){
            compressed[i]=cc->compress(arr[i]);
            decompressed[i]=cc->decompress(compressed[i]);
            cout<<"element : "<<arr[i]<<" : ";
            cout<<compressed[i]<<" , "<<decompressed[i]<<endl;
        }
        
        delete cc;
    }
};
