// use this command to include all needed info to compile.
// g++ -I ../include/ -L../lib test.cc `pkg-config --cflags --libs libavutil libavformat libavcodec`


#include <iostream>

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

}

using namespace std;

int main (int argc, char *argv[])
{
	av_register_all();	
	AVFormatContext* pFormatCtx = avformat_alloc_context();
	
	// Open Image
	if ((avformat_open_input(&pFormatCtx, argv[1], NULL, NULL)) < 0) {
		printf("Error loading image");
		return -1;
    }
	
	// Retrieve stream information
	if ((avformat_find_stream_info(pFormatCtx, NULL)) < 0) {
		printf("Error loading stream");
		return -1;
    }

	cout << "Success" << endl;
	
	// Clean Up
	avformat_free_context(pFormatCtx);
  
	return 0;
}
