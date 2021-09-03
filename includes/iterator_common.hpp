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

}

#endif
