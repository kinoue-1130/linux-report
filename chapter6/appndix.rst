システムコール
============

setsockopt()
---------------

::

int setsockopt(
    int sockfd, 
    int level, 
    int optname,
    const void *optval, 
    socklen_t optlen
);

* 成功: 0を返す
* 失敗: −1を返す、失敗の原因はerrnoにセットされる

* 第二引数: levelによって設定
* 第三引数: levelの内容によって変わる、設定値を知るには、ソケットレベルで指定可能なパラメータを知る必要がある

* SOL_SOCKET+SO_SNDTIMEO/SO_RCVTIMEOで設定
    * ソケットをノンブロッキングにしたり、epoll()を利用しなくてもシステムコールをタイムアウトさせることができる
    * 入出力システムコールがタイムアウトに達した場合：-1を返し、errnoにはEAGAINかEWOULBLOCLが設定される

設定内容
^^^^^^^^^^

=========== ================================================= ==================
第二引数      内容                                              第三引数の調べ方
=========== ================================================= ==================
SOL_SOCKET  ソケットバッファサイズなどのソケットそのものに対する設定    man 7 socket
IPPROTO_IP  マルチキャストに関連する設定などIPレベルのものを設定       man 7 ip
IPPROTO_TCP TCPに関する設定                                      man 7 tcp
=========== ================================================= ==================


getsockopt()
---------------

::

int getsockopt(
    int sockfd, 
    int level, 
    int optname,
    void *optval, 
    socklen_t *optlen
);

* 成功: 0を返す
* 失敗: −1を返す、失敗の原因はerrnoにセットされる

getsockname()
---------------

::

int getsockname(
    int sockfd,            /* ソケット */
    struct sockaddr *addr, /* sockaddr構造体へのポインタ */
    socklen_t *addrlen     /* socklen_t構造体へのポインタ */
);

* 第一引数: ソケット
* 第二引数: sockaddr構造体へのポインタ
* 第三引数: 第二引数として渡した構造体のサイズを含むsocklen_t型変数へのポインタ、値はgetsockname()によって書き換えられる

getpeername()
---------------

::

int getpeername(
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen
);


構造体
=========

timeval構造体
------------

struct timeval {
    time_t      tv_sec;     /* 秒 */
    suseconds_t tv_usec;    /* マイクロ秒 */
};

引用
あきみち，”基礎と実装Linuxネットワークプログラミング”，株式会社品の出版，2010，pp.166-186
