#include<bits/stdc++.h>
using namespace std;
const int N = 1001;
const int INF = INT_MAX;
int dp[N][N];

// Complexity: O(nlog(n))
int lis(int n, vector<int> &a) {
    vector<int> d(n+1, INF);
    d[0] = -INF;
    for(int i = 0; i < n; i++) {
        int idx = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        d[idx] = a[i];
    }
    int ans = 1;
    for(int i = 1; i <= n; i++)if(d[i] < INF)ans = i;
    return ans;
}

// Cp-Algo Complexity: O(n^2)
vector<int> lis(vector<int> const& a) {
    int n = a.size();
    vector<int> d(n, 1), p(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && d[i] < d[j] + 1) {
                d[i] = d[j] + 1;
                p[i] = j;
            }
        }
    }
    int ans = d[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (d[i] > ans) {
            ans = d[i];
            pos = i;
        }
    }
    vector<int> sq;
    while (pos != -1) {
        sq.push_back(a[pos]);
        pos = p[pos];
    }
    reverse(sq.begin(), sq.end());
    return sq;
}

// Complexity: O(n^2)
int lisTopDown(int idx, int last_idx, int n, vector<int> &a) {
    if(idx == n)return 0;
    if(dp[idx][last_idx+1] != -1)return dp[idx][last_idx+1];

    int take = INT_MIN;
    if(last_idx == -1 || a[last_idx] < a[idx]) 
    take = 1 + lisTopDown(idx+1, idx, n, a);
    int not_take = 0 + lisTopDown(idx+1, last_idx, n, a);
    return dp[idx][last_idx+1] = max(take, not_take);
}
int lisRecursion(int n, vector<int> &a) {
    memset(dp, -1, sizeof(dp));
    return lisTopDown(0, -1, n, a);
}

// Complexity: O(n^2)
int lisBottomUp(int n, vector<int> &a) {
    vector<int> d(n, 1); // d[i] = maximum length of lis end here
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
            if(a[j] < a[i])
                d[i] = max(d[i], d[j]+1);
    int ans = 1;
    for(int i = 0; i < n; i++) ans = max(ans, d[i]);
    return ans;
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
        vector<int> a(n);
        for(int i = 0; i < n; i++)cin >> a[i];
        cout << lis(n, a);
    }
    return 0;
}