#include<myhead.h>
int main(int argc, const char *argv[])
{
    pid_t pid = -1;

    pid = fork();            //创建一个子进程，父进程会将返回值赋值给父进程中的pid变量
                            //子进程会将返回值赋值给子进程中的pid变量
    //对pid进程判断
    if(pid > 0)
    {
        while(1)
        {
        //父进程要做执行的代码
        printf("我是父进程1111\n");
        sleep(1);
        }

    }else if(pid == 0)
    {
        while(1)
        {
        //子进程要执行的代码
        printf("我是子进程\n");
        sleep(1);
        }

    }else
    {
        perror("fork error");
        return -1;
    }

    return 0;
}