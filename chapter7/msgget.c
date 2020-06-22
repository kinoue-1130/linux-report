#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    int msgid;

    /*IPC_PRIVATEを利用してメッセージキューを新規作成*/
    msgid = msgget(IPC_PRIVATE,0600);

    if(msgid < 0){
        perror("msgget");
        return 1;
    }

    /*作成されたメッセージキュー識別子の値を表示*/
    printf("%d\n",msgid);

    return 0;
}