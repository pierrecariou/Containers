#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "Iterator.hpp"

#include <stdlib.h>
#include <sstream>

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
				explicit vector (const allocator_type& alloc = allocator_type()) : alloc(alloc), n(0), c(0), first(NULL), last(NULL) { }

				explicit vector (size_type n, const value_type& val = value_type(),
				                 const allocator_type& alloc = allocator_type()) : alloc(alloc), n(n), c(n) {
					if (c == 0) {
						last = (first = NULL);
						return ;
					}
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

				vector (const vector& x) : alloc(x.get_allocator()), n(x.size()), c(x.capacity()) {
					if (c == 0) {
						last = (first = NULL);
						return ;
					}
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
					if (c == 0) {
						last = (first = NULL);
						return ;
					}
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
						if (n == 0)
							last = first;
						for (size_t i = 0; i < this->n; i++) {
							if (i >= n)
								alloc.destroy(p);
							else
								last = p + 1;
							p++;
						}
						this->n = n;
					} else if (n > size()) {
						reserve(n);
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

				bool empty() const {
					return (n == 0);
				}

				void reserve (size_type n) {
					if (n > max_size())
						throw (std::length_error("vector::_M_fill_insert"));
					if (n > capacity()) {
						vector<value_type>	tmp = *this;
						this->~vector();
						p = (first = this->alloc.allocate((c = (n > size() * 2) ? n : size() * 2)));
						for (iterator it = tmp.begin(); it != tmp.end(); it++) {
							*p = *it;
							p++;
						}
						last = p;
					}
					p = first;
				}

				// ELEMENT ACCESS //
				reference operator[] (size_type n) {
					p = first;
					for (size_type i = 0; i < n; i++)
						p++;
					return *p;
				}
				const_reference operator[] (size_type n) const {
					return operator[](n);
				}	

				reference at (size_type n) {
					if (n >= size()) {
						std::stringstream n_s;
						std::stringstream size_s;
						n_s << n;
						size_s << size();
						throw std::out_of_range("vector::_M_range_check: __n (which is " +
						n_s.str() +") >= this->size() (which is " + size_s.str() + ")");
					}
					return operator[](n);
				}
				
				const_reference at (size_type n) const {
					return at(n);
				}

				reference front() {
					return *first;
				}

				const_reference front() const {
					return front();
				}

				reference back() {
					return *(last - 1);
				}

				const_reference back() const {
					return back();
				}

				// MODIFIERS //
				template <class InputIterator>
				void assign (InputIterator first, typename enable_if<!is_integral<InputIterator>::value,
							InputIterator>::type last) {
					this->~vector();
					if (first == last) {
						this->n = (c = 0);
						first = (last = NULL);
						return ;
					}
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

				void assign (size_type n, const value_type& val) {
					this->~vector();
					if (n == 0) {
						this->n = (c = n);
						first = (last = NULL);
						return ;
					}
					p = (first = this->alloc.allocate((this->n = (c = n))));
					for (size_type i = 0; i < n; i++) {
						*p = val;
						p++;
					}
					last = p;
				}

				// ALLOCATOR //
				allocator_type get_allocator() const {
					return alloc;
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
