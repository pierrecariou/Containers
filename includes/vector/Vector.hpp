#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "Iterator.hpp"

#include <iostream>

namespace ft {

	template <typename T, typename Allocator = std::allocator<T> >
		class vector {
			public:
				//define types
				typedef T									value_type;
				typedef value_type*							pointer;
				typedef const value_type*					const_pointer;
				typedef value_type&							reference;
				typedef const value_type&					const_reference;
				typedef Iterator<pointer>					iterator;
				typedef Iterator<const_pointer>				const_iterator;
				//typedef ReverseIterator<reference>			reverse_iterator;
				//typedef ReverseIterator<const_reference>	const_reverse_iterator;
				typedef std::ptrdiff_t						difference_type;
				typedef std::size_t							size_type;

				vector() {
					std::cout << "vector created" << std::endl;
				}

			private:

		};
}

#endif
