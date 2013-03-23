/*
 * UTAH image format
 * Copyright (c) 2013 Cody Tanner / Ben Rogers
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "avcodec.h"
#include "utah.h"
#include "bytestream.h"
#include "internal.h"

static av_cold int utah_encode_init(AVCodecContext *avctx)
{
    UTAHContext *context = avctx->priv_data;
    avcodec_get_frame_defaults(&context->picture);
    avctx->coded_frame = &context->picture;

    return 0;
}

static int utah_encode_frame(AVCodecContext *avctx, AVPacket *pkt,const AVFrame *pict, int *got_packet)
{
    UTAHContext *context = avctx->priv_data;
    AVFrame * const pic = &context->picture;
    *pic = *pict;
    pic->pict_type = AV_PICTURE_TYPE_I;
    pic->key_frame = 1;      
    uint8_t *frame_data, *pkt_data;
    int ret;
    int hsize = 14;

    if(ret = (ff_alloc_packet2(avctx, pkt, (hsize + avctx->height * pic->linesize[0]))) < 0)
    {
        return ret;  
    }      	

    pkt_data = pkt->data;

    bytestream_put_byte(&pkt_data, 'U');
    bytestream_put_byte(&pkt_data, 'T');
    bytestream_put_le32(&pkt_data, avctx->height);
    bytestream_put_le32(&pkt_data, avctx->width);
    bytestream_put_le32(&pkt_data, pic->linesize[0]);

    frame_data = pic->data[0];
    pkt_data = pkt->data+hsize;

    for(int row = 0; row<avctx->height;row++)
      {
        memcpy(pkt_data, frame_data, pic->linesize[0]);
        pkt_data+=pic->linesize[0];
        frame_data+=pic->linesize[0];
      }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    
    return 0;
}

AVCodec ff_utah_encoder = 
  {
	.name           = "utah",
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_UTAH,
    .priv_data_size = sizeof(UTAHContext),
    .init           = utah_encode_init,
    .encode2        = utah_encode_frame,
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
    .pix_fmts       = (const enum AVPixelFormat[]){
        AV_PIX_FMT_RGB8, AV_PIX_FMT_RGB24,
        AV_PIX_FMT_NONE
    },
  };
