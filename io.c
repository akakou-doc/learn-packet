#include "netutils.h"

/**
 * @brief イーサネットパケットの解析
 * @param (packet) パケットの構造体
 * @param (raw_packet) パケットのバイナリデータを持つ構造体
 */
int AnalyzeEtherPacket(Packet *packet, RawPacket *raw_packet){
    // 残りポインタ
    unsigned char *ptr = raw_packet -> buf;

    // 残りのサイズ
    int lest = raw_packet -> size;

    if(lest < sizeof(struct ether_header)) {
        // デバッグしてデバイスナンバートサイズを表示
        return -1;
    }

    // パケットのポインタをイーサネットに
    // 無理やりキャストして代入
    packet -> eh = (struct ether_header *)ptr;

    // バッファのポインタをコピー
    raw_packet -> buf = ptr;

    // ポインタを読んだ分まで加算
    ptr += sizeof(struct ether_header);

    // 残りサイズを読んだ分減算
    lest -= sizeof(struct ether_header);

    return 0;
}

/**
 * @brief イーサネットパケットの生成
 * @param (raw_packet) パケットのバイナリデータを持つ構造体
 * @param (packet) パケットの構造体
 */
RawPacket *GenerateRawEtherPacket(RawPacket *raw_packet, Packet *packet){
    memcpy(raw_packet -> buf, packet -> eh, raw_packet -> size);

    return raw_packet;
}

