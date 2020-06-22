#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){

    char ipv4str[INET_ADDRSTRLEN];
    struct in_addr addr4;

    /*INADDR_LOOPBACKは127.0.0.1を表す0x7f00001*/
    addr4.s_addr = ntohl(INADDR_LOOPBACK);
    inet_ntop(AF_INET,&addr4,ipv4str,sizeof(ipv4str));
    
    printf("%s\n",ipv4str);

    
    return 0;
}