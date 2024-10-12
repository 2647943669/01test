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

    //定义要存储的字符串
    char wbuf[128] = "";
    while(1)
    {
        //提示从终端上输入字符串
        printf("请输入>>>");
        fgets(wbuf, sizeof(wbuf), stdin);  //从标准输入中读取数据
        //wbuf[strlen(wbuf)-1] = 0;       //将换行换成字符串结束标志

        //判断输入的是否为 quit
        if(strcmp(wbuf, "quit\n") == 0)
        {
            break;
        }

        //将字符串写入文件
        fwrite(wbuf, strlen(wbuf), 1, fp);     //将字符串以每个字符串为单位写入文件，每次写一项
        //fwrite("\n", strlen("\n"), 1, fp);       //每输入一个字符串加上换行
        //刷新缓冲区
        fflush(fp);
        printf("录入成功\n");
    }
    //关闭文件
    fclose(fp);

    //再次以只读的形式打开文件
    if((fp = fopen("./test.txt", "r")) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    char rbuf[10] = "";
    int res = fread(rbuf, 1, sizeof(rbuf), fp);     //从文件中读取一个字符串
    fwrite(rbuf, 1, res, stdout);         //向标准输出中写入数据


    //关闭文件
    fclose(fp);



    return 0;
}