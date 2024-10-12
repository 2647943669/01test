#include<myhead.h>
int main(int argc, const char *argv[])
{
    int fildes[2];          //存放管道文件的两端文件描述符

    //创建无名管道，并返回该管道的两端文件描述符
    if(pipe(fildes) == -1)
    {
        perror("pipe error");
        return -1;
    }
    printf("fildes[0] = %d, fildes[1] = %d\n", fildes[0], fildes[1]);     //3   4


    char buf = 'A';        //定义一个字符变量
    int count = 0;         //记录向管道中写入数据的个数

    while(1)
    {
        write(fildes[1], &buf, 1);        //向管道文件中每次写入1字节的数据
        count++;
        printf("count = %d\n", count);
    }

    //关闭文件描述符
    close(fildes[0]);
    close(fildes[1]);


    return 0;
}