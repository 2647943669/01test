#include <myhead.h>

//11、定义一个条件变量
pthread_cond_t cond;
//111、定义一个互斥锁
pthread_mutex_t mutex;

//创建生产者线程
void *task1(void *arg)
{
    /*
    int num = 3;
    while(num--)
    {
        sleep(1);
        printf("%#x:生产了一辆特斯拉\n", pthread_self());

        //44、唤醒一个消费者进行消费
        pthread_cond_signal(&cond);
    }
    */
   sleep(3);
   printf("我生产了3辆特斯拉\n");
   //44、唤醒所有消费者线程
    pthread_cond_broadcast(&cond);

    //退出线程
    pthread_exit(NULL);
}

//创建消费者线程
void *task2(void *arg)
{
    //333、获取锁资源
    pthread_mutex_lock(&mutex);

    //33、进入休眠队列，等待生产者的唤醒
    pthread_cond_wait(&cond, &mutex);

    printf("%#x:消费了一辆特斯拉，很开心\n", pthread_self());

    //444、释放锁资源
    pthread_mutex_unlock(&mutex);

    //退出线程
    pthread_exit(NULL);
}




int main() 
{

    //22、初始化条件变量
    pthread_cond_init(&cond, NULL);
    //222、初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    //1、创建两个分支线程
    pthread_t tid1,tid2,tid3,tid4;
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
    if(pthread_create(&tid3, NULL, task2, NULL) != 0)
    {
        printf("tid2 create error\n");
        return -1;
    }
    if(pthread_create(&tid4, NULL, task2, NULL) != 0)
    {
        printf("tid2 create error\n");
        return -1;
    }

    printf("主线程：tid1 = %#x, tid2 = %#x, tid3 = %#x, tid4 = %#x\n", tid1, tid2, tid3, tid4);

    //2、阻塞等待线程结束
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    //55、销毁条件变量
    pthread_cond_destroy(&cond);
    ///555、销毁互斥锁
    pthread_mutex_destroy(&mutex);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}