// problem link : https://codeforces.com/contest/1709/problem/C

/*
editorial : 
There are many different approaches to this problem, but I think the model solution has the most elegant one.

First of all, let's construct an RBS from the given string (it always exists, so it is always possible). By calculating the number of opening brackets, closing brackets and questions in the given string, we can compute the number of question marks that should be replaced with opening brackets (it is easy since exactly half of the characters in each RBS are opening brackets). Then, let's form the RBS greedily: replace the first several question marks with opening brackets, and all remaining ones with closed brackets.

Okay, then what about finding a second RBS? Recall that a bracket sequence is an RBS when for each of its positions, the number of closing brackets before it is not greater than the number of opening brackets before it (and these two values should be equal at the end of the sequence, but it is less important now). Consider the segment between the last question mark replaced with an opening bracket, and the first question mark replaced by the closing bracket. If we try to change the order of characters corresponding to question marks, the balance on this segment will decrease at least by 2
(since at least one opening bracket to the left of it will become a closing bracket). Is there a way to affect only this segment, and change the balance on it only by 2? Yes — just swap the endpoints of this segment (i. e. the last opening bracket that was a question mark and the first closing bracket that was also a question mark). If it yields an RBS, then the answer is NO. Otherwise, the answer is YES since any other permutation of characters that were replacing question marks will also decrease the balance on this segment by at least 2.

*/

// Solution : 

#include <bits/stdc++.h>

using namespace std;

int main() {
  auto check = [](const string& s) {
    int bal = 0;
    for (char c : s) {
      if (c == '(') ++bal;
      if (c == ')') --bal;
      if (bal < 0) return false;
    }
    return bal == 0;
  };
  
  ios::sync_with_stdio(false); cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    vector<int> pos;
    int op = s.size() / 2, cl = s.size() / 2;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '?') pos.push_back(i);
      if (s[i] == '(') --op;
      if (s[i] == ')') --cl;
    }
    for (int i = 0; i < pos.size(); ++i) {
      if (i < op) s[pos[i]] = '(';
      else s[pos[i]] = ')';
    }
    bool ok = true;
    if (op > 0 && cl > 0) {
      swap(s[pos[op - 1]], s[pos[op]]);
      if (check(s)) ok = false;
    }
    cout << (ok ? "YES\n" : "NO\n");
  }
} 