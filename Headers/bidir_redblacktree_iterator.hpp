
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidir_redblacktree_iterator.hpp                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: psaumet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:07:34 by psaumet           #+#    #+#             */
/*   Updated: 2021/08/15 11:07:42 by psaumet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIR_REDBLACKTREE_ITERATOR_HPP
# define BIDIR_REDBLACKTREE_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "../Headers/nullptr.hpp"

namespace ft
{
	template< class T, class Node>
	class bidir_iterator : public ft::iterator<bidirectional_iterator_tag, T>
	{
		public:

			typedef T																		value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type 	difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef Node*																	ptr_node;

			/*
			**	CONSTRUCTOR
			*/
			bidir_iterator( void ) : _root(my_nullptr), _node(my_nullptr), _null(my_nullptr) {

				return ;
			}

			bidir_iterator( ptr_node root, ptr_node node, ptr_node null ) : _root(root), _node(node), _null(null) {

				return ;
			}

			bidir_iterator( bidir_iterator const &src ) : _root(src._root), _node(src._node), _null(src._null) {
			
				return ;
			}

			~bidir_iterator( void ) {

				return ;
			}

			/*
			**	OVERLOAD OPERATORS
			*/
			bidir_iterator 		&operator=( bidir_iterator const &element ) {

				if (this != &element)
				{
					this->_root = element._root;
					this->_node = element._node;
					this->_null = element._null;
				}
				return (*this);
			}

			reference 			operator*( void ) const {

				return (this->_node->value);
			}

			pointer				operator->( void ) const {

				return (&operator*());
			}

			bidir_iterator 		&operator++( void ) {

				if (_node == max(_root))
				{
					_node = _null;
					return (*this);
				}
				else if (_node == _null)
				{
					_node = my_nullptr;
					return (*this);
				}
				_node = successor(_node);
				return (*this);
			}

			bidir_iterator 		operator++( int ) {

				bidir_iterator tmp(_root, _node, _null);
				operator++();
				return (tmp);
			}

			bidir_iterator		&operator--( void ) {

				if (_node == _null)
				{
					_node = max(_root);
					return (*this);
				}
				_node = predecessor(_node);
				return (*this);
			}

			bidir_iterator		operator--( int ) {

				bidir_iterator tmp(_root, _node, _null);
				operator--();
				return (tmp);
			}

			operator 			bidir_iterator<const T, Node>( void ) {

				return (bidir_iterator<const T, Node>(_root, _node, _null));
			}

			/*
			**	GETTERS
			*/
			ptr_node 			get_root( void ) const {

				return (_root);
			}

			ptr_node 			get_node( void ) const {

				return (_node);
			}

			ptr_node 			get_null( void ) const {

				return (_null);
			}

		private:
			ptr_node 			_root;
			ptr_node 			_node;
			ptr_node 			_null;

			ptr_node 			min( ptr_node node ) {

				while (node->left != _null)
					node = node->left;
				return (node);
			}

			ptr_node 			max( ptr_node node ) {

				while (node->right != _null)
					node = node->right;
				return (node);
			}

			ptr_node 			successor( ptr_node node ) {

				if (node->right != _null)
					return (min(node->right));
				ptr_node tmp = node->parent;
				while (tmp != _null && node == tmp->right)
				{
					node = tmp;
					tmp = tmp->parent;
				}
				return (tmp);
			}

			ptr_node 			predecessor( ptr_node node ) {

				if (node->left != _null)
					return (max(node->left));
				ptr_node tmp = node->parent;
				while (tmp != _null && node == tmp->left)
				{
					node = tmp;
					tmp = tmp->parent;
				}
				return (tmp);
			}

	};
	template <class T, class Node>
	bool operator==( bidir_iterator<T, Node> &lhs, bidir_iterator<T, Node> &rhs ) {

		return (lhs.get_node() == rhs.get_node());
	}

	template <class L, class R, class Node>
	bool operator==( const bidir_iterator<L, Node> &lhs, const bidir_iterator<R, Node> &rhs ) {

		return (lhs.get_node() == rhs.get_node());
	}

	template <class T, class Node>
	bool operator!=( bidir_iterator<T, Node> &lhs, bidir_iterator<T, Node> &rhs ) {

		return (lhs.get_node() != rhs.get_node());
	}

	template <class L, class R, class Node>
	bool operator!=( const bidir_iterator<L, Node> &lhs, const bidir_iterator<R, Node> & rhs ) {

		return (lhs.get_node() != rhs.get_node());
	}
}

#endif