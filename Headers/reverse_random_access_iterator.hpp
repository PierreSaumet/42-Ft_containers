/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_random_access_iterator.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef REVERSE_RANDOM_ACCESS_ITERATOR_HPP
# define REVERSE_RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "nullptr.hpp"

namespace ft
{
	template <class Iter>
	class reverse_random_access_iterator
	{
		public:
			
			typedef Iter													iterator_type;
			/*
			**	First template parameter
			*/
			typedef typename ft::iterator_traits<Iter>::iterator_category     iterator_category;
			
			/*
			**	Second template parameter
			*/
			typedef typename ft::iterator_traits<Iter>::value_type            value_type;
			
			/*
			**	Third template parameter = ptrdiff_t
			*/
			typedef typename ft::iterator_traits<Iter>::difference_type        difference_type;
			
			/*
			**	Fourth template parameter = T*
			*/
			typedef typename ft::iterator_traits<Iter>::pointer               	pointer;
			
			/*
			**	Five template parameter  = T&
			*/
			typedef typename ft::iterator_traits<Iter>::reference           	reference;
		
			/*
			**	ALL CONSTRUCTORS
			*/
			reverse_random_access_iterator( void ) : _element()
			{
				return ;
			}

			explicit reverse_random_access_iterator( iterator_type it ) : _element(it)
			{
				return ;
			}

			template< class Iter2 >
			reverse_random_access_iterator( const reverse_random_access_iterator<Iter2> &other ) : _element(other.base())
			{
				return ;
			}

			/*
			**	ASSIGNMENT OVERLOAD
			*/
			reverse_random_access_iterator 			&operator=( const reverse_random_access_iterator &other)
			{
				if (this != &other)
				{
					this->_element = other.base();
				}
				return (*this);
			}

			/*
			**	DESTRUCTOR
			*/
			virtual ~reverse_random_access_iterator( void )
			{
				return ;
			}

			/*
			**	OTHER OVERLOAD
			*/
			reference						operator*( void ) const
			{
				iterator_type				tmp = this->_element;

				return (*(--tmp));
			}

			pointer							operator->( void ) const 
			{
				return &(this->operator*());
			}

			reverse_random_access_iterator	&operator++( void )
			{
				--_element;
				return (*this);
			}

			reverse_random_access_iterator	operator++( int )
			{
				reverse_random_access_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			reverse_random_access_iterator	&operator--( void )
			{
				++_element;
				return (*this);
			}

			reverse_random_access_iterator	operator--( int )
			{
				reverse_random_access_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			reverse_random_access_iterator	operator+( difference_type n ) const
			{
				return (reverse_random_access_iterator(this->_element - n));
			}

			reverse_random_access_iterator	operator-( difference_type n ) const
			{
				return (reverse_random_access_iterator(this->_element + n));
			}

			reverse_random_access_iterator	&operator+=( difference_type n)
			{
				_element -= n;
				return (*this);
			}

			reverse_random_access_iterator	&operator-=( difference_type n )
			{
				this->_element += n;
				return (*this);
			}

			reference						operator[]( difference_type n ) const
			{
				return (this->_element[-n - 1]);
			}



			/*
			**	GET PRIVATE MEMBER
			*/
			iterator_type				base( void ) const
			{
				return (this->_element);
			}

		private:
			/*
			**	Element from the iterator.
			*/
			iterator_type				_element;
	};
	template<class Iter>
	bool operator==( const ft::reverse_random_access_iterator<Iter> &lhs, const ft::reverse_random_access_iterator<Iter> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<class Iter1, class Iter2>
	bool operator==( const ft::reverse_random_access_iterator<Iter1> &lhs, const ft::reverse_random_access_iterator<Iter2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<class Iter>
	bool operator!=( const ft::reverse_random_access_iterator<Iter> &lhs, const ft::reverse_random_access_iterator<Iter> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<class Iter1, class Iter2>
	bool operator!=( const ft::reverse_random_access_iterator<Iter1> &lhs, const ft::reverse_random_access_iterator<Iter2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<class Iter>
	bool operator<( const ft::reverse_random_access_iterator<Iter> &lhs, const ft::reverse_random_access_iterator<Iter> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<class Iter1, class Iter2>
	bool operator<( const ft::reverse_random_access_iterator<Iter1> &lhs, const ft::reverse_random_access_iterator<Iter2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<class Iter>
	bool operator>( const ft::reverse_random_access_iterator<Iter> &lhs, const ft::reverse_random_access_iterator<Iter> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<class Iter1, class Iter2>
	bool operator>( const ft::reverse_random_access_iterator<Iter1> &lhs, const ft::reverse_random_access_iterator<Iter2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<class Iter>
	bool operator<=( const ft::reverse_random_access_iterator<Iter> &lhs, const ft::reverse_random_access_iterator<Iter> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<class Iter1, class Iter2>
	bool operator<=( const ft::reverse_random_access_iterator<Iter1> &lhs, const ft::reverse_random_access_iterator<Iter2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<class Iter>
	bool operator>=( const ft::reverse_random_access_iterator<Iter> &lhs, const ft::reverse_random_access_iterator<Iter> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<class Iter1, class Iter2>
	bool operator>=( const ft::reverse_random_access_iterator<Iter1> &lhs, const ft::reverse_random_access_iterator<Iter2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<class Iter>
	typename ft::reverse_random_access_iterator<Iter>::difference_type
	operator-( const ft::reverse_random_access_iterator<Iter> &lhs, const ft::reverse_random_access_iterator<Iter> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template<class Iter1, class Iter2>
	typename ft::reverse_random_access_iterator<Iter1>::difference_type
	operator-( const ft::reverse_random_access_iterator<Iter1> &lhs, const ft::reverse_random_access_iterator<Iter2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template<class Iter>
	ft::reverse_random_access_iterator<Iter> operator+( 
		typename ft::reverse_random_access_iterator<Iter>::difference_type n, typename ft::reverse_random_access_iterator<Iter> &it)
	{
		return ((it + n));
	}
}
#endif