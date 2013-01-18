/* 8888888888888888888888888888888888888888888888888888888888888888888888888
 *
 *   this is from an old program, that you should complile the program by
 *
 *   			gcc -o main openmp_temp.c -fopenmp -std=c99
 *
 *
 *88888888888888888888888888888888888888888888888888888888888888888888888888*/





#include <stdio.h>
/*#include <tchar.h>*/
#include <omp.h>

#define OMP_NUM_THREADS 4 // 定义线程数
int main(int argc, char* argv[])
{    
    /*Timer tm;*/
//    omp_set_num_threads(2),设定活动线程数为2
    omp_set_num_threads(3);
//    omp_get_num_procs()
    int procs=omp_get_num_procs();
    printf("There are %d processor(s) available!\n",procs);
//  omp_get_thread_num(),返回当前线程号;
    int Threadid=omp_get_thread_num();
    printf("当前线程号为:%d\n",Threadid);
//    omp_get_num_threads(),返回当前线程总数;
    int Threadnum = omp_get_num_threads();
    printf("当前活动线程数为:%d\n",Threadnum);

// 并行化编译指导语句
    printf("下面开始测试并行化编译指导语句!!\n\n");
// 1.parallel
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp parallel\n\n");

#pragma omp parallel

    printf("This is Thread %d say hello to you!\n",omp_get_thread_num());

// 2.parallel for
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp parallel for\n\n");

#pragma omp parallel for
    for (int i=0;i<4;i++)
    {
        printf("Thread %d is active when i = %d\n",omp_get_thread_num(),i);
    }
    int i,j=0;
// 3.parallel for private
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp parallel for private(j)\n\n");

    printf("使用private子句\n");
#pragma omp parallel for private(j)
    for (i=0;i<2;i++)
        for(j=5;j<7;j++)
            printf("Thread %d is active when i = %d,and j= %d\n",omp_get_thread_num(),i,j);
    printf("不使用private子句\n");
#pragma omp parallel for 
    for (i=0;i<2;i++)
//#pragma omp parallel for
        for(j=5;j<7;j++)
            printf("Thread %d is active when i = %d,and j= %d\n",omp_get_thread_num(),i,j);
// 4.parallel for firstprivate() and lastprivate()
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp parallel for firstprivate and lastprivate\n\n");

    int ai=10;
    int bi=0;
    printf("Before \"parallel for \", ai = 10 ,and bi = 0 !\n\n");
#pragma omp parallel for firstprivate(ai) lastprivate(bi) 
        for (int i=1;i<4;i++)
        {        
            bi=ai;
            ai=0;
        }
    printf("After \"parallel for \" bi equal to %d !\n\n",bi);
    printf("After \"parallel for \" ai still equal to %d !\n\n",ai);
// 5.critical 临界区
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp critical \n\n");

    int n=100000;
    int ver = 0;
    /*tm.start();*/
#pragma omp parallel for 
    for (int i=1;i<=n;i++)
    {
        //for (j=0;j<1000000;j+=2){;}
#pragma omp critical
        ver+=i;
        //printf("Thread %d is active when i = %d\n",omp_get_thread_num(),i);
    }
    printf("ver = %d\n",ver);
    /*tm.stop();*/
    /*printf("%f\n",tm.elapsedSeconds());*/

// 6.reduction(<op>:<variable>)
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp reduction \n\n");
    
    int ver2 = 0;
    /*tm.start();*/
#pragma omp parallel for reduction(+:ver2)
    for(int i=0;i<=n;i++)
    {
        //for (j=0;j<1000000;j+=2){;}
        ver2+=i;
    }

    printf("ver2 = %d\n",ver2);
    /*tm.stop();*/
    /*printf("%f\n",tm.elapsedSeconds());*/

// 7.#pragma omp for
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp for \n\n");
//将内层for循环并行化
#pragma omp parallel 
    for (int i=0;i<2;i++)
    {
#pragma omp for
        for (int j=0;j<2;j++)
        {
            printf("Thread %d is active when i=%d,and j=%d\n",omp_get_thread_num(),i,j);
        }
    }
// 8.threadprivate and copyin
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp threadprivate and copyin \n\n");

    int global=10;
//#pragma omp threadprivate(global)
//#pragma omp parallel
    for (int i=0;i<100;i++)
    {
        global++;
    }

    printf("Global is equal to %d\n",global);


// 9.功能并行#prgama omp parallel sections 
    printf("------------------华丽无比的分隔线--------------------\n");
    printf("#pragma omp parallel sections \n\n");

#pragma omp parallel sections
    {
#pragma omp section
        printf("Section 1 's thread is NO.%d\n",omp_get_thread_num());
#pragma omp section
        printf("Section 2 's thread is NO.%d\n",omp_get_thread_num());
#pragma omp section
        printf("Section 3 's thread is NO.%d\n",omp_get_thread_num());
    }

// 10.同步编译指导语句 
//    1).同步屏障
#pragma omp parallel
    {
        int initialization=0;
#pragma omp barrier
        int process=1;
    }

//    2.互斥锁机制(库函数)
#ifdef LOCKLOCK
#define LOCKLOCK
    omp_lock_t lock;
//普通锁
    omp_init_lock(&lock);
    omp_destroy_lock(&lock);
    omp_set_lock(&lock);
    omp_unset_lock(&lock);
    omp_test_lock(&lock);
//嵌套锁
    omp_init_nest_lock(&lock);
    omp_destroy_nest_lock(&lock);
    omp_set_nest_lock(&lock);
    omp_unset_nest_lock(&lock);
    omp_test_nest_lock(&lock);
#endif
//其他的OpenMP编译指导语句请参考OpenMP手册;



    return 0;
}
