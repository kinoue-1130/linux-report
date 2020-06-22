#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int main(){

    int n;
    int sock;
    struct sockaddr_un addr;
    socklen_t addrlen;

    /*UNIXソケットの作成*/
    sock = socket(AF_UNIX,SOCK_DGRAM,0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,"/tmp/afunix_test");

    n = sendto(sock,"HOGE\n",5,0,(struct sockaddr *)&addr,sizeof(addr));

    printf("send data\n");

    /*socketの終了*/
    close(sock);

    return 0;
}