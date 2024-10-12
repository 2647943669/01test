#include<iostream>
#include<stdio.h>            //属于C语言的头文件，包含了输入输出函数
using namespace std;

//自定义函数
void print()
{
	cout<<"hello world"<<endl;

	cout<<"这是我想要说给大家听的!!!"<<endl;
	
}


int main(int argc, const char *argv[])
{

	int arr[5] = {1,2,3,4,5};      //定义一个整形数组
	int i = 0;                     //循环变量
	
	for(i=0; i<5; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	//调用自定义函数
	print();


	return 0;
}
