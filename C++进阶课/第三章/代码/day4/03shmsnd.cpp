#include<myhead.h>

#define PAGE_SIZE 4096          //一页的大小

int main(int argc, const char *argv[])
{
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
        printf("请输入>>>");
        fgets(addr, PAGE_SIZE, stdin);       //从终端输入数据放入共享内存中
        addr[strlen(addr)-1] = 0;
        
        if(strcmp(addr, "quit") == 0)
        {
            break;
        }
    }


    sleep(5);       //休眠5秒
    printf("结束吧\n");


    //5、取消映射
    if(shmdt(addr) == -1)
    {
        perror("取消映射\n");
        return -1;
    }



    return 0;
}