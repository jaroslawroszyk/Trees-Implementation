#include "../include/SplayTree.hpp"
#include <iostream>
#include <memory>

SplayTree::SplayTree() : root(nullptr), accesses(0), comparisons(0), swaps(0), heights(0)
{
}

auto SplayTree::getRoot() -> std::shared_ptr<Node>
{
    return root;
}

auto SplayTree::rotateLeft(std::shared_ptr<Node> x) -> void
{

    auto y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;

    accesses += 6;
    swaps++;
}

auto SplayTree::rotateRight(std::shared_ptr<Node> x) -> void
{

    auto y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        this->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
    accesses += 6;
    swaps++;
}

auto SplayTree::splay(std::shared_ptr<Node> x) -> void
{
    while (x->parent)
    {
        if (!x->parent->parent)
        {
            if (x == x->parent->left)
            {
                rotateRight(x->parent);
            }
            else
            {
                rotateLeft(x->parent);
            }
        }
        else if (x == x->parent->left && x->parent == x->parent->parent->left)
        {
            rotateRight(x->parent->parent);
            rotateRight(x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->right)
        {
            rotateLeft(x->parent->parent);
            rotateLeft(x->parent);
        }
        else if (x == x->parent->right && x->parent == x->parent->parent->left)
        {
            rotateLeft(x->parent);
            rotateRight(x->parent);
        }
        else
        {
            rotateRight(x->parent);
            rotateLeft(x->parent);
        }
    }
}

auto SplayTree::minimum(std::shared_ptr<Node> node) -> std::shared_ptr<Node>
{
    if (node->left == nullptr)
        return node;
    return minimum(node->left);
}

auto SplayTree::maximum(std::shared_ptr<Node> node) -> std::shared_ptr<Node>
{
    if (node->right == nullptr)
        return node;
    return maximum(node->right);
}

auto SplayTree::join(std::shared_ptr<Node> leftSubtree, std::shared_ptr<Node> rightSubtree) -> std::shared_ptr<Node>
{
    if (not leftSubtree || not rightSubtree)
        return leftSubtree ? leftSubtree : rightSubtree;

    auto x = maximum(leftSubtree);
    splay(x);
    x->right = rightSubtree;
    x->parent = x;
    accesses += 3;
    swaps++;

    return x;
}

auto SplayTree::split(std::shared_ptr<Node> x, std::shared_ptr<Node> &leftSubtree, std::shared_ptr<Node> &rightSubtree) -> void
{
    splay(x);
    if (x->right)
    {
        rightSubtree = x->right;
        rightSubtree->parent = nullptr;
        accesses += 2;
    }
    else
    {
        rightSubtree = nullptr;
        accesses++;
    }
    leftSubtree = x;
    leftSubtree->right = nullptr;
    if (rightSubtree)
    {
        rightSubtree->parent = nullptr;
        accesses++;
    }
}

auto SplayTree::printTreeHelper(std::shared_ptr<Node> root, std::string indent, bool last) -> void
{
    if (root != nullptr)
    {
        std::cout << indent;
        if (last)
        {
            std::cout << "R----";
            indent += "     ";
        }
        else
        {
            std::cout << "L----";
            indent += "|    ";
        }

        std::cout << root->data << std::endl;
        printTreeHelper(root->left, indent, false);
        printTreeHelper(root->right, indent, true);
    }
}

auto SplayTree::print() -> void
{
    if (root)
    {
        printTreeHelper(root, "", true);
    }
}

auto SplayTree::insert(int key) -> void
{
    auto node = std::make_shared<Node>(key);
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    std::shared_ptr<Node> y = nullptr;
    auto x = this->root;

    while (x != nullptr)
    {
        y = x;
        if (node->data < x->data)
        {
            x = x->left;
            comparisons++;
        }
        else
        {
            x = x->right;
            comparisons++;
        }
        accesses++;
    }

    node->parent = y;
    if (y == nullptr)
    {
        root = node;
    }
    else if (node->data < y->data)
    {
        y->left = node;
    }
    else
    {
        y->right = node;
    }

    splay(node);
    heights.push_back(getHeight(root));
}

auto SplayTree::preOrderHelper(std::shared_ptr<Node> node) -> void
{
    if (node != nullptr)
    {
        std::cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

auto SplayTree::preorder() -> void
{
    preOrderHelper(root);
}

auto SplayTree::inOrderHelper(std::shared_ptr<Node> node) -> void
{
    if (node != nullptr)
    {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

auto SplayTree::inorder() -> void
{
    inOrderHelper(root);
}

auto SplayTree::postOrderHelper(std::shared_ptr<Node> node) -> void
{
    if (node != nullptr)
    {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->data << " ";
    }
}

auto SplayTree::postorder() -> void
{
    postOrderHelper(root);
}

auto SplayTree::searchInTreeHelper(std::shared_ptr<Node> node, int key) -> std::shared_ptr<Node>
{
    if (node == nullptr || key == node->data)
    {
        return node;
    }

    if (key < node->data)
    {
        return searchInTreeHelper(node->left, key);
    }
    return searchInTreeHelper(node->right, key);
}

auto SplayTree::searchInTree(int key) -> std::shared_ptr<Node>
{
    auto x = searchInTreeHelper(root, key);
    if (x)
    {
        splay(x);
    }
    return x;
}

auto SplayTree::successor(std::shared_ptr<Node> x) -> std::shared_ptr<Node>
{
    if (x->right != nullptr)
    {
        return minimum(x->right);
    }

    auto y = x->parent;
    while (y != nullptr and x == y->right)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

auto SplayTree::predecessor(std::shared_ptr<Node> x) -> std::shared_ptr<Node>
{
    if (x->left != nullptr)
    {
        return maximum(x->left);
    }

    auto y = x->parent;
    while (y != nullptr && x == y->left)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

auto SplayTree::deleteNodeHelper(std::shared_ptr<Node> node, int key) -> void
{
    std::shared_ptr<Node> x = nullptr;
    std::shared_ptr<Node> t, s;
    std::shared_ptr<Node> currentNode = node;
    while (currentNode != nullptr)
    {
        if (currentNode->data == key)
        {
            x = currentNode;
            break;
        }

        if (currentNode->data < key)
        {
            currentNode = currentNode->right;
            comparisons++;
        }
        else
        {
            currentNode = currentNode->left;
            comparisons++;
        }
        accesses++;
    }

    if (x == nullptr)
    {
        std::cout << "Couldn't find key in the tree" << std::endl;
        return;
    }

    splay(x);

    if (!x->left)
    {
        root = x->right;
        if (root)
        {
            root->parent = nullptr;
            accesses++;
        }
        return;
    }
    else if (!x->right)
    {
        root = x->left;
        if (root)
        {
            root->parent = nullptr;
            accesses++;
        }
        return;
    }

    auto maxLeft = maximum(x->left);
    splay(maxLeft);
    maxLeft->right = x->right;
    if (maxLeft->right)
    {
        maxLeft->right->parent = maxLeft;
        accesses++;
    }
    root = maxLeft;
    root->parent = nullptr;
}

auto SplayTree::deleteNode(int data) -> void
{
    deleteNodeHelper(root, data);
}

auto SplayTree::getHeight(std::shared_ptr<Node> node) -> int
{
    if (node == nullptr)
        return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

auto SplayTree::getHeights() const -> const std::vector<int> &
{
    return heights;
}
auto SplayTree::getComparisons() const -> int { return comparisons; }
auto SplayTree::getAccesses() const -> int { return accesses; }
auto SplayTree::getSwaps() const -> int { return swaps; }