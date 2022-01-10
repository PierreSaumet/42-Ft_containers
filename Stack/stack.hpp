/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <deque>
# include <list>
# include "../Vector/vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack {

		public:
			// Member Types 
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;

			/////////////////// CONSTRUCTORS ///////////////////
			/*
			**	 Constructs a stack container adaptor object.
			*/
			explicit				stack( const container_type &ctnr = container_type() ) : _container(ctnr) {

				return ;
			}

			/*
			**	Destructor
			*/
			~stack( void ) {

				return ;
			}

			/*
			**	stack::empty():
			**		Test whether container is empty.
			**		Returns true if the size is 0, otherwise false.
			*/
			bool					empty( void ) const {

				return (this->_container.empty());
			}

			/*
			**	stack::size():
			**		Returns the number of elements in the stack
			*/
			size_type				size( void ) const {

				return (this->_container.size());
			}

			/*
			**	stack::top():
			**		Access next element
			**		Returns a reference to the top element in the stack
			**		The top element is the last element
			*/
			value_type				&top( void ) {

				//std::cout << "\t Dans stack TOP" << std::endl;
				return (this->_container.back());
			}

			const value_type		&top( void ) const {

				return (this->_container.back());
			}

			/*
			**	stack::push():
			**		Insert a new element at the top of the stack, above he top element.
			*/
			void					push( const value_type &val ) {

				//std::cout << "\t Dans stack PUSH" << std::endl;
				this->_container.push_back(val);
				return ;
			}

			/*
			**	stack::pop():
			**		Remove the element on the top of the stack.
			**		And reducing its size by one.
			*/
			void					pop( void ) {

				this->_container.pop_back();
				return ;
			}

			template <class T2, class Container2>
			friend bool operator==( const stack<T2, Container2> &lhs, const stack<T2, Container2> &rhs);

			template <class T2, class Container2>
			friend bool operator!=( const stack<T2, Container2> &lhs, const stack<T2, Container2> &rhs);

			template <class T2, class Container2>
			friend bool operator<=( const stack<T2, Container2> &lhs, const stack<T2, Container2> &rhs);

			template <class T2, class Container2>
			friend bool operator>=( const stack<T2, Container2> &lhs, const stack<T2, Container2> &rhs);

			template <class T2, class Container2>
			friend bool operator<( const stack<T2, Container2> &lhs, const stack<T2, Container2> &rhs);

			template <class T2, class Container2>
			friend bool operator>( const stack<T2, Container2> &lhs, const stack<T2, Container2> &rhs);

			template <class T2, class Container2>
			friend bool operator==( const stack<T2, Container2> &lhs, const stack<T2, Container2> &rhs);

		private:
			container_type			_container;

	};

	/*
	**	Non-member function overloads
	**	Performs the appropriate comparaison operation between lhs and rhs.
	**	Each of these operator overloads calls the same operator on the underlying
	**	container objects.
	*/
	template <class T, class Container>
	bool		operator==( const stack<T, Container> &lhs, const stack<T, Container> &rhs ) {

		return (lhs._container == rhs._container);
	}

	template <class T, class Container>
	bool		operator!=( const stack<T, Container> &lhs, const stack<T, Container> &rhs ) {

		return (lhs._container != rhs._container);
	}

	template <class T, class Container>
	bool		operator<( const stack<T, Container> &lhs, const stack<T, Container> &rhs ) {
		
		return (lhs._container < rhs._container);
	}
	
	template <class T, class Container>
	bool		operator<=( const stack<T, Container> &lhs, const stack<T, Container> &rhs ) {

		return (lhs._container <= rhs._container);
	}

	template <class T, class Container>
	bool		operator>( const stack<T, Container> &lhs, const stack<T, Container> &rhs ) {

		return (lhs._container > rhs._container);
	}

	template <class T, class Container>
	bool		operator>=( const stack<T, Container> &lhs, const stack<T, Container> &rhs ) {

		return (lhs._container >= rhs._container);
	}
} 

#endif