#include <ctime>
#include <iostream>
#include <random>
#include <stack>

class Node {
 public:
  int data;
  Node* left;
  Node* right;

  void insert(Node* node) {
    if (node->data > this->data) {
      if (this->right != nullptr) {
        this->right->insert(node);
      } else {
        this->right = node;
      }
    }

    if (node->data < this->data) {
      if (this->left != nullptr) {
        this->left->insert(node);
      } else {
        this->left = node;
      }
    }

    if (node->data == this->data) return;
  }
};

class Dfs {
 public:
  static void print(Node* node) {
    if (node == nullptr) return;
    std::cout << node->data << "\n";
    print(node->left);
    print(node->right);
  }
  static bool search(int target, Node* node) {
    if (node == nullptr) return false;

    if (node->data == target) return true;

    if (target < node->data) {
      return search(target, node->left);
    } else {
      return search(target, node->right);
    }
  }
};

class Tree {
 private:
  std::stack<Node*> unvisited;

 public:
  Node* root;
  Tree(int num) {
    root = new Node;

    root->data = num;
    root->left = nullptr;
    root->right = nullptr;
  }
  void insertNode(Node* node) { root->insert(node); }

  void printTree() { Dfs::print(root); }
};

int main() {
  int n;
  std::cin >> n;
  Tree binaryTree(5);
  srand(time(0));

  int count = 0;

  for (int i = 0; i < n; i++) {
    int random = rand() % (n + 1);

    if (Dfs::search(random, binaryTree.root)) {
      count++;
      i--;
      continue;
    }
    
    Node* node = new Node;

    node->data = random;
    // std::cout << node->data << " ";

    binaryTree.insertNode(node);
  }

  binaryTree.printTree();

  std::cout << "count : " << count << "\n";
}