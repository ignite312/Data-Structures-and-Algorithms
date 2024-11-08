#include<bits/stdc++.h>
using namespace std;
#define ll long long 

vector<string> permutation(string s) {
    sort(s.begin(), s.end());
    vector<string> ans;
    do {
        ans.push_back(s);
    }while(next_permutation(s.begin(), s.end()));
    return ans;
}
vector<string> combination(int n, int k) {
    vector<string> ans;
    for(int mask = 0; mask < (1 << n); mask++) {
        if(__builtin_popcount(mask) != k)continue;
        string s = "";
        for(int i = 0; i < n; i++) if(mask & (1 << i))s+=to_string(i+1);
            ans.push_back(s);
    }
    return ans;
}
void combination2(vector<vector<int> >& ans,
    vector<int>& tmp, int n, int left, int k) {
    if (k == 0) {
        ans.push_back(tmp);
        return;
    }
    for (int i = left; i <= n; ++i) {
        tmp.push_back(i);
        combination2(ans, tmp, n, i + 1, k - 1);
        tmp.pop_back();
    }
}
vector<vector<int> > makeCombi(int n, int k) {
    vector<vector<int> > ans;
    vector<int> tmp;
    combination2(ans, tmp, n, 1, k);
    return ans;
}
ll nPr(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }
    ll result = 1;
    for (int i = 0; i < r; ++i) {
        result *= n--;
    }
    return result;
}
ll nCr(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }
    ll result = 1;
    for(int i = 1; i <= r; ++i) {
        result *= n--;
        result /= i;
    }
    return result;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while(tt--) {
        vector<string> combinations = combination(8, 4);
        for(auto ele : combinations){cout << ele << "\n";}
            cout << "\n";

        string s = "12345";
        vector<string> permutations = permutation(s);
        for(auto ele : permutations){cout << ele << "\n";}
    }
    return 0;
}