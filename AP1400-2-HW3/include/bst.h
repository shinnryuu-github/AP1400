#ifndef BST_H
#define BST_H

#include <functional>
#include <iostream>

class Node;

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;
    };
    BST();
    BST(const BST &bst);
    BST(BST &&bst);
    BST(std::initializer_list<int> list);
    ~BST();
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST &operator++();
    BST operator++(int);
    BST &operator=(const BST &bst);
    BST &operator=(BST && bst);
    friend std::ostream &operator<<(std::ostream &out, const BST &bst);

private:
    Node* root;
};

std::ostream& operator<<(std::ostream &out, const BST::Node& node);
bool operator==(int i, const BST::Node &node);
bool operator!=(int i, const BST::Node &node);
bool operator<(int i, const BST::Node &node);
bool operator>=(int i, const BST::Node &node);
bool operator>(int i, const BST::Node &node);
bool operator<=(int i, const BST::Node &node);
bool operator==(const BST::Node &node, int i);
bool operator!=(const BST::Node &node, int i);
bool operator<(const BST::Node &node, int i);
bool operator>=(const BST::Node &node, int i);
bool operator>(const BST::Node &node, int i);
bool operator<=(const BST::Node &node, int i);

#endif //BST_H