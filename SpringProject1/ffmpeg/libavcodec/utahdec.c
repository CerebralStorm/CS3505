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
    //UTAHDecContext * const s = avctx->priv_data;

    return 0;
}

static av_cold int utah_dec_init(AVCodecContext *avctx)
{
    //UTAHDecContext *s = avctx->priv_data;

    return 0;
}

static av_cold int utah_dec_end(AVCodecContext *avctx)
{
    //UTAHDecContext *s = avctx->priv_data;

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
    .capabilities   = NULL,
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
};