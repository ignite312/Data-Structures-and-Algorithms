#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
struct Segtree {
    int n;
    vector<ll> tree, lazy;
 
    ll merge(ll x, ll y) {
        return x + y;
    }
    void push(int node, int l, int r) {
        tree[node]+=(r-l+1)*lazy[node];
        int a = node*2+1, b = node*2+2;
        lazy[a]+=lazy[node], lazy[b]+=lazy[node];
        lazy[node] = 0;
    }
    void build(vector<ll> &a, int node, int l, int r) {
        if(l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = l + (r - l)/2;
        build(a, node*2+1, l, mid);
        build(a, node*2+2, mid+1, r);
        tree[node] = merge(tree[node*2+1], tree[node*2+2]);
    }
    void build(vector<ll> &a) {
        build(a, 0, 0, n-1);
    }
    void update(int i, int j, ll value, int node, int l, int r) {
        if(l > j || r < i)return;
        if(l >= i && r <= j) {
            lazy[node]+=value;
            return;
        }
        if(lazy[node])push(node, l, r);
        int mid = l + (r-l)/2;
        update(i, j, value, node*2+1, l, mid);
        update(i, j, value, node*2+2, mid+1, r);
        tree[node] = merge(tree[node*2+1], tree[node*2+2]);
    }
    void update(int i, int j, ll value) {
        update(i, j, value, 0, 0, n-1);
    }
    ll query(int i, int j, int node, int l, int r) {
        if(l > j || r < i)
            return 0;
        if(l >= i && r <= j)
            return tree[node] + (r-l+1)*lazy[node];
 
        if(lazy[node]) push(node, l, r);
        int mid = l + (r - l)/2;
        return merge(query(i, j, node*2+1, l, mid), query(i, j, node*2+2, mid+1, r));
    }
    ll query(int i, int j) {
        return query(i, j, 0, 0, n-1);
    }
    int sz(int n) {
        int size = 1;
        while(size < n) size = size << 1;
        return 2*size-1;
    }
    void init(vector<ll> &a) {
        n = a.size();
        int _sz = sz(n);
        tree.resize(_sz);
        lazy.assign(_sz, 0);
        build(a, 0, 0, n-1);
    }
} st;
/* Static Update
struct Segtree {
    int n;
    vector<ll> tree;

    ll merge(ll x, ll y) {
        return x + y;
    }
    void build(vector<ll> &a, int node, int l, int r) {
        if(l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = l + (r - l)/2;
        build(a, node*2+1, l, mid);
        build(a, node*2+2, mid+1, r);
        tree[node] = merge(tree[node*2+1], tree[node*2+2]);
    }
    void update(int i, ll value, int node, int l, int r) {
        if(l == i && r == i) {
            tree[node] = value;
            return;
        }
        int mid = l + (r-l)/2;
        if(i <= mid)update(i, value, node*2+1, l, mid);
        else update(i, value, node*2+2, mid+1, r);
        tree[node] = merge(tree[node*2+1], tree[node*2+2]);
    }
    void update(int i, int value) {
        update(i, value, 0, 0, n-1);
    }
    ll query(int i, int j, int node, int l, int r) {
        if(l > j || r < i) return 0;
        if(l >= i && r <= j)return tree[node];
        int mid = l + (r - l)/2;
        return merge(query(i, j, node*2+1, l, mid), query(i, j, node*2+2, mid+1, r));
    }
    ll query(int i, int j) {
        return query(i, j, 0, 0, n-1);
    }
    int sz(int n) {
        int size = 1;
        while(size < n) size = size << 1;
        return 2*size-1;
    }
    void init(vector<ll> &a) {
        n = a.size();
        int _sz = sz(n);
        tree.resize(_sz);
        build(a, 0, 0, n-1);
    }
} st;
*/
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
        st.init(a);
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
// https://cses.fi/problemset/task/1648
// https://cses.fi/problemset/task/1651/
// https://codeforces.com/contest/1872/problem/E
