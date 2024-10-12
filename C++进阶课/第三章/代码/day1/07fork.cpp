#include<myhead.h>
int main(int argc, const char *argv[])
{
    pid_t pid = -1;            //定义用于存储进程号的变量

    //创建进程
    pid = fork();
    if(pid > 0)
    {
        //父进程程序代码
        //输出当前进程号、子进程号、父进程号
        printf("self pid=%d, child pid = %d, parent pid = %d\n", getpid(), pid, getppid());

        sleep(8);       //休眠3秒

        //wait(NULL);        //回收子进程资源,只有回收了子进程资源后，父进程才继续向后执行
        waitpid(-1, NULL, WNOHANG);     //非阻塞回收子进程资源

        printf("子进程资源已经回收\n");

    }else if(pid == 0)
    {
        //子进程程序代码
        //输出当前进程的进程号、父进程进程号
        printf("self pid = %d, parent pid = %d\n", getpid(), getppid());

        //提出子进程
        printf("11111111111111111111111111111111111");      //没有加换行，不会自动刷新

        sleep(3);

        exit(EXIT_SUCCESS);      //刷新缓冲区并退出进程
        //_exit(EXIT_SUCCESS);      //不刷新缓冲区退出进程

    }else 
    {
        perror("fork error");
        return -1;
    }

    while(1);           //防止进程退出

    return 0;
}