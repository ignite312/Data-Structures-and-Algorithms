#include<bits/stdc++.h>
using namespace std;
const int N = 100000 + 5;
int tree[N*4+5][3], arr[N+5];
int n, q;
vector<tuple<int, int, int>> ans;

void build(int node, int l, int r) {
    if(l == r) {
        tree[node][0] = tree[node][1] = tree[node][2] = 1;
        return;
    }
    int mid = l + (r - l)/2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node][2] = max(tree[node*2][2], tree[node*2+1][2]);
    if(arr[mid] == arr[mid+1])tree[node][2] = max(tree[node][2], tree[node*2][1] + tree[node*2+1][0]);
    if(arr[l] == arr[mid+1])tree[node][0] = (mid-l+1) + tree[node*2+1][0];
    else tree[node][0] = tree[node*2][0];
    if(arr[r] == arr[mid])tree[node][1] = (r - (mid+1) + 1) + tree[node*2][1];
    else tree[node][1] = tree[node*2+1][1];
}
void query(int node, int l, int r, int i, int j) {
    if(r < i || l > j)return;
    if(l >= i && r <= j) {
        ans.emplace_back(node, l, r);
        return;
    }
    int mid = l + (r - l)/2;
    query(node*2, l, mid, i, j), query(node*2+1, mid+1, r, i, j);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(1) {
        cin >> n;
        if(n == 0)break;
        cin >> q;
        for(int i = 0; i <= 4*n; i++)tree[i][0] = tree[i][1] = tree[i][2] = 0;
        for(int i = 1; i <= n; i++)cin >> arr[i];
        build(1, 1, n);
        while(q--) {
            int l, r;
            cin >> l >> r;
            query(1, 1, n, l, r);
            int suff, mx;
            auto[node, ll, rr] = ans[0];
            suff = tree[node][1];
            mx = tree[node][2];
            int k = 0;
            for(auto[node, l, r] : ans) {
                k++;
                if(k == 1)continue;
                mx = max(mx, tree[node][2]);
                if(arr[l-1] == arr[l])mx = max(mx, suff + tree[node][0]);
                if(arr[r] == arr[l-1])suff = (r - l + 1) + suff;
                else suff = tree[node][1];
            }
            cout << mx << "\n";
            ans.clear();
        }
    }
    return 0;
}
// https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2176
