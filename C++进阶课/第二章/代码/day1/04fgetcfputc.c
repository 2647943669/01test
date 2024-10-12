#include<stdio.h>

int main(int argc, const char *argv[])
{
    //定义文件指针
    FILE *fp = NULL;
    if((fp = fopen("./file.txt", "w")) == NULL)   //以只写的形式打开一个文件
    {
        perror("fopen error");
        return -1;
    }

    //使用程序对文件进行读写操作（单个字符进行操作）
    //本次操作的结果是在外部文件中显示Hello，说明每写入一次，文件光标都会向后偏移
    fputc('H', fp);
    fputc('e', fp);
    fputc('l', fp);
    fputc('l', fp);
    fputc('o', fp);

    //能否从该处读取数据？不可以，为什么？因为光标此时在文件结尾处，没有数据可以被读取
    //关闭文件
    fclose(fp);

    //再次以只读的形式重新打开上一个文件
    if((fp = fopen("./file.txt", "r")) == NULL)   //以只写的形式打开一个文件
    {
        perror("fopen error");
        return -1;
    }

    char ch = 0;        //字符的搬运工，将文件中的字符，搬运到终端上
    while(1)
    {
        ch = fgetc(fp);          //从fp指向的文件中光标位置处读取一个字符，并返回
        if(ch == EOF)
        {
            break;         //说明文件已经全部被读取了，此时就可以退出循环了
        }
        printf("%c ", ch);     //在终端上打印读取的字符
    }


    //关闭文件
    fclose(fp);



    return 0;
}