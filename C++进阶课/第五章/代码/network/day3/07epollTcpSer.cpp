#include <myhead.h>
#define SER_PORT 8888        // 服务器端口号
#define SER_IP "172.20.10.8" // 服务器IP地址

int main(int argc, const char *argv[])
{
    // 1、创建用于连接的套接字文件描述符
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    // 参数1：AF_INET表示使用的是ipv4的通信协议
    // 参数2：SOCK_STREAM表示使用的是tcp通信
    // 参数3：由于参数2指定了协议，参数3填0即可
    if (sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success sfd = %d\n", sfd); // 3

    // 2、绑定ip地址和端口号
    // 2.1 填充要绑定的ip地址和端口号结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;                // 通信域
    sin.sin_port = htons(SER_PORT);          // 端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP); // ip地址

    // 2.2 绑定工作
    // 参数1：要被绑定的套接字文件描述符
    // 参数2：要绑定的地址信息结构体，需要进行强制类型转换，防止警告
    // 参数3：参数2的大小
    if (bind(sfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    // 3、启动监听
    // 参数1：要启动监听的文件描述符
    // 参数2：挂起队列的长度
    if (listen(sfd, 128) == -1)
    {
        perror("listen error");
        return -1;
    }
    printf("listen success\n");

    // 4、阻塞等待客户端的连接请求
    // 定义变量，用于接受客户端地址信息结构体
    struct sockaddr_in cin;          // 用于接收地址信息结构体的
    socklen_t socklen = sizeof(cin); // 用于接收地址信息的长度

    // 创建epoll实例，用于检测文件描述符
    int epfd = epoll_create(1);
    if (epfd == -1)
    {
        perror("epoll_create error");
        return -1;
    }

    // 将sfd放入到检测集合中
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET; // 要检测的是读事件   EPOLLET表示该文件描述符检测是使用边沿触发模式
    ev.data.fd = sfd;    // 要检测的文件描述符信息
    epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &ev);
    // 功能：将sfd放入到检测集合中
    // 参数1：epoll实例的文件描述符
    // 参数2：epoll操作，表示要添加文件描述符
    // 参数3：要检测的文件描述符的值
    // 参数4：要检测的事件

    // 定义接收返回的事件集合
    struct epoll_event evs[1024];
    int size = sizeof(evs) / sizeof(evs[0]); // 数组的大小

    while (1)
    {
        // 阻塞检测文件描述符集合中是否有事件产生
        int num = epoll_wait(epfd, evs, size, -1);
        // 参数1：epoll实例的文件描述符
        // 参数2：返回触发事件的文件事件集合
        // 参数3：集合的大小
        // 参数4：是否阻塞
        printf("num = %d\n", num); // 输出本次触发的文件描述符个数

        // 循环遍历集合，判断是哪个文件描述符就绪
        for (int i = 0; i < num; i++)
        {
            int fd = evs[i].data.fd; // 获取本次解除阻塞的文件描述符

            // 判断是否为sfd文件描述符就绪
            if (fd == sfd)
            {
                // 说明有新的客户端发来连接请求
                int newfd = accept(sfd, (struct sockaddr *)&cin, &socklen);
                // 参数1：服务器套接字文件描述符
                // 参数2：用于接收客户端地址信息结构体的容器，如果不接收，也可以填NULL
                // 参数3：接收参数2的大小，如果参数2为NULL，则参数3也是NULL
                if (newfd == -1)
                {
                    perror("accept error");
                    return -1;
                }
                printf("[%s:%d]:已连接成功，newfd = %d!!!!\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), newfd);

                // 将客户端文件描述符放入到epoll检测集合中
                struct epoll_event ev;
                ev.events = EPOLLIN | EPOLLET; // 要检测的是读事件
                ev.data.fd = newfd;  // 要检测的文件描述符信息
                epoll_ctl(epfd, EPOLL_CTL_ADD, newfd, &ev);
            }
            else
            {
                // 表示客户端文件描述符就绪，也就是说客户端有数据发来
                // 5、数据收发
                char rbuf[5] = ""; // 数据容器

                // 清空容器中的内容
                bzero(rbuf, sizeof(rbuf));

                // 从套接字中读取消息
                int res = recv(fd, rbuf, sizeof(rbuf)-1, 0);
                if (res == 0)
                {
                    printf("对端已经下线\n");
                    //将客户端从epoll树中删除
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);

                    //关闭套接字
                    close(fd);

                    break;
                }
                printf("收到数据:%s\n",  rbuf);

                // 对收到的数据处理一下，回给客户端
                strcat(rbuf, "*_*");

                // 将消息发送给客户端
                if (send(fd, rbuf, strlen(rbuf), 0) == -1)
                {
                    perror("send error");
                    return -1;
                }
                printf("发送成功\n");

            }
        }
    }
    close(sfd);         //关闭监听
    close(epfd);    //关闭epoll实例

    std::cout << "Hello, World!" << std::endl;
    return 0;
}