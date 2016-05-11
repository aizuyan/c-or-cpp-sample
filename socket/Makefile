objects = server client
all:$(objects)

server:server.c
	gcc -o $@ $^

client:client.c
	gcc -o $@ $^

.PHONY: clean
clean:
	rm $(objects)
