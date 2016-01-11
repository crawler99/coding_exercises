#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Server.hpp"

#define MAXLINE 1024

void Server::run()
{
    std::thread svrThread(&Server::_listen, this);
    svrThread.join();
}

void Server::_listen()
{
    int socket_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buff[MAXLINE];

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {  
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);  
        exit(0);  
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(_port);

    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {  
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);  
        exit(0);  
    } 

    if (listen(socket_fd, 10) == -1)
    {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);  
        exit(0);
    }

    printf("waiting for client's request <<< \n");
    while (true)
    {
        socklen_t len = sizeof(client_addr);
        if ((client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &len)) == -1)
        {
            printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
            continue;
        }

        printf("connection from %s, port %d\n", 
                inet_ntop(AF_INET, &client_addr.sin_addr, buff, sizeof(buff)),
                ntohs(client_addr.sin_port));

        int flag = 1;
        if (-1 == setsockopt(client_fd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag)))
        {
            perror("setsockopt() error: John Nagle");
            close(client_fd);
            continue;
        }

        // spawn twice to eliminate zombie process
        pid_t pid;                
        if ((pid = fork()) == 0)
        {
            close(socket_fd);
            if (fork() == 0)
            {
                close(socket_fd);
                ssize_t n;
                while ((n = recv(client_fd, buff, MAXLINE, 0)) > 0)
                {
                    send(client_fd, buff, n, 0);
                }
                close(client_fd);
                exit(0);
            }
            else
            {
                close(client_fd);
                exit(0);
            }
        }
        else
        {
            close(client_fd);
            if (waitpid(pid, NULL, 0) != pid)
            {
                perror("waiting for the son process error");
            }
        }
    }
}

