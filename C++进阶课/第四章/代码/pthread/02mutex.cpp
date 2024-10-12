#include <myhead.h>

//11、创建一个互斥锁
pthread_mutex_t mutex; 

//定义一个全局资源
int num = 520;            //临界资源

//定义分支线程1
void *task1(void *arg)
{
    while(1)
    {
         sleep(1);

        //33、获取锁资源
        pthread_mutex_lock(&mutex);

        num -= 10;         //线程1将临界资源减少10
        
        printf("张三取了10，剩余%d\n", num);

        //44、释放锁资源
        pthread_mutex_unlock(&mutex);
    }
}

//定义分支线程2
void *task2(void *arg)
{
    while(1)
    {
        sleep(1);

        //33、获取锁资源
        pthread_mutex_lock(&mutex);

        num -= 20;         //线程1将临界资源减少10
        
        printf("李四取了20，剩余%d\n", num);

        //44、释放锁资源
        pthread_mutex_unlock(&mutex);
    }
}

/*****************************主线程****************************/
int main() {

    //22、初始化互斥锁,参数NULL表示让系统自动分配互斥锁属性
    pthread_mutex_init(&mutex, NULL);

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

    //55、释放锁资源
    pthread_mutex_destroy(&mutex);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}