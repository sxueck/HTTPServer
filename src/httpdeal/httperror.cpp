#include "../../hf/sxwlhead.h"

using namespace std;

extern int SendSession(int,string);

int servAddr;

void urlToLong();

extern void HttpError(int erCode,int servAddrSocket){
	servAddr = servAddrSocket;
	switch (erCode){
		case 2:
			urlToLong();
		default:
			return;
	}
}

void urlToLong(){
	string httpData = "HTTP/1.1 414 Request-URI Too Long\r\n";
	httpData += "Connection: close\r\n";
	httpData += "\r\n";
	SendSession(servAddr,httpData);
}

void urlNotFound(){
	string httpData = "HTTP/1.1 404 Not Found\r\n";
	SendSession(servAddr,httpData);
}
