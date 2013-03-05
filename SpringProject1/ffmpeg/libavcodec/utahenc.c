#include "avcodec.h"
#include "internal.h"
#include "bytestream.h"
#include "dsputil.h"
#include "utah.h"

static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *pict, int *got_packet)
{
    //UTAHContext *s = avctx->priv_data;

    return 0;
}

static av_cold int utah_enc_init(AVCodecContext *avctx){
    //UTAHEncContext *s = avctx->priv_data;

    return 0;
}

AVCodec ff_utah_encoder = {
    .name           = "utah",
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_UTAH,
    .priv_data_size = 1024,
    .init           = utah_enc_init,
    .encode2        = encode_frame,
    .capabilities   = NULL,
    .pix_fmts       = NULL,
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
};
