#include<bits/stdc++.h>
using namespace std;
const int N = 1e7;
const int Mx = 33554431;
int tree[Mx], buckets[N];
map<int, int> freq;

int bucketNumber(int x) {
    if (x % 100 == 0){x--;}
    return x / 100;
}
/*
int calculateSize(int n) {
    int pw = 1;
    while (pw < n)pw = pw << 1;
    return 2 * pw - 1;
}
*/
void build() {
    int extra = Mx / 2 + 1 - N;
    int n = N;
    for (int i = Mx - 1; i >= 0; i--) {
        if (extra) {
            tree[i] = 0;
            extra--;
        }else if (n) {
            tree[i] = buckets[n - 1];
            n--;
        }else tree[i] = tree[i * 2 + 1] + tree[i * 2 + 2];
    }
}
void update(int idx, int value) {
    idx = Mx / 2 + idx;
    tree[idx] = value;
    while ((idx - 1) / 2 >= 0) {
        idx = (idx - 1) / 2;
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
        if (!idx) break;
    }
}
int sum(int node, int l, int r, int i, int j) {
    if (r < i || l > j) return 0;
    if (l >= i && r <= j) return tree[node];
    int mid = l + (r - l) / 2;
    return sum(node * 2 + 1, l, mid, i, j) + sum(node * 2 + 2, mid + 1, r, i, j);
}
int partialSum(int lo, int hi) {
    int res = 0;
    auto it = freq.lower_bound(lo);
    while (it != freq.end() && it->first <= hi) {
        res += it->second;
        it++;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while (tt--) {
        int n, q;
        cin >> n >> q;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            int idx = bucketNumber(arr[i]);
            buckets[idx]++;
            freq[arr[i]]++;
        }
        build();
        while (q--) {
            char type;
            int i, j;
            cin >> type >> i >> j;
            if (type == '!') {
                i--;
                int past_salary = arr[i];
                arr[i] = j;
                int past_bucket = bucketNumber(past_salary);
                int new_bucket = bucketNumber(j);
                buckets[past_bucket]--;
                buckets[new_bucket]++;
                freq[past_salary]--, freq[j]++;
                update(past_bucket, buckets[past_bucket]);
                update(new_bucket, buckets[new_bucket]);
            } else {
                int left_bucket = bucketNumber(i);
                int right_bucket = bucketNumber(j);

                int ans = sum(0, 0, Mx / 2, left_bucket+1, right_bucket-1);
                ans += partialSum(i, min((left_bucket+1) * 100, j));
                if (left_bucket != right_bucket) ans += partialSum(right_bucket*100 + 1, j);
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
// https://cses.fi/problemset/task/1144
