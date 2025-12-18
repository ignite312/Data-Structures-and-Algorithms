// https://cses.fi/problemset/task/1731/
#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie* child[26];
    int word_cnt, pfx_cnt;
    bool is_leaf;

    Trie() {
        word_cnt = 0;
        pfx_cnt = 0;
        is_leaf = false;
        for(int i = 0; i < 26; i++) child[i] = NULL;
    }
};
void addWord(Trie* root, string& word, int idx) {
    if(idx == word.size()) {
        root->is_leaf = true;
        root->word_cnt++;
        root->pfx_cnt++;
        return;
    }
    int c = word[idx] - 'a';
    if(root->child[c] == NULL) {
        Trie* new_node = new Trie();
        root->child[c] = new_node;
    }
    root->pfx_cnt++;
    addWord(root->child[c], word, idx + 1);
}
/*
bool search(Trie *root, string &key) {
    Trie* cur = root;
    for(auto c : key) {
        if(cur->child[c - 'a'] == NULL)
            return false;
        cur = cur->child[c - 'a'];
    }
    return (cur->word_cnt > 0);
}
bool delete_key(Trie* root, string& word) {
    Trie* cur = root;
    Trie* lastBranchNode = NULL;
    char lastBrachChar = 'a';

    for(auto c : word) {
        if(cur->child[c - 'a'] == NULL)
            return false;
        else {
            int count = 0;
            for(int i = 0; i < 26; i++)
                if(cur->child[i] != NULL)
                    count++;

            if(count > 1) {
                lastBranchNode = cur;
                lastBrachChar = c;
            }
            cur = cur->child[c - 'a'];
        }
    }
    int count = 0;
    for(int i = 0; i < 26; i++)
        if(cur->child[i] != NULL)
            count++;
    if(count > 0) {
        cur->word_cnt--;
        return true;
    }
    if(lastBranchNode != NULL) {
        lastBranchNode->child[lastBrachChar - 'a'] = NULL;
        return true;
    }else {
        root->child[word[0] - 'a'] = NULL;
        return true;
    }
}
void del(struct Trie* root) {
    for(int i = 0; i < 26; i++)if(root->child[i])del(root->child[i]);
    delete(root);
}
bool is_leaf(struct Trie* root) {
    return root->is_leaf != false;
}
void display(struct Trie* root, string word) {
    if(is_leaf(root))cout << word << "\n";
    for(int i = 0; i < 26; i++)if(root->child[i])display(root->child[i], word + (char)(i + 'a'));
}*/

/*
// https://lightoj.com/problem/consistency-checker
void isWordPfxOfOther(struct Trie* root, bool &ok) {
    for(int i = 0; i < 10; i++)if(root->child[i]) {
        if(root->child[i]->word_cnt && root->child[i]->pfx_cnt > 1) {
            ok = false;
            return;
        }
        isWordPfxOfOther(root->child[i], ok);
    }
}
*/
const int N = 100001;
const int mod = 1e9 + 7;
int dp[N];
int solve(Trie *root, string s, int st) {
  auto cur = root;
  int count = 0;
  for(int i = st; i < (int)s.size(); i++) {
    if(cur->child[s[i]-'a'] == NULL) {
      break;
    }
    cur = cur->child[s[i]-'a'];
    if(cur->is_leaf == true) {
      count = (count + dp[i+1]) % mod;
    }
  }
  return count;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    // cin >> tt;
    while (tt--) {
        Trie* root = new Trie();
        string s;
        cin >> s;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            addWord(root, s, 0);
        }
        int sz = s.size();
        dp[sz] = 1;
        for(int i = sz-1; i >= 0; i--) {
          dp[i] = solve(root, s, i);
        }
        cout << dp[0] << "\n";
    }
    return 0;
}