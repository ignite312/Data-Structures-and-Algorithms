#include<bits/stdc++.h>
using namespace std;

struct SuffixArray {
    string s;
    vector<int> p;     // suffix array
    vector<int> c;     // equivalence classes
    vector<int> lcp;   // longest common prefix array

    SuffixArray(const string& input) {
        s = input + "$";
        build_suffix_array();
        build_lcp_array();
    }
    void radix_sort() {
        int n = p.size();
        vector<int> cnt(n, 0);
        for (auto x : c) cnt[x]++;

        vector<int> p_new(n);
        vector<int> pos(n);
        pos[0] = 0;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];

        for (auto x : p) {
            int i = c[x];
            p_new[pos[i]++] = x;
        }
        p = p_new;
    }
    void build_suffix_array() {
        int n = s.size();
        p.resize(n);
        c.resize(n);

        // k = 0
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) a[i] = {s[i], i};
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            c[p[i]] = c[p[i - 1]] + (a[i].first != a[i - 1].first);
        }

        int k = 0;
        while ((1 << k) < n) {
            for (int i = 0; i < n; i++)
                p[i] = (p[i] - (1 << k) + n) % n;

            radix_sort();

            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                c_new[p[i]] = c_new[p[i - 1]] + (now != prev);
            }
            c = c_new;
            k++;
        }
    }
    void build_lcp_array() {
        int n = s.size();
        lcp.resize(n);
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            int pi = c[i];
            int j = p[pi - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pi] = k;
            k = max(k - 1, 0);
        }
    }
    void print_suffix_array() {
        for (int x : p) cout << x << " ";
        cout << "\n";
    }
    void print_lcp_array() {
        for (int i = 1; i < lcp.size(); i++) cout << lcp[i] << " ";
        cout << "\n";
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    tt = 1;
    // cin >> tt;
    while(tt--) {
        string s;
        cin >> s;
        SuffixArray sa(s);
        sa.print_suffix_array();
        sa.print_lcp_array();
    }
    return 0;
}