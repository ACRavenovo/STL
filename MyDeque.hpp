#include <iostream>
#include <vector>

#define SingleSpaceSize 8

template<class T>
class Node_Iterator {
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef T* iterator;

	Node_Iterator()
		:_node_cur(nullptr), _node_start(nullptr), _node_end(nullptr)
		,_m_start(nullptr), _node_size(0)
	{}

	Node_Iterator(value_type** mem_start, size_type index) {
		_node_size = size();
		size_type node_num = index / _node_size;
		size_type node_index = index % _node_size;
		iterator cur_node = *mem_start + node_num;
		_node_cur = cur_node + node_index;
		_node_start = cur_node;
		_node_end = cur_node + _node_size;
		_m_start = mem_start;
	}

	// ͨ���ú�����������һ��������
	void set_node(T** _new_node)
	{
		_m_start = _new_node;
		_node_start = *_new_node;
		_node_end = _node_start + _node_size;
	}

	iterator operator +(size_type n) {
		Node_Iterator _tmp = *this;
		return _tmp += n;
		//_node_start = _node_start + n;
		//_node_end = _node_end + n;
		//_node_cur = _node_cur + n;
	}
	
	iterator operator +=(size_type n) {
		size_type offset = n + (_node_cur - _node_start); // �ӵ�ǰNode����ʼ������ٸ�λ�ú�
		if (offset >= 0 && offset < _node_size) {
			_node_cur += n;
		}	
		//��Ҫ������һ��node��
		else {
			// �������ϻ����µ�nodeƫ���� ������node�� offset��������´���һ��
			size_type node_offset = offset > 0 ? offset / _node_size : -((-offset - 1) / _node_size) - 1;
			set_node(_m_start + node_offset); // ����ƫ�����ƶ�start��end����λ��

			// ����ƫ�����ƶ�cur����λ��
			_node_cur = _node_start + (offset - node_offset * _node_size);
		}
		return *this;
	}

	value_type& operator [](size_type index) {
		return *_cur;
		//return *(this + index)
	}

	size_type& size() {
		size_type sz_T = sizeof(value_type);
		return sz_T < 512 ? size_t(512 / sz_T) * sz_T : size_t(1) * sz_T;
	}

private:
	iterator _node_cur;
	iterator _node_start;
	iterator _node_end;
	T** _m_start;   // ָ��ǰnode����map
	size_type _node_size;
};

template<class T>
class Deque{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef T* iterator;
	
	deque()
		:_mem_start(nullptr), _mem_end(nullptr), _iterator_list_map(nullptr)
		,_map_size(0)
	{}

	deque(size_type n, const value_type& val) 
	{
		size_type total_nodes = n / _Deque_buf_size(sizeof(value_type)) + 1;

		// ��map+2ʹ��map���ᱻռ��
		_map_size = SingleSpaceSize > total_nodes + 2 ? SingleSpaceSize : total_nodes + 2;

		// ��map���ٿռ䣬������ʼ���ս�㾡����ռ����������
		_iterator_list_map = new iterator[_map_size];
		_mem_start = _iterator_list_map + ((_map_size - total_nodes) / 2);
		_mem_end = _iterator_list_map + total_nodes;

		// ��ʼ���ڲ��������Ŀռ�
		Nodeinit(_mem_start, _mem_end);

		_mem_start.set_node(_start);
		_mem_end.set_node(_finish - 1);

		_mem_start._node_end = _mem_start._node_start;
		// ����Щ�ռ丳��ʼֵval
		int i = *_mem_start;
		while (i != *_mem_end) {
			for (int j = 0; j < i.size(); j++) {
				i[j] = val;
				j++;
			}
			i++;
		}
		for (int j = 0; j < i.size(); j++) {
			i[j] = val;
			j++;
		}

	}

	template <class InputIterator>
	deque(InputIterator first, InputIterator last);

	deque(const deque& x);
	
	void Nodeinit(value_type** mem_start, value_type** mem_end) {
		value_type** cur;
		for (cur = mem_start; cur != mem_end; cur++) {
			*cur = Nodeallocate(_Deque_buf_size(sizeof(value_type)))
		}
	}

	iterator Nodeallocate(size_t _n)
	{
		return 0 == _n ? nullptr : new iterator(_n * sizeof(value_type));
	}

	inline size_t _Deque_buf_size(size_t _size)
	{
		return _size < 512 ? size_t(512 / _size) : size_t(1);
	}

	operator []() {};

	Deque& push_front();
	Deque& push_back();
	Deque& pop_front();
	Deque& pop_back();

	size_type size();
	size_type capacity();
	iterator insert();
	void resize();
	void empty();
	void clear();

private:
	iterator _mem_start; // map�ϵ�һ�οռ�Node����ʼλ��
	iterator _mem_end; // map�����һ�οռ�Node����ʼλ��
	std::vector<T*> _iterator_list_map;
	size_type _map_size;
};
