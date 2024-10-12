#include<myhead.h>
#include"sem.h"

#define PAGE_SIZE 4096          //一页的大小

int main(int argc, const char *argv[])
{
    //11、调用自定义函数：创建并打开信号量集
     int semid = create_sem(2);  

    //1、创建key值
    key_t key = ftok("/", 'k');
    if(key == -1)
    {
        perror("ftok error");
        return -1;
    }
    printf("key = %#x\n", key);      //输出key值

    //2、通过key值创建共享内存段
    int shmid = -1;
    if((shmid= shmget(key, PAGE_SIZE, IPC_CREAT|0664)) == -1)
    {
        perror("shmget error");
        return -1;
    }
    printf("shmid = %d\n", shmid);

    //3、将共享内存段映射到用户空间
    char *addr = (char *)shmat(shmid, NULL, 0);
    //NULL表示让系统自动寻找对齐页
    //0表示对该共享内存段的操作是读写操作打开
    if(addr == (void*)-1)
    {
        perror("shmat error");
        return -1;
    }
    printf("addr = %p\n", addr);        //输出共享内存段映射的地址

    //4、对共享内存进行操作
    while(1)
    {
        //22、调用自定义函数完成对1号信号量资源的申请
        P(semid, 1);

        printf("读取到消息为：%s\n", addr);    //通过地址访问共享内存中的数据

        if(strcmp(addr, "quit") == 0)
        {
            break;
        }

        //33、释放0号信号量的资源
        V(semid, 0);
    }

    //5、取消映射
    if(shmdt(addr) == -1)
    {
        perror("取消映射\n");
        return -1;
    }

    //6、删除共享内存段
    if(shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl error");
        return -1;
    }

    return 0;
}