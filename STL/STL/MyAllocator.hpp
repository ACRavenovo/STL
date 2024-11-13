#include <iostream>
#include <limits>
#include <stdlib.h>
//#include "headers/Allocator.hh"
#include <cinttypes>
#include <iostream>
#include <stdlib.h>
//#include <unistd.h>
#include <vector>

template <class T>
class MyAllocator
{
public:
    //�����Ǹ����ͱ�����ʵ���еĿ�ѡ��
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;

    using void_pointer = void*;
    using const_void_pointer = const void*;

    using size_type = size_t;
    using difference = std::ptrdiff_t; //typedef __int64 ptrdiff_t;

    //���°󶨺���
    template <class U>
    struct rebind
    {
        using other = MyAllocator<U>;
    };

    MyAllocator() = default;
    ~MyAllocator() = default;

    //�����ڴ�
    pointer allocate(size_type numObjects)
    {
        allocCount += numObjects;
        std::cout << "MyAllocator::allocate,�ڴ����:" << numObjects << std::endl;
        return static_cast<pointer>(operator new(sizeof(T) * numObjects));
    }

    //�����ڴ�
    pointer allocate(size_type numObjects, const_void_pointer hint)
    {

        return allocate(numObjects);
    }

    //�ͷ��ڴ�
    void deallocate(pointer p, size_type numObjects)
    {
        std::cout << "MyAllocator::deallocate,�ڴ��ͷ�:" << numObjects << std::endl;
        allocCount = allocCount - numObjects;
        operator delete(p);
    }

    //������֧�������ڴ���
    size_type max_size() const
    {
        return std::numeric_limits<size_type>::max();
    }

    // //�������
    // template <class U, class... Args>
    // void construct(U *p, Args &&... args)
    // {

    //     new (p) U(std::forward<Args>(args)...);
    // }

    // //���ٶ���
    // template <class U>
    // void destroy(U *p)
    // {
    //     p->~U();
    // }

    //����ÿ�η���/ɾ�����ڴ���
    size_type get_allocations() const
    {
        return allocCount;
    }

private:
    //ͳ�Ƶ�ǰ�ڴ��ʹ����
    size_type allocCount;
};



//int main()
//{
//    std::vector<int, MyAllocator<int>> v(0);
//
//    for (size_t i = 0; i < 30; i++)
//    {
//        sleep(1);
//        v.push_back(i);
//        std::cout << "��ǰ�����ڴ�ռ����:" << v.get_allocator().get_allocations() << std::endl;
//        //���get_allocator����vector�ڱ���������ռ�Ķ���
//    }
//}