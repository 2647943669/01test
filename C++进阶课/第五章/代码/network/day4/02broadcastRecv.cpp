#include <myhead.h>


int main(int argc, const char *argv[]) 
{
    //1、创建用于通信的套接字文件描述符
    int recvfd = socket(AF_INET, SOCK_DGRAM, 0);
    //SOCK_DGRAM表示基于udp通信方式
    if(recvfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success sfd = %d\n", recvfd);       //3


    //2、绑定ip地址和端口号
        //2.1 填充要绑定的ip地址和端口号结构体
    struct sockaddr_in rin;
    rin.sin_family = AF_INET;       //通信域
    rin.sin_port = htons(8888);   //端口号
    rin.sin_addr.s_addr = inet_addr("172.20.10.15");    //广播ip地址

    //2.2 绑定工作
    //参数1：要被绑定的套接字文件描述符
    //参数2：要绑定的地址信息结构体，需要进行强制类型转换，防止警告
    //参数3：参数2的大小
    if(bind(recvfd, (struct sockaddr*)&rin, sizeof(rin)) ==-1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");

    //3、数据收发
    char rbuf[128] = "";
    //定义容器接收对端的地址信息结构体
    struct sockaddr_in cin;
    socklen_t socklen = sizeof(cin);

    while(1)
    {
        //清空容器
        bzero(rbuf, sizeof(rbuf));

        //从客户端中读取消息
        if(recvfrom(recvfd, rbuf, sizeof(rbuf), 0, (struct sockaddr*)&cin, &socklen)==-1)
        {
            perror("recvfrom error");
            return -1;
        }

        printf("[%s:%d]:%s\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), rbuf);

    }

    //4、关闭套接字
    close(recvfd);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
