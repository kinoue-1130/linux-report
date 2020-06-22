#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){

    char ipv6str[INET6_ADDRSTRLEN];
    
    /*in6addr_loopbackは::1を表すin6_addr構造体*/
    inet_ntop(AF_INET6,&in6addr_loopback,ipv6str,sizeof(ipv6str));
    
    printf("%s\n",ipv6str);

    
    return 0;
}