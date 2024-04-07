// https://codeforces.com/contest/1944/problem/D

#include<bits/stdc++.h>
using namespace std;
#define ll long long

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

// S_n = n/2*(2*a + (n-1)*d)
ll arithmeticSeriesSum(int n) {
    return n*1LL*(n+1) >> 1;
}
void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> pal = manacher(s);
    set<int> same, alter; // Set for checking segment element are same or alternating
    for(int i = 0; i < n-1; i++) {
        if(s[i] != s[i+1]) {
            same.insert(i);
        }
        if(i < n-2) {
            if(s[i] != s[i+2]) {
                alter.insert(i);
            }
        }
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        int len = r - l + 1;
        if(l == r) {
            cout << "0\n";
        }else {
            auto it = same.lower_bound(l);
            if(it == same.end() || r <= (*it)) {
                cout << "0\n";
            }else {
                auto it = alter.lower_bound(l);
                if(it == alter.end() || r-1 <= (*it)) { // condition for alternating segment
                    cout << arithmeticSeriesSum(len) - ((ll)ceil(len/2.0))*((ll)ceil(len/2.0)) << "\n"; // subtract contribution for odd K-good
                }else {
                    if(is_palindrome(l, r, pal))cout << arithmeticSeriesSum(len) - 1 - len << "\n"; // if full segment is palindrome then it is not len-good
                    else cout << arithmeticSeriesSum(len) - 1 << "\n"; //  -1 because 1-length palindrome is out of consideration
                }
            }
        }
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