#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "../iterator_common.hpp"

namespace ft {

	template <typename It>	
		class Iterator : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		public:
			Iterator() {}
			Iterator(It* x) : p(x){}
			Iterator(const Iterator& mit) : p(mit.p) {}
			Iterator& operator++() {++p;return *this;}
			Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}
			bool operator==(const Iterator& rhs) const {return p==rhs.p;}
			bool operator!=(const Iterator& rhs) const {return p!=rhs.p;}
			int& operator*() {return *p;}
		private:
			It*	p;
	};

}

#endif
