#include <stdio.h>
//using namespace std;
//int add1(int a, int b) {
//	int c = a + b;
//	return c;
//}
//
//int& add2(int a, int b) {
//	int c = a + b;
//	return c;
//}
//
//int main() {
//	const int& ret1 = add1(1, 2);
//	add1(3, 4);
//	cout << "add1(1,2) = " << ret1 << endl;  //������ʾΪ3
//
//	const int& ret2 = add2(1, 2);
//	add2(3, 4);
//	cout << "add2(1,2) = " << ret2 << endl;  //������ʾΪ7���˳���ʾΪ���ֵ���߿�
//}