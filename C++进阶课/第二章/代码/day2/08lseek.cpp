#include<myhead.h>
int main(int argc, const char *argv[])
{
    //1、定义文件描述符，对于文件IO而言，句柄就是文件描述符
    int fd = -1;
    //以读写的形式创建文件，如果文件不存在则创建文件，如果文件存在则清空文件
    //如果创建文件时没有给权限，则该文件的权限是随机权限
    //如果创建文件时，给定了文件的权限，则文件最终的权限是 给定的 mode&~umask
    if((fd = open("./tt.txt", O_RDWR|O_CREAT|O_TRUNC, 0644)) == -1)
    {
        perror("open error");
        return -1;
    }

    printf("open success fd = %d\n", fd);          //3,由于0、1、2已经被使用，所以该数为3

    //对数据进行读写操作
    char wbuf[128] = "hello world";
    //将上述字符串写入文件中
    write(fd, wbuf, strlen(wbuf));

    //此时文件光标是在文件的末尾位置
    
    //需求是：读取文件中的 world
    //lseek(fd, 6, SEEK_SET);            //从文件开头位置向后偏移6个字节
    lseek(fd, -5, SEEK_END);          //从文件结束位置向前偏移5个字节

    //定义接收数据容器
    char rbuf[5] = "";
    int res = read(fd, rbuf, sizeof(rbuf));      //从文件中读取数据放入rbuf中

    write(1, rbuf, res);      //向1号文件描述符中写入数据，之前读取多少，现在写入多少


    //关闭文件
    close(fd);

    return 0;
}