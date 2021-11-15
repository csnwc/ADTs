CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testrealloc_s testrealloc_v testrealloc testlinked testlinked_s testlinked_v pdfs

testrealloc : bst.h Realloc/specific.h Realloc/realloc.c testbst.c ../General/general.h ../General/general.c ../Queue/Linked/linked.c
	$(CC) testbst.c Realloc/realloc.c ../General/general.c ../Queue/Linked/linked.c -o testrealloc -I./Realloc $(PRODUCTION) $(LDLIBS)

testlinked: bst.h Linked/specific.h Linked/linked.c testbst.c ../General/general.h ../General/general.c ../Queue/Linked/linked.c
	$(CC) testbst.c Linked/linked.c ../General/general.c ../Queue/Linked/linked.c -o testlinked -I./Linked $(PRODUCTION) $(LDLIBS)

testrealloc_s : bst.h Realloc/specific.h Realloc/realloc.c testbst.c ../General/general.h ../General/general.c ../Queue/Linked/linked.c
	$(CC) testbst.c Realloc/realloc.c ../General/general.c ../Queue/Linked/linked.c -o testrealloc_s -I./Realloc $(SANITIZE) $(LDLIBS)

testlinked_s: bst.h Linked/specific.h Linked/linked.c testbst.c ../General/general.h ../General/general.c ../Queue/Linked/linked.c
	$(CC) testbst.c Linked/linked.c ../General/general.c ../Queue/Linked/linked.c -o testlinked_s -I./Linked $(SANITIZE) $(LDLIBS)

testrealloc_v : bst.h Realloc/specific.h Realloc/realloc.c testbst.c ../General/general.h ../General/general.c ../Queue/Linked/linked.c
	$(CC) testbst.c Realloc/realloc.c ../General/general.c ../Queue/Linked/linked.c -o testrealloc_v -I./Realloc $(VALGRIND) $(LDLIBS)

testlinked_v: bst.h Linked/specific.h Linked/linked.c testbst.c ../General/general.h ../General/general.c ../Queue/Linked/linked.c
	$(CC) testbst.c Linked/linked.c ../General/general.c ../Queue/Linked/linked.c -o testlinked_v -I./Linked $(VALGRIND) $(LDLIBS)


clean:
	rm -f testrealloc_s testrealloc_v testrealloc testlinked testlinked_s testlinked_v Linkedb.dot Linkedb.pdf Reallocb.dot Reallocb.pdf 

run: all
	./testrealloc_s
	./testlinked_s
	valgrind ./testrealloc_v
	valgrind ./testlinked_v

































DOT := $(shell command -v dot 2> /dev/null)

Linkedb.dot:  testlinked
	./testlinked
Reallocb.dot: testrealloc
	./testrealloc

Linkedb.pdf:  testbst.c testlinked Linkedb.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Linkedb.pdf Linkedb.dot
Reallocb.pdf:  testbst.c testrealloc Reallocb.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Reallocb.pdf Reallocb.dot

pdfs : Linkedb.pdf Reallocb.pdf
