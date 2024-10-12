#include<myhead.h>
union semun {
               int              val;    // 设置信号量的值
               struct semid_ds *buf;    //关于信号量集属性的操作
               unsigned short  *array;  //对于信号量集中所有信号量的操作
               struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
           };

//定义一个关于对信号量初始化函数
int init_sem(int semid, int semno)
{
    int val = -1;
    printf("请输入第%d个信号量的初始值：", semno+1);    //让用户输入信号量的初始值
    scanf("%d", &val);
    getchar();          //吸收回车，以免影响其他程序

    //调用semctl完成设置
    union semun us;
    us.val = val;

    if(semctl(semid, semno, SETVAL, us) == -1)
    {
        perror("semctl error");
        return -1;
    }
    return 0;
}


//创建信号量集并初始化:semcount表示本次创建的信号量集中信号灯的个数
int create_sem(int semcount)
{
    //1、创建key值
    key_t key = ftok("/", 'k');
    if(key == -1)
    {
        perror("ftok error");
        return -1;
    }

    //2、通过key值创建信号量集
    int semid = -1;
    if((semid = semget(key, semcount, IPC_CREAT|IPC_EXCL|0664)) == -1)
    {
        if(errno == EEXIST)        //表示信号量集已经存在，直接打开即可
        {
            semid = semget(key, semcount, IPC_CREAT|0664);   //将信号量集直接打开
            return semid;
        }
        perror("semget error");
        return -1;
    }

    //3、循环将信号量集中的所有信号量进行初始化
    //该操作，只有在第一次创建信号量集时需要进行操作，后面再打开该信号量集时，就无需进行初始化操作了
    for(int i=0; i<semcount; i++)
    {
        init_sem(semid, i);         //调用自定义函数将每个信号量进行初始化
    }

    //将信号量集的id返回
    return semid;
}

//申请资源操作，semno表示要被申请资源的信号量编号
int P(int semid, int semno)
{
    //定义一个结构体变量
    struct sembuf buf;
    buf.sem_num = semno;      //要操作的信号编号
    buf.sem_op = -1;            //-1表示要申请该信号量的资源
    buf.sem_flg = 0;          //表示阻塞形式进行申请

    //调用semop函数完成资源的申请
    if(semop(semid, &buf, 1) == -1)
    {
        perror("P error");
        return -1;
    }

    return 0;
}

//释放资源操作，semno表示要被释放资源的信号量编号
int V(int semid, int semno)
{
//定义一个结构体变量
    struct sembuf buf;
    buf.sem_num = semno;      //要操作的信号编号
    buf.sem_op = 1;            //1表示要释放该信号量的资源
    buf.sem_flg = 0;          //表示阻塞形式进行释放

    //调用semop函数完成资源的释放
    if(semop(semid, &buf, 1) == -1)
    {
        perror("V error");
        return -1;
    }

    return 0;
}

//删除信号量集
int delete_sem(int semid)
{
    //调用semctl函数完成对该信号量集的删除
    if(semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("delete error");
        return -1;
    }

    return 0;
}