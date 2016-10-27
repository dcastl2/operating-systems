all: clean sum crack

crack: 
	gcc -std=c99 -lcrypt crack.c -o crack

sum: 
	gcc sum.c -o sum

clean:
	$(RM) sum crack
