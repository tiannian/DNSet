#include "tree.h"

#include <iostream>

namespace dnset {

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
