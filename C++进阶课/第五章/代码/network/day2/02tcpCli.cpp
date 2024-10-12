#include <myhead.h>
#define SER_PORT 8888          //服务器端口号
#define SER_IP "192.168.174.128"     //服务器IP地址
#define CLI_PORT 9999           //客户端端口号
#define CLI_IP "192.168.174.128"     //客户端ip地址

int main(int argc, const char *argv[]) 
{
    //1、创建用于通信的客户端套接字文件描述符
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success cfd = %d\n", cfd);        //3

    //2、绑定ip地址和端口号(可选)
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

    //3、连接服务器
    //3.1 填充要连接的服务器地址信息结构体
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;     //通信域
    sin.sin_port = htons(SER_PORT); //端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP);  //服务器ip地址
    //3.2 连接工作
    if(connect(cfd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("connect error");
        return -1;
    }
    printf("连接服务器成功\n");

   
    //4、数据收发
    char wbuf[128] = "";
    while(1)
    {
        //清空容器
        bzero(wbuf, sizeof(wbuf));

        //从终端获取数据
        fgets(wbuf, sizeof(wbuf), stdin);      //0     
        wbuf[strlen(wbuf)-1] = 0;         //将换行改成 '\0'

        //将数据发送给服务器
        if(send(cfd, wbuf, sizeof(wbuf), 0)==-1)
        {
            perror("send error");
            return -1;
        }




        //接受服务器发送过来的消息
        if(recv(cfd, wbuf, sizeof(wbuf), 0)==0)
        {
            printf("对端已经下线\n");
            break;
        }

        printf("收到服务器消息为：%s\n", wbuf);

    }

    //5、关闭套接字
    close(cfd);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}