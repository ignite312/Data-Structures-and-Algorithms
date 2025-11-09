#include <bits/stdc++.h>
using namespace std;
const int M = 26;
const int N = 2e5 + 1;
#define Node array<int, 6>

Node tree[N * 4 + 1];

bool eq(int x, int y) {
    return x == y;
}
void add(Node &x, int value) {
    for (int i = 0; i < 5; i++)
    	if (x[i] != -1)
        	x[i] = (x[i] + value) % M;
}
void push(int node) {
    int a = node * 2 + 1, b = node * 2 + 2;
    add(tree[a], tree[node][4]), add(tree[b], tree[node][4]);
    tree[node][4] = 0;
}
Node merge(Node x, Node y) {
    if (x[3] == -1) return y;
    if (y[0] == -1) return x;
    Node rslt = {-1, -1, -1, -1, 0, 0};
    rslt[5] = x[5] || y[5] || eq(x[2], y[0]) || eq(x[3], y[0]) || eq(x[3], y[1]);

    if (x[1] != -1) rslt[1] = x[1];
    else rslt[1] = y[0];
    if (y[2] != -1) rslt[2] = y[2];
    else rslt[2] = x[3];

    rslt[0] = x[0], rslt[3] = y[3];
    return rslt;
}
void build(vector<int> &a, int node, int l, int r) {
    if (l == r) {
        tree[node] = {a[l], -1, -1, a[l], 0, 0};
        return;
    }
    int mid = l + (r - l) / 2;
    build(a, node * 2 + 1, l, mid);
    build(a, node * 2 + 2, mid + 1, r);
    tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
}
void update(int i, int j, int value, int node, int l, int r) {
    if (l > j || r < i) return;
    if (l >= i && r <= j) {
        add(tree[node], value);
        return;
    }
    if(tree[node][4])push(node);
    int mid = l + (r - l) / 2;
    update(i, j, value, node * 2 + 1, l, mid);
    update(i, j, value, node * 2 + 2, mid + 1, r);
    tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
}
Node query(int i, int j, int node, int l, int r) {
    if (l > j || r < i)
    	return {-1, -1, -1, -1, 0, 0};
    if (l >= i && r <= j)
    	return tree[node];
    if(tree[node][4])push(node);

    int mid = l + (r - l) / 2;
    return merge(query(i, j, node * 2 + 1, l, mid), query(i, j, node * 2 + 2, mid + 1, r));
}
/*
struct segtree {
    int n;
    vector<Node> tree;
 
    bool eq(int x, int y) {
        return x == y;
    }
    void add(Node &x, int value) {
        for (int i = 0; i < 5; i++)
            if (x[i] != -1)
                x[i] = (x[i] + value) % M;
    }
    void push(int node) {
        int a = node * 2 + 1, b = node * 2 + 2;
        add(tree[a], tree[node][4]), add(tree[b], tree[node][4]);
        tree[node][4] = 0;
    }
    Node merge(Node x, Node y) {
        if (x[3] == -1)
            return y;
        if (y[0] == -1)
            return x;
        Node rslt = {-1, -1, -1, -1, 0, 0};
        rslt[5] = x[5] || y[5] || eq(x[2], y[0]) || eq(x[3], y[0]) || eq(x[3], y[1]);
 
        if (x[1] != -1)
            rslt[1] = x[1];
        else
            rslt[1] = y[0];
        if (y[2] != -1)
            rslt[2] = y[2];
        else
            rslt[2] = x[3];
 
        rslt[0] = x[0], rslt[3] = y[3];
        return rslt;
    }
    void build(vector<int> &a, int node, int l, int r) {
        if (l == r) {
            tree[node] = {a[l], -1, -1, a[l], 0, 0};
            return;
        }
        int mid = l + (r - l) / 2;
        build(a, node * 2 + 1, l, mid);
        build(a, node * 2 + 2, mid + 1, r);
        tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
    }
    void build(vector<int> &a) {
        build(a, 0, 0, n-1);
    }
    void update(int i, int j, int value, int node, int l, int r) {
        if (l > j || r < i)
            return;
        if (l >= i && r <= j) {
            add(tree[node], value);
            return;
        }
        if (tree[node][4])
            push(node);
        int mid = l + (r - l) / 2;
        update(i, j, value, node * 2 + 1, l, mid);
        update(i, j, value, node * 2 + 2, mid + 1, r);
        tree[node] = merge(tree[node * 2 + 1], tree[node * 2 + 2]);
    }
    void update(int i, int j, int value) {
        update(i, j, value, 0, 0, n-1);
    }
    Node query(int i, int j, int node, int l, int r) {
        if (l > j || r < i)
            return {-1, -1, -1, -1, 0, 0};
        if (l >= i && r <= j)
            return tree[node];
        if (tree[node][4])
            push(node);
 
        int mid = l + (r - l) / 2;
        return merge(query(i, j, node * 2 + 1, l, mid), query(i, j, node * 2 + 2, mid + 1, r));
    }
    Node query(int i, int j) {
        return query(i, j, 0, 0, n-1);
    }
    int sz(int n) {
        int size = 1;
        while(size < n) size = size << 1;
        return 2*size-1;
    }
    void init(vector<int> &a) {
        n = a.size();
        tree.resize(sz(n));
        build(a, 0, 0, n-1);
    }
} st;
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vector<int> a(n);
        for (int i = 0; i < n; i++) a[i] = s[i] - 'a';
        build(a, 0, 0, n - 1);
        while (q--) {
            int type;
            cin >> type;
            if (type == 1) {
                int l, r, x;
                cin >> l >> r >> x;
                update(--l, --r, x, 0, 0, n - 1);
            } else {
                int l, r;
                cin >> l >> r;
                Node ans = query(--l, --r, 0, 0, n - 1);
                if (ans[5]) cout << "NO\n";
                else cout << "YES\n";
            }
        }
    }
    return 0;
}
// https://codeforces.com/contest/1881/problem/G
