#include "../hf/sxwlhead.h"

using namespace std;

extern int ListenConnect(uint16_t lisPort = 80,const char *lisIp = "0.0.0.0",unsigned int lisNq = 5);
extern int AcceptConnect(int,string*,uint16_t*);
extern int SendSession(int,string);
extern int RecvSession(int,char*,unsigned int);
extern int CloseSocket(int,int);


int HttpRequest(int,string*);

extern int AccRequest(string *httpCode){
	int servIp = ListenConnect(1208);
	if (servIp == IPADDRERR){
		cout << "Sorry,Your IPAddress Error";
	} else if (servIp == BINDERR){
		cout << "Sorry,Bind Error";
	}
	string cliIp;
	uint16_t cliPort;
	int accCli = AcceptConnect(servIp,&cliIp,&cliPort);
	/*
	 * cliIp is user ip address
	 * cliport is user connect port
	 * give to log moudles
	 */
	char recvHeader[2048];
	RecvSession(accCli,recvHeader,2048);
	/*must accept httpheader*/

	//cout << recvHeader;
	if (HttpRequest(accCli,httpCode) == -1){
		cout << "Sorry,Send Error";
	}
	CloseSocket(accCli,2);
	return 0;
}

int HttpRequest(int cliAddr,string *pageCode){
	string httpdata;
	//const char* to string
	httpdata = "HTTP/1.1 200 OK\r\n";
	httpdata += "Server: wlsx/test\r\n";
	httpdata += "Content-Type: text/html\r\n";
	httpdata += "\r\n";
	httpdata += *pageCode;
	if (SendSession(cliAddr,httpdata) == SENDERR){
		return -1;
	} else {
		return 0;
	}
}
