#include<myhead.h>
int main(int argc, const char *argv[])
{
    //1、定义文件描述符，对于文件IO而言，句柄就是文件描述符
    int fd = -1;
    //以只读的形式创建文件，如果文件不存在则创建文件
    //如果创建文件时没有给权限，则该文件的权限是随机权限
    //如果创建文件时，给定了文件的权限，则文件最终的权限是 给定的 mode&~umask
    if((fd = open("./tt.txt", O_WRONLY|O_CREAT, 0644)) == -1)
    {
        perror("open error");
        return -1;
    }

    printf("open success fd = %d\n", fd);          //3,由于0、1、2已经被使用，所以该数为3

    //对数据进行读写操作
    char wbuf[128] = "hello world";
    //将上述字符串写入文件中
    write(fd, wbuf, strlen(wbuf));

    //关闭文件
    close(fd);         //关闭fd引用的文件

    //再次以只读的形式打开文件
    if((fd = open("./tt.txt", O_RDONLY)) == -1)
    {
        perror("open error");
        return -1;
    }
    printf("open success fd = %d\n", fd);       //3

    //定义接收数据容器
    char rbuf[5] = "";
    int res = read(fd, rbuf, sizeof(rbuf));      //从文件中读取数据放入rbuf中

    write(1, rbuf, res);      //向1号文件描述符中写入数据，之前读取多少，现在写入多少


    //关闭文件
    close(fd);

    return 0;
}