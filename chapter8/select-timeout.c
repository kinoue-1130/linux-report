#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int sock1,sock2;
    struct sockaddr_in addr1,addr2;
    fd_set fds,readfds;
    char buf[2048];
    int n;
    struct timeval tv;

    /*ファイルディスクリプタの最大値を計算する。selectで使う*/
    int maxfd;

    /*受信ソケットを２つ作成*/
    sock1 = socket(AF_INET,SOCK_DGRAM,0);
    sock2 = socket(AF_INET,SOCK_DGRAM,0);

    addr1.sin_family = AF_INET;
    addr2.sin_family = AF_INET;

    inet_pton(AF_INET,"127.0.0.1",&addr1.sin_addr.s_addr);
    inet_pton(AF_INET,"127.0.0.1",&addr2.sin_addr.s_addr);

    /*２つの別々のポートで待つために別のポート番号をそれぞれ設定*/
    addr1.sin_port = htons(11111);
    addr2.sin_port = htons(22222);

    /*２つの別々のポートで待つようにbindする*/
    bind(sock1,(struct sockaddr *)&addr1, sizeof(addr1));
    bind(sock2,(struct sockaddr *)&addr2, sizeof(addr2));

    /*fd_setの初期化をする*/
    FD_ZERO(&readfds);

    /*selectで待つ読み込みソケットとしてsock1を登録*/
    FD_SET(sock1,&readfds);
    /*selectで待つ読み込みソケットとしてsock2を登録*/
    FD_SET(sock2,&readfds);

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    /*selectで監視するファイルディスクリプタの最大値を計算する*/
    if(sock1>sock2){
        maxfd = sock1;
    }else{
        maxfd = sock2;
    }
    /*
    このサンプルでは、10病患データを受信しないとループを抜ける
    */
   while(1){
       /*読み込み用fd_setの初期化*/
       /*selectが毎回内容を上書きしてしまうので、毎回初期化する*/
       memcpy(&fds,&readfds,sizeof(fd_set));

       /*fdsに設定されたソケットが読み込み可能になるまで待つ*/
       n = select(maxfd+1,&fds,NULL,NULL,&tv);

       /*タイムアウトの場合にselectは0を返す*/
       if(n==0){
           /*ループから抜ける*/
           printf("timeout\n");
           break;
       }
       /*sock1に読み込み可能データがある場合*/
       if(FD_ISSET(sock1,&fds)){
           /*sock1からデータを受信して表示する*/
           memset(buf,0,sizeof(buf));
           recv(sock1,buf,sizeof(buf),0);
            printf("%s\n",buf);
       }
       /*sock2に読み込み可能データがある場合*/
       if(FD_ISSET(sock2,&fds)){
           /*sock2からデータを受信して表示する*/
           memset(buf,0,sizeof(buf));
           recv(sock2,buf,sizeof(buf),0);
            printf("%s\n",buf);
       }       
   }

    /*このサンプルでは、ここへは到達しない*/
    close(sock1);
    close(sock2);
    return 0;
}