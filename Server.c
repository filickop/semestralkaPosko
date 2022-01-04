#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

bool connectionSuccesful = false;

int sockfd, player1, player2;
socklen_t cli_len;
struct sockaddr_in serv_addr, cli_addr;
int n;
char buffer[256];

int ticTacToeArrayS[3][3];

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
            ticTacToeArrayS[i][j] = 0;
        }
    }
    return true;
}

void comunication() {
    cli_len = sizeof(cli_addr);
    player1 = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    player2 = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    if (player1 < 0 || player2 < 0)
    {
        perror("ERROR on accept");
        //return 3;
    }
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++) {
            ticTacToeArrayS[x][y] = 0;
        }
    }
    bool player1Play = true;
    for(;;) {

        bzero(buffer,256);
        if(player1Play) {
            n = read(player1, buffer, 255);
            n = write(player2, buffer, strlen(buffer)+1);
            int x = buffer[0]-'0';
            int y = buffer[1]-'0';
            ticTacToeArrayS[x][y] = 1;
            player1Play = false;
        }
        else {
            n = read(player2, buffer, 255);
            n = write(player1, buffer, strlen(buffer)+1);
            int x = buffer[0]-'0';
            int y = buffer[1]-'0';
            ticTacToeArrayS[x][y] = 2;
            player1Play = true;
        }

        if (n < 0)
        {
            perror("Error reading from socket");
            //return 4;
        }
        printf("Here is the message: %s\n", buffer);

        //const char* msg = buffer;
        for(int x = 0; x < 3; x++){
            for(int y = 0; y < 3; y++) {
                printf("%d", ticTacToeArrayS[x][y]);
            }
            printf("\n");
        }





        if (n < 0)
        {
            perror("Error writing to socket");
            //return 5;
        }


    }
    close(player1);
}

void offServer() {
    close(sockfd);
}

