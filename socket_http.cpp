#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <iostream>
//#include <time.h>
#include <unistd.h>
#include <string>
#include <sstream>
using namespace std;
int main()
{
 int sockfd;
 int len;
 struct sockaddr_in address; 
 struct hostent *server;
 int result;
//club.edu.sina.com.cn/bbs/forum-209-1.html
 string path("/index.html");
 string host("127.0.0.1");
 stringstream stream;
 //GET请求方式
 
 stream<< "GET " << path << " HTTP/1.1\r\n"
         << "Host: " << host << "\r\n"
         <<"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n"
         << "Connection:close\r\n"
         << "\r\n";
 
 //POST请求方式
 // char *post_content = new char[128];
 // memcpy(post_content,"id=*********&pw=*********",128);
 // int content_length = strlen(post_content);
 // cout<<"content length is "<<content_length<<endl;
 // stream<< "POST " << path << " HTTP/1.0\r\n"
 //            << "Host: " << host << "\r\n"
 //           <<"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n"
 //           <<"Content-Type:application/x-www-form-urlencoded\r\n"
 //           <<"Content-Length:"<<content_length<<"\r\n"
 //           <<"Connection:close\r\n"
 //           << "\r\n"
 //           <<post_content;

 // delete[] post_content;
  
  // socket connect
  /*
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    cout << "Could not open socket\n";
    exit(1);
  }

  bzero((char *)  &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  if (!inet_aton(address.c_str(), &serv_addr.sin_addr)) {
    cout << "Server address is not a valid IP address";
    return 1;
  }
  serv_addr.sin_port = htons(4567);

  int rc = connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
  if (rc < 0) {
    cout << "Could not connect to server\n";
    exit(1);
  }
  */

 string request = stream.str();
 sockfd = socket(AF_INET,SOCK_STREAM,0);
 address.sin_family = AF_INET;
 //server = gethostbyname(host.c_str()); 
 //memcpy((char *)&address.sin_addr.s_addr,(char*)server->h_addr, server->h_length);
 inet_aton(host.c_str(), &address.sin_addr);
 address.sin_port = htons(443);
 len = sizeof(address);
 result = connect(sockfd,(struct sockaddr *)&address,len);
 
 if(result==-1){
        cout<<"connection error!"<<endl; 
 }
 write(sockfd,request.c_str(),request.size());
 char buf[1024*1024];
 memset(buf,0,1024*1024);
 int offset = 0;
 int rc;
 while(rc = read(sockfd,buf+offset,1024)){
      offset += rc;
 }
 
 close(sockfd);
 buf[offset] = 0;
// cout<<strlen(buf)<<endl;
 cout<<buf<<endl;
 /*
 int size = offset;
 int outlen = 2*size; //  注意编码转换之后的字符串长度会发生变化，因此此处定义为2倍长度，确保能够容纳转换之后得到的字符串
 char *output = new char[outlen];
 memset(output,0,outlen);
 //进行编码转换，将gbk转换为utf-8
 covert("utf-8","gbk",buf,size,output,outlen);
 output[outlen] = 0;
 cout<<strlen(output)<<endl;
// cout<<output<<endl;
 delete[] output;
 */
 return 0;
}
//使用libiconv库实现的编码转换函数

//  int covert(char *desc, char *src, char *input, size_t ilen, char *output, size_t olen)
// {
//     char **pin = &input;
//     char **pout = &output;
//     iconv_t cd = iconv_open(desc, src);
//     if (cd == (iconv_t)-1)
//     {
//   iconv_close(cd);
//         return -1;
//     }
//     memset(output, 0, olen);
//     if (iconv(cd, pin, &ilen, pout, &olen)){
//   cout<<"convert failed!"<<endl;
//   iconv_close(cd);
//   return -1;
//  }
//     iconv_close(cd);
//     return 0;
// }