#include<myhead.h>
#include"sem.h"       //将自定义的头文件加入

#define PAGE_SIZE 4096          //一页的大小

int main(int argc, const char *argv[])
{
    //11、创建并打开信号量集
    int semid = create_sem(2);     //调用自定义函数，完成对信号量集的创建


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
        //22、调用自定义函数：申请0号信号量的资源
        P(semid, 0);         

        printf("请输入>>>");
        fgets(addr, PAGE_SIZE, stdin);       //从终端输入数据放入共享内存中
        addr[strlen(addr)-1] = 0;

        //33、调用自定义函数：释放1号信号量的资源
        V(semid, 1);
        
        if(strcmp(addr, "quit") == 0)
        {
            break;
        }
    }


    //5、取消映射
    if(shmdt(addr) == -1)
    {
        perror("取消映射\n");
        return -1;
    }

    //44、调用自定义函数：删除信号量集
    delete_sem(semid);

    return 0;
}