# From libguide.pdf
# Works on cmd line, but not in Makefile
#CFLAGS=‘pkg-config libgvc --cflags‘ -Wall -g -O2	
#LDFLAGS=‘pkg-config libgvc --libs‘

CFLAGS=-I/opt/local/include/graphviz -O2
LDFLAGS=-L/opt/local/lib -lgvc -lgraph -lcdt

ifdef DEBUG
CFLAGS+=-D_DEBUG
endif

a: a.cpp
	g++ $(CFLAGS) $(LDFLAGS) -o $@ $^

p: p.cpp
	g++ $(CFLAGS) $(LDFLAGS) -o $@ $^

mm: mm.cpp
	g++ $(CFLAGS) $(LDFLAGS) -o $@ $^
