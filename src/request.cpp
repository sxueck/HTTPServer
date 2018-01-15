#include "../hf/sxwlhead.h"

using namespace std;

#define URLLEN 256
#define URLLEN_BOOM 100

extern int AcceptConnect(int,string*,uint16_t*);
extern int SendSession(int,string);
extern int RecvSession(int,char*,unsigned int);
extern int CloseSocket(int,int);
extern void HttpError(int,int);

int HttpRequest(int,string*);

extern int GetCliAddr(int servIp){
	string cliIp;
	uint16_t cliPort;
	int accCli = AcceptConnect(servIp,&cliIp,&cliPort);
	/*
	 * cliIp is user ip address
	 * cliport is user connect port
	 * give to log moudles
	 */

	return accCli;
}

extern int AccRequest(int accCli,string *httpCode){
	char recvHeader[2048];
	vector<char> url(URLLEN);
	char method[4];
//	while(true){
		memset(method,'\0',4);
		memset(recvHeader,'\0',2048);
		//full '0'

		if (RecvSession(accCli,recvHeader,2048) == RECVERR){
			cout << "Recv Error";
			/*must accept httpheader*/
			return 1;
		}

		//cout << recvHeader;
		//judge "post" or "get"
	
		int i = 0;
		while (!isspace(recvHeader[i]) && (i < sizeof(recvHeader) - 1)){
			method[i] = recvHeader[i];
			i++;
		}

		if (strcmp(method,"POST") || strcmp(method,"GET")){
			while(!isspace(recvHeader[++i])){
				//url.push_back(recvHeader[i]);
				url[ i - sizeof(method)/sizeof(char) ] = recvHeader[i];
				if (i == URLLEN - URLLEN_BOOM ){
					url.resize(URLLEN * 2);
				} else if (i == (URLLEN * 2 - URLLEN_BOOM)){
					url.resize(URLLEN * 4);
				} else if (i == (URLLEN * 4) - URLLEN_BOOM){
					url.resize(URLLEN * 8);
				} else if (i == 2048){
					HttpError(2,accCli);
					CloseSocket(accCli,0);
					return 0;
				}
				//best many for 2048
			}
		}
		i -= 4;
		//del "post" or "get"
	char indexPage[] = "index.html";
	if (url[i] == '/'){
		url.resize(i + 1);
		url.push_back(*indexPage);
	}

		for (int j = 0;j <= i;j++){
			cout << url[j];
		}
	
		//cout << recvHeader;
		if (HttpRequest(accCli,httpCode) == -1){
			cout << "Sorry,Send Error";
		}
		vector<char>().swap(url);
		//clear memory
	//}
	CloseSocket(accCli,2);
	return 0;
}

int HttpRequest(int cliAddr,string *pageCode){
	string httpdata;	
	//const char* to string
	httpdata = "HTTP/1.1 200 OK\r\n";
	httpdata += "Server: wlsx/test\r\n";
	httpdata += "Connection: keep-alive\r\n";
	httpdata += "Content-Type: text/html\r\n";
	httpdata += "Content-Length: " + to_string(strlen(pageCode->c_str())) + "\r\n";
	httpdata += "\r\n";
	httpdata += *pageCode;
	if (SendSession(cliAddr,httpdata) == SENDERR){
		return -1;
	} else {
		return 0;
	}
}
