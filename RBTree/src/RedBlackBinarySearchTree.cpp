#include "../include/RedBlackBinarySearchTree.hpp"
#include <iostream>
#include <memory>

RedBlackBinarySearchTree::RedBlackBinarySearchTree() : root(nullptr)
{
}

auto RedBlackBinarySearchTree::rotateLeft(std::shared_ptr<Node> x) -> void
{
    auto y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

auto RedBlackBinarySearchTree::rotateRight(std::shared_ptr<Node> x) -> void
{
    auto y = x->left;
    x->left = y->right;

    if (y->right != nullptr)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

auto RedBlackBinarySearchTree::fixInsertion(std::shared_ptr<Node> z) -> void
{
    while (z->parent != nullptr && z->parent->color == Color::RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            auto y = z->parent->parent->right;
            if (y != nullptr && y->color == Color::RED)
            {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                rotateRight(z->parent->parent);
            }
        }
        else
        {
            auto y = z->parent->parent->left;
            if (y != nullptr && y->color == Color::RED)
            {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    root->color = Color::BLACK;
}

auto RedBlackBinarySearchTree::insert(int key) -> void
{
    auto z = std::make_shared<Node>(key);
    std::shared_ptr<Node> y = nullptr;
    std::shared_ptr<Node> x = root;

    while (x != nullptr)
    {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsertion(z);
}

auto RedBlackBinarySearchTree::printTreeHelper(std::shared_ptr<Node> root, std::string indent, bool last) -> void
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

        std::string sColor = (root->color == Color::RED) ? "RED" : "BLACK";
        std::cout << root->data << "(" << sColor << ")" << std::endl;
        printTreeHelper(root->left, indent, false);
        printTreeHelper(root->right, indent, true);
    }
}

auto RedBlackBinarySearchTree::printTree() -> void
{
    if (root)
    {
        printTreeHelper(root, "", true);
    }
}

auto RedBlackBinarySearchTree::deleteTree(std::shared_ptr<Node> node) -> void
{
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    if (node->parent)
    {
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else if (node == node->parent->right)
            node->parent->right = nullptr;
    }

    node.reset();
    root.reset();
}

auto RedBlackBinarySearchTree::minimum(std::shared_ptr<Node> node) -> std::shared_ptr<Node>
{
    if (node->left == nullptr)
        return node;
    return minimum(node->left);
}

auto RedBlackBinarySearchTree::maximum(std::shared_ptr<Node> node) -> std::shared_ptr<Node>
{
    if (node->right == nullptr)
        return node;
    return maximum(node->right);
}

auto RedBlackBinarySearchTree::fixDoubleBlack(std::shared_ptr<Node> x) -> void
{
    if (x == root)
        return;

    std::shared_ptr<Node> sibling = nullptr;
    bool isLeftChild = false;

    if (x->parent->left == x)
    {
        sibling = x->parent->right;
        isLeftChild = true;
    }
    else
    {
        sibling = x->parent->left;
        isLeftChild = false;
    }

    if (sibling != nullptr && sibling->color == Color::RED)
    {
        x->parent->color = Color::RED;
        sibling->color = Color::BLACK;
        if (isLeftChild)
            rotateLeft(x->parent);
        else
            rotateRight(x->parent);
        fixDoubleBlack(x);
    }
    else
    {
        if ((sibling == nullptr || sibling->color == Color::BLACK) &&
            ((sibling == nullptr || sibling->left == nullptr || sibling->left->color == Color::BLACK) &&
             (sibling == nullptr || sibling->right == nullptr || sibling->right->color == Color::BLACK)))
        {
            if (sibling != nullptr)
                sibling->color = Color::RED;
            if (x->parent->color == Color::BLACK)
                fixDoubleBlack(x->parent);
            else
                x->parent->color = Color::BLACK;
        }
        else
        {
            if (isLeftChild && sibling != nullptr && sibling->right != nullptr && sibling->right->color == Color::RED &&
                (sibling->left == nullptr || sibling->left->color == Color::BLACK))
            {
                sibling->color = Color::RED;
                sibling->right->color = Color::BLACK;
                rotateLeft(sibling);
            }
            else if (!isLeftChild && sibling != nullptr && sibling->left != nullptr && sibling->left->color == Color::RED &&
                     (sibling->right == nullptr || sibling->right->color == Color::BLACK))
            {
                sibling->color = Color::RED;
                sibling->left->color = Color::BLACK;
                rotateRight(sibling);
            }

            if (isLeftChild && sibling != nullptr && sibling->left != nullptr && sibling->left->color == Color::RED)
            {
                sibling->left->color = sibling->color;
                sibling->color = x->parent->color;
                sibling->right->color = Color::BLACK;
                rotateRight(x->parent);
            }
            else if (!isLeftChild && sibling != nullptr && sibling->right != nullptr && sibling->right->color == Color::RED)
            {
                sibling->right->color = sibling->color;
                sibling->color = x->parent->color;
                sibling->left->color = Color::BLACK;
                rotateLeft(x->parent);
            }

            if (x->parent != nullptr)
                x->parent->color = Color::BLACK;
        }
    }
}

auto RedBlackBinarySearchTree::deleteByKey(std::shared_ptr<Node> node, int key) -> std::shared_ptr<Node>
{
    if (node == nullptr)
        return nullptr;

    if (key < node->data)
    {
        node->left = deleteByKey(node->left, key);
    }
    else if (key > node->data)
    {
        node->right = deleteByKey(node->right, key);
    }
    else
    {
        if (node->left == nullptr || node->right == nullptr)
        {
            std::shared_ptr<Node> child = (node->left != nullptr) ? node->left : node->right;

            if (child == nullptr)
            {
                if (node == root)
                {
                    root = nullptr;
                }
                else
                {
                    if (node->color == Color::BLACK)
                    {
                        fixDoubleBlack(node);
                    }

                    if (node == node->parent->left)
                        node->parent->left = nullptr;
                    else
                        node->parent->right = nullptr;
                }

                node = nullptr;
            }
            else
            {
                node->data = child->data;
                node->left = nullptr;
                node->right = nullptr;
            }
        }
        else
        {
            std::shared_ptr<Node> successor = minimum(node->right);
            node->data = successor->data;
            node->right = deleteByKey(node->right, successor->data);
        }
    }

    return node;
}

auto RedBlackBinarySearchTree::remove(int key) -> void
{
    root = deleteByKey(root, key);
}

auto RedBlackBinarySearchTree::searchInTreeHelper(std::shared_ptr<Node> node, int key) -> std::shared_ptr<Node>
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

auto RedBlackBinarySearchTree::searchInTree(int key) -> std::shared_ptr<Node>
{
    return searchInTreeHelper(root, key);
}

auto RedBlackBinarySearchTree::getRoot() -> std::shared_ptr<Node>
{
    return root;
}

auto RedBlackBinarySearchTree::successor(std::shared_ptr<Node> x) -> std::shared_ptr<Node>
{
    if (x->right != nullptr)
    {
        return minimum(x->right);
    }

    std::shared_ptr<Node> y = x->parent;
    while (y != nullptr and x == y->right)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

auto RedBlackBinarySearchTree::predecessor(std::shared_ptr<Node> x) -> std::shared_ptr<Node>
{
    if (x->left != nullptr)
    {
        return maximum(x->left);
    }

    std::shared_ptr<Node> y = x->parent;
    while (y != nullptr && x == y->left)
    {
        x = y;
        y = y->parent;
    }

    return y;
}

auto RedBlackBinarySearchTree::preOrderHelper(std::shared_ptr<Node> node) -> void
{
    if (node != nullptr)
    {
        std::cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

auto RedBlackBinarySearchTree::preorder() -> void
{
    preOrderHelper(this->root);
}

auto RedBlackBinarySearchTree::postOrderHelper(std::shared_ptr<Node> node) -> void
{
    if (node != nullptr)
    {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->data << " ";
    }
}

auto RedBlackBinarySearchTree::postorder() -> void
{
    postOrderHelper(root);
}

auto RedBlackBinarySearchTree::inOrderHelper(std::shared_ptr<Node> node) -> void
{
    if (node != nullptr)
    {
        inOrderHelper(node->left);
        std::cout << node->data << " ";
        inOrderHelper(node->right);
    }
}

auto RedBlackBinarySearchTree::inorder() -> void
{
    inOrderHelper(root);
}
