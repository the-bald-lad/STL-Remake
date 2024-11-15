//
// Created by samjb on 27/06/2024.
//

#pragma once

#include <utility>

#include "queue.h"

// Add option to create without iterator

namespace stl
{
    template<typename T>
    struct Node
    {
        Node(const T& n_value) noexcept
            : value(n_value)
        {
        }
        Node(T&& n_value) noexcept
            : value(std::move(n_value))
        {
        }

        [[nodiscard]] constexpr bool isLeaf() const noexcept
        {
            return (left == nullptr) && (right == nullptr);
        }

        T value;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    template<typename T, size_t S = 3>
    class BinaryTree
    {
    public:
        // Should only be used with iterators
        // TODO: Check this works
        BinaryTree()
        {
        }

        template<typename It>
        explicit BinaryTree(It first, It last)
        {
            generateTree(first, last);
        }

        template<typename It>
        void generate(It first, It last)
        {
            generateTree(first, last);
        }

        constexpr Node<T>* getRoot() const noexcept
        {
            return m_root;
        }

    private:
        template<typename It>
        void generateTree(It first, It last)
        {
            auto* root = new Node<T>(*first);

            Queue<Node<T>*> node_queue;
            node_queue.push(root);

            for (auto it = first; it != last;)
            {
                Node<T>* current = node_queue.front();
                node_queue.pop();
                if (it < last)
                {
                    current->left = new Node(*(++it));
                    node_queue.push(current->left);
                }
                if (it < last)
                {
                    current->right = new Node(*(++it));
                    node_queue.push(current->right);
                }
            }

            m_root = root;
        }

        Node<T>* m_root = nullptr;
    };

}
