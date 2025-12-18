// https://codeforces.com/contest/2149/problem/E
#include<bits/stdc++.h>
using namespace std;
#define ll long long

// The subarray contains at most k distinct values.
// The subarray length is at most mxlength.
ll distAtMostK(vector<int> &v, int k, int mxlength) {
    int n = v.size();
    int dist = 0;
    int l = 0;
    ll ans = 0;
    map<int, int> mp;
    for(int r = 0; r < n; r++) {
        if(++mp[v[r]] == 1) { dist++; }
        while(dist > k || (r-l+1) > mxlength) {
            if(--mp[v[l]] == 0)dist--;
            l++;
        }
        ans+=(r-l+1)*1LL;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n, k, l, r;
        cin >> n >> k >> l >> r;
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        // Find total boundary l <= boundary size <= r and exactly k distinct element
        cout << (distAtMostK(v, k, r) - distAtMostK(v, k, l-1)) - 
         (distAtMostK(v, k-1, r) - distAtMostK(v, k-1, l-1)) << "\n";
    }
    return 0;
}