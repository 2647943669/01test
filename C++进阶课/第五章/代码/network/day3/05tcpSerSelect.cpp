#include <myhead.h>
#define SER_PORT 8888          // 服务器端口号
#define SER_IP "192.168.174.128" // 服务器IP地址

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


    //测试套接字地址默认是否能快速重用
    char reuse = -1;      //接收获取下来的数据
    socklen_t reuselen ;       //接收大小
    if(getsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, &reuselen)==-1)
    {
        perror("getscokopt error");
        return -1;
    }
    printf("reuse = %d\n", reuse);     //0表示默认不可用   1表示默认可用

    //设置端口号快速重用
    int reu = 1;
    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reu, sizeof(reu)) == -1)
    {
        perror("setsockopt error");
        return -1;
    }


    //验证
    if(getsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, &reuselen)==-1)
    {
        perror("getscokopt error");
        return -1;
    }
    printf("reuse = %d\n", reuse);     //   1表示默认可用






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

    // 定义文件描述符集合
    fd_set readfds, tempfds; // 读文件描述符集合

    // 将该文件描述符集合清空
    FD_ZERO(&readfds);

    // 将0号文件描述符以及sfd文件描述符放入到集合中
    FD_SET(0, &readfds);
    FD_SET(sfd, &readfds);

    // 定义一个变量，用于存储容器中的最大文件描述符
    int maxfd = sfd;

    int newfd = -1; // 接收客户端连接请求后，创建的通信套接字文件描述符
    //定义一个地址信息结构体数组来存储客户端对应的地址信息
    struct sockaddr_in cin_arr[1024];

    while (1)
    {
        // 将reafds备份一份放入tempfds中
        tempfds = readfds;

        // 调用阻塞函数，完成对文件描述符集合的管理工作
        int res = select(maxfd + 1, &tempfds, NULL, NULL, NULL);
        if (res == -1)
        {
            perror("select error");
            return -1;
        }
        else if (res == 0)
        {
            printf("time out !!!\n");
            return -1;
        }

        // 程序执行至此，表示一定有其中至少一个文件描述符产生了事件，只需要判断哪个文件描述符还在集合中
        // 就说明该文件描述符产生了事件

        // 表示sfd文件描述符触发了事件
        if (FD_ISSET(sfd, &tempfds))
        {
            newfd = accept(sfd, (struct sockaddr *)&cin, &socklen);
            // 参数1：服务器套接字文件描述符
            // 参数2：用于接收客户端地址信息结构体的容器，如果不接收，也可以填NULL
            // 参数3：接收参数2的大小，如果参数2为NULL，则参数3也是NULL
            if (newfd == -1)
            {
                perror("accept error");
                return -1;
            }
            printf("[%s:%d]:已连接成功，newfd = %d!!!!\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), newfd);

            //将该客户端对应的套接字地址信息结构体放入数组对应的位置上
            cin_arr[newfd] = cin;           //newfd文件描述符对应的地址信息结构体未cin_arr[newfd]

            // 将当前的newfd放入到检测文件描述符集合中，以便于检测使用
            FD_SET(newfd, &readfds); // 加入到tempfds中
            // 更新maxfd，如何更新？
            if (maxfd < newfd) // 判断最新的文件描述符是否比当前容器中最大的文件描述符大
            {
                maxfd = newfd;
            }
        }

        // 判断0号文件描述符是否产生了事件
        if (FD_ISSET(0, &tempfds))
        {
            char wbuf[128] = "";              // 字符数组
            fgets(wbuf, sizeof(wbuf), stdin); // 从终端读取数据,阻塞函数
            printf("触发了键盘输入事件：%s\n", wbuf);
            //能不能将输入的数据，全部发送给所有客户端
            for(int i=4; i<=maxfd; i++)
            {
                send(i, wbuf, strlen(wbuf), 0);     //将数据发送给所有客户端
            }
        }

        // 判断是否是newfd产生了事件
        // 循环将所有客户端文件描述符遍历一遍，如果还存在于tempfds中的客户端，表示有数据接收过来
        for (int i = 4; i <= maxfd; i++)
        {
            if (FD_ISSET(i, &tempfds))
            {
                // 5、数据收发
                char rbuf[128] = ""; // 数据容器

                // 清空容器中的内容
                bzero(rbuf, sizeof(rbuf));

                // 从套接字中读取消息
                int res = recv(i, rbuf, sizeof(rbuf), 0);
                if (res == 0)
                {
                    printf("对端已经下线\n");
                    // 将文件描述符进行关闭
                    close(i);
                    //需要将该文件描述符从readfds中删除
                    FD_CLR(i, &readfds);

                    // 更新maxfd
                    for(int k=maxfd; k>=0; k--)
                    {
                        if(FD_ISSET(k, &readfds))
                        {
                            maxfd = k;
                            break;       //结束向下进行的循环
                        }
                    }

                    continue; // 本次循环结束，继续下一次的select的阻塞
                }
                printf("[%s:%d]:%s\n", inet_ntoa(cin_arr[i].sin_addr), ntohs(cin_arr[i].sin_port), rbuf);

                // 对收到的数据处理一下，回给客户端
                strcat(rbuf, "*_*");

                // 将消息发送给客户端
                if (send(i, rbuf, strlen(rbuf), 0) == -1)
                {
                    perror("send error");
                    return -1;
                }
                printf("发送成功\n");
            }
        }
    }
    close(sfd);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}