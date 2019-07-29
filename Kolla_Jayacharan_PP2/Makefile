
CC:=gcc

program: innermost.c twoloops.c allloops.c gauss_elim.c

	 $(CC) gauss_elim.c -o gaussi.out

	 $(CC) innermost.c -fopenmp -o a.out

	 $(CC) twoloops.c -fopenmp -o b.out

	 $(CC) allloops.c -fopenmp -o c.out



clean:
	rm -rf *.out