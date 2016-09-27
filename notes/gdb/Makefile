SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=)

all: $(OBJS)

% : %.c
	gcc $^ -o $@

clean:
	$(RM) $(OBJS)
