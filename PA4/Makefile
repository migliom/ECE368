
#
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --track-origins=yes --tool=memcheck --leak-check=full --verbose

SRCS = pa4.c files.c tree.c 
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(OBJS) -o pa4

.c.o:
	$(GCC) -c $*.c

testmemory1: pa4
	$(VAL) ./pa4 -b examples/ops3.b output.b

testmemory2: pa4
	$(VAL) ./pa4 -e examples/invalidtree0.b

testall: test1 test2 test3 test12 test4 test5 test6 test10 test7 test8 test9 test11

test1: pa4
	./pa4 -e examples/invalidtree0.b

test2: pa4
	./pa4 -e examples/invalidtree1.b

test3: pa4
	./pa4 -e examples/invalidtree2.b

test12: pa4
	./pa4 -e examples/invalidtree4.b
test4: pa4
	./pa4 -e examples/tree0.b

test5: pa4
	./pa4 -e examples/tree1.b

test6: pa4
	./pa4 -e examples/tree2.b

test10: pa4
	./pa4 -e examples/tree3.b

test7: pa4
	./pa4 -b examples/ops0.b outOPS0.b
	diff outOPS0.b examples/tree0.b

test8: pa4
	./pa4 -b examples/ops1.b outOPS1.b
	diff outOPS1.b examples/tree1.b

test9: pa4
	./pa4 -b examples/ops2.b outOPS2.b
	diff outOPS2.b examples/tree2.b

test11: pa4
	./pa4 -b examples/ops3.b outOPS3.b
	diff outOPS3.b examples/tree3.b


clean:
	rm -f pa4 *.o *.b output?
