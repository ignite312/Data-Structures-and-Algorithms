/*
Problem Name: String Functions
Problem Link: https://cses.fi/problemset/task/2107/
Practice Problem: https://codeforces.com/contest/126/problem/B
*/
#include<bits/stdc++.h>
using namespace std;

// pi[i] = the length of the longest proper prefix of the substring
// s[0 ... i] which is also a suffix of this substring.
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
// z[i] = length of the longest substring starting at position i that matches the prefix of s.
// z[0] = 0
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        string s;
        cin >> s;
        vector<int> z = z_function(s);
        for(auto x : z)cout << x << " ";
            cout << "\n";
        vector<int> pi = prefix_function(s);
        for(auto x : pi)cout << x << " ";
            cout << "\n";
    }
    return 0;
}