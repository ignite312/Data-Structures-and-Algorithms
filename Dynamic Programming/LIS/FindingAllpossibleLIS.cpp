/*
https://atcoder.jp/contests/abc354/tasks/abc354_f
Complexity: O(n^2)
*/
#include<bits/stdc++.h>
using namespace std;
int n;

void backtrack(vector<vector<int>>& all_LIS, vector<int>& cur_lis, const vector<int>& A, const vector<vector<int>>& prev, int current_idx) {
    cur_lis.push_back(current_idx);
    if (prev[current_idx].empty()) {
        // Reverse the current LIS since we are backtracking
        vector<int> tmp_lis = cur_lis;
        reverse(tmp_lis.begin(), tmp_lis.end());
        all_LIS.push_back(tmp_lis);
    } else {
        for (int prev_idx : prev[current_idx]) {
            backtrack(all_LIS, cur_lis, A, prev, prev_idx);
        }
    }
    cur_lis.pop_back();
}
vector<vector<int>> find_all_LIS(const vector<int>& A) {
    int N = A.size();
    vector<int> LIS_length(N, 1);
    vector<vector<int>> prev(N);
    int max_length = 1;

    // Compute LIS lengths and track previous indices
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (A[j] < A[i]) {
                if (LIS_length[j] + 1 > LIS_length[i]) {
                    LIS_length[i] = LIS_length[j] + 1;
                    prev[i].clear();
                    prev[i].push_back(j);
                } else if (LIS_length[j] + 1 == LIS_length[i]) {
                    prev[i].push_back(j);
                }
            }
        }
        max_length = max(max_length, LIS_length[i]);
    }
    // Find all LIS by backtracking from indices with maximum LIS length
    vector<vector<int>> all_LIS;
    vector<int> cur_lis;
    for (int i = 0; i < N; ++i) {
        if (LIS_length[i] == max_length) {
            backtrack(all_LIS, cur_lis, A, prev, i);
        }
    }
    return all_LIS;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        vector<vector<int>> all_LIS = find_all_LIS(v);
        set<int> st;
        for (const auto& lis : all_LIS) {
            for (int idx : lis) {
                st.insert(idx+1);
            }
        }
        cout << st.size() << "\n";
        for(auto x : st) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}