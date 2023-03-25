/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:21 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:22 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP
#include "RBTNode.hpp"
#include "TreeIterator.hpp"
#include "../../Utilities/reverse_iterator.hpp"
#include "../../Utilities/utilities.hpp"

namespace ft
{
template <typename Value, typename Compare = std::less<Value>,
            typename Alloc = std::allocator<Value> >
class RBTree
{
public:
    typedef Value                                       value_type;
    typedef Compare                                     value_compare;
    typedef Alloc                                       allocator_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef std::ptrdiff_t                              difference_type;
    typedef std::size_t                                 size_type;
    typedef ft::TreeIterator<Value>                     iterator;
    typedef ft::TreeIterator<const Value>               const_iterator;
    typedef ft::reverse_iterator<iterator>              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
    
    typedef typename Alloc::template rebind<ft::RBTNode<Value> >::other     node_allocator;
    typedef typename node_allocator::pointer                                RBTNode;

private:
    allocator_type      m_a;
    node_allocator      m_node_alloc;
    value_compare       m_comp;
    RBTNode             m_node;
    RBTNode             m_parent;
    RBTNode             m_root;
    size_type           m_size;

    bool is_nil(RBTNode n) const { return n == m_node || n == m_parent; }

    void delete_node_value(RBTNode n)
    {
        m_a.destroy(n->value);
        m_a.deallocate(n->value, 1);
        m_node_alloc.deallocate(n, 1);
    }

    void delete_one_node(RBTNode n)
    {
        if (n && !is_nil(n))
        {
            delete_one_node(n->right);
            delete_one_node(n->left);
            delete_node_value(n);
        }
    }

    void create_nil_node()
    {
        m_node = m_node_alloc.allocate(1);
        m_node_alloc.construct(m_node, ft::RBTNode<Value>());
        m_node->is_black = true;
        m_node->is_nil = true;
        m_parent = m_node_alloc.allocate(1);
        m_node_alloc.construct(m_parent, ft::RBTNode<Value>());
        m_parent->value = m_a.allocate(1);
        m_a.construct(m_parent->value, Value());
        m_parent->is_black = true;
    }

    void RBT_swap(RBTNode dst, RBTNode n)
    {
        if (dst == m_root)
            m_root = n;
        else if (dst == dst->parent->left)
            dst->parent->left = n;
        else
            dst->parent->right = n;
        n->parent = dst->parent;
    }

    RBTNode tree_min(RBTNode n) const
    {
        while (n != NULL && !is_nil(n->left))
            n = n->left;
        return n;
    }    

    RBTNode tree_max(RBTNode n) const
    {
        while (n != NULL && !is_nil(n->right))
            n = n->right;
        return n;
    }

    void    right_rotate(RBTNode n)
    {
        RBTNode p;

        p = n->left;
        n->left = p->right;
        if (!is_nil(p->right))
            p->right->parent = n;
        p->parent = n->parent;
        if (n->parent == NULL)
            m_root = p;
        else if (n == n->parent->left)
            n->parent->left = p;
        else
            n->parent->right = p;
        p->right = n;
        n->parent = p;
    }

    void    left_rotate(RBTNode n)
    {
        RBTNode p;

        p = n->right;
        n->right = p->left;
        if (!is_nil(p->left))
            p->left->parent = n;
        p->parent = n->parent;
        if (n->parent == NULL)
            m_root = p;
        else if(n == n->parent->left)
            n->parent->left = p;
        else
            n->parent->right = p;
        p->left = n;
        n->parent = p;
    }

    RBTNode insert_node(RBTNode r, RBTNode n)
    {
        if (m_comp(*n->value, *r->value))
        {
            if (!is_nil(r->left))
                return (insert_node(r->left, n));
            r->left = n;
        }
        else
        {
            if (!is_nil(r->right))
                return (insert_node(r->right, n));
            r->right = n;
        }
        n->parent = r;
        return (n);
    }

    RBTNode insert_RBTree(RBTNode n, RBTNode dst)
    {
        if (m_root == m_parent)
            m_root = n;
        else
            insert_node(dst, n);
        return (n);
    }

    void insert_rebelance(RBTNode n)
    {
        if (n != m_root && n->parent != m_root)
        {
            while(n != m_root && !n->parent->is_black)
            {
                if (n->parent == n->parent->parent->left)
                {
                    RBTNode u = n->parent->parent->right;
                    if (!u->is_black)
                    {
                        n->parent->is_black = true;
                        u->is_black = true;
                        n->parent->parent->is_black = false;
                        n = n->parent->parent;
                    }
                    else
                    {
                        if (n == n->parent->right)
                        {
                            n = n->parent;
                            left_rotate(n);
                        }
                        n->parent->is_black = true;
                        n->parent->parent->is_black = false;
                        right_rotate(n->parent->parent);
                    }
                }
                else
                {
                    RBTNode u = n->parent->parent->left;
                    if (!u->is_black)
                    {
                        n->parent->is_black = true;
                        u->is_black = true;
                        n->parent->parent->is_black = false;
                        n = n->parent->parent;
                    }
                    else
                    {
                        if (n == n->parent->left)
                        {
                            n = n->parent;
                            right_rotate(n);
                        }
                        n->parent->is_black = true;
                        n->parent->parent->is_black = false;
                        left_rotate(n->parent->parent);
                    }
                }
            }
        }
        m_root->is_black = true;
    }

    public:
        //ctors and dtor
        RBTree(const Compare &c, const allocator_type& a = allocator_type())
                : m_a(a), m_node_alloc(node_allocator()), m_comp(c), m_root(0), m_size(0)
        {
            create_nil_node();
            m_root = m_parent;
        }

        RBTree() : m_a(allocator_type()), m_node_alloc(node_allocator()), m_comp(value_compare()), m_root(0), m_size(0)
        {
            create_nil_node();
            m_root = m_parent;
        }

        template<class IT>
        RBTree(typename ft::enable_if< !ft::is_integral<IT>::value, IT>::type first, IT last,
                const value_compare& c, const allocator_type& a = allocator_type())
                    : m_a(a), m_node_alloc(node_allocator()), m_comp(c)
        {
            create_nil_node();
            m_root = m_parent;
            for (; first != last; ++first)
                insert(*first);
        }

        RBTree(const RBTree& copy) : m_comp(copy.m_comp), m_root(NULL) { *this = copy; }

        RBTree& operator=(const RBTree& rhs)
        {
            if (this == &rhs)
                return *this;
            this->m_node_alloc = rhs.m_node_alloc;
            this->m_a = rhs.m_a;
            this->m_comp = rhs.m_comp;
            if (this->m_root == NULL)
                create_nil_node();
            else
                delete_one_node(m_root);
            if (rhs.m_size == 0)
                this->m_root = this->m_parent;
            else
            {
                this->m_root = copy_node(rhs.m_root);
                copy_child(this->m_root, rhs.m_root);
            }
            this->m_size = rhs.m_size;
            return *this;
        }

        ~RBTree() 
        {
            delete_one_node(m_root);
            m_a.destroy(m_parent->value);
            m_a.deallocate(m_parent->value, 1);
            m_node_alloc.deallocate(m_node, 1);
            m_node_alloc.deallocate(m_parent, 1);
        }

        //Capacity:
        size_type size() const { return (m_size); }
        size_type max_size() const { return (m_a.max_size()); }
        bool empty() const { return (m_size == 0); }

        //Iterators:
        iterator begin() { return (iterator(m_size == 0 ? m_parent : iterator(tree_min(m_root)))); }
        iterator end() { return (iterator(m_parent)); }
        const_iterator begin() const { return (const_iterator(m_size == 0 ? m_parent : const_iterator(tree_min(m_root)))); }
        const_iterator end() const { return const_iterator(m_parent); }
        reverse_iterator rbegin() { return (reverse_iterator(end())); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        //Observers:
        value_compare value_comp() const { return (m_comp); }

        //Allocator:
        allocator_type get_allocator() const { return (m_a); }

        //Create function
        pointer create_value(const value_type & value)
        {
            pointer rtn = m_a.allocate(1);
            m_a.construct(rtn, value);
            return rtn;
        }

        //Copy functions
        RBTNode copy_node(RBTNode other)
        {
            RBTNode rtn = m_node_alloc.allocate(1);
            m_node_alloc.construct(rtn, ft::RBTNode<Value>());
            rtn->is_black = other->is_black;
            rtn->is_nil = other->is_nil;
            if (other->value)
            {
                rtn->value = m_a.allocate(1);
                m_a.construct(rtn->value, *other->value);
            }
            return (rtn);
        }

        void copy_child(RBTNode my_node, RBTNode other)
        {
            if (other->left->is_nil)
                my_node->left = m_node;
            else
            {
                my_node->left = copy_node(other->left);
                my_node->left->parent = my_node;
                copy_child(my_node->left, other->left);
            }
            if(other->right->is_nil)
                my_node->right = m_node;
            else if (other->right->right == NULL)
            {
                my_node->right = m_parent;
                m_parent->parent = my_node;
            }
            else
            {
                my_node->right = copy_node(other->right);
                my_node->right->parent = my_node;
                copy_child(my_node->right, other->right);
            }
        }

        //Modifiers:
        ft::pair<iterator, bool> insert(value_type const &value)
        {
            RBTNode find_val = search(value, m_root);
            if (find_val)
                return ft::pair<iterator, bool>(iterator(find_val), false);
            RBTNode new_node = m_node_alloc.allocate(1);
            m_node_alloc.construct(new_node, ft::RBTNode<value_type>(create_value(value)));
            new_node->left = m_node;
            new_node->right = m_node;
            insert_RBTree(new_node, m_root);
            ft::pair<iterator, bool> res(iterator(new_node), true);
            insert_rebelance(new_node);
            m_size++;
            new_node = tree_max(m_root);
            new_node->right = m_parent;
            m_parent->parent = new_node;
            return res;
        }

        iterator insert(iterator position, const value_type& value)
        {
            RBTNode new_node = search(value, m_root);
            if (new_node)
                return (iterator(new_node));
            new_node = m_node_alloc.allocate(1);
            m_node_alloc.construct(new_node, ft::RBTNode<value_type>(create_value(value)));
            new_node->left = m_node;
            new_node->right = m_node;
            if (position == begin())
            {
                if (position != end() && m_comp(value, *position))
                    insert_RBTree(new_node, tree_min(m_root));
                else
                    insert_RBTree(new_node, m_root);
            }
            else if (position == end())
            {
                if (position != begin() && m_comp(*(--position), value))
                    insert_RBTree(new_node, m_parent->parent);
                else
                    insert_RBTree(new_node, m_root);
            }
            else
                insert_RBTree(new_node, m_root);
            insert_rebelance(new_node);
            m_size++;
            RBTNode max_of_tree = tree_max(m_root);
            max_of_tree->right = m_parent;
            m_parent->parent = max_of_tree;
            return (iterator(new_node));
        }

        template<class IT>
        void insert(typename ft::enable_if<!ft::is_integral<IT>::value, IT>::type first, IT last)
        {
            while( first != last)
            {
                insert(*first);
                ++first;
            }
        }

        void clear()
        {
            delete_one_node(m_root);
            m_root = m_parent;
            m_parent->parent = NULL;
            m_size = 0;
        }

        void erase_fixup(RBTNode x)
        {
            RBTNode brother;
            while (x != m_root && x->is_black){
                if (x == x->parent->left){
                    brother = x->parent->right;
                    //case 1
                    if (!brother->is_black){
                        brother->is_black = true;
                        x->parent->is_black = false;
                        left_rotate(x->parent);
                        brother = x->parent->right;
                    }
                    //case 2
                    if (brother->left->is_black && brother->right->is_black){
                        brother->is_black = false;
                        x = x->parent;
                    }
                    else{
                    //case 3
                        if (brother->right->is_black){
                            brother->left->is_black = true;
                            brother->is_black = false;
                            right_rotate(brother);
                            brother = x->parent->right;
                        }
                    //case 4
                        brother->is_black = x->parent->is_black;
                        x->parent->is_black = true;
                        brother->right->is_black = true;
                        left_rotate(x->parent);
                        x = m_root;
                    }
                }
                else{
                    brother = x->parent->left;
                    //case 1
                    if (!brother->is_black){
                        brother->is_black = true;
                        x->parent->is_black = false;
                        right_rotate(x->parent);
                        brother = x->parent->left;
                    }
                    //case 2
                    if (brother->right->is_black && brother->left->is_black){
                        brother->is_black = false;
                        x = x->parent;
                    }
                    else{
                    //case 3
                        if (brother->left->is_black){
                            brother->right->is_black = true;
                            brother->is_black = false;
                            left_rotate(brother);
                            brother = x->parent->left;
                        }
                    //case 4
                        brother->is_black = x->parent->is_black;
                        x->parent->is_black = true;
                        brother->left->is_black = true;
                        right_rotate(x->parent);
                        x = m_root;
                    }
                }
            }
        }

        void erase(iterator pos)
        {
            if (m_size == 0)
                return ;
            RBTNode y = pos.get_node(), x, for_free = y;
            bool y_original_is_black = y->is_black;
            if (is_nil(y->left)){
                x = y->right;
                RBT_swap(y, y->right);
            }
            else if (is_nil(y->right)){
                x = y->left;
                RBT_swap(y, y->left);
            }
            else {
                RBTNode z = y;
                y = tree_min(z->right);
                y_original_is_black = y->is_black;
                x = y->right;
                if (y->parent != z){
                    RBT_swap(y, y->right);
                    y->right = z->right;
                    z->right->parent = y;
                }
                RBT_swap(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->is_black = z->is_black;
            }
            delete_node_value(for_free);
            if (y_original_is_black)
                erase_fixup(x);
            m_size--;
            m_node->parent = NULL;
            if (m_size == 0)
                m_root = m_parent;
            else{
                if (m_size != 1)
                    x = tree_max(m_root);
                else
                    x = m_root;
                x->right = m_parent;
                m_parent->parent = x;
            }
        }

        size_type erase(const value_type& value)
        {
            RBTNode res = search(value, m_root);
            if (res)
                erase(iterator(res));
            return (res != NULL);
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
                erase(first++);
        }

        //Operations:
        RBTNode search(const value_type &value, RBTNode node) const
        {
            if (!node || is_nil(node))
                return NULL;
            if (m_comp(value, *node->value))
                return search(value, node->left);
            if (m_comp(*node->value, value))
                return search(value, node->right);
            return node;
        }

        iterator find(const value_type& value)
        {
            RBTNode find_res = search(value, m_root);
            return (find_res == NULL ? end() : iterator(find_res));
        }

        const_iterator find(const value_type& value) const
        {
            RBTNode find_res = search(value, m_root);
            return (find_res == NULL ? end() : const_iterator(find_res));
        }

        size_type count(const value_type& value) const { return (find(value) != end()); }

        iterator upper_bound(const value_type& value)
        {
            iterator last = end();
            for (iterator first = begin(); first != last; ++first)
                if (m_comp(value, *first))
                    return (first);
            return(last);
        }

        iterator lower_bound(const value_type& value)
        {
            iterator last = end();
            for (iterator first = begin(); first != last; ++first)
                if (!m_comp(*first, value))
                    return (first);
            return (last);
        }

        const_iterator upper_bound(const value_type& value) const
        {
            const_iterator last = end();
            for (const_iterator first = begin(); first != last; ++first)
                if (!m_comp(value, *first))
                    return (first);
            return last;
        }

        const_iterator lower_bound(const value_type& value) const 
        {
            const_iterator last = end();
            for (const_iterator first = begin(); first != last; ++first)
                if (!m_comp(*first, value))
                    return (first);
            return last;
        }

        void swap (RBTree &rhs)
        {
            std::swap(this->m_a, rhs.m_a);
            std::swap(this->m_root, rhs.m_root);
            std::swap(this->m_node, rhs.m_node);
            std::swap(this->m_parent, rhs.m_parent);
            std::swap(this->m_size, rhs.m_size);
            std::swap(this->m_comp, rhs.m_comp);
            std::swap(this->m_node_alloc, rhs.m_node_alloc);
        }    
        
        ft::pair<iterator, iterator> equal_range(const value_type& value)
            { return (ft::make_pair(lower_bound(value), upper_bound(value))); }
}; //RBTree

template <class T, class Compare, class Alloc>
bool operator==(const RBTree<T, Compare, Alloc>& lhs, const RBTree<T, Compare, Alloc>& rhs)
    { return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template <class T, class Compare, class Alloc>
bool operator<(const RBTree<T, Compare, Alloc>& lhs, const RBTree<T, Compare, Alloc>& rhs)
    { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template <class T, class Compare, class Alloc>
bool operator>(const RBTree<T, Compare, Alloc>& lhs, const RBTree<T, Compare, Alloc>& rhs)
    { return (lhs < rhs); }

template <class T, class Compare, class Alloc>
void swap(const RBTree<T, Compare, Alloc>& lhs, const RBTree<T, Compare, Alloc>& rhs)
    { lhs.swap(rhs); }
} //namespace ft

#endif