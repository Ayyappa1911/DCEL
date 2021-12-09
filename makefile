CC = g++

CFLAGS = -lm

DEPS = 1.h

OBJ = main.o functions.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
assignment3: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm -rf *o assignment3
