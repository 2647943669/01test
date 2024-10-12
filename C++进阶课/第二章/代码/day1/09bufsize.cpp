#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, const char *argv[])
{
    /*1、验证缓冲区如果没有达到刷新时机，就不会将数据进行刷新
    printf("hello world");           //在终端上打印输出一个hello world,没有到缓冲区的刷新时机，就不会输出数据

    while(1);             //阻塞程序不让进程结束
    */

   /*2、当程序结束后，会刷新行缓冲区
   printf("hello world");
   */

    /*3、当遇到换行时，会刷新行缓存
    printf("hello world\n");
    while(1);
    */

    /*4、当输入输出发生切换时，也会刷新行缓存
    int num = 0;
    printf("请输入>>>");        //向标准输出缓冲区中写入一组数据，没有换行符号
    scanf("%d", &num);            //cin >> num
    */

    /*5、当关闭行缓存对应的文件指针时，也会刷新行缓存
    printf("hello world");       //向标准输出缓冲区中写入数据，没有换行
    fclose(stdout);          //关闭标准输出指针
    while(1);
    */

    /*6、使用fflush函数手动刷新缓冲区时，行缓存会被刷新
    printf("hello world");
    fflush(stdout);
    while(1);
    */
    
    //7、当缓冲区满了后，会刷新行缓存，行缓存大小：1024字节
    for(int i=0; i<1025; i++)
    {
        printf("A");
    }
    while(1);      //防止程序结束



    
    return 0;
}