#pragma once

#include <iostream>

using namespace std;

template<typename Key, typename Info>
class AVLTree {
    private:
        struct Node {
            Key key;
            Info info;
            short int balanceFactor;
            Node* left;
            Node* right;
            Node(const Key& _key, const Info& _info)
                : key(_key),
                info(_info),
                balanceFactor(0),
                left(nullptr),
                right(nullptr) {

            };
        };
        Node* root;
        void setRoot(Node*);
        short int max(short int a, short int b) const;
        void rotateLeft(Node*& node);
        void rotateRight(Node*& node);
        short int rebalance(Node*& subtree);
        void clear(Node* toRemove);
        void graph(const Node* subgraph, int indent = 0) const;
        bool insert(Node*&, const Key&, const Info&);
        ostream& print(ostream& os, const Node*&) const;
        stringstream& print(stringstream& os, const Node*&) const;
        void print(const Node*&) const;
        bool remove(Node*, Node*);
        void copy(const Node*&);

    public:
        AVLTree();
        AVLTree(const AVLTree<Key, Info>&);
        ~AVLTree();
        bool insert(const Key&, const Info&); ///=> updates element info if key is present
        bool remove(const Key&); /// => not present key => nothing happens => returns 0 ---- returns 1 if successfully removed elem.
        const Info& operator[](const Key&) const;
        Info& operator[](const Key&);
        bool keyExists(const Key& key) const;
        void clear();
        void graph() const { graph(root); };
        void print() const { print(const_cast<const Node*&>(root)); cout << endl; };
        ostream& print(ostream& os) const {
            os << "{";
            stringstream buffer;
            print(buffer, const_cast<const Node*&>(root)).str();
            streambuf* buf = buffer.rdbuf();
            char ch[2];
            while(buf->sgetc() != EOF) {
                if(ch[1])os << ch[1];
                if(ch[0])ch[1] = ch[0];
                ch[0] = buf->sbumpc();
            }
            os << "}";
            return os;
        };

        template<typename K, typename I>
        friend ostream& operator<<(ostream&, const AVLTree<K, I>&);
};

#include "avltree.cpp"

template<typename Key, typename Info>
ostream& operator<<(ostream& os, const AVLTree<Key, Info>& tree) {
    return tree.print(os);
}
