SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=)

all: $(OBJS)

% : %.cpp
	gcc $^ -o $@

clean:
	$(RM) $(OBJS)
