
CC = g++
CFLAGS = -g -Wall
INCLUDE = -I/usr/local/include
LINK = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_objdetect -lopencv_videoio -lopencv_videostab 
EXC = keyeboard

$(EXC): keyeboard.o
	$(CC) $(INCLUDE) keyeboard.o -o $(EXC) $(LINK)

clean:
	rm -f *.o $(EXC)
