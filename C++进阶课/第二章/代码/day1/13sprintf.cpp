#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc, const char *argv[])
{
    char buf[10] = "";         //定义一个字符串容器
    //需求：将多种数据类型的数据连接成一个字符串，放入字符数组中
    //sprintf(buf, "%d %s %lf", 1001, "zhangsanfeng", 99.5);

    //安全起见，我们使用snprintf
    snprintf(buf, sizeof(buf), "%d %s %lf", 1001, "zhangsanfeng", 99.5);

    //输出转换后的字符串
    printf("buf = %s\n", buf);          //1001 zhangsanfeng 99.500000

    return 0;
}