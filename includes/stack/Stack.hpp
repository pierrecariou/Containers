#ifndef STACK_HPP
# define STACK_HPP

#include "../vector/Vector.hpp"

#include <stdlib.h>
#include <sstream>

namespace ft {

	template <class T, class Container = vector<T> >
		class stack {

			public:
				typedef T			value_type;
				typedef Container	container_type;
				typedef std::size_t	size_type;

				explicit stack (const container_type& ctnr = container_type()) : ctnr(ctnr) { }

				bool empty() const {
					return ctnr.empty();
				}

				size_type size() const {
					return ctnr.size();
				}

				value_type& top() {
					return ctnr.back();
				}

				const value_type& top() const {
					return ctnr.back();
				}

				void push (const value_type& val) {
					ctnr.push_back(val);
				}

				void pop() {
					ctnr.pop_back();
				}

				friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
					return (lhs.ctnr==rhs.ctnr);
				}

				friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
					return (lhs.ctnr<rhs.ctnr);
				}

			private:
				container_type	ctnr;
		};

	template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (!(lhs==rhs));
		}

	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (!(rhs<lhs));
		}

	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return rhs<lhs;
		}

	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (!(lhs<rhs));
		}
}

#endif
