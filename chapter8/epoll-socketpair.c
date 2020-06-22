#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h> /*for fork*/

#define NEVENTS 16

int soc[2]; //変数にペアとなる２つのソケットが格納される

void processA(){
    //processAは3秒待ってからソケットペアの片方にデータを書き込む
    sleep(3);

    printf("processA : send message\n");
    write(soc[0],"HOGE",4);

    return;
}

void processB(){
    //processBはソケットペアからの入力がくるとプログラムを終了する
    int epfd;
    struct epoll_event ev,ev_ret[NEVENTS];
    char buf[128];
    int i;
    int nfds;

    /*epoll_create()を利用してepollファイルディスクリプタを作成*/
    epfd = epoll_create(NEVENTS);
    if(epfd<0){
        perror("epoll_create");
        return;
    }

    /*epoll_ctl()で準備完了を待つファイルディスクリプタに関する設定を、epollファイルディスクリプタに関連付けている*/
    memset(&ev,0,sizeof(ev));
    ev.events = EPOLLIN;    //関連付けられたファイルに対してread()操作ができる
    ev.data.fd = soc[1];

    if(epoll_ctl(epfd,EPOLL_CTL_ADD,soc[1],&ev)!=0){
        perror("epoll_ctl");
        return;
    }

    memset(&ev,0,sizeof(ev));
    ev.events = EPOLLIN;    //関連付けられたファイルに対してread()操作ができる
    ev.data.fd = fileno(stdin);
    
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,fileno(stdin),&ev)!=0){
        perror("epoll_ctl");
        return;
    }

    while (1){
        printf("before epoll_wait\n");

        nfds = epoll_wait(epfd,ev_ret,NEVENTS,-1);
        if(nfds<0){
            perror("epoll_wait");
            return;
        }

        printf("after epoll_wait\n");

        for(i=0;i<nfds;i++){
            if(ev_ret[i].data.fd == soc[1]){

                printf("processB: break message from socketpair\n");
                goto outofloop;

            }else if(ev_ret[i].data.fd == fileno(stdin)){
                
                //プログラムを終了するまでの間、processBは標準入力からの入力を受け付けて処理する
                read(fileno(stdin),buf,sizeof(buf));
                printf("processB: input from stdin\n");

            }
        }
    }

outofloop:
    printf("processB: outside of loop\n");

    return;
}

int main(){
    int ret;

    ret = socketpair(AF_UNIX,SOCK_STREAM,0,soc);
    if(ret != 0){
        perror("socketpair");
        return 1;
    }
    if(fork() == 0){
        processA();
    }else{
        processB();
    }

    return 0;
}