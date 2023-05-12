#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

namespace Convertor{
	int toInt(string hexValue){
		int decimalValue=0;
		istringstream ost(hexValue);
		ost >> hex >> decimalValue;
		return decimalValue;
	}
	string toHex(int decimalValue,int len=8){
		string hexValue;
		stringstream st;
		st<<hex<<std::setfill ('0') << std::setw(len)<<decimalValue;
		hexValue=st.str();
		return hexValue;
	}


};
using namespace Convertor;
class DES{
public:
	vector<int> keys;
	vector<int> initialPBox,expansionPBox;
	vector<vector<int>> SBox;
	vector<int> straightPBox;
	DES(){
		this->perform();
		this->generateKeys();
		this->generateInitialPBox();
		this->generateExpansionPBox();
		this->generateSBox();
		this->generateStraightPBox();
	}
	void generateKeys(){
		vector<string> stringKeys={"194CD072DE8C","4568581ABCCE","06EDA4ACF5B5","DA2D032B6EE3","69A629FEC913","C1948E87475E","708AD2DDB3C0","34F822F0C66D","84BB4473DCCC","02765708B5BF","6D5560AF7CA5","C2C1E96A4BF3","99C31397C91F","251B8BC717D0","3330C5D9A36D","181C5D75C66D"};
		for(auto key:stringKeys){
			this->keys.push_back(toInt(key));
		}
	}
	void generateInitialPBox(){
		this->initialPBox= { 57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 , 61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7 , 56 , 48 , 40 , 32 , 24 , 16 , 8 , 0 , 58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52 , 44 , 36 , 28 , 20 , 12 , 4 , 62 , 54 , 46 , 38 , 30 , 22 , 14 , 6 } ;
		
	}
	void generateExpansionPBox(){
		this->expansionPBox= { 31 , 0 , 1 , 2 , 3 , 4 , 3 , 4 , 5 , 6 , 7 , 8 , 7 , 8 , 9 , 10 , 11 , 12 , 11 , 12 , 13 , 14 , 15 , 16 , 15 , 16 , 17 , 18 , 19 , 20 , 19 , 20 , 21 , 22 , 23 , 24 , 23 , 24 , 25 , 26 , 27 , 28 , 27 , 28 , 29 , 30 , 31 , 0 };
		// this->expansionPBox.assign(48,0);
		// for(int i=0;i<48;i++){
		// 	cin>>expansionPBox[i];
		// }
		// cout<<" { ";
		// for(int i=0;i<48;i++){
		// 	cout<<expansionPBox[i]-1<<" , ";
		// }
		// cout<<" } "<<endl;
	}
	void generateSBox(){
        this->SBox={{
        	14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,9,  0,  7,
        	0, 15, 7,  4,  14, 2,  13, 1,  10, 6,12, 11, 9,  5, 3,  8,
          4,  1,  14, 8,  13, 6,  2,11, 15, 12, 9, 7,  3,  10, 5,  0,  
          15, 12, 8,  2,4,  9,  1,  7, 5,  11, 3,  14, 10, 0,  6,  13 },
        { 15, 1,  8,  14, 6,  11, 3, 4,  9,  7,  2,  13, 12,
          0,  5,  10, 3,  13, 4,  7, 15, 2,  8,  14, 12, 0,
          1,  10, 6,  9,  11, 5,  0, 14, 7,  11, 10, 4,  13,
          1,  5,  8,  12, 6,  9,  3, 2,  15, 13, 8,  10, 1,
          3,  15, 4,  2,  11, 6,  7, 12, 0,  5,  14, 9 },
 
        { 10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12,
          7,  11, 4,  2,  8,  13, 7,  0,  9,  3,  4,
          6,  10, 2,  8,  5,  14, 12, 11, 15, 1,  13,
          6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12,
          5,  10, 14, 7,  1,  10, 13, 0,  6,  9,  8,
          7,  4,  15, 14, 3,  11, 5,  2,  12 },
        { 7,  13, 14, 3,  0,  6,  9,  10, 1,  2, 8,  5,  11,
          12, 4,  15, 13, 8,  11, 5,  6,  15, 0, 3,  4,  7,
          2,  12, 1,  10, 14, 9,  10, 6,  9,  0, 12, 11, 7,
          13, 15, 1,  3,  14, 5,  2,  8,  4,  3, 15, 0,  6,
          10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14 },
        { 2,  12, 4, 1,  7,  10, 11, 6, 8,  5,  3,  15, 13,
          0,  14, 9, 14, 11, 2,  12, 4, 7,  13, 1,  5,  0,
          15, 10, 3, 9,  8,  6,  4,  2, 1,  11, 10, 13, 7,
          8,  15, 9, 12, 5,  6,  3,  0, 14, 11, 8,  12, 7,
          1,  14, 2, 13, 6,  15, 0,  9, 10, 4,  5,  3 },
        { 12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3, 4, 14,
          7,  5,  11, 10, 15, 4,  2,  7,  12, 9,  5, 6, 1,
          13, 14, 0,  11, 3,  8,  9,  14, 15, 5,  2, 8, 12,
          3,  7,  0,  4,  10, 1,  13, 11, 6,  4,  3, 2, 12,
          9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8, 13 },
        { 4,  11, 2,  14, 15, 0,  8, 13, 3,  12, 9,  7,  5,
          10, 6,  1,  13, 0,  11, 7, 4,  9,  1,  10, 14, 3,
          5,  12, 2,  15, 8,  6,  1, 4,  11, 13, 12, 3,  7,
          14, 10, 15, 6,  8,  0,  5, 9,  2,  6,  11, 13, 8,
          1,  4,  10, 7,  9,  5,  0, 15, 14, 2,  3,  12 },
        { 13, 2,  8, 4,  6,  15, 11, 1,  10, 9, 3, 14, 5,
          0,  12, 7, 1,  15, 13, 8,  10, 3,  7, 4, 12, 5,
          6,  11, 0, 14, 9,  2,  7,  11, 4,  1, 9, 12, 14,
          2,  0,  6, 10, 13, 15, 3,  5,  8,  2, 1, 14, 7,
          4,  10, 8, 13, 15, 12, 9,  0,  3,  5, 6, 11 }
      };
      
	}
	void generateStraightPBox(){
		this->straightPBox={ 15 , 6 , 19 , 20 , 28 , 11 , 27 , 16 , 0 , 14 , 22 , 25 , 4 , 17 , 30 , 9 , 1 , 7 , 23 , 13 , 31 , 26 , 2 , 8 , 18 , 12 , 29 , 5 , 21 , 10 , 3 , 24 };
	}
	void permute64(bitset<64> & bs,vector<int> & box){
		bitset<64> nextbs;
		for(int i=0;i<64;i++){
			int index=box[i];
			nextbs[i]=bs[index];
		}
		bs=nextbs;
	}
	bitset<48> permute48(bitset<32> & bs,vector<int> & box){
		bitset<48> nextbs;
		for(int i=0;i<48;i++){
			int index=box[i];
			nextbs[i]=bs[index];
		}
		return nextbs;
	}
	bitset<32> permute32(bitset<32> & bs,vector<int> & box){
		// cout<<"initailly bs : "<<bs<<endl;
		bitset<32> nextbs;
		vector<int> nextBsV;
		for(int i=0;i<32;i++){
			int index=box[i];
			// cout<<i<<" <= "<<index<<" bit : "<<bs[31-index]<<endl;
			// nextBsV.push_back(bs[31-index]);
			nextbs[31-i]=bs[31-index];
			// nextbs[i]=bs[index];
		}
		// reverse(nextBsV.begin(),nextBsV.end());
		// cout<<"printing vector : "<<endl;
		// for(auto num:nextBsV) cout<<num;cout<<endl;
		// for(int i=0;i<32;i++){
		// 	nextbs[i]=nextBsV[i];
		// }
		// cout<<"next bs : "<<nextbs<<endl;
		// cout<<"in permute : "<<toHex(nextbs.to_ullong())<<endl;
		return nextbs;
	}
	void perform(){
		// bitset<64> bs(toInt("AB"));
		// cout<<bs.to_ullong()<<endl;
		
	}
	void split(bitset<64> & bits,bitset<32> & leftbits,bitset<32> & rightbits){	
		for(int k=0;k<32;k++){
			leftbits[k]=bits[k+32];
			rightbits[k]=bits[k];
		}
	}
	bitset<32> mixer(bitset<32> & leftbits,bitset<32>& rightbits,int roundKey){
		bitset<48> keybits(roundKey);
		// cout<<"in mixer : "<<endl;
		// cout<<"key : "<<keybits<<endl;
		bitset<32> rightCopy=rightbits;
		bitset<32> leftCopy=leftbits;
		bitset<32> fbs=function(rightbits,keybits);
		// cout<<"fbs : "<<toHex(fbs.to_ullong())<<endl;
		bitset<32> xorrbits=(leftCopy ^ fbs);
		// cout<<xorrbits<<endl;
		return xorrbits;
	}
	bitset<32> function(bitset<32> & rightbits,bitset<48> & keybits){
		bitset<48> rightExpanded=permute48(rightbits,expansionPBox);
		// cout<<"after expansion : "<<toHex(rightExpanded.to_ullong())<<endl;
		bitset<48> xorrbits=(rightExpanded^keybits);
		// cout<<"xorrbits : "<<toHex(xorrbits.to_ullong())<<endl;
		bitset<32> subbs=substitute48(xorrbits);
		// cout<<"after substitution : "<<toHex(subbs.to_ullong())<<endl;
		bitset<32> permbs=permute32(subbs,straightPBox);
		// cout<<"permbs : "<<permbs<<endl;
		return permbs;
	}
	bitset<32> substitute48(bitset<48> bits_bs){
		vector<int> subv;
		bitset<32> subbs;
		vector<int> bits;
		for(int i=0;i<48;i++){
			bits.push_back(bits_bs[i]);
		}
		reverse(bits.begin(),bits.end());
		// cout<<bits.to_string()<<endl;
		for(int i=0;i<8;i++){
			int l=i*6;
			int r=l+5;
			// cout<<"l : "<<l<<" , r : "<<r<<endl;
			int row=2*bits[l]+bits[r];
			int col=8*bits[l+1]+4*bits[l+2]+2*bits[l+3]+bits[l+4];
			// cout<<"bits : ";
			// for(int j=l;j<=r;j++) cout<<bits[j];cout<<endl;
			// for(int j=l;j<=r;j++) cout<<bits[j];cout<<endl;
			int sindex=row*16+col;
			// cout<<"sindex : "<<sindex<<endl;
			int value=SBox[i][sindex];
			// cout<<row<<" "<<col<<" "<<value<<endl;
			bitset<4> valuebs(value);
			// int sl=i*4;
			// int sr=sl+3;
			// cout<<valuebs<<endl;
			// for(int k=0;k<4;k++){
			// 	subbs[sl+k]=valuebs[k];
			// 	cout<<sl+k<<" : "<<k<<endl;
			// }
			subv.push_back(valuebs[3]);
			subv.push_back(valuebs[2]);
			subv.push_back(valuebs[1]);
			subv.push_back(valuebs[0]);
			// cout<<"I : "<<i<<" adding : "<<valuebs.to_string()<<", row : "<<row<<" , col : "<<col<<endl;
		}
		// for(auto bit:subv) cout<<bit;cout<<endl;
		reverse(subv.begin(),subv.end());
		for(int i=0;i<32;i++){
			subbs[i]=(subv[i])?1:0;
		}
		// cout<<(subbs)<<endl;
		return subbs;
	}
	string encrypt(string plainText){
		bitset<64> plainbits(toInt(plainText));
		cout<<toHex(plainbits.to_ullong())<<endl;
		//doing initial permutation
		permute64(plainbits,initialPBox);
		cout<<"after initial permutation : "<<endl;
		cout<<toHex(plainbits.to_ullong())<<endl;
		//done initial permutatino
		bitset<32> leftbits,rightbits;
		split(plainbits,leftbits,rightbits);
		cout<<toHex(leftbits.to_ullong())<<" "<<toHex(rightbits.to_ullong())<<endl;
		for(int i=0;i<16;i++){
			bitset<32> ansbs=mixer(leftbits,rightbits,keys[i]);
			leftbits=rightbits;
			rightbits=ansbs;
			if(i==15){
				bitset<32> tempbits=leftbits;
				leftbits=rightbits;
				rightbits=tempbits;
			}
			cout<<"round : "<<i+1<<" => ";
			cout<<toHex(leftbits.to_ullong())<<" "<<toHex(rightbits.to_ullong())<<endl;
		}
		string encrypted=toHex(leftbits.to_ullong())+toHex(rightbits.to_ullong());
		return encrypted;
	}
};

signed main(){
	
	string plainText="123456ABCD132536";
	DES* des=new DES();
	string encrypted=des->encrypt(plainText);
	cout<<"encrypted : "<<encrypted<<endl;
	delete des;
	return 0;
}