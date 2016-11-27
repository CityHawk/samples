all: bin/server bin/client

bin/server : server/server.c common/function.c
	gcc -g -o bin/server -I common server/server.c common/function.c -lpthread

bin/client : client/client.c common/function.c
	gcc -g -o bin/client -I common client/client.c common/function.c -lpthread

clean:
	rm -f bin/server
	rm -f bin/client
