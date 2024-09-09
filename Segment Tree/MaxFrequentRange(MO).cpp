// https://codeforces.com/contest/2009/problem/G1
// 1-base indexing
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1;
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
void solve(vector<tuple<int, int, int>> &queries, int k) {
    const int BLOCK_SIZE = sqrt(queries.size()) + 1;
    sort(queries.begin(), queries.end(), [&](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        int blockA = get<0>(a) / BLOCK_SIZE;
        int blockB = get<0>(b) / BLOCK_SIZE;
        if (blockA != blockB)
            return blockA < blockB;
        return get<1>(a) < get<1>(b);
    });

    auto[L, R, id] = queries[0];
    int curr_l = L, curr_r = L;
    maxFreq = 1;
    freq[a[curr_l]]++;
    freqCount[1] = 1;
    vector<int> ans(queries.size() + 1);

    for(auto [L, R, id] : queries) {
        adjust(curr_l, curr_r, L, R);
        ans[id] = maxFreq;
    }
    for(int i = 1; i < ans.size(); i++) cout << k - ans[i] << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n, k, q;
        cin >> n >> k >> q;
        for(int i = 0; i <= n; i++) {
            a[i] = freq[i] = 0;
        }
        maxFreq = 0;
        freqCount.clear();
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] -= i;
        }
        map<int, int> compress;
        int current = 1;
        for(int i = 1; i <= n; i++) {
            if(compress[a[i]]) a[i] = compress[a[i]];
            else {
                compress[a[i]] = current++;
                a[i] = compress[a[i]];
            }
        }
        vector<tuple<int, int, int>> queries;
        for(int i = 1; i <= q; i++) {
            int L, R;
            cin >> L >> R;
            queries.push_back({L, R, i});
        }
        solve(queries, k);
    }
    return 0;
}