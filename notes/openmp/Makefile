SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=)

all: $(OBJS)

% : %.c
	gcc $^ -fopenmp -o $@

clean:
	$(RM) $(OBJS)
