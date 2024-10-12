#include <myhead.h>

int main(int argc, const char *argv[]) 
{
    //地址指针记录ip地址
    const char *ip = "192.168.10.12";      //点分十进制数据

    unsigned int ip_net = inet_addr(ip);    //调用函数将点分十进制转换为4字节无符号整数

    //11000000 10101000 00001010 00001100

    printf("ip_net = %#x\n", ip_net);       //ip_net = 0xc0aa8c0



    std::cout << "Hello, World!" << std::endl;
    return 0;
}