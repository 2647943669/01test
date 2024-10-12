#include <myhead.h>
#define SER_PORT 8888          //服务器端口号
#define SER_IP "192.168.31.49"     //服务器IP地址


//自定义信号处理函数
void handler(int signo)
{
    if(signo == SIGCHLD)
    {
        while(waitpid(-1, NULL, WNOHANG) > 0);       //循环以非阻塞的形式回收僵尸进程
    }
}


/********************主程序***************************** */
int main(int argc, const char *argv[]) 
{

    //将子进程发送的SIGCHLD信号连接到自定义信号处理函数中
    if(signal(SIGCHLD, handler) == SIG_ERR)
    {
        perror("signal error");
        return -1;
    }

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

        //创建子进程，用于跟客户端进行通信
        pid_t pid = fork();
        if(pid > 0)
        {
            //父进程内容
            //wait(NULL);      //?   不可以使用wait，因为该函数时阻塞函数
            //waitpid(-1, NULL, WNOHANG);   //以非阻塞形式回收？
            //关闭newfd因为，父进程不对newfd进行操作
            close(newfd);

        }else if(pid == 0)
        {
            //关闭sfd，因为子进程主要专注于跟客户端的通信，主要使用newfd
            close(sfd);

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
                    return -1;
                }
                printf("发送成功\n");
            }


            //6、关闭套接字
            close(newfd); 

            //退出子进程
            exit(EXIT_SUCCESS); 
        }else
        {
            perror("fork error");
            return -1;
        }

                                                                          
    }
    close(sfd);     //关闭监听


    std::cout << "Hello, World!" << std::endl;
    return 0;
}