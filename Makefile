### Makefile Load Balancer project

## Author: sebastian@wormwood
## Keywords: c/c++ socket linux
CPP = g++
CFLAGS = -O2
OBJ = ClientSocket.o ServerSocket.o Socket.o
RM = rm -f
BIN = agent

Socket.o: 
	$(CPP) $(CFLAGS) -c Socket.cc -o Socket.o
ClientSocket.o: Socket.o
	$(CPP) $(CFLAGS) -c ClientSocket.cc -o ClientSocket.o
ServerSocket.o: Socket.o
	$(CPP) $(CFLAGS) -c ServerSocket.cc -o ServerSocket.o
all: Socket.o ClientSocket.o ServerSocket.o
	$(CPP) $(CFLAGS) $(OBJ) agent.cc -o $(BIN)
clean: 
	${RM} $(OBJ) $(BIN)





### Makefile ends here
