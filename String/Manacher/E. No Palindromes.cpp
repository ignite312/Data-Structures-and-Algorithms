// https://codeforces.com/contest/1951/problem/E

#include<bits/stdc++.h>
using namespace std;

vector<int> manacher(string t) {
    string s;
    for(auto c: t) {
        s += string("#") + c;
    }
    s+="#";
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

// 0-base indexing
bool is_palindrome(int l, int r, vector<int> &pal) {
    l++, r++;
    int range = (r - l) + 1;
    l = (l << 1) - 1;
    r = (r << 1) - 1;
    int mid = (l + r) >> 1;
    return pal[mid] >= range; 
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    string _s = s;
    sort(_s.begin(), _s.end());
    vector<int> pal = manacher(s);
    if(_s.front() == _s.back())cout << "NO\n";
    else if(!is_palindrome(0, n-1, pal))cout << "YES\n1\n" << s.substr(0, n) << "\n";
    else {
        for(int i = 0; i < n; i++) {
            if(!is_palindrome(0, i, pal) && !is_palindrome(i+1, n-1, pal)) {
                cout << "YES\n2\n" << s.substr(0, i+1) << " " << s.substr(i+1, n-(i+1)) << "\n";
                return;
            }
        }
        cout << "NO\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        solve();
    }
    return 0;
}