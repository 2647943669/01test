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

    //3、向消息队列中存放消息
    //组建一个消息
    struct msgBuf buf;
    while(1)
    {
        printf("请输入消息的类型：");
        scanf("%ld", &buf.mtype);
        getchar();                //吸收回车
        printf("请输入消息正文:");
        fgets(buf.mtext, MSGSZ, stdin);      //从终端输入数据
        buf.mtext[strlen(buf.mtext)-1] = '\0';     //将换行更换成'\0'

        //将上述组装的消息放入消息队列中, 以阻塞的方式将其放入消息队列
        msgsnd(msqid, &buf, MSGSZ, 0);
        printf("消息存入成功\n");

        //判断退出条件
        if(strcmp(buf.mtext, "quit") == 0)
        {
            break;
        }
    }
    return 0;
}