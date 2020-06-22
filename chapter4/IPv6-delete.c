#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

struct in6_ifreq{
    struct in6_addr ifr6_addr;
    u_int32_t ifr6_prefixlen;
    int ifr6_ifindex;
};

int main(){
    int fd;
    struct in6_ifreq ifr;
    char buf[256];
    int n;
    
    fd = socket(AF_INET6,SOCK_DGRAM,0);

    /*追加するIPv6アドレスに関する情報を設定*/
    memset(&ifr,0,sizeof(ifr));
    inet_pton(AF_INET6,"2003::1",&ifr.ifr6_addr);
    ifr.ifr6_prefixlen = 64;

    /*eth0のIPv6アドレスを削除したい*/
    ifr.ifr6_ifindex = if_nametoindex("eth0");

    /*ioctl()をSIOCDIFADDRで実行*/
    n = ioctl(fd,SIOCDIFADDR,&ifr);
    if(n < 0){
        perror("ioctl");
        return 1;
    }

    close(fd);

    return 0;
}