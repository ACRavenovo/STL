#ifndef __String__
#define __String__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

class String {
private:
	const char* _str;

public:
	String(const char* str = nullptr) 
		:_str(str) 
	{
		char* _ptr = new char[strlen(str)+1];
		strcpy(_ptr, _str);
		_str = _ptr;
	}
	
	String(String& s) {
		swap(_str, s._str);
	}

	template <class T>
	void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}

	~String() {
		delete _str;
	}
};

int count1() {
	static int n = 0;
	n++;

	return n;
}

int& count2() {
	static int n = 0;
	n++;

	return n;
}

bool judgement() {
	return true;
}

template <class T>
void f(const T& a) {
	printf("void f(const T& a)");
}

template <class T>
void f(const T&& a) {
	printf("void f(const T&& a)");
}


//int main() {
//	const char* a = "ahhhhhhhh";
//	String();
//	String s1("hello world!");
//	String s2(s1);
//	//String::swap(s1, s2);
//	const int& r1 = count1();
//	int& r2 = count2();
//
//	int&& c = 10;
//
//}


#endif