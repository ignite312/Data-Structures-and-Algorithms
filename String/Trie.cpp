#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* child[26];
    int wordCount, prefixCount;

    TrieNode() {
        wordCount = 0;
        prefixCount = 0;
        for (int i = 0; i < 26; i++)child[i] = NULL;
    }
};
void insert_key(TrieNode *root, string &key) {
    TrieNode* current = root;
    for (int i = 0; i < (int)key.length(); i++) {
        if (current->child[key[i] - 'a'] == NULL) {
            TrieNode* newNode = new TrieNode();
            current->child[key[i] - 'a'] = newNode;
        }
        current = current->child[key[i] - 'a'];
        current->prefixCount++;
    }
    current->wordCount++;
}
bool search_key(TrieNode *root, string &key) {
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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--) {
        TrieNode* root = new TrieNode();
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            string s;
            cin >> s;
            insert_key(root, s);
        }
        string s = "aaaaaaaa";
        if(search_key(root, s))cout << "Found!";
        delete_key(root, s);
        if(search_key(root, s))cout << "Found!";
    }
}
// https://www.geeksforgeeks.org/introduction-to-trie-data-structure-and-algorithm-tutorials/
