#include "avcodec.h"
#include "internal.h"
#include "bytestream.h"
#include "dsputil.h"
#include "utah.h"

typedef struct UTAHEncContext {
    DSPContext dsp;

    uint8_t *bytestream;
    uint8_t *bytestream_start;
    uint8_t *bytestream_end;
    AVFrame picture;

} UTAHEncContext;

static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *pict, int *got_packet)
{
    UTAHEncContext *s = avctx->priv_data;
    AVFrame *const p = &s->picture;

    int n_bytes_image, n_bytes_per_row, n_bytes, i, ret;
    int bit_count = avctx->bits_per_coded_sample;
    int hsize, pad_bytes_per_row;
    uint8_t *ptr, *buf;
    *p = *pict;
    p->pict_type= AV_PICTURE_TYPE_I;
    p->key_frame= 1;

    n_bytes_per_row = ((int64_t)avctx->width * (int64_t)bit_count + 7LL) >> 3LL;
    pad_bytes_per_row = (4 - n_bytes_per_row) & 3;
    n_bytes_image = avctx->height * (n_bytes_per_row + pad_bytes_per_row);

    hsize = 10;
    n_bytes = n_bytes_image + hsize;
    if ((ret = ff_alloc_packet2(avctx, pkt, n_bytes)) < 0)
        return ret;
    buf = pkt->data;
    bytestream_put_byte(&buf, 'U');                   // BITMAPFILEHEADER.bfType
    bytestream_put_byte(&buf, 'T');                   // do.
    bytestream_put_le32(&buf, avctx->width);          // BITMAPINFOHEADER.biWidth
    bytestream_put_le32(&buf, avctx->height);         // BITMAPINFOHEADER.biHeight

    // Utah files are bottom-to-top so we start from the end...
    ptr = p->data[0] + (avctx->height - 1) * p->linesize[0];
    buf = pkt->data + hsize;
    for(i = 0; i < avctx->height; i++) {
        memcpy(buf, ptr, n_bytes_per_row);
        buf += n_bytes_per_row;
        memset(buf, 0, pad_bytes_per_row);
        buf += pad_bytes_per_row;
        ptr -= p->linesize[0]; // ... and go back
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}

/*  This method is called when a utah image is encoded,
    It ensures that an image file isn't to many lines of
    resolution and that there is enough memory to handle
    the size of the image */
static av_cold int utah_enc_init(AVCodecContext *avctx){
    UTAHEncContext *s = avctx->priv_data;

    avcodec_get_frame_defaults(&s->picture);
    avctx->coded_frame = &s->picture;
    avctx->bits_per_coded_sample = 8;

    return 0;
}

AVCodec ff_utah_encoder = {
    .name           = "utah",
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_UTAH,
    .priv_data_size = sizeof(UTAHEncContext),
    .init           = utah_enc_init,
    .encode2        = encode_frame,
    .capabilities   = NULL,
    .pix_fmts       = (const enum AVPixelFormat[]){
        AV_PIX_FMT_RGB8,
        AV_PIX_FMT_NONE
    },
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
};
