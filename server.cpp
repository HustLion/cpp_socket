/*
 * =====================================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  socket 编程，服务器端
 *
 *        Version:  1.0
 *        Created:  2017/08/30 15时01分38秒
 *       Revision:  none
 *       Compiler:  gcc (g++ on MacOS)
 *       g++ -o server server.cpp
 *
 *         Author:  Jeremy Gong (Hustlion), hustlionm@qq.com
 *   Organization:  Hust
 *
 * =====================================================================================
 */
#include <unistd.h>
// #include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>


const int kPort = 4897;
const int kQLEN = 100;
const int kBLEN = 256;

int visits;

int main() {
    struct sockaddr_in self, client;
    struct hostent *cp;
    int sd, td, len;
    char buf[kBLEN] = "Greetings from server!";

    sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset((char *) &self, 0, sizeof(struct sockaddr_in));
    self.sin_family = AF_INET;
    self.sin_addr.s_addr = INADDR_ANY;
    self.sin_port = htons((u_short) kPort);

    bind(sd, (struct sockaddr *) &self, sizeof(struct sockaddr_in));

    listen(sd, kQLEN);
    std::cout << "Server online" << std::endl;

    while (1) {
        len = sizeof(struct sockaddr_in);
        td = accept(sd, (struct sockaddr *) &client, (socklen_t *)&len);

        cp = gethostbyaddr((char *) &client.sin_addr, sizeof(struct in_addr), AF_INET);
        std::cout << "Connected from " << ((cp && cp->h_name) ? cp->h_name : inet_ntoa(client.sin_addr)) << std::endl;

        ++visits;
        std::cout << "This server has been contacted " << visits << " time(s)." << std::endl;
        send(td, buf, strlen(buf), 0);
        close(td);
    }

    exit(0);
    return 0;
}

