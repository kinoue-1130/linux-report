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
    struct sockaddr_in *s_in;
    
    fd = socket(AF_INET,SOCK_DGRAM,0);

    /*新しいIPv4アドレスの値や設定を反映させたいインターフェース名をifreq構造体iftに設定*/
    s_in = (struct sockaddr_in *)&ifr.ifr_addr;

    /*IPv4*/
    s_in->sin_family = AF_INET;
    /*変更するIPアドレス*/
    s_in->sin_addr.s_addr = inet_addr("10.0.0.2");

    /*IPアドレスを変更するインターフェースを指定*/
    strncpy(ifr.ifr_name,"host1-veth1",IFNAMSIZ-1);

    /*IPアドレスを変更*/
    if(ioctl(fd,SIOCSIFADDR,&ifr) != 0){
        /*失敗したら理由を表示*/
        perror("ioctl");
    }

    close(fd);

    return 0;
}