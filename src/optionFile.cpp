#include "../hf/sxwlhead.h"

#define CONFFILE "./conf-file/sxwl.conf"

using namespace std;

void WrLog(string,string,string);
string ConfQuery(string);
string PageQu(string);

extern void WrLog(string acUrl,string acIp,string acPort)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	ofstream inLog("/var/inLog.txt",ios::app);
	inLog << 1900+ltm -> tm_year << "/" << 1+ltm -> tm_mon << "/" << ltm -> tm_mday << "-" << ltm -> tm_hour << ":" << ltm -> tm_min << "-"  << acIp << ":" << acPort << "->" << acUrl;
	inLog << "\n";
	inLog.close();
}

extern string ConfQuery(string Query)
{
	char *pbuf;
	FILE *pfile;
	long size;
	char *buffer;
	size_t result;
	string tmp3;
	string ret;
	pfile = fopen(CONFFILE,"rb");	//以二进制的方式打开
	if (pfile == 0x00){
		cout << "file not found";
		return "";
	}
	//统计文件大小
	fseek(pfile,0,SEEK_END);
	size = ftell (pfile);
	rewind(pfile);
	buffer = new char[size];
	result = fread(buffer,1,size,pfile);
	string bufStr(buffer);
	int rvKeyLo = bufStr.find(Query);
	if (rvKeyLo >= 0)
	{
		int rvKeyCount  = Query.size()+1;
		rvKeyLo += rvKeyCount;
		while(bufStr.c_str()[rvKeyLo] != ';')
		{
			ret += bufStr.c_str()[rvKeyLo];
			rvKeyLo++;
		}
	   fclose(pfile);
	   delete[] buffer;
		return ret;
	}
	else
	{
	   fclose(pfile);
	   delete[] buffer;
		return ret = "error";
	}
}

extern string PageQu(string page)
{
	long size;
	char *buffer;
	//string directory = ConfQuery("WebRoot");
	//directory += page;
	ifstream ifstr;
	ifstr.open(page,ios::in|ios::binary);
	if (!ifstr)
	{
		return "";
	}
	else
	{
      ifstr.seekg(0,ios::end);
      size = ifstr.tellg();
      buffer = new char[size];
      ifstr.seekg(0,ios::beg);
      ifstr.read(buffer,size);
      string rePageCode(buffer);
		ifstr.close();
		return rePageCode;
	}
}
