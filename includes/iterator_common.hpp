#ifndef ITERATOR_COMMON_HPP
# define ITERATOR_COMMON_HPP

#include <iostream>

namespace ft {

	template <typename Category, typename T, typename Distance = std::ptrdiff_t,
			 typename Pointer = T*, typename Reference = T&>
				 struct iterator {
					 typedef T         value_type;
					 typedef Distance  difference_type;
					 typedef Pointer   pointer;
					 typedef Reference reference;
					 typedef Category  iterator_category;
				 };

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template<typename Iter>
		struct iterator_traits
		{
			typedef typename Iter::value_type        value_type;
			typedef typename Iter::difference_type   difference_type;
			typedef typename Iter::pointer           pointer;
			typedef typename Iter::reference         reference;
			typedef typename Iter::iterator_category iterator_category;
		};

	template<typename T>
		struct iterator_traits<T*>
		{
			typedef T                         		value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef random_access_iterator_tag iterator_category;
		};

	template<typename T>
		struct iterator_traits<const T*>
		{
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef random_access_iterator_tag		iterator_category;
		};
	
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

	// distance
	typedef std::size_t	size_type;	

	template <class InputIterator>
	size_type	distance(InputIterator first, InputIterator last) {
		size_type	ret = 0;
		for (InputIterator it = first; it != last; it++)
			ret++;
		return ret;
	}
}

#endif
