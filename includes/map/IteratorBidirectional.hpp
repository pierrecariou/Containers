#ifndef ITERATORBIDIRECTIONAL_HPP
# define ITERATORBIDIRECTIONAL_HPP

#include "../iterator_common.hpp"

namespace ft {	

	// IteratorBidirectional
	template <typename It, typename Ref, typename Pair, typename value_type>
		class IteratorBidirectional : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef IteratorBidirectional<It, value_type&, value_type, value_type> iterator;
			typedef IteratorBidirectional<It, const value_type&, const value_type, value_type> const_iterator;

			IteratorBidirectional() {}
			IteratorBidirectional(It x) : p(x) {}
			IteratorBidirectional(const iterator& mit) : p(mit.p) {}
			IteratorBidirectional(const const_iterator& mit) : p(mit.p) {}
			IteratorBidirectional& operator++() {p = ++(*p);return *this;}
			IteratorBidirectional& operator--() {p = --(*p);return *this;}
			IteratorBidirectional operator++(int) {IteratorBidirectional tmp(*this); operator++(); return tmp;}
			IteratorBidirectional operator--(int) {IteratorBidirectional tmp(*this); operator--(); return tmp;}
			bool operator==(const iterator& rhs) const {if (p==NULL || rhs.p==NULL) {return true;} return p->data==rhs.p->data;}
			bool operator==(const const_iterator& rhs) const {if (p==NULL || rhs.p==NULL) {return true;} return p->data==rhs.p->data;}
			bool operator!=(const iterator& rhs) const {if (p==NULL || rhs.p==NULL) {return false;} return p->data!=rhs.p->data;}
			bool operator!=(const const_iterator& rhs) const {if (p==NULL || rhs.p==NULL) {return false;} return p->data!=rhs.p->data;}
			Ref operator*() const {return *(p->data);}
			Pair* operator->() const {return p->data;}

		public:
			It	p;
	};

	template <typename It, typename Ref, typename Pair, typename value_type>	
		class ReverseIteratorBidirectional : public IteratorBidirectional<It, Ref, Pair, value_type>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef ReverseIteratorBidirectional<It, value_type*, value_type&, value_type> rev_iterator;
			typedef ReverseIteratorBidirectional<It, const value_type*, const value_type&, value_type> const_rev_iterator;
			typedef IteratorBidirectional<It, value_type*, value_type&, value_type> iterator;
			typedef IteratorBidirectional<It, const value_type*, const value_type&, value_type> const_iterator;

			ReverseIteratorBidirectional() : parent() {}
			ReverseIteratorBidirectional(It x) : parent(x) {}
			ReverseIteratorBidirectional(const ReverseIteratorBidirectional& mit) : parent(mit) {}
			ReverseIteratorBidirectional(const IteratorBidirectional<It, Ref, Pair, value_type>& mit) : parent(mit) {}
			ReverseIteratorBidirectional& operator=(const ReverseIteratorBidirectional& rhs) {this->p = rhs.p; return *this;}
			ReverseIteratorBidirectional& operator++() {this->p = --(*this->p);return *this;}
			ReverseIteratorBidirectional& operator--() {this->p = ++(*this->p);return *this;}
			ReverseIteratorBidirectional operator++(int) {ReverseIteratorBidirectional tmp(*this); operator++(); return tmp;}
			ReverseIteratorBidirectional operator--(int) {ReverseIteratorBidirectional tmp(*this); operator--(); return tmp;}
			IteratorBidirectional<It, Ref, Pair, value_type> base() const {return parent(this->p);}
			Ref operator*() const {return *(this->p->findPrev(this->p, NULL)->data);}
			Pair* operator->() const {return this->p->findPrev(this->p, NULL)->data;}

		private:
			typedef	IteratorBidirectional<It, Ref, Pair, value_type>	parent;
	};
}

#endif
