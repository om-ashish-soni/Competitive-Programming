void decode_huff1(node * root, vector<pair<string,char>> &v,string s) {
    if(!root) return;
    if(!root->left && !root->right){
        v.push_back({s,root->data});
    }
    string left=s;
    string right=s;
    left+='0';
    right+='1';
    decode_huff1(root->left,v,left);
    decode_huff1(root->right,v,right);
}
void decode_huff(node * root, string s) {
    int i=0;
    unordered_map<string, char> ump;
    string temp;
    vector<pair<string,char>> v;
    decode_huff1(root,v,temp);
    for(int i=0;i<v.size();i++){
        ump[v[i].first]=v[i].second;
    }
    for(int i=0;i<s.size();i++){
        temp+=s[i];
        if(ump[temp]){ cout<<ump[temp];   temp="";}
    }
}