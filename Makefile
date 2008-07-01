CFLAGS+=-g -Wunused -Wmissing-noreturn

#ifdef _DEBUG
CFLAGS+=-D_DEBUG
#endif

mm: mm.cpp
	g++ $(CFLAGS) -o $@ $^
