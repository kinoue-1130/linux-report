#include <stdio.h>
#include <sys/types.h>

int main(){
    u_int32_t i32 = 0x12345678; //変数i32に0x12345678を代入
    u_int8_t *ch_i32 = (u_int8_t *)&i32; //変数i32のアドレスを8ビットのポインタであるch_i32に代入
    u_int16_t i16 = 0x1234; //変数i16に0x1234を代入
    u_int8_t *ch_i16 = (u_int8_t *)&i16; //変数i16のアドレスを8ビットのポインタであるch_i16に代入

    /*8ビットずつのメモリの配置
    ビッグエンディアンとリトルエンディアンで出力が異なる
    */
    printf("%.2x %.2x %.2x %.2x\n",ch_i32[0],ch_i32[1],ch_i32[2],ch_i32[3]);
    printf("%.2x %.2x\n",ch_i16[0],ch_i16[1]);

    return 1;
}