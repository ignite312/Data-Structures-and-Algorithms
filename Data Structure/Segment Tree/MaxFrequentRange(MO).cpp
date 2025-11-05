// https://codeforces.com/contest/2009/problem/G1
#include<bits/stdc++.h>
using namespace std;

// 0-base indexing
const int N = 200000;
int a[N], freq[N], maxFreq;
map<int, int> freqCount;

void add(int x) {
    freqCount[freq[x]]--;
    if (freqCount[freq[x]] == 0) {
        freqCount.erase(freq[x]);
    }
    freq[x]++;
    freqCount[freq[x]]++;
    maxFreq = max(maxFreq, freq[x]);
}
void remove(int x) {
    freqCount[freq[x]]--;
    if (freqCount[freq[x]] == 0) {
        freqCount.erase(freq[x]);
    }
    freq[x]--;
    if (freq[x] > 0) {
        freqCount[freq[x]]++;
    }
    if (freqCount.empty()) {
        maxFreq = 0;
    } else {
        maxFreq = freqCount.rbegin()->first;
    }
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
void solve(vector<array<int, 3>> &queries, int k) {
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
    maxFreq = 1;
    freq[a[curr_l]]++;
    freqCount[1] = 1;
    vector<int> ans(queries.size());

    for(auto [L, R, id] : queries) {
        adjust(curr_l, curr_r, L, R);
        ans[id] = maxFreq;
    }
    for(auto x : ans) cout << k - x << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        maxFreq = 0;
        freqCount.clear();

        int n, k, q;
        cin >> n >> k >> q;
        for(int i = 0; i <= n; i++) {
            a[i] = freq[i] = 0;
        }
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            a[i] -= i;
        }
        map<int, int> compress;
        int id = 0;
        for(int i = 0; i < n; i++) {
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
        solve(queries, k);
    }
    return 0;
}