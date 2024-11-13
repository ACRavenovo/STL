#include <iostream>

template<class T>
class Deque{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef T* iterator;

	deque();

	deque(size_type n, const value_type& val);

	template <class InputIterator>  
	deque(InputIterator first, InputIterator last);

	deque(const deque& x);

	void empty();
	size_type size();
	Deque& front();
	Deque& back();
	Deque& push();
	Deque& pop();

private:
	value_type _data;
	iterator _next;
	iterator _prev;

};
