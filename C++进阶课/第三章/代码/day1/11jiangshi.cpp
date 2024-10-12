#include<myhead.h>
int main(int argc, const char *argv[])
{
    pid_t pid = -1;            //定义用于存储进程号的变量

    //创建进程
    pid = fork();
    if(pid > 0)
    {
        //父进程程序代码
        while(1)
        {
            printf("我是父进程\n");
            sleep(1);
        }
        

    }else if(pid == 0)
    {
        //子进程程序代码
       
        sleep(5);
        
        exit(EXIT_SUCCESS);     //子进程退出

    }else 
    {
        perror("fork error");
        return -1;
    }

    while(1);           //防止进程退出

    return 0;
}