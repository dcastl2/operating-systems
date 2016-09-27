SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=)

all: $(OBJS)

% : %.c
	gcc $^ -pthread -o $@

clean:
	$(RM) $(OBJS)
