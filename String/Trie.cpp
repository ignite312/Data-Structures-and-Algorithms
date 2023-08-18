#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* child[26];
    int wordCount, prefixCount, mxOccurring;
    bool isLeafNode;

    TrieNode() {
        wordCount = 0;
        prefixCount = 0;
        mxOccurring = 0;
        isLeafNode = false;
        for (int i = 0; i < 26; i++)child[i] = NULL;
    }
};
void addWord(TrieNode* root, string& word, int indx) {
    if (indx == word.length()) {
        root->isLeafNode = true;
        root->wordCount++;
        root->prefixCount++;
        root->mxOccurring = root->wordCount;
        return;
    }
    int ch = word[indx] - 'a';
    if (root->child[ch] == NULL) {
        TrieNode* newNode = new TrieNode();
        root->child[ch] = newNode;
    }
    root->prefixCount++;
    addWord(root->child[ch], word, indx + 1);
}
int prec(struct TrieNode* root) {
    for(int i = 0; i < 26; i++)
        if(root->child[i] != NULL)
            root->mxOccurring = max(root->mxOccurring, prec(root->child[i]));
    return root->mxOccurring;
}
pair<string, int> query(TrieNode* root, string &word, int mxOccurring) {
    if(root->wordCount == mxOccurring)return {word, mxOccurring};
    for(int i = 0; i < 26; i++) {
        if(root->child[i] != NULL && root->child[i]->mxOccurring == mxOccurring) {
            word.push_back(i+'a');
            return query(root->child[i], word, mxOccurring);
        }
    }
}
pair<string, int> find(TrieNode* root, string &prefix, int indx) {
    if(indx == prefix.length()) return query(root, prefix, root->mxOccurring);
    if(root->child[prefix[indx] - 'a'] == NULL)return {"", -1};
    return find(root->child[prefix[indx] - 'a'], prefix, indx+1);
}/*
bool search(TrieNode *root, string &key) {
    TrieNode* current = root;
    for (auto c : key) {
        if (current->child[c - 'a'] == NULL)
            return false;
        current = current->child[c - 'a'];
    }
    return (current->wordCount > 0);
}
bool delete_key(TrieNode* root, string& word) {
    TrieNode* current = root;
    TrieNode* lastBranchNode = NULL;
    char lastBrachChar = 'a';

    for(auto c : word) {
        if(current->child[c - 'a'] == NULL)
            return false;
        else {
            int count = 0;
            for(int i = 0; i < 26; i++)
                if(current->child[i] != NULL)
                    count++;

            if(count > 1) {
                lastBranchNode = current;
                lastBrachChar = c;
            }
            current = current->child[c - 'a'];
        }
    }
    int count = 0;
    for(int i = 0; i < 26; i++)
        if(current->child[i] != NULL)
            count++;
    if(count > 0) {
        current->wordCount--;
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
bool isLeafNode(struct TrieNode* root) {
    return root->isLeafNode != false;
}
void display(struct TrieNode* root, string word) {
    if (isLeafNode(root))cout << word << "\n";
    for (int i = 0; i < 26; i++)if(root->child[i])display(root->child[i], word + (char)(i + 'a'));
}*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    tt = 1;
    while (tt--) {
        TrieNode* root = new TrieNode();
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            addWord(root, s, 0);
        }
        prec(root);
        int q;
        cin >> q;
        while(q--) {
            string prefix;
            cin >> prefix;
            auto ans = find(root, prefix, 0);
            cout << ans.first << " " << ans.second << "\n";
        }
    }
    return 0;
}
// https://www.spoj.com/problems/TRYCOMP/
