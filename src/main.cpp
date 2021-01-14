#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <array>
#include <iostream>
#include <string>

#include "config.hpp"
#include "requestExecutor.hpp"
#include "requestParser.hpp"
#include "requestReader.hpp"
#include "stringHelper.hpp"

struct cln
{
    int cfd;
    struct sockaddr_in caddr;
};

void *cthread(void *arg)
{
    struct cln *c = (struct cln *)arg;

    const auto request = own::readRawRequestFromSocket(c->cfd);
    const auto params = own::parseRequest(request);
    auto response = own::executeRequest(params) + "\n";
    response = own::findAndReplaceAll(response, "\n", "\r\n");

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
