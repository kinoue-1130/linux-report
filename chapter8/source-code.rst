================== =============================
ソースコード         内容
================== =============================
epoll-recv.c       epollを使ったデータ受信プログラム
epoll-send.c       epollサンプルへのデータ送信プログラム
buff-over-read.c   送信側バッファが溢れる例：受信プログラム（epoll_waitを利用した送信可能かどうかのチェックの比較として、意図的に送信バッファを溢れさせ、write()がブロックする様子を示すプログラム）
buff-over-write.c  送信側バッファが溢れる例：送信プログラム
send-check.c       epoll_waitを利用した送信可能かどうかのチェック（受信プログラムはbuff-over-read.c）
epoll-timeout.c    epoll_waitを利用したタイムアウトのチェック：受信プログラム（送信プログラムはepoll-send.c）
epoll-connect.c    epoll_waitを利用してconnect()処理を任意のタイミングで終了
epoll-sgusr1.c     シグナルを利用したepoll_waitの解除(シグナルの送信：kill -s SIGUSR1 プログラムのPID)
epoll_socketpair.c socketpairを利用したepoll_waitの解除
select-send.c      UDPを利用したデータ送信プログラム
select-rect.c      UDPを利用したデータ受信プログラム
select-timeout.c   selectを利用したタイムアウトのチェック
poll-send.c　　　　　UDPを利用したデータ送信プログラム
poll-rect.c　　     UDPを利用したデータ受信プログラム
================== =============================

引用
あきみち，”基礎と実装Linuxネットワークプログラミング”，株式会社品の出版，2010，pp.232-267.