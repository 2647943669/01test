#include<stdio.h>
#include<iostream>
#include<string.h>

int main(int argc, const char *argv[])
{
    //打开文件
    FILE *fp = NULL;
    if((fp = fopen("./file.txt", "w")) == NULL)
    {
        perror("fopen eror");
        return -1;
    }

    //向文件中写入多个字符
    char wbuf[128] = "";    //定义一个字符数组

    while(1)
    {
        std::cin >> wbuf;      //从终端输入一个字符串
        //将上述字符串写入文件中
        fputs(wbuf, fp); 
        fputc('\n', fp);

        if(strcmp(wbuf, "quit") == 0)      //strcmp：比较两个字符串是否一致，如果相等则返回0
        {
            break;
        }

    }
    //关闭文件
    fclose(fp);

    //以只读的形式再次打开文件
    if((fp = fopen("./file.txt", "r")) == NULL)
    {
        perror("fopen eror");
        return -1;
    }

    char rbuf[128] = "";
    while(1)
    {
        //从文件中读取数据到rbuf容器中
        char *res = fgets(rbuf, sizeof(rbuf), fp);
        if(res == NULL)
        {
            break;              //说明文件读取结束
        }

        printf("rbuf = %s\n", rbuf);       //将数据打印到终端上

    }

    //关闭文件
    fclose(fp);


    return 0;
}