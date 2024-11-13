#include "MyVector.hpp"
#include "MyString.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

//void print_Vector(const Vector<int>& v)
//{
//    Vector<int>::const_iterator it = v.begin();
//    while (it != v.end())
//    {
//        cout << *it << " ";
//        ++it;
//    }
//    cout << endl;
//}

template <class T>
const T& max(const T& a, const T& b) {
    return a > b ? a : b;
}

template <class T>
const T& min(const T& a, const T& b) {
    return a < b ? a : b;
}

int trap(Vector<int>& height) {
    int n = height.size();
    if (n == 0) {
        return 0;
    }
    Vector<int> leftMax(n);
    leftMax[0] = height[0];
    for (int i = 1; i < n; ++i) {
        //std::cout << "round" << i << '\n';
        //std::cout << "height[] = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]" << '\n';
        //std::cout << "    leftMax[i - 1] = " << leftMax[i - 1] << '\n';
        //std::cout << "    height[i] = " << height[i] << '\n';
        leftMax[i] = max(leftMax[i - 1], height[i]);
        //std::cout << "leftMax[i] = " << leftMax[i] << '\n';
        //std::cout << "-------------------------------------" << '\n';
    }

    //std::cout << "leftMax :" << '\n';
    //for (auto it = leftMax.begin(); it != leftMax.end(); it++) {
    //	std::cout << ' ' << *it;
    //	std::cout << '\n';
    //}

    Vector<int> rightMax(n);
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        rightMax[i] = max(rightMax[i + 1], height[i]);
    }

    //std::cout << "rightMax :" << '\n';
    //for (auto it = rightMax.begin(); it != rightMax.end(); it++) {
    //	std::cout << ' ' << *it;
    //	std::cout << '\n';
    //}

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += min(leftMax[i], rightMax[i]) - height[i];
    }
    return ans;
}

// Vector 容器遍历
void test1()
{
    Vector<int> v;

    // 插入
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    // 查看容量
    cout << v.size() << endl;
    cout << v.capacity() << endl << endl;;

    // 1. 下标运算符 [] 遍历
    cout << "1. 下标运算符 [] 遍历 \t\t";
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    // 2. 迭代器遍历
    cout << "2. 迭代器遍历 \t\t\t";
    auto it = v.begin();
    while (it != v.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    // 3. const_iterator 迭代器遍历
    cout << "3. const_iterator 迭代器遍历 \t";
    v.output();

    // 4. 范围 for 遍历
    cout << "4. 范围 for 遍历 \t\t";
    for (auto& e : v)
    {
        cout << e << " ";
    }
    cout << endl;

    // 4. 范围 for 遍历 const
    cout << "5. 范围 for 遍历 const \t\t";
    for (const auto& e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

void test2()
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.output();
    cout << v.size() << endl;
    cout << v.capacity() << endl << endl;;

    // 随即插入
    v.insert(v.begin(), 0);
    v.output();

    // 删除所有偶数
    auto it = v.begin();
    while (it != v.end())
    {
        if (*it % 2 == 0)
        {
            it = v.erase(it);
        }
        else
        {
            it++;
        }
    }
    v.output();
}

void test3()
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.output();

    // resize
    v.resize(4);
    v.output();

    v.resize(8);
    v.output();
    //v.outputAll();

    // resize肯定是要动finish的， 但是空间开辟我们希望是多开一点的， resize可以做，但是这里我没做，因为没必要
    v.resize(15);
    v.output();
    //v.outputAll();

    // 清除
    v.clear();
    v.output();

    // reserve
    v.reserve(20);
    v.output();

}

void test4()
{
    // 默认构造
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(6);
    v1.push_back(7);
    v1.output();

    // 拷贝构造
    Vector<int> v2(v1);
    v2.output();

    Vector<int> v3;
    v3.push_back(10);
    v3.push_back(20);
    v3.push_back(30);
    v3.push_back(40);

    // 赋值
    v1 = v3;
    v1.output();
    v3.output();
}

void test5()
{
    // 模板
    Vector<String> v;
    v.push_back("111");
    v.push_back("222");
    v.push_back("333");
    v.push_back("444");

    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}

void test6()
{
    int* ptr1 = nullptr;
    int* ptr2 = nullptr;
    int Gap = ptr2 - ptr1;
    std::cout << "The Gap between two nullptr is : " << Gap << '\0';
    std::cout << '\n';

    // constructors used in the same order as described above:
    Vector<int> first;                                // empty vector of ints
    Vector<int> second(4, 100);                       // four ints with value 100
    Vector<int> third(second.begin(), second.end());  // iterating through second
    Vector<int> fourth(third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = { 16, 2, 77, 29 };
    Vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
    //Vector<int, int> sixth(fifth); //怎么实现二维数组?

    std::cout << "The contents of fifth are:" << '\0';;
    for (auto it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    int a[] = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    Vector<int> b(a, a + sizeof(a) / sizeof(int));
    int c = trap(b);
    std::cout << c;
}

void test7() {
    Vector<int> v1();
    Vector<int> v2(4, 100);

    int a[] = { 1, 2, 3, 4, 5 };
    Vector<int> v3(a, a + sizeof(a) / sizeof(int));

    auto it2 = v2.begin();
    int* that21 = v2.insert(it2 + 2, 50);
    v2.output();
    std::cout << *that21 << '\n';
    int* that22 = v2.erase(it2 + 3);
    v2.output();
    std::cout << *that22 << '\n';

    v3.push_back(9);
    v3.output();

    auto it3 = v3.begin();
    int* that31 = v3.insert(it3 + 2, 6);
    v3.output();
    std::cout << *that31 << '\n';

    int* that32 = v3.erase(it3 + 4);
    v3.output();
    std::cout << *that32 << '\n';

    int* that33 = v3.erase(it3 + 7);
    v3.output();
    std::cout << *that33 << '\n';
}

//int main()
//{
//    //test1();
//    //test2();
//    test3();
//    //test4();
//    //test5();
//
//    return 0;
//}