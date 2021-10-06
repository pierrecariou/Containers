#ifndef MAP_HPP
# define MAP_HPP

#include "IteratorBidirectional.hpp"
#include "utility.hpp"
#include "node.hpp"
#include "../algorithm.hpp"

#include <stdlib.h>
#include <sstream>

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
				typedef IteratorBidirectional<node<value_type, allocator_type, key_type, mapped_type, key_compare>*, node<value_type, allocator_type, key_type, mapped_type, key_compare>& > iterator;
				typedef IteratorBidirectional<const_pointer, const_reference>		const_iterator;
				typedef ReverseIteratorBidirectional<pointer, reference>				reverse_iterator;
				typedef ReverseIteratorBidirectional<const_pointer, const_reference>	const_reverse_iterator;
				typedef std::ptrdiff_t												difference_type;
				typedef std::size_t													size_type;

				// CONSTRUCTORS //
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
					alloc(alloc), n(0), c(0), root(NULL), p(NULL), comp(comp) { }

				template <class InputIterator>
				map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
						        const allocator_type& alloc = allocator_type()) : alloc(alloc), comp(comp) {
					//n = ft::distance(first, last);
					//if ((c = n) == 0) {
					//	this->last = (this->first = NULL);
					//	return ;
					//}
					(void)comp;
					n = 0;
					*first = *first;
					*last = *last;
					for (InputIterator it = first; it != last; it++) {
						std::cout << "test" << std::endl;
						n++;
					}
				}

				map (const map& x);
				
					
				
				
				key_compare key_comp() const {
					return comp;
				}

				iterator begin() {
					return iterator(root->first);
				}

/**
				iterator end() {
					return iterator(last);
				}
				**/

				mapped_type& operator[] (const key_type& k) {
					if (root == NULL)
						return ((root = new node(alloc, comp, 0, k))->data->second);
					return root->find(k)->data->second;
				}

			private:
				typedef node<value_type, allocator_type, key_type, mapped_type, key_compare>*	node_pointer;
				typedef node<value_type, allocator_type, key_type, mapped_type, key_compare>	node;

				allocator_type							alloc;
				size_type								n;
				size_type								c;
				value_type*								pair;
				node_pointer							root;
				node_pointer							p;
				key_compare								comp;

		};
}

#endif
