struct Segtree {
    // 0-based array indexing
    int n;
    vector<int> t;
    Segtree(int n = 0) : n(n), t(4*n, 0) {}
    int merge(int x, int y) { return max(x, y); } // fn
    void build(vector<int> &a) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) 
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }
    void update(int p, int val) {
        for (t[p += n] = val; p > 1; p >>= 1) // increment or set
            t[p >> 1] = merge(t[p], t[p ^ 1]);
    }
    int query(int l, int r) {
        int res = INT_MIN; // identity
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, t[l++]);
            if (!(r & 1)) res = merge(res, t[r--]);
        }
        return res;
    }
};