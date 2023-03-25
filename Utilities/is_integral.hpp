/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihovhann <ihovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:37:36 by ihovhann          #+#    #+#             */
/*   Updated: 2022/12/22 17:37:37 by ihovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft
{
    //Remove Const
    template <class T> struct remove_const { typedef T type; };
    template <class T> struct remove_const <const T> { typedef T type; };

    //Conditional
    template<bool B, class T, class F>
    struct conditional {typedef F type;};
    template<class T, class F>
    struct conditional<true, T, F> {typedef T type; };

    //Is integral
    template<class T, bool val>
    struct integral_constant{
        static const bool value = val;
        typedef T                   value_type;
        typedef integral_constant   type;
        operator value_type() const { return value; }
    };

    template <class T>
    struct is_integral : public ft::integral_constant<T, false> {};

    template <>
    struct is_integral<bool> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<char> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<signed char> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<short> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<wchar_t> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<char16_t> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<int> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<long> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<long long> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned char> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned short> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned int> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned long> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned long long> : public ft::integral_constant<bool, true>{  };


}

#endif