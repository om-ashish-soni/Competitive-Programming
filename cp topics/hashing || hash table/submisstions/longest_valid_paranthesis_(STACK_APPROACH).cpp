// problem link : https://leetcode.com/problems/longest-valid-parentheses/
// solution : below code

class Solution {
public:
    int longestValidParentheses(string s) {
        int size=s.size();
        char arr[size+1];
        int index[size+1];
        arr[0]='o';
        index[0] = -100;
        int top=0;
        int total=0;
        int indices[size+ 1];
        for(int i=0;i<size;i++){
            indices[i]=-1;
        }
        for(int i=0;i<size;i++){
            if(s[i]==')'){
                if(arr[top]=='('){
                    indices[index[top]]=i;
                    indices[i]=i;
                    top--;
                }else{
                    top=0;
                }
                    
                
            }else{
                top++;
                arr[top]=s[i];
                index[top]=i;
            }
        }
        
        for(int i=0;i<size;i++){
            int count=0;
            while((i<size) && (-1 != indices[i])){
                count+=(2 + (indices[i]-i-1));
                i=indices[i]+1;
            }
            if(count>total){
                total=count;
            }
        }
        return total;
    }
};
