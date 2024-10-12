#include"stdio.h"        //标准的输入输出头文件


int main(int argc, const char *argv[])
{
    //1、定义一个文件指针
    FILE *fp = NULL;
    //以只读的形式打开一个不存在的文件,并将返回结果存入到fp指针中
    //fp = fopen("./file.txt", "r");    
    //此时会报错，原因是以只读的形式打开一个不存在的文件，是不允许的

    //以只写的形式打开一个不存在的文件,如果文件不存在就创建一个空的文件，如果文件存在就清空
    fp = fopen("./file.txt", "w");           
    if(fp == NULL)
    {
        printf("fopen error\n");
        return -1;
    }
    printf("fopen success\n");


    //2、关闭文件
    fclose(fp);
    

    return 0;
}