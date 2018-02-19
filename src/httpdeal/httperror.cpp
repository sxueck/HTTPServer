#include "../../hf/sxwlhead.h"

using namespace std;

extern int SendSession(int,string*,long long);

int servAddr;

void urlToLong();
void urlNotFound(string);

extern string PageQu(string);
extern string ConfQuery(string);

extern void HttpError(int erCode,int servAddrSocket){
   string errorPageDir = ConfQuery("ErrorPageDir");
	servAddr = servAddrSocket;

   char *pabuffer = getcwd(NULL,0);
   //read error page
   string thisDir(pabuffer);

	switch (erCode){
		case 2:
			urlToLong();
         break;
      case 3:
         urlNotFound(thisDir + "/html/404.html");
         break;
		default:
			return;
	}
}

void urlToLong(){
	string httpData = "HTTP/1.1 414 Request-URI Too Long\r\n";
   httpData += SERVERINFO;
   httpData += "Content-Length: 0\r\n\r\n";
	SendSession(servAddr,&httpData,httpData.length());
}

void urlNotFound(string pagePath){
	string httpData = "HTTP/1.1 404 Not Found\r\n";
   httpData += SERVERINFO;

   string pageCode = PageQu(pagePath);

   httpData += "Content-Type: text/html\r\n";
   httpData += "Content-Length: "+ to_string(pageCode.length()) + "\r\n\r\n";
   httpData += pageCode;
   httpData += "\r\n";
	SendSession(servAddr,&httpData,httpData.length());
}
