#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main(){

    int n,sock;
    struct sockaddr_un addr;
    socklen_t addrlen;
    char buf[2048];

    /*UNIXソケットの作成*/
    sock = socket(AF_UNIX,SOCK_DGRAM,0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,"/tmp/afunix_test");

    bind(sock,(struct sockaddr *)&addr, sizeof(addr));

    while(1){
        memset(buf,0,sizeof(buf));
        n = recv(sock,buf,sizeof(buf)-1,0);
        printf("recv : %s\n",buf);
    }
    close(sock);

    return 0;
}