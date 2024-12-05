#include <iostream>
#include <vector>
using namespace std;

// B-Tree Node
class BTreeNode {
public:
    vector<int> keys;      // Keys in the node
    vector<BTreeNode*> children; // Children pointers
    int t;                 // Minimum degree
    bool isLeaf;           // True if the node is a leaf

    BTreeNode(int t, bool isLeaf);

    void traverse(); // Traverse all nodes in a subtree rooted at this node
    BTreeNode* search(int key); // Search for a key in the subtree rooted at this node

    void insertNonFull(int key); // Insert a new key into a non-full node
    void splitChild(int i, BTreeNode* y); // Split a full child of this node

    friend class BTree; // BTree class can access private members
};

// BTree class
class BTree {
private:
    BTreeNode* root; // Pointer to the root node
    int t;           // Minimum degree
public:
    BTree(int t);

    void traverse() {
        if (root) root->traverse();
    }

    BTreeNode* search(int key) {
        return (root ? root->search(key) : nullptr);
    }

    void insert(int key);
};

// BTreeNode constructor
BTreeNode::BTreeNode(int t, bool isLeaf) {
    this->t = t;
    this->isLeaf = isLeaf;
}

// Traverse all nodes in a subtree rooted at this node
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf) children[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!isLeaf) children[i]->traverse();
}

// Search for a key in the subtree rooted at this node
BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) i++;

    if (i < keys.size() && keys[i] == key) return this;

    if (isLeaf) return nullptr;

    return children[i]->search(key);
}

// Insert a new key into the B-Tree
void BTree::insert(int key) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = (s->keys[0] < key) ? 1 : 0;
            s->children[i]->insertNonFull(key);
            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
}

// Insert a new key into a non-full node
void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    if (isLeaf) {
        keys.push_back(0);
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
    } else {
        while (i >= 0 && keys[i] > key) i--;

        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key) i++;
        }
        children[i + 1]->insertNonFull(key);
    }
}

// Split a full child of this node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    for (int j = 0; j < t - 1; j++) z->keys.push_back(y->keys[t + j]);

    if (!y->isLeaf) {
        for (int j = 0; j < t; j++) z->children.push_back(y->children[t + j]);
    }

    y->keys.resize(t - 1);
    y->children.resize(t);

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// BTree constructor
BTree::BTree(int t) {
    this->t = t;
    root = nullptr;
}

// Main function to demonstrate B-Tree
int main() {
    int t;
    cout << "Enter the minimum degree of the B-Tree: ";
    cin >> t;

    BTree tree(t);

    cout << "Inserting keys into the B-Tree (11, 25, 3, 5, 15, 40, 9, 19):\n";
    int keys[] = {11, 25, 3, 5, 15, 40, 9, 19};
    for (int key : keys) {
        tree.insert(key);
    }

    cout << "Traversal of the B-Tree:\n";
    tree.traverse();
    cout << endl;

    int searchKey;
    cout << "Enter a key to search: ";
    cin >> searchKey;

    if (tree.search(searchKey)) {
        cout << "Key " << searchKey << " found in the B-Tree.\n";
    } else {
        cout << "Key " << searchKey << " not found in the B-Tree.\n";
    }

    return 0;
}
