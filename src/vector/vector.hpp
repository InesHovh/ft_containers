/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:28 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:29 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "../../Utilities/utilities.hpp"
#include "../../Utilities/reverse_iterator.hpp"

namespace ft
{
template < class T, class Alloc = std::allocator<T> > 
class vector
{
    template<typename IT>
    class RandomAccessIterator
    {
    public:
        typedef typename iterator_traits<IT*>::difference_type      difference_type;
        typedef typename iterator_traits<IT*>::value_type           value_type;
        typedef typename iterator_traits<IT*>::reference            reference;
        typedef typename iterator_traits<IT*>::pointer              pointer;
        typedef pointer                                             iterator_type;
        typedef std::random_access_iterator_tag                     iterator_category;
        
    private:
        iterator_type m_p;
    public:

        RandomAccessIterator() : m_p() {}
        RandomAccessIterator(pointer a) : m_p(a) {}
        RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type>& s) : m_p(&(*s)) {}
        RandomAccessIterator<value_type>& operator=(RandomAccessIterator<typename remove_const<value_type>::type> const& s)
        {
            m_p = &(*s);
            return *this;
        }

        pointer operator->() const { return m_p; }
        reference operator*() const { return *m_p; }
        reference operator[](difference_type n) const { return *(m_p + n); }

        RandomAccessIterator& operator++()
        {
            ++m_p;
            return *this;
        }

        RandomAccessIterator& operator--()
        {
            --m_p;
            return *this;
        }

        RandomAccessIterator operator++(int)
        {
            RandomAccessIterator tmp(*this);
            ++m_p;
            return tmp;
        }

        RandomAccessIterator operator--(int)
        {
            RandomAccessIterator tmp(*this);
            --m_p;
            return tmp;
        }

        RandomAccessIterator operator+(const difference_type& d) const { return m_p + d; }     
        RandomAccessIterator operator-(const difference_type& d) const { return m_p - d; }

        RandomAccessIterator& operator+=(const difference_type& d)
        {
            m_p += d;
            return *this;
        }                        

        RandomAccessIterator& operator-=(const difference_type& d)
        {
            m_p -= d;
            return *this;
        }
        ~RandomAccessIterator() {}
    }; // RandomAccessIterator

    template<typename A>
    friend vector::template RandomAccessIterator<A>
    operator+(const typename vector::template RandomAccessIterator<A>::difference_type& a,
                const typename vector::template RandomAccessIterator<A>& b)
    {
        RandomAccessIterator<A> tmp(b);
        return tmp += a;
    }
    template<typename A>
    friend vector::template RandomAccessIterator<A>
    operator-(const typename vector::template RandomAccessIterator<A>::difference_type& a,
                const typename vector::template RandomAccessIterator<A>::difference_type& b)
        { return b - a; }

    template<typename A, typename B>
    friend typename vector::template RandomAccessIterator<A>::difference_type
    operator+(const vector::template RandomAccessIterator<A>& a,
                const vector::template RandomAccessIterator<B>& b)
        { return &(*a) + &(*b); }

    template<typename A, typename B>
    friend typename vector::template RandomAccessIterator<A>::difference_type
    operator-(const vector::template RandomAccessIterator<A>& a,
                const vector::template RandomAccessIterator<B>& b)
        { return &(*a) - &(*b); }

    template<typename A, typename B>
    friend bool operator==(const vector::template RandomAccessIterator<A>& a,
                            const vector::template RandomAccessIterator<B>& b)
        { return &(*a) == &(*b); }

    template<typename A, typename B>
    friend bool operator!=(const typename vector::template RandomAccessIterator<A>& a,
                            const typename vector::template RandomAccessIterator<B>& b)
        { return &(*a) != &(*b); }
    
    template<typename A, typename B>
    friend bool operator>(const typename vector::template RandomAccessIterator<A>& a,
                            const typename vector::template RandomAccessIterator<B>& b)
        { return &(*a) > &(*b); }
    
    template<typename A, typename B>
    friend bool operator<(const typename vector::template RandomAccessIterator<A>& a,
                            const typename vector::template RandomAccessIterator<B>& b)
        { return &(*a) < &(*b); }
    
    template<typename A, typename B>
    friend bool operator>=(const typename vector::template RandomAccessIterator<A>& a,
                            const typename vector::template RandomAccessIterator<B>& b)
        { return &(*a) >= &(*b); }
    
    template<typename A, typename B>
    friend bool operator<=(const typename vector::template RandomAccessIterator<A>& a,
                            const typename vector::template RandomAccessIterator<B>& b)
        { return &(*a) <= &(*b); }

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef RandomAccessIterator<value_type> iterator;
        typedef RandomAccessIterator<const value_type> const_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;

    private:
        pointer     m_p;
        size_type   m_s;
        size_type   m_c;
        allocator_type m_a;

    public:
        //Ctors and dtor
        explicit vector (const allocator_type& alloc = allocator_type()) : m_p(0), m_s(0), m_c(0), m_a(alloc){}
        explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : m_s(n), m_c(n), m_a(alloc)
        {
            m_p = m_a.allocate(n);
            for(size_type i = -1; i < n; ++i)
                m_a.construct(m_p + i, val);
        }

        template <class It>
                vector(It first, It last, const allocator_type& alloc = allocator_type(),
                        typename enable_if<!is_integral<It>::value>::type* = 0) : m_a(alloc)
        {
            if (first > last)
                throw std::length_error("vector");
            m_s = last - first;
            m_c = m_s;
            m_p = m_a.allocate(m_c);
            for (difference_type i = 0; i < static_cast<difference_type>(m_s); i++)
                m_a.construct(m_p + i, *(first + i));
        }

        vector& operator= (const vector& rhs)
        {
            if (this == &rhs)
                return *this;
            for (size_type i = 0; i < m_s; i++)
                m_a.destroy(m_p + i);
            this->m_s = rhs.m_s;
            if (m_c < m_s)
            {
                if (m_c != 0)
                    m_a.deallocate(m_p, m_c);
                m_c = m_s;
                m_p = m_a.allocate(m_c);
            }
            for (size_type i = 0; i < m_s; i++)
                m_a.construct(m_p + i, rhs[i]);
            return (*this);
        }

        vector (const vector& other) : m_s(0), m_c(0) { *this = other; }
        ~vector()
        {
            for (size_type i = 0; i < m_s; i++)
                m_a.destroy(m_p + i);
            if (m_c)
                m_a.deallocate(m_p, m_c);
        }

        //Iterators:
        iterator begin() { return (iterator(m_p)); }
        iterator end() { return (iterator(m_p + m_s)); }
        const_iterator begin() const { return (const_iterator(m_p)); }
        const_iterator end() const { return (const_iterator(m_p + m_s)); }

        reverse_iterator rbegin() { return (reverse_iterator(end())); }
        reverse_iterator rend() { return (reverse_iterator(begin())); }
        const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

        //Capacity:
        bool empty() const { return (m_s == 0); }
        size_type capacity() const { return (m_c); }
        size_type size() const { return (m_s); }
        size_type max_size() const { return (m_a.max_size()); }

        void reserve (size_type n)
        {
            if (n < m_c)
                return ;
            pointer arr = m_a.allocate(n);
            try{
                for (size_type i = 0; i < m_s; i++)
                    m_a.construct(arr + i, *(m_p + i));
            } catch (std::exception& e){
                size_type i = 0;
                while (arr + i != NULL && i < m_s){
                    m_a.destroy(arr + i);
                    i++;
                }
                m_a.deallocate(arr, n);
                throw;
            }
            for (size_type i = 0; i < m_s; i++)
                m_a.destroy(m_p + i);
            if (m_c)
                m_a.deallocate(m_p, m_c);
            m_c = n;
            m_p = arr;
        }

        void resize (size_type n, value_type val = value_type())
        {
            if (n < m_s)
            {
                for (size_type i = n; i < m_s; i++)
                    m_a.destroy(m_p + i);
                m_s = n;
            }
            else if (n > m_s)
            {
                if (m_c < n)
                    this->reserve(m_c * 2 > n ? m_c * 2 : n);
                for (size_type i = m_s; i < n; i++)
                {
                    m_a.construct(m_p + i, val);
                    m_s++;
                }
            }
        }

        //Element access:
        reference front() { return (*m_p); }
        reference back() { return (*(m_p + m_s - 1)); }
        const_reference front() const { return (*m_p);}
        const_reference back() const { return (*(m_p + m_s - 1));}

        reference at (size_type n)
        {
            if (n > m_c)
                throw std::out_of_range("vector");
            return (*(m_p + n));
        }
        const_reference at(size_type n) const
        {
            if (n > m_c)
                throw std::out_of_range("vector");
            return (*(m_p + n));
        }

        reference operator[] (size_type n) { return this->at(n); }
        const_reference operator[] (size_type n) const { return this->at(n); }

        //Modifiers:
        template <class IT>
                void assign(IT first, IT last, typename enable_if<!is_integral<IT>::value>::type* = 0)
        {
            if (first > last)
                throw std::logic_error("vector");
            difference_type n = last - first;
            clear();
            if (n > static_cast<difference_type >(capacity()))
            {
                m_a.deallocate(m_p, m_c);
                m_p = m_a.allocate(n);
                m_c = n;
            }
            iterator i = begin();
            while (first < last)
            {
                m_a.construct(&(*i), *first);
                i++;
                first++;
            }
            m_s = n;
        }

        void assign(size_type n, const value_type& val)
        {
            clear();
            if (n > m_c)
            {
                m_a.deallocate(m_p, m_c);
                m_p = m_a.allocate(n);
                m_c = n;
            }
            for (size_type i = 0; i < n; i++)
                m_a.construct(m_p + i, val);
            m_s = n;
        }

        void push_back (const value_type& val)
        {
            if (m_s == m_c)
                reserve(m_c == 0 ? 1 : m_c * 2);
            m_a.construct(m_p + m_s, val);
            m_s++;
        }

        void pop_back()
        {

            m_a.destroy(m_p + m_s - 1);
            m_s--;
        }

        iterator insert (iterator pos, const value_type& val)
        {
            if (pos < begin() || pos > end())
                throw std::logic_error("vector");
            difference_type start = pos - begin();
            if (m_s == m_c)
            {
                m_c = m_c * 2 + (m_c == 0);
                pointer arr = m_a.allocate(m_c);
                std::uninitialized_copy(begin(), pos, iterator(arr));
                m_a.construct(arr + start, val);
                std::uninitialized_copy(pos, end(), iterator(arr + start + 1));
                for (size_type i = 0; i < m_s; i++)
                    m_a.destroy(m_p + i);
                if (m_s)
                    m_a.deallocate(m_p, m_s);
                m_s++;
                m_p = arr;
            }
            else
            {
                for (size_type i = m_s; i > static_cast<size_type >(start); i--)
                {
                    m_a.destroy(m_p + i);
                    m_a.construct(m_p + i, *(m_p + i - 1));
                }
                m_a.destroy(&(*pos));
                m_a.construct(&(*pos), val);
                m_s++;
            }
            return (begin() + start);
        }

        void insert (iterator pos, size_type n, const value_type& val)
        {
            if (n == 0)
                return ;
            else if (max_size() - m_s < n)
                throw std::length_error("vector");
            difference_type start = pos - begin();
            if (m_s + n > m_c)
            {
                size_type cap = m_c * 2 >= m_s + n ? m_c * 2 : m_s + n;
                pointer arr = m_a.allocate(cap);
                std::uninitialized_copy(begin(), pos, iterator(arr));
                for (size_type i = 0; i < n; i++)
                    m_a.construct(arr + start + i, val);
                std::uninitialized_copy(pos, end(), iterator(arr + start + n));
                for (size_type i = 0; i < m_s; i++)
                    m_a.destroy(m_p + i);
                m_a.deallocate(m_p, m_c);
                m_s += n;
                m_c = cap;
                m_p = arr;
            }
            else
            {
                for (size_type i = m_s; i > static_cast<size_type>(start); i--)
                {
                    m_a.destroy(m_p + i + n - 1);
                    m_a.construct(m_p + i + n - 1, *(m_p + i - 1));
                }
                for (size_type i = 0; i < n; i++)
                {
                    m_a.destroy(m_p + i + start);
                    m_a.construct(m_p + i + start, val);
                }
                m_s += n;
            }
        }

        template <class IT>
        void insert(iterator pos, IT first, IT last, typename enable_if<!is_integral<IT>::value>::type* = 0)
        {
            if (pos < begin() || pos > end() || first > last)
                throw std::logic_error("vector");
            size_type start = static_cast<size_type>(pos - begin());
            size_type n = static_cast<size_type>(last - first);
            if (m_s + n > m_c)
            {
                size_type cap = m_c * 2 >= m_s + n ? m_c * 2 : m_s + n;
                pointer arr = m_a.allocate(cap);
                std::uninitialized_copy(begin(), pos, iterator(arr));
                try {
                    for (size_type i = 0; i < static_cast<size_type>(n); i++, first++)
                        m_a.construct(arr + start + i, *first);
                } catch (...) {
                    for (size_type i = 0; i < n + start; ++i)
                        m_a.destroy(arr + i);
                    m_a.deallocate(arr, cap);
                    throw;
                }
                std::uninitialized_copy(pos, end(), iterator(arr + start + n));
                for (size_type i = 0; i < m_s; i++)
                    m_a.destroy(m_p + i);
                m_a.deallocate(m_p, m_c);
                m_s += n;
                m_c = cap;
                m_p = arr;
            }
            else
            {
                for (size_type i = m_s; i > static_cast<size_type>(start); i--)
                {
                    m_a.destroy(m_p + i + n - 1);
                    m_a.construct(m_p + i + n - 1, *(m_p + i - 1));
                }
                for (size_type i = 0; i < static_cast<size_type>(n); i++, first++)
                {
                    m_a.destroy(m_p + i + n);
                    m_a.construct(m_p + start + i, *first);
                }
                m_s += n;
            }
        }

        iterator erase (iterator pos)
        {
            size_type n = static_cast<size_type>(std::distance(begin(), pos));
            for (size_type i = n; i < m_s - 1; ++i)
            {
                m_a.destroy(m_p + i);
                m_a.construct(m_p + i, *(m_p + i + 1));
            }
            m_s--;
            m_a.destroy(m_p + m_s - 1);
            return iterator(m_p + n);
        }

        iterator erase (iterator first, iterator last)
        {
            difference_type left = std::distance(begin(), first);
            difference_type right = std::distance(last, end());
            bool is_last = (last == end());
            for (; first != last; first++)
                m_a.destroy(&(*first));
            size_type i = left;
            while (last < end())
            {
                if (this->m_p + left)
                    m_a.destroy(m_p + i);
                m_a.construct(m_p + i, *last);
                i++;
                last++;
            }
            for ( size_type i = left + right; i < m_s; i++)
                m_a.destroy(m_p + i);
            m_s = left + right;
            return is_last ? end() : iterator(m_p + left);          
        }

        void swap(vector& x)
        {
            std::swap(m_p, x.m_p);
            std::swap(m_s, x.m_s);
            std::swap(m_c, x.m_c);
            std::swap(m_a, x.m_a);
        }
        
        void clear()
        {
            for (size_type i = 0; i < m_s; i++)
                m_a.destroy(m_p + i);
            m_s = 0;
        }

        //Allocator:
        allocator_type get_allocator() const { return (m_a); }
};

template <class T, class Alloc>
bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (size_t i = 0; i < rhs.size(); i++)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template<class T, class Alloc>
bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) 
    { return !(lhs == rhs); }

template<class T, class Alloc>
bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template<class T, class Alloc>
bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return !(rhs < lhs); }

template<class T, class Alloc>
bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return rhs < lhs; }

template<class T, class Alloc>
bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return !(lhs < rhs); }

} // namespace ft

namespace std
{
        template<class T, class Alloc>
        void swap (ft::vector<T, Alloc>& lhs, ft::vector<T,Alloc>& rhs) { lhs.swap(rhs); }
}

#endif