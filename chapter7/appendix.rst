システムコール
==============

fork()
-------

::

#include <unistd.h>

pid_t fork(void);

* 親プロセスで側では、子プロセスのプロセスID が返り、子プロセス側では、0が返る

getpid()
----------

::

#include <unistd.h>
#include <sts/types.h>

pid_t getpid(void);


signal()
---------------------

::

#include <signal.h>

typedef void (*sighandler_t)(int);

sighandler_t signal(
    int signum, /* シグナル番号 */
    sighandler_t sighandler/* シグナルハンドラ */
);

socketpair()
---------------------

::

#include <sys/types.h> 
#include <sys/socket.h>

int socketpair(
    int domain, 
    int type, 
    int protocol, 
    int sv[2]
);   

* 第一引数は必ずAF_UNIX（AF_LOCAL）

pipe()
---------------------

::

#include <unistd.h>

int pipe(int pipefd[2]);

* 配列[pipefd]にパイプの両端を参照するファイルディスクリプタを返す
* 引数として渡す配列の１つ目の要素が読み出し側になり、２つ目の要素が書き込み側になる
* 返り値は、成功すると０、失敗すると−１になりerrnoに内容が設定される

ftok()
---------------------

::

#include <sys/types.h>
#include <sys/ipc.h>

key_t ftok(
    const char *pathname, 
    int proj_id
);   

* 存在するファイルパスと第二引数のproj_idの下位８ビットを利用してIPCキーを生成する

shmget() 
---------------------

::

#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(
    key_t key, 
    size_t size, 
    int shmflg
);   

* 第一引数: keyはIPCキー

* IPCキーを元にセグメント識別子を返す

shmat()/shdt() 
---------------------------------------

::

#include <sys/types.h>
#include <sys/shm.h>

void *shmat(
    int shmid, 
    const void *shmaddr, 
    int shmflg
);

int shmdt(
    const void *shmaddr
);

* shmat()
    * shmid で指定された System V 共有メモリーセグメント (shared memory segment) を コールしたプロセスのアドレス空間に付加 (attach) する
* shmdt()
    * 呼び出したプロセスのアドレス空間から shmaddr で指定されたアドレスに配置された共有メモリーセグメントを分離 (detach) する


shmctl() 
---------------------

#include <sys/ipc.h>
#include <sys/shm.h>

int shmctl(
    int shmid, 
    int cmd, 
    struct shmid_ds *buf
);

* 第一引数: セグメント識別子
* 第二引数: shmctl()による制御の種類を示すコマンド
* 第三引数: 共有メモリに関する情報を格納するshmid_ds構造体（構造体->shmid_ds構造体）

semget() 
---------------------

::

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(
    key_t key, 
    int nsems, 
    int semflg
); 

* 第一引数: keyはIPCキー
* 第二引数: nsemsは、新しく作成されるセマフォセットに含まれるセマフォの数を指定するために利用
* 第三引数: すでに　keyと一致するセマフォ識別子が存在すると、errnoにEEXISTがセットされる

* IPCキーを元にセマフォ識別子を返す
* keyにIPC_PRAIVATEを指定すると、新しいセマフォ識別子を作成する
* keyと一致する既存のセマフォ識別子が存在せず、semflgがIPC_CREATの場合、新しくセマフォ識別子が作成される

semctl() 
---------------------


::

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semctl(
    int semid, 
    int semnum, 
    int cmd, ::.
);

semop() 
---------------------

::

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semop(
    int semid, 
    struct sembuf *sops, 
    size_t nsops
);

* 第二引数: sopsはsembuf構造体の配列、配列の長さはnsopsで指定

msgget() 
---------------------

::

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget(
    key_t key, 
    int msgflg
);

msgctl() 
---------------------

::

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgctl(
    int msqid, 
    int cmd, 
    struct msqid_ds *buf);


構造体
========

shmid_ds構造体
------------

struct shmid_ds {
    struct ipc_perm shm_perm;    /* 所有権と許可 */
    size_t          shm_segsz;   /* セグメントのサイズ (バイト) */
    time_t          shm_atime;   /* 最後の付加 (attach) の時刻 */
    time_t          shm_dtime;   /* 最後の分離 (detach) の時刻 */
    time_t          shm_ctime;   /* 最後に変更が行われた時刻 */
    pid_t           shm_cpid;    /* 作成者 (creator) の PID */
    pid_t           shm_lpid;    /* 最後の shmat(2)/shmdt(2) の PID */
    shmatt_t        shm_nattch;  /* 現在付加されている数 */
    ...
};

sembuf構造体
------------

::

struct{
    unsigned short sem_num;  /* セマフォ番号 */
    short          sem_num;   /* セマフォ操作 */
    short          sem_flg;  /* 操作フラグ */
}

* sem_num: セマフォセットの中で操作を行うセマフォ番号を指定する
* sem_op: 操作そのものを指定。sem_opに１を設定すると、指定したセマフォの値に１加算され、−１を指定すると１減産される。sem_opが０の場合は、セマフォの値が０になるまで待つことを意味する。
* sem_flg: IPC_NOWAITとSEM_UNDOが設定できる。IPC_NOWAITが指定された場合、sem_opはブロックせずにエラーで返り、errnoはEAGAINになるが、sopsに記述された操作は全て実行されない。SEM_UNDOが指定された操作は、そのプロセスが終了した時に自動的に取り消される
