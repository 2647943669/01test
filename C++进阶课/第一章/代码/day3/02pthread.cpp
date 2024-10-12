#include<iostream>
#include<math.h>           //数学相关函数所在的头文件
#include<pthread.h>       //线程支持库的相关头文件
#include<unistd.h>
using namespace std;

//定义分支线程的线程体函数
void *task(void *arg)
{
	while(1)
	{
		cout << "hello world"<<endl;
		sleep(1);                     //休眠函数
	}
}



int main(int argc, const char *argv[])
{
	pthread_t tid;       //定义一个线程号变量，用于存储创建出来的线程的线程号

	//创建线程
	if(pthread_create(&tid, NULL, task, NULL) != 0)
	{
		cout << "pthread_create error" << endl;
	}

	//主线程
	while(1);

	return 0;
}
