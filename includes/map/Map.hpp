#ifndef MAP_HPP
# define MAP_HPP

#include "IteratorBidirectional.hpp"
#include "utility.hpp"
#include "node.hpp"
#include "../algorithm.hpp"

#include <stdlib.h>
#include <sstream>
#include <unistd.h>
#include <limits>

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
		class map {
			public:  
				// define types
				typedef Key										key_type;
				typedef T										mapped_type;
				typedef pair<const key_type, mapped_type>		value_type;
				typedef Compare									key_compare;
				class value_compare
				{
					friend class map;
					protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
					public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
				};
				typedef Alloc														allocator_type;
				typedef typename allocator_type::reference							reference;
				typedef typename allocator_type::const_reference					const_reference;
				typedef typename allocator_type::pointer							pointer;
				typedef typename allocator_type::const_pointer						const_pointer;
				typedef IteratorBidirectional<node<value_type,
						allocator_type, key_type, mapped_type, key_compare>*,
						value_type&, value_type, value_type > 											iterator;
				typedef IteratorBidirectional<node<value_type,
						allocator_type, key_type, mapped_type, key_compare>*,
						const value_type&, const value_type, value_type >											const_iterator;
				typedef ReverseIteratorBidirectional<node<value_type,
						allocator_type, key_type, mapped_type, key_compare>*,
						value_type&, value_type, value_type >											reverse_iterator;
				typedef ReverseIteratorBidirectional<node<value_type,
						allocator_type, key_type, mapped_type, key_compare>*,
						const value_type&, const value_type, value_type >											const_reverse_iterator;
				typedef std::ptrdiff_t												difference_type;
				typedef std::size_t													size_type;

				// CONSTRUCTORS //
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
					alloc(alloc), root(NULL), comp(comp) { }

				template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) : alloc(alloc), root(NULL), comp(comp) {
						for (InputIterator it = first; it != last; it++) {
							if (find(it->first) == end())
								operator[](it->first) = it->second;
						}
					}

				map (const map& x) : alloc(x.alloc), root(NULL), comp(x.comp) {
					for (iterator it = x.begin(); it != x.end(); it++) {
						operator[](it->first) = it->second;
					}
				}

				// DESTRUCTOR //
				~map() {
					clear();
				}

				// operator= //
				map& operator= (const map& x) {
					clear();
					for (iterator it = x.begin(); it != x.end(); it++) {
						operator[](it->first) = it->second;
					}
					return *this;
				}

				// ITERATORS
				iterator begin() {
					return (empty()) ? iterator(NULL) : iterator(root->first);
				}

				const_iterator begin() const {
					return (empty()) ? const_iterator(NULL) : const_iterator(root->first);
				}

				reverse_iterator rbegin() {
					return (empty()) ? reverse_iterator(NULL) : reverse_iterator(root->last);
				}

				const_reverse_iterator rbegin() const {
					return (empty()) ? const_reverse_iterator(NULL) : const_reverse_iterator(root->last);
				}

				iterator end() {
					return (empty()) ? iterator(NULL) : iterator(root->last);
				}

				const_iterator end() const {
					return (empty()) ? const_iterator(NULL) : const_iterator(root->last);
				}

				reverse_iterator rend() {
					return (empty()) ? reverse_iterator(NULL) : reverse_iterator(root->first);
				}

				const_reverse_iterator rend() const {
					return (empty()) ? const_reverse_iterator(NULL) : const_reverse_iterator(root->first);
				}

				// CAPACITY //
				bool empty() const {
					return root==NULL;
				}

				size_type size() const {
					return (root == NULL) ? 0 : root->n;
				}

				size_type max_size() const {
					return alloc.max_size();
				}

				// ELEMENT ACCESS //
				mapped_type& operator[] (const key_type& k) {
					if (root == NULL)
						return ((root = new node(alloc, comp, 0, k))->data->second);
					return root->find(k)->data->second;
				}
				
				// MODIFIERS //
				pair<iterator,bool> insert (const value_type& val) {
					iterator itfind;
					node_pointer newnode;

					if (root == NULL) {
						(root = new node(alloc, comp, 0, val.first))->data->second = val.second;
						return ft::make_pair(iterator(root), true);
					}
					if ((itfind = find(val.first)) != end())
						return ft::make_pair(itfind, false);
					(newnode = root->find(val.first))->data->second = val.second;
					return ft::make_pair(iterator(newnode), true);
				}

				iterator insert (iterator position, const value_type& val) {
					iterator itfind;
					node_pointer newnode;

					(void)position;
					if (root == NULL) {
						(root = new node(alloc, comp, 0, val.first))->data->second = val.second;
						return iterator(root);
					}
					if ((itfind = find(val.first)) != end())
						return itfind;
					(newnode = root->find(val.first))->data->second = val.second;
					return iterator(newnode);
				}

				template <class InputIterator>
				void insert (InputIterator first, InputIterator last) {
					for (InputIterator it = first; it != last; it++) {
						if (find(it->first) == end())
							operator[](it->first) = it->second;
					}
				}

				void erase (iterator position) {
					erase(position->first);
				}

				size_type erase (const key_type& k) {
					if (find(k) == end())
						return 0;
					node_pointer p = root->find(k);
					if (p == root && size() == 1) { // map has only one element inside
						root->last->deleteNode();
						root->first->left->deleteNode();
						root = NULL;
					} else if (p->right == NULL && p->left == NULL) // p is a leaf
						p->deleteLeaf();
					else if (!(p->right != NULL && p->left != NULL)) // p has one child
						p->deleteOneChild();
					else { // p has 2 children
						if (p == root)
							(root = p->deleteTwoChild(root))->becomeRoot(p);
						else
							p->deleteTwoChild(root);
					}
					p->deleteNode();
					if (root != NULL) {
						root->n-=1;
						root->first = root->findFirst(root);
					}
					return 1;
				}

				void erase (iterator first, iterator last) {
					if (empty())
						return ;
					iterator cp = first;
					for (iterator it = first; it != last; it = cp) {
						if (root->n != 1) {
							cp = ++it;
							--it;
						}
						erase(it);
						if (empty())
							break;
					}
				}

				void clear() {
					erase(begin(), end());
				}

				void swap (map& x) {
					ft::swap(alloc, x.alloc);
					ft::swap(root, x.root);
					ft::swap(comp, x.comp);
				}
				
				// OBSERVERS //
				key_compare key_comp() const {
					return comp;
				}

				value_compare value_comp() const {
					return value_compare(key_comp());
				}

				// OPERATIONS //
				iterator find (const key_type& k) {
					for (iterator it = begin(); it != end(); it++) {
						if (!comp(it->first, k) && !comp(k, it->first))
							return it;
					}
					return end();
				}

				const_iterator find (const key_type& k) const {
					for (iterator it = begin(); it != end(); it++) {
						if (!comp(it->first, k) && !comp(k, it->first))
							return it;
					}
					return end();
				}

				size_type count (const key_type& k) const {
					return (find(k) != end()) ? 1 : 0;
				}

				iterator lower_bound (const key_type& k) {
					for (iterator it = begin(); it != end(); it++) {
						if (!comp(it->first, k))
							return it;
					}
					return end();
				}

				const_iterator lower_bound (const key_type& k) const {
					for (iterator it = begin(); it != end(); it++) {
						if (!comp(it->first, k))
							return it;
					}
					return end();
				}

				iterator upper_bound (const key_type& k) {
					for (iterator it = begin(); it != end(); it++) {
						if (comp(k, it->first))
							return it;
					}
					return end();
				}

				const_iterator upper_bound (const key_type& k) const {
					for (iterator it = begin(); it != end(); it++) {
						if (comp(k, it->first))
							return it;
					}
					return end();
				}

				pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
					if (find(k) != end())
						return ft::make_pair(lower_bound(k), upper_bound(k));
					return ft::make_pair(upper_bound(k), upper_bound(k));
				}

				pair<iterator,iterator>             equal_range (const key_type& k) {
					if (find(k) != end())
						return ft::make_pair(lower_bound(k), upper_bound(k));
					return ft::make_pair(upper_bound(k), upper_bound(k));
				}

				// ALLOCATOR //
				allocator_type get_allocator() const {
					return alloc;
				}

			private:
				typedef node<value_type, allocator_type, key_type, mapped_type, key_compare>*	node_pointer;
				typedef node<value_type, allocator_type, key_type, mapped_type, key_compare>	node;

				allocator_type							alloc;
				node_pointer							root;
				key_compare								comp;
		};

		// Non-member function overloads
		template< class Key, class T, class Compare, class Alloc >
		bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
			return (!(lhs == rhs));
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator<  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
			return (!(rhs < lhs));
		}

		template< class Key, class T, class Compare, class Alloc >
		bool operator>  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
			return (rhs < lhs);
		}
		
		template< class Key, class T, class Compare, class Alloc >
		bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
			return (!(lhs < rhs));
		}
}

#endif
