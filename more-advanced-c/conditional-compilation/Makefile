CC = gcc
CFLAGS = -Wall -Wextra -pedantic
FILE = text-alteration
TARGET1 = filter
TARGET2 = switched
TARGET3 = reversed
MACRO1 = -DFILTER
MACRO2 = -DSWITCHED
MACRO3 = -DREVERSED

$(TARGET1): $(FILE).c
	$(CC) $(CFLAGS) $(MACRO1) -o $(FILE) $(FILE).c

$(TARGET2): $(FILE).c
	$(CC) $(CFLAGS) $(MACRO2) -o $(FILE) $(FILE).c

$(TARGET3): $(FILE).c
	$(CC) $(CFLAGS) $(MACRO3) -o $(FILE) $(FILE).c

clean:
	rm $(FILE)
