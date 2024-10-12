#include<myhead.h>
int main(int argc, const char *argv[])
{
    //以读写的形式打开文件
    int fd = -1;
    if((fd = open("./wukong.bmp", O_RDWR)) == -1)
    {
        perror("open error");
        return -1;
    }

    //获取文件的大小
    printf("文件大小为：%ld\n", lseek(fd, 0, SEEK_END));     //输出的就是文件大小

    //定义变量存储文件大小
    int pic_size = 0;
    lseek(fd, 2, SEEK_SET);           //将文件从起始位置向后偏移两个字节，跳过文件类型
    read(fd, &pic_size, 4);         //将文件头的 3--6字节的内容读取出来
    printf("pic_size = %d\n", pic_size);            //文件的大小

    //将文件光标向后偏移54字节，跳过文件头和信息头
    lseek(fd, 54, SEEK_SET); 
    //定义一像素的颜色：颜色规律是蓝绿红
    unsigned char color[3] = {0, 0, 255};          //定义一个绿色
    for(int i=0; i<100; i++)          //以像素为单位遍历行数,遍历前100行
    {
        for(int j=0; j<684; j++)        //遍历所有列数
        {
            //此时的 (i,j) 定位的就是一个像素点，是一个三字节为单位的颜色点
            write(fd, color, sizeof(color));        //将当前光标所在位置的像素点变成绿色
        }
    }



    //关闭文件
    close(fd);


    return 0;
}