#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define NEVENTS 16

int main(){
    int sock1,sock2;
    struct sockaddr_in addr1,addr2;
    int epfd;
    struct epoll_event ev,ev_ret[NEVENTS];
    char buf[2048];
    int i;
    int nfds;
    int n;

    /*受信ソケットを２つ作成*/
    sock1 = socket(AF_INET,SOCK_DGRAM,0);
    sock2 = socket(AF_INET,SOCK_DGRAM,0);
    addr1.sin_family = AF_INET;
    addr2.sin_family = AF_INET;

    /*"127.0.0.1"の部分は必要に応じて変更*/
    inet_pton(AF_INET,"127.0.0.1",&addr1.sin_addr.s_addr);
    inet_pton(AF_INET,"127.0.0.1",&addr2.sin_addr.s_addr);

    /*２つの別々のポートで待つために別のポート番号をそれぞれ設定*/
    addr1.sin_port = htons(11111);
    addr2.sin_port = htons(22222);

    /*２つの別々のポートで待つようにbindする*/
    bind(sock1,(struct sockaddr *)&addr1, sizeof(addr1));
    bind(sock2,(struct sockaddr *)&addr2, sizeof(addr2));

    /*epoll_create()を利用してepollファイルディスクリプタを作成*/
    epfd = epoll_create(NEVENTS);
    if(epfd<0){
        perror("epoll_create");
        return 1;
    }

    /*epoll_ctl()で準備完了を待つファイルディスクリプタに関する設定を、epollファイルディスクリプタに関連付けている*/
    memset(&ev,0,sizeof(ev));
    ev.events = EPOLLIN;    //関連付けられたファイルに対してread()操作ができる
    ev.data.fd = sock1;
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock1,&ev)!=0){
        perror("epoll_ctl");
        return 1;
    }

    memset(&ev,0,sizeof(ev));
    ev.events = EPOLLIN;    //関連付けられたファイルに対してread()操作ができる
    ev.data.fd = sock2;
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock2,&ev)!=0){
        perror("epoll_ctl");
        return 1;
    }

/*
このサンプルでは、１０秒間データを受信しないとループを抜ける
*/
    while(1){
        printf("before epoll_wait()\n");

        /*epoll_wait()の第４引数に「10*1000」を渡している*/
        nfds = epoll_wait(epfd,ev_ret,NEVENTS,10*1000);
        if(nfds <= 0){
            perror("epoll_wait");
            return 1;
        }
        printf("after epoll_wait\n");

        /*タイム嘔吐の場合にはepoll_wait()は０を返す*/
        if(nfds == 0){
            /*ループから抜ける*/
            printf("timeout\n");
            return 1;
        }

        for(i=0;i<nfds;i++){
            if(ev_ret[i].data.fd == sock1){

                /*sock1に読み込み可能データがある場合*/
                /*sock1からデータを受信して表示*/
                n = recv(sock1,buf,sizeof(buf),0);
                write(fileno(stdout),buf,n);

            }else if(ev_ret[i].data.fd == sock2){

                /*sock2に読み込み可能データがある場合*/
                /*sock2からデータを受信して表示*/
                n = recv(sock2,buf,sizeof(buf),0);
                write(fileno(stdout),buf,n);
  
            }
        }
    }

    close(sock1);
    close(sock2);
    return 0;
}