#include<myhead.h>
int main(int argc, const char *argv[])
{
    //打开管道文件
    int sfd = -1;
    if((sfd = open("./myfifo", O_WRONLY)) == -1)
    {
        perror("open error");
        return -1;
    }

    //准备要写入的数据
    char wbuf[128] = "";
    while(1)
    {
        printf("请输入>>>");
        fgets(wbuf, sizeof(wbuf), stdin);  //从终端输入数据  
        wbuf[strlen(wbuf)-1] = 0;   //将换行换成'\0'

        //将数据写入管道
        write(sfd, wbuf, strlen(wbuf));

        if(strcmp(wbuf, "quit") == 0)
        {
            break;
        }
    }

    //关闭文件
    close(sfd);

    return 0;
}