#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll lazy[N*4+5], tree[N*4+5];

void build(vector<ll> &arr, int node, int l, int r) {
    if(l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = l + (r - l)/2;
    build(arr, node*2, l, mid);
    build(arr, node*2+1, mid+1, r);
    tree[node] = tree[node*2] + tree[node*2+1];
}
void update(int node, int l, int r, int i, int j, ll value) {
    if(lazy[node] != 0) {
        tree[node] += (r-l+1)*lazy[node];
        if(l != r) {
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node]; 
        }
        lazy[node] = 0;
    }
    if(l > j || r < i)return;
    if(l >= i && r <= j) {
        tree[node] += (r-l+1)*value;
        if(l != r) {
            lazy[node*2]+= value;
            lazy[node*2+1]+=value; 
        }
        return;
    }
    int mid = l + (r - l)/2;
    update(node*2, l, mid, i, j, value);
    update(node*2+1, mid+1, r, i, j, value);
    tree[node] = tree[node*2] + tree[node*2+1];
}
ll sum(int node, int l, int r, int i, int j) {
    if(lazy[node] != 0) {
        tree[node] += (r-l+1)*lazy[node];
        if(l != r) {
            lazy[node*2]+=lazy[node];
            lazy[node*2+1]+=lazy[node]; 
        }
        lazy[node] = 0;
    }
    if(l > j || r < i)return 0;
    if(l >= i && r <= j) return tree[node];
    int mid = l + (r - l)/2;
    return sum(node*2, l, mid, i, j) + sum(node*2+1, mid+1, r, i, j);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        vector<ll> arr(n+1);
        for(int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        build(arr, 1, 1, n);
        while(q--) {
            int type;
            cin >> type;
            if(type == 1) {
                int i, j, value;
                cin >> i >> j >> value;
                update(1, 1, n, i, j, value);
            }else {
                int i;
                cin >> i;
                cout << sum(1, 1, n, i, i) << "\n";
            }
        }
    }
}
// https://cses.fi/problemset/task/1651
