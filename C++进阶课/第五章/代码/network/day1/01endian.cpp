#include <myhead.h>

int main(int argc, const char *argv[]) 
{
    //定义一个整型变量
    int num = 0x12345678;

    //定义一个字符指针指向该整型变量
    char *ptr = (char *)&num;

    //如果ptr中的内容是0x12则是大端存储
    //如果是0x78则是小端存储
    if(*ptr == 0x12)
    {
        cout<< "big endian"<<endl;
    }else if(*ptr == 0x78)
    {
        cout << "little endian" << endl;
    }



    std::cout << "Hello, World!" << std::endl;
   return 0;
}