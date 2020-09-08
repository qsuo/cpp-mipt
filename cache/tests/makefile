CFLAGS:= -Wall -MD
CXX:= g++

.PHONY: all clean

all: lru 2q

-include *.d

lru: lru.o common.o
	$(CXX) $(CFLAGS) -o $@ $^

2q: 2q.o common.o
	$(CXX) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

test: all
	./lru
	./2q

clean:
	rm -rf lru 2q *.o *.d
