#include<myhead.h>

int num = 520;            //定义一个全局变量


int main(int argc, const char *argv[])
{
    //int num = 520;            //定义一个变量

    pid_t pid = fork();          //创建一个子进程

    if(pid > 0)
    {
        //父进程
        num = 1314;
        printf("父进程中：num = %d\n", num);     //1314

        wait(NULL);        //等待回收子进程

    }else if(pid == 0)
    {
        //子进程
        sleep(3);

        printf("子进程中：num = %d\n", num);        //?1314  520?

    }else 
    {
        perror("fork error");
        return -1;
    }

    return 0;
}