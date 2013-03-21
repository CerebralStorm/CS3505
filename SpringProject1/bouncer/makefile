all: a.out

a.out: test.cc
	g++ -I ../ffmpeg/include/ -L../ffmpeg/lib test.cc `pkg-config --cflags --libs libavutil libavformat libavcodec`

clean: 
	rm -f *.o *.utah a.out

movie: 
	./a.out test.jpg

