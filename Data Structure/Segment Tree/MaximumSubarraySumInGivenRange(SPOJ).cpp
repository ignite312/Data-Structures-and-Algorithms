#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 5;
ll tree[N*4+5][4];
vector<tuple<int, int, int>> ans;
 
// Empty Subarray are not allowed allowed
void build(vector<ll> &arr, int node, int l, int r) {
    if(l == r) {
        tree[node][0] = tree[node][1] = tree[node][2] = arr[l];
        tree[node][3] = arr[l];
        return;
    }
    int mid = l + (r - l)/2;
    build(arr, node*2, l, mid);
    build(arr, node*2+1, mid+1, r);
    tree[node][0] = max(tree[node*2][0], tree[node*2][3] + tree[node*2+1][0]);
    tree[node][1] = max(tree[node*2+1][1], tree[node*2+1][3] + tree[node*2][1]);
    tree[node][3] = tree[node*2][3] + tree[node*2+1][3];
    tree[node][2] = max(tree[node*2][1] + tree[node*2+1][0], max(tree[node*2][2], tree[node*2+1][2]));
}
void update(int node, int l, int r, int i, ll new_value) {
    if(r < i || l > i)return;
    if(l == i && r == i) {
        tree[node][0] = tree[node][1] = tree[node][2] = new_value;
        tree[node][3] = new_value;
        return;
    }
    int mid = l + (r - l)/2;
    update(node*2, l, mid, i, new_value);
    update(node*2+1, mid+1, r, i, new_value);
    tree[node][0] = max(tree[node*2][0], tree[node*2][3] + tree[node*2+1][0]);
    tree[node][1] = max(tree[node*2+1][1], tree[node*2+1][3] + tree[node*2][1]);
    tree[node][3] = tree[node*2][3] + tree[node*2+1][3];
    tree[node][2] = max(tree[node*2][1] + tree[node*2+1][0], max(tree[node*2][2], tree[node*2+1][2]));
}
void query(int node, int l, int r, int i, int j) {
    if(r < i || l > j)return;
    if(l >= i && r <= j) {
        ans.emplace_back(node, l, r);
        return;
    }
    int mid = l + (r - l)/2;
    query(node*2, l, mid, i, j), query(node*2 + 1, mid+1, r, i, j);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        int n;
        cin >> n;
        vector<ll> arr(n+1);
        for(int i = 1; i <= n; i++)cin >> arr[i];
        build(arr, 1, 1, n);
        int q;
        cin >> q;
        while(q--) {
            int type, i, j;
            cin >> type >> i >> j;
            if(type == 0) {
                update(1, 1, n, i, j);
                continue;
            }
            query(1, 1, n, i, j);
            ll mxpref, mxsuff, sum, mxSubarraySum;
            auto[node, l, r] = ans[0];
            mxpref = tree[node][0];
            mxsuff = tree[node][1];
            sum = tree[node][3];
            mxSubarraySum = tree[node][2];
            int k = 0;
            for(auto[node, l, r] : ans) {
                k++;
                if(k == 1)continue;
                mxSubarraySum = max(max(mxSubarraySum, tree[node][2]), mxsuff + tree[node][0]);
                mxpref = max(mxpref, sum + tree[node][0]);
                mxsuff = max(tree[node][1], tree[node][3] + mxsuff);
                sum = sum + tree[node][3];
            }
            cout << mxSubarraySum << "\n";
            ans.clear();
        }
    }
    return 0;
}
// https://www.spoj.com/problems/GSS3/cstart=70
