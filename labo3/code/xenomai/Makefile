#Optional CFLAGS: -Wall -Werror-implicit-function-declaration -g

XENOCONFIG=/usr/bin/xeno-config
CC=	$(shell $(XENOCONFIG) --cc)
CFLAGS= $(shell $(XENOCONFIG) --skin=alchemy --cflags)
LDFLAGS=$(shell $(XENOCONFIG) --skin=alchemy --ldflags)

all:: xenomai_timer
clean::
	rm -f xenomai_timer *.o
