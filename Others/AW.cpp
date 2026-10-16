#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500001;
struct Node {
	int mn;
	int ans;
	vector<array<int, 3>> v;
};
Node tree[N*4];
int a[N];

Node merge(Node &left, Node &right) {
	int fin_mn = min(left.mn, right.mn);
	int fn_ans = left.ans+right.ans;
	// cout << left.mn << " " << right.mn << "f\n";
	vector<array<int, 3>> fin_v;
	for(int i = 0; i < left.v.size(); i++) {
		if(left.v[i][0]*2 > (left.v[i][1] + right.mn)) {
			fn_ans++;
		}else {
			fin_v.push_back({left.v[i][0], left.v[i][1], min(left.v[i][2], right.mn)});
		}
	}
	for(int i = 0; i < right.v.size(); i++) {
		if(right.v[i][0]*2 > (left.mn + right.v[i][2])) {
			fn_ans++;
		}else {
			fin_v.push_back({right.v[i][0], min(right.v[i][1], left.mn), right.v[i][2]});
		}
	}
	Node nw_n;
	nw_n.mn = fin_mn;
	nw_n.ans = fn_ans;
	nw_n.v = fin_v;
	// cout << nw_n.ans << "  " << nw_n.mn << " " << "$$$$$$$$$$$\n";
	return nw_n;
}
void build(int idx, int l, int r) {
	// cout << l << " " << r << "\n";
	if(l == r) {
		Node nd;
		nd.mn = a[l];
		nd.ans = 0;
		nd.v = {{a[l], INT_MAX, INT_MAX}};
		tree[idx]  = nd;
		// cout << idx << " " << nd.mn << " " << nd.ans << " " << nd.v[0][0] << "---\n";
		return;
	}
	int mid = (l + r)/2;
	build(idx*2, l, mid);
	build(idx*2+1, mid+1, r);
	// cout << idx*2 << " " << idx*2 + 1 << "\n";
	tree[idx] = merge(tree[idx*2], tree[idx*2+1]);
}

vector<int> pr;
void query(int idx, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) {
		return;
	}
	if(ql <= l and r <= qr) {
		pr.push_back(idx);
		return;
	}
	int mid = (l + r)/2;
	query(idx*2, l, mid, ql, qr), query(idx*2+1, mid+1, r, ql, qr);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while(tt--) {
		int n, q;
		cin >> n >> q;
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		
		build(1, 0, n-1);
		while(q--) {
			pr.clear();
			int l, r;
			cin >> l >> r;
			query(1, 0, n-1, --l, --r);
			// cout << pr.size() << "\n";
			Node nd = tree[pr[0]];
			for(int i = 1; i < pr.size(); i++) {
				nd = merge(nd, tree[pr[i]]);
			}
			cout << nd.ans << "\n";
		}
	}
}