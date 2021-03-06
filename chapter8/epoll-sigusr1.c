#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <signal.h>
#include <errno.h>

#define NEVENTS 16

void sigusr1_handler(int sig){
    write(fileno(stdout),"signal called\n",14);
}

int  main(){
    int nfds;
    int epfd;

    /*SIGUSR1のシグナルハンドラを設定*/
    signal(SIGUSR1,sigusr1_handler);

    /*epoll_create()を利用してepollファイルディスクリプタを作成*/
    epfd = epoll_create(NEVENTS);
    if(epfd<0){
        perror("epoll_create");
        return 1;
    }

    printf("before epoll_wait\n");

    /*SIGUSR１が来るまでepoll_waitはblockし続ける*/
    nfds = epoll_wait(epfd,NULL,NEVENTS,-1);
    printf("after epoll_wait : %d\n",nfds);

    /*errnoがEINTRになっているのを確認*/
    printf("%d\n",errno);
    perror("perror after epoll_wait");

    return 0;
}
