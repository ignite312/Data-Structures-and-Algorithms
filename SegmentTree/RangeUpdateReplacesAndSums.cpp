#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = (1 << (int)ceil(log2(2e5 + 5))) + 5;
pair<ll,ll> seg[N*4+5];
bool mark[N*4+5];

void check(int node) {
	if(mark[node]) {
		seg[node*2].first = seg[node*2+1].first = seg[node].first/2;
		seg[node*2].second = seg[node*2+1].second = 0;
		mark[node*2] = mark[node*2+1] = true;
		mark[node] = false;
	}
}
ll assign(int node, int l, int r, int i, int j, ll value) {
	if(r < i || l > j)return seg[node].first + seg[node].second*(r-l+1);
	if(l >= i && r <= j) {
		seg[node].first = (r - l + 1)*value;
		seg[node].second = 0;
		mark[node] = true;
		return seg[node].first;
	}
	check(node);
	seg[node*2].second+=seg[node].second, seg[node*2+1].second+=seg[node].second;
	seg[node].second = 0;
	int mid = l + (r - l)/2;
	return seg[node].first = assign(node*2, l, mid, i, j, value) + assign(node*2+1, mid+1, r, i, j, value);
}
void update(int node, int l, int r, int i, int j, ll value) {
	if(r < i || l > j)return;
	if(l >= i && r <= j) {
		seg[node].second+=value;
		return;
	}
	check(node);
	int len = min(r, j) - max(l, i) + 1;
	seg[node].first += len*value;
	int mid = l + (r - l)/2;
	update(node*2, l, mid, i, j, value), update(node*2+1, mid+1, r, i, j, value);
}
ll sum(int node, int l, int r, int i, int j) {
	if(r < i || l > j)return 0;
	if(l >= i && r <= j) {
		return seg[node].first + seg[node].second*(r - l + 1);
	}
	check(node);
	seg[node].first+=seg[node].second*(r - l + 1);
	seg[node*2].second+=seg[node].second;
	seg[node*2+1].second+=seg[node].second;
	seg[node].second = 0;
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
		int tn = n;
		n = (1 << (int)ceil(log2(n)));
		for(int i = 0; i < tn; i++) {
			int x;
			cin >> x;
			update(1, 0, n-1, i, i, x);
		}
		while(q--) {
			int type, a, b;
			ll x;
			cin >> type;
			if(type == 1) {
				cin >> a >> b >> x;
				update(1, 0, n-1, --a, --b, x);
			}else if(type == 2) {
				cin >> a >> b >> x;
				assign(1, 0, n-1, --a, --b, x);
			}else {
				cin >> a >> b;
				cout << sum(1, 0, n-1, --a, --b) << "\n";
			}
		}
	}
	return 0;
}
