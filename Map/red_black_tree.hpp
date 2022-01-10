

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>
# include "../Headers/nullptr.hpp"

namespace ft
{
	template < class T >
	struct node
	{
		node			*parent;
		node			*left;
		node			*right;
		size_t			color;		// 0 black and 1 red
		T				value;

		node( void ) : parent(my_nullptr), left(my_nullptr), right(my_nullptr), color(0), value() {
	
			return ;
		}

		node( T const & v, node *p = my_nullptr, node *l = my_nullptr, node *r = my_nullptr, int c = 0 ) :
		parent(p), left(l), right(r), color(c), value(v) {

			return ;
		}

		node( node const &other ) : parent(other.parent), left(other.left), right(other.right), color(other.color), value(other.value) {

			return ;
		}

		node		&operator=( node const &element ) {

			if (this != &element)
			{
				this->parent = element.parent;
				this->left = element.left;
				this->right = element.right;
				this->color = element.color;
				this->value = element.value;
			}
			return (*this);
		}

		bool		operator==( node const &other ) {

			return (this->value == other.value);
		}
	};

	template< class T, class Compare, class Alloc = std::allocator<ft::node<T> > >
	class rbtree
	{
		public:
			// Same as map
			typedef T																value_type;
			typedef typename ft::node<T>											node_type;
			typedef Compare															value_compare;
			typedef Alloc															allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other		allocation;
			typedef typename allocator_type::reference 								reference;
			typedef typename allocator_type::const_reference 						const_reference;
			typedef typename allocator_type::pointer 								pointer;
			typedef typename allocator_type::const_pointer 							const_pointer;
			typedef typename allocator_type::difference_type 						difference_type;
			typedef typename allocator_type::size_type 								size_type;

			rbtree( value_compare const & cmp = value_compare())  : _size(0), _cmp(cmp) {

				_null = _alloc_test.allocate(1);
				_alloc_test.construct(_null, node_type());
				_root = _null;
				return ;
			}

			~rbtree( void ) {

				return ;
			}

			size_type max_size( void ) const {

				return (_alloc_test.max_size());
			}

			pointer search(value_type val) const {

				return (searchTreeHelper(_root, val));
			}

			pointer min_node( void ) const {

				return (min_node(_root));
			}

			pointer max_node( void ) const {

				return (max_node(_root));
			}

			pointer lower_bound(value_type const & val) const {

				pointer begin = min_node();
				while (begin != _null)
				{
					if (_cmp(begin->value, val) == false)
						break ;
					begin = successor(begin);
				}
				return (begin);
			}

			pointer upper_bound(value_type const & val) const {

				pointer begin = min_node();
				while (begin != _null)
				{
					if (_cmp(val, begin->value) == true)
						break ;
					begin = successor(begin);
				}
				return (begin);
			}

			void	swap(rbtree & x) {

				pointer tmp_r = _root;
				pointer tmp_n = _null;
				size_type tmp_s = _size;
				_root = x.get_root();
				_null = x.get_null();
				_size = x.get_size();
				x._root = tmp_r;
				x._null = tmp_n;
				x._size = tmp_s;
			}

			bool insert(value_type const & val) {

				pointer new_node = allocator_type().allocate(1);
				allocator_type().construct(new_node, node_type(val, my_nullptr, _null,_null, 1));
				pointer cur = my_nullptr;
				pointer root = _root;
				while (root != _null)
				{
					cur = root;
					if (_cmp(new_node->value, root->value))
						root = root->left;
					else if (_cmp(root->value, new_node->value))
						root = root->right;
					else
					{
						allocator_type().destroy(new_node);
						allocator_type().deallocate(new_node, 1);
						return (false);
					}
				}
				new_node->parent = cur;
				if (cur == my_nullptr)
					_root = new_node;
				else if (_cmp(new_node->value, cur->value))
					cur->left = new_node;
				else
					cur->right = new_node;
				if (new_node->parent == my_nullptr)
				{
					new_node->color = 0;
					_size++;
					return (true);
				}
				if (new_node->parent->parent == my_nullptr)
				{
					_size++;
					return (true);
				}
				fixInsert(new_node);
				_size++;
				return (true);
			}

			bool deleteNode( value_type const &value ) {

				return deleteNodeHelper(_root, value);
			}

			void destroy( void ) {

				_size = 0;
				ft_clear(_root);
				_root = _null;
				return ;
			}

			void destroynull( void ) {

				allocator_type().destroy(_null);
				allocator_type().deallocate(_null, 1);
				return ;
			}

			pointer successor( pointer node ) const {

				if (node->right != _null)
					return (min_node(node->right));
				if (node->parent == my_nullptr || node == max_node())
					return (_null);
				pointer tmp = node->parent;
				while (tmp != _null && node == tmp->right)
				{
					node = tmp;
					tmp = tmp->parent;
				}
				return (tmp);
			}

			/*
			**	Getters
			*/
			pointer	get_root( void ) const {

				return (_root);
			}

			pointer get_null( void ) const {

				return (_null);
			}

			size_type get_size( void ) const {

				return (_size);
			}

		private:
			/*
			**	Private functions
			*/
			void	ft_clear( pointer root ) {

				if (root == _null)
					return ;
				ft_clear(root->left);
				ft_clear(root->right);
				_alloc_test.destroy(root);
				_alloc_test.deallocate(root, 1);
				return ;
			}

			pointer	searchTreeHelper( pointer node, value_type const &value ) const {

				if (node == _null)
					return (node);
				else if (_cmp(value, node->value))
					return (searchTreeHelper(node->left, value));
				else if (_cmp(node->value, value))
					return (searchTreeHelper(node->right, value));
				else
					return (node);
			}

			pointer	min_node( pointer node ) const {

				if (node == my_nullptr || node == _null)
					return (_null);
				while (node->left != _null)
					node = node->left;
				return (node);
			}

			pointer	max_node( pointer node ) const {

				if (node == my_nullptr || node == _null)
					return (_null);
				while (node->right != _null)
					node = node->right;
				return (node);
			}

			void	leftRotate( pointer node ) {

				pointer tmp = node->right;
				node->right = tmp->left;
				if (tmp->left != _null)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (node->parent == my_nullptr)
					_root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;
				return ;
			}

			void	rightRotate( pointer node ) {

				pointer tmp = node->left;
				node->left = tmp->right;
				if (tmp->right != _null)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (node->parent == my_nullptr)
					_root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->right = node;
				node->parent = tmp;
				return ;
			}

			void	fixInsert( pointer node ) {

				pointer tmp = my_nullptr;
				while (node->parent->color == 1)
				{
					if (node->parent == node->parent->parent->right)
					{
						tmp = node->parent->parent->left;
						if (tmp->color == 1)
						{
							tmp->color = 0;
							node->parent->color = 0;
							node->parent->parent->color = 1;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								rightRotate(node);
							}
							node->parent->color = 0;
							node->parent->parent->color = 1;
							leftRotate(node->parent->parent);
						}
					}
					else
					{
						tmp = node->parent->parent->right;
						if (tmp->color == 1)
						{
							tmp->color = 0;
							node->parent->color = 0;
							node->parent->parent->color = 1;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent;
								leftRotate(node);
							}
							node->parent->color = 0;
							node->parent->parent->color = 1;
							rightRotate(node->parent->parent);
						}
					}
					if (node == _root)
						break ;
				}
				_root->color = 0;
				return ;
			}

			void	fixDelete( pointer node ) {

				pointer tmp = my_nullptr;
				while (node != _root && node->color == 0)
				{
					if (node == node->parent->left)
					{
						tmp = node->parent->right;
						if (tmp->color == 1)
						{
							tmp->color = 0;
							node->parent->color = 1;
							leftRotate(node->parent);
							tmp = node->parent->right;
						}
						if (tmp->left->color == 0 && tmp->right->color == 0)
						{
							tmp->color = 1;
							node = node->parent;
						}
						else
						{
							if (tmp->right->color == 0)
							{
								tmp->left->color = 0;
								tmp->color = 1;
								rightRotate(tmp);
								tmp = node->parent->right;
							}
							tmp->color = node->parent->color;
							node->parent->color = 0;
							tmp->right->color = 0;
							leftRotate(node->parent);
							node = _root;
						}
					}
					else
					{
						tmp = node->parent->left;
						if (tmp->color == 1)
						{
							tmp->color = 0;
							node->parent->color = 1;
							rightRotate(node->parent);
							tmp = node->parent->left;
						}
						if (tmp->left->color == 0 && tmp->right->color == 0)
						{
							tmp->color = 1;
							node = node->parent;
						}
						else
						{
							if (tmp->left->color == 0)
							{
								tmp->right->color = 0;
								tmp->color = 1;
								leftRotate(tmp);
								tmp = node->parent->left;
							}
							tmp->color = node->parent->color;
							node->parent->color = 0;
							tmp->left->color = 0;
							rightRotate(node->parent);
							node = _root;
						}
					}
				}
				node->color = 0;
				return ;
			}

			void	transplant( pointer node, pointer toTransplant ) {

				if (node->parent == my_nullptr)
					_root = toTransplant;
				else if (node == node->parent->left)
					node->parent->left = toTransplant;
				else
					node->parent->right = toTransplant;
				toTransplant->parent = node->parent;
				return ;
			}

			bool	deleteNodeHelper( pointer node, value_type const &key ) {

				pointer toDelete = _null;
				pointer tmp	= my_nullptr;
				pointer cur = my_nullptr;
				while (node != _null)
				{
					if (_cmp(node->value, key))
						node = node->right;
					else if (_cmp(key, node->value))
						node = node->left;
					else
					{
						toDelete = node;
						node = node->right;
					}
				}
				if (toDelete == _null)
					return (false);
				cur = toDelete;
				int tmp_color = cur->color;
				if (toDelete->left == _null)
				{
					tmp = toDelete->right;
					transplant(toDelete, toDelete->right);
				}
				else if (toDelete->right == _null)
				{
					tmp = toDelete->left;
					transplant(toDelete, toDelete->left);
				}
				else
				{
					cur = min_node(toDelete->right);
					tmp_color = cur->color;
					tmp = cur->right;
					if (cur->parent == toDelete)
						tmp->parent = cur;
					else
					{
						transplant(cur, cur->right);
						cur->right = toDelete->right;
						cur->right->parent = cur;	
					}
					transplant(toDelete, cur);
					cur->left = toDelete->left;
					cur->left->parent = cur;
					cur->color = toDelete->color;
				}
				_alloc_test.destroy(toDelete);
				_alloc_test.deallocate(toDelete, 1);
				if (tmp_color == 0)
					fixDelete(tmp);
				--_size;
				return (true);
			}

			pointer				_root;
			pointer				_null;
			size_type			_size;
			value_compare 		_cmp;
			allocation			_alloc_test;
	};
}


#endif