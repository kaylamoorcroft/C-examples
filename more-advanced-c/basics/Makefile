CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET1 = if
TARGET2 = while
TARGET3 = do-while
TARGET4 = switch
TARGET5 = for
 
all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)
  
$(TARGET1): $(TARGET1).c
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c
  
$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).c

$(TARGET3): $(TARGET3).c
	$(CC) $(CFLAGS) -o $(TARGET3) $(TARGET3).c

$(TARGET4): $(TARGET4).c
	$(CC) $(CFLAGS) -o $(TARGET4) $(TARGET4).c

$(TARGET5): $(TARGET5).c
	$(CC) $(CFLAGS) -o $(TARGET5) $(TARGET5).c

clean:
	rm $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5)
