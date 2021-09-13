#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "Iterator.hpp"

#include <iostream>

namespace ft {

	template <typename T, typename Allocator = std::allocator<T> >
		class vector {
			public:
				//define types
				typedef T												value_type;
				typedef value_type*										pointer;
				typedef const value_type*								const_pointer;
				typedef value_type&										reference;
				typedef const value_type&								const_reference;
				typedef Iterator<pointer, reference, value_type>					iterator;
				typedef Iterator<const_pointer, const_reference, value_type>		const_iterator;
				typedef ReverseIterator<pointer, reference, value_type>				reverse_iterator;
				typedef ReverseIterator<const_pointer, const_reference, value_type>	const_reverse_iterator;
				typedef std::ptrdiff_t									difference_type;
				typedef std::size_t										size_type;
				typedef Allocator										allocator_type;

				// CONSTRUCTORS //
				explicit vector (const allocator_type& alloc = allocator_type()) : alloc(alloc), n(0), c(0) { }

				explicit vector (size_type n, const value_type& val = value_type(),
				                 const allocator_type& alloc = allocator_type()) : alloc(alloc), n(n), c(n) {
					p = (first = this->alloc.allocate(n));
					for (size_type i = 0; i < n; i++) {
						*p = val;
						p++;
					}
					last = p;
				}

				template <class InputIterator>
				vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type()) : alloc(alloc) {
					n = 0;
					for (InputIterator i = first; i != last; i++)
						n++;
					c = n;
					p = (this->first = this->alloc.allocate(n));
					for (size_type i = 0; i < n; i++) {
						*p = *first;
						first++;
						p++;
					}
					this->last = p;
				}

				vector (const vector& x) : alloc(x.get_allocator()), n(x.size()), c(x.capacity()) {
					p = (this->first = this->alloc.allocate(c));
					for (const_iterator i = x.begin(); i != x.end(); i++)	{
						*p = *i;
						p++;
					}
					this->last = p;
				}

				// DESTRUCTORS //
				~vector() {
					if (!empty()) {
						p = first;
						for (size_type i = 0; i < n; i++)
							alloc.destroy(p++);
					}
					if (c != 0)
						alloc.deallocate(first, c);
				}

				// ASSIGN CONTENT //
				 vector& operator= (const vector& x) {
					~vector();
					c = x.capacity();
					n = x.size();
					p = (first = alloc.allocate(c));
					for (const_iterator i = x.begin(); i != x.end(); i++)	{
						*p = *i;
						p++;
					}
					this->last = p;
				}

				// ITERATORS //
				iterator begin() {
					return iterator(first);
				}
					  
				const_iterator begin() const {
					return const_iterator(first);
				}

				reverse_iterator rbegin() {
					return reverse_iterator(last - 1);
				}

				const_reverse_iterator rbegin() const {
					return const_reverse_iterator(last - 1);
				}

				iterator end() {
					return iterator(last);
				}
					  
				const_iterator end() const {
					return const_iterator(last);
				}

	 			reverse_iterator rend() {
					return reverse_iterator(first - 1);
				}
					  
				const_reverse_iterator rend() const {
					return const_reverse_iterator(first - 1);
				}

				// CAPACITY //
				size_type size() const {
					return n;
				}

				size_type max_size() const {
					return alloc.max_size();
				}

				void resize (size_type n, value_type val = value_type()) {
					p = first;
					if (n < size()) {
						for (size_t i = 0; i < this->n; i++) {
							if (i >= n){
								std::cout << "test" << std::endl;
								alloc.destroy(p);
							}
							else
								last = p + 1;
							p++;
						}
						this->n = n;
					} else if (n > size()) {
						if (n > c)
							std::cout <<  "realloc" << std::endl;
						for (size_t i = 0; i < n; i++) {
							if (i >= this->n)
								*p = val;	
							p++;
						}
						last = p;
						this->n = n;
					}
				}

				size_type capacity() const {
					return c;
				}

				allocator_type get_allocator() const {
					return alloc;
				}

				bool empty() const {
					return (n == 0);
				}

			private:
				allocator_type			alloc;
				size_type				n;
				size_type				c;
				pointer					first;
				pointer					last;
				pointer					p;
		};
}

#endif
