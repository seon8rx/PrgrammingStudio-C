CC = gcc
main : main.c crud_member.o
	$(CC) -o $@ $^
libcrud.a : crud_member.o
	ar rv $@ $^
C006 : main.o crud_member.o
	$(CC) -o $@ $^ -I/Users/seooonggyu/Documents/22100110_kimseonggyu/Lab4 -L/Users/seooonggyu/Documents/22100110_kimseonggyu/Lab4 -lcrud
clear :
	rm *.o *.a C006