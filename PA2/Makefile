#
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --track-origins=yes --tool=memcheck --leak-check=full --verbose

SRCS = pa2.c files.c huffman.c merge.c codeTable.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS)
	$(GCC) $(OBJS) -o pa2

.c.o:
	$(GCC) -c $*.c

testmemory: pa2
	$(VAL)	./pa2 original/lorum myLorum.count myLorum.tree myLorum.code myLorum.hbt

testall: test1 test2 test3 test4 test5 test6

test1: pa2
	./pa2 original/lorum myLorum.count myLorum.tree myLorum.code myLorum.hbt	
	diff myLorum.count count/lorum.count
	diff myLorum.tree tree/lorum.tree
	diff myLorum.code code/lorum.code
	diff myLorum.hbt compressed/lorum.hbt

test2: pa2
	./pa2 original/gophers myGophers.count myGophers.tree myGophers.code myGophers.hbt	
	diff myGophers.count count/gophers.count
	diff myGophers.tree tree/gophers.tree
	diff myGophers.code code/gophers.code
	diff myGophers.hbt compressed/gophers.hbt

test3: pa2
	./pa2 original/stone myStone.count myStone.tree myStone.code myStone.hbt
	diff myStone.count count/stone.count
	diff myStone.tree tree/stone.tree
	diff myStone.code code/stone.code
	diff myStone.hbt compressed/stone.hbt

test4: pa2
	./pa2 original/empty myEmpty.count myEmpty.tree myEmpty.code myEmpty.hbt
	diff myEmpty.count count/empty.count
	diff myEmpty.tree tree/empty.tree
	diff myEmpty.code code/empty.code
	diff myEmpty.hbt compressed/empty.hbt

test5: pa2
	./pa2 original/binary1 myB1.count myB1.tree myB1.code myB1.hbt
	diff myB1.count count/binary1.count
	diff myB1.tree tree/binary1.tree
	diff myB1.code code/binary1.code
	diff myB1.hbt compressed/binary1.hbt

test6: pa2
	./pa2 original/woods myWoods.count myWoods.tree myWoods.code myWoods.hbt
	diff myWoods.count count/woods.count
	diff myWoods.tree tree/woods.tree
	diff myWoods.code code/woods.code
	diff myWoods.hbt compressed/woods.hbt


clean: # remove all machine generated files
	rm -f pa2 *.o *.code *.tree *.count *.hbt output?
