CC = gcc
FLAGS = -pedantic -Wall
HDRDIRS = -I$(HOME)/Documents/Libraries/Fxs/Include
LIBDIRS = -L$(HOME)/Documents/Libraries/Fxs/Lib
LIBS = -lFxs -lm
OBJS = Renderer.o Object.o
TARGET = RayTrace00

$(TARGET): Main.c ${OBJS}
	$(CC) -o $(TARGET) Main.c $(FLAGS) $(OBJS) $(LIBS) $(HDRDIRS) $(LIBDIRS)

%.o: %.c
	echo $<
	$(CC) -c $< $(HDRDIRS)

clean:
	rm *.o
	rm $(TARGET)
