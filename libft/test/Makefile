all: main

main : main_test.c
	make -C ../
	gcc -o main main_test.c -I.. -L.. -lft

clean :
	rm -rf main

re : clean all
