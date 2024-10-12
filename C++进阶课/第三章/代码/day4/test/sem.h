#ifndef _SEM_H_
#define _SEM_H_

//创建信号量集并初始化:semcount表示本次创建的信号量集中信号灯的个数
int create_sem(int semcount);

//申请资源操作，semno表示要被申请资源的信号量编号
int P(int semid, int semno);

//释放资源操作，semno表示要被释放资源的信号量编号
int V(int semid, int semno);

//删除信号量集
int delete_sem(int semid);

#endif