#pragma once
#include "Color.hpp"
#include <memory>

struct Node
{
    Node(int data);

    int data;
    Color color;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;
};