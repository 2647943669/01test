#include <myhead.h>

//11、创建无名信号量
sem_t sem;

//创建生产者线程
void *task1(void *arg)
{
    int num = 5;
    while(num--)
    {
        sleep(1);
        printf("我生产了一辆特斯拉\n");

        //44、释放无名信号量资源
        sem_post(&sem);
    }

    //退出线程
    pthread_exit(NULL);
}

//创建消费者线程
void *task2(void *arg)
{
    int num = 5;
    while(num--)
    {
        //33、申请无名信号量的资源
        sem_wait(&sem);

        printf("我消费了一辆特斯拉，很开心\n");
    }

    //退出线程
    pthread_exit(NULL);
}


/*******************************主程序*************************/
int main() {

    //22、初始化无名信号量,第一个0表示用于线程间通信，第二个0表示初始值为0
    sem_init(&sem, 0, 0);

    //1、创建两个分支线程
    pthread_t tid1,tid2;
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

    printf("主线程：tid1 = %#x, tid2 = %#x\n", tid1, tid2);

    //2、阻塞等待线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    //55、销毁无名信号量
    sem_destroy(&sem);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}