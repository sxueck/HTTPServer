#include "../hf/sxwlhead.h"

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
	httpData += "<h2>414 Error,URL To Long....^_^</h2>\r\n";
	SendSession(servAddr,httpData);
}
