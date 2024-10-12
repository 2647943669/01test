#include<myhead.h>
//定义信号处理函数
void handler(int signo)
{
    if(signo == SIGCHLD)
    {
        //回收僵尸进程
        while(waitpid(-1, NULL, WNOHANG) > 0);
    }
}



int main(int argc, const char *argv[])
{

    //当子进程退出后，会向父进程发送一个SIGCHLD的信号，我们可以将其捕获，在信号处理函数中将子进程资源回收
    if(signal(SIGCHLD, handler) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }

    //创建10个僵尸进程
    for(int i=0; i<10; i++)
    {

        if(fork() == 0)              //当子进程创建出来后，立马扼杀在摇篮中
        {
            exit(EXIT_SUCCESS);
        }
    }


    while(1);


    return 0;
}