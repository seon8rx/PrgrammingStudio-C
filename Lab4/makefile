CC = gcc
main : main.c crud_member.o
	$(CC) -o $@ $^
crud_member.o : crud_member.c crud_member.h
	$(CC) -c $<
C006 : main.c crud_member.o
	$(CC) -o $@ $^ -I/Users/seooonggyu/Documents/22100110_kimseonggyu/Lab4 -L/Users/seooonggyu/Documents/22100110_kimseonggyu/Lab4 -lcrud
clear :
	rm *.o