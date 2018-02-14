#include "hf/sxwlhead.h"

using namespace std;

extern int AccRequest(int);
extern int GetCliAddr(int);
extern int ListenConnect(uint16_t,const char* lisIp = "0.0.0.0",unsigned int lisNq = 100);
extern string ConfQuery(string);

int main(){
	string sLisPort = ConfQuery("Port");
	if (sLisPort == ""){
		sLisPort = "80";
	}

	uint16_t lisPort = atoi(sLisPort.c_str());

	const char *lisIp = ConfQuery("Listen").c_str();

	int servIp = ListenConnect(lisPort,lisIp);
	if (servIp == IPADDRERR){
		cout << "Sorry,Your IPAddress Error";
		return 1;
	} else if (servIp == BINDERR){
		cout << "Sorry,Bind Error";
		return 1;
	}

	/*int val = 1;
	if (setsockopt(servIp,SOL_SOCKET,SO_KEEPALIVE,&val,sizeof(val)) != 0){
		cout << "Keep Alive Error";
	}
	*/
	while(true){
		int cliAddr = GetCliAddr(servIp);
		if (cliAddr == 1){
			return 1;
		}
		AccRequest(cliAddr);
		//thread new_Request(AccRequest,cliAddr);
		//new_Request.detach();
	}
}
