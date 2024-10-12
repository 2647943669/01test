#include<myhead.h>

//消息类型的定义
struct msgBuf{
               long mtype;       //  消息的类型
               char mtext[1024];    //消息正文
           };
#define MSGSZ (sizeof(struct msgBuf)-sizeof(long))      //正文的大小


int main(int argc, const char *argv[])
{
    //1、创建key值，用于创建出一个消息队列
    key_t key = ftok("/", 'k');            
    //参数1：已经存在的路径
    //参数2:是一个随机值
    if(key == -1)
    {
        perror("ftok error");
        return -1;
    }
    printf("key = %#x\n", key);      //输出键值

    //2、通过key值创建出一个消息队列，并返回该消息队列的id
    int msqid = -1;
    if((msqid = msgget(key, IPC_CREAT|0664)) == -1)
    {
        perror("msgget error");
        return -1;
    }
    printf("msgqid = %d\n", msqid);        //输出id号

    //创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        //父进程
        //3、向消息队列中存放消息
        //组建一个消息
        struct msgBuf buf = {.mtype = 1};       //向消息队列中放入类型为1的消息
        while(1)
        {
            fgets(buf.mtext, MSGSZ, stdin);      //从终端输入数据
            buf.mtext[strlen(buf.mtext)-1] = '\0';     //将换行更换成'\0'

            //将上述组装的消息放入消息队列中, 以阻塞的方式将其放入消息队列
            msgsnd(msqid, &buf, MSGSZ, 0);

            //判断退出条件
            if(strcmp(buf.mtext, "quit") == 0)
            {
                break;
            }
        }

    }else if(pid == 0)
    {
        //子进程
        struct msgBuf buf;
        while(1)
        {
            //清空容器
            bzero(&buf, sizeof(buf));

            //读取消息
            msgrcv(msqid, &buf, MSGSZ, 2, 0);     //从消息队列中读取类型2的消息
            //参数4：表示读取的消息类型
            //参数5：表示是否阻塞读取

            printf("读取到的消息为:%s\n", buf.mtext);

            if(strcmp(buf.mtext,"quit") == 0)
            {
                    break;
            }
        }

    }else 
    {
        perror("fork error");
        return -1;
    }

    
    return 0;
}