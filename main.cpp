#include <iostream>
#include <string>
#include <deque>
#if STL //CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include "includes/map/Map.hpp"
#include "includes/stack/Stack.hpp"
#include "includes/vector/Vector.hpp"
#endif

#include <stdlib.h>
#include <unistd.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))
/**

  template<typename T>
  class MutantStack : public ft::stack<T>
  {
  public:
  MutantStack() {}
  MutantStack(const MutantStack<T>& src) { *this = src; }
  MutantStack<T>& operator=(const MutantStack<T>& rhs) 
  {
  this->c = rhs.c;
  return *this;
  }
  ~MutantStack() {}

  typedef typename ft::stack<T>::container_type::iterator iterator;

  iterator begin() { return this->c.begin(); }
  iterator end() { return this->c.end(); }
  };
 **/

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

void	test_delete_map(int i) {
	std::cout << std::endl;
	std::cout << "TEST: " << i << std::endl;
	ft::map<int,int> first;

	first[12]=10;
	first[5]=50;
	first[3]=70;
	first[7]=100;
	first[1]=90;
	first[9]=90;
	first[8]=90;
	first[11]=90;
	first[14]=90;
	first[13]=90;
	first[17]=90;
	first[20]=90;
	first[18]=90;
	first[16]=90;

	first[2]=90;
	first[4]=90;
	first[6]=90;
	first[10]=90;
	first[15]=90;
	first[19]=90;


	ft::map<int, int>::iterator it;

	it=first.find(i);
	first.erase(it);

	for (ft::map<int, int>::iterator it = first.begin(); it != first.end(); it++) {
		std::cout << "[" << it->first << ", " << it->second << "]" << std::endl;
		//third.erase(it);
		//sleep(1);
	}
}

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	//ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	//	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	//	ft::map<int, int> map_int;
	//ft::vector<int> *test = new ft::vector<int>();
	//(void)test;
	ft::vector<int> v(4);
	ft::vector<int> vc(v.begin(), v.end());
	ft::vector<int> vcc(vc);
	ft::vector<int> vccc = v;

	for(ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << "\n";
	}
	std::cout << std::endl;
	for(ft::vector<int>::iterator it = vc.begin(); it != vc.end(); ++it) {
		std::cout << *it << "\n";
	}
	std::cout << std::endl;
	for(ft::vector<int>::iterator it = vcc.begin(); it != vcc.end(); ++it) {
		std::cout << *it << "\n";
	}
	std::cout << std::endl;

	vccc.resize(3);
	std::cout << "c: " << vccc.capacity() << std::endl;
	vccc.resize(5);
	std::cout << "c: " << vccc.capacity() << std::endl;
	vccc.resize(10);
	std::cout << "c: " << vccc.capacity() << std::endl;
	vccc.resize(0);
	std::cout << "c: " << vccc.capacity() << std::endl;
	for(ft::vector<int>::iterator it = vccc.begin(); it != vccc.end(); ++it) {
		std::cout << *it << "\n";
	}
	std::cout << "max size vccc: "<< vccc.max_size() << std::endl;

	ft::vector<int> myvector (5);  // 5 default-constructed ints

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';




	ft::vector<int> myvecto (10);   // 10 zero-initialized elements

	ft::vector<int>::size_type sz = myvecto.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvecto[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvecto[sz-1-i];
		myvecto[sz-1-i]=myvecto[i];
		myvecto[i]=temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvecto[i];
	std::cout << '\n';


	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	first.assign(7,100);             // 7 ints with a value of 100

	ft::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.




	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';
	third.assign(0, 100);
	std::cout << "Size of third: " << int (third.size()) << '\n';
	third.assign(first.begin(), first.end());
	std::cout << "Size of third: " << int (third.size()) << '\n';
	third.assign(first.begin(), first.begin());
	std::cout << "Size of third: " << int (third.size()) << '\n';



	ft::vector<int> myv;

	myv.push_back(10);

	while (myv.back() != 0)
	{
		myv.push_back ( myv.back() -1 );
	}

	std::cout << "myvector contains:";
	myv.pop_back();
	for (unsigned i=0; i<myv.size() ; i++)
		std::cout << ' ' << myv[i];
	std::cout << '\n';


	ft::vector<int> vector (3,100);
	ft::vector<int>::iterator ite;

	ite = vector.begin();
	ite = vector.insert ( ite , 200 );

	std::cout << "a: " << *ite << std::endl;
	vector.insert (ite,2,300);

	// "it" no longer valid, get a new one:
	ite = vector.begin();

	vector.begin();
	ft::vector<int> anothervec (2,400);
	//std::cout <<"main: " << &(*(vector.begin() + 2)) << std::endl;
	//std::cout << "main: "<< &(*(ite + 2)) << std::endl;
	vector.insert(ite + 2, anothervec.begin(), anothervec.end());

	int myarray [] = { 501,502,503 };
	vector.insert (vector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=vector.begin(); it < vector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "myvector capacity: " << vector.capacity() << std::endl;
	std::cout << "myvector size: " << vector.size() << std::endl;



	{
		ft::vector<int> myvector;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++) myvector.push_back(i);

		// erase the 6th element
		ft::vector<int>::iterator it = myvector.erase (myvector.begin()+5);

		std::cout << "myvector contains:";

		for (unsigned i=0; i<myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';


		// erase the first 3 elements:
		std::cout << "a: " << *myvector.erase(myvector.begin(),myvector.begin()+3) << std::endl;

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "c: " << myvector.capacity() << std::endl;
		std::cout << "s: " << myvector.size() << std::endl;
		std::cout << "a: " << *it << std::endl;

	}

	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (5,200);   // five ints with a value of 200


		std::cout << "before swap first elem foo addr: " << &(*foo.begin()) << std::endl;
		foo.swap(bar);
		std::cout << "after swap first elem bar addr: " << &(*bar.begin()) << std::endl;

		std::cout << "foo contains:";
		for (unsigned i=0; i<foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << "\nfoo capacity: " << foo.capacity() << std::endl;

		std::cout << "bar contains:";
		for (unsigned i=0; i<bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << "\nbar capacity: " << bar.capacity() << std::endl;
	}

	{
		ft::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << "\nc: " << myvector.capacity();
		std::cout << '\n';

		myvector.clear();
		myvector.push_back (1101);
		myvector.push_back (2202);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << "\nc: " << myvector.capacity();
		std::cout << '\n';
	}

	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}

	// iterators

	{
		ft::vector<int>	v(4);
		v.push_back(11);
		ft::vector<int>::iterator it = v.begin();
		std::cout << it[4] << std::endl;
	}


	// STACK //
	{

		std::deque<int> mydeque (3,100);          // deque with 3 elements
		ft::vector<int> myvector (2,200);        // vector with 2 elements

		ft::stack<int> first;                    // empty stack
		ft::stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque

		ft::stack<int,ft::vector<int> > third;  // empty stack using vector
		ft::stack<int, ft::vector<int> > fourth (myvector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	}

	{
		ft::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		std::cout << "mystack.top() is now " << mystack.top() << '\n';
	}

	{
		ft::vector<int> v(4, 5);
		ft::stack<int, ft::vector<int> >	s(v);
		while (!s.empty()) {
			std::cout << s.top() << "; ";
			s.pop();
		}
		std::cout << std::endl;
	}	

	/**
	  try {
	// vector throws a length_error if resized above max_size
	//ft::vector<int> myvec(4611686018427387905);
	ft::vector<int> myvec;
	myvec.resize(myvec.max_size()+1);
	}
	catch (const std::length_error& le) {
	std::cerr << "Length error: " << le.what() << '\n';
	}
	 **/
	ft::vector<int> myvec(10);
	try {
		myvec.at(20)=100;      // vector::at throws an out-of-range
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}


	//pair make_pair

	ft::pair <int,int> foo;
	ft::pair <int,int> bar;

	foo = ft::make_pair (10,20);
	bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n';


	ft::pair <std::string,double> product1;                     // default constructor
	ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	ft::pair <std::string,double> product3 (product2);          // copy constructor

	product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double

	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

	//TEST MAP

	ft::map<char,int> mymap;

	ft::map<char,int>::key_compare mycomp = mymap.key_comp();
	std::cout << mycomp(2, 3)  << std::endl;

	{

		std::cout << std::endl;
		ft::map<char,int> first;

		//ft::map<char, int>::iterator ite = first.begin();
		//std::cout << ite->first;


		first['e']=10;
		std::cout << first['e'] << std::endl;
		std::cout << (first['b'] = 30) << std::endl;
		std::cout << first['b'] << std::endl;
		first['c']=50;
		first['d']=70;
		first['z']=100;
		first['a']=90;
		std::cout << first['d']  << " " << first['c'] << first['z'] << first['a'] << std::endl;

		for (ft::map<char, int>::iterator it = first.begin(); it != first.end(); it++) {
			std::cout << "[" << it->first << ", " << it->second << "]" << std::endl;
			//third.erase(it);
			//sleep(1);
		}

		ft::map<char, int>::iterator it;

		it=first.find('e');
		first.erase(it);
		//std::cout << "TRY   " <<  first.begin()->first << std::endl;

		for (ft::map<char, int>::iterator it = first.begin(); it != first.end(); it++) {
			std::cout << "[" << it->first << ", " << it->second << "]" << std::endl;
			//third.erase(it);
			//sleep(1);
		}

		ft::map<char,int> second (first.begin(), first.end());

		ft::map<char,int> third (second);	
		for (ft::map<char, int>::reverse_iterator it = third.rbegin(); it != third.rend(); it++) {
			std::cout << "[" << it->first << ", " << it->second << "]" << std::endl;
			//sleep(1);
		}

		for (ft::map<char, int>::iterator it = third.begin(); it != third.end(); it++) {
			std::cout << "[" << it->first << ", " << it->second << "]" << std::endl;
			//third.erase(it);
			//sleep(1);
		}
	}

	for (int i = 1; i < 21; i++)
		test_delete_map(i);

	{
		ft::map<char,int> mymap;

		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;

		// show content:
		ft::map<char,int>::reverse_iterator rit;
		for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
			std::cout << rit->first << " => " << rit->second << '\n';
	}

	//std::map<char,int,classcomp> fourth;                 // class as Compare

	//bool(*fn_pt)(char,char) = fncomp;
	//std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator it;

		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;

		it=mymap.find('b');
		mymap.erase (it);                   // erasing by iterator

		mymap.erase ('c');                  // erasing by key

		it=mymap.find ('e');
		mymap.erase ( it, mymap.end() );    // erasing by range

		// show content:
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

	}

	{

		ft::map<char,int> first;
		ft::map<char,int> second;

		first['x']=8;
		first['y']=16;
		first['z']=32;

		second=first;                // second now contains 3 ints
		first=ft::map<char,int>();  // and first is now empty

		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
	}

	{
		int i;
		ft::map<int,int> mymap;

		if (mymap.max_size()>1000)
		{
			for (i=0; i<1000; i++) mymap[i]=0;
			std::cout << "The map contains 1000 elements.\n";
		}
		else std::cout << "The map could not hold 1000 elements.\n";
	}

	{
		ft::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( ft::pair<char,int>('j',100) );
		mymap.insert ( ft::pair<char,int>('z',200) );
		mymap.insert ( ft::pair<char,int>('g',200) );
		mymap.insert ( ft::pair<char,int>('c',200) );
		mymap.insert ( ft::pair<char,int>('a',200) );
		mymap.insert ( ft::pair<char,int>('l',200) );
		mymap.insert ( ft::pair<char,int>('p',200) );
		mymap.insert ( ft::pair<char,int>('m',200) );


		ft::pair<ft::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( ft::pair<char,int>('z',500) );
		if (ret.second==false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}
		else
			std::cout << "z inserted" << std::endl;

		ret = mymap.insert ( ft::pair<char,int>('b',500) );
		if (ret.second==false) {
			std::cout << "element 'b' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}
		else
			std::cout << "b inserted" << std::endl;

		// second insert function version (with hint position):
		ft::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		ft::map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	{
		ft::map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	{
		ft::map<char,int> mymap;

		mymap['x']=1001;
		mymap['y']=2002;
		mymap['z']=3003;

		std::cout << "mymap contains:\n";

		ft::pair<char,int> highest = *mymap.rbegin();          // last element

		ft::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mymap.value_comp()(*it++, highest) );
	}

	{
		ft::map<char,int> mymap;
		char c;

		mymap ['a']=101;
		mymap ['c']=202;
		mymap ['f']=303;

		for (c='a'; c<'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c)>0)
				std::cout << " is an element of mymap.\n";
			else 
				std::cout << " is not an element of mymap.\n";
		}
	}

	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator itlow,itup;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;

		itlow=mymap.lower_bound ('b');  // itlow points to b
		itup=mymap.upper_bound ('d');   // itup points to e (not d!)

		std::cout << "itlow "<<  itlow->first << std::endl;
		std::cout << "itup " << itup->first << std::endl;

		mymap.erase(itlow,itup);        // erases [itlow,itup)

		// print content:
		for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	{
		ft::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
		ret = mymap.equal_range('b');

		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';

		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}
	/**
	  ft::vector<int> myvector2;

	// set some initial content:
	for (int i=1;i<10;i++) myvector1.push_back(i);

	myvector1.resize(5);
	myvector1.resize(8,100);
	myvector1.resize(12);

	std::cout << "myvector contains:";
	for (int i=0;i<myvector1.size();i++)
	std::cout << ' ' << myvector1[i];
	std::cout << '\n';
	 **/

	/**
	  for (int i = 0; i < COUNT; i++)
	  {
	  vector_buffer.push_back(Buffer());
	  }

	  for (int i = 0; i < COUNT; i++)
	  {
	  const int idx = rand() % COUNT;
	  vector_buffer[idx].idx = 5;
	  }
	  ft::vector<Buffer>().swap(vector_buffer);

	  try
	  {
	  for (int i = 0; i < COUNT; i++)
	  {
	  const int idx = rand() % COUNT;
	  vector_buffer.at(idx);
	  std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
	  }
	  }
	  catch(const std::exception& e)
	  {
	//NORMAL ! :P
	}
	 **/

	/**
	  for (int i = 0; i < COUNT; ++i)
	  {
	  map_int.insert(ft::make_pair(rand(), rand()));
	  }

	  int sum = 0;
	  for (int i = 0; i < 10000; i++)
	  {
	  int access = rand();
	  sum += map_int[access];
	  }
	  std::cout << "should be constant with the same seed: " << sum << std::endl;

	  {
	  ft::map<int, int> copy = map_int;
	  }
	  MutantStack<char> iterable_stack;
	  for (char letter = 'a'; letter <= 'z'; letter++)
	  iterable_stack.push(letter);
	  for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	  {
	  std::cout << *it;
	  }
	 **/
	std::cout << std::endl;
	return (0);
}
