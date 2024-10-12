#include<myhead.h>

//定义信号处理函数
void handler(int signo)
{
    if(signo == SIGUSR1)
    {
        printf("逆子，何至于此!!!\n");
        raise(SIGKILL);                 //向自己发送一个自杀信号  kill(getpid(), SIGKILL)
    }
}


int main(int argc, const char *argv[])
{
    //将子进程发送的信号绑定到指定功能中
    if(signal(SIGUSR1, handler) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }

    //创建父子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        //父进程
        while(1)
        {
            printf("我真的还想再活五百年\n");
            sleep(1);
        }

    }else if(pid == 0)
    {
        //子进程
        sleep(5);
        printf("红尘已经看破，叫上父亲一起死吧\n");

        kill(getppid(), SIGUSR1);        //向自己的父进程发送了一个自定义的信号

        exit(EXIT_SUCCESS);         //退出进程
    }


    return 0;
}