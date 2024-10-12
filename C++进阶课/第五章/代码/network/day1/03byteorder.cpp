#include <myhead.h>

int main(int argc, const char *argv[]) 
{
    //定义一个整型变量
    int num = 0x12345678;

    //调用函数完成数据转换为网络字节序
    int res = htonl(num);

    printf("res = %#x\n", res);      //res = 0x78563412


    std::cout << "Hello, World!" << std::endl;
   return 0;
}