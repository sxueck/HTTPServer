#include "../hf/sxwlhead.h"

using namespace std;

extern int AccRequest(int,string*);
extern int GetCliAddr(int);
extern int ListenConnect(uint16_t lisPort = 80,const char *lisIp = "0.0.0.0",unsigned int lisNq = 100);

int main(){
	string sourceCode = "<center>working</center>";
	int servIp = ListenConnect(1208);
	if (servIp == IPADDRERR){
		cout << "Sorry,Your IPAddress Error";
		return 1;
	} else if (servIp == BINDERR){
		cout << "Sorry,Bind Error";
		return 1;
	}

	int val = 1;
	if (setsockopt(servIp,SOL_SOCKET,SO_KEEPALIVE,&val,sizeof(val)) != 0){
		cout << "Keep Alive Error";
	}
	while(true){
		int cliAddr = GetCliAddr(servIp);
		if (cliAddr == 1){
			return 1;
		}
		thread new_Request(AccRequest,cliAddr,&sourceCode);
		new_Request.detach();
	}
}
