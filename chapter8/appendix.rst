システムコール
=============

epoll_create()
--------------------------

::

#include <sys/epoll.h>

int epoll_create(
    int size    /*未使用。ただし０以下の値はNG*/
    );

* 引数をひとつ取るが、この引数は現在利用されていない
* 引数を０以下の値として渡すとEINVALにエラーになる
* 成功した時に０を返し、失敗した時に−１を返す

epoll_ctl()
--------------------------

::

#include <sys/epoll.h>

int epoll_ctl(
    int epfd,                   /*epollファイルディスクリプタ*/
    int op,                     /*fdへの操作*/
    int fd,                     /*操作を設定するファイルディスクリプタ*/
    struct epoll_event *event   /*fdにリンクされたオブジェクト*/
);

* 成功した時は０を返す
* 失敗した時は-1 を返し、 errno を適切に設定する

epoll_wait()
--------------------------

::

#include <sys/epoll.h>

int epoll_wait(
    int epfd,                   /*epollファイルディスクリプタ*/
    struct epoll_event *events, /*結果を格納するepoll_event構造体の配列*/
    int maxevents,              /*引数eventsの配列長*/
    int timeout                 /*タイムアウト（単位はミリ秒）*/
);

* epollファイルディスクリプタepfdに設定されたイベントを待つ
* 引数timeout
    * −１を指定すると利用可能なイベントが発生するまで無限に待ち続け、
    * １以上の値を設定すると最大その時間（ミリ秒）だけ待つ
    * 0を指定するとその場で利用可能なイベントがあるかどうかを判定し、なければ即座にタイムアウトする
* 成功した時に準備ができているファイルディスクリプタの数を返す
* タイムアウトが発生すると０が返る
* 失敗したときは−１が返り、errno変数に失敗内容が設定される

引数
============

* epoll_ctl()の第二引数
`` man 2 epoll_ctl
* epoll_event構造体
    * eventsメンバのイベントタイプ
    * man 2 epoll_ctl


構造体
======

epoll_event構造体
--------------------------

::

typedef union epoll_data {
    void    *ptr;
    int      fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

struct epoll_event {
    uint32_t     events;    /* epoll イベント */
    epoll_data_t data;      /* ユーザーデータ変数 */
};


引用
あきみち，”基礎と実装Linuxネットワークプログラミング”，株式会社品の出版，2010，pp.232-267.