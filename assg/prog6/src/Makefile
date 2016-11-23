SRCS=$(wildcard *c)
OBJS=$(SRCS:.c=)
TOOLS=hextoraw rawtohex

tools: $(TOOLS)
	# Made tools; use 'all' target for all.

install:
	mkdir -p $(HOME)/bin
	cp $(TOOLS) $(HOME)/bin/

all : $(OBJS)

% : %.c
	gcc $^ -o $@

clean :
	$(RM) $(OBJS)
