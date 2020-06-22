#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>

#define NEVENTS 16

int main(){
    int sock;
    struct sockaddr_in server;
    int epfd;
    struct epoll_event ev,ev_ret[NEVENTS];
    char buf[32];
    int nfds,n;
    int val;

    /*ソケットを作成*/
    sock = socket(AF_INET,SOCK_STREAM,0);

    /*接続先指定用構造体の準備*/
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);

    /*"192.168.0.0"は利用されていないIPアドレス*/
    inet_pton(AF_INET,"192.168.0.0",&server.sin_addr.s_addr);

    /*epoll_create()を利用してepollファイルディスクリプタを作成*/
    epfd = epoll_create(NEVENTS);
    if(epfd<0){
        perror("epoll_create");
        return 1;
    }

    /*epoll_ctl()で準備完了を待つファイルディスクリプタに関する設定を、epollファイルディスクリプタに関連付けている*/
    memset(&ev,0,sizeof(ev));
    ev.events = EPOLLIN;    //関連付けられたファイルに対してread()操作ができる
    ev.data.fd = sock;
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev)!=0){
        perror("epoll_ctl");
        return 1;
    }

    val = 1;
    ioctl(sock,FIONBIO,&val);//ソケットをノンブロッキングに設定→connect()はTCPコネクションが確立していなくてもブロックせずに終了できる

    /*サーバに接続*/
    n = connect(sock,(struct sockaddr *)&server,sizeof(server));
    if(n != 0){
        if(errno == EINPROGRESS){//errnoがEINPROGRESSのとき、ソケットがノンブロッキングなのでconnect()が完了していないにもかかわらず終了したことを示す
            printf("before epoll_wait\n");

            /*タイムアウト付きのepoll_wait()でconnect()の完了を待つ*/
            nfds = epoll_wait(epfd,ev_ret,NEVENTS,1000);
            if(nfds < 0){
                perror("epoll_wait");
                return 1;
            }else if(nfds == 0){//タイムアウト発生
                printf("timeout\n");
                /*socketの終了*/
                close(sock);
                return 1;
            }
            printf("anter epoll_wait : nfds%d\n",nfds);
        }else{
            perror("connect");
            return 1;
        }
    }
    /*サーバからデータを受信*/
    n = read(sock,buf,sizeof(buf));
    write(fileno(stdout),buf,n);

    /*sockの終了*/
    close(sock);
    return 0;
}