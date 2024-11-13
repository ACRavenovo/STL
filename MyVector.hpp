#pragma once
#ifndef __Vector__
#define __Vector__
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <assert.h>
static const size_t npos = -1;
static const float SpaceMutiConstant = 1.5;
using std::iostream;
using std::ifstream;

template <class T>
class Vector {
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef T* iterator;

	Vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _end(nullptr)
	{}

	Vector(const Vector& vec) {
		size_type MySize = vec.size();
		value_type* ptr = new value_type[vec.capacity()];
		for (int i = 0; i < MySize; i++) {
			ptr[i] = vec._start[i];
		}
		_start = ptr;
		// delete[] ptr;  // �����Բ��ӣ���Ϊ�൱���й�
		_finish = _start + MySize;
		_end = _start + vec.capacity();
	}

	//Vector(const Vector& vec)
	//	: _start(nullptr), _finish(nullptr), _end(nullptr)
	//{
	//	reserve(vec.capacity());
	//	for (const auto& e : vec)
	//	{
	//		push_back(e);
	//	}
	//}

	Vector(size_type n, const value_type& val = value_type())
		: _start(nullptr)
		, _finish(nullptr)
		, _end(nullptr)
	{
		resize(n, val);
	}

	Vector(int n, const value_type& val = value_type())
		: _start(nullptr)
		, _finish(nullptr)
		, _end(nullptr)
	{
		resize(n, val);
	}
	//vector(long long n, const Ty&val= Ty())��//����size_t n,int n

	template <class InputIterator>
	Vector(InputIterator first, InputIterator last) {
		size_type MySize = last - first;
		reserve(MySize);
		while (first != last) {
			push_back(*first);
			first++;
		}
		_finish = _start + MySize;
		_end = _finish;
	}

	// �ƶ����캯��
	Vector(Vector&& vec) noexcept
		: _start(vec._start)
		, _finish(vec._finish)
		, _end(vec._end)
	{
		vec._start = nullptr;
		vec._finish = nullptr;
		vec._end = nullptr;
	}

	// �ƶ���ֵ�����
	Vector& operator=(Vector&& vec) noexcept
	{
		if (this != &vec) {
			delete[] _start;
			_start = vec._start;
			_finish = vec._start + vec.size();
			_end = vec._start + vec.capacity();
			vec._start = nullptr;
			vec._finish = nullptr;
			vec._end = nullptr;
		}
		return *this;
	}

	value_type& operator [](const size_type& index) {
		if (index >= size()) {
			throw std::out_of_range("Index out of range");
		}
		return *(_start + index);
	}

	value_type& at(size_t index)
	{
		if (index >= size()) {
			throw std::out_of_range("Index out of bounds");
		}
		return _start[index];
	}

	const Vector& operator=(const Vector& vec) {
		if (this != &vec) {
			delete[] _start;

			size_type MySize = vec.size();
			_start = new value_type[vec.capacity()];

			for (int i = 0; i < MySize; i++) {
				_start[i] = vec._start[i];
			}

			_finish = _start + MySize;
			_end = _start + vec.capacity();
		}
		return *this;
	}

	// ����д��
	//void swap(Vector& vec)   // �Լ�д��swap��ǳ����������С
	//{
	//	std::swap(_start, vec._start);
	//	std::swap(_finish, vec._finish);
	//	std::swap(_end, vec._end);
	//}

	//Vector& operator=(Vector vec)
	//{
	//	swap(vec);    // �������swap����������ۼ���
	//	return *this;
	//}

	bool operator==(const Vector& vec) {
		for (int i = 0; i < size(); i++) {
			if (*(_start + i) != vec[i]) {
				return false;
			}
		}
		return true;
	}

	iterator erase(iterator pos) {
		assert(pos < _finish);

		iterator it = pos;
		// ����պ�ɾ���������һ����ЧԪ�أ���ô���ص�λ�þ���Խ���
		// ��û�п���ɾ���Ľ�����û��ֵ�Ŀռ���Ԫ�أ�
		while (it < _finish)
		{
			*it = *(it + 1);
			++it;
		}
		--_finish;
		return pos;
	}

	iterator insert(iterator pos, value_type val) {
		assert(pos <= _finish);

		// ֻҪ�漰�ռ�仯���������ͻ�ʧЧ����Ϊ�������ǵ�ַ���ռ���ˣ���ô�ϵ�ָ�����ռ�ĵ�ַ��ʧЧ��
		if (_finish == _end) {
			size_type len = pos - _start;
			//size_t newcapacity = capacity() == 0 ? 4 : capacity() * SpaceMutiConstant;
			//reserve(newcapacity);
			reserve(capacity() * SpaceMutiConstant);
			// �ؼ�������� �����˵�����ʧЧ������
			pos = _start + len;
		}

		iterator it = _finish - 1;
		while (it > pos)
		{
			*(it + 1) = *it;
			it--;
		}
		*(it + 1) = *it;
		*it = val;
		++_finish;
		return pos;
	}

	void push_back(const value_type& val) {
		if (!_start) {
			reserve(SpaceMutiConstant);
		}

		if (_finish == _end) {
			reserve(capacity() * SpaceMutiConstant);
		}

		*_finish = val;
		_finish = _finish + 1;
	}

	void push_back(value_type&& val)
	{
		if (_finish == _end)
		{
			reserve(capacity() == 0 ? 4 : capacity() * SpaceMutiConstant);
		}
		*_finish = std::move(val); // ʹ�� move ����
		++_finish;
	}

	iterator pop_back() {
		assert(_start < _finish);
		//if (_start == _end) {
		//	return _start;
		//}
		iterator ret = _finish - 1;
		_finish = _finish - 1;
		return ret;
	}

	void resize(const size_type& n, const value_type& val = '\0') {
		if (!_start) {
			reserve(n);
			for (int i = 0; i < n; i++) {
				_start[i] = val;
			}
			_finish = _start + n;
		}
		else {
			size_type MySize = size();
			size_type MyCapacity = capacity();
			if (n > MyCapacity) {
				reserve(n);
				for (int i = MySize; i < n; i++) {
					_start[i] = val;
				}
				_finish = _start + n;
			}
			else if (n == MyCapacity) {
				for (auto it = _finish; it != _end; it++) {
					*it = val;
				}
			}
			else {
				_finish = _start + n;
				for (auto it = _finish; it != _end; it++) {
					*it = val;
				}
			}
		}
	}

	void reserve(const size_type n) {
		if (!_start) {
			// �������Ǵ���һ���µ���ʱ����������if�ͻ�����
			//iterator _start = new value_type[n];
			//value_type* _start = new value_type[n];
			value_type* ptr = new value_type[n];
			_start = ptr;
			_finish = _start;
			_end = _finish + n;
		}
		else {
			size_type sz = size();
			if (n >= capacity()) {
				value_type* ptr = new value_type[n];
				for (int i = 0; i < sz; i++) {
					ptr[i] = _start[i];
					//ptr[i] = std::move(_start[i]);
				}
				//ǳ����, ������һ����ַ���ƹ�ȥ�����ջ����ҵ�һ���ط��� ������Ҫ���ǲ�ͬ�ĵط�����ͬ������
				//memcpy(ptr, _start, sizeof(value_type) * n * SpaceMutiConstant);

				//Ϊʲô����д�����У� ��Ϊ�����ݲ����ʱ��swap��������һ��ǳ����
				//swap(_start, ptr);
				//delete[] ptr;
				delete[] _start;
				_start = ptr;

				_finish = _start + sz;
				_end = _start + static_cast<int>(n);
			}
			else {
				_finish = _start + n;
				_end = _finish;
			}
		}
	}

	bool empty() {
		return _start == _finish;
	}

	void clear()
	{
		_finish = _start;
	}

	//void swap(value_type& v1, value_type& v2) {
	//	value_type v3;
	//	v3 = v1;
	//	v1 = v2;
	//	v2 = v3;
	//}	
	//
	//void swap(value_type* v1, value_type* v2) {
	//	value_type* v3;
	//	v3 = v1;
	//	v1 = v2;
	//	v2 = v3;
	//}

	void output() {
		for (auto it = _start; it != _finish; it++) {
			std::cout << ' ' << *it;
		}
		std::cout << '\n';
		std::cout << size() << '\n';
		std::cout << capacity() << '\n';
	}

	void outputAll() {
		for (auto it = _start; it != _end; it++) {
			std::cout << ' ' << *it;
		}
		std::cout << '\n';
		std::cout << size() << '\n';
		std::cout << capacity() << '\n';
	}

	size_type size() const {
		return _finish - _start;
	}

	size_type capacity() const {
		return _end - _start;
	}

	iterator begin() {
		return _start;
	}

	iterator end() {
		return _finish;
	}

	~Vector() {
		//if (_start) {
		//	delete[] _start;
		//}
		delete[] _start;
		_start = _finish = _end = nullptr;
	}

private:
	iterator _start;
	iterator _finish;
	iterator _end;
};
#endif