/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:08 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:09 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include "RBTree.hpp"
#include "../../Utilities/utilities.hpp"

namespace ft 
{
template <typename Key, typename T, typename Compare = std::less<Key>,
            typename Allocator = std::allocator<pair<const Key, T> > >
class map 
{
public:
    typedef Key                                     key_type;
    typedef T                                       mapped_type;
    typedef Compare                                 key_compare;
    typedef Allocator                               allocator_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef pair<const Key, T>                      value_type;
    typedef const value_type&                       reference;
    typedef typename allocator_type::pointer        pointer;
    typedef typename allocator_type::const_pointer  const_pointer;

private:
    class Value_Comapre
    {
        private:
            key_compare m_comp;
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
        public:
            Value_Comapre(const key_compare& compare) : m_comp(compare) {}
            bool operator()(const value_type& lhs, const value_type& rhs) const
                { return (m_comp(lhs.first, rhs.first)); }
    };
public:
    typedef Value_Comapre                                       value_compare;
    typedef RBTree<value_type, value_compare, allocator_type>   RB_Tree;
    typedef typename RB_Tree::iterator                          iterator;
    typedef typename RB_Tree::const_iterator                    const_iterator;
    typedef typename RB_Tree::reverse_iterator                  reverse_iterator;
    typedef typename RB_Tree::const_reverse_iterator            const_reverse_iterator;

private:
    allocator_type  m_a;
    RB_Tree         rb_tree;
    key_compare     m_comp;

public:
    //ctors
    explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        : m_a(alloc), rb_tree(RB_Tree(comp,alloc)), m_comp(comp) {}

    template<class Iterator>
    map(Iterator first, Iterator last, const Compare& compare = Compare(), const Allocator& alloc = Allocator())
        : m_a(alloc), rb_tree(first, last, compare, m_a), m_comp(compare) {}

    //Iterators:
    iterator begin() { return (rb_tree.begin()); }
    iterator end () { return (rb_tree.end()); }
    reverse_iterator rbegin() { return (rb_tree.rbegin()); }
    reverse_iterator rend() { return (rb_tree.rend()); }

    //Capacity:
    bool empty() const { return (rb_tree.empty()); }
    size_type size() const { return (rb_tree.size()); }
    size_type max_size() const { return (rb_tree.max_size()); }

    //Element access:
    mapped_type& operator[](const key_type& k)
        { return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second; }
    mapped_type& at(const Key &key)
    {
        iterator res = rb_tree.find(ft::make_pair(key, mapped_type()));
        if (res == rb_tree.end())
            throw std::out_of_range("map::at()");
        return (res->second);
    }

    //Modifiers:
    pair<iterator, bool> insert (const value_type& value)
        { return (rb_tree.insert(value)); }
    iterator insert(iterator hint, const value_type& value)
        { return (rb_tree.insert(hint, value)); }
    template<class Iterator>
    void insert(typename enable_if< !is_integral<Iterator>::value, Iterator>::type first,
                Iterator last) { rb_tree.insert(first, last); }

    void erase(iterator pos) { rb_tree.erase(pos); }
    void erase(iterator first, iterator last) { rb_tree.erase(first, last); }
    size_type erase(const Key& key) { return (rb_tree.erase(make_pair(key, mapped_type()))); }

    void swap(map & other)
    {
        std::swap(this->m_comp, other.m_comp);
        rb_tree.swap(other.rb_tree);
    }

    void clear() { rb_tree.clear(); }

    //Observers:
    value_compare value_comp() const { return (rb_tree.value_comp()); }
    key_compare key_comp() const { return (m_comp); }

    //Operations:
    iterator find(const Key& key)
        { return (rb_tree.find(make_pair(key, mapped_type()))); }
    size_type count( const Key& key) const
        { return (rb_tree.count(make_pair(key, mapped_type()))); }
    iterator lower_bound(const key_type& key)
        { return (rb_tree.lower_bound(make_pair(key, mapped_type()))); }
    iterator upper_bound(const key_type& key)
        { return (rb_tree.upper_bound(make_pair(key, mapped_type()))); }
    const_iterator lower_bound(const key_type& key) const
        { return (rb_tree.lower_bound(make_pair(key, mapped_type()))); }
    const_iterator upper_bound(const key_type& key) const
        { return (rb_tree.upper_bound(make_pair(key, mapped_type()))); }
    pair<iterator, iterator> equal_range(const key_type& key)
        { return (rb_tree.equal_range(make_pair(key, mapped_type()))); }
    pair<const_iterator, const_iterator> equal_range(const key_type& key) const
        { return rb_tree.equal_range(make_pair(key, mapped_type())); }

    //Allocator:
    allocator_type get_allocator() const { return (rb_tree.get_allocator()); }

    //Operators:
    template<class K, class T1, class Comp, class Alloc>
    friend bool operator==(const map<K, T1, Comp, Alloc>& lhs, const map<K, T1, Comp, Alloc>& rhs);

    template<class K, class T1, class Comp, class Alloc>
    friend bool operator<(const map<K, T1, Comp, Alloc>& lhs, const map<K, T1, Comp, Alloc>& rhs);
};

template<class Key, class T, class Comp, class Alloc>
bool operator==(const map<Key, T, Comp, Alloc>& lhs, const map<Key, T, Comp, Alloc>& rhs)
    { return (lhs.rb_tree == rhs.rb_tree); }

template<class Key, class T, class Comp, class Alloc>
bool operator!=(const map<Key, T, Comp, Alloc>& lhs, const map<Key, T, Comp, Alloc>& rhs)
    { return !(lhs == rhs); }

template<class Key, class T, class Comp, class Alloc>
bool operator<(const map<Key, T, Comp, Alloc>& lhs, const map<Key, T, Comp, Alloc>& rhs)
    { return (lhs.rb_tree < rhs.rb_tree); }

template<class Key, class T, class Comp, class Alloc>
bool operator>(const map<Key, T, Comp, Alloc>& lhs, const map<Key, T, Comp, Alloc>& rhs)
    { return (rhs < lhs); }

template<class Key, class T, class Comp, class Alloc>
bool operator<=(const map<Key, T, Comp, Alloc>& lhs, const map<Key, T, Comp, Alloc>& rhs)
    { return !(lhs > rhs); }

template<class Key, class T, class Comp, class Alloc>
bool operator>=(const map<Key, T, Comp, Alloc>& lhs, const map<Key, T, Comp, Alloc>& rhs)
    { return !(lhs < rhs); }

template<class Key, class T, class Comp, class Alloc>
void swap(const map<Key, T, Comp, Alloc>& lhs, const map<Key, T, Comp, Alloc>& rhs)
    { lhs.swap(rhs); }
}

#endif