#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

bool connectionSuccesful = false;

int sockfd, newsockfd;
socklen_t cli_len;
struct sockaddr_in serv_addr, cli_addr;
int n;
char buffer[256];

int ticTacToeArray[3][3];

bool connEst(char *conn[]) {

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(conn[0]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return false;
    }

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket address");
        return false;
    }

    listen(sockfd, 5);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ticTacToeArray[i][j] = 0;
        }
    }
    return true;
}

void comunication() {
    cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        //return 3;
    }
    for(;;) {

        bzero(buffer,256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            //return 4;
        }
        printf("Here is the message: %s\n", buffer);

        const char* msg = "I got your message";
        n = write(newsockfd, msg, strlen(msg)+1);
        if (n < 0)
        {
            perror("Error writing to socket");
            //return 5;
        }


    }
    close(newsockfd);
}

void offServer() {
    close(sockfd);
}

