#include <myhead.h>
#include<thread>         //线程支持库的头文件
using namespace std;      //引入名字空间

//定义全局函数作为线程体函数
void task(int a, int b, int c)
{
    int num = 5;
    while(num--)
    {
        sleep(1);
        printf("我是分支线程, a = %d, b = %d, c= %d\n", a, b, c);
    }
}




int main() 
{
    //实例化一个线程对象
    thread th(task, 1,2,3);

    //阻塞等待分支线程的结束，并回收资源
    //th.join();

    //将线程设置成分离态
    th.detach();

    sleep(3);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}