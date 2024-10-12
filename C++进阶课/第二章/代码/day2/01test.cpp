#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

//定义注册函数
int do_register()
{
    //定义存储注册账户和密码的容器
    char reg_name[20] = "";
    char reg_pwd[20] = "";

    //输入注册账户和密码
    printf("请输入注册账户：");
    fgets(reg_name, sizeof(reg_name), stdin);
    reg_name[strlen(reg_name)-1] = '\0';      //将字符串最后的换行符换成结束符号
    printf("请输入注册密码：");
    fgets(reg_pwd, sizeof(reg_pwd), stdin);
    reg_pwd[strlen(reg_pwd)-1] = '\0';

    //将账户和密码写入文件
    FILE *wfp = NULL;
    if((wfp = fopen("./usr.txt", "a")) == NULL)     //以追加的方式打开文件
    {
        perror("fopen error");
        return -1;
    }
    //将账户和密码写入文件
    fprintf(wfp, "%s %s\n", reg_name, reg_pwd);
    //关闭文件
    fclose(wfp);

    printf("注册成功\n");
    return 0;
}

//定义登录功能
int do_login()
{
    //定义容器存储登录账户和密码
    char log_name[20] = "";
    char log_pwd[20] = "";
    char name[20] = "";        //存储从文件中读取下来的账户
    char pwd[20] = "";         //存储从文件中读取下来的密码

    //提示并输入登录账户和密码
    printf("请输入登录账户：");
    fgets(log_name, sizeof(log_name), stdin);
    log_name[strlen(log_name)-1] = '\0';      //将字符串最后的换行符换成结束符号
    printf("请输入登录密码：");
    fgets(log_pwd, sizeof(log_pwd), stdin);
    log_pwd[strlen(log_pwd)-1] = '\0';

    //打开文件
    FILE *rfp = NULL;
    if((rfp = fopen("./usr.txt", "r")) == NULL)
    {
        perror("fopen error");
        return -1;
    }
    //将登录账户和密码跟文件中所有账户和密码进行匹配
    while(1)
    {
        //将每一行的账户和密码读取出来
        int res = fscanf(rfp, "%s %s", name, pwd);
        if(res == EOF)         //说明全部都试一遍了，他也没有成功
        {
            break;
        }

        //将读取出来的账户和密码跟登录账户和密码进行匹配
        if(strcmp(name, log_name)==0 && strcmp(pwd, log_pwd)==0)
        {
            printf("登录成功\n");
              //关闭文件
            fclose(rfp);
            return 1;
        }

    }

    printf("登录失败, 请重新登录\n");
    //关闭文件
    fclose(rfp);

    return 0;
}




/*****************主程序************/
int main(int argc, const char *argv[])
{
    int menu = 0;     //存储菜单选项变量

    while(1)
    {
        system("clear");            //创建子进程调用终端指令
        printf("\t\t======XXX 登录界面=========\n");
        printf("\t\t======1、注册==========\n");
        printf("\t\t======2、登录==========\n");
        printf("\t\t======0、退出==========\n");

        printf("请输入功能选项：");
        scanf("%d", &menu);
        getchar();             //吸收一下scanf留下的回车

        switch(menu)
        {
            case 1:
            {
                //注册
                do_register();
            }
            break;

            case 2:
            {
                //登录
                int res = do_login();
                if(res == 1)
                {
                    printf("登录成功后的界面\n");
                    //此处省略一万行程序代码
                }
            }
            break;
            case 0:exit(EXIT_SUCCESS);
            default:printf("您输入的功能有误，请重新输入!!!!!\n");
        }
        printf("请输入任意键按回车清屏\n");
        while(getchar() != '\n');
    }


    return 0;
}