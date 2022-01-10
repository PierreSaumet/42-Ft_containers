/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <iostream>
/*
**	Pair si a structure template that hold / save 2 objects as a single unit
**		==> see tuple with 2 elements
*/

namespace ft {

	template<class T1, class T2>
	struct				pair
	{
		public:
			// Member types
			typedef T1		first_type;
			typedef T2		second_type;

			// Member objects
			first_type		first;
			second_type		second;

			// Constructor
			pair( void ) : first(), second() { 
			
				return ;
			}
			pair( const first_type &x, const second_type &y ) : first(x), second(y) {

				return ;
			}

			pair( const pair &copy ) : first(copy.first), second(copy.second) {

				return ;
			}

			template<class U1, class U2>
			pair( const pair<U1, U2> &p ) : first(p.first), second(p.second) {

				return ;
			}

			pair			&operator=(const pair &element)
			{
				if (this != &element)
				{
					this->first = element.first;
					this->second = element.second;
				}
				return (*this);
			}
	};

    template <class T1, class T2>
    bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }
	template <class T1, class T2>
    ft::pair<T1,T2> make_pair(T1 x, T2 y)
    {
        return (ft::pair<T1, T2>(x, y));
    }
}
#endif