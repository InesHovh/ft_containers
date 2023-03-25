/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:31 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:32 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
    template <bool b, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> {typedef T t; };
}

#endif