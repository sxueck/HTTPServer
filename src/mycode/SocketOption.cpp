#include "../../hf/net.h"

using namespace std;

extern int ListenConnect(uint16_t lisPort,const char *lisIp,unsigned int lisNq){
   /*lisProt need uint16_t and between to 0-65535(under 1024 need root)*/
   int servSock = socket(PF_INET,SOCK_STREAM,0);
   
   struct in_addr netAddr;
   struct sockaddr_in servInfo;
   servInfo.sin_family = AF_INET;
   servInfo.sin_port = htons(lisPort);
   if (inet_aton(lisIp,&netAddr) != 0){
      servInfo.sin_addr.s_addr = netAddr.s_addr;
   } else {
      return IPADDRERR;
   }

   if (bind(servSock,(struct sockaddr*)&servInfo,sizeof(servInfo)) != 0){
      return BINDERR;
       /*check:root,port num*/
   }
   listen(servSock,lisNq);
   return servSock;
}

extern int AcceptConnect(int servSock,string *reCliAddr,uint16_t *reCliPort){
   /*return client ip and port*/
   struct sockaddr_in cliScok;
   socklen_t cliScokLen = sizeof(cliScok);
   int accAddr = accept(servSock,(struct sockaddr*)&cliScok,&cliScokLen);

   /*char buff[255];
   printf("conn from %s:%d",inet_ntop(AF_INET,&cliScok.sin_addr,buff,sizeof(buff)),ntohs(cliScok.sin_port));*/
   
   char tmpText[IPLEN];
   if (reCliAddr != NULL){
      *reCliAddr = inet_ntop(AF_INET,&cliScok.sin_addr,tmpText,IPLEN);
   }
   if (reCliPort != NULL){
      *reCliPort = ntohs(cliScok.sin_port);
   }

   return accAddr;
}

extern int SendSession(int sdAccAddr,string *sendStr,long long strLength){
   int reSendSs = write(sdAccAddr,sendStr->c_str(),strLength);
/*   struct iovec wr_iov;
   wr_iov.iov_len = strLength;
   
   void* sStrCopy = malloc(strLength);
   memcpy(sStrCopy,sendStr->c_str(),strLength);
   //const void* to void*,copy memory to void*

   wr_iov.iov_base = sStrCopy;

   free(sStrCopy);

   ssize_t nWrite = writev(sdAccAddr,&wr_iov,1);
	//int reSendSs = send(sdAccAddr,sendStr,(int)sizeof(sendStr),0);
   if (nWrite == -1 ){
      return SENDERR;
   }*/
	return 0;
}

extern int RecvSession(int rvAccAddr,char *txtBuffer,unsigned int txtLen){
	struct iovec iov;
	iov.iov_base = txtBuffer;
	iov.iov_len = txtLen;
	if (readv(rvAccAddr,&iov,1) != -1){
		return 0;
	} else {
		return RECVERR;
	}
}

extern void CloseSocket(int servSock,int closeNum){
	//SD_RECEIVE:recv 0
	//SD_SEND:send 1
	//SD_BOTH:all 2
	
	switch(closeNum){
		case 0:
			shutdown(servSock,SHUT_RD);
		case 1:
			shutdown(servSock,SHUT_WR);
		default:
			shutdown(servSock,SHUT_RDWR);
	}
}

/*extern string createShellProcess(const char* cmd){
   char *result;
   FILE *fpRead = popen(cmd,"r");
   char htmlCodeRecv[1000000];
   //test
   memset(htmlCodeRecv,'\0',1000000);
   while(fgets(htmlCodeRecv,1000000-1,fpRead) != NULL){
      result = htmlCodeRecv;
   }
   if (fpRead != NULL){
      pclose(fpRead);
   }
   string strResult(result);
   return strResult;
}*/
