#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 1024

void str_cli(FILE *fp, int sock_fd)
{
    char send_line[MAXLINE], recv_line[MAXLINE];

    while (nullptr != fgets(send_line, MAXLINE, fp)) 
    {
        auto send_len = strlen(send_line); // including the new line char at the end
        send(sock_fd, send_line, send_len, 0);

        auto recv_len = recv(sock_fd, recv_line, MAXLINE, 0);
        if (recv_len > 0)
        {
            recv_line[recv_len] = '\0';
            fputs(recv_line, stdout);
        }
        else
        {
            perror("str_cli: server terminated prematurely");
        }
    }
}

int main(int argc, char **argv)
{
    int sock_fd;
    struct sockaddr_in server_addr;

    if (argc != 3)
    {
        perror("usage: tcpcli <IPaddress> <IPport>");
        exit(0);
    }

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {  
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);  
        exit(0);  
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_aton(argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons(atoi(argv[2]));

    connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    str_cli(stdin, sock_fd);

    return 0;
}

