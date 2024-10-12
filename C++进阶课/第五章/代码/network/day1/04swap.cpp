#include <myhead.h>

int main(int argc, const char *argv[]) 
{
    //地址指针记录ip地址
    const char *ip = "172.20.10.8";    //点分十进制

    unsigned int ip_net = inet_addr(ip);    //调用函数将点分十进制转换为4字节无符号整数

    // AC  14 A 8
    printf("ip_net = %#x\n", ip_net);     //0x80a14ac

    std::cout << "Hello, World!" << std::endl;
   return 0;
}