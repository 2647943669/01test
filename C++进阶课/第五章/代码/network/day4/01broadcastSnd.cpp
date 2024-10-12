#include <myhead.h>

int main(int argc, const char *argv[]) 
{
    //1、创建用于通信的客户端套接字文件描述符
    int sndfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sndfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success cfd = %d\n", sndfd);       //3

    //设置允许广播
    int broad = 1;     //要设置的值
    if(setsockopt(sndfd, SOL_SOCKET, SO_BROADCAST, &broad, sizeof(broad)) ==-1)
    {
        perror("setsockopt error");
        return -1;
    }
    printf("成功设置广播\n");


    //2、可以绑定也可以不绑定

    //3、数据收发
    char wbuf[128] = "";
    //填充接收端的地址信息结构体
    struct sockaddr_in rin;
    rin.sin_family = AF_INET;      //通信域
    rin.sin_port = htons(8888);   //端口号
    rin.sin_addr.s_addr = inet_addr("172.20.10.15");   //广播ip地址

    while(1)
    {
        //清空容器
        bzero(wbuf, sizeof(wbuf));

        //从终端读取数据
        fgets(wbuf, sizeof(wbuf), stdin);
        wbuf[strlen(wbuf)-1] = 0;

        //将数据发送给服务器
        sendto(sndfd, wbuf, strlen(wbuf), 0, (struct sockaddr*)&rin, sizeof(rin));

        printf("发送成功\n");

    }

    //4、关闭套接字
    close(sndfd);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}