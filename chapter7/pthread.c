#include <stdio.h>
#include <pthread.h>

/*スレッドが同じ仮想アドレス空間を共有しているため、
各スレッド内部での変数を扱うと同時にglobal_valという整数の変数の値を少しずつ大きくできる*/
int global_val = 0;

void *
thread_start_routine(void *data){
    int val = (int)data;
    int i;

    printf("thread_start_routine : val=%d\n",val);

    for(i=0;i<10;i++){
        global_val++;
        printf("thread_start_routine : i=%d,g=%d\n",i,global_val);
        sleep(1);
    }
    return NULL;
}

int main(){
    int i;
    pthread_t th;
    void *th_ret;

    /*
    pthread_create()を行うことで、thread_start_routine()という自作関数を中心とした新規スレッドが作成される
    pthread_create()によって開始されたthread_start_routine()が実行されていくのと並行して、main()関数内での動作も実行されていく
    */

    if(pthread_create(&th,NULL,thread_start_routine,(void *)100) != 0){
        perror("pthread_create");
        return 1;
    }

    for(i=0;i<10;i++){
        global_val++;
        printf("main : i=%d,g=%d\n",i,global_val);
        sleep(1);
    }

    /*
    pthread_join()は、pthread_create()によって生成されたスレッドの終了を検知すると、スレッドの資源解放を行う
    */
    if(pthread_join(th,&th_ret) != 0){
        perror("pthread_join");
        return 1;
    }
    return 0;
}