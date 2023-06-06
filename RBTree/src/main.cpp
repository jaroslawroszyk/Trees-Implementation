#include "../include/RedBlackBinarySearchTree.hpp"
#include <iostream>

auto main() -> int
{
    RedBlackBinarySearchTree tree;

    tree.insert(8);
    tree.insert(18);
    tree.insert(5);
    tree.insert(15);
    tree.insert(17);
    tree.insert(25);
    tree.insert(40);
    tree.insert(80);
    tree.remove(8);
    tree.remove(25);
    tree.remove(80);
    tree.remove(40);

    tree.printTree();
}