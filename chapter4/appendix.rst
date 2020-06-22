関数一覧
=======

if_nametoindex()関数
------------------------

::

unsigned int if_nametoindex(
    const char *ifname /*インターフェース名*/
);

* 関数が失敗：戻り値として０が返り、エラー内容はerrnoに設定される
* 指定したインターフェース名が存在しない場合：errnoにENODEVが設定される
* その他のシステムエラーが発生した場合：エラー番号がerrnoに設定される
* ソケット作成に失敗するとENOBUFSやENFILEなどが発生する可能性がある

if_indextoname()関数
------------------------

::

char *if_indextoname(
    unsigned int ifindex,   /*インデックス名/
    char *ifname            /*インターフェース名のポインタ*/
);

* 引数ifnameのサイズがIF_NAMESIZE以上でなければならない
* 関数が成功：引数ifnameのポインタが戻り地として返る
* 関数が失敗：戻り値としてNULLが返り、この時のエラー内容はerrnoに設定される
* 指定したインデックス番号が存在しない場合：errnoにENXIOが設定される
* その他のシステムエラーが発生した場合：エラー番号がerrnoに設定される
* ソケット作成に失敗するとENOBUFSやENFILEなどが発生する可能性がある

getifaddrs()関数
------------------------

::

int getifaddrs(
    struct ifaddrs **ifap   /*ifaddrs構造体*/
);

* getifaddrs()関数で取得したifaddrs構造体はfreeifaddrs()関数を利用して開放する必要がある(構造体->ifaddrs構造体)


freeifaddrs()関数
------------------------

::

void freeifaddrs(struct ifaddrs *ifa);


ioctl()関数
------------

::

int ioctl(
    int fd,
    unsigned long request,
    ...
);

* 第１引数:オープンされたファイルディスクリプタ
* 第２引数:デバイス依存のリクエストコード
* 第３引数:メモリへの型を指定しないポインタ

================ ========================================================= 
リクエストコード    内容   
================ =========================================================
SIOCGFCONF       インターフェースの (トランスポート層の) アドレスのリストを返す
SIOCSIFNAME      ifr_name で指定したインターフェースの名前を ifr_newname に変更する
SIOCGIFHWADDR    デバイスのハードウェアアドレスを ifr_hwaddr を用いて取得する
SIOCSIFHWADDR    デバイスのハードウェアアドレスを ifr_hwaddr を用いて設定する
SIOCSIFADDR      ifr_addr を用いてデバイスのアドレスの取得を行う
SIOCSIFNETMASK   デバイスのネットワークマスクを ifr_netmask を用いて取得する
SIOCGIFFLAGS     デバイスの active フラグワードを取得する
SIOCSIFFLAGS     デバイスの active フラグワードを設定する
SIOCGIFMTU       デバイスのメトリックを ifr_metric を用いて取得する
SIOCSIFMTU       デバイスのメトリックを ifr_metric を用いて設定する  
================ =========================================================

構造体
======

ifaddrs構造体
------------
::

struct ifaddrs {
    struct ifaddrs  *ifa_next;    /* Next item in list */
    char            *ifa_name;    /* Name of interface */
    unsigned int     ifa_flags;   /* Flags from SIOCGIFFLAGS */
    struct sockaddr *ifa_addr;    /* Address of interface */
    struct sockaddr *ifa_netmask; /* Netmask of interface */
    union {
        struct sockaddr *ifu_broadaddr;
                        /* Broadcast address of interface */
        struct sockaddr *ifu_dstaddr;
                        /* Point-to-point destination address */
    } ifa_ifu;
#define              ifa_broadaddr ifa_ifu.ifu_broadaddr
#define              ifa_dstaddr   ifa_ifu.ifu_dstaddr
    void            *ifa_data;    /* Address-specific data */
};

