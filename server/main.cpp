#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "config.hpp"
#include "httpRequest.cpp"
#include "stringHelper.cpp"

struct cln
{
    int cfd;
    struct sockaddr_in caddr;
};

void *cthread(void *arg)
{
    struct cln *c = (struct cln *)arg;

    // 1450 due to TCP MTU
    char buffer[1450] = {};
    read(c->cfd, buffer, 1450);
    std::stringstream firstPacket{buffer};

    size_t contentLength = 0;

    // Read Content-Length from the first TCP packet
    // If not header not provided equals 0
    std::string line;
    while (std::getline(firstPacket, line))
    {
        auto words = own::splitByDelimiter(line, ' ');
        if (words.at(0) == "Content-Length:")
        {
            contentLength = std::stoi(words.at(1));
            break;
        }
    };

    std::string request{firstPacket.str()};

    // Read entire request body
    while (own::getBodySizeFromRawRequest(request) < contentLength)
    {
        char buffer[1450] = {};
        read(c->cfd, buffer, 1450);
        request += buffer;
    }

    const auto response = own::proceedRequest(request);

    write(c->cfd, response.c_str(), response.size());
    close(c->cfd);
    free(c);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    std::cout << "Server is running at: http://localhost:" << SERVER_PORT << "\n" << std::flush;

    pthread_t tid;
    socklen_t slt;
    int sfd, on = 1;
    struct sockaddr_in saddr;

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(SERVER_PORT);
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
    listen(sfd, 5);

    while (1)
    {
        struct cln *c = new cln;
        slt = sizeof(c->caddr);
        c->cfd = accept(sfd, (struct sockaddr *)&c->caddr, &slt);
        pthread_create(&tid, NULL, cthread, c);
        pthread_detach(tid);
    }

    close(sfd);
    return EXIT_SUCCESS;
}
