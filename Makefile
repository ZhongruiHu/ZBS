CFLAGS+=-g -Wunused -Wmissing-noreturn

#ifdef _DEBUG
CFLAGS+=-D_DEBUG
#endif

a: a.cpp
	g++ $(CFLAGS) -o $@ $^

p: p.cpp
	g++ $(CFLAGS) -o $@ $^

mm: mm.cpp
	g++ $(CFLAGS) -o $@ $^
