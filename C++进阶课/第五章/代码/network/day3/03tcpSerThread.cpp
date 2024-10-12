#include <myhead.h>
#define SER_PORT 8888          //服务器端口号
#define SER_IP "192.168.31.49"     //服务器IP地址

//定义用于传送数据的结构体类型
struct Info
{
    int newfd;      //套接字文件描述符
    struct sockaddr_in cin;    //客户端套接字地址信息结构体
};


//分支线程，用户跟客户端进行通信
void *deal_cli_msg(void *arg)
{
    //解析传过来的数据
    int newfd = ((struct Info *)arg)->newfd;    //解析套接字文件描述符
    struct sockaddr_in cin = ((struct Info *)arg)->cin;

//5、数据收发
        char rbuf[128] = "";       //数据容器
        while(1)
        {
            //清空容器中的内容
            bzero(rbuf, sizeof(rbuf));

            //从套接字中读取消息
            int res = recv(newfd, rbuf, sizeof(rbuf), 0);
            if(res == 0)
            {
                printf("对端已经下线\n");
                break;
            }
            printf("[%s:%d]:%s\n", inet_ntoa(cin.sin_addr),  ntohs(cin.sin_port), rbuf);

            //对收到的数据处理一下，回给客户端
            strcat(rbuf, "*_*");

            //将消息发送给客户端
            if(send(newfd, rbuf, strlen(rbuf), 0) == -1)
            {
                perror("send error");
                return NULL;
            }
            printf("发送成功\n");
        }


        //6、关闭套接字
        close(newfd);     

        //退出分支线程
        pthread_exit(NULL);            
}



/******************************主程序********************************* */
int main(int argc, const char *argv[]) 
{
    //1、创建用于连接的套接字文件描述符
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    //参数1：AF_INET表示使用的是ipv4的通信协议
    //参数2：SOCK_STREAM表示使用的是tcp通信
    //参数3：由于参数2指定了协议，参数3填0即可
    if(sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success sfd = %d\n", sfd);         //3

    //2、绑定ip地址和端口号
    //2.1 填充要绑定的ip地址和端口号结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;       //通信域
    sin.sin_port = htons(SER_PORT);   //端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP);    //ip地址

    //2.2 绑定工作
    //参数1：要被绑定的套接字文件描述符
    //参数2：要绑定的地址信息结构体，需要进行强制类型转换，防止警告
    //参数3：参数2的大小
    if(bind(sfd, (struct sockaddr*)&sin, sizeof(sin)) ==-1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    //3、启动监听
    //参数1：要启动监听的文件描述符
    //参数2：挂起队列的长度
    if(listen(sfd, 128) ==-1)
    {
        perror("listen error");
        return -1;
    }
    printf("listen success\n");

    //4、阻塞等待客户端的连接请求
    //定义变量，用于接受客户端地址信息结构体
    struct sockaddr_in cin;             //用于接收地址信息结构体的
    socklen_t socklen = sizeof(cin);        //用于接收地址信息的长度

    while(1)
    {

        //对于accept函数而言，当程序执行到该函数时，会给当前客户端预分配一个最小未使用的文件描述符
        //后期再有新的小的文件描述符，也不使用了，新的最小的，用于下一次客户端的选定
        int newfd = accept(sfd, (struct sockaddr *)&cin, &socklen);
        //参数1：服务器套接字文件描述符
        //参数2：用于接收客户端地址信息结构体的容器，如果不接收，也可以填NULL
        //参数3：接收参数2的大小，如果参数2为NULL，则参数3也是NULL
        if(newfd == -1)
        {
            perror("accept error");
            return -1;
        }
        printf("[%s:%d]:已连接成功，newfd = %d!!!!\n", inet_ntoa(cin.sin_addr),  ntohs(cin.sin_port), newfd);

        //填充要传输给分支线程的数据结构体变量
        struct Info buf = {newfd, cin};

        //创建分支线程，用于处理客户端的操作
        pthread_t tid = -1;
        if(pthread_create(&tid, NULL, deal_cli_msg, &buf) != 0)
        {
            printf("pthread_create error\n");
            return -1;
        }

        //完成对分支线程资源的处理
        //pthread_join(tid, NULL);        //?  不能使用该函数回收，因为该函数时阻塞函数
        pthread_detach(tid);        //将线程设置成分离态，执行结束后，系统自动回收资源

                                                          
    }
    close(sfd);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}