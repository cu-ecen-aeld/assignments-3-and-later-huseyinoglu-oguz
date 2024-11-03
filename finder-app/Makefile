writer: writer.c
	gcc -o writer writer.c

CROSS_COMPILE: writer.c
	aarch64-none-linux-gnu-gcc -o writer writer.c

clean:
	rm *.o writer