#include <myhead.h>

//定义一个共用体，多个成员共享同一个内存空间，共享的是所占内存最大的成员空间
union Info
{
    int num;      //四字节整数
    char ch;      //一字节整数
};


int main(int argc, const char *argv[]) 
{
    //定义一个共用体变量
    union Info temp;

    //给其整型数据赋值
    temp.num = 0x12345678;

    //判断其ch成员的值
    if(temp.ch == 0x12)
    {
        cout<<"big endian"<<endl;
    }else if(temp.ch == 0x78)
    {
        cout<<"little endian"<<endl;
    }


    std::cout << "Hello, World!" << std::endl;
   return 0;
}