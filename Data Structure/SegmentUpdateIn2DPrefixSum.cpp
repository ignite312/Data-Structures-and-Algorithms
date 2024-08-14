// https://codeforces.com/contest/2000/problem/E
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n, m, k;

void apply_increment(vector<vector<ll>>& diff, int x1, int y1, int x2, int y2, int val) {
    diff[x1][y1] += val;
    if (x2 + 1 < n) diff[x2 + 1][y1] -= val;
    if (y2 + 1 < m) diff[x1][y2 + 1] -= val;
    if (x2 + 1 < n && y2 + 1 < m) diff[x2 + 1][y2 + 1] += val;
}

vector<vector<ll>> calculate(vector<vector<ll>> &diff) {
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            grid[i][j] = diff[i][j];
            if (i > 0) grid[i][j] += grid[i - 1][j];
            if (j > 0) grid[i][j] += grid[i][j - 1];
            if (i > 0 && j > 0) grid[i][j] -= grid[i - 1][j - 1];
        }
    }
    return grid;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    cin >> tt;
    while(tt--) {
        cin >> n >> m >> k;
        vector<vector<ll>> grid(n, vector<ll>(m, 0));
        for(int i = 0; i < n-k+1; i++) {
            for(int j = 0; j < m-k+1; j++) {
                apply_increment(grid, i, j, i+k-1, j+k-1, 1);
            }
        }
        int w;
        cin >> w;
        vector<ll> wt(w);
        for(int i = 0; i < w; i++) {
            cin >> wt[i];
        }
        grid = calculate(grid);
        vector<ll> ans;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans.push_back(grid[i][j]);
            }
        }
        sort(ans.rbegin(), ans.rend());
        sort(wt.rbegin(), wt.rend());
        ll final = 0;
        for(int i = 0; i < w; i++) {
            final += wt[i] * ans[i];
        }
        cout << final << "\n";
    }
    return 0;
}