#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Empty or Non-empty Subarray
/*
ll maxSubArraySum(vector<ll> v, ll n) {
    ll mx = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + v[i];
        if(sum > mx) mx = sum;
        if(sum < 0) sum = 0;
    }
    return mx;
}
*/
// Non-empty Subarray
ll maxSubArraySum(vector<ll> v, ll n) {
    ll sum = v[0], mx = v[0];
    for (int i = 1; i < n; i++) {
        sum = max(sum+v[i], v[i]);
        mx = max(mx, sum);
    }
    return mx;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<ll> v(n);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        cout << maxSubArraySum(v, n);
    }
    return 0;
}