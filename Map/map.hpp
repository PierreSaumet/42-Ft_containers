/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP
# define FT_MAP

# include "../Headers/less.hpp"
# include "../Headers/binary_function.hpp"
# include "../Headers/pair.hpp"
# include "../Vector/vector.hpp"
# include "../Headers/reverse_random_access_iterator.hpp"
# include "../Headers/bidir_redblacktree_iterator.hpp"
# include "red_black_tree.hpp"
# include "../Headers/lexicographical.hpp"
# include "../Headers/equal.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map {
		
		public :
			// Member Types 
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename std::size_t										size_type;
			typedef ptrdiff_t													difference_type;
			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {
						return ;
					}

				public:
					bool operator()(const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef ft::bidir_iterator<value_type, ft::node<value_type> >		iterator;
			typedef ft::bidir_iterator<const value_type, ft::node<value_type> >	const_iterator;
			typedef ft::reverse_random_access_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_random_access_iterator<const_iterator>			const_reverse_iterator;

			/////////////////// CONSTRUCTORS ///////////////////
			/*
			**	Empty container constructor == default constructor
			**	Constructs an empty container with no elements
			*/
			explicit map( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(value_compare(comp) ) {

				( void )alloc;
				return ;
			}
			
			/*
			**	Range constructor:
			**		Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range.
			*/
			template <class InputIterator>
			map( InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type()) : _tree(value_compare(comp) ) {

				( void )alloc;
				insert(first, last);
				return ;
			}

			/*
			**	Copy Constructor
			*/
			map( const map &other ) : _tree(value_compare(key_compare())) {

				insert(other.begin(), other.end());
				return ;
			}
			
			/*
			**	Destructor
			*/
			~map( void ) {

				clear();
				_tree.destroynull();
				return ;
			}

			/*
			**	Overload assignment operator
			*/
			map &operator=( const map &element ) {

				if (this != &element)
				{
					this->~map();
					_tree = ft::rbtree<value_type, value_compare>(value_compare(key_compare()));
					insert(element.begin(), element.end());
				}
				return (*this);
			}

			/*
			**	map::begin():
			**		Return iterator to the first element of the map container
			*/
			iterator 					begin( void ) {

				return (iterator(_tree.get_root(), _tree.min_node(), _tree.get_null()));
			}
			
			const_iterator 				begin( void ) const {

				return (const_iterator(_tree.get_root(), _tree.min_node(), _tree.get_null()));
			}

			/*
			**	map::end():
			**		Return iterator to the last element of the map container
			*/
			iterator 									end( void ) {

				return (iterator(_tree.get_root(), _tree.get_null(), _tree.get_null()));
			}

			const_iterator 								end( void ) const {

				return (const_iterator(_tree.get_root(), _tree.get_null(), _tree.get_null()));
			}

			/*
			**	map::rbegin()
			**		Return reverse iterator to reverse beginning	==	return the last element.
			*/
			reverse_iterator 							rbegin( void ) {

				return (reverse_iterator(end()));
			}

			const_reverse_iterator 						rbegin( void ) const {

				return (const_reverse_iterator(end()));
			}

			/*
			**	map::rend()
			**		Return reverse iterator to reverse end	==	return the first element.
			*/
			reverse_iterator 							rend( void ) {

				return (reverse_iterator(begin()));
			}

			const_reverse_iterator						rend( void ) const {

				return (const_reverse_iterator(begin()));
			}

			/*
			**	map::empty():
			**		REtursn whether the map container is empty
			*/
			bool				 						empty( void ) const {

				return (!_tree.get_size());
			}
			/*
			**	map::get_size():
			**		Return container size
			*/
			size_type									size( void ) const {

				return (_tree.get_size());
			}

			/*
			**	map::max_size():
			**		Return maximum size
			*/
			size_type 									max_size( void ) const {

				return (_tree.max_size());
			}

			/*
			**	map::operator[]
			**		Access element
			*/
			mapped_type 								&operator[]( const key_type & k ) {

				return (insert(ft::make_pair(k, mapped_type())).first->second);
			}

			/*
			**	map::insert():
			**		Extends the container by inserting new elements.
			**		1) single element
			**		2) with hint
			**		3) range
			*/
			ft::pair<iterator, bool>					insert( const value_type &val ) {

				if (_tree.insert(val) == false)
					return (ft::make_pair(find(val.first), false));
				return (ft::make_pair(find(val.first), true));
			}

			iterator									insert( iterator position, const value_type &val ) {

				( void )position;
				return (insert(val).first);
			}

			template <class InputIterator>
			void										insert( InputIterator first, InputIterator last ) {

				while (first != last)
				{
					insert(*first++);
				}
				return ;
			}
			
			/*
			**	map::erase():
			**		Removes from the map container either a single element or a range
			**		of elements.
			**		1) By position
			**		2) By key
			**		3) By iterator == range
			*/
			void										erase( iterator position ) {

				erase(position->first);
				return ;
			}

			size_type 									erase( const key_type &k ) {

				if (_tree.deleteNode(ft::make_pair(k, mapped_type())) == false)
					return (0);
				return (1);
			}

			void										erase( iterator first, iterator last ) {

				while (first != last)
				{
					first = find(first->first);
					erase(first++);
				}
				return ;
			}

			/*
			**	map::swap():
			**		Swap content of the container
			*/
			void										swap( map &x ) {

				_tree.swap(x._tree);
				return ;
			}

			/*
			**	map::clear():
			**		Clear content
			*/
			void										clear( void ) {

				_tree.destroy();
				return ;
			}

			/*
			**	map::key_conp():
			**		Return Key comparaison object.
			*/
			key_compare									key_comp( void ) const {

				return (key_compare());
			}

			/*
			**	map::value_comp():
			**		Return value comparaison object
			*/
			value_compare 								value_comp( void ) const {
		
				return (value_compare(key_comp()));
			}
			
			/*
			**	map::find():
			**		Get iterator to element
			*/
			iterator 									find( const key_type &k ) {

				return (iterator(_tree.get_root(), _tree.search(ft::make_pair(k, mapped_type())), _tree.get_null()));
			}

			const_iterator 								find(const key_type & k) const {

				return (iterator(_tree.get_root(), _tree.search(ft::make_pair(k, mapped_type())), _tree.get_null()));
			}

			/*
			**	map::count():
			**		Count elements with a specific key
			*/
			size_type									count( const key_type &k ) const {

				if (find(k) == end())
					return (0);
				return (1);
			}

			/*
			**	map::lower_bound():
			**		Return iterator to lower bound
			*/
			iterator 									lower_bound( const key_type &k ) {

				return (iterator(_tree.get_root(),
				_tree.lower_bound(ft::make_pair(k, mapped_type())), _tree.get_null()));
			}
			
			const_iterator 								lower_bound( const key_type &k ) const {

				return (const_iterator(_tree.get_root(),
				_tree.lower_bound(ft::make_pair(k, mapped_type())), _tree.get_null()));
			}
			
			/*
			**	map::upper_bound():
			**		Return  iterator to upper bound
			*/
			iterator 									upper_bound( const key_type & k ) {

				return (iterator(_tree.get_root(),
				_tree.upper_bound(ft::make_pair(k, mapped_type())), _tree.get_null()));
			}

			const_iterator 								upper_bound( const key_type & k ) const {

				return (const_iterator(_tree.get_root(),
				_tree.upper_bound(ft::make_pair(k, mapped_type())), _tree.get_null()));
			}
			
			/*
			**	map::equal_range():
			**		Get range og equal elements
			*/
			ft::pair<const_iterator, const_iterator>	equal_range( const key_type &k ) const {

				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			ft::pair<iterator, iterator>				equal_range( const key_type &k ) {

				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			/*
			**	map::get_allocator():
			**		get allocator
			*/
			allocator_type								get_allocator( void ) const {

				return (allocator_type());
			}

		private :
			ft::rbtree<value_type, value_compare>			_tree;

	};

	/*
	**	Non-member function overloads
	**	Performs the appropriate comparaison operation between lhs and rhs.
	**	Each of these operator overloads calls the same operator on the underlying
	**	container objects.
	*/
	template <class Key, class T, class Compare, class Allocator>
	bool operator==( const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs ) {

		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=( const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs ) {

		if (lhs.size() != rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin())); 
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<( const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs ) {

		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=( const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs ) {

		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>( const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs ) {

		return (!(rhs >= lhs));
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=( const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs ) {

		return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Allocator>
	void swap( map<Key, T, Compare, Allocator> &x, map<Key, T, Compare, Allocator> &y ) {

		return (x.swap(y));
	}
}

#endif