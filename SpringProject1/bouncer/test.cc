#include <iostream>

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

int main(int argc, char *argv[]) {
  AVFormatContext *pFormatCtx = NULL;
  int             i, videoStream;
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

  AVDictionary    *optionsDict = NULL;
  struct SwsContext      *sws_ctx = NULL;
  
  if(argc < 2) {
    printf("Please provide a movie file\n");
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
  
  // Dump information about file onto standard error
  av_dump_format(pFormatCtx, 0, argv[1], 0);
  
  // Find the first video stream
  videoStream=-1;
  for(i=0; i<pFormatCtx->nb_streams; i++)
    if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
      videoStream=i;
      break;
    }
  if(videoStream==-1)
    return -1; // Didn't find a video stream

  // Get a pointer to the codec context for the video stream
  pCodecCtx=pFormatCtx->streams[videoStream]->codec;
  
  // Find the decoder for the video stream
  pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
  if(pCodec==NULL) {
    fprintf(stderr, "Unsupported codec!\n");
    return -1; // Codec not found
  }
  // Open codec
  if(avcodec_open2(pCodecCtx, pCodec, &optionsDict)<0)
    return -1; // Could not open codec
  
  // Allocate video frame
  pFrame=avcodec_alloc_frame();
  
  // Allocate an AVFrame structure
  pFrameRGB=avcodec_alloc_frame();
  if(pFrameRGB==NULL)
    return -1;
  
  // Determine required buffer size and allocate buffer
  numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
            pCodecCtx->height);
  buffer=(uint8_t *)av_malloc(numBytes*sizeof(uint8_t));

  sws_ctx =
    sws_getContext
    (
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
  // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
  // of AVPicture
  avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24,
     pCodecCtx->width, pCodecCtx->height);
  
  // Read frames and save first five frames to disk
  i=0;
  if(av_read_frame(pFormatCtx, &packet)>=0) {
    // Is this a packet from the video stream?
    if(packet.stream_index==videoStream) {
      // Decode video frame
      avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, 
         &packet);

      
      // Did we get a video frame?
      if(frameFinished) {
        // Convert the image from its native format to RGB
        sws_scale
        (
            sws_ctx,
            (uint8_t const * const *)pFrame->data,
            pFrame->linesize,
            0,
            pCodecCtx->height,
            pFrameRGB->data,
            pFrameRGB->linesize
        );
        
        utahCodec = avcodec_find_encoder(AV_CODEC_ID_UTAH);
        pCodecCtx->codec = utahCodec;
        avcodec_encode_video2(pCodecCtx, &utahPacket, pFrameRGB, &gotPacket);
        FILE *pFile;
        pFile = fopen("frame.utah", "wb");
        fwrite(utahPacket.data, 1, utahPacket.size, pFile);
        fclose(pFile);     
      }
    }
    
    // Free the packet that was allocated by av_read_frame
    av_free_packet(&packet);
  }
  
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