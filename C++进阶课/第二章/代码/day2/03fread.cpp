#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int main(int argc, const char *argv[])
{
    //定义文件指针，以只写的形式打开文件
    FILE *fp = NULL;
    if((fp = fopen("./test.txt", "w")) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    //定义要写入文件中的数据
    int num = 16;
    //将数据写入文件中
    fwrite(&num, sizeof(num), 1, fp);       //将num中的数据写入fp指向的文件中
    
    //关闭文件
    fclose(fp);

    //再次以只读的形式打开文件
    if((fp = fopen("./test.txt", "r")) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    //定义接收数据的变量
    int key = 0;
    //从文件中读取数据
    fread(&key, sizeof(key), 1, fp);

    //关闭文件
    fclose(fp);

    printf("key = %d\n", key);   



    return 0;
}