#include "MyString.hpp"
using std::cout;
using std::cin;

template <class T>
void f(const T& a) {
	printf("void f(const T& a)");
}

template <class T>
void f(const T&& a) {
	printf("void f(const T&& a)");
}

void foo(String x) {

}

void bar(const String& x) {

}

String baz() {
	String ret("world");
	return ret;
}

void test1() {
	const char* a = "ahhhhhhhh";
	//String();
	//String s1("hello world!");
	//String s2(s1);
	////String::swap(s1, s2);
	//int&& c = 10;
	String s0("Initial string");

	// constructors used in the same order as described above:
	String s1;
	String s2(s0);
	String s3(s0, 8, 3);
	String s4("A character sequence");
	String s5("Another character sequence", 12);
	String s6a(10, 'x');
	String s6b(10, 42);      // 42 is the ASCII code for '*'
	std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
	std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6a: " << s6a;
	std::cout << "\ns6b: " << s6b << '\n';

	std::cout << s4.erase(&s4[4]) << '\n';
	std::cout << s4[10] << '\n';
	std::cout << s4.erase(4, 6) << '\n';
	s4 += "In";
	s4 += "Initial string";
	int f1 = s4.find(s0.c_str(), 3);
	printf("s4.find(s0.c_str(), 3) is : %d \n", f1);
	int f2 = s4.find(3, 'a');
	printf("s4.find(3, 'a') is : %d \n", f2);
	s4.resize(10);
	int f3 = s4.size();
	printf("s4.size() is : %d \n", f3);
	s0.reserve();
	int f4 = s0.capacity();
	printf("s0.capacity() is : %d \n", f4);
	s0 += 'a';
	std::cout << s0 << " after add a " << '\n';
	s0 += s4.c_str();
	std::cout << s0 << " after add s4 " << '\n';
	String ss = s0 + 'c';
	std::cout << ss << '\n';
	s3 = s4;
	std::cout << s3 << '\n';
	if (s3 == s4) {
		printf("s3 == s4!\n");
	}

	if (s0 == s4) {
		printf("s0 == s4!\n");
	}
	else {
		printf("s0 != s4!\n");
	}

	bool emptys1 = s1.empty(s1);
	if (emptys1) {
		printf("s1 is empty!\n");
	}
	else {
		printf("s1 is not empty!\n");
	}

	bool emptys4 = s4.empty(s4);
	if (emptys4) {
		printf("s4 is empty!\n");
	}
	else {
		printf("s4 is not empty!\n");
	}

	s1.clear();
	std::cout << s1 << '\n';
}


//int main() {
//	//String g1;
//	//getline(std::cin, g1);
//	String s8;
//	String s9("hello");
//	String s10(s8);
//	String s11 = s9;
//	s10 = s9;
//	foo(s9);
//	bar(s9);
//	foo("temporary");
//	bar("temporary");
//	String s12 = baz();
//	std::vector<String> svec;
//	svec.push_back(s8);
//	svec.push_back(s9);
//	svec.push_back(baz());
//	svec.push_back("good job");
//
//	std::cout << "s8: " << s8 << "\ns9: " << s9 << "\ns10: " << s10;
//	std::cout << "\ns11: " << s11 << "\ns12: " << s12 << "\n";
//}
