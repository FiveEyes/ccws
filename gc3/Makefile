CC = gcc
CFLAGS = -std=c11 -I. 
DEPS = GCTypes.h
OBJ = GCObj.o GCPtr.o GCStr.o GCMain.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gcmain.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o gcmain.exe

rebuild:
	make clean
	make gcmain.exe

lib:
	make rebuild
	$(CC) -fPIC GCObj.c GCPtr.c GCStr.c -shared -o libgc3.so
	ar -rc libgc3.a GCObj.o GCPtr.o GCStr.o