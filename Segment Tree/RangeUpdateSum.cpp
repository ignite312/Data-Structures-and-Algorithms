/*
Problem Name: Range Update Queries
Problem Link: https://cses.fi/problemset/task/1651/
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Segtree {
    // 0-base array indexing
    int n;
    vector<ll> tree, lazy;

    Segtree(int n) {
        this->n = n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    ll merge(ll x, ll y) {
        return x + y;
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;
        int left = node * 2, right = node * 2 + 1;
        int mid = (l + r) / 2;

        tree[left] += (mid - l + 1) * lazy[node];
        tree[right] += (r - mid) * lazy[node];

        lazy[left] += lazy[node];
        lazy[right] += lazy[node];
        lazy[node] = 0;
    }

    void build(vector<ll> &a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, node * 2, l, mid);
        build(a, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(vector<ll> &a) {
        build(a, 1, 0, n - 1);
    }

    void update(int i, int j, ll value, int node, int l, int r) {
        if (l > j || r < i) return;
        if (l >= i && r <= j) {
            lazy[node] += value;
            tree[node] += (r - l + 1) * value;
            return;
        }
        if (lazy[node]) push(node, l, r);
        int mid = (l + r) / 2;
        update(i, j, value, node * 2, l, mid);
        update(i, j, value, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int i, int j, ll value) {
        update(i, j, value, 1, 0, n - 1);
    }

    ll query(int i, int j, int node, int l, int r) {
        if (l > j || r < i) return 0;
        if (l >= i && r <= j) return tree[node];
        if (lazy[node]) push(node, l, r);
        int mid = (l + r) / 2;
        return merge(query(i, j, node * 2, l, mid),
                     query(i, j, node * 2 + 1, mid + 1, r));
    }

    ll query(int i, int j) {
        return query(i, j, 1, 0, n - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        for(int i = 0; i < n; i++)cin >> a[i];

        Segtree st(n);
        st.build(a);

        while(q--) {
            int type;
            cin >> type;
            if(type == 1) {
                int i, j;
                ll value;
                cin >> i >> j >> value;
                st.update(--i, --j, value);
            }else {
                int i;
                cin >> i;
                cout << st.query(i-1, i-1) << "\n";
            }
        }
    }
    return 0;
}