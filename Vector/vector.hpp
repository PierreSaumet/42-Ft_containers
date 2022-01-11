/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TEST_HPP
# define VECTOR_TEST_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include <new>
# include <cstdlib>
# include <limits>
# include "../Headers/random_access_iterator.hpp"
# include "../Headers/reverse_random_access_iterator.hpp"
# include "../Headers/nullptr.hpp"
# include "../Headers/enable_if.hpp"
# include "../Headers/is_integral.hpp"
# include "../Headers/iterator.hpp"
# include "../Headers/lexicographical.hpp"
# include "../Headers/equal.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {

		public:
			// Member Types 
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef size_t												size_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::random_access_iterator<value_type>				iterator;
			typedef ft::random_access_iterator<const value_type>		const_iterator;
			typedef ft::reverse_random_access_iterator<iterator>		reverse_iterator;
			typedef ft::reverse_random_access_iterator<const_iterator>	const_reverse_iterator;
			typedef ptrdiff_t											difference_type;
		
			/////////////////// CONSTRUCTORS ///////////////////
			/*
			**	Empty container constructor == default constructor
			**	Constructs an empty container with no elements
			*/
			explicit vector( const allocator_type &alloc = allocator_type() ) :
				_allocator(alloc), _first(my_nullptr), _last(my_nullptr), _capacity(my_nullptr), _nbrItems(0) {

				return ;
			}

			/*
			**	Fill constructor
			**	Constructs a container with n elements. Each element is a copy of val.
			*/
			explicit vector( size_type n, const value_type &val = value_type(), 
			const allocator_type &alloc =allocator_type() ) : _allocator(alloc), _first(my_nullptr), 
			_last(my_nullptr), _capacity(my_nullptr), _nbrItems(0) {

				_first = _allocator.allocate(n);
				_last = _first;
				_capacity = _first + n;
				for ( _nbrItems = 0; _nbrItems < n; _nbrItems++)
				{
					_allocator.construct(_last, val);
					_last++;
				}
				return ;
			}

			/*
			**	Range constructor
			**	Constructs a container with as many elements as the range (first last).
			*/
			template< class InputIterator>
			vector( InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = my_nullptr) : _allocator(alloc) {

				difference_type n = ft::distance(first, last); // - first;
				_first = _allocator.allocate(n);
				_capacity = _first + n;
				_last = _first;
				_nbrItems = n;
				while (n--)
				{
					_allocator.construct(_last , *first++);
					_last++;	
				}
				return ;
			}

			/*
			**	Copy Constructor
			*/
			vector( const vector & other ) : _allocator(other._allocator), 
			_first(my_nullptr), _last(my_nullptr), _capacity(0), _nbrItems(0) {

				this->insert(this->begin(), other.begin(), other.end());
				return ;
			}

			/*
			**	Destructor
			*/
			~vector( void ) {

				this->clear();
				_allocator.deallocate(_first, this->capacity());
				return ;
			}

			/*
			**	Overload assignment operator
			*/
			vector &operator=( const vector& x ) {

				if (this != &x)
				{
					this->clear();
					_first = _allocator.allocate(x.capacity());
					_last = _first;
					_capacity = x._capacity;
					_nbrItems = 0;
					while (_nbrItems < x.size())
					{
						_allocator.construct(_last, x[_nbrItems]);
						_last++;
						_nbrItems++;
					}
				}
				return (*this);
			}

			/*
			**	std::vector::begin()
			**		Return iterator to beginning.
			**		If empty, should not dereferenced the iterator.	
			*/
			iterator				begin( void ) {

				return (_first);
			}
			
			const_iterator			begin( void ) const {

				return (_first);
			}

			/*
			**	std::vector::end()
			**		Return iterator to end.
			**		If empty, return the same as vector::begin().
			*/
			iterator				end( void ) {
			
				if (this->empty())
					return (this->begin());
				return (_last);
			}

			const_iterator			end( void ) const {
				
				if (this->empty())
					return (this->begin());
				return (_last);
			}

			/*
			**	std::vector::rbegin()
			**		Return reverse iterator to reverse beginning	==	return the last element.
			*/
			reverse_iterator		rbegin( void ) {

				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator	rbegin( void ) const {

				return (reverse_iterator( this->end()));
			}

			/*
			**	std::vector::rend()
			**		Return reverse iterator to reverse end	==	return the first element.
			*/
			reverse_iterator		rend( void ) {
				
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator	rend( void ) const {
				
				return (reverse_iterator(this->begin()));
			}

			/*
			**	std::vector::size()
			**		Return the size	==	number of elements in the vector.
			**		Not necessarily equal to its storage capacity.
			*/
			size_type				size( void ) const {
				
				return (this->_nbrItems);
			}

			/*
			**	std::vector::max_size()
			**		Return the maximum size of elements that the vector can hold.
			**		Does not guaranteed to  be able to reach that size.
			*/
			size_type				max_size( void ) const {
				
				return (allocator_type().max_size());
			}			

			/*
			**	std::vector::resize()
			**		Resize the container for n elements.
			**		if n is smaller than size(), it reduces the container to its first n elements
			**		if n is bigger than the current size(), it adds at the end, the n elements. if 
			**		val is not specified, they are value-initialized
			*/
			void					resize( size_type n, value_type val = value_type() ) {

				if (n > this->max_size())
					throw (std::length_error("Error, not enough space for resize vector."));
				else if (n < this->size())
				{
					while (this->size() > n)
					{
						_allocator.destroy(--_last);
						_nbrItems--;
					}
				}
				else if (n > this->size())
				{	
					for (size_type i = this->size(); i < n; i++)
						push_back(val);
				}
				return ;
			}

			/*
			**	std::vector::capacity()
			**		Return size of allocated storage capacity.
			**		This capacity can be different from size(), it can be equal or greater,
			**		for accommodate growth.
			*/
			size_type				capacity( void ) const {
			
				return (this->_capacity - this->_first);
			}

			/*
			**	std::vector::empty()
			**		Test whether vector is empty.
			**		true if the container size is 0, false otherwise.
			*/
			bool					empty( void ) const {
				
				return (this->size() == 0);
			}

			/*
			**	std::vector::reserve()
			**		Request a change in capacity.
			**		if n is greater than the vector::max_size, std::length_error exception is thrown.
			**		if n is smaller than the vector::max_size, and bigger thann the current capacoty, the function
			**			reallocate its storage and increase the capacity
			**		else, do nothing.
			*/
			void					reserve( size_type n ) {

				if (n > this->max_size())
					throw (std::length_error("Error, not enough space for reserve vector"));
				else if (n > this->capacity())
				{
					pointer tmp_first = _first;
					pointer tmp_last = _last;
					size_type tmp_capacity = this->capacity();
					_first = _allocator.allocate(n);
					_last = _first;
					_capacity = _first + n;
					while (tmp_first != tmp_last)
					{
						_allocator.construct(_last, *tmp_first);
						tmp_first++;
						_last++;
					}
					_allocator.deallocate(tmp_first - _nbrItems, tmp_capacity);
				
				}
				return ;
			}

			/*
			**	Overload operator []
			**		Returns a reference to the element at position n.
			**		Do not check boudary != vector::at do it
			*/
			reference				operator[]( size_type n ) {
				
				return (*(_first + n));
			}

			const_reference			operator[]( size_type n ) const {
				
				return (*(_first + n));
			}

			/*
			**	ft::vector::at
			**		Returns a reference to the element at position n.
			**		Checks if n is within the bounds of the vector. Throw an error if not.
			*/
			reference				at( size_type n) {

				if (n < 0)
					throw (std::out_of_range("vector::_M_range_check: __n == Out of boudary's vector."));
				else if (n > this->size())
				{
					throw (std::out_of_range("vector::_M_range_check: __n == Out of boudary's vector."));
				}
				return (*(_first + n));
			}

			const_reference			at( size_type n ) const {

				if (n < 0)
					throw (std::out_of_range("vector::_M_range_check: __n == Out of boudary's vector."));
				else if (n > this->size())
					throw (std::out_of_range("vector::_M_range_check: __n == Out of boudary's vector."));
				return (*(_first + n));
			}

			/*
			**	ft::vector::front
			**		Returns a reference to the first element.		
			*/
			reference				front( void ) {

				return (*_first);
			}

			const_reference			front( void ) const {

				return (*_first);
			}

			/*
			**	ft::vector::back
			**		Returns a reference to the last element.
			*/
			reference				back( void ) {
 
				return (*(_last - 1));
			}

			const_reference			back( void ) const {

				return (*(_last - 1));
			}

			/*
			**	ft::vector::assign()
			**		Assign vector content.
			**		Assign new contents to the vector, replacing its current contents and modifying its
			**		size accordingly.
			**		==> range version, the new contents are elements constructed from each of the elements in the range
			**			between first and last in the same order. 
			**		==> fill version, the new contents are  n elements initialized to a copy of val
			*/
			template< class InputIterator>
			void					assign( InputIterator first, InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = my_nullptr ) {

				this->clear();
				InputIterator	tmp = first;
				size_type	count = ft::distance(first, last);
				while (tmp != last)
				{
					tmp++;
					count++;
				}
				if (size_type(_capacity - _first) >= count)
				{
					while(first != last)
					{
						_allocator.construct(_last++, *first);
						first++;
					}
				}
				else
				{
					pointer	tmp_first;
					pointer tmp_last;
					pointer tmp_capacity;
					size_type tmp_nbritems = 0;

					tmp_first = _allocator.allocate(count);
					tmp_last = tmp_first;
					tmp_capacity = tmp_first + count;
					
					while (first != last)
					{
						_allocator.construct(tmp_last, *first);
						tmp_last++;
						first++;
						tmp_nbritems++;
					}
					_allocator.deallocate(_first, this->capacity());
					_first = tmp_first;
					_last = tmp_last;
					_capacity = tmp_capacity;
					_nbrItems = tmp_nbritems;
				}
				return ;
			}

			void					assign( size_type n, const value_type &val ) {

				this->clear();
				if (n >= std::numeric_limits<size_t>::max())
					throw (std::bad_alloc());
				if (n == 0)
					return ;
				if (size_type(_capacity - _first) >= n)
				{
					while (n)
					{
						_allocator.construct(_last++, val);
						n--;
						_nbrItems++;
					}
				}
				else
				{
					_allocator.deallocate(_first, this->capacity());
					_first = _allocator.allocate(n);
					_last = _first;
					_capacity = _first + n;
					for ( _nbrItems = 0; _nbrItems < n; _nbrItems++)
						_allocator.construct(_last++, val);				
				}
				return ;
			}

			/*
			**	std::vector::push_back()
			**		Add element at the end of the vector.
			**		If the new vector size surpasses the current vector capacity,
			**		reallocate the storage.
			*/
			void					push_back( const value_type &val ) {

				if (_last == _capacity)
				{
					int tmp_capacity;
					if (this->size() > 0)
						tmp_capacity = (int)this->size() * 2;
					else
						tmp_capacity = 1;
					this->reserve(tmp_capacity);

				}
				_allocator.construct(_last, val);
				_last++;
				_nbrItems++;
				return ;
			}

			/*
			**	ft::vector::pop_back()
			**		Delete last element
			**		Reduce the container size by one, this destroys the removed element
			*/
			void					pop_back( void ) {

				_last--;
				_allocator.destroy(_last);
				_nbrItems--;
				return ;
			}

			/*
			**	ft::vector::insert()
			**		Insert elements before the element at the specified position, of course
			**		it increases the container size by the number of elements inserted.
			**		Do and reallocation if and only if the new size surpasses the current one.
			**		==> preferes list or forward_list	
			*/
			iterator				insert( iterator position, const value_type &val ) {

				size_type i = 0;

				for (iterator it_tmp = this->begin(); it_tmp != position; it_tmp++)
					i++;
				insert(position, 1, val);
				return (iterator(_first + i ));				
			}

			void					insert( iterator position, size_type n, const value_type &val ) {

				if (n < 0)
					throw (std::length_error("Error, minus n -insert-."));
				else if (n == 0)
					return ;
				else if (n > this->max_size())
					throw (std::length_error("Error, max size -insert-."));
				vector tmp;
				iterator it_tmp = this->begin();
				for (; it_tmp != position;  it_tmp++)
					tmp.push_back(*it_tmp);
				for (; n > 0; n--)
					tmp.push_back(val);
				for (; it_tmp != this->end(); it_tmp++)
					tmp.push_back(*it_tmp);
				this->swap(tmp);
				return ;
			}

			template<class InputIterator>
			void					insert( iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = my_nullptr ) {
	
				vector tmp;
				iterator it = this->begin();
				for (iterator it = this->begin(); it < position; it++)
					tmp.push_back(*it);
				for (; first != last; first++)
					tmp.push_back(*first);
				for (; position != this->end(); position++)
					tmp.push_back(*position);
				this->swap(tmp);
				return ;
			}

			/*
			**	ft::vector::erase()
			**		Erase elements, either an element or a range of elements.
			**		Reduces the container size by the number of elements removed.
			*/
			iterator				erase( iterator position ) {

				iterator ret = &(*position);
				_allocator.destroy(&(*position));
				if (&(*position) + 1 == _last)
				{
					_allocator.destroy(&(*position));
				}
				else
				{
					for (int i = 0; i < _last - &(*position) - 1; i++)
					{
						_allocator.construct(&(*position) + i, *(&(*position) + i + 1));
						_allocator.destroy(&(*position) + i + 1);
					}
				}
				_last -= 1;
				_nbrItems--;
				return (ret);
			}
			
			iterator				erase( iterator first, iterator last ) {

				iterator ret = &(*first);
				_nbrItems -= ft::distance(first, last);
				iterator tmp = first;
				while (first != last)
				{
					_allocator.destroy(&(*first));
					first++;
				}
				for (int i = 0; i < _last - &(*last); i++)
				{
					_allocator.construct(&(*tmp) + i, *(&(*last) + i));
					_allocator.destroy(&(*last) + i);
				}
				_last -= (&(*last) - &(*tmp));
				return (ret);
			}
			
			/*
			**	ft::vector::swap()
			**		Swap content, exchanges the content of the container by the content of x.
			*/
			void					swap( vector &x ) {

				if (this != &x)
				{
					pointer tmp_first = x._first;
					pointer tmp_last = x._last;
					pointer tmp_capacity = x._capacity;
					allocator_type tmp_allocator = x._allocator;
					size_type tmp_items = x._nbrItems;
					x._first = this->_first;
					x._last = this->_last;
					x._capacity = this->_capacity;
					x._allocator = this->_allocator;
					x._nbrItems = this->_nbrItems;
					this->_first = tmp_first;
					this->_last = tmp_last;
					this->_capacity = tmp_capacity;
					this->_allocator = tmp_allocator;
					this->_nbrItems = tmp_items;
				}
				return ;
			}

			/*
			**	ft::vector::clear
			**		Clear content, removes all elements from the vector
			**		leaving the container with a size of 0
			*/
			void					clear( void ) {

				size_type tmp = this->size();					
				for (size_type i = 0; i < tmp; i++)
				{
					_last--;
					_allocator.destroy(_last);
				}
				_nbrItems = 0;
				return ;
			}

			/*
			**	ft::vecor::get_allocator():
			**		Returns a copy of the allocator object.
			*/
			allocator_type			get_allocator( void ) const {

				return (this->_allocator);
			}

		private:
			allocator_type			_allocator;
			pointer					_first;
			pointer					_last;
			pointer					_capacity;
			size_type				_nbrItems;
	};

	template<class T, class Alloc>
	bool	operator==( const vector<T, Alloc> &lhs,  const vector<T, Alloc> &rhs ) {

		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class T, class Alloc>
	bool	operator!=( const vector<T, Alloc> &lhs,  const vector<T, Alloc> &rhs ) {

		if (lhs.size() != rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin())); 
	}

	template <class T, class Alloc>
	bool	operator<( const vector<T, Alloc> &lhs,  const vector<T, Alloc> &rhs ) {

		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=( const vector<T, Alloc> &lhs,  const vector<T, Alloc> &rhs ) {

		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>( const vector<T, Alloc> &lhs,  const vector<T, Alloc> &rhs ) {

		return (!(rhs >= lhs));
	}

	template <class T, class Alloc>
	bool	operator>=( const vector<T, Alloc> &lhs,  const vector<T, Alloc> &rhs ) {

		return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template <class T, class Alloc>
	void	swap( vector<T, Alloc> &x, vector<T, Alloc> &y ) {

		x.swap(y);
		return ;
	}

}



#endif