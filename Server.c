#include "Server.h"

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
int checker() {
    for(int i = 0; i < 3; i++) {
        if(ticTacToeArrayS[0][i] == ticTacToeArrayS[1][i] && ticTacToeArrayS[0][i] == ticTacToeArrayS[2][i] && ticTacToeArrayS[0][i] != 0) {
            return ticTacToeArrayS[0][i];
        }
        if(ticTacToeArrayS[i][0] == ticTacToeArrayS[i][1] && ticTacToeArrayS[i][0] == ticTacToeArrayS[i][2] && ticTacToeArrayS[i][0] != 0) {
            return ticTacToeArrayS[i][0];
        }
    }
    if(ticTacToeArrayS[0][0] == ticTacToeArrayS[1][1] && ticTacToeArrayS[0][0] == ticTacToeArrayS[2][2] && ticTacToeArrayS[0][0] != 0) {
        return ticTacToeArrayS[0][0];
    }
    if(ticTacToeArrayS[0][2] == ticTacToeArrayS[1][1] && ticTacToeArrayS[0][2] == ticTacToeArrayS[2][0] && ticTacToeArrayS[0][2] != 0) {
        return ticTacToeArrayS[0][2];
    }
    return 0;
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

            int x = buffer[0]-'0';
            int y = buffer[1]-'0';
            ticTacToeArrayS[x][y] = 1;
            player1Play = false;

            buffer[2] = checker() + '0';
            n = write(player2, buffer, strlen(buffer)+1);
        }
        else {
            n = read(player2, buffer, 255);

            int x = buffer[0]-'0';
            int y = buffer[1]-'0';
            ticTacToeArrayS[x][y] = 2;
            player1Play = true;

            buffer[2] = checker() + '0';
            n = write(player1, buffer, strlen(buffer)+1);
        }
        if(checker() != 0) {
            n = write(player2, buffer, strlen(buffer)+1);
            n = write(player1, buffer, strlen(buffer)+1);
            break;
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
    close(player2);
    close(sockfd);
}


