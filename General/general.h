#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void on_error(const char* s);
void* ncalloc(int n, size_t size);
void* nrecalloc(void* p, int oldsz, int newsz);
void* nrealloc(void* p, int n);
void* nfopen(char* fname, char* mode);
