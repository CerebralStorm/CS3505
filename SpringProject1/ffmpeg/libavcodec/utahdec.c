/* Written by: Alex Gritton and Anthony Jordan Wanlass
 * 
 * Spring 2013
 * 
 * CS 3505
 * 
 * 
 * This will decode an .utah image.  Our Utah image is an RGB 8-bit image.
 * 
 * This will take the raw data of an image from an AVPacket and place it into an AVFrame.
 * 
 */
 
#include "bytestream.h"
#include "avcodec.h"
#include "internal.h"
#include "utah.h"


/* Initialize the frame
 * */
static av_cold int utah_decode_init(AVCodecContext *avctx)
{
    UTAHContext *context = avctx->priv_data;// Sets utahcontext frame equal to an empty frame.
    avcodec_get_frame_defaults(&context->picture);// Set the frame back to defaults.
    avctx->coded_frame = &context->picture;// Setting the avcodeccontext frame equal to a default frame.
    return 0;
}


/*
 * This will be in charge of decoding the image.  Basically it will take information from the AVPacket and 
 * store it into an AVFrame.
 * 
 * 
 * */
static int utah_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt)
{
	/*Initializing Variables*/
	UTAHContext *context = avctx->priv_data;// Sets utahcontext frame equal to an empty frame
	const uint8_t *buffer = avpkt->data;// Creates a pointer to a byte buffer and points it at the packet data.
	uint8_t* pic_buffer;// Creates a byte buffer pointer
	int buffer_size = avpkt->size, fheight = 0, fwidth = 0, ret, header = 14, line = 0;
	AVFrame *picture = data;// 
	AVFrame *pic = &context->picture;// Creates an AVFrame pointer and points it at the Utahcontext frame.
	avctx->pix_fmt = AV_PIX_FMT_RGB24;// Sets our picture format to equal to and RGB 8-bit image, this must be set
	
	/*Checks the buffer size and if the size is less than the header its not a .utah image.
	 * Header is 10, that is an arbitrary number that we chose for our utah image format
	 * */
	if(buffer_size <header)
	{
		av_log(avctx, AV_LOG_ERROR, "Image is not a .utah image(invalid header size)\n");
        return AVERROR_INVALIDDATA;
	}
	
	/*Checks the image header to verify a .utah image.
	 * The first element in the packet buffer should be a 'U', the second element should be a 'T'
	 * */
	if(bytestream_get_byte(&buffer) != 'U' || bytestream_get_byte(&buffer)!='T')
	{
		av_log(avctx, AV_LOG_ERROR, "Image is not a .utah image\n");
		return AVERROR_INVALIDDATA;
	}
	
	/*Gets the width and height of the image from the pkt buffer and sets avctx accordingly.*/
	fheight = bytestream_get_le32(&buffer);// Get the height from the packet buffer
	fwidth = bytestream_get_le32(&buffer);// get the width from the packet buffer
	avctx->height = fheight;
	
	line = bytestream_get_le32(&buffer);
	avctx->width =fwidth;
	//printf("\n\nHere1\n\n");
	/* Our height multiplied by the width plus the height should be equivalent to the size of our packet buffer
	 * If its not, we have a problem and should stop decoding.
	 * 
	 * */
	if(fheight*line +header != buffer_size)
	{
		av_log(avctx, AV_LOG_ERROR, ("Image is not the right size: Expected = %i, Actual = %i", fheight*line+header, buffer_size));
		return AVERROR_INVALIDDATA;
	}
	//printf("\n\nHere2\n\n");
	/*Checks if the frame already has memory allocated
	 * If it does have memory allocated, release it
	 * */	
	if (pic->data[0])
	{
        avctx->release_buffer(avctx, pic);
	}
	pic->reference = 0;
	//printf("\n\nHere3\n\n");
	/*Allocates space for the frame buffer to store raw image bytes
	 * We need to have space to put what we take out of our packet buffer
	 * */
	if ((ret = ff_get_buffer(avctx, pic)) < 0) {
        return ret;
    }
	//printf("\n\nHere4\n\n");
    /*Clears the allocated memory
     * Sets all of the memory that we allocated equal to zero, almost like initializing it
     * */
	memset(pic->data[0], 0, fheight*pic->linesize[0]);
	pic_buffer = pic->data[0];// points our byte buffer pointer at the AVFrame data
	
	/*loops through the image bytes in the packet data storing it in the frame data and then pads each row
	 * with zeros to take up the remaning space in each line
	 * */
	//	printf("\n\nHere5\n\n");
	for(int row = 0; row<fheight;row++)
	{
		memcpy(pic_buffer, buffer, line);// store the data
		//	memset(pic_buffer+line, 0, pic->linesize[0]-line);// pad the row
		pic_buffer+=pic->linesize[0];// increment the buffer
		buffer+=line;// increment the buffer
	}
	//printf("\n\nHere6\n\n");
	*picture = context->picture;
	*got_frame = 1;
	return buffer_size;
}

/* Release the memory that was allocated
 * 
 * 
 * */
static av_cold int utah_decode_end(AVCodecContext *avctx)
{
    UTAHContext* context = avctx->priv_data;
    if (context->picture.data[0])
        avctx->release_buffer(avctx, &context->picture);
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
