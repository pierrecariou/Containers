#ifndef MAP_HPP
# define MAP_HPP

#include "IteratorBidirectional.hpp"
#include "utility.hpp"
#include "node.hpp"
#include "../algorithm.hpp"

#include <stdlib.h>
#include <sstream>
#include <unistd.h>

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
						value_type&, value_type > 											iterator;
				typedef IteratorBidirectional<node<value_type,
						allocator_type, key_type, mapped_type, key_compare>*,
						value_type&, value_type >											const_iterator;
				typedef ReverseIteratorBidirectional<node<value_type,
						allocator_type, key_type, mapped_type, key_compare>*,
						value_type&, value_type >											reverse_iterator;
				typedef ReverseIteratorBidirectional<node<value_type,
						allocator_type, key_type, mapped_type, key_compare>*,
						value_type&, value_type >											const_reverse_iterator;
				typedef std::ptrdiff_t												difference_type;
				typedef std::size_t													size_type;

				// CONSTRUCTORS //
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
					alloc(alloc), root(NULL), comp(comp) { }

				template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) : alloc(alloc), root(NULL), comp(comp) {
						for (InputIterator it = first; it != last; it++) {
							operator[](it->first) = it->second;
						}
					}

				map (const map& x) : alloc(x.alloc), root(NULL), comp(x.comp) {
					for (iterator it = x.begin(); it != x.end(); it++) {
						operator[](it->first) = it->second;
					}
				}

				// DESTRUCTORS //

				~map() {
					clear();
				}

				key_compare key_comp() const {
					return comp;
				}

				iterator begin() {
					return (empty()) ? iterator(NULL) : iterator(root->first);
				}

				const_iterator begin() const {
					return (empty()) ? const_iterator(NULL) : const_iterator(root->first);
				}

				reverse_iterator rbegin() {
					return (empty()) ? reverse_iterator(NULL) : reverse_iterator(root->last->root);
				}

				const_reverse_iterator rbegin() const {
					return (empty()) ? const_reverse_iterator(NULL) : const_reverse_iterator(root->last->root);
				}

				iterator end() {
					return (empty()) ? iterator(NULL) : iterator(root->last);
				}

				const_iterator end() const {
					return (empty()) ? const_iterator(NULL) : const_iterator(root->last);
				}

				reverse_iterator rend() {
					return (empty()) ? reverse_iterator(NULL) : reverse_iterator(root->first->left);
				}

				const_reverse_iterator rend() const {
					return (empty()) ? const_reverse_iterator(NULL) : const_reverse_iterator(root->first->left);
				}

				bool empty() const {
					return root==NULL;
				}

				size_type size() const {
					return (root == NULL) ? 0 : root->n;
				}

				mapped_type& operator[] (const key_type& k) {
					if (root == NULL)
						return ((root = new node(alloc, comp, 0, k))->data->second);
					//std::cout << k << ": " << root->first->data->first << "-->" << root->last->root->data->first << std::endl;
					return root->find(k)->data->second;
				}

				void erase (iterator position) {
					erase(position->first);
				}

				size_type erase (const key_type& k) {
					node_pointer p = root->find(k);	
					/*
					   if (p == root)
					   std::cout << "element is root" << std::endl;
					//std::cout << "p:" << p << " / "<< "r:" << root <<"-->" <<  "size: " << size() << std::endl;
					std::cout <<"--- " << root->data->first << " ---"  << std::endl;
					if (root->left == NULL)
					std::cout << "left: (null)" << std::endl;
					else if (root->left->data != NULL)
					std::cout << "left: " << root->left->data->first << std::endl;
					else if (root->left == root->first->left && root->left->data == NULL)
					std::cout << "left: " << "first-1" << std::endl;
					if (root->right == NULL)
					std::cout << "right: (null)" << std::endl;
					else if (root->right->data != NULL)
					std::cout << "right: " << root->right->data->first << std::endl;
					else if (root->right == root->last && root->right->data == NULL)
					std::cout << "right: " << "last" << std::endl;
					std::cout << "---------" << std::endl;
					 */
					if (p == root && size() == 1) { // map has only one element inside
						delete root->last;
						delete root->first->left;
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
					alloc.destroy(p->data);
					alloc.deallocate(p->data, 1);
					delete p;
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

				iterator find (const key_type& k) {
					for (iterator it = begin(); it != end(); it++) {
						if (!comp(it->first, k) && !comp(k, it->first))
							return it;
					}
					return end();
				}

				const_iterator find (const key_type& k) const {
					for (const_iterator it = begin(); it != end(); it++) {
						if (!comp(it->first, k) && !comp(k, it->first))
							return it;
					}
					return end();
				}

			private:
				typedef node<value_type, allocator_type, key_type, mapped_type, key_compare>*	node_pointer;
				typedef node<value_type, allocator_type, key_type, mapped_type, key_compare>	node;

				allocator_type							alloc;
				node_pointer							root;
				key_compare								comp;
		};
}

#endif
