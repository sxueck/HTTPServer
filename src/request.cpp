#include "../hf/sxwlhead.h"

using namespace std;

#define URLLEN 256
#define URLLEN_BOOM 100

extern int AcceptConnect(int,string*,uint16_t*);
extern int SendSession(int,string*,long long);
extern int RecvSession(int,char*,unsigned int);
extern int CloseSocket(int,int);
extern void HttpError(int,int);
extern string ConfQuery(string);
extern string PageQu(string);
extern string httpMime(string);
extern string createShellProcess(const char*);

int HttpRequest(int,string*,string);
int HttpRequest(int,byte*,string,long long);

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

extern int AccRequest(int accCli){
	char recvHeader[2048];
	char method[4];
	
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
	string surl;
	if (strcmp(method,"POST") || strcmp(method,"GET")){
		while(!isspace(recvHeader[++i])){
			surl += recvHeader[i];
			if (i == 2048){
				HttpError(2,accCli);
				CloseSocket(accCli,0);
				return 0;
			}
		}
	}
	i -= 4;
	//del "post" or "get"
	
   string dePage = ConfQuery("DefaultPage");
	if (surl[surl.length() - 1] == '/'){
		surl += dePage;
	}
   //cout << surl << endl;
   
   string fileContentType = httpMime(surl);
   
   string pagePath = ConfQuery("WebRoot") + surl;
   //binary file read

   string pageCode = PageQu(pagePath);
   if (pageCode == ""){
      cout << "file read error";
      HttpError(3,accCli);
      return -1;
   }

   if (fileContentType == "text/plain" | fileContentType == "text/html" | fileContentType == "application/x-javascript" | fileContentType == "text/css"){
      //this is text mime
      //cout << endl << fileContentType;
      if (fileContentType != "php"){
         HttpRequest(accCli,&pageCode,fileContentType);
      } else {
         cout << endl << "php";
         return -1;
      }
   } else {
      ifstream file(pagePath,ios::in);

      if (!file){
         file.close();
         HttpError(3,accCli);
         return -1;
      }

      file.seekg(0,ios_base::end);
      long long fSize = file.tellg();
      //cout << fSize;
      byte *binData = new byte[fSize];
      //bit data byte value
      file.seekg(0,ios::beg);
      file.read((char*)binData,fSize);
      file.close();
      if (HttpRequest(accCli,binData,fileContentType,fSize) == -1){
         cout << "Sorry,Send Error";
      }
      /*CFile fileSize;
      if (fileSize.Open(pagePath,CFile::modeRead)){
         long long size = fileSize.GetLength();
         void *binValue = malloc(size);
         //binary data value
         BinaryRead(binValue,size);
      }
      this's Windows MFC!!!
      */
   }

	//clear memory
	CloseSocket(accCli,2);
	return 0;
}

int HttpRequest(int cliAddr,string *pageCode,string ContentType){
	//text send
   string httpdata; 
	//const char* to string
	httpdata = "HTTP/1.1 200 OK\r\n";
	httpdata += SERVERINFO;
	httpdata += "Content-Type: "+ ContentType + "\r\n";
	httpdata += "Content-Length: " + to_string(pageCode->length())  + "\r\n";
	httpdata += "Connection: keep-alive\r\n";
	httpdata += "\r\n";
	httpdata += *pageCode;
   httpdata += "\r\n";
   //cout << endl << httpdata;
	if (SendSession(cliAddr,&httpdata,httpdata.length()) == SENDERR){
		return -1;
	} else {
		return 0;
	}
}

int HttpRequest(int cliAddr,byte *binFileData,string ContentType,long long ContentSize){
   //binary send
   string httpdata;
   httpdata = "HTTP/1.1 200 OK\r\n";
   httpdata += SERVERINFO;
   httpdata += "Content-Type: " + ContentType + "\r\n";
   httpdata += "Content-Length: " + to_string(ContentSize) + "\r\n";
   httpdata += "Connection: keep-alive\r\n";
   httpdata += "\r\n";
   httpdata.append((const char*)binFileData,ContentSize);
   httpdata += "\r\n";
   //cout << httpdata.length();
   if (SendSession(cliAddr,&httpdata,httpdata.length()) == SENDERR){
      return -1;
   } else {
      return 0;
   }
}
