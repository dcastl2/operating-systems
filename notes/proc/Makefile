SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=)

all: $(OBJS)

shm-read : shm-read.c
	gcc shm-read.c -lrt -o shm-read

shm-write : shm-write.c
	gcc shm-write.c -lrt -o shm-write

% : %.c
	gcc $^ -o $@

clean:
	$(RM) $(OBJS)
