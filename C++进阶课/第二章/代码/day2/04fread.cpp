#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

//定义一个学生信息
class Stu
{
public:
    char name[20];        //姓名
    int age;             //年龄
    double score;          //成绩
};

int main(int argc, const char *argv[])
{
    //定义文件指针，以只写的形式打开文件
    FILE *fp = NULL;
    if((fp = fopen("./test.txt", "w")) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    //定义三个学生
    Stu s[3] = {{"张三",18, 98}, \
                {"李四",20, 88}, \
                {"王五",16, 95}};
    //将三个学生信息写入文件中
    fwrite(s, sizeof(Stu), 3, fp); 
    
    //关闭文件
    fclose(fp);

    //再次以只读的形式打开文件
    if((fp = fopen("./test.txt", "r")) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    //定义一个对象，接收读取的结果
    Stu temp;

    //从文件中读取一个学生的信息
    fread(&temp, sizeof(Stu), 1, fp);


    //将读取的数据展示出来
    printf("name:%s, age:%d, score:%.2lf\n", temp.name, temp.age, temp.score);

    //关闭文件
    fclose(fp);
 

    return 0;
}