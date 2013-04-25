Several students asked me if they could link against my utah codec.
Yes, but I won't release my source code files.  Instead, I'll give you
my compiled files.  First, make sure your existing utah codec files
are named:

utahenc.c
utahdec.c

If they are not named like this, you'll have problems.  If you want to
use my utah codec, you'll have to change the filenames and makefile
appropriately in ffmpeg.

Next, make sure your utah codec ids match my instructions from the
project and the earlier checkpoints.  (This shouldn't be a problem as
most students followed the instructions.  If it is a problem, you'll
need to make sure your identifiers exactly match my instructions from
the project.)

Finally, if your files are named as above, then your compiled files
will be named:

utahenc.o
utahdec.o

You will replace your compiled files with my compiled files.  Copy
these files to the directories shown below.

utahenc.o -> ffmpeg/libavcodec/utahenc.o
utahdec.o -> ffmpeg/libavcodec/utahdec.o

Now, when you remake your ffmpeg project, my codec will be linked in.

Note - if you edit your utahcodec .c files, they will be rebuilt into
object files the next time you make ffmpeg.  You will need to replace
your .o files with my .o files again.  (Remember, the make program
checks timestamps.  As long as you don't update the timestamps on your
utahenc.c and utahdec.c files, then the make utility will not
recompile them.)



