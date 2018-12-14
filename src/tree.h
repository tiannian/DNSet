#ifndef _TREE_H
#define _TREE_H

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
        bool operator<(const Node &other) const {
            return data < other.data;
        }
}

template<typename T>
class Tree {
    public:
        Tree() = default;
        Tree(const Tree &) = default;
        ~Tree() = delete;
    
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
}
    
}

#endif