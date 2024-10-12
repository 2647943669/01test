#include<myhead.h>

//定义信号处理函数
void handler(int signo)
{
    if(signo == SIGINT)
    {
        printf("用户键入了ctrl + c\n");
    }
}


/*********************主程序*********************/
int main(int argc, const char *argv[])
{
    /*1、尝试忽略SIGINT信号,SIG_INGN
    if(signal(SIGINT, SIG_IGN) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }
    */
   /*2、尝试捕获SIGINT信号
   if(signal(SIGINT, handler) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }
    */

   //3、尝试默认相关信号的操作
    if(signal(SIGINT, SIG_DFL) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }



    while(1)
    {
        printf("我真的还想再活五百年\n");
        sleep(1);
    }


    return 0;
}