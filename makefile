# ------------------------------------------------
# Generic Makefile
#
# @author Hitin Sarin - hitinsarin@cmail.carleton.ca
# @author Jaspreet Kaur - jaspreetkaur4@cmail.carleton.ca
# @author Saksham Mal - sakshammal@cmail.caretlon.ca
# @author Prerit Sikerwal - preritsikerwal@cmail.carleton.ca
# 

# Date  : 2020-06-23
#
# 2020-06-23: Makefile
# -----------------------------------------------

CC = gcc
LIBS = -pthread

$(shell mkdir -p bin)
$(shell mkdir -p build)

all: client serverSingle serverMulti test_client test_server message

serverMulti: serverMulti.o queue.o common.o
		$(CC) $(LIBS) ./build/serverMulti.o ./build/queue.o ./build/common.o -o ./bin/serverMulti

serverSingle: serverSingle.o common.o
		$(CC) ./build/serverSingle.o ./build/common.o -o ./bin/serverSingle

client: client.o common.o
		$(CC) ./build/client.o ./build/common.o -o ./bin/client

test_client: test_client.o common.o
		$(CC) ./build/test_client.o ./build/common.o -o ./bin/test_client

test_server: test_server.o common.o
		$(CC) ./build/test_server.o ./build/common.o -o ./bin/test_server

serverMulti.o: ./src/server-multithread/server.c ./include/server_multi.h ./include/queue.h ./include/common.h
		$(CC) -c ./src/server-multithread/server.c -o ./build/serverMulti.o

serverSingle.o: ./src/server-singlethread/server.c  ./include/server_single.h ./include/common.h
		$(CC) -c ./src/server-singlethread/server.c -o ./build/serverSingle.o

client.o: ./src/client/client.c ./include/client.h ./include/common.h
		$(CC) -c ./src/client/client.c -o ./build/client.o

queue.o: ./lib/queue.c ./include/queue.h
		$(CC) -c ./lib/queue.c -o ./build/queue.o

test_client.o: ./test/src/test_client.c ./include/client.h ./include/common.h
	  $(CC) -c ./test/src/test_client.c -o ./build/test_client.o

test_server.o: ./test/src/test_server.c ./include/server_single.h ./include/server_multi.h ./include/common.h
		$(CC) -c ./test/src/test_server.c -o ./build/test_server.o

common.o: ./src/common.c ./include/common.h
		$(CC) -c ./src/common.c -o ./build/common.o

message:
	@echo ""
	@echo "		Now you can run this project by folowing the steps in the User_Manual"
	@echo "		bin/./client 127.0.0.1 8080"
	@echo "		bin/./serverSingle 8080"

.PHONY: clean

clean:
		rm -f ./build/*.o ./bin/serverSingle ./bin/serverMulti ./bin/client ./bin/test_client ./bin/test_server
