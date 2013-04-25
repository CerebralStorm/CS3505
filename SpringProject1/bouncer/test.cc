/*  
 * Bouncer Application
 * Copyright (c) 2013 Cody Tanner / Ben Rogers
 *
 * This file uses FFmpeg to draw a bouncing ball on top of an image provided via the command line.
 *
 */

#include <iostream>
#include <math.h>

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{

#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"

}

using namespace std;

// Draw a single pixel on image frame
void drawPixel(int x, int y, int r, int g, int b, AVFrame *f) {
  uint8_t *pix = f->data[0] + f->linesize[0] * y + x * 3;
  *(pix++) = r;
  *(pix++) = g;
  *(pix++) = b;
}

// Draw a circle and shade it
void drawCircle(int cx, int cy, int rad, AVFrame *f) {
  int x, y, cirX, cirY;
  int i;

  for(x = cx-rad; x < cx+rad; x++) {
    for(y = cy-rad; y < cy+rad; y++) {
      cirX = x - cx;
      cirY = y - cy;
      if (((cirX*cirX)+(cirY*cirY))<(rad*rad)) {
        drawPixel(x, y, 255-i, 255-i, 255-i, f);
      }
    }
    i += 1;
  }     
}

int main(int argc, char *argv[]) {
  AVFormatContext *pFormatCtx = NULL;
  int              videoStream;
  AVCodecContext  *pCodecCtx = NULL;
  AVCodec         *pCodec = NULL;
  AVCodec         *utahCodec = NULL;
  AVFrame         *pFrame = NULL; 
  AVFrame         *pFrameRGB = NULL;
  AVPacket        packet;
  AVPacket        utahPacket;
  int             gotPacket = 0;
  int             frameFinished;
  int             numBytes;
  uint8_t         *buffer = NULL;
  uint8_t         *buffer2 = NULL;

  AVDictionary    *optionsDict = NULL;
  struct SwsContext      *sws_ctx = NULL;
  
  // ensure command line argument for image
  if(argc < 2) {
    printf("Please provide an jpeg file\n");
    return -1;
  }
  // Register all formats and codecs
  av_register_all();
  avcodec_register_all();
  
  // Open video file
  if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL)!=0)
    return -1; // Couldn't open file
  
  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, NULL)<0)
    return -1; // Couldn't find stream information
  
  // Get a pointer to the codec context for the video stream
  pCodecCtx=pFormatCtx->streams[0]->codec;
  
  // Find the decoder for the video stream
  pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec==NULL) {
    fprintf(stderr, "Unsupported codec!\n");
    return -1; // Codec not found
  }
  // Open codec
  if(avcodec_open2(pCodecCtx, pCodec, NULL)<0)
    return -1; // Could not open codec
  
  // Allocate video frame
  pFrame = avcodec_alloc_frame();
  
  // Allocate an AVFrame structure
  pFrameRGB = avcodec_alloc_frame();
  if(pFrameRGB==NULL)
    return -1;
  
  // Determine required buffer size and allocate buffer
  numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
  buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));

  sws_ctx = sws_getContext(
        pCodecCtx->width,
        pCodecCtx->height,
        pCodecCtx->pix_fmt,
        pCodecCtx->width,
        pCodecCtx->height,
        PIX_FMT_RGB24,
        SWS_BILINEAR,
        NULL,
        NULL,
        NULL
    );
  
  // Assign appropriate parts of buffer to image planes in pFrameRGB
  avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
  
  // Read frames and save first five frames to disk
  if(av_read_frame(pFormatCtx, &packet)>=0) {

    // Decode video frame
    avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
      
    // Did we get a video frame?
    if(frameFinished) {
      // Convert the image from its native format to RGB
      sws_scale(
          sws_ctx,
          (uint8_t const * const *)pFrame->data,
          pFrame->linesize,
          0,
          pCodecCtx->height,
          pFrameRGB->data,
          pFrameRGB->linesize
      );             
    }

    int height = pCodecCtx->height;
    int width = pCodecCtx->width;
    int rad = width/8;
    cout << "Height: " << height << endl;
    cout << "Width: " << width << endl;
    int cirX = height/2+rad;
    int cirY = height/2;
    int dir = 0;
    int velocity = 8;    
    

    AVFrame * tempFrame;
    for(int i = 0; i < 300; i++) {
      // Allocate an AVFrame structure
      tempFrame = avcodec_alloc_frame();
      
      // Determine required buffer size and allocate buffer
      numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
      buffer = (uint8_t *) av_malloc(numBytes*sizeof(uint8_t));

      sws_ctx = sws_getContext(
        pCodecCtx->width,
        pCodecCtx->height,
        PIX_FMT_RGB24,
        pCodecCtx->width,
        pCodecCtx->height,
        PIX_FMT_RGB24,
        SWS_BILINEAR,
        NULL,
        NULL,
        NULL
      );     

      // Assign appropriate parts of buffer to image planes in tempFrame
      avpicture_fill((AVPicture *)tempFrame, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
      
      sws_scale(sws_ctx,pFrameRGB->data,pFrameRGB->linesize,0,pCodecCtx->height,tempFrame->data,tempFrame->linesize);
      sws_freeContext(sws_ctx);

      drawCircle(cirX, cirY, rad, tempFrame);

      // Simple Collision detection to make the ball bounce on the screen
      if(dir == 0)
        cirY += (int) velocity;
      if(dir == 1)
        cirY -= (int) velocity;

      if(cirY+rad+velocity+1 > height)
        dir = 1;
      if(cirY-rad-velocity-1 < 0)
        dir = 0;

      utahPacket.size = 0;
      utahPacket.data = NULL;
      utahCodec = avcodec_find_encoder(AV_CODEC_ID_UTAH);
      pCodecCtx->codec = utahCodec;
      avcodec_encode_video2(pCodecCtx, &utahPacket, tempFrame, &gotPacket);

      // save the file in the format frame000.utah
      char filename[32];
      FILE *pFile;
      snprintf(filename, sizeof(filename), "frame%03d.utah", i);
      pFile = fopen(filename, "wb");
      fwrite(utahPacket.data, 1, utahPacket.size, pFile);
      fclose(pFile);
      
      // free up the temp frame
      //av_free(tempFrame);
    }      
  }
    
  // Free the packet that was allocated by av_read_frame
  av_free_packet(&packet);
  
  // Free the RGB image
  av_free(buffer);
  av_free(pFrameRGB);
  
  // Free the YUV frame
  av_free(pFrame);
  
  // Close the codec
  avcodec_close(pCodecCtx);
  
  // Close the video file
  avformat_close_input(&pFormatCtx);
  
  return 0;
}
