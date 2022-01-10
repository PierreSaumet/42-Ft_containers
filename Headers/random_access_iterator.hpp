/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "nullptr.hpp"


namespace ft
{
    template <typename T>
        class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
        {
            public:
                
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer               pointer;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference           	reference;
                
				/*
				**	ALL CONSTRUCTORS
				*/
                random_access_iterator( void ) : _element(my_nullptr) {

					return ;
				}

                random_access_iterator( pointer elem ) : _element(elem) {

					return ;
				}

                random_access_iterator( const random_access_iterator &other ) : _element(other._element) {

					return ;
				}

                random_access_iterator		&operator=( const random_access_iterator &other ) {

                    if (this != &other)
						this->_element = other.base();
		            return (*this);

                }

                virtual						~random_access_iterator( void )
				{
					return ;
				}

                pointer						base( void ) const
                {
					return (this->_element);
				}

				/*
				**	OTHER OVERLOAD
				*/
				reference					operator*( void ) const {

					return (*this->_element);
				}

                pointer						operator->( void ) {

					return &(this->operator*());
				}

                random_access_iterator		&operator++( void ) {

                    ++_element;
                    return (*this);
                }

                random_access_iterator		operator++( int ) {

                    random_access_iterator tmp(*this);
                    operator++();
                    return (tmp);
                }

                random_access_iterator		&operator--( void ) {

                    --_element;
                    return (*this);
                }

                random_access_iterator 		operator--( int ) {

                    random_access_iterator tmp(*this);
                    operator--();
                    return (tmp);
                }

                random_access_iterator 		operator+( difference_type n ) const {

					return (_element + n);
				}

                random_access_iterator 		operator-( difference_type n ) const {

					return (_element - n);
				}

                random_access_iterator		&operator+=( difference_type n ) {

                    _element += n;
                    return (*this);
                }

                random_access_iterator		&operator-=( difference_type n ) {

                    _element -= n;
                    return (*this);
                }

                reference 					operator[]( difference_type n ) const {

					return (*(operator+(n)));
				}

                operator					random_access_iterator<const T>( void ) const {

					return (random_access_iterator<const T>(this->_element));
				}

                private:
                    pointer _element;
        };

    template <typename T>
    bool operator==( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {

        return (lhs.base() == rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator==( const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs ) {

        return (lhs.base() == rhs.base());
    }

    template <typename T>
    bool operator!=( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {

        return (lhs.base() != rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator!=( const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs ) {

        return (lhs.base() != rhs.base());
    }

    template <typename T>
    bool operator<( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {

        return (lhs.base() < rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator<( const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs ) {

        return (lhs.base() < rhs.base());
    }

    template <typename T>
    bool operator>( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {

        return (lhs.base() > rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator>( const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs ) {

        return (lhs.base() > rhs.base());
    }

    template <typename T>
    bool operator<=( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {

        return (lhs.base() <= rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator<=( const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs ) {

        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    bool operator>=( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {

        return (lhs.base() >= rhs.base());
    }

    template<typename T_L, typename T_R>
    bool operator>=( const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs ) {

        return (lhs.base() >= rhs.base());
    }

    template<typename T>
    ft::random_access_iterator<T> operator+(
        typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T> &it) {

        return (&(*it) + n);
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator-( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {

        return (lhs.base() - rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator-( const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs ) {

        return (lhs.base() - rhs.base());
    }

}

#endif