#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
  int val;
  TreeNode * left, * right;

  TreeNode(int val): val(val), left(nullptr), right(nullptr) {}
};

/* Traversals */
void inorder(TreeNode * root) {
  if (!root) return;
  inorder(root -> left);
  cout << root -> val << " ";
  inorder(root -> right);
}

void preorder(TreeNode * root) {
  if (!root) return;
  cout << root -> val << " ";
  preorder(root -> left);
  preorder(root -> right);
}

void postorder(TreeNode * root) {
  if (!root) return;
  postorder(root -> left);
  postorder(root -> right);
  cout << root -> val << " ";
}

int height(TreeNode * root) {
  if (!root) return 0;
  return 1 + max(height(root -> left), height(root -> right));
}

bool isSameTree(TreeNode * p, TreeNode * q) {
  if (p == nullptr and q == nullptr) return true;
  if (p == nullptr || q == nullptr) return false;
  if (p -> val != q -> val) return false;
  return isSameTree(p -> left, q -> left) and isSameTree(p -> right, q -> right);
}

bool isFullBinaryTree(TreeNode * root) {
  if (root == nullptr)
    return true;

  // If exactly one child exists → not full
  if ((root -> left == nullptr && root -> right != nullptr) ||
    (root -> left != nullptr && root -> right == nullptr))
    return false;

  return isFullBinaryTree(root -> left) &&
    isFullBinaryTree(root -> right);
}

bool isCompleteBinaryTree(TreeNode * root) {
  if (!root) return true;

  queue < TreeNode * > q;
  q.push(root);
  bool flag = false; // indicates we have seen a missing child

  while (!q.empty()) {
    TreeNode * node = q.front();
    q.pop();

    // Left child
    if (node -> left) {
      if (flag) return false; // found a child after missing node
      q.push(node -> left);
    } else {
      flag = true; // left child missing
    }

    // Right child
    if (node -> right) {
      if (flag) return false; // found a child after missing node
      q.push(node -> right);
    } else {
      flag = true; // right child missing
    }
  }

  return true;
}

int depth(TreeNode * root) {
  if (root == nullptr)
    return 0;
  return 1 + depth(root -> left);
}

bool isPerfect(TreeNode * root, int depth, int level = 1) {
  if (root == nullptr)
    return true;

  // Leaf node
  if (root -> left == nullptr && root -> right == nullptr)
    return depth == level;

  // Internal node must have two children
  if (root -> left == nullptr || root -> right == nullptr)
    return false;

  return isPerfect(root -> left, depth, level + 1) &&
    isPerfect(root -> right, depth, level + 1);
}

bool isPerfectBinaryTree(TreeNode * root) {
  return isPerfect(root, depth(root));
}

bool isLeftSkewed(TreeNode * root) {
  if (!root) return true;
  if (root -> right) return false;
  return isLeftSkewed(root -> left);
}

bool isRightSkewed(TreeNode * root) {
  if (!root) return true;
  if (root -> left) return false;
  return isRightSkewed(root -> right);
}

/* BST operations */
TreeNode * insertNode(TreeNode * root, int key) {
  if (!root) return new TreeNode(key);

  if (key < root -> val)
    root -> left = insertNode(root -> left, key);
  else
    root -> right = insertNode(root -> right, key);

  return root;
}

TreeNode * inorderSuccessor(TreeNode * root) {
  while (root && root -> left)
    root = root -> left;
  return root;
}

TreeNode * search(TreeNode * root, int key) {
  if (!root || root -> val == key) return root;
  if (key > root -> val) return search(root -> right, key);
  return search(root -> left, key);
}

TreeNode * deleteNode(TreeNode * root, int key) {
  if (!root) return nullptr;

  if (key < root -> val)
    root -> left = deleteNode(root -> left, key);
  else if (key > root -> val)
    root -> right = deleteNode(root -> right, key);
  else {
    // One or zero child
    if (!root -> left) {
      TreeNode * temp = root -> right;
      delete root;
      return temp;
    }
    if (!root -> right) {
      TreeNode * temp = root -> left;
      delete root;
      return temp;
    }

    // Two children
    TreeNode * temp = inorderSuccessor(root -> right);
    root -> val = temp -> val;
    root -> right = deleteNode(root -> right, temp -> val);
  }
  return root;
}

int main() {
  TreeNode * root = new TreeNode(1);
  root -> left = new TreeNode(2);
  root -> right = new TreeNode(3);
  cout << isPerfectBinaryTree(root) << "\n";

  inorder(root);
  cout << "\n";
  preorder(root);
  cout << "\n";
  postorder(root);
  cout << "\n";

  root = deleteNode(root, 10);

  inorder(root);
  cout << "\n";
  preorder(root);
  cout << "\n";
  postorder(root);
  cout << "\n";

  cout << (search(root, 12) ? "Found" : "Not Found") << "\n";
}