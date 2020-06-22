#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(){
    
    char buf[128];
    int n;
    int sock;
    struct sockaddr_un s_un;

    /*UNIXソケットの作成*/
    sock = socket(AF_UNIX,SOCK_STREAM,0);

    if(sock<0){
        perror("socket");
        return 1;
    }

    s_un.sun_family = AF_UNIX;
    strcpy(s_un.sun_path,"/tmp/afunix_test");

    /*
    サーバに接続
    クライアント側のconnect()が呼び出されると、サーバ側のaccept()がUNIXソケットによる新規コネクションを生成し、
    AF_UNIXによる通信が確立する
    */
    if(connect(sock,(struct sockaddr *)&s_un,sizeof(s_un))!=0){
        perror("connect");
        return 1;
    }
    
    printf("after accept\n");


    /*サーバからデータを受信*/
    memset(buf,0,sizeof(buf));
    n = read(sock,buf,sizeof(buf));

    if(n<0){
        perror("read");
        return 1;
    }

    printf("%s\n",buf);

    /*socketの終了*/
    close(sock);

    return 0;
}