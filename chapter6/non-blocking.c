#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

int main(){

    int sock;
    struct sockaddr_in addr;
    
    char buf[2048];
    int val;
    int n;

    sock = socket(AF_INET,SOCK_DGRAM,0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock,(struct sockaddr *)&addr, sizeof(addr));

    /*
    ここで、ノンブロッキングに設定しています。
    val=0でブロッキングモードに設定できます。
    */

    val = 1;
    ioctl(sock,FIONBIO,&val);

    while(1){
        memset(buf,0,sizeof(buf));
        n = recv(sock,buf,sizeof(buf),0);
        if(n<1){
            if(errno == EAGAIN){
                 /*
                 ノンブロッキングモードに設定したソケットでデータがないとき
                 recv()システムコールはエラーを返す
                 errnoの値がEAGAIN
                 */
                printf("MADA KONAI\n");
            }else{
                perror("recv");
                break;
            }
        }else{
            printf("received data\n");
            printf("%s\n",buf);
            break;
        }
        /*とりあえず１秒待ってみる*/
        sleep(1);
    }
    
    close(sock);
    
    return 0;
}