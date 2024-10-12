#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, const char *argv[])
{
    //如果缓冲区没有被使用时，求出大小为0，只有被至少使用了一次后，缓冲区的大小就被分配了
    printf("行缓存的大小为：%d\n", stdout->_IO_buf_end - stdout->_IO_buf_base);    //行缓存的大小
    printf("行缓存的大小为：%d\n", stdout->_IO_buf_end - stdout->_IO_buf_base);     //1024

    printf("行缓存的大小为：%d\n", stdin->_IO_buf_end - stdin->_IO_buf_base);     //0  没有使用标准输入
    int num = 0;
    //scanf("%d", &num);         //从终端输入一个整数让如num变量中，类似于cin >> num
    cin >> num;             //使用了标准的输入缓冲区
    printf("行缓存的大小为：%d\n", stdin->_IO_buf_end - stdin->_IO_buf_base);    //1024

    //验证全缓存的大小为4096
    FILE *fp = NULL;
    if((fp = fopen("./aa.txt", "r")) == NULL)
    {
        perror("fopen error");
        return -1;
    }
    //未使用全缓存时，大小为0
    printf("全缓存的大小为：%d\n", fp->_IO_buf_end - fp->_IO_buf_base);     //0
    //使用一次全缓存
    fgetc(fp);           //从文件中读取一个字符
    printf("全缓存的大小为：%d\n", fp->_IO_buf_end - fp->_IO_buf_base);     //4096
    //关闭文件
    fclose(fp);

    //验证不缓存的大小为0
    //未使用不缓存时大小为0
    printf("不缓存的大小为：%d\n", stderr->_IO_buf_end - stderr->_IO_buf_base);    //0
    //使用一次不缓存
    perror("error");
    printf("不缓存的大小为：%d\n", stderr->_IO_buf_end - stderr->_IO_buf_base);    //0

    
    return 0;
}