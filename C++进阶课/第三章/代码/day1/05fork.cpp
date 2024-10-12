#include<myhead.h>
int main(int argc, const char *argv[])
{
    pid_t pid = -1;

    pid = fork();            //创建一个子进程，父进程会将返回值赋值给父进程中的pid变量
                            //子进程会将返回值赋值给子进程中的pid变量

    printf("pid = %d\n", pid);      //对于父进程而言会得到大于0的数字，对于子进程而言会得到0

    //对pid进程判断
    if(pid > 0)
    {
        //父进程要做执行的代码
        printf("我是父进程\n");

    }else if(pid == 0)
    {
        //子进程要执行的代码
        printf("我是子进程\n");

    }else
    {
        perror("fork error");
        return -1;
    }


    while(1);          //防止进程结束

    return 0;
}