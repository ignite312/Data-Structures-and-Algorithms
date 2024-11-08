// https://codeforces.com/contest/2014/problem/H
#include<bits/stdc++.h>
using namespace std;
#define ll long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        vector<ll> v(n);
        map<int, int> compress;
        int id = 0;
        for(int i = 0; i < n; i++) {
            cin >> v[i];
            if(compress.find(v[i]) != compress.end()) {
                v[i] = compress[v[i]];
            } else {
                compress[v[i]] = id++;
                v[i] = compress[v[i]];
            }
        }
        vector<ll> rv(n);
        for(int i = 0; i < n; i++) {
            rv[i] = rng();
        }
        for(int i = 0; i < n; i++) {
            v[i] = rv[v[i]];
        }
        vector<ll> pfx(n+1, 0);
        for(int i = 1; i <= n; i++) {
            pfx[i] = (pfx[i-1] ^ v[i-1]);
        }
        while(q--) {
            int l, r;
            cin >> l >> r;
            if(pfx[l-1] == pfx[r]) {
                cout << "YES\n";
            }else cout << "NO\n";
        }
    }
    return 0;
}