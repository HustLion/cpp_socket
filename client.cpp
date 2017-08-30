/*
 * =====================================================================================
 *
 *       Filename:  client.cpp
 *
 *    Description:  客户端程序
 *
 *        Version:  1.0
 *        Created:  2017/08/30 20时12分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *       g++ -o client client.cpp
 *
 *         Author:  Jeremy Gong (Hustlion), hustlionm@qq.com
 *   Organization:  Hust
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
// #include <string>
#include <iostream>

const char kServer[] = "localhost";
const int kPort = 4897;
const int kBlen = 128;

int main() {
    struct sockaddr_in server;
    struct hostent *sp;
    int sd, n;
    char buf[kBlen];

    sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset((char *)&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(kPort);
    sp = gethostbyname(kServer);

    connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));

    n = recv(sd, buf, sizeof(buf), 0);
    while (n > 0) {
        write(1, buf, n);
        n = recv(sd, buf, sizeof(buf), 0);
    }

    close(sd);
    exit(0);
    return 0;
}
