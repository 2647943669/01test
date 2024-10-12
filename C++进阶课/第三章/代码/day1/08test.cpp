#include<myhead.h>
//定义求文件大小的函数
int get_file_size(const char *srcfile, const char *destfile)
{
    //以只读的形式打开源文件，以创建写的形式打开目标文件
    int srcfd, destfd;        //记录源文件和目标文件的文件描述符
    if((srcfd = open(srcfile, O_RDONLY)) == -1)
    {
        perror("open secfile error");
        return -1;
    }
    if((destfd = open(destfile, O_WRONLY|O_CREAT|O_TRUNC, 0664)) == -1)
    {
        perror("open destfile error");
        return -1;
    }

    //求源文件的大小
    int len = lseek(srcfd, 0, SEEK_END);

    //关闭文件
    close(srcfd);
    close(destfd);

    return len;         //将源文件大小返回

}

//定义拷贝文件的函数
int copy_file(const char *srcfile, const char *destfile, int start, int len)
{
    //以只读的形式打开源文件，以只写的形式打开目标文件
    int srcfd, destfd;        //记录源文件和目标文件的文件描述符
    if((srcfd = open(srcfile, O_RDONLY)) == -1)
    {
        perror("open secfile error");
        return -1;
    }
    if((destfd = open(destfile, O_WRONLY)) == -1)
    {
        perror("open destfile error");
        return -1;
    }

    //将两个文件的光标位置统一
    lseek(srcfd, start, SEEK_SET); 
    lseek(destfd, start, SEEK_SET); 

    //开始拷贝
    char buf[128] = "";            //数据的搬运工
    int sum = 0;             //记录拷贝的总字节数
    while(1)
    {
        int res = read(srcfd, buf, sizeof(buf));         //从源文件中读取数据
        sum += res;              //将拷贝的字节数累加
        if(res==0 || sum>=len)
        {
            write(destfd, buf, res-(sum-len));        //将最后一次内容拷贝  
            break;              //文件结束
        }

        write(destfd, buf, res);                     //从源文件读多少，写入目标文件多少
    }

    return 0;
}




/*******************主程序***************************/
int main(int argc, const char *argv[])
{
    //使用外部传参，将要拷贝的文件以及存储文件传进来
    if(argc != 3)
    {
        printf("input file error\n");
        printf("usage:./a.out srcfile destfile\n");
        return -1;
    }

    //获取源文件的长度，并且创建目标文件
    int len = get_file_size(argv[1], argv[2]);

    //创建父子进程，分别执行拷贝函数
    pid_t pid = fork();
    if(pid > 0)
    {
        //父进程拷贝前一半内容
        copy_file(argv[1], argv[2], 0, len/2);     //从开头位置拷贝，拷贝len/2内容

        //回收子进程资源
        wait(NULL);

    }else if(pid == 0)
    {
        //子进程拷贝后一半内容
        copy_file(argv[1], argv[2], len/2, len-len/2);   //从中间开始拷贝，拷贝剩余的内容

        //退出进程
        exit(EXIT_SUCCESS);
    }else
    {
        perror("fork error");
        return -1;
    }

    printf("拷贝成功\n");
    return 0;
}