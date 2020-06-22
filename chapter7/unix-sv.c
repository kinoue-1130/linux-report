#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define FILEPATH "/tmp/afunix_test"

int main(){
    int s0,sock;
    struct sockaddr_un s_un;
    struct sockaddr_un s_un_accept;
    socklen_t addrlen;

    /*UNIXソケットの作成*/
    s0 = socket(AF_UNIX,SOCK_STREAM,0);

    if(s0<0){
        perror("socket");
        return 1;
    }

    s_un.sun_family = AF_UNIX;
    strcpy(s_un.sun_path,FILEPATH);

    if(bind(s0,(struct sockaddr *)&s_un, sizeof(s_un)) != 0){
        perror("bind");
        return 1;
    }

    /*クライアントからの接続要求を待てる状態にする*/
    if(listen(s0,5) != 0){
        perror("listen");
        return 1;
    }
    
    addrlen = sizeof(s_un_accept);

    /*
    クライアント側のconnect()が呼び出されると、サーバ側のaccept()がUNIXソケットによる新規コネクションを生成し、
    AF_UNIXによる通信が確立する    
    */

    sock = accept(s0,(struct sockaddr *)&s_un_accept,&addrlen);

    if(sock<0){
        perror("accept");
        return 1;
    }

    printf("after accept\n");

    write(sock,"HOGE",4);

    close(sock);

    close(s0);
    
    /*UNIXソケット用に作成されたファイルを削除*/
    unlink(FILEPATH);

    return 0;
}