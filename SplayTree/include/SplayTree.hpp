#pragma once
#include "Node.hpp"
#include <memory>
#include <string>
#include <vector>

class SplayTree
{
private:
    std::shared_ptr<Node> root;

private:
    auto rotateLeft(std::shared_ptr<Node>) -> void;
    auto rotateRight(std::shared_ptr<Node>) -> void;
    auto splay(std::shared_ptr<Node>) -> void;
    auto join(std::shared_ptr<Node>, std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto split(std::shared_ptr<Node>, std::shared_ptr<Node> &, std::shared_ptr<Node> &) -> void;
    auto printTreeHelper(std::shared_ptr<Node>, std::string, bool) -> void;
    auto preOrderHelper(std::shared_ptr<Node>) -> void;
    auto inOrderHelper(std::shared_ptr<Node>) -> void;
    auto postOrderHelper(std::shared_ptr<Node>) -> void;
    auto deleteNodeHelper(std::shared_ptr<Node>, int) -> void;
    auto searchInTreeHelper(std::shared_ptr<Node>, int) -> std::shared_ptr<Node>;

public:
    SplayTree();
    auto preorder() -> void;
    auto inorder() -> void;
    auto postorder() -> void;
    auto searchInTree(int) -> std::shared_ptr<Node>;
    auto minimum(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto maximum(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto successor(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto predecessor(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
    auto insert(int) -> void;
    auto getRoot() -> std::shared_ptr<Node>;

    auto deleteNode(int) -> void;
    auto print() -> void;

    // For charts:
    int accesses;
    int comparisons;
    int swaps;
    std::vector<int> heights;
    auto getHeight(std::shared_ptr<Node> node) -> int;
    auto getHeights() const -> const std::vector<int> &;

    auto getComparisons() const -> int;
    auto getAccesses() const -> int;
    auto getSwaps() const -> int;
};
