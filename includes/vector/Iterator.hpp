#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "../iterator_common.hpp"

namespace ft {	

	// Iterators
	template <typename It, typename Ref, typename value_type>
		class Iterator : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			typedef std::ptrdiff_t	difference_type;

			Iterator() {}
			Iterator(It x) : p(x) {}
			Iterator(const Iterator& mit) : p(mit.p) {}
			Iterator& operator++() {++p;return *this;}
			Iterator& operator--() {--p;return *this;}
			Iterator operator++(value_type) {Iterator tmp(*this); operator++(); return tmp;}
			Iterator operator--(value_type) {Iterator tmp(*this); operator--(); return tmp;}
			Iterator operator+(difference_type n) const {Iterator tmp(*this); tmp.p+=n; return tmp;}
			Iterator operator-(difference_type n) const {Iterator tmp(*this); tmp.p-=n; return tmp;}
			Iterator& operator+=(difference_type n) {p+=n; return *this;}
			Iterator& operator-=(difference_type n) {p-=n; return *this;}
			bool operator==(const Iterator& rhs) const {return p==rhs.p;}
			bool operator!=(const Iterator& rhs) const {return p!=rhs.p;}
			bool operator>(const Iterator& rhs) const {return p>rhs.p;}
			bool operator<(const Iterator& rhs) const {return p<rhs.p;}
			bool operator<=(const Iterator& rhs) const {return p<=rhs.p;}
			bool operator>=(const Iterator& rhs) const {return p>=rhs.p;}
			Ref operator*() {return *p;}
			Ref operator[](difference_type n) const { return *(operator+(n));}

		protected:
			It	p;
	};

	template <typename It, typename Ref, typename value_type>	
		class ReverseIterator : public Iterator<It, Ref, value_type>
	{
		public:
			typedef std::ptrdiff_t	difference_type;

			ReverseIterator() : parent() {}
			ReverseIterator(It x) : parent(x){}
			ReverseIterator(const ReverseIterator& mit) : parent(mit) {}
			ReverseIterator& operator++() {--this->p;return *this;}
			ReverseIterator& operator--() {++this->p;return *this;}
			ReverseIterator operator++(value_type) {ReverseIterator tmp(*this); operator++(); return tmp;}
			ReverseIterator operator--(value_type) {ReverseIterator tmp(*this); operator--(); return tmp;}
			ReverseIterator operator+(difference_type n) const {ReverseIterator tmp(*this); tmp.p-=n; return tmp;}
			ReverseIterator operator-(difference_type n) const {ReverseIterator tmp(*this); tmp.p+=n; return tmp;}
			ReverseIterator& operator+=(difference_type n) {this->p-=n; return *this;}
			ReverseIterator& operator-=(difference_type n) {this->p+=n; return *this;}
			Ref operator[](difference_type n) const { return *(operator-(n));}

		private:
			typedef	Iterator<It, Ref, value_type>	parent;
	};
}

#endif
