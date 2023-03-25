/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:26 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:27 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "../vector/vector.hpp"

namespace ft
{
template<class T, class Container = ft::vector<T> >
class stack
{
    public:
        typedef T                               value_type;
        typedef value_type&                     reference;
        typedef const value_type&               const_reference;
        typedef Container                       container_type;
        typedef typename Container::size_type   size_type;
    
    protected:
        container_type m_c;

    public:
        //ctors
        explicit stack(const container_type& container = container_type()) : m_c(container) {};
        stack(const stack& copy) : m_c(copy.m_c) {}

        stack& operator=(const stack& rhs)
        {
            m_c = rhs.m_c;
            return (*this);
        }
        ~stack(){}

        container_type get_type() const { return m_c; }

        bool empty() const { return (m_c.empty()); }
        size_type size() const { return (m_c.size()); }
        value_type& top() { return (m_c.back()); }
        const value_type& top() const { return (m_c.back()); }
        void push (const value_type& val) { m_c.push_back(val); }
        void pop () { m_c.pop_back(); }
    };
    template <class A, class Cont>
    bool operator== (const stack<A, Cont>& lhs, const stack<A, Cont>& rhs)
        { return lhs.get_type() == rhs.get_type(); }
    template <class A, class Cont>
    bool operator!= (const stack<A, Cont>& lhs, const stack<A, Cont>& rhs)
        { return lhs.get_type() != rhs.get_type(); }
    template <class A, class Cont>
    bool operator<  (const stack<A, Cont>& lhs, const stack<A, Cont>& rhs)
        { return lhs.get_type() < rhs.get_type(); }
    template <class A, class Cont>
    bool operator<= (const stack<A, Cont>& lhs, const stack<A, Cont>& rhs)
        { return lhs.get_type() <= rhs.get_type(); }
    template <class A, class Cont>
    bool operator>  (const stack<A, Cont>& lhs, const stack<A, Cont>& rhs)
        { return lhs.get_type() > rhs.get_type(); }
    template <class A, class Cont>
    bool operator>= (const stack<A, Cont>& lhs, const stack<A, Cont>& rhs)
        { return lhs.get_type() >= rhs.get_type(); }
}


#endif