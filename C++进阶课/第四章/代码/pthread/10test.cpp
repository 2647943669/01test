#include <myhead.h>

//1、定义三个无名信号量
sem_t sem1, sem2, sem3;

//定义三个任务，分别打印A\B\C
void *task1(void *arg)
{
    while(1)
    {
        //申请sem1的资源
        sem_wait(&sem1);

        sleep(1);
        printf("A");
        fflush(stdout);       //刷新缓冲区

        //释放sem2的资源
        sem_post(&sem2);
    }
}

void *task2(void *arg)
{
    while(1)
    {
        //申请sem2的资源
        sem_wait(&sem2);

        sleep(1);
        printf("B");
        fflush(stdout);       //刷新缓冲区

        //释放sem3的资源
        sem_post(&sem3);
    }
}

void *task3(void *arg)
{
    while(1)
    {
        //申请sem3的资源
        sem_wait(&sem3);

        sleep(1);
        printf("C");
        fflush(stdout);       //刷新缓冲区

        //释放sem1的资源
        sem_post(&sem1);
    }
}




/********************主程序**************** */
int main(int argc, const char *argv[]) 
{

    //初始化无名信号量
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);

    //准备三个任务
    pthread_t tid1, tid2, tid3;

    //创建三个任务
    if(pthread_create(&tid1, NULL, task1, NULL) != 0)
    {
        printf("tid1 create error\n");
        return -1;
    }
    if(pthread_create(&tid2, NULL, task2, NULL) != 0)
    {
        printf("tid2 create error\n");
        return -1;
    }
    if(pthread_create(&tid3, NULL, task3, NULL) != 0)
    {
        printf("tid3 create error\n");
        return -1;
    }

    //阻塞等待分支线程的结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}