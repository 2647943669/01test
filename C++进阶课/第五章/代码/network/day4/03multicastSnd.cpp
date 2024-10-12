#include <myhead.h>


int main(int argc, const char *argv[]) 
{
    //1、创建用于通信的客户端套接字文件描述符
    int sendfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sendfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success cfd = %d\n", sendfd);       //3

    //2、绑定ip地址和端口号（可选）


    //3、数据收发
    char wbuf[128] = "";
    //填充接收端的地址信息结构体
    struct sockaddr_in rin;
    rin.sin_family = AF_INET;      //通信域
    rin.sin_port = htons(8888);   //端口号
    rin.sin_addr.s_addr = inet_addr("224.1.2.3");   //组播ip地址

    while(1)
    {
        //清空容器
        bzero(wbuf, sizeof(wbuf));

        //从终端读取数据
        fgets(wbuf, sizeof(wbuf), stdin);
        wbuf[strlen(wbuf)-1] = 0;

        //将数据发送给服务器r
        sendto(sendfd, wbuf, strlen(wbuf), 0, (struct sockaddr*)&rin, sizeof(rin));

    }

    //4、关闭套接字
    close(sendfd);


    std::cout << "Hello, World!" << std::endl;
    return 0;
}