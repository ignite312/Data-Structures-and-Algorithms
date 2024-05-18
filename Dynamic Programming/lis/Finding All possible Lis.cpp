/*
https://atcoder.jp/contests/abc354/tasks/abc354_f
Complexity: O(n^2)
*/
#include<bits/stdc++.h>
using namespace std;
int n;

void backtrack(vector<vector<int>>& all_LIS, vector<int>& current_LIS, const vector<int>& A, const vector<vector<int>>& prev, int current_index) {
    current_LIS.push_back(current_index);
    if (prev[current_index].empty()) {
        // Reverse the current LIS since we are backtracking
        vector<int> temp_LIS = current_LIS;
        reverse(temp_LIS.begin(), temp_LIS.end());
        all_LIS.push_back(temp_LIS);
    } else {
        for (int prev_index : prev[current_index]) {
            backtrack(all_LIS, current_LIS, A, prev, prev_index);
        }
    }
    current_LIS.pop_back();
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
    vector<int> current_LIS;
    for (int i = 0; i < N; ++i) {
        if (LIS_length[i] == max_length) {
            backtrack(all_LIS, current_LIS, A, prev, i);
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
            for (int index : lis) {
                st.insert(index+1);
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