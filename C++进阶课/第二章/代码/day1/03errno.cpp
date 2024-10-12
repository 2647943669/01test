#include"stdio.h"        //标准的输入输出头文件
#include<errno.h>          //错误码所在的头文件
#include<string.h>         //字符串处理的头文件


int main(int argc, const char *argv[])
{
    //1、定义一个文件指针
    FILE *fp = NULL;

    fp = fopen("./file.txt", "r");           
    if(fp == NULL)
    {
        //printf("fopen error: %d, errmsg:%s\n", errno, strerror(errno));     //打印错误信息，并输出错误码 2
        perror("fopen error");      //打印当前错误码对应的错误信息
        return -1;
    }
    printf("fopen success\n");

    //2、关闭文件
    fclose(fp);
    
    return 0;
}