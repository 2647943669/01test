#ifndef SWAP_H
#define SWAP_H

#include<myhead.h>

//声明一个自定义交换类
class My_swap
{
private:
    int a;
    int b;          //两个成员变量
public:
    //定义构造函数
    My_swap(int a, int b)
    {
        this->a = a; 
        this->b = b;
    }

    //声明交换函数
    void run();

    //声明打印函数
    void printInfo();
    
};


#endif

