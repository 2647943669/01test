#include<iostream>
#include<stdio.h>            //属于C语言的头文件，包含了输入输出函数
using namespace std;
int main(int argc, const char *argv[])
{
	int *ptr = NULL;       //定义一个指针变量并赋值为空

	*ptr = 520;       //此时能不能进行操作？绝对不能进行的

	return 0;
}
