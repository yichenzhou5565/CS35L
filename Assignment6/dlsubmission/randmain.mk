OPTIMIZE = -O2
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

#use static linking to combine randmain.o and randcpuid.o into a single program
#executable randmain.
#randmain.mk should link randmain with the options “-ldl -Wl,-rpath=$PWD”
randmain: randcpuid.o randmain.o
	gcc $(CFLAGS) randmain.o randcpuid.o -o randmain -ldl -Wl,-rpath=$(PWD)

randcpuid.o: randcpuid.c randcpuid.h
	gcc $(CFLAGS) -c randcpuid.c -o randcpuid.o

randmain.o: randmain.c randcpuid.h randcpuid.c
	gcc $(CFLAGS) -c randmain.c -o randmain.o


#use dynamic linking as usual to link the C library
#and any other necessary system-supplied files 
#before its main function is called

#build shared object files randlibhw.so and randlibsw.so
#by linking the corresponding object modules with the -shared option
#e.g., “gcc ... -shared randlibsw.o -o randlibsw.so”
randlibhw.so: randlibhw.o
	gcc $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o
	gcc $(CFLAGS) -shared randlibhw.o -o librandlibhw.so

randlibsw.so: randlibsw.o
	gcc $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o
	gcc $(CFLAGS) -shared randlibsw.o -o librandlibsw.so

#compile randlibhw.c and randlibsw.c with the -fPIC
#randlibhw.o: randlib.h randlibhw.c
#	gcc $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o

#randlibsw.o: randlib.h randlibsw.c
#	gcc $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o
