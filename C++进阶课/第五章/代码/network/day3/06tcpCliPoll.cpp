#include <myhead.h>
#define SER_PORT 8888            // 服务器端口号
#define SER_IP "192.168.174.128" // 服务器IP地址
#define CLI_PORT 9999            // 客户端端口号
#define CLI_IP "192.168.174.128" // 客户端ip地址

int main(int argc, const char *argv[])
{
    // 1、创建用于通信的客户端套接字文件描述符
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success cfd = %d\n", cfd); // 3

    // 2、绑定ip地址和端口号(可选)
    // 2.1 填充要绑定的地址信息结构体
    struct sockaddr_in cin;
    cin.sin_family = AF_INET;
    cin.sin_port = htons(CLI_PORT);
    cin.sin_addr.s_addr = inet_addr(CLI_IP);
    // 2.2 绑定工作
    if (bind(cfd, (struct sockaddr *)&cin, sizeof(cin)) == -1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    // 3、连接服务器
    // 3.1 填充要连接的服务器地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;                // 通信域
    sin.sin_port = htons(SER_PORT);          // 端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP); // 服务器ip地址
    // 3.2 连接工作
    if (connect(cfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("connect error");
        return -1;
    }
    printf("连接服务器成功\n");

    // 使用poll完成终端输入和套接字接收数据的并发执行
    struct pollfd pfds[2]; // pfds[0]   pfds[1]
    // 分别给数组中两个文件描述符成员赋值
    pfds[0].fd = 0;          // 表示检测0号
    pfds[0].events = POLLIN; // 表示检测的是读事件

    pfds[1].fd = cfd;        // 检测cfd文件描述符
    pfds[1].events = POLLIN; // 检测读事件

    // 4、数据收发
    char wbuf[128] = "";
    while (1)
    {
        int res = poll(pfds, 2, -1);
        // 功能：阻塞等待文件描述符集合中是否有事件产生
        // 参数1：文件描述符集合起始地址
        // 参数2：文件描述符个数
        // 参数3：表示永久等待
        if (res == -1)
        {
            perror("poll error");
            return -1;
        }

        // 程序执行至此，表示文件描述符容器中，有事件产生
        // 表示0号文件描述符的事件
        if (pfds[0].revents == POLLIN)
        {
            // 清空容器
            bzero(wbuf, sizeof(wbuf));

            // 从终端获取数据
            fgets(wbuf, sizeof(wbuf), stdin); // 0
            wbuf[strlen(wbuf) - 1] = 0;       // 将换行改成 '\0'

            // 将数据发送给服务器
            if (send(cfd, wbuf, sizeof(wbuf), 0) == -1)
            {
                perror("send error");
                return -1;
            }
        }

        //表示有客户端发来消息
        if (pfds[1].revents == POLLIN)
        {
            // 接受服务器发送过来的消息
            if (recv(cfd, wbuf, sizeof(wbuf), 0) == 0) // cfd
            {
                printf("对端已经下线\n");
                break;
            }

            printf("收到服务器消息为：%s\n", wbuf);
        }
    }

    // 5、关闭套接字
    close(cfd);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}