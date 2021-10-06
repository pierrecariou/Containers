#ifndef ITERATORBIDIRECTIONAL_HPP
# define ITERATORBIDIRECTIONAL_HPP

#include "../iterator_common.hpp"

namespace ft {	

	// IteratorBidirectional
	template <typename It, typename Ref>
		class IteratorBidirectional : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			typedef std::ptrdiff_t	difference_type;

			IteratorBidirectional() {}
			IteratorBidirectional(It x) : p(x) {}
			IteratorBidirectional(const IteratorBidirectional& mit) : p(mit.p) {}
			IteratorBidirectional& operator++() {++p;return *this;}
			IteratorBidirectional& operator--() {--p;return *this;}
			IteratorBidirectional operator++(int) {IteratorBidirectional tmp(*this); operator++(); return tmp;}
			IteratorBidirectional operator--(int) {IteratorBidirectional tmp(*this); operator--(); return tmp;}
			bool operator==(const IteratorBidirectional& rhs) const {return p==rhs.p;}
			bool operator!=(const IteratorBidirectional& rhs) const {return p!=rhs.p;}
			Ref operator*() {return *p;}

		protected:
			It	p;
	};

	template <typename It, typename Ref>	
		class ReverseIteratorBidirectional : public IteratorBidirectional<It, Ref>
	{
		public:
			typedef std::ptrdiff_t	difference_type;

			ReverseIteratorBidirectional() : parent() {}
			ReverseIteratorBidirectional(It x) : parent(x){}
			ReverseIteratorBidirectional(const ReverseIteratorBidirectional& mit) : parent(mit) {}
			ReverseIteratorBidirectional& operator++() {--this->p;return *this;}
			ReverseIteratorBidirectional& operator--() {++this->p;return *this;}
			ReverseIteratorBidirectional operator++(int) {ReverseIteratorBidirectional tmp(*this); operator++(); return tmp;}
			ReverseIteratorBidirectional operator--(int) {ReverseIteratorBidirectional tmp(*this); operator--(); return tmp;}

		private:
			typedef	IteratorBidirectional<It, Ref>	parent;
	};
}

#endif
