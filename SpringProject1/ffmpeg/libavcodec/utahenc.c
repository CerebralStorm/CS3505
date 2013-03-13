#include "avcodec.h"
#include "internal.h"
#include "bytestream.h"
#include "dsputil.h"
#include "utah.h"

typedef struct UTAHContext {
    AVFrame picture;
} UTAHContext;

static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *pict, int *got_packet)
{
    UTAHContext *s = avctx->priv_data;
    AVFrame *const p = &s->picture;

    int n_bytes_image, n_bytes_per_row, n_bytes, i, ret;
    int hsize;
    uint8_t *ptr, *buf;
    *p = *pict;
    p->pict_type= AV_PICTURE_TYPE_I;
    p->key_frame= 1;

    n_bytes_image = pict->height * pict->width;
    hsize = 9;
    n_bytes = n_bytes_image + hsize;

    if ((ret = ff_alloc_packet2(avctx, pkt, n_bytes)) < 0)
        return ret;
    buf = pkt->data;                
    bytestream_put_byte(&buf, hsize);
    bytestream_put_le32(&buf, avctx->width);        
    bytestream_put_le32(&buf, avctx->height);         

    ptr = p->data[0];
    buf = pkt->data + hsize;
    for(i = 0; i < avctx->height; i++) {
        memcpy(buf, ptr, pict->width);
        buf += pict->width;
        ptr += p->linesize[0];
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}

/*  This method is called when a utah image is encoded */
static av_cold int utah_enc_init(AVCodecContext *avctx){
    UTAHContext *s = avctx->priv_data;

    avcodec_get_frame_defaults(&s->picture);
    avctx->coded_frame = &s->picture;
    avctx->bits_per_coded_sample = 8;

    return 0;
}

AVCodec ff_utah_encoder = {
    .name           = "utah",
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_UTAH,
    .priv_data_size = sizeof(UTAHContext),
    .init           = utah_enc_init,
    .encode2        = encode_frame,
    .pix_fmts       = (const enum AVPixelFormat[]){
        AV_PIX_FMT_RGB8,
        AV_PIX_FMT_NONE
    },
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
};
