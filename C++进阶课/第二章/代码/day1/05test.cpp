#include<stdio.h>

int main(int argc, const char *argv[])
{
    //判断外部传参的个数是否为 3
    if(argc != 3)
    {
        printf("input file error\n");
        printf("usage:./a.out srcfile destfile\n");
        return -1;
    }

    //以只读的形式打开源文件，以只写的形式打开目标文件
    FILE *srcfp = NULL;    //源文件文件指针
    FILE *destfp = NULL;   //目标文件文件指针
    if((srcfp = fopen(argv[1], "r")) ==NULL)
    {
        perror("srcfile open error");
        return -1;
    }
    if((destfp = fopen(argv[2], "w")) ==NULL)
    {
        perror("destfile open error");
        return -1;
    }

    //将源文件中的内容搬运到目标文件中
    char ch = 0;        //搬运工
    while(1)
    {
        ch = fgetc(srcfp);      //从源文件中读取一个字符
        if(ch == EOF)
        {
            break;              //文件全部读取结束
        }

        fputc(ch, destfp);        //将读取的字符写入到目标文件中

    }

    //关闭两个文件
    fclose(srcfp);
    fclose(destfp);

    printf("拷贝成功\n");

    return 0;
}