all:
	gcc grocery.c -lrt -pthread -o grocery

clean: 
	rm grocery