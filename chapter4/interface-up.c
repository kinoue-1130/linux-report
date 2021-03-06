#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

int main(){
    int fd;
    struct ifreq ifr;
    
    fd = socket(AF_INET,SOCK_DGRAM,0);

    /*インターフェースを指定*/
    strncpy(ifr.ifr_name,"host1-veth1",IFNAMSIZ-1);

    /*現在の状態を取得*/
    if(ioctl(fd,SIOCGIFFLAGS,&ifr) != 0){
        perror("ioctl");
        return 1;
    }

    /*現在の状態からIFF_UPとIFF_RUNNINGをONに*/
    ifr.ifr_flags |= IFF_UP | IFF_RUNNING;

    /*状態を変更*/
    if(ioctl(fd,SIOCSIFFLAGS,&ifr) != 0){
        /*失敗したら理由を表示*/
        perror("ioctl");
        return 1;
    }

    close(fd);

    return 0;
}