all: clean sum crack

crack: 
	gcc -fopenmp -lm -lcrypt crack.c -o crack

sum: 
	gcc sum.c -o sum

clean:
	$(RM) sum crack
