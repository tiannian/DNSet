#ifndef _TREE_H
#define _TREE_H

#include <set>
#include <vector>
namespace dnset {

template<typename T>
class TreeNode {
    public:
        TreeNode() = default;
        TreeNode(const TreeNode &) = default;
        TreeNode(T &d): data(d) {}
        ~TreeNode() = default;
        
        T data;
        std::set<TreeNode<T>>children;
        bool operator<(const TreeNode &other) const {
            return data < other.data;
        }
};

template<typename T>
class Tree {
    public:
        Tree() = default;
        Tree(const Tree &) = default;
        ~Tree() = default;
    
    public:
        void addNode(const std::vector<T> &p);
        void delNode(const std::vector<T> &p);
        bool hasNode(const std::vector<T> &p);
    
    public:
        void dump() {print(data);}
    private:
        void print(TreeNode<T> &d);

    private:
        TreeNode<T> data;
};

template<typename T>
void Tree<T>::addNode(const std::vector<T> &p) {
    auto &curr = data;
    for (auto &x: p) {
        // find target
        auto fr = curr.children.find();
        if (fr = curr.children.end()) {
            TreeNode<T> buffer(x);
            curr.children.insert(buffer);
            curr = buffer;
        } else {
            curr = *fr;
        }
    }
}

template<typename T>
void Tree<T>::delNode(const std::vector<T> &p) {
    
}

template<typename T>
bool Tree<T>::hasNode(const std::vector<T> &p) {
    return true;
}

template<typename T>
void Tree<T>::print(TreeNode<T> &d) {
    std::cout << "current node is " << d.data ;
    std::cout << "children node are ";
    for (auto &x: d.children) {
        std::cout << x.data << " ";
    }
    std::cout << std::endl;
    for (auto &x: d.children) {
        print(x);
    }
}

}

#endif
