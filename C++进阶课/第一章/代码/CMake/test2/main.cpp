#include "swap.h"

int main(int argc, const char *argv[]) 
{
    //声明一个交换类对象,调用有参构造完成
    My_swap my_swap(520, 1314);   

    //输出交换前的结果
    my_swap.printInfo();      //520  1314

    cout<<"**************************"<<endl;

    //调用交换函数
    my_swap.run();

    //输出交换后的结果
    my_swap.printInfo();

    
    return 0;
}