#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, const char *argv[])
{
    //向标准输出文件指针中写入数据
    fprintf(stdout, "%d %lf %s\n", 520, 3.14, "I Love Xingqiu");

    //从标准输入中读取数据到程序中来
    int num = 0;
    fscanf(stdin, "%d", &num);        //从标准输入缓冲区中以%d的格式读取一个整数
    printf("num = %d\n", num);          //1314

    //对外部文件进行格式化读写
    FILE *fp = NULL;
    if((fp = fopen("./usr.txt", "w")) == NULL)     //以只写的形式打开外部文件
    {
        perror("fopen error");
        return -1;
    }

    //向文件中写入数据
    fprintf(fp, "%s %d", "admin", 123456);      //将两个不同的数据存放到文件中
    
    //关闭文件
    fclose(fp);

    //再次以只读的形式打开文件
    if((fp = fopen("./usr.txt", "r")) == NULL)     //以只写的形式打开外部文件
    {
        perror("fopen error");
        return -1;
    }

    char usrName[20] = "";      //存放用户名
    int pwd = 0;             //存放密码
    fscanf(fp, "%s %d", usrName, &pwd);           //从外部文件中分别读取一个字符串和一个整数放入程序中的
                                            //usrName和pwd中

    //关闭
    fclose(fp);

    printf("usrName = %s, pwd = %d\n", usrName, pwd);

    return 0;
}