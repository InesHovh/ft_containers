/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:23 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:24 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP
#include "RBTNode.hpp"
#include "../../Utilities/iterator_traits.hpp"

namespace ft
{
    template<typename T>
    class TreeIterator 
    {
    public:
        typedef std::bidirectional_iterator_tag                         iterator_category;
        typedef typename ft::iterator_traits<T*>::value_type            value_type;
        typedef typename ft::iterator_traits<T*>::reference             reference;
        typedef typename ft::iterator_traits<T*>::pointer               pointer;
        typedef typename ft::iterator_traits<T*>::difference_type       difference_type;
        typedef RBTNode<typename ft::remove_const<value_type>::type>*   node_ptr;

    private:
        node_ptr m_node;
        
        node_ptr min_value(node_ptr n) const 
        {
            while(n->left != NULL && !n->left->is_nil)
                n = n->left;
            return n; 
        }

        node_ptr max_value(node_ptr n) const 
        {
            while (!n->right->is_nil)
                n = n->right;
            return n;
        }
    public:

        TreeIterator() {}
        TreeIterator(void *node) : m_node(static_cast<node_ptr>(node)) {}
        TreeIterator(const TreeIterator<typename ft::remove_const<value_type>::type > & copy) { *this = copy; }
        TreeIterator& operator=(const TreeIterator<typename ft::remove_const<value_type>::type>& rhs)
        {
            this->m_node = rhs.get_node();
            return *this;
        }
        reference operator*() const { return *(m_node->value); }
        pointer operator->() const { return (m_node->value); }

        node_ptr get_node() const { return m_node; }

        TreeIterator& operator++()
        {
            if(m_node->right && !m_node->right->is_nil)
                m_node = min_value(m_node->right);
            else
            {
                node_ptr p = m_node->parent;
                while (p != NULL && m_node == p->right)
                {
                    m_node = p;
                    p = p->parent;
                }
                m_node = p;
            }
            return *this;
        }
        TreeIterator operator++(int)
        {
            TreeIterator<value_type> temp = *this;
            if (!m_node->right->is_nil)
                m_node = min_value(m_node->right);
            else
            {
                node_ptr p = m_node->parent;
                while(p != NULL && m_node == p->right)
                {
                    m_node = p;
                    p = p->parent;
                }
                m_node = p;
            }
            return temp;
        }

        TreeIterator& operator--()
        {
            if (m_node->left && !m_node->left->is_nil)
                m_node = max_value(m_node->left);
            else
            {
                node_ptr p = m_node->parent;
                while (p != NULL && m_node == p->left)
                {
                    m_node = p;
                    p = p->parent;
                }
                m_node = p;
            }
            return *this;
        }
        
        TreeIterator operator--(int)
        {
            TreeIterator<value_type> temp = *this;
            if (m_node->left && !m_node->left->is_nil)
                m_node = max_value(m_node->left);
            else
            {
                node_ptr p = m_node->parent;
                while (p != NULL && m_node == p->left)
                {
                    m_node = p;
                    p = p->parent;
                }
                m_node = p;
            }
            return temp;
        }
    }; // TreeIterator

    template<typename A, typename B>
    bool operator==(const TreeIterator<A> &lhs, const TreeIterator<B> &rhs)
        { return (lhs.get_node() == rhs.get_node()); }

    template<typename A, typename B>
    bool operator!=(const TreeIterator<A> &lhs, const TreeIterator<B> &rhs)
        { return (lhs.get_node() != rhs.get_node()); }
} // namespace ft

#endif