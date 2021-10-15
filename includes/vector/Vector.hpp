#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "IteratorRandomAccess.hpp"
#include "../algorithm.hpp"

#include <stdlib.h>
#include <sstream>

namespace ft {

	template <typename T, typename Allocator = std::allocator<T> >
		class vector {
			public:
				//define types
				typedef T															value_type;
				typedef value_type*													pointer;
				typedef const value_type*											const_pointer;
				typedef value_type&													reference;
				typedef const value_type&											const_reference;
				typedef IteratorRandomAccess<pointer, reference>					iterator;
				typedef IteratorRandomAccess<const_pointer, const_reference>		const_iterator;
				typedef ReverseIteratorRandomAccess<pointer, reference>				reverse_iterator;
				typedef ReverseIteratorRandomAccess<const_pointer, const_reference>	const_reverse_iterator;
				typedef std::ptrdiff_t												difference_type;
				typedef std::size_t													size_type;
				typedef Allocator													allocator_type;

				// CONSTRUCTORS //
				explicit vector (const allocator_type& alloc = allocator_type()) :
								alloc(alloc), n(0), c(0), first(NULL), last(NULL) { }

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
				vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value,
				InputIterator>::type last, const allocator_type& alloc = allocator_type()) : alloc(alloc) {
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
					c = (n = ft::distance(first, last));
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

				void push_back (const value_type& val) {
					reserve(n + 1);
					n+=1;
					*last = val;
					last+=1;
				}

				void pop_back() {
					alloc.destroy(last - 1);
					n-=1;
					last-=1;
				}

				iterator insert (iterator position, const value_type& val) {
					vector<value_type>	tmp(*this);
					iterator	it_tmp = tmp.begin();
					iterator	ret;
					size_t		pos = ft::distance(begin(), position);
					reserve(n + 1);
					n+=1;
					last+=1;
					p = first;
					for (size_t i = 0; i < pos; i++) {
						p++;
						it_tmp++;
					}
					alloc.destroy(p);
					*p++ = val;
					ret = iterator(p - 1);
					for (iterator it = it_tmp; it != tmp.end(); it++) {
							alloc.destroy(p);
							*p++ = *it_tmp++;
					}
					return ret;
				}

				void insert (iterator position, size_type n, const value_type& val) {
					vector<value_type>	tmp(*this);
					iterator	it_tmp = tmp.begin();
					size_t		pos = ft::distance(begin(), position);
					reserve(this->n + n);
					this->n+=n;
					last+=n;
					p = first;
					for (size_t i = 0; i < pos; i++) {
						p++;
						it_tmp++;
					}
					for (size_type i = 0; i < n; i++) {
						alloc.destroy(p);
						*p++ = val;
					}
					for (iterator it = it_tmp; it != tmp.end(); it++) {
							alloc.destroy(p);
							*p++ = *it_tmp++;
					}
				}

				template <class InputIterator>
				void insert (iterator position, InputIterator first,
							typename enable_if<!is_integral<InputIterator>::value,
							InputIterator>::type last) {
					vector<value_type>	tmp(*this);
					iterator			it_tmp = tmp.begin();
					size_t				count = ft::distance(first, last);
					size_t				pos = ft::distance(begin(), position);
					reserve(this->n + count);
					this->n+=count;
					this->last+=count;
					p = this->first;
					for (size_t i = 0; i < pos; i++) {
						p++;
						it_tmp++;
					}
					for (InputIterator it = first; it != last; it++) {
						alloc.destroy(p);
						*p++ = *it;
					}
					for (iterator it = it_tmp; it != tmp.end(); it++) {
							alloc.destroy(p);
							*p++ = *it_tmp++;
					}
				}
				
				iterator erase (iterator position) {
					vector<value_type>	tmp(*this);
					iterator			it_tmp = tmp.begin();
					iterator			ret;
					iterator			cp;
					p = first;
					n-=1;
					for (iterator it = begin(); it != position; it++) {
						p++;
						it_tmp++;
					}
					it_tmp++;
					cp = it_tmp;
					for (iterator it = it_tmp; it < tmp.end(); it++) {
						alloc.destroy(p);
						*p = *it_tmp;
						if (cp == it_tmp)
							ret = iterator(p);
						p++;
						it_tmp++;
					}
					for (iterator it = iterator(p); it < end(); it++) {
						alloc.destroy(p);
						p++;
					}
					last-=1;
					return (ret);
				}

				iterator erase (iterator first, iterator last) {
					vector<value_type>	tmp(*this);
					iterator			it_tmp = tmp.begin();
					iterator			ret;
					iterator			cp;
					size_t				count = ft::distance(first, last);
					p = this->first;
					n-=count;
					for (iterator it = begin(); it != first; it++) {
						p++;
						it_tmp++;
					}
					it_tmp+=count;
					cp = it_tmp;
					for (iterator it = first; it != last; it++) {
						alloc.destroy(p);
						if (it_tmp < tmp.end())
							*p = *it_tmp;
						if (cp == it_tmp)
							ret = iterator(p);
						p++;
						it_tmp++;
					}
					for (iterator it = it_tmp; it < tmp.end(); it++) {
						alloc.destroy(p);
						*p = *it_tmp;
						p++;
						it_tmp++;
					}
					for (iterator it = iterator(p); it < end(); it++) {
						alloc.destroy(p);
						p++;
					}
					this->last-=count;
					return (ret);
				}

				void swap (vector& x) {
					ft::swap(alloc, x.alloc);
					ft::swap(n, x.n);
					ft::swap(c, x.c);
					ft::swap(first, x.first);
					ft::swap(last, x.last);
				}

				void clear() {
					p = first;
					for (size_type i = 0; i < n; i++)
						alloc.destroy(p++);
					n = 0;
					last = first;
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

		// Non-member function overloads
		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(lhs == rhs));
		}

		template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(rhs < lhs));
		}

		template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (rhs < lhs);
		}

		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(lhs < rhs));
		}

		template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
			x.swap(y);
		}
}

#endif
