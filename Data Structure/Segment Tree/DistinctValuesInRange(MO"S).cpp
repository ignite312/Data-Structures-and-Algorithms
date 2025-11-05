/*
Problem Name: Distinct Values Queries
Problem Link: https://cses.fi/problemset/task/1734/
Complexity:O((N+Q)sqrt(N))
Resource: https://cp-algorithms.com/data_structures/sqrt_decomposition.html
More Problems: https://codeforces.com/contest/2014/problem/H
               https://codeforces.com/contest/2009/problem/G1
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 200000;
int a[N], freq[N], distinct;

// 0-base indexing
void add(int x) {
    if(!freq[x]) distinct++;
    freq[x]++;
}
void remove(int x) {
    freq[x]--;
    if(!freq[x]) distinct--;
}
void adjust(int &curr_l, int &curr_r, int L, int R) {
    while(curr_l > L) {
        curr_l--;
        add(a[curr_l]);
    }
    while(curr_r < R) {
        curr_r++;
        add(a[curr_r]);
    }
    while(curr_l < L) {
        remove(a[curr_l]);
        curr_l++;
    }
    while(curr_r > R) {
        remove(a[curr_r]);
        curr_r--;
    }
}
void solve(vector<array<int, 3>> &queries) {
    // const int BLOCK_SIZE = sqrt(queries.size()) + 1;
    const int BLOCK_SIZE = 555;
    sort(queries.begin(), queries.end(), [&](const array<int, 3>& a, const array<int, 3>& b) {
        int blockA = a[0] / BLOCK_SIZE;
        int blockB = b[0] / BLOCK_SIZE;
        if (blockA != blockB)
            return blockA < blockB;
        return a[1] < b[1];
    });
    auto[L, R, id] = queries[0];
    int curr_l = L, curr_r = L;
    distinct = 1;
    freq[a[curr_l]]++;
    vector<int> ans(queries.size());
    for(auto [L, R, id] : queries) {
        adjust(curr_l, curr_r, L, R);
        ans[id] = distinct;
    }
    for(auto x : ans) cout << x << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        map<int, int> compress;
        int id = 0;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(compress.find(a[i]) != compress.end()) a[i] = compress[a[i]];
            else {
                compress[a[i]] = id++;
                a[i] = compress[a[i]];
            }
        }
        vector<array<int, 3>> queries;
        for(int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            queries.push_back({l, r, i});
        }
        solve(queries);
    }
    return 0;
}