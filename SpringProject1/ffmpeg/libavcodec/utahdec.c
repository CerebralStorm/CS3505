#include "libavutil/bprint.h"
#include "libavutil/imgutils.h"
#include "avcodec.h"
#include "bytestream.h"
#include "internal.h"
#include "utah.h"

static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    UTAHContext *s  = avctx->priv_data;
    AVFrame *picture   = data;
    AVFrame *p         = &s->picture;
    int width, height;
    unsigned int hsize;
    int i, n, linesize, ret;
    uint8_t *ptr;
    const uint8_t *buf0 = buf;

    hsize  = bytestream_get_byte(&buf); /* header size */
    width = bytestream_get_le32(&buf);
    height = bytestream_get_le32(&buf);

    n = width;
    avctx->width  = width;
    avctx->height = height; /*> 0 ? height : -height;*/
    avctx->pix_fmt = AV_PIX_FMT_RGB24;    

    p->reference = 0;
    if ((ret = ff_get_buffer(avctx, p)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return ret;
    }
    p->pict_type = AV_PICTURE_TYPE_I;
    p->key_frame = 1;
    ptr = p->data[0];
    linesize = p->linesize[0];

    buf = buf0 + hsize;

    for (i = 0; i < avctx->height; i++) {
        memcpy(ptr, buf, n*3);
        buf += n;
        ptr += linesize;
    }

    *picture = s->picture;
    *got_frame = 1;

    return buf_size;
}

static av_cold int utah_dec_init(AVCodecContext *avctx)
{
    UTAHContext *s = avctx->priv_data;

    avcodec_get_frame_defaults(&s->picture);
    avctx->coded_frame = &s->picture;
    avctx->bits_per_coded_sample = 8;

    return 0;
}

static av_cold int utah_dec_end(AVCodecContext *avctx)
{
    UTAHContext *s = avctx->priv_data;
    
    if (s->picture.data[0])
        avctx->release_buffer(avctx, &s->picture);

    return 0;
}

AVCodec ff_utah_decoder = {
    .name           = "utah",
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_UTAH,
    .priv_data_size = 1024,
    .init           = utah_dec_init,
    .close          = utah_dec_end,
    .decode         = decode_frame,
    .capabilities   = CODEC_CAP_DR1,
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
};