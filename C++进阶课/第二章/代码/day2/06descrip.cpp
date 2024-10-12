#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, const char *argv[])
{
    //分别输出标准输入、标准输出、标准出错文件指针对应的文件描述符
    printf("stdin->_fileno = %d\n", stdin->_fileno);       //0
    printf("stdout->_fileno = %d\n", stdout->_fileno);     //1
    printf("stderr->_fileno = %d\n", stderr->_fileno);     //2
    

    return 0;
}