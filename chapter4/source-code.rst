================= =============================
ソースコード        内容
================= =============================
if-nametoindex.c  if_nametoindex()を利用してインターフェース番号とインターフェース名を取得する
getifaddrs.c      getifaddrs()を利用してインターフェース一覧を取得する
if_nameindex.c    if_nameindex()を利用してインターフェース一覧のみを取得する
ioctl.c           ioctl()を利用してインターフェース一覧のみを取得する
hardware-get.c    ioctl()を利用してハードウェアアドレスを取得する
hardware-set.c    ioctl()を利用してハードウェアアドレスを設定する
IPv4-set.c        ioctl()を利用してIPv4アドレスを設定する
IPv6-set.c        ioctl()を利用してIPv6アドレスを設定する
IPv6-delete.c     ioctl()を利用してIPv6アドレスを削除する
netmask-set.c     ioctl()を利用してネットマスクを変更する
interface-down.c  ioctl()を利用してインターフェースをdown状態にする
interface-up      ioctl()を利用してインターフェースをup状態にする
mtu-get.c         ioctl()を利用してMTUを取得する
================= =============================

引用
あきみち，”基礎と実装Linuxネットワークプログラミング”，株式会社品の出版，2010，pp.102-126.