#include "bst.h"
#include <vector>
#include <queue>
#include <iomanip>
BST::Node::Node(int value, Node* left, Node* right)
: value(value), left(left), right(right){}

BST::Node::Node()
: value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node& node)
: value(node.value), left(node.left), right(node.right) {}

BST::Node::~Node(){
    
}

std::ostream& operator<<(std::ostream &out, const BST::Node& node){
    out << std::left << std::setw(17) << &node << "=> value:" << std::left << std::setw(10) << node.value << "left:" << std::left << std::setw(16) << node.left << "right:" << std::left << std::setw(17) << node.right << std::endl;
    return out;
}

bool operator==(int i, const BST::Node& node){
    return node.value == i;
}

bool operator!=(int i, const BST::Node& node){
    return !(i == node);
}

bool operator<(int i, const BST::Node& node){
    return i < node.value;
}

bool operator>=(int i, const BST::Node& node){
    return !(i < node);
}

bool operator>(int i, const BST::Node& node){
    return i > node.value;
}

bool operator<=(int i, const BST::Node& node){
    return !(i > node);
}

bool operator==(const BST::Node& node, int i){
    return i == node;
}

bool operator!=(const BST::Node& node, int i){
    return !(i == node);
}

bool operator<(const BST::Node& node, int i){
    return i > node;
}

bool operator>=(const BST::Node& node, int i){
    return i <= node;
}

bool operator>(const BST::Node& node, int i){
    return i < node;
}

bool operator<=(const BST::Node& node, int i){
    return i >= node;
}

BST::BST()
: root(nullptr) {}

BST::Node* copyTree(BST::Node* root) {
    if (root == nullptr)
        return nullptr;
    BST::Node* newRoot = new BST::Node(root->value, nullptr, nullptr);
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);
    return newRoot;
}

BST::BST(const BST& b) {
    if (b.root == nullptr)
        this->root = nullptr;
    this->root = copyTree(b.root);
}

BST::BST(BST &&bst)
: root(bst.root) {
    bst.root = nullptr;
}

BST::BST(std::initializer_list<int> list){
    this->root = nullptr;
    for (int i : list){
        this->add_node(i);
    }
}

BST::~BST(){
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for(auto& node: nodes)
        delete node;
}

BST::Node*& BST::get_root(){
    return root;
}

void BST::bfs(std::function<void(BST::Node*& node)> func){
    if (root == nullptr)
        return;
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()){
        Node *tmp = q.front();
        q.pop();
        func(tmp);
        if (tmp->left != nullptr)
            q.push(tmp->left);
        if (tmp->right != nullptr)
            q.push(tmp->right);
    }
}

size_t BST::length(){
    size_t length{0};
    std::function<void(BST::Node * &node)> func = [&](BST::Node *&node) -> void
    {
        length++;
    };
    bfs(func);
    return length;
}

bool add_node_helper(int value, BST::Node *&node){
    if (node == nullptr){
        node = new BST::Node(value, nullptr, nullptr);
        return true;
    }
    if (value == node->value){
        return false;
    }
    else if (value < node->value){
        return add_node_helper(value, node->left);
    }
    else{
        return add_node_helper(value, node->right);
    }
}

bool BST::add_node(int value){
    return add_node_helper(value, root);
}

BST::Node** find_node_helper(int value, BST::Node *&node){
    if (node == nullptr)
        return nullptr;
    if (value < node->value)
        return find_node_helper(value, node->left);
    else if (value > node->value)
        return find_node_helper(value, node->right);
    else
        return &node;
}

BST::Node** BST::find_node(int value){
    return find_node_helper(value, root);
}

BST::Node** find_parent_helper(int value, BST::Node *&node, BST::Node *&parent){
    if (node == nullptr)
        return nullptr;
    if (value < node->value)
        return find_parent_helper(value, node->left, node);
    else if (value > node->value)
        return find_parent_helper(value, node->right, node);
    else
        return &parent;
}

BST::Node** BST::find_parrent(int value){
    return find_parent_helper(value, root, root);
}

BST::Node** find_successor_helper(BST::Node *&node){
    if (node->right == nullptr)
        return &node;
    return find_successor_helper(node->right);
}

BST::Node** BST::find_successor(int value) {
    if (root == nullptr)
        return nullptr;
    auto b = find_node(value);
    if (b == nullptr || (*b)->left == nullptr) {
        return nullptr;
    }
    return find_successor_helper((*b)->left);
}

BST::Node* find_max(BST::Node *node){
    if (node->right == nullptr)
        return node;
    return find_max(node->right);
}

BST::Node* delete_node_helper(int value, BST::Node *&node){
    if (node == nullptr)
        return nullptr;
    if (value < node->value){
        node->left = delete_node_helper(value, node->left);
        return node;
    }
    else if (value > node->value){
        node->right = delete_node_helper(value, node->right);
        return node;
    }
    else{
        if (node->left != nullptr && node->right != nullptr){
            BST::Node *tmp = find_max(node->left);
            node->value = tmp->value;
            node->left = delete_node_helper(tmp->value, node->left);
        }
        else{
            BST::Node *tmp = node;
            if (node->left == nullptr)
                node = node->right;
            else
                node = node->left;
            delete tmp;
        }
        return node;
    }
}

bool BST::delete_node(int value){
    if (find_node(value) == nullptr)
        return false;
    root = delete_node_helper(value, root);
    return true;
}

std::ostream &operator<<(std::ostream &out, const BST &bst){
    out << "********************************************************************************" << std::endl;
    std::function<void(BST::Node * &node)> func = [&](BST::Node *&node) -> void
    {
        out << *node;
    };
    ((BST)bst).bfs(func);
    out << "binary search tree size: " << ((BST)bst).length() << std::endl;
    out << "********************************************************************************" << std::endl;
    return out;
}

BST& BST::operator++(){
    std::function<void(BST::Node * &node)> add = [](BST::Node *&node) -> void
    {
        node->value++;
    };
    this->bfs(add);
    return *this;
}

BST BST::operator++(int){
    BST tmp{*this};
    std::function<void(BST::Node * &node)> add = [](BST::Node *&node) -> void
    {
        node->value++;
    };
    this->bfs(add);
    return tmp;
}

BST& BST::operator=(const BST &bst){
    this->root = copyTree(bst.root);
    return *this;
}

BST& BST::operator=(BST &&bst){
    this->root = bst.root;
    bst.root = nullptr;
    return *this;
}