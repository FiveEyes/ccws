CC = gcc
CFLAGS = -std=c11 -I.
DEPS = 
OBJ = CCPureBlock.o Blocks/CCAddBlock.o CCMain.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ccmain.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) ../gc3/libgc3.a

clean:
	rm -f *.o ccmain.exe

rebuild:
	make clean
	make ccmain.exe

