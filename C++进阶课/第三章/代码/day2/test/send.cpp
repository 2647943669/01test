#include<myhead.h>
int main(int argc, const char *argv[])
{

    //创建子进程
    pid_t pid = fork();
    if(pid > 0)
    {
        //父进程，完成向管道1中写入数据
        //打开管道文件
            int sfd = -1;
            if((sfd = open("./myfifo1", O_WRONLY)) == -1)
            {
                perror("open error");
                return -1;
            }

            //准备要写入的数据
            char wbuf[128] = "";
            while(1)
            {
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

        //回收子进程资源
        wait(NULL);

    }else if(pid == 0)
    {
        //子进程，完成从管道2中读取数据
            //打开管道文件
        int rfd = -1;
        if((rfd = open("./myfifo2", O_RDONLY)) == -1)
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

        //退出进程
        exit(EXIT_SUCCESS);
    }else 
    {
        perror("fork error");
        return -1;
    }

    

    return 0;
}