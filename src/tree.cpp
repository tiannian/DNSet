#include "tree.h"

#include <iostream>

namespace dnset {

void Tree::addNode(const std::vector<T> &p) {
    auto &curr = data;
    for (auto &x: p) {
        // find target
        auto fr = curr.children.find();
        if (fr = curr.children.end()) {
            TreeNode buffer(x);
            curr.children.insert(buffer);
            curr = buffer;
        } else {
            curr = *fr;
        }
    }
}

void Tree::delNode(const std::vector<T> &p) {
    
}

bool Tree::hasNode(const std::vector<T> &p) {
    
}

void Tree::print(TreeNode<T> &d) {
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