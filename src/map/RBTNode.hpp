/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:18 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:19 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTNode_HPP
#define RBTNode_HPP
#include "../../Utilities/utilities.hpp"

namespace ft
{
template <class T>
struct RBTNode
{
public:
    T*          value;
    RBTNode*    parent;
    RBTNode*    left;
    RBTNode*    right;
    bool        is_black;
    bool        is_nil;
    
    explicit RBTNode(T *src = 0)
        : value(src), parent(0), left(0), right(0), is_black(false), is_nil(0) {}
    RBTNode(RBTNode const& copy)
        : value(copy.value), parent(copy.parent), left(copy.left), right(copy.right),
        is_black(copy.is_black), is_nil(copy.is_nil) {}
    
    RBTNode& operator=(const RBTNode& rhs)
    {
        this->value = rhs.value;
        this->parent = rhs.parent;
        this->left = rhs.left;
        this->right = rhs.right;
        this->is_black = rhs.is_black;
        this->is_nil = rhs.is_nil;
        return *this;
    }
    virtual ~RBTNode(){}
}; //RBTNode
} //namespace ft


#endif