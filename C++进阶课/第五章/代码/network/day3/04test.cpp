#include <myhead.h>

int main(int argc, const char *argv[]) 
{
    int num = 0, key;         //定义一个整型变量

    printf("请输入num的值：");
    scanf("%d", &num);            //提示并输入第一个值
    printf("num = %d\n", num);


    printf("请输入key的值：");
    scanf("%d", &key);           //提示并输入第二个值
    printf("num = %d\n", key);

    std::cout << "Hello, World!" << std::endl;
   return 0;
}