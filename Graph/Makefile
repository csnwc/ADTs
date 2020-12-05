CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testrealloc_s testrealloc_v testrealloc testlinked testlinked_s testlinked_v pdfs

testrealloc : graph.h Realloc/specific.h Realloc/realloc.c testgraph.c indep.c ../General/general.h ../General/general.c indep.c
	$(CC) testgraph.c Realloc/realloc.c indep.c ../General/general.c -o testrealloc -I./Realloc $(PRODUCTION) $(LDLIBS)

testlinked: graph.h Linked/specific.h Linked/linked.c testgraph.c indep.c ../General/general.h ../General/general.c indep.c
	$(CC) testgraph.c Linked/linked.c indep.c ../General/general.c -o testlinked -I./Linked $(PRODUCTION) $(LDLIBS)

testrealloc_s : graph.h Realloc/specific.h Realloc/realloc.c testgraph.c indep.c ../General/general.h ../General/general.c indep.c
	$(CC) testgraph.c Realloc/realloc.c indep.c ../General/general.c -o testrealloc_s -I./Realloc $(SANITIZE) $(LDLIBS)

testlinked_s: graph.h Linked/specific.h Linked/linked.c testgraph.c indep.c ../General/general.h ../General/general.c indep.c
	$(CC) testgraph.c Linked/linked.c indep.c ../General/general.c -o testlinked_s -I./Linked $(SANITIZE) $(LDLIBS)

testrealloc_v : graph.h Realloc/specific.h Realloc/realloc.c testgraph.c indep.c ../General/general.h ../General/general.c indep.c
	$(CC) testgraph.c Realloc/realloc.c indep.c ../General/general.c -o testrealloc_v -I./Realloc $(VALGRIND) $(LDLIBS)

testlinked_v: graph.h Linked/specific.h Linked/linked.c testgraph.c indep.c ../General/general.h ../General/general.c indep.c
	$(CC) testgraph.c Linked/linked.c indep.c ../General/general.c -o testlinked_v -I./Linked $(VALGRIND) $(LDLIBS)


clean:
	rm -f testrealloc_s testrealloc_v testrealloc testlinked testlinked_s testlinked_v Linkedg.dot Linkedg.pdf Reallocg.dot Reallocg.pdf

run: testrealloc_s testrealloc_v testlinked_s testlinked_v pdfs
	./testrealloc_s
	valgrind ./testrealloc_v
	./testlinked_s
	valgrind ./testlinked_v

DOT := $(shell command -v dot 2> /dev/null)

Linkedg.dot:  testlinked
	./testlinked
Reallocg.dot: testrealloc
	./testrealloc

Linkedg.pdf:  testgraph.c testlinked Linkedg.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Linkedg.pdf Linkedg.dot
Reallocg.pdf:  testgraph.c testrealloc Reallocg.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Reallocg.pdf Reallocg.dot

pdfs : Reallocg.pdf Linkedg.pdf
