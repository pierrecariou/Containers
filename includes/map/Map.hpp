#ifndef MAP_HPP
# define MAP_HPP

#include "Iterator.hpp"
#include "../algorithm.hpp"

#include <stdlib.h>
#include <sstream>

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
		class map {
			public:  

				typedef Key										key_type;
				typedef T										mapped_type;
				typedef std::pair<const key_type, mapped_type>	value_type;
				typedef Compare									key_compare;

				class value_compare
				{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
					friend class map;
					protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
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


			private:

		};
}

#endif
