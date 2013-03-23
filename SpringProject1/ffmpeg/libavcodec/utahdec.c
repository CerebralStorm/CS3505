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
 
#include "bytestream.h"
#include "avcodec.h"
#include "internal.h"
#include "utah.h"

static av_cold int utah_decode_init(AVCodecContext *avctx)
{
    UTAHContext *context = avctx->priv_data;
    avcodec_get_frame_defaults(&context->picture);
    avctx->coded_frame = &context->picture;

    return 0;
}

static int utah_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)
{
    UTAHContext *context = avctx->priv_data;
    const uint8_t *buffer = avpkt->data;
    uint8_t* pic_buffer;
    int buffer_size = avpkt->size;
    int height = 0;
    int width = 0;
    int ret;
    int hsize = 14;
    int line = 0;
    int n_bytes = 0;
    AVFrame *picture = data;
    AVFrame *pic = &context->picture;
    avctx->pix_fmt = AV_PIX_FMT_RGB24;

    if(buffer_size < hsize)
    {
        av_log(avctx, AV_LOG_ERROR, "Image is not a .utah image(invalid hsize size)\n");
        return AVERROR_INVALIDDATA;
    }

    if(bytestream_get_byte(&buffer) != 'U' || bytestream_get_byte(&buffer)!='T')
    {
        av_log(avctx, AV_LOG_ERROR, "Invalid .utah image\n");
        return AVERROR_INVALIDDATA;
    }

    height = bytestream_get_le32(&buffer);// Get the height from the packet buffer
    width = bytestream_get_le32(&buffer);// get the width from the packet buffer
    avctx->height = height;

    line = bytestream_get_le32(&buffer);
    avctx->width =width;

    n_bytes = height*line + hsize; 
    if(n_bytes != buffer_size)
    {
        av_log(avctx, AV_LOG_ERROR, "Invalid image size");
        return AVERROR_INVALIDDATA;
    }

    if (pic->data[0])
    {
        avctx->release_buffer(avctx, pic);
    }

    pic->reference = 0;
    if ((ret = ff_get_buffer(avctx, pic)) < 0) {
          return ret;
      }

    memset(pic->data[0], 0, height*pic->linesize[0]);
    pic_buffer = pic->data[0];

    for(int row = 0; row<fheight;row++)
    {
    	memcpy(pic_buffer, buffer, line);
    	pic_buffer += pic->linesize[0];
    	buffer += line;
    }

    *picture = context->picture;
    *got_frame = 1;

    return buffer_size;
}

static av_cold int utah_decode_end(AVCodecContext *avctx)
{
    UTAHContext* context = avctx->priv_data;
    if (context->picture.data[0])
    {
        avctx->release_buffer(avctx, &context->picture);
    }
    
    return 0;
}

AVCodec ff_utah_decoder = 
{
    .id = AV_CODEC_ID_UTAH,
    .type = AVMEDIA_TYPE_VIDEO,
    .name = "utah",
    .priv_data_size = sizeof(UTAHContext),
    .init = utah_decode_init,
    .close = utah_decode_end,
    .decode = utah_decode_frame,
    .capabilities = CODEC_CAP_DR1,
    .long_name = NULL_IF_CONFIG_SMALL("UTAH (Built for CS 3505 in U of U) image"),
};
