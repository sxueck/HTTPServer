#include "../../hf/sxwlhead.h"

using namespace std;

extern string httpMime(string urlStr){
   //get me all url string
   string extName;
   
   int i = urlStr.length();
   while(true){
      if (urlStr[i] != '.'){
         extName += urlStr[i];
         i--;
      } else {
         break;
      }
   }

   reverse(extName.begin(),extName.end());
  
   //mime dic
   map<string,string> mime;
   mime["avi"] = "video/x-msvideo";
   mime["bmp"] = "image/bmp";
   mime["c"] = "text/plain";
   mime["cpp"] = "text/plain";
   mime["crt"] = "application/x-x509-ca-cert";
   mime["css"] = "text/css";
   mime["der"] = "application/x-x509-ca-cert";
   mime["dll"] = "application/x-msdownload";
   mime["doc"] = "application/msword";
   mime["exe"] = "application/octet-stream";
   mime["gif"] = "image/gif";
   mime["gz"] = "application/x-gzip";
   mime["htm"] = "text/html";
   mime["html"] = "text/html";
   mime["ico"] = "image/x-icon";
   mime["jpeg"] = "image/jpeg";
   mime["jpg"] = "image/jpeg";
   mime["js"] = "application/x-javascript";
   mime["mp3"] = "audio/mpeg";
   mime["mpeg"] = "video/mpeg";
   mime["ppt"] = "application/vnd.ms-powerpoint";
   mime["php"] = "text/html";
   mime["png"] = "image/png";
   mime["tar"] = "application/x-tar";
   mime["tgz"] = "application/x-compressed";
   mime["txt"] = "text/plain";
   mime["ogg"] = "audio/ogg";
   mime["wav"] = "audio/x-wav";
   mime["zip"] = "application/zip";
   mime["other"] = "application/octet-stream";
   
   map<string,string>::iterator findIter = mime.find(extName.c_str());
   if (findIter == mime.end()){
      extName = "other";
   }
   return mime[extName.c_str()];
}
