all: m

LIBS += HighAccuracy.cpp \
		BITree.cpp
DEPS = HighAccuracy.cpp HighAccuracy.h \
	   BITree.cpp BITree.h
CFLAGS += $(LIBS) -O2

m: m.cpp $(DEPS)
	g++ -o $@ $< $(CFLAGS)

test: test.cpp $(DEPS)
	g++ -o $@ $< $(CFLAGS)

clean:
	rm test

.PHONY: clean
