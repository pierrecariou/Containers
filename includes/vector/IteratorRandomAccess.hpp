#ifndef ITERATORRANDOMACCESS_HPP
# define ITERATORRANDOMACCESS_HPP

#include "../iterator_common.hpp"
#include "Vector.hpp"

namespace ft {	

	// IteratorRandomAccesss
	template <typename It, typename Ref, typename value_type>
		class IteratorRandomAccess : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef IteratorRandomAccess<value_type*, value_type&, value_type> iterator;
			typedef IteratorRandomAccess<const value_type*, const value_type&, value_type> const_iterator;

			IteratorRandomAccess() {}
			IteratorRandomAccess(It x) : p(x) {}
			IteratorRandomAccess(const iterator& mit) : p(mit.p) {}
			IteratorRandomAccess& operator=(const iterator& rhs) {p = rhs.p; return *this;}
			IteratorRandomAccess& operator++() {++p;return *this;}
			IteratorRandomAccess& operator--() {--p;return *this;}
			IteratorRandomAccess operator++(int) {IteratorRandomAccess tmp(*this); operator++(); return tmp;}
			IteratorRandomAccess operator--(int) {IteratorRandomAccess tmp(*this); operator--(); return tmp;}
			IteratorRandomAccess operator+(difference_type n) const {return IteratorRandomAccess(p+n);}
			IteratorRandomAccess operator-(difference_type n) const {return IteratorRandomAccess(p-n);}
			friend IteratorRandomAccess operator+(difference_type n, const IteratorRandomAccess& rhs)
				{return rhs.p+n;}
			friend IteratorRandomAccess operator-(difference_type n, const IteratorRandomAccess& rhs)
				{return rhs.p-n;}
			difference_type operator+(const IteratorRandomAccess& rhs) const {return p+rhs.p;}
			difference_type operator-(const IteratorRandomAccess& rhs) const {return p-rhs.p;}
			IteratorRandomAccess& operator+=(difference_type n) {p+=n; return *this;}
			IteratorRandomAccess& operator-=(difference_type n) {p-=n; return *this;}
			bool operator==(const iterator& rhs) const {return p==rhs.p;}
			bool operator==(const const_iterator& rhs) const {return p==rhs.p;}
			bool operator!=(const iterator& rhs) const {return p!=rhs.p;}
			bool operator!=(const const_iterator& rhs) const {return p!=rhs.p;}
			bool operator>(const iterator& rhs) const {return p>rhs.p;}
			bool operator>(const const_iterator& rhs) const {return p>rhs.p;}
			bool operator<(const iterator& rhs) const {return p<rhs.p;}
			bool operator<(const const_iterator& rhs) const {return p<rhs.p;}
			bool operator<=(const iterator& rhs) const {return p<=rhs.p;}
			bool operator<=(const const_iterator& rhs) const {return p<=rhs.p;}
			bool operator>=(const iterator& rhs) const {return p>=rhs.p;}
			bool operator>=(const const_iterator& rhs) const {return p>=rhs.p;}
			Ref operator*() {return *p;}
			Ref operator[](difference_type n) const { return *(operator+(n));}
			It	operator->() {return p;}

		public:
			It	p;
	};

	template <typename It, typename Ref, typename value_type>
		class ReverseIteratorRandomAccess : public IteratorRandomAccess<It, Ref, value_type>
	{
		public:
			typedef std::ptrdiff_t	difference_type;
			typedef ReverseIteratorRandomAccess<value_type*, value_type&, value_type> rev_iterator;
			typedef IteratorRandomAccess<value_type*, value_type&, value_type> iterator;
			typedef IteratorRandomAccess<const value_type*, const value_type&, value_type> const_iterator;

			ReverseIteratorRandomAccess() : parent() {}
			ReverseIteratorRandomAccess(It x) : parent(x) {}
			ReverseIteratorRandomAccess(const rev_iterator& mit) : parent(static_cast<iterator>(mit)) {}
			ReverseIteratorRandomAccess(const iterator& mit) : parent(mit) {}
			ReverseIteratorRandomAccess(const const_iterator& mit) : parent(mit) {}
			ReverseIteratorRandomAccess& operator=(const rev_iterator& rhs) {this->p = rhs.p; return *this;}
			ReverseIteratorRandomAccess& operator++() {--this->p;return *this;}
			ReverseIteratorRandomAccess& operator--() {++this->p;return *this;}
			ReverseIteratorRandomAccess operator++(int) {ReverseIteratorRandomAccess tmp(*this); operator++(); return tmp;}
			ReverseIteratorRandomAccess operator--(int) {ReverseIteratorRandomAccess tmp(*this); operator--(); return tmp;}
			ReverseIteratorRandomAccess operator+(difference_type n) const {return ReverseIteratorRandomAccess(this->p-n);}
			ReverseIteratorRandomAccess operator-(difference_type n) const {return ReverseIteratorRandomAccess(this->p+n);}
			friend ReverseIteratorRandomAccess operator+(difference_type n, const ReverseIteratorRandomAccess& rhs)
				{return rhs.p-n;}
			friend ReverseIteratorRandomAccess operator-(difference_type n, const ReverseIteratorRandomAccess& rhs)
				{return rhs.p+n;}
			difference_type operator+(const ReverseIteratorRandomAccess& rhs) const {return (this->p+rhs.p)*-1;}
			difference_type operator-(const ReverseIteratorRandomAccess& rhs) const {return (this->p-rhs.p)*-1;}
			ReverseIteratorRandomAccess& operator+=(difference_type n) {this->p-=n; return *this;}
			ReverseIteratorRandomAccess& operator-=(difference_type n) {this->p+=n; return *this;}
			Ref operator[](difference_type n) const { return *(operator+(n));}
			IteratorRandomAccess<It, Ref, value_type>	base() const {return parent(*this);};
			Ref operator*() {return *(this->p-1);}
			It	operator->() {return this->p-1;}
			bool operator>(const iterator& rhs) const {return this->p<rhs.p;}
			bool operator>(const const_iterator& rhs) const {return this->p<rhs.p;}
			bool operator<(const iterator& rhs) const {return this->p>rhs.p;}
			bool operator<(const const_iterator& rhs) const {return this->p>rhs.p;}
			bool operator<=(const iterator& rhs) const {return this->p>=rhs.p;}
			bool operator<=(const const_iterator& rhs) const {return this->p>=rhs.p;}
			bool operator>=(const iterator& rhs) const {return this->p<=rhs.p;}
			bool operator>=(const const_iterator& rhs) const {return this->p<=rhs.p;}

		private:
			typedef	IteratorRandomAccess<It, Ref, value_type>	parent;
	};
}

#endif
