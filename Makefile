CC = gcc
CFLAGS = -O3 # Optimisation du code
LDFLAGS = -lm # Librairie math
OBJFILES = grid.o main.o menu.o missiles.o save.o verifications.o
TARGET = exe

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

cleanall:
	rm -f $(OBJFILES) $(TARGET) *~

clean:
	rm -f *.o
