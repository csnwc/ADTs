CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wvla -Wpedantic -std=c99 -Werror
PRODUCTION= $(COMMON) -O3
DEBUG= -g3
SANITIZE= -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
LDLIBS=

all: drivefixed drivefixed_s drivefixed_v drivelinked drivelinked_s drivelinked_v pdfs

drivefixed: deque.h Fixed/specific.h Fixed/fixed.c drivedeque.c ../General/general.h ../General/general.c
	$(CC) drivedeque.c Fixed/fixed.c ../General/general.c -o drivefixed -I./Fixed $(PRODUCTION) $(LDLIBS)

drivelinked: deque.h Linked/specific.h Linked/linked.c drivedeque.c ../General/general.h ../General/general.c
	$(CC) drivedeque.c Linked/linked.c ../General/general.c -o drivelinked -I./Linked $(PRODUCTION) $(LDLIBS)

drivefixed_s: deque.h Fixed/specific.h Fixed/fixed.c drivedeque.c ../General/general.h ../General/general.c
	$(CC) drivedeque.c Fixed/fixed.c ../General/general.c -o drivefixed_s -I./Fixed $(SANITIZE) $(LDLIBS)

drivelinked_s: deque.h Linked/specific.h Linked/linked.c drivedeque.c ../General/general.h ../General/general.c
	$(CC) drivedeque.c Linked/linked.c ../General/general.c -o drivelinked_s -I./Linked $(SANITIZE) $(LDLIBS)

drivefixed_v: deque.h Fixed/specific.h Fixed/fixed.c drivedeque.c ../General/general.h ../General/general.c
	$(CC) drivedeque.c Fixed/fixed.c ../General/general.c -o drivefixed_v -I./Fixed $(VALGRIND) $(LDLIBS)

drivelinked_v: deque.h Linked/specific.h Linked/linked.c drivedeque.c ../General/general.h ../General/general.c
	$(CC) drivedeque.c Linked/linked.c ../General/general.c -o drivelinked_v -I./Linked $(VALGRIND) $(LDLIBS)



clean:
	rm -f drivefixed drivefixed_s drivefixed_v drivelinked drivelinked_s drivelinked_v Linkedq.dot Fixedq.dot Fixedq.pdf Linkedq.pdf

run: all
	./drivefixed_s
	valgrind --quiet ./drivefixed_v
	./drivelinked_s
	valgrind --quiet ./drivelinked_v
































DOT := $(shell command -v dot 2> /dev/null)

Fixedq.dot : drivefixed
	./drivefixed

Linkedq.dot : drivelinked
	./drivelinked

Fixedq.pdf: Fixedq.dot drivedeque.c drivefixed Fixedq.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Fixedq.pdf Fixedq.dot 
Linkedq.pdf: Linkedq.dot drivedeque.c drivelinked Linkedq.dot
ifndef DOT
    $(error "dot is not available please install graphviz")
endif
	dot -Tpdf -o Linkedq.pdf Linkedq.dot 

pdfs:	Fixedq.pdf Linkedq.pdf
