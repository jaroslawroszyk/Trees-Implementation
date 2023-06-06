#pragma once
#include <memory>

struct Node
{
    Node(int data);

    int data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;
};