// https://codeforces.com/contest/126/problem/B

#include<bits/stdc++.h>
using namespace std;

// https://cp-algorithms.com/string/z-function.html
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
        int n = (int)s.size();
        vector<int> Z = z_function(s);
        set<int> track;
        for(int i = 0; i < n; i++) {
            if(i + Z[i] == n) {
                auto it = track.lower_bound(Z[i]);
                if(it != track.end()) {
                    cout << s.substr(i, Z[i]) << "\n";
                    return 0;
                }
            }
            track.insert(Z[i]);
        }
        cout << "Just a legend" << "\n";
    }
    return 0;
}