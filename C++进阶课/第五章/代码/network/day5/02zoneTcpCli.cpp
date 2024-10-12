#include <myhead.h>

int main(int argc, const char *argv[]) 
{
    //1、创建用于通信的客户端套接字文件描述符
    int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(cfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("socket success cfd = %d\n", cfd);        //3

    //2、绑定ip地址和端口号(可选)    如果没有绑定，系统也不会自动绑定，会给的一个随机的文件

     //判断套接字文件是否存在
    if(access("./linux", F_OK) == 0)
    {
        //说明文件已经存在，需要将其进行删除操作
        if(unlink("./linux") == -1)
        {
            perror("unlink error");
            return -1;
        }
    }

    //2.1 填充要绑定的地址信息结构体
    struct sockaddr_un cun;
    cun.sun_family = AF_UNIX;
    strcpy(cun.sun_path, "./linux");

    //2.2 绑定工作
    if(bind(cfd, (struct sockaddr*)&cun, sizeof(cun)) == -1)
    {
        perror("bind error");
        return -1;
    }
    printf("bind success\n");
    

    //3、连接服务器
    //3.1 填充要连接的服务器地址信息结构体
    struct sockaddr_un sun;
    sun.sun_family = AF_UNIX;     //通信域
    strcpy(sun.sun_path, "./unix");    //服务器套接字文件

    //3.2 连接工作
    if(connect(cfd, (struct sockaddr*)&sun, sizeof(sun)) == -1)
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
