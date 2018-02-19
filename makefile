CC = g++
CFLAGS = -std=c++11 -Wl,--no-as-needed -pthread -g

sxwl:
	$(CC) $(CFLAGS) -o sxwl \
			  main.cpp \
			  src/request.cpp \
			  src/optionFile.cpp \
			  src/mycode/SocketOption.cpp \
			  src/httpdeal/mime.cpp \
			  src/httpdeal/httperror.cpp

clean:
	rm sxwl
