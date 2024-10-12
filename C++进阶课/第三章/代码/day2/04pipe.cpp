#include<myhead.h>
int main(int argc, const char *argv[])
{
    //可以在此创建管道文件，并返回该管道文件的两端，那么父子进程都会拥有该管道两端的文件描述符
    int fildes[2];          //存放管道文件的两端文件描述符

    //创建无名管道，并返回该管道的两端文件描述符
    if(pipe(fildes) == -1)
    {
        perror("pipe error");
        return -1;
    }
    printf("fildes[0] = %d, fildes[1] = %d\n", fildes[0], fildes[1]);     //3   4

    pid_t pid = fork();          //创建一个子进程

    //也不可以在此创建管道文件，因为如果在此创建，那么父进程中和子进程中会分别创建一个无名管道

    if(pid > 0)
    {
        //父进程
        //不用读端，就关闭
        close(fildes[0]);

        char wbuf[128] = "hello world";    //想要将该数据发送给子进程使用
        //如果在此创建管道，那么只能父进程使用，子进程用不了，因为子进程中没有管道文件的读端和写端文件描述符
        
        //将上述数据发送给子进程,只需将数据通过写端写入管道文件中
        write(fildes[1], wbuf, strlen(wbuf));

        //sleep(3);           //休眠3秒
        //write(fildes[1], wbuf, strlen(wbuf));    //当父进程执行该语句时，管道的读端已经全部被关闭了

        //while(1);              //阻塞
        //关闭写端
        close(fildes[1]);

        wait(NULL);        //等待回收子进程

    }else if(pid == 0)
    {
        //子进程
        //关闭写端
        close(fildes[1]);

        //通过读端从管道文件中读取数据
        char rbuf[128] = "";

        while(1)
        {
        read(fildes[0], rbuf, sizeof(rbuf));

        printf("收到父进程的数据为：%s\n", rbuf);    //将数据输出到终端
        }
        
        //关闭读端
        close(fildes[0]);
        //退出子进程
        exit(EXIT_SUCCESS);
    }else 
    {
        perror("fork error");
        return -1;
    }

    return 0;
}