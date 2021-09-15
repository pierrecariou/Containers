#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft {
	
	template <class T>
	void	swap(T& a, T& b) {
		T	cp = a;
		a = b;
		b = cp;
	}

}

#endif
