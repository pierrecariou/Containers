#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "../iterator_common.hpp"

namespace ft {

	template <typename It, typename Ref, typename value_type>
		class Iterator : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			Iterator() {}
			Iterator(It x) : p(x) {}
			Iterator(const Iterator& mit) : p(mit.p) {}
			Iterator& operator++() {++p;return *this;}
			Iterator operator++(value_type) {Iterator tmp(*this); operator++(); return tmp;}
			bool operator==(const Iterator& rhs) const {return p==rhs.p;}
			bool operator!=(const Iterator& rhs) const {return p!=rhs.p;}
			Ref operator*() {return *p;}
		private:
			It	p;
	};

	template <typename It, typename Ref, typename value_type>	
		class ReverseIterator : public Iterator<It, Ref, value_type>
	{
		public:
			ReverseIterator() {}
			ReverseIterator(It x) : p(x) {}
			ReverseIterator(const ReverseIterator& mit) : p(mit.p) {}
			ReverseIterator& operator++() {--p;return *this;}
			ReverseIterator operator++(value_type) {ReverseIterator tmp(*this); operator++(); return tmp;}
			bool operator==(const ReverseIterator& rhs) const {return p==rhs.p;}
			bool operator!=(const ReverseIterator& rhs) const {return p!=rhs.p;}
			Ref operator*() {return *p;}
		private:
			It	p;
	};
}

#endif
