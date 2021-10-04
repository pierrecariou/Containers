#ifndef MAP_HPP
# define MAP_HPP

#include "Iterator.hpp"
#include "utility.hpp"
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
				typedef pair<const key_type, mapped_type>	value_type;
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
				typedef Iterator<pointer, reference, value_type>					iterator;
				typedef Iterator<const_pointer, const_reference, value_type>		const_iterator;
				typedef ReverseIterator<pointer, reference, value_type>				reverse_iterator;
				typedef ReverseIterator<const_pointer, const_reference, value_type>	const_reverse_iterator;
				typedef std::ptrdiff_t												difference_type;
				typedef std::size_t													size_type;

				// CONSTRUCTORS //
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
					alloc(alloc), n(0), c(0), first(NULL), last(NULL), comp(comp) { }

/*
				template <class InputIterator>
				map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
						        const allocator_type& alloc = allocator_type()) : alloc(alloc) {
					n = ft::distance(first, last);
					if ((c = n) == 0) {
						this->last = (this->first = NULL);
						return ;
					}
					p = (this->first = this->alloc.allocate(n));
					for (size_type i = 0; i < n; i++) {
						*p = *first;
						first++;
						p++;
					}
					this->last = p;
				}
				*/

				map (const map& x);
				
				




					

				key_compare key_comp() const {
					return comp;
				}




			private:
				allocator_type			alloc;
				size_type				n;
				size_type				c;
				pointer					first;
				pointer					last;
				pointer					p;
				key_compare				comp;


		};
}

#endif
