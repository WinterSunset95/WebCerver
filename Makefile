all:
	gcc -o server main.c
	gcc -o client client.c
clean:
	rm client server
