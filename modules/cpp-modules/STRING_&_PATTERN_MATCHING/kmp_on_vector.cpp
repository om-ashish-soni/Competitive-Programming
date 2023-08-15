void prefix_function(vector<int> &s, vector<int> &pf)
{
    int n = s.size();
    pf.resize(n);
    pf[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int j = pf[i - 1];
        while (j > 0 && s[i] != s[j])
        {
            j = pf[j - 1];
        }
        if (s[i] == s[j])
        {
            j++;
        }
        pf[i] = j;
    }
    // Time complexity : O(n)
}
void kmp(vector<int> &s, vector<int> &pattern, vector<int> &match)
{
    int pz = pattern.size();
    int pos(-1), i(0), j(0);
    vector<int> pf;
    prefix_function(pattern, pf);
    // for(auto num:pf) cout<<num<<" ";cout<<endl;
    while (i < s.size())
    {
        // cout<<i<<" vs "<<s.size()<<" , "<<j<<" vs "<<pf.size()<<endl;
        if (s[i] == pattern[j])
        {
            j++;
            i++;
        }
        else
        {
            if (j != 0)
            {
                j = pf[j - 1];
            }
            else
                i++;
        }
        // cout<<j<<" vs "<<pattern.size()<<endl;
        if (j == pattern.size())
        {
            match.push_back(i - pz);
            j = pf[j - 1];
        }
    }
}