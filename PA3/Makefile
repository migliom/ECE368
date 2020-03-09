#
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --track-origins=yes --tool=memcheck --leak-check=full --verbose

SRCS = pa3.c files.c stack.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	$(GCC) $(OBJS) -o pa3

.c.o:
	$(GCC) -c $*.c

testmemory: pa3
	$(VAL)	./pa3 examples/3.po my3.pr my3.dim my3.pck
	

testall: test1 test2 test3 

test1: pa3
	./pa3 examples/3.po my3.pr my3.dim my3.pck
	diff my3.pr examples/3.pr
	diff my3.dim examples/3.dim
	diff my3.pck examples/3.pck

test2: pa3
	./pa3 examples/8.po my8.pr my8.dim my8.pck
	diff my8.pr examples/8.pr
	diff my8.dim examples/8.dim
	diff my8.pck examples/8.pck

test3: pa3
	./pa3 examples/1K.po myK.pr myK.dim myK.pck
	diff myK.pr examples/1K.pr
	diff myK.dim examples/1K.dim
	diff myK.pck examples/1K.pck


clean: # remove all machine generated files
	rm -f pa3 *.o output?
