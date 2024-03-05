CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = calc
DEP1 = myMath

all:	$(TARGET)

$(TARGET):	$(TARGET).c $(DEP1).o
	$(CC) $(CFLAGS) $(DEP1).o -o $(TARGET) $(TARGET).c

$(DEP1).o:	$(DEP1).c
	$(CC) $(CFLAGS) -c $(DEP1).c

clean:
	rm $(TARGET) *.o

