#include<myhead.h>
int main(int argc, const char *argv[])
{


    fork();            //创建一个子进程
    fork();            //创建一个子进程
    fork();            //创建一个子进程

    while(1);          //防止进程结束

    return 0;
}