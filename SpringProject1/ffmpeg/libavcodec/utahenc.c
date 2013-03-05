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

    return 0;
}

static av_cold int utah_enc_init(AVCodecContext *avctx){
    UTAHEncContext *s = avctx->priv_data;

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
    .pix_fmts       = AV_PIX_FMT_RGB24,
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
};
