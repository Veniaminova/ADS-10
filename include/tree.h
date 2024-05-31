// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <iostream>
#include <string>
#include <vector>

class Node {
 public:
    std::vector<Node*> children;
    char value;
    int count;

    explicit Node(char val) : value(val), count(1) {}

    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }

    Node* findChild(char val) {
        for (Node* child : children) {
            if (child->value == val) {
                return child;
            }
        }
        return nullptr;
    }

    void incrementCount() {
        count++;
    }
};
class Tree {
 public:
    Node* root;

    explicit Tree(const std::vector<char>& elements) {
        root = new Node('\0');
        buildTree(root, elements);
    }

    ~Tree() {
        delete root;
    }

    std::vector<std::string> getAllPermutations() const {
        std::vector<std::string> permutations;
        genPerm(root, "", &permutations);
        return permutations;
    }

    std::string getPrime(int index) const {
        std::string result;
        genPrimeHelper(root, index, result);
        return result;
    }

 private:
    void buildTree(Node* node, const std::vector<char>& elements) {
        for (char element : elements) {
           Node* child = new Node(element);
           node->children.push_back(child);
           std::vector<char> el = elements;
           auto it = std::remove(el.begin(), el.end(), element);
           el.erase(el.begin() + std::distance(el.begin(), it), el.end());
           buildTree(child, el);
        }
    }

    void genPerm(Node* n, std::string cur, std::vector<std::string>* p) const {
        if (n->children.empty()) {
            p->push_back(cur);
            return;
        }
        for (auto child : n->children) {
            genPerm(child, cur + n->value, p);
        }
    }

    void genPrimeHelper(Node* n, int& index, const std::string& result) const {
        if (n->children.empty()) {
            if (index == 0) {
                result = n->value;
            } else {
                --index;
            }
            return;
        }
        for (auto child : n->children) {
            genPrimeHelper(child, index, result);
        }
    }
};

std::vector<char> getPerm(const Tree& tree, int index);

#endif  // INCLUDE_TREE_H_
