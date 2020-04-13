#
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --leak-check=full --verbose --track-origins=yes


SRCS = pa5.c sorting.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS)
	$(GCC) $(OBJS) -o pa5

.c.o:
	$(GCC) -c $*.c

testmemory: pa5
	$(VAL) ./pa5 -m inputs/100K.b output100K.b

testall: test1 test2 test3 test4 test5 test7 test6

test1: pa5
	./pa5 -m inputs/10.b 10m.b
	diff 10q.b 10m.b

test2: pa5
	./pa5 -m inputs/100.b 100m.b
	./pa5 -q inputs/100.b 100q.b
	diff 100q.b 100m.b

test3: pa5
	./pa5 -m inputs/1K.b 1Km.b
	./pa5 -q inputs/1K.b 1Kq.b
	diff 1Kq.b 1Km.b

test4: pa5
	./pa5 -m inputs/50K.b 50Km.b
	./pa5 -q inputs/50K.b 50Kq.b
	diff 50Kq.b 50Km.b

test5: pa5
	./pa5 -m inputs/100K.b 100Km.b
	./pa5 -q inputs/100K.b 100Kq.b
	diff 100Kq.b 100Km.b

test6: pa5
	./pa5 -m inputs/250K.b 250Km.b
	./pa5 -q inputs/250K.b 250Kq.b
	diff 250Kq.b 250Km.b

test7: pa5
	./pa5 -m inputs/1M.b 1Mm.b
	./pa5 -q inputs/1M.b 1Mq.b
	diff 1Mq.b 1Mm.b

test8: pa5
	./pa5 -m inputs/5M.b 5Mm.b
	./pa5 -q inputs/5M.b 5Mq.b
	diff 5Mq.b 5Mm.b

clean: # remove all machine generated files
	rm -f pa5 *.o *.b output?
