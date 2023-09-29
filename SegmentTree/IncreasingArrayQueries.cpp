#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define all(v) v.begin(), v.end()
const int N = 2e5 + 5;

struct Node {
    vector<ll> v, pref;
    ll cnt;
};
vector<Node> tree(N*4+5);

void merge(int node) {
    vector<ll> l, r;
    l = tree[node*2].v, r = tree[node*2+1].v;
    int lst = l.back();
    int idx = lower_bound(all(r), lst) - r.begin();
    ll cnt = tree[node*2].cnt+tree[node*2+1].cnt;
    for(int i = 0; i < idx; i++)l.push_back(lst);
    for(int i = idx; i < (int)r.size(); i++)l.push_back(r[i]);
    if(idx > 0)cnt += idx*1LL*lst - tree[node*2+1].pref[idx-1];

    vector<ll> pref(l.size());
    pref[0] = l[0];
    for(int i = 1; i < (int)l.size(); i++) pref[i] = pref[i-1]+l[i];

    struct Node t_node;
    t_node.v = l;
    t_node.pref = pref;
    t_node.cnt = cnt;
    tree[node] = t_node;
}
void build(vector<ll> &arr, int node, int l, int r) {
    if(l == r) {
        struct Node t_node;
        t_node.v.push_back(arr[l]);
        t_node.pref.push_back(arr[l]);
        t_node.cnt = 0;
        tree[node] = t_node;
        return;
    }
    int mid = l + (r - l)/2;
    build(arr, node*2, l, mid);
    build(arr, node*2+1, mid+1, r);
    merge(node);
}

vector<int> ans;
void query(int node, int l, int r, int i, int j) {
    if(r < i || l > j)return;
    if(l >= i && r <= j) {
        ans.push_back(node);
        return;
    }
    int mid = l + (r-l)/2;
    query(node*2, l, mid, i, j), query(node*2+1, mid+1, r, i, j);
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
        for(int i = 1; i <= n; i++)cin >> arr[i];
        build(arr, 1, 1, n);
        while(q--) {
            int l, r;
            cin >> l >> r;
            query(1, 1, n, l, r);
            ll cnt = tree[ans[0]].cnt;
            int lst = tree[ans[0]].v.back();
            for(int i = 1; i < (int)ans.size(); i++) {
                cnt+=tree[ans[i]].cnt;
                int idx = lower_bound(all(tree[ans[i]].v), lst) - tree[ans[i]].v.begin();
                if(idx > 0)cnt += idx*1LL*lst - tree[ans[i]].pref[idx-1];
                if(idx != (int)tree[ans[i]].v.size())lst = tree[ans[i]].v.back();
            }
            cout << cnt << "\n";
            ans.clear();
        }
     }
    return 0;
}
// https://cses.fi/problemset/task/2416/
