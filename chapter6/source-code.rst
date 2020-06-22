================== =============================
ソースコード         内容
================== =============================
non-blocking.c     ノンブロッキングでのUDPを受信
udp-send.c         UDPを送信
16-32.c            16ビットと32ビットの変数がリトルエンディアンやビッグエンディアンでどう扱われるかを見る
byte-order.c       システムのバイトオーダーを知る
so-sndtimeo.c      SO_SNDTIMEOを利用して、存在しないIPアドレスに対してconnect()を行い、connect()をタイムアウトさせる
getsockname.c      getsockname()の第三引数（socklen_t型変数）の変化を見る
inet-addesrtlen.c  INET_ADDESTRLENを利用してIPv4アドレスを格納する文字列を宣言
inet6-addesrtlen.c INET6_ADDESTRLENを利用してIPv4アドレスを格納する文字列を宣言
================== =============================

引用
あきみち，”基礎と実装Linuxネットワークプログラミング”，株式会社品の出版，2010，pp.166-186.