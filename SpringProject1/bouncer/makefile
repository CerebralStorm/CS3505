all: a.out

a.out: test.cc
	g++ -I ../ffmpeg/include/ -L../ffmpeg/lib test.cc `pkg-config --cflags --libs libavutil libavformat libavcodec libswscale`

clean: 
	rm -f *.o *.utah a.out

movie: 
	./a.out test.jpg
	ffmpeg -i frame%03d.utah -vcodec mpeg4 test.mp4
	rm -f *.utah
