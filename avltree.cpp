#pragma once
#include <iomanip>

#include "avltree.h"

template<typename Key, typename Info>
void AVLTree<Key, Info>::setRoot(Node* r) {
    root = r;
}

template<typename Key, typename Info>
short int AVLTree<Key, Info>::rebalance(Node*& subtree) {
    if(!subtree) {
        return 0;
    }
    short int lheight = rebalance(subtree->left);
    short int rheight = rebalance(subtree->right);

    subtree->balanceFactor = rheight - lheight;
    if(subtree->balanceFactor == 2 && subtree->right->balanceFactor == 0) {
        ///lr
        rotateLeft(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == -2 && subtree->left->balanceFactor == 0) {
        ///lr
        rotateRight(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == 2 && subtree->right->balanceFactor == 1) {
        ///rr
        rotateLeft(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == 2 && subtree->right->balanceFactor == -1) {
        ///rl
        rotateRight(subtree->right);
        rotateLeft(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == -2 && subtree->left->balanceFactor == -1) {
        ///ll
        rotateRight(subtree);
        return rebalance(subtree);
    }
    if(subtree->balanceFactor == -2 && subtree->left->balanceFactor == 1) {
        ///lr
        rotateLeft(subtree->left);
        rotateRight(subtree);
        return rebalance(subtree);
    }
    return max(lheight, rheight) + 1;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::rotateRight(Node*& node) {
    Node* tmp = node;
    Node* tmp2 = tmp->left;
    tmp->left = tmp->left->right;
    tmp2->right = tmp;
    node = tmp2;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::rotateLeft(Node*& node) {
    Node* tmp = node;
    Node* tmp2 = tmp->right;
    tmp->right = tmp->right->left;
    tmp2->left = tmp;
    node = tmp2;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::graph(const Node* subgraph, int indent) const {
    if(subgraph) {
        graph(subgraph->right, indent + 8);
        std::cout << setw(indent) << " " << subgraph->key << " " << subgraph->balanceFactor << endl;
        graph(subgraph->left, indent + 8);
    } else {
        std::cout << setw(indent) << " \n";
    }
}

template<typename Key, typename Info>
AVLTree<Key, Info>::AVLTree() : root(nullptr) {

}

template<typename Key, typename Info>
AVLTree<Key, Info>::AVLTree(const AVLTree<Key, Info>& toCopy) {
    root = nullptr;
    clear();
    this->copy(const_cast<const Node*&>(toCopy.root));
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::copy(const Node*& toCopy) {
    if(toCopy){
        insert(this->root, toCopy->key, toCopy->info);
        copy(const_cast<const Node*&>(toCopy->left));
        copy(const_cast<const Node*&>(toCopy->right));
    }
}

template<typename Key, typename Info>
AVLTree<Key, Info>::~AVLTree() {
    clear();
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::insert(const Key& key, const Info& info) {
    return insert(root, key, info);
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::insert(Node*& root, const Key& key, const Info& info) {
    if(!root) {
        root = new Node(key, info);
        rebalance(this->root);
        return true;
    }
    if(key > root->key){
        insert(root->right, key, info);
    } else if(key < root->key) {
        insert(root->left, key, info);
    } else {
        root->info = info;
        return true;
    }
    return false;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::clear() {
    clear(root);
    root = nullptr;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::clear(Node* node) {
    if(node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename Info>
short int AVLTree<Key, Info>::max(short int a, short int b) const {
     if ( a < b )
        return b;
     return a;
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::keyExists(const Key& key) const {
    Node* node = root;
    while(node) {
        if(key == node->key) return true;
        else if(key > node->key) node = node->right;
        else if(key < node->key) node = node->left;
    }
    return false;
}

template<typename Key, typename Info>
const Info& AVLTree<Key, Info>::operator[](const Key& key) const {
    Node* node = root;
    while(node) {
        if(key == node->key) return const_cast<const Info&>(node->info);
        else if(key > node->key) node = node->right;
        else if(key < node->key) node = node->left;
    }
    throw "Key Not Found";
}

template<typename Key, typename Info>
Info& AVLTree<Key, Info>::operator[](const Key& key) {
    Node* node = root;
    while(node) {
        if(key == node->key) return node->info;
        else if(key > node->key) node = node->right;
        else if(key < node->key) node = node->left;
    }
    throw "Key Not Found";
}

template<typename Key, typename Info>
ostream& AVLTree<Key, Info>::print(ostream& os, const Node*& node) const {
    if(node) {
        print(os, const_cast<const Node*&>(node->left));
        os << "(" << node->key << ", " << node->info << ")";
        print(os, const_cast<const Node*&>(node->right));
    }
    return os;
}

template<typename Key, typename Info>
stringstream& AVLTree<Key, Info>::print(stringstream& os, const Node*& node) const {
    if(node) {
        print(os, const_cast<const Node*&>(node->left));
        os << node->key << ": " << node->info << ", ";
        print(os, const_cast<const Node*&>(node->right));
    }
    return os;
}

template<typename Key, typename Info>
void AVLTree<Key, Info>::print(const Node*& node) const {
    if(node) {
        print(const_cast<const Node*&>(node->left));
        cout << "(" << node->key << ", " << node->info << ")";
        print(const_cast<const Node*&>(node->right));
    }
}

template<typename Key, typename Info>
bool AVLTree<Key, Info>::remove(const Key& key) {
    Node* toDelete = root;
    Node* toDeleteParent = nullptr;
    while(toDelete) {
        if(key < toDelete->key) {
            toDeleteParent = toDelete;
            toDelete = toDelete->left;
        } else if(key > toDelete->key) {
            toDeleteParent = toDelete;
            toDelete = toDelete->right;
        } else {
            return remove(toDelete, toDeleteParent);
        }
    }
    return false;
};

template<typename Key, typename Info>
bool AVLTree<Key, Info>::remove(Node* toDelete, Node* toDeleteParent) {
    if(toDelete->left && toDelete->right) { ///2 children
        Node* toSwap = toDelete->right;
        toDeleteParent = toDelete;
        while (toSwap->left != nullptr) {
            toDeleteParent = toSwap;
            toSwap = toSwap->left;
        }
        toDelete->key = toSwap->key;
        toDelete->info = toSwap->info;
        toDelete = toSwap;
    }
    Node* subtree = toDelete->left;
    if(!subtree){
        subtree = toDelete->right;
    }
    if(!toDeleteParent){
        root = subtree;
    }
    else if(toDeleteParent->left == toDelete)
        toDeleteParent->left = subtree;
    else
        toDeleteParent->right = subtree;

    delete toDelete;
    rebalance(root);
    return true;
};

