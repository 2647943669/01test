#include"swap.h"

//对交换函数的定义
void My_swap::run()
{
    int temp = a;
    a = b; 
    b = temp;
}

//对打印函数的定义
void My_swap::printInfo()
{
    cout << "a = " << a<< endl;
    cout << "b = " << b<< endl;
}