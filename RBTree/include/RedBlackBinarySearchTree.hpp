#pragma once
#include "Node.hpp"
#include <memory>

class RedBlackBinarySearchTree
{
private:
    std::shared_ptr<Node> root;

    auto rotateLeft(std::shared_ptr<Node>) -> void;
    auto rotateRight(std::shared_ptr<Node>) -> void;
    auto fixInsertion(std::shared_ptr<Node>) -> void;
    auto printTreeHelper(std::shared_ptr<Node>, std::string, bool) -> void;
    auto deleteByKey(std::shared_ptr<Node>, int) -> std::shared_ptr<Node>;
    auto minimum(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto maximum(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto searchInTreeHelper(std::shared_ptr<Node>, int) -> std::shared_ptr<Node>;
    void transplant(std::shared_ptr<Node>, std::shared_ptr<Node>);
    auto preOrderHelper(std::shared_ptr<Node>) -> void;
    auto postOrderHelper(std::shared_ptr<Node>) -> void;
    auto inOrderHelper(std::shared_ptr<Node>) -> void;
    auto fixDoubleBlack(std::shared_ptr<Node>) -> void;

public:
    RedBlackBinarySearchTree();
    auto deleteTree(std::shared_ptr<Node>) -> void;
    auto inorder() -> void;
    auto insert(int) -> void;
    auto predecessor(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto preorder() -> void;
    auto postorder() -> void;
    auto remove(int) -> void;
    auto successor(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    [[maybe_unused]] auto searchInTree(int key) -> std::shared_ptr<Node>;
    [[maybe_unused]] auto getRoot() -> std::shared_ptr<Node>;
    auto printTree() -> void;
};
