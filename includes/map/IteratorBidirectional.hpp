#ifndef ITERATORBIDIRECTIONAL_HPP
# define ITERATORBIDIRECTIONAL_HPP

#include "../iterator_common.hpp"

namespace ft {	

	// IteratorBidirectional
	template <typename It, typename Ref, typename Pair>
		class IteratorBidirectional : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef Pair			value_type;

			IteratorBidirectional() {}
			IteratorBidirectional(It x) : p(x) {}
			IteratorBidirectional(const IteratorBidirectional& mit) : p(mit.p) {}
			IteratorBidirectional& operator++() {p = ++(*p);return *this;}
			IteratorBidirectional& operator--() {p = --(*p);return *this;}
			IteratorBidirectional operator++(int) {IteratorBidirectional tmp(*this); operator++(); return tmp;}
			IteratorBidirectional operator--(int) {IteratorBidirectional tmp(*this); operator--(); return tmp;}
			bool operator==(const IteratorBidirectional& rhs) const {return p->data==rhs.p->data;}
			bool operator!=(const IteratorBidirectional& rhs) const {return p->data!=rhs.p->data;}
			Ref operator*() {return *(p->data);}
			value_type* operator->() {return p->data;}

		protected:
			It	p;
	};

	template <typename It, typename Ref, typename Pair>	
		class ReverseIteratorBidirectional : public IteratorBidirectional<It, Ref, Pair>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef Pair			value_type;

			ReverseIteratorBidirectional() : parent() {}
			ReverseIteratorBidirectional(It x) : parent(x){}
			ReverseIteratorBidirectional(const ReverseIteratorBidirectional& mit) : parent(mit) {}
			ReverseIteratorBidirectional& operator++() {this->p = --(*this->p);return *this;}
			ReverseIteratorBidirectional& operator--() {this->p = ++(*this->p);}
			ReverseIteratorBidirectional operator++(int) {ReverseIteratorBidirectional tmp(*this); operator++(); return tmp;}
			ReverseIteratorBidirectional operator--(int) {ReverseIteratorBidirectional tmp(*this); operator--(); return tmp;}

		private:
			typedef	IteratorBidirectional<It, Ref, Pair>	parent;
	};
}

#endif
