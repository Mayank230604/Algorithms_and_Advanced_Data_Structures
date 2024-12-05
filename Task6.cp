#include <iostream>
using namespace std;

// Define a Node structure for the tree
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Class for the Binary Search Tree
class BinarySearchTree {
private:
    TreeNode* root;

    // Helper function for insertion
    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    // Helper function for searching
    bool search(TreeNode* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->value) {
            return true;
        } else if (value < node->value) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    // Helper function for inorder traversal (optional)
    void inorder(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        inorder(node->left);
        cout << node->value << " ";
        inorder(node->right);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // Public insert function
    void insert(int value) {
        root = insert(root, value);
    }

    // Public search function
    bool search(int value) {
        return search(root, value);
    }

    // Public function to display the tree (optional)
    void display() {
        inorder(root);
        cout << endl;
    }
};

// Main function to demonstrate the tree
int main() {
    BinarySearchTree tree;

    cout << "Inserting values: 50, 30, 70, 20, 40, 60, 80\n";
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Tree (in-order traversal): ";
    tree.display();

    int searchValue;
    cout << "Enter a value to search: ";
    cin >> searchValue;

    if (tree.search(searchValue)) {
        cout << "Value " << searchValue << " is found in the tree.\n";
    } else {
        cout << "Value " << searchValue << " is not found in the tree.\n";
    }

    return 0;
}
