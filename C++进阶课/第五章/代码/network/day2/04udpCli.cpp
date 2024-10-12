#include <myhead.h>
#define SER_PORT 8888          //服务器端口号
#define SER_IP "192.168.11.53"     //服务器IP地址
#define CLI_PORT 9999     //客户端端口号
#define CLI_IP "192.168.11.53"    //客户端IP地址

int main(int argc, const char *argv[]) 
{
    //1、创建用于通信的客户端套接字文件描述符
    int cfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(cfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success cfd = %d\n", cfd);       //3

    //2、绑定ip地址和端口号（可选）
    //2.1 填充要绑定的地址信息结构体
    struct sockaddr_in cin;
    cin.sin_family = AF_INET;
    cin.sin_port = htons(CLI_PORT);
    cin.sin_addr.s_addr = inet_addr(CLI_IP);
    //2.2 绑定工作
    if(bind(cfd, (struct sockaddr*)&cin, sizeof(cin)) == -1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");



    //3、数据收发
    char wbuf[128] = "";
    //填充服务器的地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;      //通信域
    sin.sin_port = htons(SER_PORT);   //端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP);   //ip地址

    while(1)
    {
        //清空容器
        bzero(wbuf, sizeof(wbuf));

        //从终端读取数据
        fgets(wbuf, sizeof(wbuf), stdin);
        wbuf[strlen(wbuf)-1] = 0;

        //将数据发送给服务器
        sendto(cfd, wbuf, strlen(wbuf), 0, (struct sockaddr*)&sin, sizeof(sin));

        //接收服务器发来的数据
        recvfrom(cfd, wbuf, sizeof(wbuf), 0, NULL, NULL);

        printf("服务器发来的消息为：%s\n", wbuf);

    }

    //4、关闭套接字
    close(cfd);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}