INCLUDE=-I/usr/include/graphviz -I/opt/local/include/graphviz
LIB=-L/usr/lib/graphviz -L/opt/local/lib/graphviz -lgvc -lagraph

CFLAGS+=-g -Wunused -Wmissing-noreturn -Wno-write-strings $(INCLUDE) $(LIB)

ifdef DEBUG
CFLAGS+=-D_DEBUG
endif

a: a.cpp
	g++ $(CFLAGS) -o $@ $^

p: p.cpp
	g++ $(CFLAGS) -o $@ $^

mm: mm.cpp
	g++ $(CFLAGS) -o $@ $^
