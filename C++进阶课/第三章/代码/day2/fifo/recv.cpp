#include<myhead.h>
int main(int argc, const char *argv[])
{
    //打开管道文件
    int rfd = -1;
    if((rfd = open("./myfifo", O_RDONLY)) == -1)
    {
        perror("open error");
        return -1;
    }

    //准备要写入的数据
    char rbuf[128] = "";
    while(1)
    {
        //将容器清空
        bzero(rbuf, sizeof(rbuf));

        //从管道文件中读取数据
        read(rfd, rbuf, sizeof(rbuf));
        printf("收到数据为：%s\n", rbuf);

        if(strcmp(rbuf, "quit") == 0)
        {
            break;
        }
    }

    //关闭文件
    close(rfd);

    return 0;
}