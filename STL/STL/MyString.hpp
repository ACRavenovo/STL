#ifndef __String__
#define __String__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
static const size_t npos = -1;
static const float SpaceMutiConstant = 1.5;
#define iterator char*
using std::ostream;
using std::istream;

class String {
	friend ostream& operator << (ostream& cout, const String& str);
	friend istream& operator >> (istream& cin, const String& str);
	friend istream& getline(istream& is, String& str);
	//friend void foo(String x);
	//friend void bar(const String& x);

private:
	size_t _size; // 已使用空间大小
	size_t _capacity; // 空间大小
	char* _str;

public:
	// 为什么不能直接使用这个传进来的地址？ 因为这是一个浅拷贝，析构的时候会析构2次，有安全问题，我们需要用深拷贝来解决
	// 即开辟一块新空间，然后把传进来的字符串复制一份进去，再看情况释放传进来的地址所指向的空间}

	String(const char* str = "") // 缺省一个没有字符的字符串，编译器会将其对待为只有/0
		:_size(strlen(str))
		, _capacity(_size)
		, _str(new char[_capacity + 1])
	{
		strcpy(_str, str);
	}

	// 右值引用， 针对自定义类型的临时变量以及将亡值采取转移资源的方式，不创建多余的空间
	String(String&& str)
		:_str(str._str)
	{
		str._str = nullptr;
	}

	String& operator = (String&& str)
	{
		_str = str._str;
		str._str = nullptr;
		return *this;
	}

	//// 标准拷贝构造写法
	//String(const String& s) 
	//	:_str(new char[strlen(s._str) + 1])
	//{
	//	strcpy(_str, s._str); // 开辟空间, 拷贝内容
	//}

	//String& operator=(const String& s) {
	//	if (this != &s) {
	//		// 开辟空间, 拷贝内容, 释放原来的空间, 替换地址
	//		char* pStr = new char[strlen(s._str) + 1]; 
	//		strcpy(pStr, s._str);
	//		delete[] _str;
	//		_str = pStr;
	//	}
	//	return *this;
	//}


	// 成年人炮灰写法
	String(const String& s)
		: _str(nullptr)// 先给_str赋一个空的初值   邪恶的炮灰写法
	{
		// 用给过来的对象的成员变量的地址 构造一个strTmp对象（这个对象会构造自己的空间，并且给好数据）
		String strTmp(s._str);
		// 交换我俩的空间，strTmp出了当前构造函数作用域带着空销毁，我自己拿上创建并已经赋值好的空间

		swap(_str, strTmp._str);
		_size = strTmp._size;
		_capacity = strTmp._capacity;
		// 也就是说直接偷偷把strTmp的地址换成我的，偷梁换柱，函数结束时，就只有我使用这片已经建立好的空间了
	}

	// 对比下和上面的赋值哪个实现比较好？  那就是看构造和拷贝构造哪个快了
	String& operator=(String s) { // 赋值的时候顺便拷贝构造一下，这样释放也不是自己
		swap(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}

	/*
	String& operator=(const String& s){
		if(this != &s){
			String strTmp(s);
			swap(_str, strTmp._str);
		}
		return *this;
	}
	*/

	String(const String& str, size_t pos, size_t len = npos) {
		// 拷贝构造str从pos开始的len个字符
		_size = len;
		_capacity = _size;
		_str = new char[_capacity + 1];
		strncpy(_str, str._str + pos, len);
		_str[len] = '\0'; // 没办法兄弟， strncpy就要这么用， 不然后面的空间他就是乱码
	}

	String(const char* s, size_t n) {
		// 拷贝构造s，只取n个字符
		_size = n;
		_capacity = _size;
		_str = new char[_capacity + 1];
		strncpy(_str, s, n);
		_str[n] = '\0';
	}

	String(size_t n, char c) {
		// 拷贝构造长度为n的字符串，所有内容都初始化为c
		_size = n;
		_capacity = _size;
		_str = new char[_capacity + 1];
		//for (int i = 0; i <= n; i++) {
		//	_str[i] = c;
		//}
		memset(_str, c, n);
		_str[n] = '\0';
	}

	String& operator += (const char* str) {
		int strSize = strlen(str);
		if (_capacity - _size < strSize) {
			SpaceExpending(_capacity + strSize);
			//strcpy(_str + _size, str);
			for (int i = _size, j = 0; j < strSize; i++, j++) {
				_str[i] = str[j];
			}
		}
		else {
			for (int i = _size, j = 0; j < strSize; i++, j++) {
				_str[i] = str[j];
			}
		}
		_size = strSize + _size;
		_str[_size] = '\0';
		return *this;
	}

	String& operator += (char c) {
		if (_size - _capacity < 1) {
			SpaceExpending(_capacity);
		}
		_str[_size] = c;
		_size++;
		_str[_size] = '\0';
		return *this;
	}

	String operator + (const char* str) {
		String Ret(*this);
		Ret += str;
		return Ret;
	}

	String operator + (char c) {
		// 不改变当前对象的内容，将两者相加的和作为一个新对象传出去
		String Ret(_str);
		Ret += c;
		return Ret;
	}

	char& operator [] (size_t pos) {
		return _str[pos];
	}

	bool operator == (const String& str) {
		for (int i = 0; i < _size; i++) {
			if (_str[i] != str._str[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator == (const char* str) {
		for (int i = 0; i < _size; i++) {
			if (_str[i] != str[i]) {
				return false;
			}
		}
		return true;
	}

	template <class T>
	void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}

	char* begin() {
		return &_str[0];
	}

	char* end() {
		return &_str[_size];
	}

	char* cbegin();
	char* cend();

	const char* c_str() const {
		// 返回字符串地址 const char*
		return _str;
	}

	void SpaceExpending(size_t n) {
		char* pStr = new char[n * SpaceMutiConstant];
		strcpy(pStr, _str);
		_str = pStr;
		_capacity = n * SpaceMutiConstant;
	}

	size_t loopInside(size_t iMaybe, const char* cstr, size_t cSize) {
		int j = 0;
		while (j < cSize) {
			if (_str[iMaybe] != cstr[j]) {
				return npos;
			}
			j++;
			iMaybe++;
		}
		return cSize + 1;
	}

	int find(const char* cstr, size_t pos = 0) {
		// 返回从pos位置开始找的第一个字符串c的位置序号
		char cMaybe = cstr[0];
		int cSize = strlen(cstr);
		int inSide = 0;
		for (int i = pos - 1; i < _size; i++) {
			if (_str[i] == cMaybe) {
				int hook = loopInside(i, cstr, cSize);
				if (hook >= 0) {
					return hook;
				}
			}
		}
		return -1;
	}

	int find(size_t pos, char c) {
		// 返回从pos位置开始找的第一个字符串c的位置序号
		for (int i = pos - 1; i < _size; i++) {
			if (_str[i] == c) {
				return i + 1;
			}
		}
		return -1;
	}

	// 检测字符串为空串，是返回True，不是返回False
	bool empty(const String& str) {
		if (str._size) {
			return false;
		}
		else {
			return true;
		}
	}

	// 清空有效字符， 不改变空间大小
	void clear() {
		memset(_str, '\0', _size);
		_size = 0;
	}

	// 为字符串预留空间
	void reserve(size_t n = 0) {
		//String Ret(new char[n]);
		//swap(Ret._str, _str);
		if (n > _capacity) {
			SpaceExpending(n);
		}
	}

	// 有效字符个数改为n个，其余空间用字符c填充
	void resize(size_t n, char c) {
		int Gap = _size - n; // 多出来的或是亏欠的空间个数
		if (n > _size) {
			SpaceExpending(n);
			_str[n] = '\0';
			// memset(_str + n, c, Gap)
			while (Gap < 0) {
				_str[n + Gap] = c;
				Gap++;
			}
		}
		else {
			_str[_size] = '\0';
			Gap--;
			while (Gap >= 0) {
				_str[n + Gap] = c;
				Gap--;
			}
		}
		_size = n;
	}

	// 有效字符个数改为n个
	void resize(size_t n) {
		int Gap = _size - n;
		if (n > _size) {
			SpaceExpending(n);
			// memset(_str + n, c, Gap)
			while (Gap < 0) {
				_str[n + Gap] = '\0';
				Gap++;
			}
		}
		else {
			_str[_size] = '\0';
			Gap--;
			while (Gap >= 0) {
				_str[n + Gap] = '\0';
				Gap--;
			}
		}
		_size = n;
	}

	iterator erase(iterator ptr) {
		// 删除的方法是用后面的元素覆盖当前位置的元素，并返回新的当前位置迭代器地址
		// 还会区分处理删除和不删除的情况
		int curLocation = ptr - _str;
		for (int i = curLocation; i < _size; i++) {
			_str[i] = _str[i + 1];
		}
		_str[_size] = '\0';
		_size--;

		return &_str[curLocation];
	}

	String& erase(size_t pos = 0, size_t len = npos) {
		for (int i = pos; i < _size; i++) {
			_str[i - 1] = _str[i + len - 1];
		}
		//A chracter sequence
		_size = _size - len;
		_str[_size] = '\0';
		return *this;
	}

	size_t size()const {
		return _size;
	}

	size_t capacity()const {
		return _capacity;
	}

	~String() {
		delete[] _str;
	}
};

//istream& getline(istream& is, String& str) {
//	// 拿数据直到遇到换行符才会结束， 也就是说拿了一行数据
//	is >> str;
//	return is;
//}

ostream& operator << (ostream& cout, const String& str) {
	cout << str._str << '\n';
	return cout;
}

istream& operator >> (istream& cin, const String& str) {
	cin >> str._str;
	return cin;
}

#endif