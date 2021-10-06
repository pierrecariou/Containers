#ifndef ITERATORRANDOMACCESS_HPP
# define ITERATORRANDOMACCESS_HPP

#include "../iterator_common.hpp"

namespace ft {	

	// IteratorRandomAccesss
	template <typename It, typename Ref>
		class IteratorRandomAccess : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			typedef std::ptrdiff_t	difference_type;

			IteratorRandomAccess() {}
			IteratorRandomAccess(It x) : p(x) {}
			IteratorRandomAccess(const IteratorRandomAccess& mit) : p(mit.p) {}
			IteratorRandomAccess& operator++() {++p;return *this;}
			IteratorRandomAccess& operator--() {--p;return *this;}
			IteratorRandomAccess operator++(int) {IteratorRandomAccess tmp(*this); operator++(); return tmp;}
			IteratorRandomAccess operator--(int) {IteratorRandomAccess tmp(*this); operator--(); return tmp;}
			IteratorRandomAccess operator+(difference_type n) const {IteratorRandomAccess tmp(*this); tmp.p+=n; return tmp;}
			IteratorRandomAccess operator-(difference_type n) const {IteratorRandomAccess tmp(*this); tmp.p-=n; return tmp;}
			IteratorRandomAccess& operator+=(difference_type n) {p+=n; return *this;}
			IteratorRandomAccess& operator-=(difference_type n) {p-=n; return *this;}
			bool operator==(const IteratorRandomAccess& rhs) const {return p==rhs.p;}
			bool operator!=(const IteratorRandomAccess& rhs) const {return p!=rhs.p;}
			bool operator>(const IteratorRandomAccess& rhs) const {return p>rhs.p;}
			bool operator<(const IteratorRandomAccess& rhs) const {return p<rhs.p;}
			bool operator<=(const IteratorRandomAccess& rhs) const {return p<=rhs.p;}
			bool operator>=(const IteratorRandomAccess& rhs) const {return p>=rhs.p;}
			Ref operator*() {return *p;}
			Ref operator[](difference_type n) const { return *(operator+(n));}

		protected:
			It	p;
	};

	template <typename It, typename Ref>	
		class ReverseIteratorRandomAccess : public IteratorRandomAccess<It, Ref>
	{
		public:
			typedef std::ptrdiff_t	difference_type;

			ReverseIteratorRandomAccess() : parent() {}
			ReverseIteratorRandomAccess(It x) : parent(x){}
			ReverseIteratorRandomAccess(const ReverseIteratorRandomAccess& mit) : parent(mit) {}
			ReverseIteratorRandomAccess& operator++() {--this->p;return *this;}
			ReverseIteratorRandomAccess& operator--() {++this->p;return *this;}
			ReverseIteratorRandomAccess operator++(int) {ReverseIteratorRandomAccess tmp(*this); operator++(); return tmp;}
			ReverseIteratorRandomAccess operator--(int) {ReverseIteratorRandomAccess tmp(*this); operator--(); return tmp;}
			ReverseIteratorRandomAccess operator+(difference_type n) const {ReverseIteratorRandomAccess tmp(*this); tmp.p-=n; return tmp;}
			ReverseIteratorRandomAccess operator-(difference_type n) const {ReverseIteratorRandomAccess tmp(*this); tmp.p+=n; return tmp;}
			ReverseIteratorRandomAccess& operator+=(difference_type n) {this->p-=n; return *this;}
			ReverseIteratorRandomAccess& operator-=(difference_type n) {this->p+=n; return *this;}
			Ref operator[](difference_type n) const { return *(operator-(n));}

		private:
			typedef	IteratorRandomAccess<It, Ref>	parent;
	};
}

#endif
