#include <myhead.h>

//定义要向线程体函数中出入数据的结构体类型
struct Info
{
    const char *srcfile;    //要拷贝的原文件
    const char *destfile;   //目标文件
    int start;              //起始位置
    int len;                //要拷贝的长度
};

//定义获取文件长度的函数
int get_file_len(const char *srcfile, const char *destfile)
{
    //定义两个文件描述符，分别作为源文件和目标文件的句柄
    int sfd, dfd;
    //以只读的形式打开源文件
    if((sfd = open(srcfile, O_RDONLY)) == -1)
    {
        perror("open srcfile error");
        return -1;
    }

    //以只写的形式打开目标文件
    if((dfd = open(destfile, O_RDWR|O_CREAT|O_TRUNC, 0664)) == -1)
    {
        perror("open destfile error");
        return -1;
    }

    //获取源文件的长度
    int len = lseek(sfd, 0, SEEK_END);

    //关闭文件
    close(sfd);
    close(dfd);

    return len;
}

//定义线程体函数
void *task(void *arg)
{
    //将传入的数据解析出来
    const char *srcfile = ((struct Info*)arg)->srcfile;
    const char *destfile = ((struct Info*)arg)->destfile;
    int start = ((struct Info*)arg)->start;
    int len = ((struct Info*)arg)->len;

    //准备拷贝工作
    //定义两个文件描述符，分别作为源文件和目标文件的句柄
    int sfd, dfd;
    //以只读的形式打开源文件
    if((sfd = open(srcfile, O_RDONLY)) == -1)
    {
        perror("open srcfile error");
        return NULL;
    }

    //以只写的形式打开目标文件
    if((dfd = open(destfile, O_RDWR)) == -1)
    {
        perror("open destfile error");
        return NULL;
    }

    //偏移指针
    lseek(sfd, start, SEEK_SET);
    lseek(dfd, start, SEEK_SET);

    //拷贝工作
    int ret = 0;         //记录每次读取的数据
    int count = 0;        //记录拷贝的总个数
    char buf[128] = "";         //数据搬运工
    while(1)
    {
        ret = read(sfd, buf, sizeof(buf));
        //将读取的数据放入到count中
        count += ret;
        if(count >= len)
        {
            //说明该部分的内容拷贝结束，还剩最后一次
            write(dfd, buf, ret - (count-len));
            break;
        }

        //其余的正常拷贝
        write(dfd, buf, ret);
    }

    //关闭文件描述符
    close(dfd);
    close(sfd);

}



int main(int argc, const char *argv[]) 
{
    //判断传入的文件个数是否正确
    if(argc != 3)
    {
        printf("input file error\n");
        printf("usage:./a.out srcfile destfile\n");
        return -1;
    }

    //获取原文件的长度,顺便将目标文件创建出来
    int len = get_file_len(argv[1], argv[2]);

    //创建两个线程
    pthread_t tid1, tid2;

    //定义向线程体函数传参的变量
    struct Info buf[2] = {{argv[1], argv[2], 0, len/2}, \
                           {argv[1], argv[2], len/2, len-len/2}};

    if(pthread_create(&tid1, NULL, task, &buf[0]) != 0)
    {
        printf("线程创建失败\n");
        return -1;
    }

    if(pthread_create(&tid2, NULL, task, &buf[1]) != 0)
    {
        printf("线程创建失败\n");
        return -1;
    }

    //主线程中完成对两个分支线程资源的回收
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("拷贝成功\n");


    std::cout << "Hello, World!" << std::endl;
    return 0;
}