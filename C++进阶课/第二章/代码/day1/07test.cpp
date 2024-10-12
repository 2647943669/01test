#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int main(int argc, const char *argv[])
{
    //判断外部是否传入两个文件
    if(argc != 3)
    {
        printf("inut file error\n");
        printf("usage:./a.out srcfile destfile\n");
        return -1;
    }

    //以只读的形式打开源文件，以只写的形式打开目标文件
    FILE *srcfp = NULL;
    FILE *destfp = NULL;
    if((srcfp = fopen(argv[1], "r")) == NULL)
    {
        perror("fopen error");
        return -1;
    }
    if((destfp = fopen(argv[2], "w")) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    //定义搬运工
    char buf[128] = "";
    while(1)
    {
        char *ptr = fgets(buf, sizeof(buf), srcfp);     //将将数据从源文件中读取下来
        if(ptr == NULL)
        {
            break;             //读取结束
        }
        fputs(buf, destfp);         //将从源文件中读取的数据写入到目标文件中
    }



    //关闭文件
    fclose(srcfp);
    fclose(destfp);

    printf("拷贝成功\n");

    return 0;
}
