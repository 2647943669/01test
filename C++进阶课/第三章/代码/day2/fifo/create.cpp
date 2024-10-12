#include<myhead.h>
int main(int argc, const char *argv[])
{
    //该文件主要负责创建管道文件，注意：如果管道文件已经存在，则mkfifo函数会报错
    if(mkfifo("./myfifo", 0664) == -1)
    {
        perror("mkfifo error");
        return -1;
    }
    printf("管道创建成功\n");


    return 0;
}