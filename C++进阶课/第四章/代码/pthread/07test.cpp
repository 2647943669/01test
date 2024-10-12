#include <myhead.h>

//定义有关数据传递的结构体变量
struct msgInfo
{
    const char *srcfile;         //源文件
    const char *destfile;        //目标文件
    int start;                  //起始位置
    int len;                    //要拷贝的长度
};

//定义分支线程，完成两个文件的拷贝工作
void *task(void * arg)
{
    //将传递进来的结构体变量解析出来
    struct msgInfo info = *((struct msgInfo*)arg);

    //定义文件描述符，以只读的形式打开源文件
    int srcfd,destfd;
    //以只读的形式打开源文件
    if((srcfd = open(info.srcfile, O_RDONLY)) ==-1)
    {
        printf("srcfile open error");
        return NULL;
    }
    //以创建的形式打开目标文件，如果目标文件已存在，则清空
    if((destfd = open(info.destfile, O_WRONLY)) ==-1)
    {
        printf("destfile open error");
        return NULL;
    }

    //将两个文件指针偏移到相同位置
    lseek(srcfd, info.start, SEEK_SET);
    lseek(destfd, info.start, SEEK_SET);

    printf("start = %d, len = %d\n", info.start, info.len);

    //循环拷贝
    char buf[128] = "";          //数据的搬运工
    int sum = 0;                 //记录本次拷贝的总字节数
    while(1)
    {
        //从源文件中读取数据
        int ret = read(srcfd, buf, sizeof(buf));
        printf("%s\n", buf);
        sum += ret;                //将拷贝的字节数累加
        if(sum>=info.len)
        {
            write(destfd, buf, ret-(sum-info.len));         //最后一次拷贝
            break;
        }
        
        //说明是正常的拷贝情况
        write(destfd, buf, ret);
    }

    //关闭两个文件描述符
    close(srcfd);
    close(destfd);


}



//定义求源文件长度的函数
int get_file_len(const char *srcfile, const char *destfile)
{
    //定义两个文件描述符，分别记录两个文件
    int srcfd,destfd;
    //以只读的形式打开源文件
    if((srcfd = open(srcfile, O_RDONLY)) ==-1)
    {
        printf("srcfile open error");
        return -1;
    }
    //以创建的形式打开目标文件，如果目标文件已存在，则清空
    if((destfd = open(destfile, O_WRONLY|O_CREAT|O_TRUNC, 0664)) ==-1)
    {
        printf("destfile open error");
        return -1;
    }

    //求出源文件的大小
    int len = lseek(srcfd, 0, SEEK_END);

    //关闭两个文件
    close(srcfd);
    close(destfd);
    
    //将源文件的长度返回
    return len;
}


int main(int argc, const char *argv[]) 
{
    //1、判断外部传参的个数
    if(argc != 3)
    {
        printf("input file error\n");
        printf("usage:./a.out secfile destfile\n");
        return -1;
    }

    //2、打开源文件，并创建目标文件，求出源文件的大小
    int len = get_file_len(argv[1], argv[2]);
    printf("len = %d\n", len);

    //3、创建两个分支线程
    pthread_t tid1, tid2;

    //定义结构体变量，传输要拷贝的内容
    struct msgInfo info[2] = {{argv[1], argv[2], 0, len/2},\
                              {argv[1], argv[2], len/2, len-len/2}};

    //4、创建两个线程,线程1用于拷贝前一半内容
    if(pthread_create(&tid1, NULL, task, &info[0]) != 0)
    {
        printf("创建线程失败\n");
        return -1;
    }
    //线程2拷贝后一半内容
    if(pthread_create(&tid2, NULL, task, &info[1]) != 0)
    {
        printf("创建线程失败\n");
        return -1;
    }


    //5、主线程用于回收分支线程的资源
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);



    std::cout << "Hello, World!" << std::endl;
    return 0;
}