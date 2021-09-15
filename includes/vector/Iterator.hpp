#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "../iterator_common.hpp"

namespace ft {

	// enable_if
	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };
	
	// is_integral	
	template <class T, T v>
	struct integral_constant {
		static const T value = v ;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		const operator T() { return v; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template <class T> struct is_integral : public false_type {};
	template<> struct is_integral<unsigned char> : public true_type {};
	template<> struct is_integral<unsigned short> : public true_type{};
	template<> struct is_integral<unsigned int> : public true_type{};
	template<> struct is_integral<unsigned long> : public true_type{};
	template<> struct is_integral<signed char> : public true_type{};
	template<> struct is_integral<short> : public true_type{};
	template<> struct is_integral<int> : public true_type{};
	template<> struct is_integral<long> : public true_type{};
	template<> struct is_integral<char> : public true_type{};
	template<> struct is_integral<bool> : public true_type{};

	// Iterators
	template <typename It, typename Ref, typename value_type>
		class Iterator : public iterator<typename iterator_traits<It>::iterator_category,
		typename iterator_traits<It>::value_type,
		typename iterator_traits<It>::difference_type,
		typename iterator_traits<It>::pointer,
		typename iterator_traits<It>::reference>
	{
		typedef std::ptrdiff_t									difference_type;
		public:
			Iterator() {}
			Iterator(It x) : p(x) {}
			Iterator(const Iterator& mit) : p(mit.p) {}
			Iterator& operator++() {++p;return *this;}
			Iterator& operator--() {--p;return *this;}
			Iterator operator++(value_type) {Iterator tmp(*this); operator++(); return tmp;}
			Iterator operator--(value_type) {Iterator tmp(*this); operator--(); return tmp;}
			Iterator operator+(difference_type n) const {Iterator tmp(*this); tmp.p+=n; return tmp;}
			Iterator operator-(difference_type n) const {Iterator tmp(*this); tmp.p-=n; return tmp;}
			bool operator==(const Iterator& rhs) const {return p==rhs.p;}
			bool operator!=(const Iterator& rhs) const {return p!=rhs.p;}
			bool operator>(const Iterator& rhs) const {return p>rhs.p;}
			bool operator<(const Iterator& rhs) const {return p<rhs.p;}
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
