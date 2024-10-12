#include <myhead.h>

sem_t sem1, sem2, sem3;

void *task1(void *arg)
{
    while (1)
    {
        sem_wait(&sem3);
        sleep(1);
        printf("A\n");
        sem_post(&sem1);
    }

}

void *task2(void *arg)
{
    while (1)
    {
        sem_wait(&sem1);
        sleep(1);
        printf("B\n");
        sem_post(&sem2);
    }
    
}

void *task3(void *arg)
{
    while (1)
    {
        sem_wait(&sem2);
        sleep(1);
        printf("C\n");
        sem_post(&sem3);
    }
    
}



int main(int argc, const char *argv[]) 
{
    //定义三个任务
    pthread_t tid1, tid2, tid3;

    //初始化无名信号量
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 1);

    //创建三个任务
    if(pthread_create(&tid1, NULL, task1, NULL) != 0)
    {
        printf("tid1 create error\n");
        return -1;
    }

    if(pthread_create(&tid2, NULL, task2, NULL) != 0)
    {
        printf("tid1 create error\n");
        return -1;
    }

    if(pthread_create(&tid3, NULL, task3, NULL) != 0)
    {
        printf("tid1 create error\n");
        return -1;
    }

    //阻塞回收线程
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);




    std::cout << "Hello, World!" << std::endl;
    return 0;
}