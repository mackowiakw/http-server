#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "httpRequest.cpp"
#include "stringHelper.cpp"

constexpr int SERVER_PORT = 1234;

struct cln {
    int cfd;
    struct sockaddr_in caddr;
};

void* cthread(void* arg) {
    struct cln* c = (struct cln*)arg;
    printf("new connection: %s", inet_ntoa((struct in_addr)c->caddr.sin_addr));
    
    // 1450 due to TCP MTU
    char buffer[1450];
    read(c->cfd, buffer, 1450);
    std::string request {buffer};
    own::findAndReplaceAll(request, "\r\n", "\n");

    // printf("  |  Recived msg: %s\n", buffer);
    std::cout << "  |  Recived msg: " << request << "\n";
    std::string response = own::proceedRequest(request);
    own::findAndReplaceAll(response, "\n", "\r\n");

    write(c->cfd, response.c_str(), response.size());
    close(c->cfd);
    free(c);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    pthread_t tid;
    socklen_t slt;
    int sfd, on = 1;
    struct sockaddr_in saddr;

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(SERVER_PORT);
    sfd = socket (AF_INET, SOCK_STREAM, 0);
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr));
    listen(sfd, 5);

    while(1)
    {
        struct cln* c = new cln;
        slt = sizeof(c->caddr);
        c->cfd = accept(sfd, (struct sockaddr*)&c->caddr, &slt);
        pthread_create(&tid, NULL, cthread, c);
        pthread_detach(tid);
    } 
        
    close(sfd);
    return EXIT_SUCCESS;
}