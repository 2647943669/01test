#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<error.h>
#include<unistd.h>
using namespace std;
int main()
{

	//1、定义文件描述符，并打开文件
	int fd = -1;
	if((fd = open("./test.txt", O_WRONLY|O_CREAT|O_TRUNC, 0664)) ==-1)
	{
		perror("open error");
		return -1;
	}

	//2、读写文件
	write(fd, "hello", strlen("hello"));	

	//3、关闭文件
	close(fd);

	return 0;
}
