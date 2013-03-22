/* Written by: Alex Gritton and Anthony Jordan Wanlass
 * 
 * Spring 2013
 * 
 * CS 3505
 * 
 * 
 * This will encode an image into a .utah image format.  It can take in any image format and 
 * will convert it.  Our Utah image is an RGB 8-bit image.
 * 
 * This will take the raw data of an image from an AVFrame and place it into an AVPacket.
 * 
 */

#include "avcodec.h"
#include "utah.h"
#include "bytestream.h"
#include "internal.h" //Needed for ff_alloc_packet2

/*
 *  This will initialize the Frame to be encoded.
 * 
 * */
static av_cold int utah_encode_init(AVCodecContext *avctx)
{
	UTAHContext *context = avctx->priv_data;// Sets utahcontext frame equal to an empty frame.
	avcodec_get_frame_defaults(&context->picture);// Set the frame back to defaults.
	avctx->coded_frame = &context->picture;// Setting the avcodeccontext frame equal to a default frame.
	return 0;
}

/*
 * This will be in charge of encoding the frame.  Basically it will take information from the AVFrame and 
 * store it into an AVPacket.
 * 
 * 
 * */
static int utah_encode_frame(AVCodecContext *avctx, AVPacket *pkt,const AVFrame *pict, int *got_packet)
{
	UTAHContext *context = avctx->priv_data;// Sets utahcontext frame equal to an empty frame
    AVFrame * const pic = &context->picture;//  Gives us a pointer to an empty AVFrame
    *pic = *pict;// Sets the frame equal to the frame that contains the actual image data
    
    pic->pict_type= AV_PICTURE_TYPE_I;
    pic->key_frame= 1;
    
	uint8_t *frame_data, *pkt_data;// Create pointers to byte buffers
	
	// Creates an integer that will be used to check if our space allocation works.  Header will represent the amount of space we need for our header
	int ret, header = 14;
	
	/*Checks if the return value of ff_alloc_pakcet is less than 0. if so a problem occured so this returns ret.*/
	/*ff_alloc_packet2 allocates a buffer space*/
	if(ret = (ff_alloc_packet2(avctx, pkt, (header+avctx->height*pic->linesize[0]))) <0)
	  return ret;		
	pkt_data = pkt->data; /*gets the data buffer from AVPackage*/
	
	/*Header packing*/
	bytestream_put_byte(&pkt_data, 'U');// Put the letter 'U' into our buffer
	bytestream_put_byte(&pkt_data, 'T');// Put the letter 'T' into our buffer
	bytestream_put_le32(&pkt_data, avctx->height);// Puts the height into our buffer
	bytestream_put_le32(&pkt_data, avctx->width);// Puts the width into our buffer
	bytestream_put_le32(&pkt_data, pic->linesize[0]);
	/*Image Packing*/
	frame_data = pic->data[0];// Set our pointer equal to our Frame data or the actual image data
	pkt_data = pkt->data+header;// Sets it so we will start placing bytes after our header
	//printf("\n\n\nHERERERERERE = %i\n\n\n", pic->linesize[0]*avctx->height);
	//  This will put our frame bytes into the packet buffer
	for(int row = 0; row<avctx->height;row++)
	  {
	    memcpy(pkt_data, frame_data, pic->linesize[0]);// copty the bytes from the frame into the packet
	    pkt_data+=pic->linesize[0];// Increment our packet buffer
	    frame_data+=pic->linesize[0];// Increment our frame buffer
	  }
	pkt->flags |= AV_PKT_FLAG_KEY;
	*got_packet = 1;// signifies we got the packet
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
