#include<myhead.h>
#include"sem.h"        //引入自定义的头文件

int main(int argc, const char *argv[])
{
    //1、创建并打开信号量集
    int semid = create_sem(3);
    
    while(1)
    {
        //2、申请0号信号量的资源
        P(semid, 2);

        printf("C");
        fflush(stdout);         //刷新标准输出缓冲区

        sleep(1);

        //3、释放1号信号量的资源
        V(semid, 0);
    }


    return 0;
}