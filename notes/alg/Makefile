SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=)

all: $(OBJS)

% : %.cpp
	g++ $^ -o $@

clean:
	$(RM) $(OBJS)
