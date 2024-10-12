#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, const char *argv[])
{
    //perror("a");        //向标准出错中放入数据

    fputs("A", stderr);          //向标准出错缓冲区中写入一个字符A

    while(1);          //阻塞


    return 0;
}