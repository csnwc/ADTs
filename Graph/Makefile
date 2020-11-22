CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testrealloc_s testrealloc_v testrealloc testlinked testlinked_s testlinked_v pdfs

testrealloc : graph.h Realloc/specific.h Realloc/realloc.c testgraph.c ../General/general.h ../General/general.c
	$(CC) testgraph.c Realloc/realloc.c ../General/general.c -o testrealloc -I./Realloc $(PRODUCTION) $(LDLIBS)

testlinked: graph.h Linked/specific.h Linked/linked.c testgraph.c ../General/general.h ../General/general.c
	$(CC) testgraph.c Linked/linked.c ../General/general.c -o testlinked -I./Linked $(PRODUCTION) $(LDLIBS)

testrealloc_s : graph.h Realloc/specific.h Realloc/realloc.c testgraph.c ../General/general.h ../General/general.c
	$(CC) testgraph.c Realloc/realloc.c ../General/general.c -o testrealloc_s -I./Realloc $(SANITIZE) $(LDLIBS)

testlinked_s: graph.h Linked/specific.h Linked/linked.c testgraph.c ../General/general.h ../General/general.c
	$(CC) testgraph.c Linked/linked.c ../General/general.c -o testlinked_s -I./Linked $(SANITIZE) $(LDLIBS)

testrealloc_v : graph.h Realloc/specific.h Realloc/realloc.c testgraph.c ../General/general.h ../General/general.c
	$(CC) testgraph.c Realloc/realloc.c ../General/general.c -o testrealloc_v -I./Realloc $(VALGRIND) $(LDLIBS)

testlinked_v: graph.h Linked/specific.h Linked/linked.c testgraph.c ../General/general.h ../General/general.c
	$(CC) testgraph.c Linked/linked.c ../General/general.c -o testlinked_v -I./Linked $(VALGRIND) $(LDLIBS)


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

Linkedb.pdf:  testgraph.c testlinked Linkedb.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Linkedb.pdf Linkedb.dot
Reallocb.pdf:  testgraph.c testrealloc Reallocb.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Reallocb.pdf Reallocb.dot

pdfs : Linkedb.pdf Reallocb.pdf
