#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, const char *argv[])
{
    //打开一个文件
    FILE *fp = NULL;
    if((fp = fopen("./aa.txt", "r+")) == NULL)        //以读写的形式打开文件
    {
        perror("fopen error");
        return -1;
    }

    /*1、当缓冲区刷新时机未到时，不会刷新全缓存
    fputs("hello world", fp);                //将字符串写入到文件中
    while(1);
    */

    /*2、当遇到换行时,也不会刷新全缓存
    fputs("hello world\n", fp);                //将字符串写入到文件中
    while(1);
    */

    /*3、当程序结束后，会刷新全缓存
    fputs("hello world 你好 星球！\n", fp);   
    */
    
    /*4、当输入输出发生切换时，会刷新全缓存
    fputs("I love China\n", fp);      //向文件中输出一个字符串
    fgetc(fp);               //从文件中读取一个字符，主要是让输入输出发生切换

    while(1);
    */

    /*5、当关闭缓冲区对应的文件指针时，也会刷新全缓存
    fputs("上海欢迎你", fp);
    fclose(fp);            //刷新文件指针
    while(1);
    */

    /*6、当手动刷新缓冲区对应的文件指针时，也会刷新全缓存
    fputs("上海欢迎你", fp);
    fflush(fp);            //刷新文件指针
    while(1);
    */
    
    //7、当缓冲区满了后，再向缓冲区中存放数据时会刷新全缓存
    for(int i=0; i<4097; i++)
    {
        fputc('A', fp);        //循环将单字符放入文件中
    }
    while(1);
    


    return 0;
}