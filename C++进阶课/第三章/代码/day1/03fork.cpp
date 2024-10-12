#include<myhead.h>
int main(int argc, const char *argv[])
{
    printf("ni hao xingqiu\n");

    fork();            //创建一个子进程

    printf("hello world\n");

    while(1);          //防止进程结束

    return 0;
}