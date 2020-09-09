CFLAGS:= -Wall -MD
CXX:= g++

.PHONY: all clean

all: lru 2q 2q_int

-include *.d

lru: lru.o
	$(CXX) $(CFLAGS) -o $@ $^

2q: 2q.o
	$(CXX) $(CFLAGS) -o $@ $^

2q_int: 2q_int.o
	$(CXX) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

test: all
	./lru
	./2q
	./2q_int

clean:
	rm -rf lru 2q 2q_int *.o *.d
