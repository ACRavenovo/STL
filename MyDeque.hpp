#include <iostream>
#include <vector>

#define SingleSpaceSize 8

template<class T>
class _node_iterator {
public:
	typedef _node_iterator<T> iterator;

	typedef T value_type;
	typedef size_t size_type;
	typedef T** map_pointer;

	//typedef _node_iterator  self;

	_node_iterator()
		:_node_cur(nullptr), _node_start(nullptr), _node_end(nullptr)
		, _m_node(nullptr), _node_size(0)
	{}

	_node_iterator(value_type** mem_start, size_type index) {
		_node_size = size();
		size_type node_num = index / _node_size;
		size_type node_index = index % _node_size;
		iterator cur_node = *mem_start + node_num;
		_node_cur = cur_node + node_index;
		_node_start = cur_node;
		_node_end = cur_node + _node_size;
		_m_node = mem_start;
	}

	// 通过该函数来跳到另一个缓冲区
	void set_node(T** _new_node)
	{
		_m_node = _new_node;
		_node_start = *_new_node;
		_node_end = _node_start + _node_size;
	}

	_node_iterator& operator *() const { 
		return *_node_cur; 
	}

	iterator operator ->() const { 
		return &(operator *()); 
	}

	//重载前置 ++ 运算符
	_node_iterator& operator ++() {
		++_node_cur;
		//处理 cur 处于连续空间边缘的特殊情况
		if (_node_cur == _node_end) {
			//调用该函数，将迭代器跳跃到下一个连续空间中
			set_node(_m_node + 1);
			//对 cur 重新赋值
			_node_cur = _node_start;
		}
		return *this;
	}
	//重置前置 -- 运算符
	_node_iterator& operator --() {
		//如果 cur 位于连续空间边缘，则先将迭代器跳跃到前一个连续空间中
		if (_node_cur == _node_start) {
			set_node(_m_node - 1);
			_node_cur == _node_end;
		}
		--_node_cur;
		return *this;
	}

	iterator operator +(size_type n) {
		_node_iterator _tmp = *this;
		return _tmp += n;
		//_node_start = _node_start + n;
		//_node_end = _node_end + n;
		//_node_cur = _node_cur + n;
	}
	
	iterator operator +=(size_type n) {
		size_type offset = n + (_node_cur - _node_start); // 从当前Node的起始算起多少个位置后
		if (offset >= 0 && offset < _node_size) {
			_node_cur += n;
		}	
		//需要跳到另一个node中
		else {
			// 计算向上或向下的node偏移量 （几个node） offset正负情况下处理不一样
			size_type node_offset = offset > 0 ? offset / _node_size : -((-offset - 1) / _node_size) - 1;
			set_node(_m_node + node_offset); // 根据偏移量移动start和end到新位置

			// 根据偏移量移动cur到新位置
			_node_cur = _node_start + (offset - node_offset * _node_size);
		}
		return *this;
	}

	//value_type& operator [](size_type index) {
	//	return *_node_cur;
	//}

	// 随机存取，迭代器可以直接跳跃 index 个距离
	// 调用上面的 operator + ,以及operator *
	value_type& operator [](size_type index) const {
		return *(*this + index);
	}

	size_type& size() {
		size_type sz_T = sizeof(value_type);
		return sz_T < 512 ? size_t(512 / sz_T) * sz_T : size_t(1) * sz_T;
	}

private:
	iterator _node_cur;
	iterator _node_start;
	iterator _node_end;
	map_pointer _m_node;   // 指向当前node所在map
	size_type _node_size;
};

template<class T>
class Deque{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef _node_iterator<T> iterator;
	
	Deque()
		:_mem_start(nullptr), _mem_end(nullptr), _iterator_list_map(nullptr)
		,_map_size(0)
	{}

	Deque(size_type n, const value_type& val)
	{
		size_type total_nodes = n / _Deque_buf_size(sizeof(value_type)) + 1;

		// 给map+2使得map不会被占满
		_map_size = SingleSpaceSize > total_nodes + 2 ? SingleSpaceSize : total_nodes + 2;

		// 给map开辟空间，并让起始和终结点尽量向空间的中心区域靠
		_iterator_list_map = new T*[_map_size];
		_mem_start = _iterator_list_map + ((_map_size - total_nodes) / 2);
		_mem_end = _iterator_list_map + total_nodes - 1;

		// tmp_start，tmp_finish 指向 map的最中央区域
		// 保持在最中央使得两端的开展区域一样
		value_type** tmp_start = _iterator_list_map + (_map_size - total_nodes) / 2;
		value_type** tmp_finish = tmp_start + total_nodes - 1;

		// 为map每个节点配置缓冲区
		// 初始化内部缓存区的空间
		Nodeinit(_mem_start, _mem_end);

		// 设置 start 和 end 两个迭代器
		_mem_start.set_node(tmp_start);
		_mem_start._node_cur = _mem_start._node_start;

		_mem_end.set_node(tmp_finish);
		_mem_end._node_cur = _mem_end._node_start + n % _Deque_buf_size(sizeof(value_type));

		// 给这些空间赋初始值val
		//auto i = *_mem_start;
		//while (i != *_mem_end) {
		//	for (int j = 0; j < i->size(); j++) {
		//		i[j] = val;
		//		j++;
		//	}
		//	i++;
		//}
		//for (int j = 0; j < i->size(); j++) {
		//	i[j] = val;
		//	j++;
		//}

	}

	template <class InputIterator>
	Deque(InputIterator first, InputIterator last);

	Deque(const Deque& x);
	
	void Nodeinit(value_type** mem_start, value_type** mem_end) {
		value_type** cur;
		for (cur = mem_start; cur != mem_end; cur++) {
			*cur = Nodeallocate(_Deque_buf_size(sizeof(value_type)))
		}
	}

	value_type* Nodeallocate(size_t _n)
	{
		return 0 == _n ? nullptr : new T*(_n * sizeof(value_type));
	}

	inline size_t _Deque_buf_size(size_t _size)
	{
		return _size < 512 ? size_t(512 / _size) : size_t(1);
	}

	value_type& operator[](size_type n) {
		return _mem_start[n];
	}
	Deque& push_front();
	Deque& push_back();
	Deque& pop_front();
	Deque& pop_back();

	size_type capacity();
	value_type* insert();
	void resize();
	void clear();

	//begin() 成员函数
	value_type* begin() {
		return _mem_start; 
	}

	//end() 成员函数
	value_type* end() {
		return _mem_end; 
	}

	//front() 成员函数
	Deque front() { 
		// 调用的是_node_iterator的 operator*
		// 返回 start的成员 *cur
		return *_mem_start; 
	}

	//back() 成员函数
	Deque back() {
		iterator tmp = _mem_end;
		--tmp;
		return *tmp; //返回的是finish 的 *cur
	}

	//size() 成员函数
	size_type size() const { 
		return _mem_end - _mem_start; 
	}//deque迭代器重载了 - 运算符

	//size_type size() {
	//	return sizeof(_iterator_list_map) / sizeof(T);
	//}

	//enpty() 成员函数
	bool empty() const { 
		return _mem_end == _mem_start; 
	}

private:
	iterator _mem_start; // map上第一段空间Node的起始位置
	iterator _mem_end; // map上最后一段空间Node的起始位置
	//::vector<iterator> _iterator_list_map;
	value_type** _iterator_list_map;
	size_type _map_size;
};
