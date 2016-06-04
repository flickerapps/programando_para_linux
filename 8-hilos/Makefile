build:
	gcc cap25.c -lpthread -o cap25
run:
	make build
	./cap24
%.o: %.c
	gcc -DDEBUG $< -lpthread -o $@
	./$@
clean:
	rm cap24
