#include<myhead.h>
int main(int argc, const char *argv[])
{
    pid_t pid = fork();          //创建大儿子
    if(pid > 0)
    {
        //父进程
        pid_t pid_2 = fork();       //创建二儿子
        if(pid_2 > 0)
        {
            //父进程
            printf("我是父进程\n");
            //回收两个子进程的资源
            wait(NULL);
            wait(NULL);

        }else if(pid_2 == 0)
        {
            sleep(3);
            //二儿子进程内容
            printf("我是进程2\n");
            exit(EXIT_SUCCESS);
        }
    }else if(pid == 0)
    {
        sleep(3);
        //大儿子进程
        printf("我是进程1\n");
        exit(EXIT_SUCCESS);

    }else 
    {
        perror("fork error");
        return -1;
    }


    return 0;
}