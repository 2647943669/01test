#include <myhead.h>
#define SER_PORT 8888          //服务器端口号
#define SER_IP "192.168.64.128"     //服务器IP地址

int main(int argc, const char *argv[]) 
{
    //1、创建用于通信的套接字文件描述符
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    //SOCK_DGRAM表示基于udp通信方式
    if(sfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success sfd = %d\n", sfd);       //3


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
        if(recvfrom(sfd, rbuf, sizeof(rbuf), 0, (struct sockaddr*)&cin, &socklen)==-1)
        {
            perror("recvfrom error");
            return -1;
        }

        printf("[%s:%d]:%s\n", inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), rbuf);

        //加个笑脸发给客户端
        strcat(rbuf, "*_*");

        //将数据发送给客户端
        sendto(sfd, rbuf, strlen(rbuf), 0, (struct sockaddr*)&cin, sizeof(cin));
        printf("发送成功\n");

    }

    //4、关闭套接字
    close(sfd);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}