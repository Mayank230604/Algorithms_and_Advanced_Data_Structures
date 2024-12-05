#include <iostream>
#include <map>
#include <string>
#include <algorithm> // For transform
using namespace std;

// Node structure for the Suffix Tree
class SuffixTreeNode {
public:
    map<char, SuffixTreeNode*> children;
    int start;
    int* end;
    SuffixTreeNode* suffixLink;

    SuffixTreeNode(int start, int* end) : start(start), end(end), suffixLink(nullptr) {}
};

// Suffix Tree class
class SuffixTree {
private:
    SuffixTreeNode* root;
    string text;
    int size;

    void freeTree(SuffixTreeNode* node) {
        for (auto& child : node->children) {
            freeTree(child.second);
        }
        delete node->end;
        delete node;
    }

    void printTree(SuffixTreeNode* node, int level = 0) {
        for (auto& child : node->children) {
            for (int i = 0; i < level; i++) cout << " ";
            cout << text.substr(child.second->start, *(child.second->end) - child.second->start + 1) << "\n";
            printTree(child.second, level + 4);
        }
    }

public:
    SuffixTree(const string& str) : text(str), size(str.size()) {
        root = new SuffixTreeNode(-1, new int(-1));
        buildSuffixTree();
    }

    ~SuffixTree() {
        freeTree(root);
    }

    void buildSuffixTree() {
        for (int i = 0; i < size; i++) {
            insertSuffix(i);
        }
    }

    void insertSuffix(int suffixStart) {
        SuffixTreeNode* current = root;
        for (int i = suffixStart; i < size; i++) {
            char currentChar = text[i];
            if (current->children.find(currentChar) == current->children.end()) {
                current->children[currentChar] = new SuffixTreeNode(i, new int(size - 1));
                return;
            }
            current = current->children[currentChar];
        }
    }

    bool search(const string& pattern) {
        SuffixTreeNode* current = root;
        int i = 0;

        while (i < pattern.size()) {
            if (current->children.find(pattern[i]) == current->children.end()) {
                return false;
            }
            current = current->children[pattern[i]];
            int start = current->start;
            int end = *(current->end);

            for (int j = start; j <= end && i < pattern.size(); j++, i++) {
                if (text[j] != pattern[i]) {
                    return false;
                }
            }
        }

        return true;
    }

    void display() {
        printTree(root);
    }
};

int main() {
    string input;
    cout << "Enter the string to build the suffix tree: ";
    cin >> input;

    // Convert input to lowercase for case-insensitive matching
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    SuffixTree suffixTree(input);
    cout << "Suffix tree built successfully.\n";

    cout << "Displaying the suffix tree:\n";
    suffixTree.display();

    string pattern;
    cout << "Enter a pattern to search: ";
    cin >> pattern;

    // Convert pattern to lowercase
    transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);

    if (suffixTree.search(pattern)) {
        cout << "Pattern \"" << pattern << "\" found in the text.\n";
    } else {
        cout << "Pattern \"" << pattern << "\" not found in the text.\n";
    }

    return 0;
}
